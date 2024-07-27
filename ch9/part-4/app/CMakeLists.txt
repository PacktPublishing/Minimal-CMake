cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life_window LANGUAGES CXX)

include(GNUInstallDirs)

option(SUPERBUILD "Perform a superbuild (or not)" OFF)
option(USE_VERBOSE_SHADER_OUTPUT "Show output from shader compilation" OFF)
option(MC_GOL_APP_BUILD_TESTING "Enable testing" OFF)

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

add_library(${PROJECT_NAME}-common INTERFACE)
target_sources(
  ${PROJECT_NAME}-common
  INTERFACE src/main.cpp src/imgui/sdl2/imgui_impl_sdl2.cpp
            src/imgui/bgfx/imgui_impl_bgfx.cpp src/viewport/screen.cpp)
target_link_libraries(
  ${PROJECT_NAME}-common
  INTERFACE minimal-cmake::game-of-life
            minimal-cmake::vertex
            minimal-cmake::line
            minimal-cmake::quad
            SDL2::SDL2
            SDL2::SDL2main
            bgfx::bgfx
            bgfx::bx
            imgui-test-engine.cmake::imgui-test-engine.cmake)
set_target_properties(
  ${PROJECT_NAME}-common
  PROPERTIES
    INSTALL_RPATH
    "$<$<PLATFORM_ID:Linux>:$ORIGIN>$<$<PLATFORM_ID:Darwin>:@loader_path>"
    BUILD_WITH_INSTALL_RPATH TRUE)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-common)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

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

if(MC_GOL_APP_BUILD_TESTING)
  include(CTest)
  add_executable(${PROJECT_NAME}-test)
  target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME}-common)
  target_compile_features(${PROJECT_NAME}-test PRIVATE cxx_std_20)
  target_sources(${PROJECT_NAME}-test PRIVATE tests/gol-tests.cpp)
  target_compile_definitions(
    ${PROJECT_NAME}-test
    PRIVATE
      MC_GOL_APP_BUILD_TESTING
      $<$<BOOL:${MC_GOL_APP_INTERACTIVE_TESTING}>:MC_GOL_APP_INTERACTIVE_TESTING>
  )
  add_test(
    NAME "game of life end-to-end tests"
    COMMAND ${PROJECT_NAME}-test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

  find_package(Catch2 REQUIRED CONFIG)
  add_executable(${PROJECT_NAME}-unit-test)
  target_sources(${PROJECT_NAME}-unit-test PRIVATE src/viewport/screen.cpp
                                                   src/viewport/screen.test.cpp)
  target_link_libraries(${PROJECT_NAME}-unit-test Catch2::Catch2WithMain
                        as-c-math)
  target_compile_features(${PROJECT_NAME}-unit-test PRIVATE cxx_std_20)

  add_test(NAME "game of life unit tests" COMMAND ${PROJECT_NAME}-unit-test)
  # cmake-format: off
  # example of using PASS_REGULAR_EXPRESSION property for pass/fail check
  # set_tests_properties("game of life unit tests"
  #                     PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed")
  # cmake-format: on

  add_test(
    NAME "shaders compiled"
    COMMAND ${CMAKE_COMMAND} -P tests/shaders-compiled.cmake
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
