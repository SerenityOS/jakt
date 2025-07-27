# Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
# Copyright (c) 2022, Ali Mohammad Pur <mpfard@serenityos.org>
#
# SPDX-License-Identifier: BSD-2-Clause

import argparse
import os
import subprocess
import sys
from pathlib import Path
from dataclasses import dataclass

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

@dataclass
class RegularTestParams:
    temp_dir: Path
    jakt_binary: Path
    test_file: Path
    temp_dir: Path
    runtime_path_for_stdlib: Path
    cpp_export_gen: str
    cpp_compiler: str
    target_triple: str
    cpp_include: str
    cpp_export_include: str
    relevant_cpp_files: list[Path]
    jakt_lib_dir: Path

@dataclass
class OnHoverTestParams:
    temp_dir: Path
    runtime_path_for_stdlib: Path
    jakt_binary: Path
    test_file: Path
    line: int
    column: int


def run_on_hover(params: OnHoverTestParams):

    # find offset of line/column
    offset = 0
    with open(params.test_file, 'rb') as file:
        content = file.read()

        cur_line = 1
        while cur_line < params.line and offset < len(content):
            count = content[offset:].find(b'\n')
            if count == -1:
                offset = len(content)
                break
            cur_line += 1
            # skip over newline too
            offset += count + 1

        offset += params.column - 1

        offset = min(offset, len(content))

    # run on-hover stdout
    with open(params.temp_dir / "compile_jakt.err", "w") as stderr, open(params.temp_dir / "runtest.out", "w") as stdout:
        try:
            subprocess.run(
                [
                    params.jakt_binary,
                    "-e",
                    str(offset),
                    params.test_file,
                    "-R",
                    params.runtime_path_for_stdlib,
                ],
                check=True,
                stderr=stderr,
                stdout=stdout,
                cwd=params.test_file.parent,
            )
        except subprocess.CalledProcessError as e:
            sys.exit(3)

def run_regular_test(params: RegularTestParams):
   # Generate C++ code, exit with status == 3 on failure
    with open(params.temp_dir / "compile_jakt.err", "w") as stderr:
        try:
            subprocess.run(
                [
                    params.jakt_binary,
                    params.test_file,
                    "-B",
                    params.temp_dir,
                    "-S",
                    "-R",
                    params.runtime_path_for_stdlib,
                    params.cpp_export_gen,
                ],
                check=True,
                stderr=stderr,
                cwd=params.test_file.parent,
            )
        except subprocess.CalledProcessError as e:
            sys.exit(3)

    # Compile C++ code, exit with status == 2 on failure
    with open(params.temp_dir / "compile_cpp.err", "w") as stderr:
        try:
            command = [
                    params.cpp_compiler,
                    f"--target={params.target_triple}",
                    "-fdiagnostics-color=always",
                    "-std=c++23",
                    "-Wno-unknown-warning-option",
                    "-Wno-trigraphs",
                    "-Wno-parentheses-equality",
                    "-Wno-unqualified-std-cast-call",
                    "-Wno-user-defined-literals",
                    "-Wno-deprecated-declarations",
                    "-Iruntime",
                    params.cpp_include,
                    params.cpp_export_include,
                    "-DJAKT_CONTINUE_ON_PANIC",
                    "-o",
                    params.temp_dir / "output",
                    *WINDOWS_SPECIFIC_COMPILER_ARGUMENTS,
                    *(params.relevant_cpp_files + list(params.temp_dir.glob("*.cpp"))),
                    params.jakt_lib_dir
                    / params.target_triple
                    / MAIN_LIBRARY_NAME.format(params.target_triple),
                    params.jakt_lib_dir
                    / params.target_triple
                    / RUNTIME_LIBRARY_NAME.format(params.target_triple),
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
    with open(params.temp_dir / "runtest.out", "w") as stdout, open(
        params.temp_dir / "runtest.err", "w"
    ) as stderr:
        try:
            subprocess.run(
                [params.temp_dir / "output"],
                stdout=stdout,
                stderr=stderr,
                check=True,
                cwd=params.test_file.parent,
            )
        except subprocess.CalledProcessError:
            sys.exit(1)


def parse_line_col(arg: str):
    # handle placeholder for Windows empty values
    if arg == 'none':
        return None
    column = 1
    line, _, column_str = arg.partition(':')

    if line == 'none':
        return None

    try:
        line = int(line)
        if column_str:
            column = int(column_str)
    except ValueError:
        raise argparse.ArgumentTypeError("Expected format 'line:column' with integer values")

    return line, column


def main():
    # Parse arguments
    parser = argparse.ArgumentParser(description="Run a single test")
    parser.add_argument("temp_dir", help="Temporary directory to use")
    parser.add_argument("test_file", help="The test file to run")
    parser.add_argument("--hover-test", help="If test is a hover test, <LINE:COLUMN>", default=None, required=False, type=parse_line_col)
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

    runtime_path_for_stdlib = Path("./runtime").resolve()

    if args.hover_test:
        line,column = args.hover_test
        run_on_hover(OnHoverTestParams(temp_dir, runtime_path_for_stdlib, jakt_binary, test_file, line, column))
        return




    run_regular_test(RegularTestParams(
        temp_dir,
        jakt_binary,
        test_file,
        runtime_path_for_stdlib,
        cpp_export_gen,
        cpp_compiler,
        target_triple,
        cpp_include,
        cpp_export_include,
        relevant_cpp_files,
        jakt_lib_dir
    ))



 


if __name__ == "__main__":
    main()
