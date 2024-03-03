cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life LANGUAGES C)
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
  GIT_TAG 616fe946956561ef4884fc32c4eec2432fd952c8)
set(AS_MATH_ENABLE_TEST
    OFF
    CACHE INTERNAL "")
set(AS_MATH_ENABLE_COVERAGE
    OFF
    CACHE INTERNAL "")
FetchContent_Declare(
  minimal-cmake-array
  # SOURCE_DIR ../../lib/array) # temp
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG e9f596c6d62ab3919a187be3bbfd14d52303ba5c
  SOURCE_SUBDIR ch4/part-1/lib/array) # look just in array folder

FetchContent_MakeAvailable(timer_lib as-c-math minimal-cmake-array)

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib as-c-math array)
