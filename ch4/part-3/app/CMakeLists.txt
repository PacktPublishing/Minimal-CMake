cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life LANGUAGES C)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>") # works!

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
  SOURCE_DIR ../../lib/gol)

FetchContent_MakeAvailable(timer_lib minimal-cmake-gol)

set_target_properties(
  mc-gol PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>") # works!

# FetchContent_GetProperties(minimal-cmake-gol)
# if(NOT minimal-cmake-gol_POPULATED)
#   FetchContent_Populate(minimal-cmake-gol)
#   add_subdirectory(${minimal-cmake-gol_SOURCE_DIR} ${minimal-cmake-gol_BINARY_DIR})
#   set_target_properties(
#     mc-gol PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>") # works!
# endif()

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib mc-gol)

# if(WIN32)
#   # copy mc-gol.dll to the same folder as the executable
#   add_custom_command(
#     TARGET ${PROJECT_NAME}
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:mc-gol>
#             $<TARGET_FILE_DIR:${PROJECT_NAME}>
#     VERBATIM)
# endif()


