# ch5/part-5

Adds Windows (Visual Studio) and macOS (Xcode) configure presets to `CMakePresets.json` for use with CMake GUI.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch5/part-5/app`

```bash
cd ch5/part-5/app
code .

# or

code ch5/part-5/app
```

## Commands

```bash
# start
cd ch5/part-5
# configure, build, and run
cd app
cmake --preset list-presets
# windows
cmake --preset shared-visual-studio
cmake --build build/shared-visual-studio
./build/shared-visual-studio/Debug/minimal-cmake_game-of-life_console
# macOS
cmake --preset shared-xcode
cmake --build build/shared-xcode
./build/shared-xcode/Debug/minimal-cmake_game-of-life_console
```
