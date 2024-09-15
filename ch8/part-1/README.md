# ch8/part-1

Show how to simplify configuration with `ExternalProject_Add`. _Note: continues from_ `ch7/part-6`.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch8/part-1/app`

```bash
cd ch8/part-1/app
code .

# or

code ch8/part-1/app
```

## Commands

```bash
# start
cd ch8/part-1
# setup third-party
cd third-party
cmake -B build -G "Ninja Multi-Config"
cmake --build build --config Debug
# configure and build
cd ../../app
cmake --preset multi-ninja
cmake --build build/multi-ninja --config Debug
# compile shaders
./compile-shader-<platform>.sh # e.g. compile-shader-linux.sh
# run
./build/multi-ninja/Debug/minimal-cmake_game-of-life_window
```
