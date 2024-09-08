# ch3/part-5

Showing adding an additional third-party dependency with `FetchContent`.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch3/part-5`

```bash
cd ch3/part-5
code .

# or

code ch3/part-5
```

## Commands

```bash
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life
```
