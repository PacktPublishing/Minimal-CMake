ExternalProject_Add(
  ${CMAKE_PROJECT_NAME}_superbuild
  DEPENDS SDL2 bgfx mc-gol mc-draw
  SOURCE_DIR ${PROJECT_SOURCE_DIR}
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}
  CMAKE_ARGS -DCMAKE_PREFIX_PATH=${CMAKE_CURRENT_SOURCE_DIR}/third-party/install
             -DSUPERBUILD=OFF ${build_type_arg})
