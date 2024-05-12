#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "minimal-cmake::mc-draw" for configuration "Debug"
set_property(TARGET minimal-cmake::mc-draw APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(minimal-cmake::mc-draw PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "bgfx::bgfx"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libmc-drawd.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libmc-drawd.dylib"
  )

list(APPEND _cmake_import_check_targets minimal-cmake::mc-draw )
list(APPEND _cmake_import_check_files_for_minimal-cmake::mc-draw "${_IMPORT_PREFIX}/lib/libmc-drawd.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
