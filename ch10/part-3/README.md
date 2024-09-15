# ch10/part-3

Show an example of using MACOSX_BUNDLE and CPack.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch10/part-3/app`

```bash
cd ch10/part-3/app
code .

# or

code ch10/part-3/app
```

## Commands

```bash
# start
cd ch10/part-3
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Release
# package
# windows
cpack --config build/multi-ninja-super/CPackConfig.cmake -G NSIS64 -B package
# macos
cpack --config build/multi-ninja-super/CPackConfig.cmake -B package -G DragNDrop
# linux
cpack --config build/multi-ninja-super/CPackConfig.cmake -G DEB -B package
```
