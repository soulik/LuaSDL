cmake_minimum_required (VERSION 3.1.0)
project (SDL)

list(APPEND CMAKE_MODULE_PATH "${SDLIMAGE_SOURCE_DIR}/cmake")

include(testOS)
include(testArchitecture)
include(AC_HEADER_STDC)

include_directories(include)

add_subdirectory(src)

# add libcaca
add_subdirectory(dependencies/libcaca)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

set_target_properties(SDL PROPERTIES
	OUTPUT_NAME "SDL"
)

if (WIN32)
	set_target_properties(SDL PROPERTIES
		PREFIX ""
	)
endif()