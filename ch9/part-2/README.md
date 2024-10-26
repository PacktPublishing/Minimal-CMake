# ch9/part-2

Shows an example of integrating Dear ImGui.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch9/part-2/app`

```bash
cd ch9/part-2/app
code .

# or

code ch9/part-2/app
```

## Commands

```bash
# start
cd ch9/part-2
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# run (build folder)
./build/multi-ninja/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
