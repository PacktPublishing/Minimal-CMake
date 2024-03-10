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
  minimal-cmake-gol
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG d7cefc72384a55f700653b0b473c4b4acbf1698a
  SOURCE_SUBDIR ch4/part-3/lib/gol) # look just in gol folder
FetchContent_MakeAvailable(timer_lib minimal-cmake-gol)

target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib mc-gol)
# set_target_properties(${PROJECT_NAME} PROPERTIES BUILD_RPATH "@loader_path")
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
    BUILD_RPATH
    $<IF:$<PLATFORM_ID:Linux>,$ORIGIN,$<IF:$<PLATFORM_ID:Darwin>,@loader_path,>>
)

if(WIN32)
  # copy mc-gol.dll to the same folder as the executable
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:mc-gol>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif()
