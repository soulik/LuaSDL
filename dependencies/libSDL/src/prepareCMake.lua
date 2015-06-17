#!/usr/bin/lua

require 'lfs'

local function fileMask(name)
	if name:match('%.c$') or name:match('%.cpp$') or name:match('%.cc$') or name:match('%.h$') or name:match('%.hpp$') or name:match('%.m$') or name:match('%.mm$') then
		return true
	else
		return false
	end
end

local function getFiles(path, state)
	local state = state or {}
	if not path:match('/$') then
		path = path..'/'
	end
	for item in lfs.dir(path) do
		local fullPath = path..item
		if fullPath:match('^%./') then
			fullPath = fullPath:sub(3)
		end
		local attr = lfs.attributes(fullPath)
	
		if not (item == '.' or item == '..') then
			if attr.mode == 'file' then
				if fileMask(item) then
					table.insert(state, fullPath)
				end
			elseif attr.mode == 'directory' then
				getFiles('./'..fullPath..'/', state)
			end
		end
	end
	return state
end

local function getFilesNR(path)
	local state = {}
	if not path:match('/$') then
		path = path..'/'
	end
	for item in lfs.dir(path) do
		local fullPath = path..item
		if fullPath:match('^%./') then
			fullPath = fullPath:sub(3)
		end
		local attr = lfs.attributes(fullPath)
	
		if not (item == '.' or item == '..') then
			if attr.mode == 'file' then
				if fileMask(item) then
					table.insert(state, fullPath)
				end
			end
		end
	end
	return state
end

local templates = {
    main = [[
include (CheckIncludeFiles)
include(TestBigEndian)
TEST_BIG_ENDIAN(BIGENDIAN)

if(BIGENDIAN)
	set(SDL_BYTEORDER 4321)
else()
	set(SDL_BYTEORDER 1234)
endif()

set(SDL_LIBRARIES "")
set(DIRECTX_LIBRARIES
	winmm.lib
	dxguid.lib
)

{{PROJECT_FILES}}

set(SDL_MAIN_SRC
    main/dummy/SDL_dummy_main.c
)

if (WIN32)
	list(APPEND SDL_MAIN_SRC
	    main/win32/SDL_win32_main.c
	)
elseif (APPLE)
	if (DARWIN)
	elseif (MACOSX)
		list(APPEND SDL_MAIN_SRC
			main/macosx/SDLMain.m
		)
	else()
		list(APPEND SDL_MAIN_SRC
		    main/macos/SDL_main.c
		)
	endif()
endif()

set(SDL_SRC
    SDL.c
    SDL_error.c
    SDL_fatal.c
)

set(SDL_STDLIB_SRC
    stdlib/SDL_getenv.c
    stdlib/SDL_iconv.c
    stdlib/SDL_malloc.c
    stdlib/SDL_qsort.c
    stdlib/SDL_stdlib.c
    stdlib/SDL_string.c
)

set(SDL_SOURCES
{{SOURCES}}
	${SDL_MAIN_SRC}
	${SDL_SRC}
	${SDL_STDLIB_SRC}
)

if (WIN32 AND (SDL_AUDIO_DRIVER_WINDX5 OR SDL_VIDEO_DRIVER_DDRAW))
	list(APPEND SDL_LIBRARIES
		${DIRECTX_LIBRARIES}
	)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/../include)

# -------------------------- CONFIG -----------------------------

if (NOT SDL_VIDEO_DISABLED)
	check_include_files(GL/gl.h;GL/glu.h HAVE_OPENGL_H)
	check_include_files(gl.h;glu.h HAVE_OPENGL_MAC_H)
	
	if (HAVE_OPENGL_H OR HAVE_OPENGL_MAC_H)
		set(SDL_VIDEO_OPENGL 1)
		if (WIN32)
			set(SDL_VIDEO_OPENGL_WGL 1)
		elseif (UNIX)
			set(SDL_VIDEO_OPENGL_GLX 1)
		endif()
	endif()
endif()

check_include_files(X11/extensions/XShm.h USE_SHARED_MEMORY)
if (NOT USE_SHARED_MEMORY)
	set(NO_SHARED_MEMORY 1)
	add_definitions(-DNO_SHARED_MEMORY=1)
endif()


if ((${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64|x86"))
	set(SDL_ASSEMBLY_ROUTINES 1)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../include/SDL_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/../include/SDL_config.h @ONLY)

# ----------------------- libSDL LIBRARY ------------------------

add_library(SDL SHARED
	${SDL_SOURCES}
)

set_target_properties(SDL
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries (SDL
	${SDL_LIBRARIES}
)

    ]],
    additionalLibraries = [[
				list(APPEND SDL_LIBRARIES
					{{LIBRARIES}}
				)
				{{INCLUDES}}

]],
	subsystem = [[
# -------------------- {{SUBSYSTEM}} -----------------------

set(SDL_{{SUBSYSTEM}}_DISABLED OFF CACHE BOOL "Disable support for {{SUBSYSTEM_DESC}} support")
set(SDL_{{SUBSYSTEM}}_SRC "")

if(NOT SDL_{{SUBSYSTEM}}_DISABLED)

{{COMMON_FILES}}

{{SUBSYSTEM_PLATFORMS}}
endif()

source_group("{{SUBSYSTEM_DESC}}" FILES ${SDL_{{SUBSYSTEM}}_SRC})

]],
	subsystemPlatforms = [[
{{PLATFORM_GENERIC}}
	if(WIN32)
{{PLATFORM_WIN32}}
	elseif(UNIX AND NOT APPLE)
{{PLATFORM_LINUX}}
	else()
		if(MACOSX)
{{PLATFORM_MACOSX}}
		else()
{{PLATFORM_MACOS}}
		endif()
	endif()
]],
	subsystemDriverFiles = [[
				list(APPEND SDL_{{SUBSYSTEM}}_SRC
{{FILES}}
				)
	]],
	
	subsystemDriverFilesWithDep = [[
				if ({{PACKAGE_NAME_DEP}})
					list(APPEND SDL_{{SUBSYSTEM}}_SRC
{{FILES}}
					)
{{ADDITIONAL_LIBRARIES}}
				endif()
	]],

	subsystemDriverFilesWithDepSpecific = [[
				{{SPECIFIC_CODE}}

				if ({{PACKAGE_NAME_DEP}} AND {{SPECIFIC_DEP}})
					list(APPEND SDL_{{SUBSYSTEM}}_SRC
{{FILES}}
					)
{{ADDITIONAL_LIBRARIES}}
				endif()
	]],
	
	subsystemDriver = [[
{{PACKAGES}}
			set(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}} ON CACHE BOOL "Enable support for {{SUBSYSTEM_DRIVER_DESC}} {{subsystem_desc}} driver")
			if(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}})
				add_definitions(-DSDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}}=1)
{{DRIVER_FILES}}
			endif()
]],
	subsystemDriverDynamic = [[
{{PACKAGES}}
			set(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}} ON CACHE BOOL "Enable support for {{SUBSYSTEM_DRIVER_DESC}} {{subsystem_desc}} driver")
			set(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}}_DYNAMIC ON CACHE BOOL "Enable support for {{SUBSYSTEM_DRIVER_DESC}} {{subsystem_desc}} dynamic driver")

			if(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}})
				add_definitions(-DSDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}}=1)
{{DRIVER_FILES}}
			endif()
]],

	subsystemGeneric = [[
{{PACKAGES}}
{{DRIVER_FILES}}
]],
	package = [[
		find_package({{PACKAGE_NAME}})
]],
}

local subsystems = {
	audio = {
		desc = 'Audio',
		platforms = {
			generic = {
				['dummy'] = {
					desc = 'Dummy'
				},
			},
			win32 = {
				['windib'] = {
					desc = 'Waveout',
				},
				['windx5'] = {
					desc = 'MS DirectX (DirectSound)'
				},
			},
			linux = {
				['alsa'] = {
					desc = 'ALSA',
					dynamic = true,
					packages = {
						['ALSA']={},
					},
				},
				['esd'] = {
					desc = 'Enlightement Sound Daemon',
					dynamic = true,
					packages = {
						['ESD']={},
					},
				},
				['pulse'] = {
					desc = 'PulseAudio',
					dynamic = true,
					packages = {
						['pulseaudio']={},
					},
				},
				['arts'] = {
					desc = 'ARTS',
					dynamic = true,
					packages = {
						['artsc']={},
					},
				},
				['nas'] = {
					desc = 'NAS',
					dynamic = true,
					packages = {
						['NASaudio']={},
					},
				},
				['dsp'] = {
					desc = 'DSP'
				},
			},
			macos = {
				['macrom'] = {
					desc = 'MacOS Sound System'
				}
			},
			macosx = {
				['macosx'] = {
					desc = 'MacOS X Sound System'
				}
			},
		},
	},
	cdrom = {
		desc = 'CD-ROM',
		platforms = {
			generic = {
				['dummy'] = {
					desc = 'Dummy'
				},
			},
			win32 = {
				['win32'] = {
					desc = 'Windows'
				},
			},
			linux = {
				['linux'] = {
					desc = 'Linux'
				},
			},
			macos = {
				['macos'] = {
					desc = 'MacOS'
				},
			},
			macosx = {
				['macosx'] = {
					desc = 'MacOS X'
				},
			},
		},
	},
	cpuinfo = {
		desc = 'CPU info',
		platforms = {
			generic = {},
			win32 = {},
			linux = {},
			macos = {},
			macosx = {},
			all = true,
		},
	},
	events = {
		desc = 'Events',
		platforms = {
			generic = {},
			win32 = {},
			linux = {},
			macos = {},
			macosx = {},
			all = true,
		},
	},
	file = {
		desc = 'File management',
		platforms = {
			generic = {},
			win32 = {},
			linux = {},
			macos = {},
			macosx = {},
			all = true,
		},
	},
	joystick = {
		desc = 'Joystick',
		platforms = {
			generic = {
				['dummy'] = {
					desc = 'Dummy',
				},
			},
			win32 = {
				['win32'] = {
					desc = 'Win32 Multimedia',
				},
			},
			linux = {
				['linux'] = {
					desc = 'Linux',
				},
			},
			macos = {
				['macos'] = {
					desc = 'MacOS',
				},
			},
			macosx = {
				['darwin'] = {
					desc = 'MacOS X',
				},
			},
		},
	},
	loadso = {
		desc = 'Dynamic library loading',
		platforms = {
			generic = {
				['dummy'] = {
					desc = 'Dummy',
				},
			},
			win32 = {
				['win32'] = {
					desc = 'Windows DLL',
				},
			},
			linux = {
				['dlopen'] = {
					desc = 'Unix dlopen',
				},
			},
			macos = {
				['macos'] = {
					desc = 'MacOS',
				},
			},
			macosx = {
				['macosx'] = {
					desc = 'MacOS X',
				},
			},
		},
	},
	threads = {
		dir = 'thread',
		desc = 'Threads',
		platforms = {
			generic = {},
			win32 = {
				['win32'] = {
					desc = 'Windows Threads',
				},
			},
			linux = {
				['generic'] = {
					desc = 'Generic Threads',
				},
				['pthread'] = {
					desc = 'pthread',
					packages = {
						['Threads'] = {
							libraries = 'CMAKE_THREAD_LIBS_INIT',
							includes = false,
						}
					},
				},
			},
			macos = {},
			macosx = {},
		},
	},
	timers = {
		dir = 'timer',
		desc = 'Timers',
		platforms = {
			generic = {
				['dummy'] = {
					desc = 'Dummy',
				},
			},
			win32 = {
				['win32'] = {
					desc = 'Windows Timers',
				},
			},
			linux = {
				['unix'] = {
					desc = 'Unix',
				},
			},
			macos = {
				['macos'] = {
					desc = 'MacOS',
				},
			},
			macosx = {},
		},
	},
	video = {
		desc = 'Video',
		platforms = {
			generic = {
				['dummy'] = {
					desc = 'Dummy'
				},
				['aalib'] = {
					desc = 'ASCII Art library',
					packages = {
						['AAlib']={}
					},
				},
				['caca'] = {
					desc = 'Color ASCII Art library',
					packages = {
						['CACAlib']={}
					},
				},
			},
			win32 = {
				['wincommon'] = {
					desc = 'Windows common'
				},
				['windib'] = {
					desc = 'Windows DIB'
				},
				['windx5'] = {
					desc = 'Windows DirectX'
				},
			},
			linux = {
				['svga'] = {
					desc = 'SVGAlib',
					packages = {
						['SVGAlib']={},
					},
				},
				['directfb'] = {
					desc = 'DirectFB',
					packages = {
						['DirectFB']={},
					},
				},
				['fbcon'] = {
					desc = 'FrameBuffer Console',
					packages = {
						['FBcon']={},
					},
				},
				['nanox'] = {
					desc = 'NanoX',
					packages = {
						['NanoX']={},
					},
				},
				['x11'] = {
					desc = 'X11',
					packages = {
						['X11']={},
					},
				},
			},
			macos = {
				['maccommon'] = {
					desc = 'MacOS common'
				},
				['macdsp'] = {
					desc = 'MacOS DSP'
				},
				['macrom'] = {
					desc = 'MacOS'
				},
			},
			macosx = {
				['maccommon'] = {
					desc = 'MacOS common'
				},
				['quartz'] = {
					desc = 'Quartz'
				},
			},
		},
	},
}

local function applyTemplate(template, vars)
	return (template:gsub("{{([_%w%d]+)}}", vars))
end

local function processPackages(packages, vars)
	local output = {}
		
	for package, def in pairs(packages) do
		local def = def or {}
		vars['PACKAGE_NAME'] = package
		vars['PACKAGE_NAME_DEP'] = '${'..(def.found or package..'_FOUND')..'}'
		if type(def.libraries)=='boolean' and def.libraries == false then
			vars['LIBRARIES'] = ''
		else	
			vars['LIBRARIES'] = '${'..(def.libraries or package..'_LIBRARIES')..'}'
		end

		if type(def.includes)=='boolean' and def.includes == false then
			vars['INCLUDES'] = ''
		else
			vars['INCLUDES'] = 'include_directories( ${'..(def.includes or package..'_INCLUDES')..'})'
		end

		vars['ADDITIONAL_LIBRARIES'] = applyTemplate(templates.additionalLibraries, vars)
		table.insert(output, applyTemplate(templates.package, vars))
	end

	return table.concat(output)
end

local function prepareDriver(driver, vars)
	local output = {}
	vars['SUBSYSTEM_DRIVER_DESC'] = driver.desc
	vars['ADDITIONAL_LIBRARIES'] = ''

	local path = vars.subsystem_dir..'/'..vars.subsystem_driver
	local tabs = ("\t"):rep(6)
	vars['FILES'] = tabs..table.concat(getFiles(path), "\n"..tabs)
	vars['PACKAGE_NAME_DEP'] = ''

	if type(driver.packages)=='table' then
		vars['PACKAGES'] = processPackages(driver.packages, vars)

		if type(driver.conditions)=='table' then
			for name, code in pairs(driver.conditions) do
				vars['SPECIFIC_DEP'] = name
				vars['SPECIFIC_CODE'] = code
			end
			vars['DRIVER_FILES'] = applyTemplate(templates.subsystemDriverFilesWithDepSpecific, vars)
		else
			vars['DRIVER_FILES'] = applyTemplate(templates.subsystemDriverFilesWithDep, vars)
		end
	else
		vars['PACKAGES'] = ''
		vars['DRIVER_FILES'] = applyTemplate(templates.subsystemDriverFiles, vars)
	end

	if vars.PLATFORM == 'GENERIC' then
		table.insert(output, applyTemplate(templates.subsystemGeneric, vars))
	else
		if driver.dynamic then
			table.insert(output, applyTemplate(templates.subsystemDriverDynamic, vars))
		else
			table.insert(output, applyTemplate(templates.subsystemDriver, vars))
		end
	end
	return table.concat(output)
end

local function preparePlatform(platform, vars)
	local output = {}
	for name, driver in pairs(platform) do
		vars['SUBSYSTEM_DRIVER'] = (name):upper()
		vars['subsystem_driver'] = name
		table.insert(output, prepareDriver(driver, vars))
	end
	return table.concat(output)
end

local function preparePlatforms(platforms, vars)
	if platforms.all then
		vars['PACKAGES'] = ''
		
		local path = vars.subsystem_dir
		local tabs = ("\t"):rep(5)
		vars['FILES'] = tabs..table.concat(getFiles(path), "\n"..tabs)

		vars['DRIVER_FILES'] = applyTemplate(templates.subsystemDriverFiles, vars)

		return applyTemplate(templates.subsystemGeneric, vars)
	else
		for name, platform in pairs(platforms) do
			vars.PLATFORM = (name):upper()
			vars['PLATFORM_'..vars.PLATFORM] = preparePlatform(platform, vars)
		end
		return applyTemplate(templates.subsystemPlatforms, vars)
	end
end

local function prepareSubsystem(subsystem, vars)
	vars['SUBSYSTEM_DESC'] = subsystem.desc
	vars['subsystem_dir'] = subsystem.dir or vars.subsystem
	vars['subsystem_desc'] = (subsystem.desc):lower()

	vars['SUBSYSTEM_PLATFORMS'] = preparePlatforms(subsystem.platforms, vars)
	return applyTemplate(templates.subsystem, vars)
end

local function prepareSubsystems(vars)
	local output = {}
	for name, subsystem in pairs(subsystems) do
		vars['SUBSYSTEM'] = (name):upper()
		vars['subsystem'] = name
		local commonFiles = getFilesNR(subsystem.dir or name)
		if #commonFiles>0 then
			local tabs = ("\t"):rep(2)
			vars['COMMON_FILES'] = applyTemplate([[
	list(APPEND SDL_{{SUBSYSTEM}}_SRC
{{FILES}}	
	)
]], 
			{
				FILES = tabs..table.concat(commonFiles, "\n"..tabs),
				SUBSYSTEM = vars['SUBSYSTEM'],
			})
		else
			vars['COMMON_FILES'] = ''
		end
		table.insert(output, prepareSubsystem(subsystem, vars))
	end
	return table.concat(output)
end

local function prepareProject()
	local vars = {
	}
	vars['SOURCES'] = (function()
		local output = {}
		local tabs = ("\t"):rep(1)
		for name, subsystem in pairs(subsystems) do
			 table.insert(output, tabs..'${SDL_'..(name):upper().."_SRC}\n")
		end
		return table.concat(output)
	end)()
	vars['PROJECT_FILES'] = prepareSubsystems(vars)

	return applyTemplate(templates.main, vars)
end

print(prepareProject())

--[[
SDL_AUDIO_DISABLED 1
SDL_CDROM_DISABLED 1
SDL_CPUINFO_DISABLED 1
SDL_EVENTS_DISABLED 1
SDL_FILE_DISABLED 1
SDL_JOYSTICK_DISABLED 1
SDL_LOADSO_DISABLED 1
SDL_THREADS_DISABLED 1
SDL_TIMERS_DISABLED 1
SDL_VIDEO_DISABLED 1

SDL_AUDIO_DRIVER_ALSA 1
SDL_AUDIO_DRIVER_ALSA_DYNAMIC 1
SDL_AUDIO_DRIVER_ARTS 1
SDL_AUDIO_DRIVER_ARTS_DYNAMIC 1
SDL_AUDIO_DRIVER_BAUDIO 1
SDL_AUDIO_DRIVER_BSD 1
SDL_AUDIO_DRIVER_COREAUDIO 1
SDL_AUDIO_DRIVER_DART 1
SDL_AUDIO_DRIVER_DC 1
SDL_AUDIO_DRIVER_DISK 1
SDL_AUDIO_DRIVER_DUMMY 1
SDL_AUDIO_DRIVER_DMEDIA 1
SDL_AUDIO_DRIVER_DSOUND 1
SDL_AUDIO_DRIVER_PULSE 1
SDL_AUDIO_DRIVER_PULSE_DYNAMIC 1
SDL_AUDIO_DRIVER_ESD 1
SDL_AUDIO_DRIVER_ESD_DYNAMIC 1
SDL_AUDIO_DRIVER_MINT 1
SDL_AUDIO_DRIVER_MMEAUDIO 1
SDL_AUDIO_DRIVER_NAS 1
SDL_AUDIO_DRIVER_NAS_DYNAMIC 1
SDL_AUDIO_DRIVER_OSS 1
SDL_AUDIO_DRIVER_OSS_SOUNDCARD_H 1
SDL_AUDIO_DRIVER_PAUD 1
SDL_AUDIO_DRIVER_QNXNTO 1
SDL_AUDIO_DRIVER_SNDMGR 1
SDL_AUDIO_DRIVER_SUNAUDIO 1
SDL_AUDIO_DRIVER_WAVEOUT 1
SDL_CDROM_AIX 1
SDL_CDROM_BEOS 1
SDL_CDROM_BSDI 1
SDL_CDROM_DC 1
SDL_CDROM_DUMMY 1
SDL_CDROM_FREEBSD 1
SDL_CDROM_LINUX 1
SDL_CDROM_MACOS 1
SDL_CDROM_MACOSX 1
SDL_CDROM_MINT 1
SDL_CDROM_OPENBSD 1
SDL_CDROM_OS2 1
SDL_CDROM_OSF 1
SDL_CDROM_QNX 1
SDL_CDROM_WIN32 1
SDL_INPUT_LINUXEV 1
SDL_INPUT_TSLIB 1
SDL_JOYSTICK_BEOS 1
SDL_JOYSTICK_DC 1
SDL_JOYSTICK_DUMMY 1
SDL_JOYSTICK_IOKIT 1
SDL_JOYSTICK_LINUX 1
SDL_JOYSTICK_MACOS 1
SDL_JOYSTICK_MINT 1
SDL_JOYSTICK_OS2 1
SDL_JOYSTICK_RISCOS 1
SDL_JOYSTICK_WINMM 1
SDL_JOYSTICK_USBHID 1
SDL_JOYSTICK_USBHID_MACHINE_JOYSTICK_H 1
SDL_LOADSO_BEOS 1
SDL_LOADSO_DLCOMPAT 1
SDL_LOADSO_DLOPEN 1
SDL_LOADSO_DUMMY 1
SDL_LOADSO_LDG 1
SDL_LOADSO_MACOS 1
SDL_LOADSO_OS2 1
SDL_LOADSO_WIN32 1
SDL_THREAD_BEOS 1
SDL_THREAD_DC 1
SDL_THREAD_OS2 1
SDL_THREAD_PTH 1
SDL_THREAD_PTHREAD 1
SDL_THREAD_PTHREAD_RECURSIVE_MUTEX 1
SDL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP 1
SDL_THREAD_SPROC 1
SDL_THREAD_WIN32 1
SDL_TIMER_BEOS 1
SDL_TIMER_DC 1
SDL_TIMER_DUMMY 1
SDL_TIMER_MACOS 1
SDL_TIMER_MINT 1
SDL_TIMER_OS2 1
SDL_TIMER_RISCOS 1
SDL_TIMER_UNIX 1
SDL_TIMER_WIN32 1
SDL_TIMER_WINCE 1
SDL_VIDEO_DRIVER_AALIB 1
SDL_VIDEO_DRIVER_BWINDOW 1
SDL_VIDEO_DRIVER_CACA 1
SDL_VIDEO_DRIVER_DC 1
SDL_VIDEO_DRIVER_DDRAW 1
SDL_VIDEO_DRIVER_DGA 1
SDL_VIDEO_DRIVER_DIRECTFB 1
SDL_VIDEO_DRIVER_DRAWSPROCKET 1
SDL_VIDEO_DRIVER_DUMMY 1
SDL_VIDEO_DRIVER_FBCON 1
SDL_VIDEO_DRIVER_GAPI 1
SDL_VIDEO_DRIVER_GEM 1
SDL_VIDEO_DRIVER_GGI 1
SDL_VIDEO_DRIVER_IPOD 1
SDL_VIDEO_DRIVER_NANOX 1
SDL_VIDEO_DRIVER_OS2FS 1
SDL_VIDEO_DRIVER_PHOTON 1
SDL_VIDEO_DRIVER_PICOGUI 1
SDL_VIDEO_DRIVER_PS2GS 1
SDL_VIDEO_DRIVER_PS3 1
SDL_VIDEO_DRIVER_QTOPIA 1
SDL_VIDEO_DRIVER_QUARTZ 1
SDL_VIDEO_DRIVER_RISCOS 1
SDL_VIDEO_DRIVER_SVGALIB 1
SDL_VIDEO_DRIVER_TOOLBOX 1
SDL_VIDEO_DRIVER_VGL 1
SDL_VIDEO_DRIVER_WINDIB 1
SDL_VIDEO_DRIVER_WSCONS 1
SDL_VIDEO_DRIVER_X11 1
SDL_VIDEO_DRIVER_X11_DGAMOUSE 1
SDL_VIDEO_DRIVER_X11_DYNAMIC 1
SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT 1
SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR 1
SDL_VIDEO_DRIVER_X11_DYNAMIC_XRENDER 1
SDL_VIDEO_DRIVER_X11_VIDMODE 1
SDL_VIDEO_DRIVER_X11_XINERAMA 1
SDL_VIDEO_DRIVER_X11_XME 1
SDL_VIDEO_DRIVER_X11_XRANDR 1
SDL_VIDEO_DRIVER_X11_XV 1
SDL_VIDEO_DRIVER_XBIOS 1
SDL_VIDEO_OPENGL 1
SDL_VIDEO_OPENGL_GLX 1
SDL_VIDEO_OPENGL_WGL 1
SDL_VIDEO_OPENGL_OSMESA 1
SDL_VIDEO_OPENGL_OSMESA_DYNAMIC 1
--]]
