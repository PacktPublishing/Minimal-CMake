#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "as-c-math" for configuration "Debug"
set_property(TARGET as-c-math APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(as-c-math PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libas-c-math.a"
  )

list(APPEND _cmake_import_check_targets as-c-math )
list(APPEND _cmake_import_check_files_for_as-c-math "${_IMPORT_PREFIX}/lib/libas-c-math.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
