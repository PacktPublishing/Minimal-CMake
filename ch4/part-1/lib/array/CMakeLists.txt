cmake_minimum_required(VERSION 3.28)
project(array LANGUAGES C)
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE array.c)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)
