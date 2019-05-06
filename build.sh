#!/bin/bash

mkdir compile_files
cd compile_files
cmake .. -DBUILD_TESTS=ON
make DEBUG=TRUE
bash tests

