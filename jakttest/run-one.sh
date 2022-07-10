#!/bin/sh
# run-one.sh <temp-dir> <file>

# NOTE: we need this because selfhost doesn't yet have a way to specify
# build directories, and it doesn't use temporary directories for
# temporary building (i.e building and running)

set -e

temp_dir=$1
file=$2

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

# Run
$temp_dir/output
