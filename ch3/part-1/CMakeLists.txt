cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life LANGUAGES C)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c array/array.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

include(FetchContent)
FetchContent_Declare(
  timer_lib
  GIT_REPOSITORY https://github.com/pr0g/timer_lib.git
  GIT_TAG v1.0)
FetchContent_MakeAvailable(timer_lib)

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib)
