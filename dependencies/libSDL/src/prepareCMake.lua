#!/usr/bin/lua

local templates = {
	subsystem = [[
# -------------------- {{SUBSYSTEM}} -----------------------

set(SDL_{{SUBSYSTEM}}_DISABLED OFF CACHE BOOL "Disable support for {{SUBSYSTEM_DESC}} support")
set(SDL_{{SUBSYSTEM}}_SRC "")

if(not SDL_{{SUBSYSTEM}}_DISABLED)
{{SUBSYSTEM_PLATFORMS}}
endif()

]],
	subsystemPlatforms = [[
{{PLATFORM_GENERIC}}
	if(WIN32)
{{PLATFORM_WIN32}}
	elseif(UNIX and not APPLE)
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
			if (PACKAGE_NAME_DEF)
				list(APPEND SDL_{{SUBSYSTEM}}_SRC
{{FILES}}
				)
			endif()
	]],
	
	subsystemDriver = [[
{{PACKAGES}}
		set(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}} ON CACHE BOOL "Enable support for {{SUBSYSTEM_DRIVER_DESC}} {{subsystem_desc}} driver")
		if(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}})
{{DRIVER_FILES}}
		endif()
]],
	subsystemDriverDynamic = [[
{{PACKAGES}}
		set(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}} ON CACHE BOOL "Enable support for {{SUBSYSTEM_DRIVER_DESC}} {{subsystem_desc}} driver")
		set(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}}_DYNAMIC ON CACHE BOOL "Enable support for {{SUBSYSTEM_DRIVER_DESC}} {{subsystem_desc}} dynamic driver")

		if(SDL_{{SUBSYSTEM}}_DRIVER_{{SUBSYSTEM_DRIVER}})
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
					packages = {'ALSA'},
				},
				['esd'] = {
					desc = 'Enlightement Sound Daemon',
					dynamic = true,
					packages = {'ESD'},
				},
				['pulse'] = {
					desc = 'PulseAudio',
					dynamic = true,
					packages = {'pulseaudio'},
				},
				['arts'] = {
					desc = 'ARTS',
					dynamic = true,
					packages = {'artsc'},
				},
				['nas'] = {
					desc = 'NAS',
					dynamic = true,
					packages = {'NASaudio'},
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
					packages = {'Threads'},
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
					desc = 'AAlib',
					packages = {'aa'},
				},
				['caca'] = {
					desc = 'CACAlib',
					packages = {'caca'},
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
					packages = {'SVGAlib'},
				},
				['vgl'] = {
					desc = 'VGL',
					packages = {'VGL'},
				},
				['directfb'] = {
					desc = 'DirectFB',
					packages = {'DirectFB'},
				},
				['fbcon'] = {
					desc = 'FrameBuffer Console',
					packages = {'FBcon'},
				},
				['nanox'] = {
					desc = 'NanoX',
					packages = {'NanoX'},
				},
				['x11'] = {
					desc = 'X11',
					packages = {'X11'},
				},
				['Xext'] = {
					desc = 'X11 Xext',
					packages = {'X11'},
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

local function prepareDriver(driver, vars)
	local output = {}
	vars['SUBSYSTEM_DRIVER_DESC'] = driver.desc
	vars['FILES'] = ""

	if type(driver.packages)=='table' then
		local packages = {}

		for _, package in ipairs(driver.packages) do
			vars['PACKAGE_NAME'] = package
			vars['PACKAGE_NAME_DEP'] = (package):upper()
			table.insert(packages, applyTemplate(templates.package, vars))
		end
		vars['PACKAGES'] = table.concat(packages)
		vars['DRIVER_FILES'] = applyTemplate(templates.subsystemDriverFiles, vars)
	else
		vars['PACKAGES'] = ''
		vars['DRIVER_FILES'] = applyTemplate(templates.subsystemDriverFilesWithDep, vars)
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
		vars['DRIVER_FILES'] = ''
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
	vars['subsystem_desc'] = (subsystem.desc):lower()

	vars['SUBSYSTEM_PLATFORMS'] = preparePlatforms(subsystem.platforms, vars)
	return applyTemplate(templates.subsystem, vars)
end

local function prepareSubsystems()
	local output = {}
	for name, subsystem in pairs(subsystems) do
		local vars = {
			SUBSYSTEM = (name):upper(),
			subsystem = name,
		}
		table.insert(output, prepareSubsystem(subsystem, vars))
	end
	return table.concat(output)
end

print(prepareSubsystems())

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
