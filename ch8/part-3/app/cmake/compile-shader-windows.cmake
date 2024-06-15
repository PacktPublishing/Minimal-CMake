get_filename_component(COMPILE_SHADER_DIR ${CMAKE_SCRIPT_MODE_FILE} DIRECTORY)
cmake_path(GET COMPILE_SHADER_DIR PARENT_PATH COMPILE_SHADER_WORKING_DIR)

option(USE_VERBOSE_SHADER_OUTPUT "" OFF)
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
