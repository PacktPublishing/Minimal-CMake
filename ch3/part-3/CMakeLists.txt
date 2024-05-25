cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life LANGUAGES C)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c array/array.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

# no FetchContent

if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" OR "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "AMD64")
  set(platform_dir x86_64)
elseif("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "arm64" OR "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "aarch64")
  set(platform_dir arm64)
else()
  message(STATUS "Unsupported target architecture ${CMAKE_SYSTEM_PROCESSOR}")
  return()
endif()

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third-party/timer-lib/include)
target_link_directories(
  ${PROJECT_NAME}
  PRIVATE
  $<$<PLATFORM_ID:Darwin>:${CMAKE_CURRENT_SOURCE_DIR}/third-party/timer-lib/lib/macos>
  $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/third-party/timer-lib/lib/win/${platform_dir}>
  $<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/third-party/timer-lib/lib/linux>
)
target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib)
