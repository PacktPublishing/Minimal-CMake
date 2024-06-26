cmake_minimum_required(VERSION 3.28)
project(minimal-cmake_game-of-life LANGUAGES C)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c array/array.c)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)

# no FetchContent

# pick sensible defaults for library architecture for main platforms
if(APPLE)
  set(MC_DEFAULT_ARCH arm64)
elseif(LINUX OR WIN32)
  set(MC_DEFAULT_ARCH x86_64)
else()
  message(FATAL_ERROR "Unsupported platform")
endif()
# pass through the default, and allow the user to modify the cache variable
set(MC_ARCH
    ${MC_DEFAULT_ARCH}
    CACHE STRING "Architecutre being compiled for")
# set supported values to be displayed in cmake-gui
set_property(CACHE MC_ARCH PROPERTY STRINGS x86_64 arm64)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third-party/timer-lib/include)
target_link_directories(
  ${PROJECT_NAME}
  PRIVATE
  $<$<PLATFORM_ID:Darwin>:${CMAKE_CURRENT_SOURCE_DIR}/third-party/timer-lib/lib/macos/${MC_ARCH}>
  $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/third-party/timer-lib/lib/win/${MC_ARCH}>
  $<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/third-party/timer-lib/lib/linux/${MC_ARCH}>
)
target_link_libraries(${PROJECT_NAME} PRIVATE timer_lib)
