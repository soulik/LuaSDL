set (TOLUAPP_BIN_SRC
#	bin/tolua.c
	bin/toluabind.c
#	bin/toluabind_default.c
)

set (TOLUAPP_LIB_SRC
	lib/tolua_event.c
	lib/tolua_is.c
	lib/tolua_map.c
	lib/tolua_push.c
	lib/tolua_to.c
)

set(TOLUAPP_SOURCES
	${TOLUAPP_BIN_SRC} ${TOLUAPP_LIB_SRC}
)


add_definitions(-DLUA_BUILD_AS_DLL)
add_definitions(-DLUA_LIB)

include_directories(./)

# ------------------- ADDITIONAL LIBRARIES ----------------------

set(TOLUAPP_LIBRARIES
	${LUA_LIBRARIES}
)

# -------------------------- SDL ----------------------------

add_library(TOLUAPP SHARED
	${TOLUAPP_SOURCES}
)

set_target_properties(TOLUAPP
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries (TOLUAPP
	${TOLUAPP_LIBRARIES}
)
