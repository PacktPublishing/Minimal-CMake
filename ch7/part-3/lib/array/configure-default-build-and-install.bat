@echo off

CALL configure-default.bat
cmake --build build --config Release --target install
