# ch9/part-1

Shows an example of a library tests using CTest.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch9/part-1/app`

```bash
cd ch9/part-1/app
code .

# or

code ch9/part-1/app
```

## Commands

```bash
# start
cd ch9/part-1
# test libraries
cd lib/array
cmake --preset test
cmake --build build/test
ctest --test-dir build/test -C Debug
cmake --preset default
cmake --build build/default --target install
cd ../gol
cmake --preset shared-ninja-test
cmake --build build/shared-ninja-test
ctest --test-dir build/shared-ninja-test -C Debug
# configure and build
cd ../../app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Debug
# run (build folder)
./build/multi-ninja/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
