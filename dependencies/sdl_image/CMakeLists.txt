cmake_minimum_required (VERSION 3.1.0)
project (SDLIMAGE)

include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)

list(APPEND CMAKE_MODULE_PATH "${SDLIMAGE_SOURCE_DIR}/cmake")

find_package(SDL REQUIRED)

set(SDL_LIBRARIES "${SDL_LIBRARY}")
set(SDL_INCLUDE_DIRS "${SDL_INCLUDE_DIR}")

include_directories(${SDL_INCLUDE_DIRS})

set(SDLIMAGE_SUPPORT_BMP ON CACHE BOOL "Support for BMP file format")
set(SDLIMAGE_SUPPORT_GIF ON CACHE BOOL "Support for GIF file format")
set(SDLIMAGE_SUPPORT_LBM ON CACHE BOOL "Support for LBM file format")
set(SDLIMAGE_SUPPORT_PCX ON CACHE BOOL "Support for PCX file format")
set(SDLIMAGE_SUPPORT_PNM ON CACHE BOOL "Support for PNM file format")
set(SDLIMAGE_SUPPORT_TGA ON CACHE BOOL "Support for TGA file format")
set(SDLIMAGE_SUPPORT_XPM ON CACHE BOOL "Support for XPM file format")
set(SDLIMAGE_SUPPORT_XV ON CACHE BOOL "Support for XV file format")

set(SDLIMAGE_SUPPORT_JPEG ON CACHE BOOL "Support for JPEG file format")
set(SDLIMAGE_SUPPORT_PNG ON CACHE BOOL "Support for PNG file format")
set(SDLIMAGE_SUPPORT_WEBP ON CACHE BOOL "Support for WEBP file format")
set(SDLIMAGE_SUPPORT_TIFF ON CACHE BOOL "Support for TIFF file format")

if(SDLIMAGE_SUPPORT_BMP)
	add_definitions(-DLOAD_BMP)
endif()
if(SDLIMAGE_SUPPORT_GIF)
	add_definitions(-DLOAD_GIF)
endif()
if(SDLIMAGE_SUPPORT_LBM)
	add_definitions(-DLOAD_LBM)
endif()
if(SDLIMAGE_SUPPORT_PCX)
	add_definitions(-DLOAD_PCX)
endif()
if(SDLIMAGE_SUPPORT_PNM)
	add_definitions(-DLOAD_PNM)
endif()
if(SDLIMAGE_SUPPORT_TGA)
	add_definitions(-DLOAD_TGA)
endif()
if(SDLIMAGE_SUPPORT_XPM)
	add_definitions(-DLOAD_XPM)
endif()
if(SDLIMAGE_SUPPORT_XV)
	add_definitions(-DLOAD_XV)
endif()

if(SDLIMAGE_SUPPORT_JPEG)
	add_subdirectory(external/jpeg-9)
	include_directories(external/jpeg-9)
	add_definitions(-DLOAD_JPG)
	add_definitions(-DLOAD_JPG_DYNAMIC="libjpeg-9.dll")
endif()

if(SDLIMAGE_SUPPORT_PNG)
	set(PNG_SHARED ON)
	add_subdirectory(external/libpng-1.6.2)
	include_directories(external/libpng-1.6.2)
	add_definitions(-DLOAD_PNG)
	add_definitions(-DLOAD_PNG_DYNAMIC="libpng16.dll")
	add_definitions(-DPNG_USE_DLL)
	add_definitions(-DZLIB_DLL)

	set_target_properties("${PNG_LIB_TARGETS}"
	    PROPERTIES
	    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)
	set_target_properties(zlib
	    PROPERTIES
	    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)
endif()

if(SDLIMAGE_SUPPORT_TIFF)
	add_subdirectory(external/tiff-4.0.3)
	include_directories(external/tiff-4.0.3/libtiff)
	include_directories("${CMAKE_BINARY_DIR}/external/tiff-4.0.3/libtiff")
	include_directories("${CMAKE_CURRENT_BINARY_DIR}/external/tiff-4.0.3/libtiff")
	add_definitions(-DLOAD_TIF)
	add_definitions(-DLOAD_TIF_DYNAMIC="libtiff-5.dll")
endif()

if(SDLIMAGE_SUPPORT_WEBP)
	add_subdirectory(external/libwebp-0.3.0)
	include_directories(external/libwebp-0.3.0/src)
	add_definitions(-DLOAD_WEBP)
	add_definitions(-DLOAD_WEBP_DYNAMIC="libwebp-4.dll")
endif()

set(SDLIMAGE_SRC
	IMG.c
	IMG_bmp.c
	IMG_gif.c
	IMG_jpg.c
	IMG_lbm.c
	IMG_pcx.c
	IMG_png.c
	IMG_pnm.c
	IMG_tga.c
	IMG_tif.c
	IMG_webp.c
	IMG_xcf.c
	IMG_xpm.c
	IMG_xv.c
	IMG_xxx.c
	showimage.c
)

set(SDLIMAGE_SOURCES
	${SDLIMAGE_SRC}
)

include_directories(./)

add_library(SDLIMAGE SHARED
	${SDLIMAGE_SOURCES}
)

set_target_properties(SDLIMAGE
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries (SDLIMAGE
	${SDL_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(SDLIMAGE PROPERTIES
	PREFIX ""
	OUTPUT_NAME "SDL_image"
)
