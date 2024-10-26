# ch11/part-4

Show an example of GitHub Actions.

(_Note: See root `.github/workflows/cmake.yml` that uses this folder_).

## Visual Studio Code Debugging

Open Visual Studio Code from `ch11/part-4/app`

```bash
cd ch11/part-4/app
code .

# or

code ch11/part-4/app
```

## Commands

```bash
# start
cd ch11/part-4
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# run (build folder)
./build/multi-ninja-super/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
