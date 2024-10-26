# ch9/part-4

Shows an example of combining different kinds of tests with CTest.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch9/part-4/app`

```bash
cd ch9/part-4/app
code .

# or

code ch9/part-4/app
```

## Commands

```bash
# start
cd ch9/part-4
# configure and build
cd app
cmake --preset multi-ninja-super-test
cmake --build build/multi-ninja-super-test --config Debug
# test
ctest --test-dir build/multi-ninja-super-test -C Debug
# run (build folder)
./build/multi-ninja-super-test/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
