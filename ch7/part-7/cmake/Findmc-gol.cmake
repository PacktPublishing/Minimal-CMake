# use the find_path() function to locate the header file
# second parameter must match folder name
find_path(mc-gol_INCLUDE_DIR minimal-cmake-gol PATHS ${mc-gol_PATH}/include)

# use the find_library() function to locate the library binary
# second parameter must match library (target) name
find_library(
  mc-gol_LIBRARY
  NAMES game-of-life game-of-lifed
  PATHS ${mc-gol_PATH}/lib)

# on Windows, attempt to locate a .dll file (if the library was built as shared)
if(WIN32)
  find_file(
    mc-gol_DLL
    NAMES game-of-life.dll game-of-lifed.dll
    PATHS ${mc-gol_PATH}/bin)
endif()

include(FindPackageHandleStandardArgs)

# handle find_package standard args (include mc-gol_DLL in the shared library
# case on Windows)
if(mc-gol_DLL)
  find_package_handle_standard_args(mc-gol DEFAULT_MSG mc-gol_LIBRARY
                                    mc-gol_INCLUDE_DIR mc-gol_DLL)
else()
  find_package_handle_standard_args(mc-gol DEFAULT_MSG mc-gol_LIBRARY
                                    mc-gol_INCLUDE_DIR)
endif()

# if the library has been found, define the imported target
if(mc-gol_FOUND AND NOT TARGET minimal-cmake::game-of-life)
  if(WIN32)
    # if a .dll file was found, reference .lib file using IMPORTED_LIB, and
    # .dll file using IMPORTED_LOCATION, otherwise default to normal static
    # behaviour
    if(mc-gol_DLL)
      add_library(minimal-cmake::game-of-life SHARED IMPORTED)
      set_target_properties(
        minimal-cmake::game-of-life
        PROPERTIES IMPORTED_IMPLIB "${mc-gol_LIBRARY}"
                   IMPORTED_LOCATION "${mc-gol_DLL}"
                   INTERFACE_INCLUDE_DIRECTORIES "${mc-gol_INCLUDE_DIR}")
    else()
      add_library(minimal-cmake::game-of-life STATIC IMPORTED)
      set_target_properties(
        minimal-cmake::game-of-life
        PROPERTIES IMPORTED_LOCATION "${mc-gol_LIBRARY}"
                   INTERFACE_INCLUDE_DIRECTORIES "${mc-gol_INCLUDE_DIR}")
    endif()
  else()
    cmake_path(GET mc-gol_LIBRARY EXTENSION LAST_ONLY mc-gol_LIBRARY_EXT)
    if(${mc-gol_LIBRARY_EXT} STREQUAL ${CMAKE_SHARED_LIBRARY_SUFFIX})
      add_library(minimal-cmake::game-of-life SHARED IMPORTED)
    else()
      add_library(minimal-cmake::game-of-life STATIC IMPORTED)
    endif()
    set_target_properties(
      minimal-cmake::game-of-life
      PROPERTIES IMPORTED_LOCATION "${mc-gol_LIBRARY}"
                 INTERFACE_INCLUDE_DIRECTORIES "${mc-gol_INCLUDE_DIR}")
  endif()
endif()
