cmake_minimum_required(VERSION 3.28)
project(mc-gol LANGUAGES C)

option(MC_GOL_SHARED "Enable shared library (dynamic linking)" OFF)

set(MC_GOL_LIB_TYPE STATIC)
if(MC_GOL_SHARED)
  set(MC_GOL_LIB_TYPE SHARED)
endif()

add_library(${PROJECT_NAME} ${MC_GOL_LIB_TYPE})

target_sources(${PROJECT_NAME} PRIVATE src/gol.c)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    "$<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/;${CMAKE_CURRENT_BINARY_DIR}/>"
)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

include(FetchContent)
FetchContent_Declare(
  as-c-math
  GIT_REPOSITORY https://github.com/pr0g/as-c-math.git
  GIT_TAG 05094067885567480271c14c64f3324e000c9c04)
set(AS_MATH_ENABLE_TEST
    OFF
    CACHE INTERNAL "")
set(AS_MATH_ENABLE_COVERAGE
    OFF
    CACHE INTERNAL "")
FetchContent_Declare(
  minimal-cmake-array
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG 3eafd75e33ad0fd424e613ec4d5adb3cf3a6c2bf
  SOURCE_SUBDIR ch4/part-3/lib/array) # only look in array folder
FetchContent_Declare(minimal-cmake-utils SOURCE_DIR ../../utils)
FetchContent_MakeAvailable(as-c-math minimal-cmake-array minimal-cmake-utils)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} BASE_NAME mc_gol)
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES C_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN ON
             C_STANDARD_REQUIRED ON
             C_EXTENSIONS OFF)
target_link_libraries(${PROJECT_NAME} PRIVATE as-c-math mc-array mc-utils)
target_compile_definitions(
  ${PROJECT_NAME}
  PUBLIC $<$<NOT:$<BOOL:${MC_GOL_SHARED}>>:MC_GOL_STATIC_DEFINE>)
