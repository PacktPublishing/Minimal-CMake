cmake_minimum_required(VERSION 3.28)

project(third-party)

include(ExternalProject)

# options to pass through to third-party libraries
option(MC_GOL_SHARED "Enable shared library for Game of Life" OFF)
option(MC_DRAW_SHARED "Enable shared library for Draw" OFF)

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT isMultiConfig)
  if(NOT CMAKE_BUILD_TYPE)
    # set Debug as default build type if one is not provided (match CMake
    # default behavior)
    set(CMAKE_BUILD_TYPE
        Debug
        CACHE STRING "" FORCE)
  endif()
  # give different build types their own folder with single config generators
  set(build_type_dir ${CMAKE_BUILD_TYPE})
  # pass through build type arg to ExternalProject_Add command
  set(build_type_arg -DCMAKE_BUILD_TYPE=$<CONFIG>)
endif()

if(SUPERBUILD AND NOT PROJECT_IS_TOP_LEVEL)
  set(PREFIX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
else()
  set(PREFIX_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif()

ExternalProject_Add(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.2
  GIT_SHALLOW TRUE
  PREFIX ${PREFIX_DIR}/SDL2
  BINARY_DIR ${PREFIX_DIR}/SDL2/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)

# compile bgfx and tools (bgfxt -> bgfx tools) bgfx must be compiled statically
# for use when building the tools (shaderc, geometryv etc...)
ExternalProject_Add(
  bgfxt
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG v1.127.8710-464
  GIT_SHALLOW TRUE
  PREFIX ${PREFIX_DIR}/bgfxt
  BINARY_DIR ${PREFIX_DIR}/bgfxt/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DBGFX_BUILD_EXAMPLES=OFF
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

ExternalProject_Get_Property(bgfxt SOURCE_DIR)
# compile bgfx dynamically for use by our application
ExternalProject_Add(
  bgfx
  URL "file://${SOURCE_DIR}"
  DEPENDS bgfxt
  PREFIX ${PREFIX_DIR}/bgfx
  BINARY_DIR ${PREFIX_DIR}/bgfx/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DBGFX_LIBRARY_TYPE=SHARED -DBGFX_BUILD_TOOLS=OFF
             -DBGFX_BUILD_EXAMPLES=OFF
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

ExternalProject_Add(
  imgui.cmake
  GIT_REPOSITORY https://github.com/pr0g/imgui.cmake.git
  GIT_TAG abf77e443a0d23b6d874dbbb42bbd02009562a9a
  PREFIX ${PREFIX_DIR}/imgui
  BINARY_DIR ${PREFIX_DIR}/imgui.cmake/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=ON
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

ExternalProject_Add(
  mc-array
  PREFIX ${PREFIX_DIR}/mc-array
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/array
  BINARY_DIR ${PREFIX_DIR}/mc-array/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

ExternalProject_Add(
  mc-draw
  DEPENDS mc-array bgfx
  PREFIX ${PREFIX_DIR}/mc-draw
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/draw
  BINARY_DIR ${PREFIX_DIR}/mc-draw/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DMC_DRAW_SHARED=${MC_DRAW_SHARED}
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

ExternalProject_Add(
  mc-gol
  DEPENDS mc-array
  PREFIX ${PREFIX_DIR}/mc-gol
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/gol
  BINARY_DIR ${PREFIX_DIR}/mc-gol/build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DMC_GOL_SHARED=${MC_GOL_SHARED}
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

if(SUPERBUILD AND NOT PROJECT_IS_TOP_LEVEL)
  ExternalProject_Add(
    ${CMAKE_PROJECT_NAME}_superbuild
    DEPENDS SDL2 bgfx imgui.cmake mc-gol mc-draw
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    BINARY_DIR ${CMAKE_BINARY_DIR}
    CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DSUPERBUILD=OFF
               ${build_type_arg})
endif()
