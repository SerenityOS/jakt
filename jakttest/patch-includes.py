#!/bin/env python
# ./patch.sh $in $out
# Add `#include "../process.h"` to the output file (.. because file is under build/)
import sys

target_file = sys.argv[1]
target_output = sys.argv[2]

with open(target_file) as source, open(target_output, "w") as sink:
    sink.write('#include "../process.h"\n')
    sink.write('#include "../fs.h"\n')
    sink.write(source.read())
