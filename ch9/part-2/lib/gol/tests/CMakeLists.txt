include(CTest)
include(FetchContent)
FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG 5a36b197fb34c0a77ac891c355596cb5c25aaf5b)
FetchContent_MakeAvailable(unity)
add_executable(game-of-life-test)
target_sources(game-of-life-test PRIVATE ${CMAKE_SOURCE_DIR}/src/gol.test.c)
target_link_libraries(game-of-life-test PRIVATE game-of-life unity)
target_compile_features(game-of-life-test PRIVATE c_std_17)
add_test(NAME "game of life unit tests" COMMAND game-of-life-test)
