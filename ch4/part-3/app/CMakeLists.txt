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
FetchContent_MakeAvailable(timer_lib)

FetchContent_Declare(
  minimal-cmake-gol
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG 3eafd75e33ad0fd424e613ec4d5adb3cf3a6c2bf
  SOURCE_SUBDIR ch4/part-3/lib/gol) # look just in gol folder

set(BUILD_SHARED_LIBS_BEFORE ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS ON)
FetchContent_MakeAvailable(minimal-cmake-gol)
set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_BEFORE})

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib mc-gol)
