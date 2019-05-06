#!/bin/bash

mkdir compile_files
cd compile_files
cmake .. -DBUILD_TESTS=ON
@$(MAKE) DEBUG=TRUE
bash tests

