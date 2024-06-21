@echo off

cmake -B build -G "Ninja Multi-Config" -DCMAKE_PREFIX_PATH=../third-party/install
