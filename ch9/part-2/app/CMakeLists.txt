cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life_window LANGUAGES CXX)

include(GNUInstallDirs)

option(SUPERBUILD "Perform a superbuild (or not)" OFF)
option(USE_VERBOSE_SHADER_OUTPUT "Show output from shader compilation" OFF)

if(SUPERBUILD)
  add_subdirectory(third-party)
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
find_package(mc-gol CONFIG REQUIRED)
find_package(imgui-test-engine.cmake REQUIRED CONFIG)
find_package(mc-draw 3.0 CONFIG REQUIRED COMPONENTS line quad vertex)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp imgui/sdl2/imgui_impl_sdl2.cpp
                                       imgui/bgfx/imgui_impl_bgfx.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE minimal-cmake::game-of-life
          minimal-cmake::vertex
          minimal-cmake::line
          minimal-cmake::quad
          SDL2::SDL2
          SDL2::SDL2main
          bgfx::bgfx
          imgui-test-engine.cmake::imgui-test-engine.cmake)

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
  COMMAND
    ${CMAKE_COMMAND} -D USE_VERBOSE_SHADER_OUTPUT=${USE_VERBOSE_SHADER_OUTPUT}
    -P ${COMPILE_SHADER_SCRIPT}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  VERBATIM)

# copy dynamic libraries to the same folder as the executable
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2>
    $<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:SDL2::SDL2>>
    $<TARGET_FILE:bgfx::bgfx>
    $<$<STREQUAL:$<TARGET_PROPERTY:minimal-cmake::game-of-life,TYPE>,SHARED_LIBRARY>:$<TARGET_FILE:minimal-cmake::game-of-life>>
    $<$<STREQUAL:$<TARGET_PROPERTY:minimal-cmake::vertex,TYPE>,SHARED_LIBRARY>:$<TARGET_FILE:minimal-cmake::vertex>>
    $<$<STREQUAL:$<TARGET_PROPERTY:minimal-cmake::quad,TYPE>,SHARED_LIBRARY>:$<TARGET_FILE:minimal-cmake::quad>>
    $<$<STREQUAL:$<TARGET_PROPERTY:minimal-cmake::line,TYPE>,SHARED_LIBRARY>:$<TARGET_FILE:minimal-cmake::line>>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
  VERBATIM)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(
  FILES
    $<TARGET_FILE:SDL2::SDL2>
    $<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:SDL2::SDL2>>
    $<TARGET_FILE:bgfx::bgfx>
    $<$<STREQUAL:$<TARGET_PROPERTY:minimal-cmake::game-of-life,TYPE>,SHARED_LIBRARY>:$<TARGET_FILE:minimal-cmake::game-of-life>>
    $<$<STREQUAL:$<TARGET_PROPERTY:minimal-cmake::vertex,TYPE>,SHARED_LIBRARY>:$<TARGET_FILE:minimal-cmake::vertex>>
    $<$<STREQUAL:$<TARGET_PROPERTY:minimal-cmake::quad,TYPE>,SHARED_LIBRARY>:$<TARGET_FILE:minimal-cmake::quad>>
    $<$<STREQUAL:$<TARGET_PROPERTY:minimal-cmake::line,TYPE>,SHARED_LIBRARY>:$<TARGET_FILE:minimal-cmake::line>>
  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/shader/build
        DESTINATION ${CMAKE_INSTALL_BINDIR}/shader)
