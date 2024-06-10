# ch7/part-1

Add install support to mc-array.

## Build commands

```bash
# to be run from ch7/part-1

cd lib/array
cmake -B build -G "Ninja Multi-Config" -DCMAKE_INSTALL_PREFIX=install
cmake --build build --config Release --target install
cd ../../third-party
cmake -B build -G "Ninja Multi-Config"
cmake --build build --config Release
cd ../app
cmake --preset shared-ninja
cmake --build build/shared-ninja --config Release
./compile-shader-<platform>.sh
./build/shared-ninja/Release/minimal-cmake_game-of-life_window
```
