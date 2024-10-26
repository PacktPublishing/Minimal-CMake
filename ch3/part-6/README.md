# ch3/part-6

Shows an example of setting properties on a third-party dependency, added with `FetchContent`.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch3/part-6`

```bash
cd ch3/part-6
code .

# or

code ch3/part-6
```

## Commands

```bash
# start
cd ch3/part-6
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life
```
