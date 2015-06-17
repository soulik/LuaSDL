cmake_minimum_required (VERSION 3.1.0)
project (SDLTTF)

include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)

list(APPEND CMAKE_MODULE_PATH "${SDLTTF_SOURCE_DIR}/cmake")

find_package(SDL REQUIRED)

set(SDL_LIBRARIES "${SDL_LIBRARY}")
set(SDL_INCLUDE_DIRS "${SDL_INCLUDE_DIR}")
set(SDLTTF_LIBRARIES "")

include_directories(${SDL_INCLUDE_DIRS})

set(BUILD_SHARED_LIBS ON)
add_subdirectory(external/freetype-2.5.5)
include_directories(external/freetype-2.5.5/include)
list(APPEND SDLTTF_LIBRARIES freetype)

set_target_properties(freetype
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set(SDLTTF_SRC
	SDL_ttf.c
)

set(SDLTTF_SOURCES
	${SDLTTF_SRC} ${SDLTTF_ADDITIONAL_SRC}
)

include_directories(./)

add_library(SDLTTF SHARED
	${SDLTTF_SOURCES}
)

set_target_properties(SDLTTF
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries (SDLTTF
	${SDL_LIBRARIES} ${SDLTTF_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(SDLTTF PROPERTIES
	PREFIX ""
	OUTPUT_NAME "SDL_ttf"
)
