#!/bin/sh

includepath="/usr/include/"
runtime="./runtime/*"
exe="./target/debug/jakt"
path="/usr/bin/"
cargo build &&
sudo cp $exe $path &&
sudo cp -r $runtime $includepath

