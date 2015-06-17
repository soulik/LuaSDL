# - Try to find vgl
# Once done, this will define
#
#  vgl_FOUND - system has VGL
#  vgl_INCLUDE_DIRS - the VGL include directories
#  vgl_LIBRARIES - link these to use VGL

include(LibFindMacros)

# Dependencies
libfind_package(vgl vgl)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(vgl_PKGCONF vgl)

# Include dir
find_path(vgl_INCLUDE_DIR
  NAMES vgl.h
  PATHS ${vgl_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(vgl_LIBRARY
  NAMES vgl
  PATHS ${vgl_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(vgl_PROCESS_INCLUDES vgl_INCLUDE_DIR vgl_INCLUDE_DIRS)
set(vgl_PROCESS_LIBS vgl_LIBRARY vgl_LIBRARIES)
libfind_process(vgl)
