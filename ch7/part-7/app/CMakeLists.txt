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
find_package(mc-gol MODULE REQUIRED) # updated (MODULE not CONFIG)
find_package(mc-draw 1.0 CONFIG REQUIRED COMPONENTS line quad vertex)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE minimal-cmake::game-of-life
          minimal-cmake::dynamic-array
          minimal-cmake::vertex
          minimal-cmake::line
          minimal-cmake::quad
          SDL2::SDL2
          SDL2::SDL2main
          bgfx::bgfx)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
    BUILD_RPATH
    $<IF:$<PLATFORM_ID:Linux>,$ORIGIN,$<IF:$<PLATFORM_ID:Darwin>,@loader_path,>>
)

if(WIN32)
  # copy SDL2.dll, bgfx.dll, and game-of-life.dll to the same folder as the
  # executable
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:bgfx::bgfx>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:minimal-cmake::game-of-life>
      $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:minimal-cmake::draw>
      $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif()
