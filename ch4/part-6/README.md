# ch4/part-6

Adds interface (header-only) library.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch4/part-6/app`

```bash
cd ch4/part-6/app
code .

# or

code ch4/part-6/app
```

## Commands

```bash
# start
cd ch4/part-6/app
# configure
cmake -B build -G "Ninja Multi-Config" -DMC_GOL_SHARED=ON
# build
cmake --build build
# run
./build/Debug/minimal-cmake_game-of-life_console
```
