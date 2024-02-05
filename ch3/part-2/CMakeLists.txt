cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life LANGUAGES C)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c array/array.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

# demonstrate how to add the current path to the module path
# LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(CMakeHelpers.cmake)

include(FetchContent)
FetchContent_Declare(
  timer_lib
  GIT_REPOSITORY https://github.com/pr0g/timer_lib.git
  GIT_TAG main)
FetchContent_MakeAvailable(timer_lib)

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib)

message(STATUS "list_cmake_variables")
list_cmake_variables()
