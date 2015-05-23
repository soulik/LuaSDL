cmake_minimum_required (VERSION 3.1.0)
project (TOLUAPP)

set(CMAKE_MODULE_PATH "${SDLIMAGE_SOURCE_DIR}/cmake")
# include(${TOLUAPP_SOURCE_DIR}/cmake/testOS.cmake)

# Include Lua 5.1

include(FindLua51)
include_directories(${LUA_INCLUDE_DIR})
include_directories(dependencies/lua/include)

include_directories(include)

add_subdirectory(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
set_target_properties(TOLUAPP PROPERTIES
	PREFIX ""
	OUTPUT_NAME "tolua++5.1"
)
