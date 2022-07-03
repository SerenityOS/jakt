#!/bin/bash


is_binary_behind_src() {
    local binary_path=$1
    local src_dir=$2
    # if the target file does not exist, then
    # we'll say yes
    if [ ! -x "$binary_path" ]; then
        return 0
    else
        local binary_mtime=$(stat -c %Y "$binary_path")
        local latest_source_mtime=$(\
            stat -c %Y $src_dir/*.jakt |\
            sort |\
            tail -n1)
        [ "$binary_mtime" -lt "$latest_source_mtime" ]
    fi
}

if is_binary_behind_src build/jakttest jakttest; then
    echo "(re)compiling jakttest to match source"
    cargo run jakttest/jakttest.jakt
fi

# check for selfhost/ mtime and build/main mtime
if is_binary_behind_src build/main selfhost; then
    echo "(re)compiling selfhost to match source"
    cargo run selfhost/main.jakt
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
    $(./build/jakttest $f >/dev/null 2>/dev/null) >/dev/null 2>/dev/null
    
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
