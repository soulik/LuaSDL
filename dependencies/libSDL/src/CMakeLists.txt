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
	dxguid.lib
)

# -------------------- JOYSTICK -----------------------

set(SDL_JOYSTICK_DISABLED OFF CACHE BOOL "Disable support for Joystick support")
set(SDL_JOYSTICK_SRC "")

if(NOT SDL_JOYSTICK_DISABLED)

	list(APPEND SDL_JOYSTICK_SRC
		joystick/SDL_sysjoystick.h
		joystick/SDL_joystick_c.h
		joystick/SDL_joystick.c	
	)
			#set(SDL_JOYSTICK_DUMMY 0)
			#
			#	list(APPEND SDL_JOYSTICK_SRC
			#			joystick/dummy/SDL_sysjoystick.c
			#	)

	if(WIN32)

			set(SDL_JOYSTICK_WIN32 ON CACHE BOOL "Enable support for Win32 Multimedia joystick driver")
			if(SDL_JOYSTICK_WIN32)
				list(APPEND SDL_JOYSTICK_SRC
						joystick/win32/SDL_mmjoystick.c
				)
	
			endif()

	elseif(UNIX AND NOT APPLE)

			set(SDL_JOYSTICK_LINUX ON CACHE BOOL "Enable support for Linux joystick driver")
			if(SDL_JOYSTICK_LINUX)
				list(APPEND SDL_JOYSTICK_SRC
						joystick/linux/SDL_sysjoystick.c
				)
	
			endif()

	else()
		if(MACOSX)

			set(SDL_JOYSTICK_DARWIN ON CACHE BOOL "Enable support for MacOS X joystick driver")
			if(SDL_JOYSTICK_DARWIN)
				list(APPEND SDL_JOYSTICK_SRC
						joystick/darwin/SDL_sysjoystick.c
				)
	
			endif()

		else()

			set(SDL_JOYSTICK_MACOS ON CACHE BOOL "Enable support for MacOS joystick driver")
			if(SDL_JOYSTICK_MACOS)
				list(APPEND SDL_JOYSTICK_SRC
						joystick/macos/SDL_sysjoystick.c
				)
	
			endif()

		endif()
	endif()

endif()

source_group("Joystick" FILES ${SDL_JOYSTICK_SRC})

# -------------------- TIMERS -----------------------

set(SDL_TIMERS_DISABLED OFF CACHE BOOL "Disable support for Timers support")
set(SDL_TIMERS_SRC "")

if(NOT SDL_TIMERS_DISABLED)

	list(APPEND SDL_TIMERS_SRC
		timer/SDL_systimer.h
		timer/SDL_timer.c
		timer/SDL_timer_c.h	
	)



	#		set(SDL_TIMER_DUMMY 1)
	#			list(APPEND SDL_TIMERS_SRC
	#					timer/dummy/SDL_systimer.c
	#			)
	

	if(WIN32)

			set(SDL_TIMER_WIN32 ON CACHE BOOL "Enable support for Windows Timers timers driver")
			if(SDL_TIMER_WIN32)
				list(APPEND SDL_TIMERS_SRC
						timer/win32/SDL_systimer.c
				)
	
			endif()

	elseif(UNIX AND NOT APPLE)

			set(SDL_TIMER_UNIX ON CACHE BOOL "Enable support for Unix timers driver")
			if(SDL_TIMER_UNIX)
				list(APPEND SDL_TIMERS_SRC
						timer/unix/SDL_systimer.c
				)
	
			endif()

	else()
		if(MACOSX)

		else()

			set(SDL_TIMER_MACOS ON CACHE BOOL "Enable support for MacOS timers driver")
			if(SDL_TIMER_MACOS)
				list(APPEND SDL_TIMERS_SRC
						timer/macos/SDL_MPWtimer.c
						timer/macos/FastTimes.h
						timer/macos/FastTimes.c
						timer/macos/SDL_systimer.c
				)
	
			endif()

		endif()
	endif()

endif()

source_group("Timers" FILES ${SDL_TIMERS_SRC})

# -------------------- AUDIO -----------------------

set(SDL_AUDIO_DISABLED OFF CACHE BOOL "Disable support for Audio support")
set(SDL_AUDIO_SRC "")

if(NOT SDL_AUDIO_DISABLED)
	list(APPEND SDL_AUDIO_SRC
		audio/SDL_mixer.c
		audio/SDL_sysaudio.h
		audio/SDL_audio_c.h
		audio/SDL_wave.h
		audio/SDL_mixer_MMX.h
		audio/SDL_mixer_MMX.c
		audio/SDL_mixer_m68k.h
		audio/SDL_audiomem.h
		audio/SDL_audiocvt.c
		audio/SDL_audiodev_c.h
		audio/SDL_audiodev.c
		audio/SDL_mixer_m68k.c
		audio/SDL_audio.c
		audio/SDL_wave.c
		audio/SDL_mixer_MMX_VC.h
		audio/SDL_mixer_MMX_VC.c	
	)


			set(SDL_AUDIO_DRIVER_DUMMY 1)
				list(APPEND SDL_AUDIO_SRC
						audio/dummy/SDL_dummyaudio.c
						audio/dummy/SDL_dummyaudio.h
				)
			set(SDL_AUDIO_DRIVER_DISK 1)
				list(APPEND SDL_AUDIO_SRC
						audio/disk/SDL_diskaudio.c
						audio/disk/SDL_diskaudio.h
				)
	if(WIN32)

			set(SDL_AUDIO_DRIVER_DSOUND ON CACHE BOOL "Enable support for MS DirectX (DirectSound) audio driver")
			if(SDL_AUDIO_DRIVER_DSOUND)
				list(APPEND SDL_AUDIO_SRC
						audio/windx5/directx.h
						audio/windx5/SDL_dx5audio.c
						audio/windx5/SDL_dx5audio.h
				)
	
			endif()

			set(SDL_AUDIO_DRIVER_WAVEOUT ON CACHE BOOL "Enable support for Waveout audio driver")
			if(SDL_AUDIO_DRIVER_WAVEOUT)
				list(APPEND SDL_AUDIO_SRC
						audio/windib/SDL_dibaudio.h
						audio/windib/SDL_dibaudio.c
				)
	
			endif()

	elseif(UNIX AND NOT APPLE)
		find_package(NASaudio)
			if (NASaudio_LIBRARY)
				set(SDL_AUDIO_DRIVER_NAS ON CACHE BOOL "Enable support for NAS audio driver")
			else()
				set(SDL_AUDIO_DRIVER_NAS OFF CACHE BOOL "Enable support for NAS audio driver")
			endif()
			set(SDL_AUDIO_DRIVER_NAS_DYNAMIC ${NASaudio_LIBRARY})

			if(SDL_AUDIO_DRIVER_NAS)
				if (${NASaudio_FOUND})
					list(APPEND SDL_AUDIO_SRC
						audio/nas/SDL_nasaudio.c
						audio/nas/SDL_nasaudio.h
					)
				list(APPEND SDL_LIBRARIES
					${NASaudio_LIBRARIES}
				)
				include_directories( ${NASaudio_INCLUDES})


				endif()
	
			endif()
		find_package(artsc)
			if (artsc_LIBRARY)
				set(SDL_AUDIO_DRIVER_ARTS ON CACHE BOOL "Enable support for ARTS audio driver")
			else()
				set(SDL_AUDIO_DRIVER_ARTS OFF CACHE BOOL "Enable support for ARTS audio driver")
			endif()
			set(SDL_AUDIO_DRIVER_ARTS_DYNAMIC ${artsc_LIBRARY})

			if(SDL_AUDIO_DRIVER_ARTS)
				if (${artsc_FOUND})
					list(APPEND SDL_AUDIO_SRC
						audio/arts/SDL_artsaudio.h
						audio/arts/SDL_artsaudio.c
					)
				list(APPEND SDL_LIBRARIES
					${artsc_LIBRARIES}
				)
				include_directories( ${artsc_INCLUDES})


				endif()
	
			endif()
		find_package(pulseaudio)

			if (pulseaudio_LIBRARY)
				set(SDL_AUDIO_DRIVER_PULSE ON CACHE BOOL "Enable support for PulseAudio audio driver")
			elseif()
				set(SDL_AUDIO_DRIVER_PULSE OFF CACHE BOOL "Enable support for PulseAudio audio driver")
			endif()
			set(SDL_AUDIO_DRIVER_PULSE_DYNAMIC ${pulseaudio_LIBRARY})

			if(SDL_AUDIO_DRIVER_PULSE)
				if (${pulseaudio_FOUND})
					list(APPEND SDL_AUDIO_SRC
						audio/pulse/SDL_pulseaudio.h
						audio/pulse/SDL_pulseaudio.c
					)
				list(APPEND SDL_LIBRARIES
					${pulseaudio_LIBRARIES}
				)
				include_directories( ${pulseaudio_INCLUDES})


				endif()
	
			endif()

			set(SDL_AUDIO_DRIVER_OSS 1)
			
			check_include_files(soundcard.h SDL_AUDIO_DRIVER_OSS_SOUNDCARD_H)

			list(APPEND SDL_AUDIO_SRC
					audio/dsp/SDL_dspaudio.c
					audio/dsp/SDL_dspaudio.h
			)

			list(APPEND SDL_AUDIO_SRC
					audio/dma/SDL_dmaaudio.c
					audio/dma/SDL_dmaaudio.h
			)
	
		find_package(ALSA)
			if (ALSA_LIBRARY)
				set(SDL_AUDIO_DRIVER_ALSA ON CACHE BOOL "Enable support for ALSA audio driver")
			elseif()
				set(SDL_AUDIO_DRIVER_ALSA OFF CACHE BOOL "Enable support for ALSA audio driver")
			endif()
			set(SDL_AUDIO_DRIVER_ALSA_DYNAMIC ${ALSA_LIBRARY})

			if(SDL_AUDIO_DRIVER_ALSA)
				if (${ALSA_FOUND})
					list(APPEND SDL_AUDIO_SRC
						audio/alsa/SDL_alsa_audio.h
						audio/alsa/SDL_alsa_audio.c
					)
				list(APPEND SDL_LIBRARIES
					${ALSA_LIBRARIES}
				)
				include_directories( ${ALSA_INCLUDES})


				endif()
	
			endif()
		find_package(ESD)
			if (ESD_LIBRARY)
				set(SDL_AUDIO_DRIVER_ESD ON CACHE BOOL "Enable support for Enlightement Sound Daemon audio driver")
			else()
				set(SDL_AUDIO_DRIVER_ESD OFF CACHE BOOL "Enable support for Enlightement Sound Daemon audio driver")
			endif()
			set(SDL_AUDIO_DRIVER_ESD_DYNAMIC ${ESD_LIBRARY})

			if(SDL_AUDIO_DRIVER_ESD)
				if (${ESD_FOUND})
					list(APPEND SDL_AUDIO_SRC
						audio/esd/SDL_esdaudio.c
						audio/esd/SDL_esdaudio.h
					)
				list(APPEND SDL_LIBRARIES
					${ESD_LIBRARIES}
				)
				include_directories( ${ESD_INCLUDES})


				endif()
	
			endif()

	else()
		if(MACOSX)

			set(SDL_AUDIO_DRIVER_MACOSX ON CACHE BOOL "Enable support for MacOS X Sound System audio driver")
			if(SDL_AUDIO_DRIVER_MACOSX)
				list(APPEND SDL_AUDIO_SRC
						audio/macosx/SDL_coreaudio.c
						audio/macosx/SDL_coreaudio.h
				)
	
			endif()

		else()

			set(SDL_AUDIO_DRIVER_MACROM ON CACHE BOOL "Enable support for MacOS Sound System audio driver")
			if(SDL_AUDIO_DRIVER_MACROM)
				list(APPEND SDL_AUDIO_SRC
						audio/macrom/SDL_romaudio.h
						audio/macrom/SDL_romaudio.c
				)
	
			endif()

		endif()
	endif()

endif()

source_group("Audio" FILES ${SDL_AUDIO_SRC})

# -------------------- CDROM -----------------------

set(SDL_CDROM_DISABLED OFF CACHE BOOL "Disable support for CD-ROM support")
set(SDL_CDROM_SRC "")

if(NOT SDL_CDROM_DISABLED)

	list(APPEND SDL_CDROM_SRC
		cdrom/SDL_cdrom.c
		cdrom/SDL_syscdrom.h	
	)



		#	set(SDL_CDROM_DUMMY 1)
		#		list(APPEND SDL_CDROM_SRC
		#				cdrom/dummy/SDL_syscdrom.c
		#		)
	

	if(WIN32)

			set(SDL_CDROM_WIN32 ON CACHE BOOL "Enable support for Windows cd-rom driver")
			if(SDL_CDROM_WIN32)
				list(APPEND SDL_CDROM_SRC
						cdrom/win32/SDL_syscdrom.c
				)
	
			endif()

	elseif(UNIX AND NOT APPLE)

			set(SDL_CDROM_LINUX ON CACHE BOOL "Enable support for Linux cd-rom driver")
			if(SDL_CDROM_LINUX)
				list(APPEND SDL_CDROM_SRC
						cdrom/linux/SDL_syscdrom.c
				)
	
			endif()

	else()
		if(MACOSX)

			set(SDL_CDROM_MACOSX ON CACHE BOOL "Enable support for MacOS X cd-rom driver")
			if(SDL_CDROM_MACOSX)
				list(APPEND SDL_CDROM_SRC
						cdrom/macosx/SDL_syscdrom.c
						cdrom/macosx/CDPlayer.h
						cdrom/macosx/SDL_syscdrom_c.h
						cdrom/macosx/SDLOSXCAGuard.h
						cdrom/macosx/AudioFileReaderThread.c
						cdrom/macosx/CDPlayer.c
						cdrom/macosx/AudioFilePlayer.c
						cdrom/macosx/SDLOSXCAGuard.c
						cdrom/macosx/AudioFilePlayer.h
				)
	
			endif()

		else()

			set(SDL_CDROM_MACOS ON CACHE BOOL "Enable support for MacOS cd-rom driver")
			if(SDL_CDROM_MACOS)
				list(APPEND SDL_CDROM_SRC
						cdrom/macos/SDL_syscdrom.c
						cdrom/macos/SDL_syscdrom_c.h
				)
	
			endif()

		endif()
	endif()

endif()

source_group("CD-ROM" FILES ${SDL_CDROM_SRC})

# -------------------- VIDEO -----------------------

set(SDL_VIDEO_DISABLED OFF CACHE BOOL "Disable support for Video support")
set(SDL_VIDEO_SRC "")

if(NOT SDL_VIDEO_DISABLED)

	list(APPEND SDL_VIDEO_SRC
		video/SDL_RLEaccel_c.h
		video/SDL_blit_0.c
		video/SDL_glfuncs.h
		video/SDL_yuv_mmx.c
		video/SDL_pixels.c
		video/SDL_bmp.c
		video/SDL_leaks.h
		video/SDL_yuv_sw_c.h
		video/SDL_blit_N.c
		video/SDL_gamma.c
		video/SDL_stretch_c.h
		video/SDL_video.c
		video/default_cursor.h
		video/e_log.h
		video/SDL_sysvideo.h
		video/e_sqrt.h
		video/SDL_surface.c
		video/e_pow.h
		video/SDL_blit.c
		video/SDL_blit_A.c
		video/mmx.h
		video/SDL_yuv.c
		video/SDL_stretch.c
		video/SDL_pixels_c.h
		video/SDL_yuv_sw.c
		video/SDL_yuvfuncs.h
		video/SDL_cursor_c.h
		video/math_private.h
		video/SDL_cursor.c
		video/SDL_blit.h
		video/SDL_blit_1.c
		video/SDL_RLEaccel.c
		video/blank_cursor.h	
	)



			set(SDL_VIDEO_DRIVER_DUMMY 1)
				list(APPEND SDL_VIDEO_SRC
						video/dummy/SDL_nullevents.c
						video/dummy/SDL_nullvideo.h
						video/dummy/SDL_nullvideo.c
						video/dummy/SDL_nullevents_c.h
						video/dummy/SDL_nullmouse_c.h
						video/dummy/SDL_nullmouse.c
				)
	
		find_package(AAlib QUIET)

				if (${AAlib_FOUND})
					set(SDL_VIDEO_DRIVER_AALIB ON CACHE BOOL "Enable support for Windows DirectX video driver")
					if (SDL_VIDEO_DRIVER_AALIB)
						list(APPEND SDL_VIDEO_SRC
							video/aalib/SDL_aaevents.c
							video/aalib/SDL_aavideo.c
							video/aalib/SDL_aamouse_c.h
							video/aalib/SDL_aaevents_c.h
							video/aalib/SDL_aavideo.h
							video/aalib/SDL_aamouse.c
						)
						list(APPEND SDL_LIBRARIES
							${AAlib_LIBRARIES}
						)
						include_directories( ${AAlib_INCLUDES})
					endif()

				endif()

	
		find_package(CACAlib QUIET)

				if (${CACAlib_FOUND})
					set(SDL_VIDEO_DRIVER_CACA ON CACHE BOOL "Enable support for Windows DirectX video driver")
					if (SDL_VIDEO_DRIVER_CACA)
						list(APPEND SDL_VIDEO_SRC
							video/caca/SDL_cacaevents_c.h
							video/caca/SDL_cacavideo.h
							video/caca/SDL_cacavideo.c
							video/caca/SDL_cacaevents.c
						)
						list(APPEND SDL_LIBRARIES
							${CACAlib_LIBRARIES}
						)
						include_directories( ${CACAlib_INCLUDES})
					endif()

				endif()
	

	if(WIN32)

			set(SDL_VIDEO_DRIVER_WINDX5 ON CACHE BOOL "Enable support for Windows DirectX video driver")
			if(SDL_VIDEO_DRIVER_WINDX5)
				list(APPEND SDL_VIDEO_SRC
						video/windx5/SDL_dx5yuv_c.h
						video/windx5/directx.h
						video/windx5/SDL_dx5events.c
						video/windx5/SDL_dx5yuv.c
						video/windx5/SDL_dx5video.c
						video/windx5/SDL_dx5video.h
						video/windx5/SDL_dx5events_c.h
				)
	
			endif()

			set(SDL_VIDEO_DRIVER_WINCOMMON ON CACHE BOOL "Enable support for Windows common video driver")
			if(SDL_VIDEO_DRIVER_WINCOMMON)
				list(APPEND SDL_VIDEO_SRC
						video/wincommon/SDL_wingl.c
						video/wincommon/SDL_sysevents.c
						video/wincommon/SDL_sysmouse_c.h
						video/wincommon/SDL_wingl_c.h
						video/wincommon/SDL_syswm.c
						video/wincommon/SDL_syswm_c.h
						video/wincommon/wmmsg.h
						video/wincommon/SDL_sysmouse.c
						video/wincommon/SDL_lowvideo.h
				)
	
			endif()

			set(SDL_VIDEO_DRIVER_WINDIB ON CACHE BOOL "Enable support for Windows DIB video driver")
			if(SDL_VIDEO_DRIVER_WINDIB)
				list(APPEND SDL_VIDEO_SRC
						video/windib/SDL_gapidibvideo.h
						video/windib/SDL_dibvideo.h
						video/windib/SDL_dibevents.c
						video/windib/SDL_dibevents_c.h
						video/windib/SDL_dibvideo.c
						video/windib/SDL_vkeys.h
				)
	
			endif()

	elseif(UNIX AND NOT APPLE)
		find_package(NanoX)
		if (NANOX_LIBRARY)
			set(SDL_VIDEO_DRIVER_NANOX ON CACHE BOOL "Enable support for NanoX video driver")
		else()
			set(SDL_VIDEO_DRIVER_NANOX OFF CACHE BOOL "Enable support for NanoX video driver")
		endif()
			if(SDL_VIDEO_DRIVER_NANOX)
				if (${NanoX_FOUND})
					list(APPEND SDL_VIDEO_SRC
						video/nanox/SDL_nxmouse.c
						video/nanox/SDL_nxmouse_c.h
						video/nanox/SDL_nxwm_c.h
						video/nanox/SDL_nxmodes.c
						video/nanox/SDL_nxwm.c
						video/nanox/SDL_nxvideo.h
						video/nanox/SDL_nximage_c.h
						video/nanox/SDL_nxevents_c.h
						video/nanox/SDL_nxevents.c
						video/nanox/SDL_nximage.c
						video/nanox/SDL_nxmodes_c.h
						video/nanox/SDL_nxvideo.c
					)
				list(APPEND SDL_LIBRARIES
					${NanoX_LIBRARIES}
				)
				include_directories( ${NanoX_INCLUDES})


				endif()
	
			endif()
		find_package(X11)
			if (X11_X11_LIB)
				set(SDL_VIDEO_DRIVER_X11 ON CACHE BOOL "Enable support for X11 video driver")
				set(SDL_VIDEO_DRIVER_X11_DYNAMIC ${X11_X11_LIB})
			else()
				set(SDL_VIDEO_DRIVER_X11 OFF CACHE BOOL "Enable support for X11 video driver")
			endif()

			#set(SDL_VIDEO_DRIVER_X11_VIDMODE ON CACHE BOOL "Enable support for X11 vidmode video driver")
			#set(SDL_VIDEO_DRIVER_X11_XME ON CACHE BOOL "Enable support for X11 Xme video driver")

			set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT ${X11_Xext_LIB})
			set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR ${X11_Xrandr_LIB})
			set(SDL_VIDEO_DRIVER_X11_DYNAMIC_XRENDER ${X11_Xrender_LIB})
			if (X11_Xinerama_LIB)
				set(SDL_VIDEO_DRIVER_X11_XINERAMA 1)
			endif()
			if (X11_Xv_LIB)
				set(SDL_VIDEO_DRIVER_X11_XV 1)
			endif()

			if(SDL_VIDEO_DRIVER_X11)
				if (${X11_FOUND})
					if(SDL_VIDEO_DRIVER_X11_XINERAMA)
						list(APPEND SDL_VIDEO_SRC
							video/Xext/Xinerama/Xinerama.c
						)
					endif()

					if(SDL_VIDEO_DRIVER_X11_XV)
						list(APPEND SDL_VIDEO_SRC
							video/Xext/Xv/Xv.c
							video/Xext/Xv/Xvlibint.h
						)
					endif()

					if(SDL_VIDEO_DRIVER_X11_XME)
						list(APPEND SDL_VIDEO_SRC
							video/Xext/XME/xme.c
						)
					endif()

					if (SDL_VIDEO_DRIVER_X11_VIDMODE)
						list(APPEND SDL_VIDEO_SRC
							video/Xext/Xxf86vm/XF86VMode.c
						)
					endif()
					list(APPEND SDL_VIDEO_SRC
						video/x11/SDL_x11sym.h
						video/x11/SDL_x11image_c.h
						video/x11/SDL_x11modes_c.h
						video/x11/SDL_x11dyn.h
						video/x11/SDL_x11events.c
						video/x11/SDL_x11gamma.c
						video/x11/SDL_x11video.h
						video/x11/SDL_x11mouse_c.h
						video/x11/SDL_x11gamma_c.h
						video/x11/SDL_x11modes.c
						video/x11/SDL_x11wm_c.h
						video/x11/SDL_x11gl_c.h
						video/x11/SDL_x11yuv.c
						video/x11/SDL_x11mouse.c
						video/x11/SDL_x11dga.c
						video/x11/SDL_x11dga_c.h
						video/x11/SDL_x11yuv_c.h
						video/x11/SDL_x11wm.c
						video/x11/SDL_x11dyn.c
						video/x11/SDL_x11gl.c
						video/x11/SDL_x11image.c
						video/x11/SDL_x11video.c
						video/x11/SDL_x11events_c.h
					)
				list(APPEND SDL_LIBRARIES
					${X11_LIBRARIES}
				)
				include_directories( ${X11_INCLUDES})


				endif()
	
			endif()


		find_package(FBcon)
			if (FBCON_LIBRARY)
				set(SDL_VIDEO_DRIVER_FBCON ON CACHE BOOL "Enable support for FrameBuffer Console video driver")
			else()
				set(SDL_VIDEO_DRIVER_FBCON OFF CACHE BOOL "Enable support for FrameBuffer Console video driver")
			endif()
			if(SDL_VIDEO_DRIVER_FBCON)
				if (${FBcon_FOUND})
					list(APPEND SDL_VIDEO_SRC
						video/fbcon/SDL_fbmatrox.c
						video/fbcon/SDL_fb3dfx.c
						video/fbcon/SDL_fbmatrox.h
						video/fbcon/3dfx_mmio.h
						video/fbcon/SDL_fbmouse_c.h
						video/fbcon/SDL_fbelo.c
						video/fbcon/SDL_fbevents.c
						video/fbcon/SDL_fbmouse.c
						video/fbcon/SDL_fbkeys.h
						video/fbcon/SDL_fbriva.c
						video/fbcon/SDL_fbriva.h
						video/fbcon/riva_regs.h
						video/fbcon/3dfx_regs.h
						video/fbcon/riva_mmio.h
						video/fbcon/SDL_fbvideo.c
						video/fbcon/matrox_mmio.h
						video/fbcon/SDL_fb3dfx.h
						video/fbcon/SDL_fbevents_c.h
						video/fbcon/SDL_fbvideo.h
						video/fbcon/matrox_regs.h
						video/fbcon/SDL_fbelo.h
					)
				list(APPEND SDL_LIBRARIES
					${FBcon_LIBRARIES}
				)
				include_directories( ${FBcon_INCLUDES})


				endif()
	
			endif()
		find_package(SVGAlib)
			if (SVGALIB_LIBRARY)
				set(SDL_VIDEO_DRIVER_SVGA ON CACHE BOOL "Enable support for SVGAlib video driver")
			else()
				set(SDL_VIDEO_DRIVER_SVGA OFF CACHE BOOL "Enable support for SVGAlib video driver")
			endif()

			if(SDL_VIDEO_DRIVER_SVGA)
				if (${SVGAlib_FOUND})
					list(APPEND SDL_VIDEO_SRC
						video/svga/SDL_svgaevents.c
						video/svga/SDL_svgaevents_c.h
						video/svga/SDL_svgavideo.c
						video/svga/SDL_svgamouse_c.h
						video/svga/SDL_svgavideo.h
						video/svga/SDL_svgamouse.c
					)
				list(APPEND SDL_LIBRARIES
					${SVGAlib_LIBRARIES}
				)
				include_directories( ${SVGAlib_INCLUDES})


				endif()
	
			endif()
		find_package(DirectFB)
			if (DIRECTFB_LIBRARY)
				set(SDL_VIDEO_DRIVER_DIRECTFB ON CACHE BOOL "Enable support for DirectFB video driver")
			else()
				set(SDL_VIDEO_DRIVER_DIRECTFB OFF CACHE BOOL "Enable support for DirectFB video driver")
			endif()

			if(SDL_VIDEO_DRIVER_DIRECTFB)
				if (${DirectFB_FOUND})
					list(APPEND SDL_VIDEO_SRC
						video/directfb/SDL_DirectFB_video.c
						video/directfb/SDL_DirectFB_events.h
						video/directfb/SDL_DirectFB_keys.h
						video/directfb/SDL_DirectFB_events.c
						video/directfb/SDL_DirectFB_video.h
						video/directfb/SDL_DirectFB_yuv.h
						video/directfb/SDL_DirectFB_yuv.c
					)
				list(APPEND SDL_LIBRARIES
					${DirectFB_LIBRARIES}
				)
				include_directories( ${DirectFB_INCLUDES})


				endif()
	
			endif()

	else()
		if(MACOSX)

			set(SDL_VIDEO_DRIVER_QUARTZ ON CACHE BOOL "Enable support for Quartz video driver")
			if(SDL_VIDEO_DRIVER_QUARTZ)
				list(APPEND SDL_VIDEO_SRC
						video/quartz/SDL_QuartzVideo.m
						video/quartz/SDL_QuartzWindow.m
						video/quartz/SDL_QuartzKeys.h
						video/quartz/SDL_QuartzGL.m
						video/quartz/SDL_QuartzVideo.h
						video/quartz/SDL_QuartzWM.m
						video/quartz/SDL_QuartzEvents.m
						video/quartz/CGS.h
						video/quartz/SDL_QuartzWindow.h
						video/quartz/SDL_QuartzWM.h
				)
	
			endif()

			set(SDL_VIDEO_DRIVER_MACCOMMON ON CACHE BOOL "Enable support for MacOS common video driver")
			if(SDL_VIDEO_DRIVER_MACCOMMON)
				list(APPEND SDL_VIDEO_SRC
						video/maccommon/SDL_macwm.c
						video/maccommon/SDL_macmouse.c
						video/maccommon/SDL_mackeys.h
						video/maccommon/SDL_macgl.c
						video/maccommon/SDL_macmouse_c.h
						video/maccommon/SDL_macevents.c
						video/maccommon/SDL_macevents_c.h
						video/maccommon/SDL_lowvideo.h
						video/maccommon/SDL_macwm_c.h
						video/maccommon/SDL_macgl_c.h
				)
	
			endif()

		else()

			set(SDL_VIDEO_DRIVER_MACDSP ON CACHE BOOL "Enable support for MacOS DSP video driver")
			if(SDL_VIDEO_DRIVER_MACDSP)
				list(APPEND SDL_VIDEO_SRC
						video/macdsp/SDL_dspvideo.c
						video/macdsp/SDL_dspvideo.h
				)
	
			endif()

			set(SDL_VIDEO_DRIVER_MACCOMMON ON CACHE BOOL "Enable support for MacOS common video driver")
			if(SDL_VIDEO_DRIVER_MACCOMMON)
				list(APPEND SDL_VIDEO_SRC
						video/maccommon/SDL_macwm.c
						video/maccommon/SDL_macmouse.c
						video/maccommon/SDL_mackeys.h
						video/maccommon/SDL_macgl.c
						video/maccommon/SDL_macmouse_c.h
						video/maccommon/SDL_macevents.c
						video/maccommon/SDL_macevents_c.h
						video/maccommon/SDL_lowvideo.h
						video/maccommon/SDL_macwm_c.h
						video/maccommon/SDL_macgl_c.h
				)
	
			endif()

			set(SDL_VIDEO_DRIVER_MACROM ON CACHE BOOL "Enable support for MacOS video driver")
			if(SDL_VIDEO_DRIVER_MACROM)
				list(APPEND SDL_VIDEO_SRC
						video/macrom/SDL_romvideo.c
						video/macrom/SDL_romvideo.h
				)
	
			endif()

		endif()
	endif()

endif()

source_group("Video" FILES ${SDL_VIDEO_SRC})

# -------------------- THREADS -----------------------

set(SDL_THREADS_DISABLED OFF CACHE BOOL "Disable support for Threads support")
set(SDL_THREADS_SRC "")

if(NOT SDL_THREADS_DISABLED)

	list(APPEND SDL_THREADS_SRC
		thread/SDL_systhread.h
		thread/SDL_thread_c.h
		thread/SDL_thread.c
	)



	if(WIN32)

			set(SDL_THREAD_WIN32 ON CACHE BOOL "Enable support for Windows Threads threads driver")
			if(SDL_THREAD_WIN32)
				list(APPEND SDL_THREADS_SRC
						thread/win32/win_ce_semaphore.c
						thread/win32/SDL_systhread_c.h
						thread/win32/win_ce_semaphore.h
						thread/win32/SDL_systhread.c
						thread/win32/SDL_sysmutex.c
						thread/win32/SDL_syssem.c
				)
	
			endif()

	elseif(UNIX AND NOT APPLE)
		find_package(Threads)

			set(SDL_THREAD_PTHREAD ON CACHE BOOL "Enable support for pthread threads driver")
			if(SDL_THREAD_PTHREAD)
				if (${Threads_FOUND})
					list(APPEND SDL_THREADS_SRC
						thread/pthread/SDL_systhread_c.h
						thread/pthread/SDL_syscond.c
						thread/pthread/SDL_systhread.c
						thread/pthread/SDL_sysmutex_c.h
						thread/pthread/SDL_sysmutex.c
						thread/pthread/SDL_syssem.c
					)
				list(APPEND SDL_LIBRARIES
					${CMAKE_THREAD_LIBS_INIT}
				)
				


				endif()
	
			endif()

			set(SDL_THREAD_GENERIC ON CACHE BOOL "Enable support for Generic Threads threads driver")
			if(SDL_THREAD_GENERIC AND NOT SDL_THREAD_PTHREAD)
				list(APPEND SDL_THREADS_SRC
						thread/generic/SDL_systhread_c.h
						thread/generic/SDL_syscond.c
						thread/generic/SDL_systhread.c
						thread/generic/SDL_sysmutex_c.h
						thread/generic/SDL_sysmutex.c
						thread/generic/SDL_syssem.c
				)
	
			endif()

	else()
		if(MACOSX)

		else()

		endif()
	endif()

endif()

source_group("Threads" FILES ${SDL_THREADS_SRC})

# -------------------- EVENTS -----------------------

set(SDL_EVENTS_DISABLED OFF CACHE BOOL "Disable support for Events support")
set(SDL_EVENTS_SRC "")

if(NOT SDL_EVENTS_DISABLED)

	list(APPEND SDL_EVENTS_SRC
		events/SDL_resize.c
		events/SDL_events.c
		events/SDL_events_c.h
		events/SDL_sysevents.h
		events/SDL_mouse.c
		events/SDL_keyboard.c
		events/SDL_active.c
		events/SDL_quit.c
		events/SDL_expose.c	
	)
endif()

source_group("Events" FILES ${SDL_EVENTS_SRC})

# -------------------- CPUINFO -----------------------

set(SDL_CPUINFO_DISABLED OFF CACHE BOOL "Disable support for CPU info support")
set(SDL_CPUINFO_SRC "")

if(NOT SDL_CPUINFO_DISABLED)

	list(APPEND SDL_CPUINFO_SRC
		cpuinfo/SDL_cpuinfo.c	
	)

endif()

source_group("CPU info" FILES ${SDL_CPUINFO_SRC})

# -------------------- FILE -----------------------

set(SDL_FILE_DISABLED OFF CACHE BOOL "Disable support for File management support")
set(SDL_FILE_SRC "")

if(NOT SDL_FILE_DISABLED)

	list(APPEND SDL_FILE_SRC
		file/SDL_rwops.c	
	)

endif()

source_group("File management" FILES ${SDL_FILE_SRC})

# -------------------- LOADSO -----------------------

set(SDL_LOADSO_DISABLED OFF CACHE BOOL "Disable support for Dynamic library loading support")
set(SDL_LOADSO_SRC "")

if(NOT SDL_LOADSO_DISABLED)




#			set(SDL_LOADSO_DUMMY 1)
#				list(APPEND SDL_LOADSO_SRC
#						loadso/dummy/SDL_sysloadso.c
#				)
	

	if(WIN32)

			set(SDL_LOADSO_WIN32 ON CACHE BOOL "Enable support for Windows DLL dynamic library loading driver")
			if(SDL_LOADSO_WIN32)
				list(APPEND SDL_LOADSO_SRC
						loadso/win32/SDL_sysloadso.c
				)
	
			endif()

	elseif(UNIX AND NOT APPLE)

			set(SDL_LOADSO_DLOPEN ON CACHE BOOL "Enable support for Unix dlopen dynamic library loading driver")
			if(SDL_LOADSO_DLOPEN)
				list(APPEND SDL_LOADSO_SRC
						loadso/dlopen/SDL_sysloadso.c
				)
	
			endif()

	else()
		if(MACOSX)

			set(SDL_LOADSO_MACOSX ON CACHE BOOL "Enable support for MacOS X dynamic library loading driver")
			if(SDL_LOADSO_MACOSX)
				list(APPEND SDL_LOADSO_SRC
						loadso/macosx/SDL_dlcompat.c
				)
	
			endif()

		else()

			set(SDL_LOADSO_MACOS ON CACHE BOOL "Enable support for MacOS dynamic library loading driver")
			if(SDL_LOADSO_MACOS)
				list(APPEND SDL_LOADSO_SRC
						loadso/macos/SDL_sysloadso.c
				)
	
			endif()

		endif()
	endif()

endif()

source_group("Dynamic library loading" FILES ${SDL_LOADSO_SRC})

set(SDL_MAIN_SRC
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
else()
	list(APPEND SDL_MAIN_SRC
	    main/dummy/SDL_dummy_main.c
	)
endif()

if (WIN32 OR APPLE)
	set(SDLmain_LIBRARIES "")

	add_library(SDLmain STATIC
		${SDL_MAIN_SRC}
	)

	set_target_properties(SDLmain
    	PROPERTIES
	    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
	)

	target_link_libraries (SDLmain
		${SDLmain_LIBRARIES}
	)

	list(APPEND SDL_LIBRARIES
		SDLmain
	)

endif()

set(SDL_SRC
    SDL.c
    SDL_error.c
    SDL_fatal.c
)

source_group("SDL Main" FILES ${SDL_MAIN_SRC})

set(SDL_STDLIB_SRC
    stdlib/SDL_getenv.c
    stdlib/SDL_iconv.c
    stdlib/SDL_malloc.c
    stdlib/SDL_qsort.c
    stdlib/SDL_stdlib.c
    stdlib/SDL_string.c
)

source_group("STDLIB" FILES ${SDL_STDLIB_SRC})

set(SDL_SOURCES
	${SDL_JOYSTICK_SRC}
	${SDL_TIMERS_SRC}
	${SDL_AUDIO_SRC}
	${SDL_CDROM_SRC}
	${SDL_VIDEO_SRC}
	${SDL_THREADS_SRC}
	${SDL_EVENTS_SRC}
	${SDL_CPUINFO_SRC}
	${SDL_FILE_SRC}
	${SDL_LOADSO_SRC}
	${SDL_SRC}
	${SDL_STDLIB_SRC}
)

if (WIN32 AND (SDL_AUDIO_DRIVER_WINDX5 OR SDL_VIDEO_DRIVER_WINDX5 OR SDL_VIDEO_DRIVER_WINCOMMON))
	list(APPEND SDL_LIBRARIES
		${DIRECTX_LIBRARIES}
		winmm.lib
	)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/../include)

# -------------------------- CONFIG -----------------------------

if (NOT SDL_VIDEO_DISABLED)
	find_package(OpenGL QUIET)
	
	if (OPENGL_FOUND)
		message("OpenGL support: On")
		set(SDL_VIDEO_OPENGL 1)
		if (WIN32)
			set(SDL_VIDEO_OPENGL_WGL 1)
		elseif (UNIX)
			set(SDL_VIDEO_OPENGL_GLX 1)
		endif()
	else()
		message("OpenGL support: Off")
	endif()
endif()

check_include_files(X11/extensions/XShm.h USE_SHARED_MEMORY)
if (NOT USE_SHARED_MEMORY)
	set(NO_SHARED_MEMORY 1)
	add_definitions(-DNO_SHARED_MEMORY=1)
endif()


if ((${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64|x86|AMD64"))
	set(SDL_ASSEMBLY_ROUTINES 1)
endif()

if(WIN32)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../include/SDL_config_win32.h ${CMAKE_CURRENT_BINARY_DIR}/../include/SDL_config.h @ONLY)
else()
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../include/SDL_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/../include/SDL_config.h @ONLY)
endif()

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

    
