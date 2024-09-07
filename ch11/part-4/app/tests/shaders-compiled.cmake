# verify shaders have been compiled

if(NOT EXISTS shader/build/vs_vertcol.bin)
  message(FATAL_ERROR "vs_vertcol.bin missing")
endif()

if(NOT EXISTS shader/build/fs_vertcol.bin)
  message(FATAL_ERROR "fs_vertcol.bin missing")
endif()
