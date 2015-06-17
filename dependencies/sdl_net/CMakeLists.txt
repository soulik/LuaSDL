cmake_minimum_required (VERSION 3.1.0)
project (SDLNET)

include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)

list(APPEND CMAKE_MODULE_PATH "${SDLNET_SOURCE_DIR}/cmake")

find_package(SDL REQUIRED)

set(SDL_LIBRARIES "${SDL_LIBRARY}")
set(SDL_INCLUDE_DIRS "${SDL_INCLUDE_DIR}")
set(SDLNET_LIBRARIES "")

include_directories(${SDL_INCLUDE_DIRS})

set(SDLNET_SRC
	SDLnet.c
	SDLnetTCP.c
	SDLnetUDP.c
	SDLnetselect.c
)

set(SDLNET_SOURCES
	${SDLNET_SRC} ${SDLNET_ADDITIONAL_SRC}
)

include_directories(./)

add_library(SDLNET SHARED
	${SDLNET_SOURCES}
)

set_target_properties(SDLNET
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (WIN32)
	LIST(APPEND SDLNET_LIBRARIES wsock32.lib iphlpapi.lib)
else()
endif()

target_link_libraries (SDLNET
	${SDL_LIBRARIES}
	${SDLNET_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(SDLNET PROPERTIES
	PREFIX ""
	OUTPUT_NAME "SDL_net"
)
