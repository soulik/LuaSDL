cmake_minimum_required (VERSION 3.1.0)
project (WEBP)

include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)

set(WEBP_DEC_SRC
	src/dec/alpha.c
	src/dec/buffer.c
	src/dec/frame.c
	src/dec/idec.c
	src/dec/io.c
	src/dec/layer.c
	src/dec/quant.c
	src/dec/tree.c
	src/dec/vp8.c
	src/dec/vp8l.c
	src/dec/webp.c
)

set(WEBP_DEMUX_SRC demux.c)

set(WEBP_DSP_SRC
	src/dsp/cpu.c
	src/dsp/dec.c             
	src/dsp/dec_neon.c        
	src/dsp/dec_sse2.c        
	src/dsp/enc.c             
	src/dsp/enc_neon.c        
	src/dsp/enc_sse2.c        
	src/dsp/lossless.c        
	src/dsp/upsampling.c      
	src/dsp/upsampling_neon.c 
	src/dsp/upsampling_sse2.c 
	src/dsp/yuv.c             
)
set(WEBP_ENC_SRC
	src/enc/alpha.c              
	src/enc/analysis.c           
	src/enc/backward_references.c
	src/enc/config.c             
	src/enc/cost.c               
	src/enc/filter.c             
	src/enc/frame.c              
	src/enc/histogram.c          
	src/enc/iterator.c           
	src/enc/layer.c              
	src/enc/picture.c            
	src/enc/quant.c              
	src/enc/syntax.c             
	src/enc/token.c              
	src/enc/tree.c               
	src/enc/vp8l.c               
	src/enc/webpenc.c
)
set(WEBP_MUX_SRC
	src/mux/muxedit.c
	src/mux/muxinternal.c
	src/mux/muxread.c
)
set(WEBP_UTILS_SRC
	src/utils/bit_reader.c
	src/utils/bit_writer.c
	src/utils/color_cache.c
	src/utils/filters.c
	src/utils/huffman.c
	src/utils/huffman_encode.c
	src/utils/quant_levels.c
	src/utils/quant_levels_dec.c
	src/utils/rescaler.c
	src/utils/thread.c
	src/utils/utils.c
)

set(WEBP_DECODER_ONLY OFF CACHE BOOL "Compile with decoder only")
set(WEBP_MUX OFF CACHE BOOL "Compile with mux")
set(WEBP_DEMUX OFF CACHE BOOL "Compile with demux")

set(WEBP_SOURCES ${WEBP_DEC_SRC} ${WEBP_DSP_SRC} ${WEBP_UTILS_SRC})

if(WEBP_MUX)
	list(APPEND WEBP_SOURCES ${WEBP_MUX_SRC})
endif()

if(WEBP_DEMUX)
	list(APPEND WEBP_SOURCES ${WEBP_DEMUX_SRC})
endif()

if(NOT WEBP_DECODER_ONLY)
	list(APPEND WEBP_SOURCES ${WEBP_ENC_SRC})
endif()

if(WIN32)
	list(APPEND WEBP_SOURCES src/webp_dll.c)
endif()

include_directories(./)

add_library(WEBP SHARED
	${WEBP_SOURCES}
)

if(WIN32)
	set_property(TARGET WEBP APPEND_STRING PROPERTY
		COMPILE_FLAGS "/FI\"src/webp_dll.h\""
	)
endif()

set_target_properties(WEBP
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(WEBP
	PROPERTIES PREFIX "" OUTPUT_NAME "libwebp-4"
)
