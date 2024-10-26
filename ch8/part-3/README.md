# ch8/part-3

Shows an example of building shaders using `add_custom_command`.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch8/part-3/app`

```bash
cd ch8/part-3/app
code .

# or

code ch8/part-3/app
```

## Commands

```bash
# start
cd ch8/part-3
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# run
./build/multi-ninja/Debug/minimal-cmake_game-of-life_window
```
