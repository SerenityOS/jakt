#!/bin/bash

set -e

: "${CURRENT_JAKT_COMPILER:=Build/bin/jakt}"
: "${JAKT_RUNTIME_DIR:=Build/lib}"
: "${COMPILE_JOBS:=$(nproc)}"

# First, get a working build of the compiler
"$CURRENT_JAKT_COMPILER" -J"$COMPILE_JOBS" --runtime-library-path "$JAKT_RUNTIME_DIR" selfhost/main.jakt

# Next, use that to build the selfhost
rm -fr selfhost_build
mkdir selfhost_build
build/main --binary-dir selfhost_build -S -T unknown-unknown-unknown-unknown --runtime-library-path "$JAKT_RUNTIME_DIR" --runtime-path runtime selfhost/main.jakt

# Now copy all the things
rm -fr bootstrap/temp
mkdir -p bootstrap/temp

cp bootstrap/stage0/README.md bootstrap/temp/
cp -rL runtime bootstrap/temp/
cp selfhost_build/*.cpp bootstrap/temp
cp selfhost_build/*.h bootstrap/temp

# Great, now replace the old one with the new one
rm -fr bootstrap/stage0
mv bootstrap/temp bootstrap/stage0

# Committee committee
git add bootstrap
git commit -m 'bootstrap: Update stage0 snapshot'
