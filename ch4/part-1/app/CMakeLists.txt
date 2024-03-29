cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life_console LANGUAGES C)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

include(FetchContent)
FetchContent_Declare(
  timer_lib
  GIT_REPOSITORY https://github.com/pr0g/timer_lib.git
  GIT_TAG v1.0)
FetchContent_Declare(
  as-c-math
  GIT_REPOSITORY https://github.com/pr0g/as-c-math.git
  GIT_TAG 108b653154b7e55832d4dc1386feb91b3db88880)
set(AS_MATH_ENABLE_TEST
    OFF
    CACHE INTERNAL "")
set(AS_MATH_ENABLE_COVERAGE
    OFF
    CACHE INTERNAL "")
FetchContent_Declare(
  minimal-cmake-array
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG d4b3fef8d2be74c1b6f8eebdf68b3c7bdc9a6668
  SOURCE_SUBDIR ch4/part-1/lib/array) # only look in array folder

FetchContent_MakeAvailable(timer_lib as-c-math minimal-cmake-array)

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib as-c-math mc-array)
