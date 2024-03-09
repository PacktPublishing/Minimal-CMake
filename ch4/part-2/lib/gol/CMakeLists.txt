cmake_minimum_required(VERSION 3.28)
project(mc-gol LANGUAGES C)
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/gol.c)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)

include(FetchContent)
FetchContent_Declare(
  as-c-math
  GIT_REPOSITORY https://github.com/pr0g/as-c-math.git
  GIT_TAG 05094067885567480271c14c64f3324e000c9c04)
set(AS_MATH_ENABLE_TEST
    OFF
    CACHE INTERNAL "")
set(AS_MATH_ENABLE_COVERAGE
    OFF
    CACHE INTERNAL "")
FetchContent_Declare(
  minimal-cmake-array
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG 6a47f60260b8d0809d15e8a38843daf1a94bd2f2
  SOURCE_SUBDIR ch4/part-2/lib/array) # look just in array folder

FetchContent_MakeAvailable(as-c-math minimal-cmake-array)

target_link_libraries(${PROJECT_NAME} PRIVATE as-c-math mc-array)
