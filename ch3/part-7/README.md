# ch3/part-7

Updating example to us x/y coordinates and `as-c-math` instead of rows/cols.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch3/part-7`

```bash
cd ch3/part-7
code .

# or

code ch3/part-7
```

## Commands

```bash
# start
cd ch3/part-7
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life
```
