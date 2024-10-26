# ch5/part-3

Expands our `CMakePresets.json` file.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch5/part-3/app`

```bash
cd ch5/part-3/app
code .

# or

code ch5/part-3/app
```

## Commands

```bash
# start
cd ch5/part-3
# configure and build
cd app
cmake --preset static
cmake --build build/static
cmake --preset shared
cmake --build build/shared
# run
./build/static/Debug/minimal-cmake_game-of-life_console
./build/shared/Debug/minimal-cmake_game-of-life_console
```
