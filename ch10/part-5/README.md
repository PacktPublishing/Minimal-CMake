# ch10/part-5

Show an example of CPack source packages.

## Visual Studio Code Debugging

Open Visual Studio Code from `ch10/part-5/app`

```bash
cd ch10/part-5/app
code .

# or

code ch10/part-5/app
```

## Commands

```bash
# start
cd ch10/part-5
# configure and build
cd app
cmake --preset multi-ninja-super
cmake --build build/multi-ninja-super --config Release
# package source
cpack --config build/multi-ninja-super/CPackSourceConfig.cmake -G TGZ -B package-source
# package source (using preset)
cpack --preset source
```
