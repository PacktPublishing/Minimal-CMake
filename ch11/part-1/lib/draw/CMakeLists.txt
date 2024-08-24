cmake_minimum_required(VERSION 3.28)

project(
  mc-draw
  LANGUAGES C
  VERSION 3.5.4)

include(FetchContent)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

find_package(bgfx CONFIG REQUIRED)
find_package(mc-array CONFIG REQUIRED)

option(MC_DRAW_SHARED "Enable shared library (dynamic linking)" OFF)

set(MC_DRAW_LIB_TYPE STATIC)
if(MC_DRAW_SHARED)
  set(MC_DRAW_LIB_TYPE SHARED)
endif()

FetchContent_Declare(
  as-c-math
  GIT_REPOSITORY https://github.com/pr0g/as-c-math.git
  GIT_TAG bfdd8539fe8b1825a6a3da53976b712f75b5a1ed)
set(AS_MATH_ENABLE_TEST
    OFF
    CACHE INTERNAL "")
set(AS_MATH_ENABLE_COVERAGE
    OFF
    CACHE INTERNAL "")
FetchContent_MakeAvailable(as-c-math)

add_library(vertex ${MC_DRAW_LIB_TYPE})
target_sources(vertex PRIVATE src/pos-color-vertex.c)
target_include_directories(
  vertex
  PUBLIC
    "$<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/;${CMAKE_CURRENT_BINARY_DIR}/>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${PROJECT_VERSION}>"
)
target_compile_features(vertex PRIVATE c_std_17)
generate_export_header(vertex BASE_NAME mc_vertex)
set_target_properties(
  vertex
  PROPERTIES C_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN ON
             C_STANDARD_REQUIRED ON
             C_EXTENSIONS OFF
             DEBUG_POSTFIX "d")
target_link_libraries(
  vertex
  PUBLIC as-c-math
  PRIVATE $<BUILD_LOCAL_INTERFACE:bgfx::bgfx minimal-cmake::dynamic-array>)
target_compile_definitions(
  vertex PUBLIC $<$<NOT:$<BOOL:${MC_DRAW_SHARED}>>:MC_DRAW_STATIC_DEFINE>)

add_library(line ${MC_DRAW_LIB_TYPE})
target_sources(line PRIVATE src/pos-color-line.c)
target_include_directories(
  line
  PUBLIC
    "$<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/;${CMAKE_CURRENT_BINARY_DIR}/>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${PROJECT_VERSION}>"
)
target_compile_features(line PRIVATE c_std_17)
generate_export_header(line BASE_NAME mc_line)
set_target_properties(
  line
  PROPERTIES C_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN ON
             C_STANDARD_REQUIRED ON
             C_EXTENSIONS OFF
             DEBUG_POSTFIX "d")
target_link_libraries(line PRIVATE $<BUILD_LOCAL_INTERFACE:bgfx::bgfx
                                   minimal-cmake::dynamic-array vertex>)
target_compile_definitions(
  line PUBLIC $<$<NOT:$<BOOL:${MC_DRAW_SHARED}>>:MC_DRAW_STATIC_DEFINE>)

add_library(quad ${MC_DRAW_LIB_TYPE})
target_sources(quad PRIVATE src/pos-color-quad.c)
target_include_directories(
  quad
  PUBLIC
    "$<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/;${CMAKE_CURRENT_BINARY_DIR}/>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${PROJECT_VERSION}>"
)
target_compile_features(quad PRIVATE c_std_17)
generate_export_header(quad BASE_NAME mc_quad)
set_target_properties(
  quad
  PROPERTIES C_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN ON
             C_STANDARD_REQUIRED ON
             C_EXTENSIONS OFF
             DEBUG_POSTFIX "d")
target_link_libraries(quad PRIVATE $<BUILD_LOCAL_INTERFACE:bgfx::bgfx
                                   minimal-cmake::dynamic-array vertex>)
target_compile_definitions(
  quad PUBLIC $<$<NOT:$<BOOL:${MC_DRAW_SHARED}>>:MC_DRAW_STATIC_DEFINE>)

install(
  TARGETS vertex
  EXPORT vertex-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
)

install(
  EXPORT vertex-config
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  NAMESPACE minimal-cmake::
  FILE vertex-targets.cmake)

configure_package_config_file(
  vertex-config.cmake.in vertex-config.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION})
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/vertex-config.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION})

install(
  TARGETS line
  EXPORT line-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
)

install(
  EXPORT line-config
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  NAMESPACE minimal-cmake::)

install(
  TARGETS quad
  EXPORT quad-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}-${PROJECT_VERSION}
)

install(
  EXPORT quad-config
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  NAMESPACE minimal-cmake::)

install(
  DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/minimal-cmake/
  DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${PROJECT_VERSION}/minimal-cmake
)
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/mc_line_export.h
        ${CMAKE_CURRENT_BINARY_DIR}/mc_vertex_export.h
        ${CMAKE_CURRENT_BINARY_DIR}/mc_quad_export.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${PROJECT_VERSION})

configure_package_config_file(
  ${PROJECT_NAME}-config.cmake.in ${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION})
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION})

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION})
