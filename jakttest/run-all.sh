#!/bin/bash

STAT_FORMAT_FLAGS="-c %Y"
if [[ $OSTYPE == 'darwin'* ]]; then
    STAT_FORMAT_FLAGS="-f %m"
fi

JAKTTEST_BUILD_DIR="./jakttest/build"
SELFHOST_BUILD_DIR="./selfhost/build"

JAKTTEST_EXECUTABLE="$JAKTTEST_BUILD_DIR/jakttest"
SELFHOST_EXECUTABLE="$SELFHOST_BUILD_DIR/main"

is_executable_behind_src() {
    local executable_path=$1
    local src_path=$2

    local executable_mtime=$(stat "$STAT_FORMAT_FLAGS" "$executable_path")
    local src_latest_mtime=$(stat $STAT_FORMAT_FLAGS "$src_path"/*.jakt | sort | tail -n1)
    [ "$executable_mtime" -lt "$src_latest_mtime" ]
}

compile_jakttest() {
    cargo run jakttest/jakttest.jakt -o "$JAKTTEST_BUILD_DIR"
}

compile_selfhost() {
    cargo run selfhost/main.jakt -o "$SELFHOST_BUILD_DIR"
}

# check for jakttest availability
if [ ! -x "$JAKTTEST_EXECUTABLE" ]; then
    echo "Jakttest binary does not exist. Compiling it now."
    compile_jakttest
elif is_executable_behind_src "$JAKTTEST_EXECUTABLE" jakttest; then
    echo "Updating jakttest binary to match source."
    compile_jakttest
fi

# check for selfhost availability
if [ ! -x "$SELFHOST_EXECUTABLE" ]; then
    echo "Selfhost binary does not exist. Compiling it now."
    compile_selfhost
elif is_executable_behind_src "$SELFHOST_EXECUTABLE" selfhost; then
    echo "Updating selfhost binary to match source."
    compile_selfhost
fi

pass=0
fail=0
skipped=0

count=0

if [ -n "$1" ]
then
    TEST_FILES=$(find "$1" -type f -name "*.jakt")
else
    TEST_FILES="samples/**/*.jakt tests/**/*.jakt"
fi

for f in $TEST_FILES; do
    count=$((count + 1))
done

i=0

set +m

for f in $TEST_FILES; do
    i=$((i + 1))
    $($JAKTTEST_EXECUTABLE \
        --selfhost-executable "$SELFHOST_EXECUTABLE" \
        $f >/dev/null 2>/dev/null) >/dev/null 2>/dev/null
    
    exitcode=$?

    if [ $exitcode == 0 ]; then
        pass=$((pass + 1))
        echo -ne "[ \033[32;1mPASS\033[0m ] "
    elif [ $exitcode == 2 ]; then
        skipped=$((skipped + 1))
        echo -ne "[ \033[33;1mSKIP\033[0m ] "
    else
        fail=$((fail + 1))
        echo -ne "[ \033[31;1mFAIL\033[0m ] "
    fi
    echo "$f"

done

rm runtest.err runtest.out

echo ==============================
echo "$pass" passed
echo "$fail" failed
echo "$skipped" skipped
echo ==============================
