cmake_minimum_required (VERSION 3.1.0)
project (JPEG)

include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)

set(JPEG_SRC
	jaricom.c jcapimin.c jcapistd.c jcarith.c jccoefct.c jccolor.c
	jcdctmgr.c jchuff.c jcinit.c jcmainct.c jcmarker.c jcmaster.c
	jcomapi.c jcparam.c jcprepct.c jcsample.c jctrans.c jdapimin.c
	jdapistd.c jdarith.c jdatadst.c jdatasrc.c jdcoefct.c jdcolor.c
	jddctmgr.c jdhuff.c jdinput.c jdmainct.c jdmarker.c jdmaster.c
	jdmerge.c jdpostct.c jdsample.c jdtrans.c jerror.c jfdctflt.c
	jfdctfst.c jfdctint.c jidctflt.c jidctfst.c jidctint.c jquant1.c
	jquant2.c jutils.c jmemmgr.c
)

if(WIN32)
	set(JPEG_PLATFORM_SRC jmemnobs.c)
elseif(UNIX AND NOT APPLE)
	set(JPEG_PLATFORM_SRC jmemansi.c)
elseif(APPLE)
	set(JPEG_PLATFORM_SRC jmemmac.c)
else()
	set(JPEG_PLATFORM_SRC jmemname.c)
endif()

set(JPEG_SOURCES
	${JPEG_SRC} ${JPEG_PLATFORM_SRC}
)

include_directories(./)

add_library(JPEG SHARED
	${JPEG_SOURCES}
)

set_target_properties(JPEG
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(JPEG
	PROPERTIES PREFIX "" OUTPUT_NAME "libjpeg-9"
)
