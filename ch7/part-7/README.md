# ch7/part-7

Shows an example of a `FindModule` file.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch7/part-7/app`

```bash
cd ch7/part-7/app
code .

# or

code ch7/part-7/app
```

## Commands

```bash
# start
cd ch7/part-7
# setup third-party
cd third-party
cmake -B build -G "Ninja Multi-Config"
cmake --build build --config Debug
# build and install libraries
cd ../lib/array
cmake --preset default
cmake --build build --config Debug --target install
cd ../gol
cmake --preset shared-ninja
cmake --build build/shared-ninja --config Debug --target install
cd ../draw
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
