#!/bin/bash

cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Release
cpack --config build/multi-ninja-super/CPackConfig.cmake -G DEB -B package
# sudo dpkg -i package/mc-game-of-life-0.1.1-Linux.deb # install package
