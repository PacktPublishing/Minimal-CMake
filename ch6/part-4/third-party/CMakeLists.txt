cmake_minimum_required(VERSION 3.28)

project(third-party)

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

ExternalProject_Add(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.2
  GIT_SHALLOW TRUE
  BINARY_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/SDL2-prefix/src/SDL2-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>)

# compile bgfx and tools (bgfxt -> bgfx tools)
# bgfx must be compiled statically for use when building the
# tools (shaderc, geometryv etc...)
ExternalProject_Add(
  bgfxt
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG v1.127.8710-464
  GIT_SHALLOW TRUE
  BINARY_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/bgfxt-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)

# compile bgfx dynamically for use by our application
ExternalProject_Add(
  bgfx
  GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
  GIT_TAG v1.127.8710-464
  GIT_SHALLOW TRUE
  DEPENDS bgfxt
  BINARY_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/bgfx-build/${build_type_dir}
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install
  CMAKE_ARGS ${build_type_arg} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
             -DBGFX_LIBRARY_TYPE=SHARED -DBGFX_BUILD_TOOLS=OFF
             -DBGFX_BUILD_EXAMPLES=OFF
  CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=d)
