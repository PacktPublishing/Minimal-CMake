cmake_minimum_required(VERSION 3.28)
project(mc-utils LANGUAGES C)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_LOCAL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_compile_features(${PROJECT_NAME} INTERFACE c_std_17)
