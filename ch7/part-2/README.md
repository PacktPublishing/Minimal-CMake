# ch7/part-2

Shows how to name the project and library differently in `mc-array`.

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
cd ch7/part-2
# setup third-party
cd third-party
cmake -B build -G "Ninja Multi-Config"
cmake --build build --config Debug
# build and install libraries
cd ../lib/array
cmake -B build -G "Ninja Multi-Config" -DCMAKE_INSTALL_PREFIX=install
cmake --build build --config Debug --target install
# configure and build
cd ../../app
cmake --preset shared-ninja
cmake --build build/shared-ninja --config Debug
# compile shaders
./compile-shader-<platform>.sh # e.g. compile-shader-linux.sh
# run
./build/shared-ninja/Debug/minimal-cmake_game-of-life_window
```
