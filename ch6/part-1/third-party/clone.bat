@echo off

REM check if we haven't already created the sdl directory
if not exist sdl (
  git clone https://github.com/libsdl-org/SDL.git --branch release-2.30.2 --depth 1 sdl
)
