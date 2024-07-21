#!/bin/bash

cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Release
cmake --preset multi-ninja # workaround 'failed recompaction' error
cmake --build build/multi-ninja --config Release
cpack --config build/multi-ninja/CPackConfig.cmake -G NSIS64 -B package
