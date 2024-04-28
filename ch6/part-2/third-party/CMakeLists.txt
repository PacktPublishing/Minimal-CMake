cmake_minimum_required(VERSION 3.28)

project(third-party)

include(ExternalProject)

ExternalProject_Add(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.2
  GIT_SHALLOW TRUE
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)
