#!/bin/bash

if [ ! -x ./build/jakttest ]; then
    echo "jakttest binary does not exist."
    echo 'You can build it with `cargo run jakttest/jakttest.jakt`'
    exit 1
fi

pass=0
fail=0

count=0

for f in samples/**/*.jakt tests/**/*.jakt; do
    count=$(expr $count + 1)
done

i=0

set +m

for f in samples/**/*.jakt tests/**/*.jakt; do
    i=$(expr $i + 1)
    $(./build/jakttest $f >/dev/null 2>/dev/null) >/dev/null 2>/dev/null && result=pass || result=fail 

    echo -n "($i/$count: $pass+$fail) "

    if [ "x$result" == "xpass" ]; then
        pass=$(expr $pass + 1)
        echo -ne "[ \033[32;1mPASS\033[0m ] "
    else
        fail=$(expr $fail + 1)
        echo -ne "[ \033[31;1mFAIL\033[0m ] "
    fi
    echo "$f"

done

echo ==============================
echo $pass passed
echo $fail failed
echo ==============================
