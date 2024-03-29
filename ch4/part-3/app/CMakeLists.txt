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
  minimal-cmake-gol
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG d4b3fef8d2be74c1b6f8eebdf68b3c7bdc9a6668
  SOURCE_SUBDIR ch4/part-3/lib/gol) # only look in gol folder

FetchContent_MakeAvailable(timer_lib minimal-cmake-gol)

# option 1
# if(WIN32)
#   set_target_properties(mc-gol PROPERTIES RUNTIME_OUTPUT_DIRECTORY
#                                           "${CMAKE_CURRENT_BINARY_DIR}")
# endif()

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib mc-gol)

# option 2
if(WIN32)
  # copy mc-gol.dll to the same folder as the executable
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:mc-gol>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif()
