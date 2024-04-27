@echo off

cmake -S sdl -B build-sdl -G "Ninja Multi-Config" -DCMAKE_INSTALL_PREFIX=install
