/* ================================================================== */
/*
 * sdllib.h
 * Additional code to support SDL binding.
 *
 * This file is part of LuaSDL.
 *
 * Copyright (c) 2007 Kein-Hong Man <khman@users.sf.net>
 * The COPYRIGHT-LuaSDL file describes the conditions
 * under which this software may be distributed.
 */
/* ================================================================== */
#ifdef _WIN32
#include <io.h>
#ifndef MAX_PATH
#define MAX_PATH	260
#endif
#else
#include <limits.h>
#define MAX_PATH PATH_MAX
#endif

/* also, please change version number at luasdl.rc */
#define LuaSDL_VERSION  "LuaSDL 0.3.4"

/* default script, resides in executable's directory */
#define SCRIPT_DEFAULT  "__init__.lua"

/* information passed to LuaSDL library startup, paranoid array sizing */
struct LuaSDL_StartInfo {
    char dir_sep[2];
    char dir_cwd[MAX_PATH+1];
    char dir_exe[MAX_PATH+1];
    char dir_app[MAX_PATH+1];
    char appname[MAX_PATH+1];
    char *notfound;
};

/* called by luasdl.c to initialize LuaSDL services */
TOLUA_API int luaopen_LuaSDL (lua_State* L);

/* supplementary functionality exposed */

extern Uint32 SDL_GetPixel(SDL_Surface *surface, int x, int y);
extern void SDL_PutPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

extern void LuaSDL_AudioCh1(void *audio_buf, Uint32 audio_len, int loop, int volume);
extern void LuaSDL_AudioCh2(void *audio_buf, Uint32 audio_len, int loop, int volume);

/* modified API calls exposed */

/* SDL_timer.h */
extern SDL_TimerID _SDL_AddTimer(Uint32 interval, SDL_Event *param);
/* SDL_audio.h */
extern SDL_AudioSpec * _SDL_LoadWAV_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec,
    void **audio_buf, Uint32 *audio_len);
extern SDL_AudioSpec * _SDL_LoadWAV(const char *file, SDL_AudioSpec *spec,
    void **audio_buf, Uint32 *audio_len);

/* memory management functions */

extern SDL_AudioSpec* SDL_AudioSpec_new(void);          /* SDL_audio.h */
extern void SDL_AudioSpec_delete(SDL_AudioSpec *obj);
extern SDL_AudioCVT* SDL_AudioCVT_new(void);
extern void SDL_AudioCVT_delete(SDL_AudioCVT *obj);

extern SDL_CDtrack* SDL_CDtrack_new(void);              /* SDL_cdrom.h */
extern void SDL_CDtrack_delete(SDL_CDtrack *obj);
extern SDL_CD* SDL_CD_new(void);
extern void SDL_CD_delete(SDL_CD *obj);

extern SDL_Event* SDL_Event_new(void);                  /* SDL_events.h */
extern void SDL_Event_delete(SDL_Event *obj);

extern SDL_keysym* SDL_keysym_new(void);                /* SDL_keyboard.h */
extern void SDL_keysym_delete(SDL_keysym *obj);

extern SDL_Cursor* SDL_Cursor_new(void);                /* SDL_mouse.h */
extern void SDL_Cursor_delete(SDL_Cursor *obj);

extern IPaddress* IPaddress_new(void);                  /* SDL_net.h */
extern void IPaddress_delete(IPaddress *obj);

extern SDL_version* SDL_version_new(void);              /* SDL_version.h */
extern void SDL_version_delete(SDL_version *obj);

extern SDL_Rect* SDL_Rect_new(void);                    /* SDL_video.h */
extern void SDL_Rect_delete(SDL_Rect *obj);
extern SDL_Color* SDL_Color_new(void);
extern void SDL_Color_delete(SDL_Color *obj);
extern SDL_PixelFormat* SDL_PixelFormat_new(void);
extern void SDL_PixelFormat_delete(SDL_PixelFormat *obj);

/* NOTE: not required, user never needs to set one up directly */
/* extern SDL_Surface* SDL_Surface_new(void); */
/* extern void SDL_Surface_delete(SDL_Surface *obj); */
extern SDL_VideoInfo* SDL_VideoInfo_new(void);
extern void SDL_VideoInfo_delete(SDL_VideoInfo *obj);

#ifndef SDL_AUDIO_DISABLED
#define SDL_AUDIO_DISABLED 0
#endif

#ifndef SDL_CDROM_DISABLED
#define SDL_CDROM_DISABLED 0
#endif

#ifndef SDL_CPUINFO_DISABLED
#define SDL_CPUINFO_DISABLED 0
#endif

#ifndef SDL_EVENTS_DISABLED
#define SDL_EVENTS_DISABLED 0
#endif

#ifndef SDL_FILE_DISABLED
#define SDL_FILE_DISABLED 0
#endif

#ifndef SDL_JOYSTICK_DISABLED
#define SDL_JOYSTICK_DISABLED 0
#endif

#ifndef SDL_LOADSO_DISABLED
#define SDL_LOADSO_DISABLED 0
#endif

#ifndef SDL_THREADS_DISABLED
#define SDL_THREADS_DISABLED 0
#endif

#ifndef SDL_TIMERS_DISABLED
#define SDL_TIMERS_DISABLED 0
#endif

#ifndef SDL_VIDEO_DISABLED
#define SDL_VIDEO_DISABLED 0
#endif

#ifndef SDL_AUDIO_DRIVER_ALSA
#define SDL_AUDIO_DRIVER_ALSA 0
#endif

#ifndef SDL_AUDIO_DRIVER_ALSA_DYNAMIC
#define SDL_AUDIO_DRIVER_ALSA_DYNAMIC 0
#endif

#ifndef SDL_AUDIO_DRIVER_ARTS
#define SDL_AUDIO_DRIVER_ARTS 0
#endif

#ifndef SDL_AUDIO_DRIVER_ARTS_DYNAMIC
#define SDL_AUDIO_DRIVER_ARTS_DYNAMIC 0
#endif

#ifndef SDL_AUDIO_DRIVER_BAUDIO
#define SDL_AUDIO_DRIVER_BAUDIO 0
#endif

#ifndef SDL_AUDIO_DRIVER_BSD
#define SDL_AUDIO_DRIVER_BSD 0
#endif

#ifndef SDL_AUDIO_DRIVER_COREAUDIO
#define SDL_AUDIO_DRIVER_COREAUDIO 0
#endif

#ifndef SDL_AUDIO_DRIVER_DART
#define SDL_AUDIO_DRIVER_DART 0
#endif

#ifndef SDL_AUDIO_DRIVER_DC
#define SDL_AUDIO_DRIVER_DC 0
#endif

#ifndef SDL_AUDIO_DRIVER_DISK
#define SDL_AUDIO_DRIVER_DISK 0
#endif

#ifndef SDL_AUDIO_DRIVER_DUMMY
#define SDL_AUDIO_DRIVER_DUMMY 0
#endif

#ifndef SDL_AUDIO_DRIVER_DMEDIA
#define SDL_AUDIO_DRIVER_DMEDIA 0
#endif

#ifndef SDL_AUDIO_DRIVER_DSOUND
#define SDL_AUDIO_DRIVER_DSOUND 0
#endif

#ifndef SDL_AUDIO_DRIVER_PULSE
#define SDL_AUDIO_DRIVER_PULSE 0
#endif

#ifndef SDL_AUDIO_DRIVER_PULSE_DYNAMIC
#define SDL_AUDIO_DRIVER_PULSE_DYNAMIC 0
#endif

#ifndef SDL_AUDIO_DRIVER_ESD
#define SDL_AUDIO_DRIVER_ESD 0
#endif

#ifndef SDL_AUDIO_DRIVER_ESD_DYNAMIC
#define SDL_AUDIO_DRIVER_ESD_DYNAMIC 0
#endif

#ifndef SDL_AUDIO_DRIVER_MINT
#define SDL_AUDIO_DRIVER_MINT 0
#endif

#ifndef SDL_AUDIO_DRIVER_MMEAUDIO
#define SDL_AUDIO_DRIVER_MMEAUDIO 0
#endif

#ifndef SDL_AUDIO_DRIVER_NAS
#define SDL_AUDIO_DRIVER_NAS 0
#endif

#ifndef SDL_AUDIO_DRIVER_NAS_DYNAMIC
#define SDL_AUDIO_DRIVER_NAS_DYNAMIC 0
#endif

#ifndef SDL_AUDIO_DRIVER_OSS
#define SDL_AUDIO_DRIVER_OSS 0
#endif

#ifndef SDL_AUDIO_DRIVER_OSS_SOUNDCARD_H
#define SDL_AUDIO_DRIVER_OSS_SOUNDCARD_H 0
#endif

#ifndef SDL_AUDIO_DRIVER_PAUD
#define SDL_AUDIO_DRIVER_PAUD 0
#endif

#ifndef SDL_AUDIO_DRIVER_QNXNTO
#define SDL_AUDIO_DRIVER_QNXNTO 0
#endif

#ifndef SDL_AUDIO_DRIVER_SNDMGR
#define SDL_AUDIO_DRIVER_SNDMGR 0
#endif

#ifndef SDL_AUDIO_DRIVER_SUNAUDIO
#define SDL_AUDIO_DRIVER_SUNAUDIO 0
#endif

#ifndef SDL_AUDIO_DRIVER_WAVEOUT
#define SDL_AUDIO_DRIVER_WAVEOUT 0
#endif

#ifndef SDL_CDROM_AIX
#define SDL_CDROM_AIX 0
#endif

#ifndef SDL_CDROM_BEOS
#define SDL_CDROM_BEOS 0
#endif

#ifndef SDL_CDROM_BSDI
#define SDL_CDROM_BSDI 0
#endif

#ifndef SDL_CDROM_DC
#define SDL_CDROM_DC 0
#endif

#ifndef SDL_CDROM_DUMMY
#define SDL_CDROM_DUMMY 0
#endif

#ifndef SDL_CDROM_FREEBSD
#define SDL_CDROM_FREEBSD 0
#endif

#ifndef SDL_CDROM_LINUX
#define SDL_CDROM_LINUX 0
#endif

#ifndef SDL_CDROM_MACOS
#define SDL_CDROM_MACOS 0
#endif

#ifndef SDL_CDROM_MACOSX
#define SDL_CDROM_MACOSX 0
#endif

#ifndef SDL_CDROM_MINT
#define SDL_CDROM_MINT 0
#endif

#ifndef SDL_CDROM_OPENBSD
#define SDL_CDROM_OPENBSD 0
#endif

#ifndef SDL_CDROM_OS2
#define SDL_CDROM_OS2 0
#endif

#ifndef SDL_CDROM_OSF
#define SDL_CDROM_OSF 0
#endif

#ifndef SDL_CDROM_QNX
#define SDL_CDROM_QNX 0
#endif

#ifndef SDL_CDROM_WIN32
#define SDL_CDROM_WIN32 0
#endif

#ifndef SDL_INPUT_LINUXEV
#define SDL_INPUT_LINUXEV 0
#endif

#ifndef SDL_INPUT_TSLIB
#define SDL_INPUT_TSLIB 0
#endif

#ifndef SDL_JOYSTICK_BEOS
#define SDL_JOYSTICK_BEOS 0
#endif

#ifndef SDL_JOYSTICK_DC
#define SDL_JOYSTICK_DC 0
#endif

#ifndef SDL_JOYSTICK_DUMMY
#define SDL_JOYSTICK_DUMMY 0
#endif

#ifndef SDL_JOYSTICK_IOKIT
#define SDL_JOYSTICK_IOKIT 0
#endif

#ifndef SDL_JOYSTICK_LINUX
#define SDL_JOYSTICK_LINUX 0
#endif

#ifndef SDL_JOYSTICK_MACOS
#define SDL_JOYSTICK_MACOS 0
#endif

#ifndef SDL_JOYSTICK_MINT
#define SDL_JOYSTICK_MINT 0
#endif

#ifndef SDL_JOYSTICK_OS2
#define SDL_JOYSTICK_OS2 0
#endif

#ifndef SDL_JOYSTICK_RISCOS
#define SDL_JOYSTICK_RISCOS 0
#endif

#ifndef SDL_JOYSTICK_WINMM
#define SDL_JOYSTICK_WINMM 0
#endif

#ifndef SDL_JOYSTICK_USBHID
#define SDL_JOYSTICK_USBHID 0
#endif

#ifndef SDL_JOYSTICK_USBHID_MACHINE_JOYSTICK_H
#define SDL_JOYSTICK_USBHID_MACHINE_JOYSTICK_H 0
#endif

#ifndef SDL_LOADSO_BEOS
#define SDL_LOADSO_BEOS 0
#endif

#ifndef SDL_LOADSO_DLCOMPAT
#define SDL_LOADSO_DLCOMPAT 0
#endif

#ifndef SDL_LOADSO_DLOPEN
#define SDL_LOADSO_DLOPEN 0
#endif

#ifndef SDL_LOADSO_DUMMY
#define SDL_LOADSO_DUMMY 0
#endif

#ifndef SDL_LOADSO_LDG
#define SDL_LOADSO_LDG 0
#endif

#ifndef SDL_LOADSO_MACOS
#define SDL_LOADSO_MACOS 0
#endif

#ifndef SDL_LOADSO_OS2
#define SDL_LOADSO_OS2 0
#endif

#ifndef SDL_LOADSO_WIN32
#define SDL_LOADSO_WIN32 0
#endif

#ifndef SDL_THREAD_BEOS
#define SDL_THREAD_BEOS 0
#endif

#ifndef SDL_THREAD_DC
#define SDL_THREAD_DC 0
#endif

#ifndef SDL_THREAD_OS2
#define SDL_THREAD_OS2 0
#endif

#ifndef SDL_THREAD_PTH
#define SDL_THREAD_PTH 0
#endif

#ifndef SDL_THREAD_PTHREAD
#define SDL_THREAD_PTHREAD 0
#endif

#ifndef SDL_THREAD_PTHREAD_RECURSIVE_MUTEX
#define SDL_THREAD_PTHREAD_RECURSIVE_MUTEX 0
#endif

#ifndef SDL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP
#define SDL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP 0
#endif

#ifndef SDL_THREAD_SPROC
#define SDL_THREAD_SPROC 0
#endif

#ifndef SDL_THREAD_WIN32
#define SDL_THREAD_WIN32 0
#endif

#ifndef SDL_TIMER_BEOS
#define SDL_TIMER_BEOS 0
#endif

#ifndef SDL_TIMER_DC
#define SDL_TIMER_DC 0
#endif

#ifndef SDL_TIMER_DUMMY
#define SDL_TIMER_DUMMY 0
#endif

#ifndef SDL_TIMER_MACOS
#define SDL_TIMER_MACOS 0
#endif

#ifndef SDL_TIMER_MINT
#define SDL_TIMER_MINT 0
#endif

#ifndef SDL_TIMER_OS2
#define SDL_TIMER_OS2 0
#endif

#ifndef SDL_TIMER_RISCOS
#define SDL_TIMER_RISCOS 0
#endif

#ifndef SDL_TIMER_UNIX
#define SDL_TIMER_UNIX 0
#endif

#ifndef SDL_TIMER_WIN32
#define SDL_TIMER_WIN32 0
#endif

#ifndef SDL_TIMER_WINCE
#define SDL_TIMER_WINCE 0
#endif

#ifndef SDL_VIDEO_DRIVER_AALIB
#define SDL_VIDEO_DRIVER_AALIB 0
#endif

#ifndef SDL_VIDEO_DRIVER_BWINDOW
#define SDL_VIDEO_DRIVER_BWINDOW 0
#endif

#ifndef SDL_VIDEO_DRIVER_CACA
#define SDL_VIDEO_DRIVER_CACA 0
#endif

#ifndef SDL_VIDEO_DRIVER_DC
#define SDL_VIDEO_DRIVER_DC 0
#endif

#ifndef SDL_VIDEO_DRIVER_DDRAW
#define SDL_VIDEO_DRIVER_DDRAW 0
#endif

#ifndef SDL_VIDEO_DRIVER_DGA
#define SDL_VIDEO_DRIVER_DGA 0
#endif

#ifndef SDL_VIDEO_DRIVER_DIRECTFB
#define SDL_VIDEO_DRIVER_DIRECTFB 0
#endif

#ifndef SDL_VIDEO_DRIVER_DRAWSPROCKET
#define SDL_VIDEO_DRIVER_DRAWSPROCKET 0
#endif

#ifndef SDL_VIDEO_DRIVER_DUMMY
#define SDL_VIDEO_DRIVER_DUMMY 0
#endif

#ifndef SDL_VIDEO_DRIVER_FBCON
#define SDL_VIDEO_DRIVER_FBCON 0
#endif

#ifndef SDL_VIDEO_DRIVER_GAPI
#define SDL_VIDEO_DRIVER_GAPI 0
#endif

#ifndef SDL_VIDEO_DRIVER_GEM
#define SDL_VIDEO_DRIVER_GEM 0
#endif

#ifndef SDL_VIDEO_DRIVER_GGI
#define SDL_VIDEO_DRIVER_GGI 0
#endif

#ifndef SDL_VIDEO_DRIVER_IPOD
#define SDL_VIDEO_DRIVER_IPOD 0
#endif

#ifndef SDL_VIDEO_DRIVER_NANOX
#define SDL_VIDEO_DRIVER_NANOX 0
#endif

#ifndef SDL_VIDEO_DRIVER_OS2FS
#define SDL_VIDEO_DRIVER_OS2FS 0
#endif

#ifndef SDL_VIDEO_DRIVER_PHOTON
#define SDL_VIDEO_DRIVER_PHOTON 0
#endif

#ifndef SDL_VIDEO_DRIVER_PICOGUI
#define SDL_VIDEO_DRIVER_PICOGUI 0
#endif

#ifndef SDL_VIDEO_DRIVER_PS2GS
#define SDL_VIDEO_DRIVER_PS2GS 0
#endif

#ifndef SDL_VIDEO_DRIVER_PS3
#define SDL_VIDEO_DRIVER_PS3 0
#endif

#ifndef SDL_VIDEO_DRIVER_QTOPIA
#define SDL_VIDEO_DRIVER_QTOPIA 0
#endif

#ifndef SDL_VIDEO_DRIVER_QUARTZ
#define SDL_VIDEO_DRIVER_QUARTZ 0
#endif

#ifndef SDL_VIDEO_DRIVER_RISCOS
#define SDL_VIDEO_DRIVER_RISCOS 0
#endif

#ifndef SDL_VIDEO_DRIVER_SVGALIB
#define SDL_VIDEO_DRIVER_SVGALIB 0
#endif

#ifndef SDL_VIDEO_DRIVER_TOOLBOX
#define SDL_VIDEO_DRIVER_TOOLBOX 0
#endif

#ifndef SDL_VIDEO_DRIVER_VGL
#define SDL_VIDEO_DRIVER_VGL 0
#endif

#ifndef SDL_VIDEO_DRIVER_WINDIB
#define SDL_VIDEO_DRIVER_WINDIB 0
#endif

#ifndef SDL_VIDEO_DRIVER_WSCONS
#define SDL_VIDEO_DRIVER_WSCONS 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11
#define SDL_VIDEO_DRIVER_X11 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_DGAMOUSE
#define SDL_VIDEO_DRIVER_X11_DGAMOUSE 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_DYNAMIC
#define SDL_VIDEO_DRIVER_X11_DYNAMIC 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XEXT 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRANDR 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_DYNAMIC_XRENDER
#define SDL_VIDEO_DRIVER_X11_DYNAMIC_XRENDER 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_VIDMODE
#define SDL_VIDEO_DRIVER_X11_VIDMODE 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_XINERAMA
#define SDL_VIDEO_DRIVER_X11_XINERAMA 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_XME
#define SDL_VIDEO_DRIVER_X11_XME 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_XRANDR
#define SDL_VIDEO_DRIVER_X11_XRANDR 0
#endif

#ifndef SDL_VIDEO_DRIVER_X11_XV
#define SDL_VIDEO_DRIVER_X11_XV 0
#endif

#ifndef SDL_VIDEO_DRIVER_XBIOS
#define SDL_VIDEO_DRIVER_XBIOS 0
#endif

#ifndef SDL_VIDEO_OPENGL
#define SDL_VIDEO_OPENGL 0
#endif

#ifndef SDL_VIDEO_OPENGL_GLX
#define SDL_VIDEO_OPENGL_GLX 0
#endif

#ifndef SDL_VIDEO_OPENGL_WGL
#define SDL_VIDEO_OPENGL_WGL 0
#endif

#ifndef SDL_VIDEO_OPENGL_OSMESA
#define SDL_VIDEO_OPENGL_OSMESA 0
#endif

#ifndef SDL_VIDEO_OPENGL_OSMESA_DYNAMIC
#define SDL_VIDEO_OPENGL_OSMESA_DYNAMIC 0
#endif

