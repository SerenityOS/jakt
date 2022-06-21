#!/bin/bash

if [ ! -x ./build/jakttest ]; then
    echo "jakttest binary does not exist."
    echo 'You can build it with `cargo run jakttest/jakttest.jakt`'
    exit 1
fi

if [ ! -x ./build/main ]; then
    echo "selfhosted jakt binary does not exist."
    echo 'You can build it with `cargo run selfhost/main.jakt`'
    exit 1
fi

pass=0
fail=0
skipped=0

count=0

for f in samples/**/*.jakt tests/**/*.jakt; do
    count=$(expr $count + 1)
done

i=0

set +m

for f in samples/**/*.jakt tests/**/*.jakt; do
    i=$(expr $i + 1)
    $(./build/jakttest $f >/dev/null 2>/dev/null) >/dev/null 2>/dev/null
    
    exitcode=$?

    echo -n "($i/$count: $pass+$fail+$skipped) "

    if [ $exitcode == 0 ]; then
        pass=$(expr $pass + 1)
        echo -ne "[ \033[32;1mPASS\033[0m ] "
    elif [ $exitcode == 2 ]; then
        skipped=$(expr $skipped + 1)
        echo -ne "[ \033[33;1mSKIPPED\033[0m ] "
    else
        fail=$(expr $fail + 1)
        echo -ne "[ \033[31;1mFAIL\033[0m ] "
    fi
    echo "$f"

done

echo ==============================
echo $pass passed
echo $fail failed
echo $skipped skipped
echo ==============================
