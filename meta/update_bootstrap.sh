#!/bin/bash

set -euo pipefail

: "${CURRENT_JAKT_COMPILER:=build/bin/jakt_stage1}"
: "${SELFHOST_BUILD_DIR:=selfhost_build}"
: "${STAGE0_TARGET_TRIPLE:=unknown-unknown-unknown-unknown}"
: "${AUTO_COMMIT:=0}"

if [ ! -x "$CURRENT_JAKT_COMPILER" ]; then
    echo "error: compiler not found or not executable: $CURRENT_JAKT_COMPILER" >&2
    echo "hint: build it first with: CCACHE_DISABLE=1 ninja -C build jakt_stage1" >&2
    exit 1
fi

rm -rf "$SELFHOST_BUILD_DIR"
mkdir -p "$SELFHOST_BUILD_DIR"

"$CURRENT_JAKT_COMPILER" \
    --binary-dir "$SELFHOST_BUILD_DIR" \
    -S \
    -T "$STAGE0_TARGET_TRIPLE" \
    --runtime-path runtime \
    -I selfhost \
    -I runtime \
    selfhost/main.jakt

rm -rf bootstrap/temp
mkdir -p bootstrap/temp

cp bootstrap/stage0/README.md bootstrap/temp/
cp -rL runtime bootstrap/temp/
cp "$SELFHOST_BUILD_DIR"/*.cpp bootstrap/temp/
cp "$SELFHOST_BUILD_DIR"/*.h bootstrap/temp/

rm -rf bootstrap/stage0
mv bootstrap/temp bootstrap/stage0

if [ "$AUTO_COMMIT" = "1" ]; then
    git add bootstrap
    git commit -m 'bootstrap: Update stage0 snapshot'
fi
