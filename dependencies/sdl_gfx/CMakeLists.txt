cmake_minimum_required (VERSION 3.1.0)
project (SDLGFX)

include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)

set(CMAKE_MODULE_PATH "${SDLGFX_SOURCE_DIR}/cmake")

find_package(SDL REQUIRED)

set(SDL_LIBRARIES "${SDL_LIBRARY}")
set(SDL_INCLUDE_DIRS "${SDL_INCLUDE_DIR}")
set(SDLGFX_LIBRARIES "")

include_directories(${SDL_INCLUDE_DIRS})

set_target_properties(freetype
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set(SDLGFX_SRC
	SDL_framerate.c
	SDL_gfxBlitFunc.c
	SDL_gfxPrimitives.c
	SDL_imageFilter.c
	SDL_rotozoom.c
)

set(SDLGFX_SOURCES
	${SDLGFX_SRC} ${SDLGFX_ADDITIONAL_SRC}
)

include_directories(./)

set(SDLGFX_USE_MMX OFF CACHE BOOL "Use MMX instructions")

if (SDLGFX_USE_MMX)
	add_definitions(-DUSE_MMX)
endif()

add_definitions(-DDLL_EXPORT)

add_library(SDLGFX SHARED
	${SDLGFX_SOURCES}
)

set_target_properties(SDLGFX
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries (SDLGFX
	${SDL_LIBRARIES} ${SDLGFX_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(SDLGFX PROPERTIES
	PREFIX ""
	OUTPUT_NAME "SDL_gfx"
)
