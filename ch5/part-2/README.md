# ch5/part-2

An introduction to `CMakePresets.json`.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch5/part-2/app`

```bash
cd ch5/part-2/app
code .

# or

code ch5/part-2/app
```

## Commands

```bash
# start
cd ch5/part-2
# configure and build
cd app
cmake --preset default
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life_console
```
