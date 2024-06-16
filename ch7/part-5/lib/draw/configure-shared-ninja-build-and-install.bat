@echo off

CALL configure-shared-ninja.bat
cmake --build build/shared-ninja --config Release --target install
