# ch10/part-2

Shows an example of integrating CPack.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch10/part-2/app`

```bash
cd ch10/part-2/app
code .

# or

code ch10/part-2/app
```

## Commands

```bash
# start
cd ch10/part-2
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Release
# package
# windows
cpack --config build/multi-ninja-super/CPackConfig.cmake -G NSIS64 -B package
# macos
cpack --config build/multi-ninja-super/CPackConfig.cmake -B package -G Bundle
# linux
cpack --config build/multi-ninja-super/CPackConfig.cmake -G DEB -B package
```
