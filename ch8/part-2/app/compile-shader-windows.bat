@echo off

REM compile shaders

if not exist shader\build mkdir shader\build

REM simple shader
third-party\install\bin\shaderc.exe ^
-f shader\vs_vertcol.sc -o shader\build\vs_vertcol.bin ^
--platform windows --type vertex --verbose -i ./ -p s_5_0

third-party\install\bin\shaderc.exe ^
-f shader\fs_vertcol.sc -o shader\build\fs_vertcol.bin ^
--platform windows --type fragment --verbose -i ./ -p s_5_0
