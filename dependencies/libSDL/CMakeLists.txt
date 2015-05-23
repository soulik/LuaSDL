cmake_minimum_required (VERSION 3.1.0)
project (SDL)

set(CMAKE_MODULE_PATH "${SDLIMAGE_SOURCE_DIR}/cmake")
include(${SDL_SOURCE_DIR}/cmake/testOS.cmake)

include_directories(include)

add_subdirectory(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(SDL PROPERTIES
	PREFIX ""
	OUTPUT_NAME "SDL"
)
