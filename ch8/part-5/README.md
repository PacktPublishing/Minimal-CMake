# ch8/part-5

Shows an example of installing the application.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch8/part-5/app`

```bash
cd ch8/part-5/app
code .

# or

code ch8/part-5/app
```

## Commands

```bash
# start
cd ch8/part-5
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# run (build folder)
./build/multi-ninja/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
