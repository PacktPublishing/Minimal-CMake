@echo off

cmake -B build -G "Ninja Multi-Config" -DMC_GOL_SHARED=ON -DCMAKE_PREFIX_PATH=../third-party/build/SDL2-prefix
