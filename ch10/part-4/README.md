# ch10/part-4

Shows an example of CMake presets packaging step.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch10/part-4/app`

```bash
cd ch10/part-4/app
code .

# or

code ch10/part-4/app
```

## Commands

```bash
# start
cd ch10/part-4
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Release
# package
# windows
cpack --preset windows
# macos
cpack --preset macos
# linux
cpack --preset linux
```
