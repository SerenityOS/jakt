# Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
# Copyright (c) 2022, Ali Mohammad Pur <mpfard@serenityos.org>
#
# SPDX-License-Identifier: BSD-2-Clause

import argparse
import os
import subprocess
import sys
from pathlib import Path

# .lib on windows, .a otherwise
MAIN_LIBRARY_NAME = "libjakt_main_{}.a" if os.name != "nt" else "jakt_main_{}.lib"
RUNTIME_LIBRARY_NAME = (
    "libjakt_runtime_{}.a" if os.name != "nt" else "jakt_runtime_{}.lib"
)
WINDOWS_SPECIFIC_COMPILER_ARGUMENTS = (
    []
    if os.name != "nt"
    else [
        "-Xlinker",
        "/subsystem:console",
    ]
)


def main():
    # Parse arguments
    parser = argparse.ArgumentParser(description="Run a single test")
    parser.add_argument("temp_dir", help="Temporary directory to use")
    parser.add_argument("test_file", help="The test file to run")
    parser.add_argument(
        "--jakt-binary-dir",
        help="The directory to find the jakt binary in",
        default="build/bin",
    )
    parser.add_argument(
        "--jakt-lib-dir",
        help="The path to the jakt library directory",
        default="build/lib",
    )
    parser.add_argument(
        "--target-triple",
        help="The target triple of the host platform",
    )
    parser.add_argument(
        "--cpp-include",
        help="Additional include path",
    )
    parser.add_argument(
        "--cpp-compiler",
        help="Path to the C++ compiler to use (defaults to clang++ on $PATH)",
        default="clang++",
    )
    parser.add_argument(
        "--cpp-link",
        help="Extra C++ files to compile and link (separated by :)",
        default=":",
    )
    parser.add_argument(
        "--cpp-export-dir",
        help="Directory where exports should be generated, relative to the temp build directory",
        default="",
    )
    args = parser.parse_args()

    # Since we're running the output binary from a different
    # working directory, we need the full path of the binary.
    temp_dir = Path(args.temp_dir).resolve()
    test_file = Path(args.test_file).resolve()
    jakt_binary = Path(args.jakt_binary_dir).resolve() / (
        "jakt.exe" if os.name == "nt" else "jakt"
    )
    jakt_lib_dir = Path(args.jakt_lib_dir).resolve()
    target_triple = args.target_triple
    cpp_include = ""
    cpp_export_gen = ""
    cpp_export_include = ""
    cpp_compiler = args.cpp_compiler
    relevant_cpp_files = [Path(test_file.parent, x).resolve() for x in args.cpp_link.split(":") if len(x) > 0]

    if args.cpp_include:
        cpp_include = f"-I{Path(test_file.parent, args.cpp_include)}"

    if args.cpp_export_dir:
        path = temp_dir / args.cpp_export_dir
        cpp_export_gen = f"-E{path}"
        cpp_export_include = f"-I{path}"

    # clear the temp directory: go bottom up and remove files
    for root, _, files in os.walk(temp_dir, False):
        for file in files:
            os.remove(Path(root)  / file)

    runtime_path_for_stdlib = str(Path("./runtime").resolve())

    # Generate C++ code, exit with status == 3 on failure
    with open(temp_dir / "compile_jakt.err", "w") as stderr:
        try:
            subprocess.run(
                [
                    jakt_binary,
                    test_file,
                    "-B",
                    temp_dir,
                    "-S",
                    "-R",
                    runtime_path_for_stdlib,
                    cpp_export_gen,
                ],
                check=True,
                stderr=stderr,
                cwd=test_file.parent,
            )
        except subprocess.CalledProcessError as e:
            sys.exit(3)

    # Compile C++ code, exit with status == 2 on failure
    with open(temp_dir / "compile_cpp.err", "w") as stderr:
        try:
            command = [
                    cpp_compiler,
                    f"--target={target_triple}",
                    "-fdiagnostics-color=always",
                    "-std=c++23",
                    "-Wno-unknown-warning-option",
                    "-Wno-trigraphs",
                    "-Wno-parentheses-equality",
                    "-Wno-unqualified-std-cast-call",
                    "-Wno-user-defined-literals",
                    "-Wno-deprecated-declarations",
                    "-Iruntime",
                    cpp_include,
                    cpp_export_include,
                    "-DJAKT_CONTINUE_ON_PANIC",
                    "-o",
                    temp_dir / "output",
                    *WINDOWS_SPECIFIC_COMPILER_ARGUMENTS,
                    *(relevant_cpp_files + list(temp_dir.glob("*.cpp"))),
                    jakt_lib_dir
                    / target_triple
                    / MAIN_LIBRARY_NAME.format(target_triple),
                    jakt_lib_dir
                    / target_triple
                    / RUNTIME_LIBRARY_NAME.format(target_triple),
                ]
            command_string = ' '.join(f'"{x}"' for x in command)
            stderr.write(f"[Running command: {command_string} ]\n\n")
            subprocess.run(
                command,
                check=True,
                stderr=stderr,
            )
        except subprocess.CalledProcessError as e:
            sys.exit(2)

    # Run the executable inside the parent directory of the test file,
    # dump stderr into runtest.err and stdout into runtest.out in temp_dir
    # exit with status == 1 on failure
    with open(temp_dir / "runtest.out", "w") as stdout, open(
        temp_dir / "runtest.err", "w"
    ) as stderr:
        try:
            subprocess.run(
                [temp_dir / "output"],
                stdout=stdout,
                stderr=stderr,
                check=True,
                cwd=test_file.parent,
            )
        except subprocess.CalledProcessError:
            sys.exit(1)


if __name__ == "__main__":
    main()
