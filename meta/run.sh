#!/usr/bin/env bash

print_help() {
    NAME=$(basename "$0")
    cat <<EOF
Usage: $NAME [arguments...] [arguments to Jakt...]
Build and run a Jakt program!
Optional arguments:
    --build-compiler: Build the Jakt compiler before compiling the program (equivalent to running cargo build first).
    --help: Print this message.
EOF
}

if [ $# -eq 0 ]; then
    print_help
    exit 1
fi

BUILD_JAKT=0

for argument in "$@"
do
    if [ $argument = "--help" ]; then
        print_help
        exit
    fi
    if [ $argument = "--build-compiler" ]; then
        BUILD_JAKT=1
        shift
    fi
done

# Check to make sure clang is installed, since we need it to run the program.
if ! command -v clang++ &> /dev/null
then
    echo "clang++ was not found on your PATH, and it's required for building the output C++ program. Install it, then come back here :^)"
    exit 1
fi

# Assuming that jakt is in the normal place after it's built...
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

if [ $BUILD_JAKT = 1 ] || [ ! -f $SCRIPT_DIR/../target/debug/jakt ]; then
    cargo build
fi

$SCRIPT_DIR/../target/debug/jakt "$@"

JAKT_EXIT=$?
if [ $JAKT_EXIT != 0 ]; then
    echo "Compilation failed :^("
    exit $JAKT_EXIT
fi

# Use the last argument to Jakt to get output file name. If the user gave multiple files to Jakt to compile, 
# this means only the last one will be ran.
for i in $@; do :; done
cppfilename=$(basename -- "$i")
cppfilename="${cppfilename%.*}.cpp"

clang++ -std=c++20 -Iruntime -Wno-user-defined-literals ./build/$cppfilename
./a.out
