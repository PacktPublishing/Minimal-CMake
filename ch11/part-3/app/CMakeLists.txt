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
target_compile_features(${PROJECT_NAME}-common INTERFACE cxx_std_20)

# cmake-format: off
string(
  APPEND
  compile_options
  "$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:"
    "-Weverything;-Wno-c++98-compat;-Wno-;-Wno-global-constructors;"
    "-Wno-;-Wno-c++98-compat-pedantic;-Wno-;-Wno-padded;-Wno->"
  "$<$<CXX_COMPILER_ID:MSVC>:"
    "/W4;/permissive-;/w14640;/w14242;/w14254;/w14263;/w14265;/w14287;"
    "/we4289;/w14296;/w14311;/w14545;/w14546;/w14547;/w14549;/w14555;"
    "/w14619;/w14640;/w14826;/w14928;/w14800>"
  "$<$<CXX_COMPILER_ID:GNU>:"
    "-Wall;-Wextra;-Wshadow;-Wnon-virtual-dtor;-Wpedantic;-Wold-style-cast;"
    "-Wcast-align;-Wunused;-Wconversion;"
    "-Wmisleading-indentation;-Wduplicated-cond;-Wduplicated-branches;"
    "-Wlogical-op;-Wnull-dereference;-Wdouble-promotion;-Wuseless-cast>")
# cmake-format: on

target_compile_options(${PROJECT_NAME}-common INTERFACE ${compile_options})

function(set_common_target_properties TARGET_NAME)
  set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
      INSTALL_RPATH
      "$<$<PLATFORM_ID:Linux>:$ORIGIN>$<$<PLATFORM_ID:Darwin>:@loader_path>"
      BUILD_WITH_INSTALL_RPATH TRUE
      CXX_STANDARD_REQUIRED ON
      CXX_EXTENSIONS OFF)
endfunction()

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-common)
set_common_target_properties(${PROJECT_NAME})

if(WIN32)
  # windows icon
  target_sources(${PROJECT_NAME} PRIVATE packaging/windows/icon.rc)
  set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE
                                                   $<CONFIG:Release>)
endif()

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

# copy dynamic libraries to the same folder as the executable and copy compiled
# shaders to nested shader folder
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
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader/build
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/shader
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
install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/shader/build/
  DESTINATION ${CMAKE_INSTALL_BINDIR}/shader
  FILES_MATCHING
  PATTERN "*.bin")
if(LINUX)
  # linux icon
  install(FILES ${CMAKE_SOURCE_DIR}/packaging/linux/mc-gol.desktop
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
  install(FILES ${CMAKE_SOURCE_DIR}/packaging/linux/mc-gol-logo.png
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons)
endif()

if(MC_GOL_APP_BUILD_TESTING)
  add_subdirectory(tests)
endif()

add_subdirectory(packaging)
