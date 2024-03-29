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
  GIT_TAG 108b653154b7e55832d4dc1386feb91b3db88880)
set(AS_MATH_ENABLE_TEST
    OFF
    CACHE INTERNAL "")
set(AS_MATH_ENABLE_COVERAGE
    OFF
    CACHE INTERNAL "")
FetchContent_Declare(
  minimal-cmake-array
  GIT_REPOSITORY https://github.com/PacktPublishing/Minimal-CMake.git
  GIT_TAG d4b3fef8d2be74c1b6f8eebdf68b3c7bdc9a6668
  SOURCE_SUBDIR ch4/part-3/lib/array) # only look in array folder

FetchContent_MakeAvailable(as-c-math minimal-cmake-array)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} BASE_NAME mc_gol)

target_link_libraries(${PROJECT_NAME} PRIVATE as-c-math mc-array)
