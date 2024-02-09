cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life LANGUAGES C)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c array/array.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

# No FetchContent - add dependency through add_subdirectory

add_subdirectory(third-party)

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib)
