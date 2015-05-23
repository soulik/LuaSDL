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

#include <io.h>

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

