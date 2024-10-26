# ch6/part-2

Using `ExternalProject_Add` to download and install SDL2 for use in our updated windowed application.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch6/part-2/app`

```bash
cd ch6/part-2/app
code .

# or

code ch6/part-2/app
```

## Commands

```bash
# start
cd ch6/part-2
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
