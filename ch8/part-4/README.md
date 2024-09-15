# ch8/part-4

Show an example of passing settings to dependencies and scripts.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch8/part-4/app`

```bash
cd ch8/part-4/app
code .

# or

code ch8/part-4/app
```

## Commands

```bash
# start
cd ch8/part-4
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# run
./build/multi-ninja/Debug/minimal-cmake_game-of-life_window
```
