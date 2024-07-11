if(NOT CMAKE_SCRIPT_MODE_FILE)
  message(
    WARNING
      "This script cannot be included, it must be executed using `cmake -P`")
  return()
endif()

cmake_path(GET CMAKE_SCRIPT_MODE_FILE PARENT_PATH COMPILE_SHADER_DIR)
cmake_path(GET COMPILE_SHADER_DIR PARENT_PATH COMPILE_SHADER_WORKING_DIR)

option(USE_VERBOSE_SHADER_OUTPUT "Show output from shader compilation" OFF)
if(USE_VERBOSE_SHADER_OUTPUT)
  set(VERBOSE_SHADER_OUTPUT --verbose)
else()
  set(QUIET_SHADER_OUTPUT ERROR_QUIET)
endif()

# cmake-format: off
file(MAKE_DIRECTORY ${COMPILE_SHADER_WORKING_DIR}/shader/build)
execute_process(
  COMMAND
    third-party/install/bin/shaderc.exe
    -f shader/vs_vertcol.sc
    -o shader/build/vs_vertcol.bin
    --platform windows
    --type vertex
    -i ./
    -p s_5_0
    ${VERBOSE_SHADER_OUTPUT}
  ${QUIET_SHADER_OUTPUT}
  WORKING_DIRECTORY ${COMPILE_SHADER_WORKING_DIR})
execute_process(
  COMMAND
    third-party/install/bin/shaderc.exe
    -f shader/fs_vertcol.sc
    -o shader/build/fs_vertcol.bin
    --platform windows
    --type fragment
    -i ./
    -p s_5_0
    ${VERBOSE_SHADER_OUTPUT}
  ${QUIET_SHADER_OUTPUT}
  WORKING_DIRECTORY ${COMPILE_SHADER_WORKING_DIR})
# cmake-format: on
