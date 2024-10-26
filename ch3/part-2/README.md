# ch3/part-2

Adds a simple CMake diagnostic utility to print CMake variables.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch3/part-2`

```bash
cd ch3/part-2
code .

# or

code ch3/part-2
```

## Commands

```bash
# start
cd ch3/part-2
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life
```
