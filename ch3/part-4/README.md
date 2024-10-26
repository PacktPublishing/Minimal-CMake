# ch3/part-4 README

Shows an example of an embedded third-party project added with Git.

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
# start
cd ch3/part-4
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
