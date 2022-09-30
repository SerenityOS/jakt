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
MAIN_LIBRARY_NAME = "libjakt_main.a" if os.name != "nt" else "jakt_main.lib"
RUNTIME_LIBRARY_NAME = "libjakt_runtime.a" if os.name != "nt" else "jakt_runtime.lib"
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
        "--jakt-binary", help="The path to the jakt binary", default="build/bin/jakt"
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
    args = parser.parse_args()

    # Since we're running the output binary from a different
    # working directory, we need the full path of the binary.
    temp_dir = Path(args.temp_dir).resolve()
    test_file = Path(args.test_file).resolve()
    jakt_binary = Path(args.jakt_binary).resolve()
    jakt_lib_dir = Path(args.jakt_lib_dir).resolve()
    target_triple = args.target_triple

    # clear the temp directory
    for f in os.listdir(temp_dir):
        os.remove(temp_dir / f)

    # Generate C++ code, exit with status == 3 on failure
    with open(temp_dir / "compile_jakt.err", "w") as stderr:
        try:
            subprocess.run(
                [jakt_binary, test_file, "-B", temp_dir, "-S"],
                check=True,
                stderr=stderr,
                cwd=test_file.parent,
            )
        except subprocess.CalledProcessError as e:
            sys.exit(3)

    # Compile C++ code, exit with status == 2 on failure
    with open(temp_dir / "compile_cpp.err", "w") as stderr:
        try:
            subprocess.run(
                [
                    "clang++",
                    f"--target={target_triple}"
                    "-fdiagnostics-color=always",
                    "-std=c++20",
                    "-Wno-unknown-warning-option",
                    "-Wno-trigraphs",
                    "-Wno-parentheses-equality",
                    "-Wno-unqualified-std-cast-call",
                    "-Wno-user-defined-literals",
                    "-Wno-deprecated-declarations",
                    "-Iruntime",
                    "-DJAKT_CONTINUE_ON_PANIC",
                    "-o",
                    temp_dir / "output",
                    *WINDOWS_SPECIFIC_COMPILER_ARGUMENTS,
                    *list(temp_dir.glob("*.cpp")),
                    jakt_lib_dir / MAIN_LIBRARY_NAME,
                    jakt_lib_dir / RUNTIME_LIBRARY_NAME,
                ],
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
