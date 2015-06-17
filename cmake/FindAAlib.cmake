# - Try to find AAlib
# Once done, this will define
#
#  AAlib_FOUND - system has AA
#  AAlib_INCLUDE_DIRS - the AA include directories
#  AAlib_LIBRARIES - link these to use AA

include(LibFindMacros)

# Dependencies
#libfind_package(AAlib aalib)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(AAlib_PKGCONF aalib)

# Include dir
find_path(AAlib_INCLUDE_DIR
  NAMES aalib.h
  PATHS ${AAlib_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(AAlib_LIBRARY
  NAMES aa
  PATHS ${AAlib_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(AAlib_PROCESS_INCLUDES AAlib_INCLUDE_DIR)
set(AAlib_PROCESS_LIBS AAlib_LIBRARY)
libfind_process(AAlib)