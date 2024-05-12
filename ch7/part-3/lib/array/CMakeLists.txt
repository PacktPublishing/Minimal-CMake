cmake_minimum_required(VERSION 3.28)

project(mc-array LANGUAGES C)

add_library(dynamic-array STATIC)
target_sources(dynamic-array PRIVATE src/array.c)

include(GNUInstallDirs)

target_include_directories(
  dynamic-array
  PUBLIC $<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(dynamic-array PRIVATE c_std_17)
set_target_properties(dynamic-array PROPERTIES DEBUG_POSTFIX "d")

install(
  TARGETS dynamic-array
  EXPORT ${PROJECT_NAME}-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
  EXPORT ${PROJECT_NAME}-config
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  NAMESPACE minimal-cmake::)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/minimal-cmake/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/minimal-cmake)
