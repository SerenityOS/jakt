#!/bin/bash
# run-one.sh <temp-dir> <file>

# NOTE: we need this because selfhost doesn't yet have a way to specify
# build directories, and it doesn't use temporary directories for
# temporary building (i.e building and running)

set -e

# Since we're running the output binary from a different
# working directory, we need the full path of the binary.
temp_dir=$(realpath $1)
file=$2

file_cwd=$(dirname $file)

# Generate C++ code into 
build/main $2 > $temp_dir/output.cpp

# Compile C++ code
clang++ -fcolor-diagnostics \
    -std=c++20 \
    -Wno-unknown-warning-option \
    -Wno-trigraphs \
    -Wno-parentheses-equality \
    -Wno-unqualified-std-cast-call \
    -Wno-user-defined-literals \
    -Wno-deprecated-declarations \
    -Iruntime \
    -o $temp_dir/output \
    $temp_dir/output.cpp

pushd $file_cwd >/dev/null 2>/dev/null
# Run
$temp_dir/output
popd >/dev/null 2>/dev/null
