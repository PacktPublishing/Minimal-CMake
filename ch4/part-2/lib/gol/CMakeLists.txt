cmake_minimum_required(VERSION 3.28)
project(mc-gol LANGUAGES C)
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/gol.c)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

include(FetchContent)
FetchContent_Declare(
  as-c-math
  GIT_REPOSITORY https://github.com/pr0g/as-c-math.git
  GIT_TAG 1795a41abece464f70a19ee8dc271e586d5cfddc)
set(AS_MATH_ENABLE_TEST
    OFF
    CACHE INTERNAL "")
set(AS_MATH_ENABLE_COVERAGE
    OFF
    CACHE INTERNAL "")
FetchContent_Declare(
  minimal-cmake-array
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG 00049e6ccf0acaaa320f3a6eae2b5eb694d6be09
  SOURCE_SUBDIR ch4/part-2/lib/array) # only look in array folder

FetchContent_MakeAvailable(as-c-math minimal-cmake-array)

target_link_libraries(${PROJECT_NAME} PRIVATE as-c-math mc-array)
