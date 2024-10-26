# ch10/part-1

Shows an example of loading resources relative to the executable.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch10/part-1/app`

```bash
cd ch10/part-1/app
code .

# or

code ch10/part-1/app
```

## Commands

```bash
# start
cd ch10/part-1
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# move to repository root (to test loading relative to executable)
cd ../../..
# run (build folder)
./ch10/part-1/app/build/multi-ninja-super/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./ch10/part-1/app/install/bin/minimal-cmake_game-of-life_window
# also try launching from GUI (Windows Desktop, macOS Finder, Ubuntu Desktop)
```
