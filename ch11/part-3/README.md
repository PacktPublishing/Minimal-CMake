# ch11/part-3

Show an example of splitting-up parts of the main app/CMakeLists.txt file.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch11/part-3/app`

```bash
cd ch11/part-3/app
code .

# or

code ch11/part-3/app
```

## Commands

```bash
# start
cd ch11/part-3
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# run (build folder)
./build/multi-ninja-super/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
