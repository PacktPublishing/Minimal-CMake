# ch3/part-4 README

Showing an example of an embedded third-party project added with git.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch3/part-4`

```bash
cd ch3/part-4
code .

# or

code ch3/part-4
```

## Commands

```bash
# manually setup dependencies
cd third-party
git clone https://github.com/pr0g/timer_lib.git
cd ..
# configure
cmake -B build -G "Ninja Multi-Config"
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life
```
