# general CPack options
set(CPACK_PACKAGE_NAME "minimal-cmake_game-of-life")
# required for NSIS installer - Start Menu icon
set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "Minimal CMake - Game of Life")

# Linux debian specific options
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "<maintainer-email>")

# macOS bundle specific options
set(CPACK_BUNDLE_NAME "Minimal CMake - Game of Life")
set(CPACK_BUNDLE_PLIST "${CMAKE_SOURCE_DIR}/packaging/macos/info.plist")
set(CPACK_BUNDLE_ICON "${CMAKE_SOURCE_DIR}/packaging/macos/gol.icns")
set(CPACK_BUNDLE_STARTUP_COMMAND
    "${CMAKE_SOURCE_DIR}/packaging/macos/bundle-run.sh")
# macOS dmg specific options (used by bundle as well)
set(CPACK_DMG_DS_STORE "${CMAKE_SOURCE_DIR}/packaging/macos/custom_DS_Store")
set(CPACK_DMG_BACKGROUND_IMAGE
    "${CMAKE_SOURCE_DIR}/packaging/macos/dmg-background.png")

# Windows NSIS specific options
set(CPACK_NSIS_PACKAGE_NAME "Minimal CMake - Game of Life")
set(CPACK_NSIS_MANIFEST_DPI_AWARE true)
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/packaging/windows/mc_icon.ico")
set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
    "CreateShortCut '$DESKTOP\\\\Minimal CMake - Game of Life.lnk' '$INSTDIR\\\\bin\\\\${PROJECT_NAME}.exe'"
)
set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
    "Delete '$DESKTOP\\\\Minimal CMake - Game of Life.lnk'")

# cmake-format: off
set(CPACK_SOURCE_IGNORE_FILES
  "build.*\/"
  "package.*\/"
  "install\/"
  "\.git\/"
  "\.gitignore"
  "\.vscode")
# cmake-format: on

include(CPack)
