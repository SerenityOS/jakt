#!/bin/sh

includepath="/usr/include/"
runtime="./runtime/*"
cargo install --path . &&
sudo cp -r $runtime $includepath

