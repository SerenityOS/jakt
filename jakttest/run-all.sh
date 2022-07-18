#!/bin/bash
#
# Copyright (c) 2022, Jesús Lapastora <cyber.gsuscode@gmail.com>
#
# SPDX-License-Identifier: BSD-2-Clause

echo "Checking & building Jakttest if necessary"
set -e
ninja -C jakttest
set +e

exec ./jakttest/build/jakttest
