#!/bin/bash
#
# Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
#
# SPDX-License-Identifier: BSD-2-Clause

# run-one.sh <temp-dir> <file> <cpp_options>
# NOTE: we need this because selfhost doesn't yet have a way to specify
# build directories, and it doesn't use temporary directories for
# temporary building (i.e building and running)

set -e

# Since we're running the output binary from a different
# working directory, we need the full path of the binary.
temp_dir=$(realpath $1)
file=$2
cpp_options=$3

file_cwd=$(dirname $file)
arr=($(echo $cpp_options | tr " " "\n"))
cpp_options=${arr[@]/#/-I$file_cwd/}

# Generate C++ code into 
$(build/jakt $2 -B $temp_dir -o output -S 2>$temp_dir/compile_jakt.err) || exit 3

# Compile C++ code
clang++ -fdiagnostics-color=always -v \
    -std=c++20 \
    -Wno-unknown-warning-option \
    -Wno-trigraphs \
    -Wno-parentheses-equality \
    -Wno-unqualified-std-cast-call \
    -Wno-user-defined-literals \
    -Wno-deprecated-declarations \
    -Iruntime \
    ${cpp_options[@]} \
    -DJAKT_CONTINUE_ON_PANIC \
    -o $temp_dir/output \
    $temp_dir/output.cpp 2>$temp_dir/compile_cpp.err || exit 2

# Run the executable inside the parent directory of the test file
cd $file_cwd
$($temp_dir/output >$temp_dir/runtest.out 2>$temp_dir/runtest.err) || exit 1
