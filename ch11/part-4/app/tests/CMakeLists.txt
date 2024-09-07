add_library(${PROJECT_NAME}-coverage INTERFACE)
set(coverage_flags
    "$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:--coverage>"
)
target_compile_options(${PROJECT_NAME}-coverage INTERFACE ${coverage_flags})
target_link_options(${PROJECT_NAME}-coverage INTERFACE ${coverage_flags})

include(CTest)
enable_testing()
add_executable(${PROJECT_NAME}-test)
target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME}-common
                                                   ${PROJECT_NAME}-coverage)
target_compile_features(${PROJECT_NAME}-test PRIVATE cxx_std_20)
set_common_target_properties(${PROJECT_NAME}-test)
target_sources(${PROJECT_NAME}-test
               PRIVATE ${CMAKE_SOURCE_DIR}/tests/gol-tests.cpp)
target_compile_definitions(
  ${PROJECT_NAME}-test
  PRIVATE
    MC_GOL_APP_BUILD_TESTING
    $<$<BOOL:${MC_GOL_APP_INTERACTIVE_TESTING}>:MC_GOL_APP_INTERACTIVE_TESTING>)
add_test(
  NAME "game of life end-to-end tests"
  COMMAND ${PROJECT_NAME}-test
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set_tests_properties("game of life end-to-end tests"
                     PROPERTIES LABELS "end-to-end;slow")

find_package(Catch2 REQUIRED CONFIG)
add_executable(${PROJECT_NAME}-unit-test)
target_sources(
  ${PROJECT_NAME}-unit-test
  PRIVATE ${CMAKE_SOURCE_DIR}/src/viewport/screen.cpp
          ${CMAKE_SOURCE_DIR}/src/viewport/screen.test.cpp)
target_link_libraries(${PROJECT_NAME}-unit-test Catch2::Catch2WithMain
                      as-c-math ${PROJECT_NAME}-coverage)
target_compile_features(${PROJECT_NAME}-unit-test PRIVATE cxx_std_20)

add_test(NAME "game of life unit tests" COMMAND ${PROJECT_NAME}-unit-test)

add_test(
  NAME "shaders compiled"
  COMMAND ${CMAKE_COMMAND} -P shaders-compiled.cmake
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake.in
               ${CMAKE_BINARY_DIR}/CTestCustom.cmake COPYONLY)
