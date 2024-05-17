@echo off

CALL configure-default.bat
cmake --build build --config Debug 
cmake --build build --config RelWithDebInfo
