# use the find_path() function to locate the header file
# second parameter must match folder name
find_path(mc-gol_INCLUDE_DIR minimal-cmake-gol PATHS ${mc-gol_PATH}/include)

# use the find_library() function to locate the library binary
# second parameter must match library (target) name
find_library(
  mc-gol_LIBRARY
  NAMES game-of-life
  PATHS ${mc-gol_PATH}/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(mc-gol DEFAULT_MSG mc-gol_LIBRARY
                                  mc-gol_INCLUDE_DIR)

# if the library has been found, define the imported target
if(mc-gol_FOUND AND NOT TARGET minimal-cmake::game-of-life)
  add_library(minimal-cmake::game-of-life UNKNOWN IMPORTED)
  set_target_properties(
    minimal-cmake::game-of-life
    PROPERTIES IMPORTED_LOCATION "${mc-gol_LIBRARY}"
               INTERFACE_INCLUDE_DIRECTORIES "${mc-gol_INCLUDE_DIR}")
endif()
