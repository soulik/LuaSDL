cmake_minimum_required (VERSION 3.1.0)
project (TIFF)

include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)

set(TIFF_SRC
	libtiff/tif_aux.c
	libtiff/tif_close.c
	libtiff/tif_codec.c
	libtiff/tif_color.c
	libtiff/tif_compress.c
	libtiff/tif_dir.c
	libtiff/tif_dirinfo.c
	libtiff/tif_dirread.c
	libtiff/tif_dirwrite.c
	libtiff/tif_dumpmode.c
	libtiff/tif_error.c
	libtiff/tif_extension.c
	libtiff/tif_fax3.c
	libtiff/tif_fax3sm.c
	libtiff/tif_flush.c
	libtiff/tif_getimage.c
	libtiff/tif_jbig.c
	libtiff/tif_jpeg.c
	libtiff/tif_jpeg_12.c
	libtiff/tif_luv.c
	libtiff/tif_lzma.c
	libtiff/tif_lzw.c
	libtiff/tif_next.c
	libtiff/tif_ojpeg.c
	libtiff/tif_open.c
	libtiff/tif_packbits.c
	libtiff/tif_pixarlog.c
	libtiff/tif_predict.c
	libtiff/tif_print.c
	libtiff/tif_read.c
	libtiff/tif_strip.c
	libtiff/tif_swab.c
	libtiff/tif_thunder.c
	libtiff/tif_tile.c
	libtiff/tif_version.c
	libtiff/tif_warning.c
	libtiff/tif_write.c
	libtiff/tif_zip.c
)

if(WIN32)
	list(APPEND TIFF_SRC libtiff/tif_win32.c)
	configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tiffconf.vc.h ${CMAKE_CURRENT_BINARY_DIR}/libtiff/tiffconf.h @ONLY)
	configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_config.vc.h ${CMAKE_CURRENT_BINARY_DIR}/libtiff/tif_config.h @ONLY)
	configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/libtiff/libtiff.def ${CMAKE_CURRENT_BINARY_DIR}/libtiff/libtiff.def @ONLY)
endif()

set(TIFF_SOURCES
	${TIFF_SRC}
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/libtiff")

add_library(TIFF SHARED
	${TIFF_SOURCES}
)

set_target_properties(TIFF
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(WIN32)
	if(MSVC)
		set_target_properties(TIFF PROPERTIES LINK_FLAGS "/DEF:libtiff/libtiff.def")
	endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(TIFF
	PROPERTIES PREFIX "" OUTPUT_NAME "libtiff-5"
)
