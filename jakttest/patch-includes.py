#!/bin/env python
#
# Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
#
# SPDX-License-Identifier: BSD-2-Clause

# Add `#include "../process.h"` to the output file (.. because file is under build/)
import sys

target_file = sys.argv[1]
target_output = sys.argv[2]

with open(target_file) as source, open(target_output, "w") as sink:
    sink.write('#include "../process.h"\n')
    sink.write('#include "../fs.h"\n')
    sink.write('#include "../os.h"\n')
    sink.write(source.read())
