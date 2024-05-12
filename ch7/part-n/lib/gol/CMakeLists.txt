cmake_minimum_required(VERSION 3.28)
project(mc-gol LANGUAGES C)

include(GNUInstallDirs)

find_package(mc-array CONFIG REQUIRED)

option(MC_GOL_SHARED "Enable shared library (dynamic linking)" OFF)

set(MC_GOL_LIB_TYPE STATIC)
if(MC_GOL_SHARED)
  set(MC_GOL_LIB_TYPE SHARED)
endif()

add_library(game-of-life ${MC_GOL_LIB_TYPE})

target_sources(game-of-life PRIVATE src/gol.c)
target_include_directories(
  game-of-life
  PUBLIC
    "$<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/;${CMAKE_CURRENT_BINARY_DIR}/>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_compile_features(game-of-life PRIVATE c_std_17)

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
FetchContent_Declare(
  minimal-cmake-utils
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG d4b3fef8d2be74c1b6f8eebdf68b3c7bdc9a6668
  SOURCE_SUBDIR ch4/part-6/lib/utils) # only look in utils folder
FetchContent_MakeAvailable(as-c-math minimal-cmake-utils)

include(GenerateExportHeader)
generate_export_header(game-of-life BASE_NAME mc_gol)
set_target_properties(
  game-of-life
  PROPERTIES C_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN ON
             C_STANDARD_REQUIRED ON
             C_EXTENSIONS OFF
             DEBUG_POSTFIX "d")
target_link_libraries(
  game-of-life PRIVATE $<BUILD_LOCAL_INTERFACE:as-c-math
                       minimal-cmake::dynamic-array mc-utils>)
target_compile_definitions(
  game-of-life PUBLIC $<$<NOT:$<BOOL:${MC_GOL_SHARED}>>:MC_GOL_STATIC_DEFINE>)

install(
  TARGETS game-of-life
  EXPORT ${PROJECT_NAME}-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
  EXPORT ${PROJECT_NAME}-config
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  NAMESPACE minimal-cmake::)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/minimal-cmake-gol/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/minimal-cmake-gol)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mc_gol_export.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
