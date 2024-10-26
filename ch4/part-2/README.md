# ch4/part-2

Game of Life extracted to static library.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch4/part-2/app`

```bash
cd ch4/part-2/app
code .

# or

code ch4/part-2/app
```

## Commands

```bash
# start
cd ch4/part-2/app
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life_console
```
