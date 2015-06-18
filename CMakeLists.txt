cmake_minimum_required (VERSION 3.1.0)
project (luasdl)

list(APPEND CMAKE_MODULE_PATH "${luasdl_SOURCE_DIR}/cmake")

set(luasdl_libraries "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
# set(CMAKE_BINARY_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin")

# libSDL

set(luasdl_USE_INTERNAL_SDL ON CACHE BOOL "Build and use internal copy of libSDL")

if(luasdl_USE_INTERNAL_SDL)
	set(SDL_SHARED ON CACHE BOOL "libSDL shared library")
	set(SDL_STATIC OFF CACHE BOOL "libSDL static library")

	add_subdirectory(dependencies/libSDL)

	set(SDL_DYNAMIC_LIBRARY_DIRECTORIES )

	set(SDL_LIBRARY $<TARGET_LINKER_FILE:SDL>)

	set(SDL_INCLUDE_DIR
		${CMAKE_CURRENT_BINARY_DIR}/dependencies/libSDL/include
		dependencies/libSDL/include
	)

	include_directories( ${SDL_INCLUDE_DIR})
	list(APPEND luasdl_libraries ${SDL_LIBRARY})
else()
	find_package(SDL REQUIRED)

	include_directories( ${SDL_INCLUDE_DIR})
	list(APPEND luasdl_libraries ${SDL_LIBRARY})
endif()

# SDL_image

set(PNG_STATIC OFF CACHE BOOL "")
set(PNG_TESTS OFF CACHE BOOL "")
# set(SDLIMAGE_INCLUDE_DIR "" CACHE PATH "libSDL_image include directory")
# set(SDLIMAGE_LIBRARY "" CACHE FILEPATH "libSDL_image library")
add_subdirectory(dependencies/sdl_image)
include_directories(dependencies/sdl_image)
list(APPEND luasdl_libraries SDLIMAGE)

# SDL_mixer

# set(SDLMIXER_INCLUDE_DIR "" CACHE PATH "libSDL_mixer include directory")
# set(SDLMIXER_LIBRARY "" CACHE FILEPATH "libSDL_mixer library")
add_subdirectory(dependencies/sdl_mixer)
include_directories(dependencies/sdl_mixer)
list(APPEND luasdl_libraries SDLMIXER)

# SDL_ttf

# set(SDLTTF_INCLUDE_DIR "" CACHE PATH "libSDL_ttf include directory")
# set(SDLTTF_LIBRARY "" CACHE FILEPATH "libSDL_ttf library")
add_subdirectory(dependencies/sdl_ttf)
include_directories(dependencies/sdl_ttf)
list(APPEND luasdl_libraries SDLTTF)

# SDL_net

# set(SDLNET_INCLUDE_DIR "" CACHE PATH "libSDL_net include directory")
# set(SDLNET_LIBRARY "" CACHE FILEPATH "libSDL_net library")
add_subdirectory(dependencies/sdl_net)
include_directories(dependencies/sdl_net)
list(APPEND luasdl_libraries SDLNET)

# SDL_gfx

# set(SDLGFX_INCLUDE_DIR "" CACHE PATH "libSDL_gfx include directory")
# set(SDLGFX_LIBRARY "" CACHE FILEPATH "libSDL_gfx library")
add_subdirectory(dependencies/sdl_gfx)
include_directories(dependencies/sdl_gfx)
include_directories(${CMAKE_BINARY_DIR}/dependencies/sdl_gfx)
include_directories(${SDLGFX_INCLUDE_DIR})
list(APPEND luasdl_libraries SDLGFX)

# tolua++

add_subdirectory(dependencies/tolua++-1.0.93)
include_directories(dependencies/tolua++-1.0.93)
include_directories(dependencies/tolua++-1.0.93/include)
list(APPEND luasdl_libraries TOLUAPP)

# Include Lua 5.1

include(FindLua51)
include_directories(
	${LUA_INCLUDE_DIR}
	${LUA_INCLUDE_DIR}/lua5.1
)

include_directories(dependencies/lua/include)

add_subdirectory(src)
