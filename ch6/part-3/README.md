# ch6/part-3

Updating our use of ExternalProject_Add to handle different config types with single and multi-config generators.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch6/part-3/app`

```bash
cd ch6/part-3/app
code .

# or

code ch6/part-3/app
```

## Commands

```bash
# start
cd ch6/part-3
# setup third-party
cd third-party
cmake -B build -G "Ninja Multi-Config"
cmake --build build --config Debug
# configure and build
cd ../app
cmake --preset shared-ninja
cmake --build build/shared-ninja --config Debug
# run
./build/shared-ninja/Debug/minimal-cmake_game-of-life_window
```
