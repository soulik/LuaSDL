set(luasdl_src
	DejaVu-Sans-Mono-13.c
	sdllib.c	
)

set(luasdl_binding_src
	binding/SDL.c
)

set(luasdl_sources
	${luasdl_src} ${luasdl_autogen_src} ${luasdl_binding_src}
)

include_directories(./)

set(luasdl_version_script luasdl.version)

IF(UNIX)
    IF(CMAKE_COMPILER_IS_GNUCC)
         SET(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY}hidden -Wl,--version-script=${luasdl_version_script}")
    ENDIF(CMAKE_COMPILER_IS_GNUCC)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
ENDIF(UNIX)

add_definitions(-DLUA_BUILD_AS_DLL)
add_definitions(-DLUA_LIB)

add_library(luasdl SHARED
	${luasdl_sources}
)

target_link_libraries (luasdl
	${LUA_LIBRARIES}
	${luasdl_libraries}
)

set_target_properties(luasdl
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	PREFIX ""
	OUTPUT_NAME "LuaSDL"
)

