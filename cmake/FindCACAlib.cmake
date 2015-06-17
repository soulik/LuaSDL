# - Try to find CACAlib
# Once done, this will define
#
#  CACAlib_FOUND - system has caca
#  CACAlib_INCLUDE_DIRS - the caca include directories
#  CACAlib_LIBRARIES - link these to use caca

include(LibFindMacros)

# Dependencies
#libfind_package(CACAlib caca)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(CACAlib_PKGCONF caca)

# Include dir
find_path(CACAlib_INCLUDE_DIR
  NAMES caca.h
  PATHS ${CACAlib_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(CACAlib_LIBRARY
  NAMES caca
  PATHS ${CACAlib_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(CACAlib_PROCESS_INCLUDES CACAlib_INCLUDE_DIR)
set(CACAlib_PROCESS_LIBS CACAlib_LIBRARY)
libfind_process(CACAlib)
