cmake_minimum_required (VERSION 3.1.0)

project (VORBIS)

include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)

if (NOT TARGET OGG)
	add_subdirectory(../libogg-1.3.1 "${CMAKE_CURRENT_BINARY_DIR}/libogg")
endif()
include_directories(../libogg-1.3.1/include)

include_directories("${VORBIS_SOURCE_DIR}/include")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

include(cmake/libvorbis.cmake)
include(cmake/libvorbisfile.cmake)
