# ch9/part-5

Show an example integrating CTest with CDash.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch9/part-5/app`

```bash
cd ch9/part-5/app
code .

# or

code ch9/part-5/app
```

## Commands

```bash
# start
cd ch9/part-5
# configure and build
cd app
cmake --preset multi-ninja-super-test
cmake --build build/multi-ninja-super-test --config Debug
# test and upload results to CDash
ctest --test-dir build/multi-ninja-super-test -C Debug -D Experimental
# run (build folder)
./build/multi-ninja-super-test/Debug/minimal-cmake_game-of-life_window
# run (install folder)
./install/bin/minimal-cmake_game-of-life_window
```
