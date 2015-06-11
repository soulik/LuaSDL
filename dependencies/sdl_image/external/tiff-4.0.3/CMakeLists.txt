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

include( ${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake )
include( ${CMAKE_ROOT}/Modules/TestBigEndian.cmake )
check_include_file( fcntl.h HAVE_FCNTL_H )

if( HAVE_FCNTL_H )
	add_definitions(-DHAVE_FCNTL_H=1)
endif()

if (HAVE_STDDEF_H)
	add_definitions(-DHAVE_STDDEF_H=1)
endif()

TEST_BIG_ENDIAN(HOST_BIGENDIAN)

set(TIFF_INT8_T int8_t)
set(TIFF_UINT8_T uint8_t)
set(TIFF_INT16_T int16_t)
set(TIFF_UINT16_T uint16_t)
set(TIFF_INT32_T int32_t)
set(TIFF_UINT32_T uint32_t)
set(TIFF_INT64_T int64_t)
set(TIFF_UINT64_T uint64_t)
set(TIFF_SSIZE_T ssize_t)

set(TIFF_INT8 int8_t)
set(TIFF_UINT8 uint8_t)
set(TIFF_INT16 int16_t)
set(TIFF_UINT16 uint16_t)
set(TIFF_INT32 int32_t)
set(TIFF_UINT32 uint32_t)
set(TIFF_INT64 int64_t)
set(TIFF_UINT64 uint64_t)
set(TIFF_SSIZE ssize_t)

if(UINT64_FORMAT)
	set(TIFF_UINT64_FORMAT UINT64_FORMAT)
else()
	set(TIFF_UINT64_FORMAT \"%I64u\")
endif()

if(SSIZE_FORMAT)
	set(TIFF_SSIZE_FORMAT SSIZE_FORMAT)
else()
	set(TIFF_SSIZE_FORMAT \"%ld\")
endif()

if(HOST_BIGENDIAN)
	set(HOST_FILLORDER FILLORDER_MSB2LSB)
else()
	set(HOST_FILLORDER FILLORDER_LSB2MSB)
endif()

if(WIN32)
	list(APPEND TIFF_SRC libtiff/tif_win32.c)
	configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tiffconf.vc.h ${CMAKE_CURRENT_BINARY_DIR}/libtiff/tiffconf.h @ONLY)
	configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_config.vc.h ${CMAKE_CURRENT_BINARY_DIR}/libtiff/tif_config.h @ONLY)
	configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/libtiff/libtiff.def ${CMAKE_CURRENT_BINARY_DIR}/libtiff/libtiff.def @ONLY)
else()
	configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tiffconf.h.in ${CMAKE_CURRENT_BINARY_DIR}/libtiff/tiffconf.h @ONLY)
	configure_file(	${CMAKE_CURRENT_SOURCE_DIR}/libtiff/tif_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/libtiff/tif_config.h @ONLY)
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
	PROPERTIES
	OUTPUT_NAME "libtiff-5"
)

if (WIN32)
	set_target_properties(TIFF
		PROPERTIES
		PREFIX ""
	)
endif()
