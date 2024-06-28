cmake_policy(SET CMP0140 NEW)

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/shader/build/vs_vertcol.bin)
  message(FATAL_ERROR "vs_vertcol.bin missing")
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/shader/build/fs_vertcol.bin)
  message(FATAL_ERROR "fs_vertcol.bin missing")
endif()
