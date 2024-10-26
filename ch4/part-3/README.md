# ch4/part-3

Converts Game of Life to shared library.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch4/part-3/app`

```bash
cd ch4/part-3/app
code .

# or

code ch4/part-3/app
```

## Commands

```bash
# start
cd ch4/part-3/app
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life_console
```
