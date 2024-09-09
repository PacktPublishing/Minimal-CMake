# ch6/part-4

Add another dependency (bgfx) using ExternalProject_Add.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch6/part-4/app`

```bash
cd ch6/part-4/app
code .

# or

code ch6/part-4/app
```

## Commands

```bash
# start
cd ch6/part-4
# setup third-party
cd third-party
cmake -B build -G "Ninja Multi-Config"
cmake --build build --config Debug
# configure and build
cd ../app
cmake --preset shared-ninja
cmake --build build/shared-ninja --config Debug
# compile shaders
./compile-shader-<platform>.sh # e.g. compile-shader-linux.sh
# run
./build/shared-ninja/Debug/minimal-cmake_game-of-life_window
```
