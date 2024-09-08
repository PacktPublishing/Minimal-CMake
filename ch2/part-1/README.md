# ch2/part-1

_"Hello, ~~world~~ CMake!"_ application.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch2/part-1`.

```bash
cd ch2/part-1
code .

# or

code ch2/part-1
```

## Commands

```bash
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake
```
