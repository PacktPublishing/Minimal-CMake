#!/bin/bash

cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Release
cpack --config build/multi-ninja-super/CPackConfig.cmake -G Bundle -B package
