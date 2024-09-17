# ch5/part-4

Adding build and workflow presets to `CMakePresets.json`.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch5/part-4/app`

```bash
cd ch5/part-4/app
code .

# or

code ch5/part-4/app
```

## Commands

```bash
# start
cd ch5/part-4
# configure and build
cd app
cmake --preset static
cmake --build --preset static
cmake --workflow --preset shared
# run
./build/static/Debug/minimal-cmake_game-of-life_console
./build/shared/Debug/minimal-cmake_game-of-life_console
```
