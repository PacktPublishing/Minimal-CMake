# ch7/part-3

Show how to deal with private nested dependencies when installing.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch7/part-2/app`

```bash
cd ch7/part-2/app
code .

# or

code ch7/part-2/app
```

## Commands

```bash
# start
cd ch7/part-3
# setup third-party
cd third-party
cmake -B build -G "Ninja Multi-Config"
cmake --build build --config Debug
# build and install libraries
cd ../lib/array
cmake -B build -G "Ninja Multi-Config" -DCMAKE_INSTALL_PREFIX=install
cmake --build build --config Debug --target install
cd ../gol
cmake --preset shared-ninja
cmake --build build/shared-ninja --config Debug --target install
# configure and build
cd ../../app
cmake --preset multi-ninja
cmake --build build/multi-ninja --config Debug
# compile shaders
./compile-shader-<platform>.sh # e.g. compile-shader-linux.sh
# run
./build/multi-ninja/Debug/minimal-cmake_game-of-life_window
```
