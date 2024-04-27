#!/bin/bash

# check if we haven't already created the sdl directory
if [ ! -d sdl ]; then
  git clone https://github.com/libsdl-org/SDL.git --branch release-2.30.2 --depth 1 sdl
fi
