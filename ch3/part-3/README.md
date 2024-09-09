# ch3/part-3

Showing an example of an embedded third-party project.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch3/part-3`

```bash
cd ch3/part-3
code .

# or

code ch3/part-3
```

## Commands

```bash
# start
cd ch3/part-3
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life
```
