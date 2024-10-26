# ch11/part-1

Shows an example of a Visual Studio Code CMake Tools compatible setup.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch11/part-1/app`

```bash
cd ch11/part-1/app
code .

# or

code ch11/part-1/app
```

## Commands

```bash
# start
cd ch11/part-1
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# run (build folder)
./build/multi-ninja-super/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
