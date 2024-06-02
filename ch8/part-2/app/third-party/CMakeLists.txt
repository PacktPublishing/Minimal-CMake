cmake_minimum_required(VERSION 3.28)

if(NOT SUPERBUILD)
  project(third-party)
endif()

include(ExternalProject)

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

if(SUPERBUILD)
  set(PREFIX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
else()
  set(PREFIX_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif()

ExternalProject_Add(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.2
  GIT_SHALLOW TRUE
  PREFIX ${PREFIX_DIR}
  BINARY_DIR ${PREFIX_DIR}/SDL2-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)

# compile bgfx and tools (bgfxt -> bgfx tools) bgfx must be compiled statically
# for use when building the tools (shaderc, geometryv etc...)
ExternalProject_Add(
  bgfxt
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG v1.127.8710-464
  GIT_SHALLOW TRUE
  PREFIX ${PREFIX_DIR}
  # reduce path length of binary_dir to avoid max path length on windows
  BINARY_DIR ${PREFIX_DIR}/bgfxt-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

# compile bgfx dynamically for use by our application
ExternalProject_Add(
  bgfx
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG v1.127.8710-464
  GIT_SHALLOW TRUE
  DEPENDS bgfxt # ensure bgfx builds and installs after bgfxt
  PREFIX ${PREFIX_DIR}
  # reduce path length of binary_dir to avoid max path length on windows
  BINARY_DIR ${PREFIX_DIR}/bgfx-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DBGFX_LIBRARY_TYPE=SHARED -DBGFX_BUILD_TOOLS=OFF
             -DBGFX_BUILD_EXAMPLES=OFF
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

ExternalProject_Add(
  mc-array
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG 18535c9d140e828895c57dbb39b97a3307f846ab
  SOURCE_SUBDIR ch8/part-1/lib/array
  PREFIX ${PREFIX_DIR}
  BINARY_DIR ${PREFIX_DIR}/mc-array-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

ExternalProject_Add(
  mc-draw
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG 18535c9d140e828895c57dbb39b97a3307f846ab
  DEPENDS mc-array bgfx
  PREFIX ${PREFIX_DIR}
  SOURCE_SUBDIR ch8/part-1/lib/draw
  BINARY_DIR ${PREFIX_DIR}/mc-draw-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

ExternalProject_Add(
  mc-gol
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG 18535c9d140e828895c57dbb39b97a3307f846ab
  DEPENDS mc-array
  PREFIX ${PREFIX_DIR}
  SOURCE_SUBDIR ch8/part-1/lib/gol
  BINARY_DIR ${PREFIX_DIR}/mc-gol-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)
