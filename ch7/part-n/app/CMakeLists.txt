cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life_window LANGUAGES C)

find_package(
  SDL2
  CONFIG
  REQUIRED
  NO_CMAKE_ENVIRONMENT_PATH
  NO_CMAKE_SYSTEM_PACKAGE_REGISTRY
  NO_SYSTEM_ENVIRONMENT_PATH
  NO_CMAKE_PACKAGE_REGISTRY
  NO_CMAKE_SYSTEM_PATH)
find_package(bgfx CONFIG REQUIRED)
find_package(mc-array CONFIG REQUIRED)
find_package(mc-gol CONFIG REQUIRED)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c pos-color-vertex.c
                                       pos-color-line.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

include(FetchContent)
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
FetchContent_MakeAvailable(as-c-math)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE minimal-cmake::game-of-life minimal-cmake::dynamic-array SDL2::SDL2
          SDL2::SDL2main bgfx::bgfx as-c-math)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
    BUILD_RPATH
    $<IF:$<PLATFORM_ID:Linux>,$ORIGIN,$<IF:$<PLATFORM_ID:Darwin>,@loader_path,>>
)

if(WIN32)
  # copy SDL2.dll and bgfx.dll to the same folder as the executable
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:bgfx::bgfx>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
  if(MC_GOL_SHARED)
    # copy mc-gol.dll to the same folder as the executable
    add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:mc-gol>
              $<TARGET_FILE_DIR:${PROJECT_NAME}>
      VERBATIM)
  endif()
endif()
