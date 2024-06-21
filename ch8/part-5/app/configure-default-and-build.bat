@echo off

CALL configure-default.bat
cmake --build build --config RelWithDebInfo --target install
