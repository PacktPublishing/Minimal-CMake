cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life_window LANGUAGES C)

include(GNUInstallDirs)

option(SUPERBUILD "Perform a superbuild (or not)" OFF)

if(SUPERBUILD)
  add_subdirectory(third-party)
  include(cmake/superbuild.cmake)
  return()
endif()

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
find_package(mc-draw 3.0 CONFIG REQUIRED COMPONENTS line quad vertex)

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
    INSTALL_RPATH
    $<IF:$<PLATFORM_ID:Linux>,$ORIGIN,$<IF:$<PLATFORM_ID:Darwin>,@loader_path,>>
    BUILD_WITH_INSTALL_RPATH TRUE)

if(WIN32)
  set(COMPILE_SHADER_SCRIPT
      ${CMAKE_SOURCE_DIR}/cmake/compile-shader-windows.cmake)
elseif(LINUX)
  set(COMPILE_SHADER_SCRIPT
      ${CMAKE_SOURCE_DIR}/cmake/compile-shader-linux.cmake)
elseif(APPLE)
  set(COMPILE_SHADER_SCRIPT
      ${CMAKE_SOURCE_DIR}/cmake/compile-shader-macos.cmake)
endif()

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -P ${COMPILE_SHADER_SCRIPT}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  VERBATIM)

# copy dynamic libraries to the same folder as the executable
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2>
    $<TARGET_FILE:bgfx::bgfx> $<TARGET_FILE:minimal-cmake::game-of-life>
    $<TARGET_FILE:minimal-cmake::vertex> $<TARGET_FILE:minimal-cmake::quad>
    $<TARGET_FILE:minimal-cmake::line> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  VERBATIM)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(
  FILES $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE:bgfx::bgfx>
        $<TARGET_FILE:minimal-cmake::game-of-life>
        $<TARGET_FILE:minimal-cmake::vertex>
        $<TARGET_FILE:minimal-cmake::quad>
        $<TARGET_FILE:minimal-cmake::line>
  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/shader/build
        DESTINATION ${CMAKE_INSTALL_BINDIR}/shader)