# ch8/part-2

Show an example of setting-up a super build.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch8/part-2/app`

```bash
cd ch8/part-2/app
code .

# or

code ch8/part-2/app
```

## Commands

```bash
# start
cd ch8/part-2
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# compile shaders
./compile-shader-<platform>.sh # e.g. compile-shader-linux.sh
# run
./build/multi-ninja/Debug/minimal-cmake_game-of-life_window
```
