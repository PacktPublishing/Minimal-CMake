# ch6/part-1

Manually installs SDL2 and uses it from the updated windowed application.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch6/part-1/app`

```bash
cd ch6/part-1/app
code .

# or

code ch6/part-1/app
```

## Commands

```bash
# start
cd ch6/part-1
# setup third-party
cd third-party
./everything.sh # (or everything.bat)
# configure and build
cd ../app
./configure-default-and-build.sh # (or configure-default-and-build.bat)
# run
./build/Debug/minimal-cmake_game-of-life_window
```
