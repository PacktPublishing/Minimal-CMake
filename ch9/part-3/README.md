# ch9/part-3

Show an example of testing an application using Dear ImGui and CTest.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch9/part-3/app`

```bash
cd ch9/part-3/app
code .

# or

code ch9/part-3/app
```

## Commands

```bash
# start
cd ch9/part-3
# configure and build
cd app
cmake --preset multi-ninja-super-test
cmake --build build/multi-ninja-super-test --config Debug
cmake --preset multi-ninja-test-interactive
cmake --build build/multi-ninja-test-interactive --config Debug
# test
ctest --test-dir build/multi-ninja-super-test -C Debug
# test (interactive)
./build/multi-ninja-test-interactive/Debug/minimal-cmake_game-of-life_window-test
# run (build folder)
./build/multi-ninja-super-test/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
