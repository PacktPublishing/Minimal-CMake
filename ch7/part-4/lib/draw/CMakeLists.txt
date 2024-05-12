cmake_minimum_required(VERSION 3.28)

project(mc-draw LANGUAGES C)

include(GNUInstallDirs)

find_package(bgfx CONFIG REQUIRED)
find_package(mc-array CONFIG REQUIRED)

option(MC_DRAW_SHARED "Enable shared library (dynamic linking)" OFF)

set(MC_DRAW_LIB_TYPE STATIC)
if(MC_DRAW_SHARED)
  set(MC_DRAW_LIB_TYPE SHARED)
endif()

add_library(${PROJECT_NAME} ${MC_DRAW_LIB_TYPE})

target_sources(${PROJECT_NAME} PRIVATE src/pos-color-vertex.c
                                       src/pos-color-line.c)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    "$<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/;${CMAKE_CURRENT_BINARY_DIR}/>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

include(FetchContent)
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

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} BASE_NAME mc_draw)
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES C_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN ON
             C_STANDARD_REQUIRED ON
             C_EXTENSIONS OFF
             DEBUG_POSTFIX "d")
target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC as-c-math
  PRIVATE $<BUILD_LOCAL_INTERFACE:bgfx::bgfx minimal-cmake::dynamic-array>)
target_compile_definitions(
  ${PROJECT_NAME}
  PUBLIC $<$<NOT:$<BOOL:${MC_DRAW_SHARED}>>:MC_DRAW_STATIC_DEFINE>)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(
  EXPORT ${PROJECT_NAME}-config
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  NAMESPACE minimal-cmake::
  FILE ${PROJECT_NAME}-targets.cmake)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/minimal-cmake/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/minimal-cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mc_draw_export.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(${PROJECT_NAME}-config.cmake.in ${PROJECT_NAME}-config.cmake
               @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
