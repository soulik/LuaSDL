/*
** Lua binding: SDL
** Generated automatically by tolua++-1.0.92 on 12/29/10 03:12:00.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#define MAX_PATH 1024
/* Exported function */
TOLUA_API int tolua_SDL_open (lua_State* tolua_S);

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_ttf.h"
#include "SDL_mutex.h"
#include <SDL_gfx/SDL_gfx.h>
#include "sdllib.h"

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
#include <shellapi.h>
#endif

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

#ifndef SDL_revcpy
void * SDL_revcpy(void *dst, const void *src, size_t len)
{
    char *srcp = (char *) src;
    char *dstp = (char *) dst;
    srcp += len - 1;
    dstp += len - 1;
    while (len--) {
        *dstp-- = *srcp--;
    }
    return dst;
}
#endif

#ifndef HAVE_STRDUP
char *
SDL_strdup(const char *string)
{
    size_t len = SDL_strlen(string) + 1;
    char *newstr = (char*)SDL_malloc(len);
    if (newstr) {
        SDL_strlcpy(newstr, string, len);
    }
    return newstr;
}
#endif

inline void * _SDL_memcpy (void *dst, const void *src, size_t len)
{
#if defined(__GNUC__) && defined(i386)
	SDL_memcpy(dst, src, len);
	return dst;
#else
	return SDL_memcpy(dst, src, len);
#endif
}
inline void * _SDL_revcpy (void *dst, const void *src, size_t len)
{
#if defined(__GNUC__) && defined(i386)
	SDL_revcpy(dst, src, len);
	return dst;
#else
	return SDL_revcpy(dst, src, len);
#endif
}
inline Uint16 SDL_Pass16 (Uint16 x)
{
	return x;
}
inline Uint32 SDL_Pass32 (Uint32 x)
{
	return x;
}
static const char* _MIX_EFFECTSMAXSPEED = MIX_EFFECTSMAXSPEED;
typedef struct {
	int ready;
} _SDLNet_GenericSocket;
inline SDL_bool _SDLNet_SocketReady(SDLNet_GenericSocket sock)
{
	return SDLNet_SocketReady(sock);
}
inline SDL_bool _SDLNet_TCP_SocketReady(TCPsocket sock)
{
	return SDLNet_SocketReady(sock);
}
inline SDL_bool _SDLNet_UDP_SocketReady(UDPsocket sock)
{
	return SDLNet_SocketReady(sock);
}

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
	tolua_usertype(tolua_S,"_TCPsocket");
	tolua_usertype(tolua_S,"_Mix_Music");
	tolua_usertype(tolua_S,"SDL_MouseButtonEvent");
	tolua_usertype(tolua_S,"SDL_MouseMotionEvent");
	tolua_usertype(tolua_S,"SDL_ResizeEvent");
	tolua_usertype(tolua_S,"SDL_ExposeEvent");
	tolua_usertype(tolua_S,"SDL_Event");
	tolua_usertype(tolua_S,"SDL_Cursor");
	tolua_usertype(tolua_S,"SDL_AudioCVT");
	tolua_usertype(tolua_S,"_SDL_Joystick");
	tolua_usertype(tolua_S,"_TTF_Font");
	tolua_usertype(tolua_S,"Mix_Chunk");
	tolua_usertype(tolua_S,"SDL_QuitEvent");
	tolua_usertype(tolua_S,"SDL_JoyBallEvent");
	tolua_usertype(tolua_S,"UDPpacket");
	tolua_usertype(tolua_S,"_SDL_TimerID");
	tolua_usertype(tolua_S,"SDL_Overlay");
	tolua_usertype(tolua_S,"SDL_CD");
	tolua_usertype(tolua_S,"SDL_Color");
	tolua_usertype(tolua_S,"SDL_JoyHatEvent");
	tolua_usertype(tolua_S,"SDL_Palette");
	tolua_usertype(tolua_S,"IPaddress");
	tolua_usertype(tolua_S,"SDL_SysWMmsg");
	tolua_usertype(tolua_S,"SDL_Rect");
	tolua_usertype(tolua_S,"_SDLNet_GenericSocket");
	tolua_usertype(tolua_S,"SDL_CDtrack");
	tolua_usertype(tolua_S,"WMcursor");
	tolua_usertype(tolua_S,"SDL_RWops");
	tolua_usertype(tolua_S,"_UDPsocket");
	tolua_usertype(tolua_S,"_SDL_iconv_t");
	tolua_usertype(tolua_S,"SDL_Surface");
	tolua_usertype(tolua_S,"SDL_JoyButtonEvent");
	tolua_usertype(tolua_S,"SDL_JoyAxisEvent");
	tolua_usertype(tolua_S,"SDL_ActiveEvent");
	tolua_usertype(tolua_S,"SDL_version");
	tolua_usertype(tolua_S,"SDL_VideoInfo");
	tolua_usertype(tolua_S,"SDL_PixelFormat");
	tolua_usertype(tolua_S,"SDL_keysym");
	tolua_usertype(tolua_S,"SDL_SysWMEvent");
	tolua_usertype(tolua_S,"SDL_KeyboardEvent");
	tolua_usertype(tolua_S,"SDL_AudioSpec");
	tolua_usertype(tolua_S,"SDL_UserEvent");
	tolua_usertype(tolua_S,"_SDLNet_SocketSet");
	tolua_usertype(tolua_S,"SDL_Mutex");
}

#ifdef __WIN32__
/* function: SDL_shellExecute */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_shell_execute00
static int tolua_SDL_SDL_SDL_shell_execute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char * op = lua_tostring(tolua_S,1);
		const char * fname = lua_tostring(tolua_S,2);
		HINSTANCE ret = ShellExecute(NULL,op,fname,NULL,NULL,SW_SHOWNORMAL);
		lua_pushinteger(tolua_S,(int)ret);
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_shellExecute'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE
#endif

/* function: SDL_malloc */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_malloc00
static int tolua_SDL_SDL_SDL_malloc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int size = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
		{
			void* tolua_ret = (void*)  SDL_malloc(size);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_malloc'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_calloc */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_calloc00
static int tolua_SDL_SDL_SDL_calloc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int nmemb = (( unsigned int)  tolua_tonumber(tolua_S,1,0));
		unsigned int size = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
		{
			void* tolua_ret = (void*)  SDL_calloc(nmemb,size);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_calloc'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_realloc */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_realloc00
static int tolua_SDL_SDL_SDL_realloc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* mem = ((void*)  tolua_touserdata(tolua_S,1,0));
		unsigned int size = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
		{
			void* tolua_ret = (void*)  SDL_realloc(mem,size);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_realloc'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_free */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_free00
static int tolua_SDL_SDL_SDL_free00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* mem = ((void*)  tolua_touserdata(tolua_S,1,0));
		{
			SDL_free(mem);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_free'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_getenv */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_getenv00
static int tolua_SDL_SDL_SDL_getenv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  SDL_getenv(name);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_getenv'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_putenv */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_putenv00
static int tolua_SDL_SDL_SDL_putenv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* variable = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_putenv(variable);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_putenv'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_isdigit */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_isdigit00
static int tolua_SDL_SDL_SDL_isdigit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int X = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_isdigit(X);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_isdigit'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_isspace */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_isspace00
static int tolua_SDL_SDL_SDL_isspace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int X = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_isspace(X);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_isspace'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_toupper */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_toupper00
static int tolua_SDL_SDL_SDL_toupper00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int X = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_toupper(X);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_toupper'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_tolower */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_tolower00
static int tolua_SDL_SDL_SDL_tolower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int X = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_tolower(X);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_tolower'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_memset */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_memset00
static int tolua_SDL_SDL_SDL_memset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* dst = ((void*)  tolua_touserdata(tolua_S,1,0));
		int c = ((int)  tolua_tonumber(tolua_S,2,0));
		unsigned int len = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			void* tolua_ret = (void*)  SDL_memset(dst,c,len);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_memset'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: _SDL_memcpy */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_memcpy00
static int tolua_SDL_SDL_SDL_memcpy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* dst = ((void*)  tolua_touserdata(tolua_S,1,0));
		const void* src = ((const void*)  tolua_touserdata(tolua_S,2,0));
		unsigned int len = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			void* tolua_ret = (void*)  _SDL_memcpy(dst,src,len);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_memcpy'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: _SDL_revcpy */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_revcpy00
static int tolua_SDL_SDL_SDL_revcpy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* dst = ((void*)  tolua_touserdata(tolua_S,1,0));
		const void* src = ((const void*)  tolua_touserdata(tolua_S,2,0));
		unsigned int len = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			void* tolua_ret = (void*)  _SDL_revcpy(dst,src,len);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_revcpy'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_memmove */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_memmove00
static int tolua_SDL_SDL_SDL_memmove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* dst = ((void*)  tolua_touserdata(tolua_S,1,0));
		const void* src = ((const void*)  tolua_touserdata(tolua_S,2,0));
		unsigned int len = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			void* tolua_ret = (void*)  SDL_memmove(dst,src,len);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_memmove'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_memcmp */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_memcmp00
static int tolua_SDL_SDL_SDL_memcmp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const void* s1 = ((const void*)  tolua_touserdata(tolua_S,1,0));
		const void* s2 = ((const void*)  tolua_touserdata(tolua_S,2,0));
		unsigned int len = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_memcmp(s1,s2,len);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_memcmp'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strlen */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strlen00
static int tolua_SDL_SDL_SDL_strlen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			unsigned int tolua_ret = ( unsigned int)  SDL_strlen(str);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strlen'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strlcpy */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strlcpy00
static int tolua_SDL_SDL_SDL_strlcpy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* dst = ((char*)  tolua_tostring(tolua_S,1,0));
		const char* src = ((const char*)  tolua_tostring(tolua_S,2,0));
		unsigned int maxlen = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			unsigned int tolua_ret = ( unsigned int)  SDL_strlcpy(dst,src,maxlen);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strlcpy'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strlcat */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strlcat00
static int tolua_SDL_SDL_SDL_strlcat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* dst = ((char*)  tolua_tostring(tolua_S,1,0));
		const char* src = ((const char*)  tolua_tostring(tolua_S,2,0));
		unsigned int maxlen = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			unsigned int tolua_ret = ( unsigned int)  SDL_strlcat(dst,src,maxlen);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strlcat'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strdup */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strdup00
static int tolua_SDL_SDL_SDL_strdup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  SDL_strdup(str);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strdup'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strrev */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strrev00
static int tolua_SDL_SDL_SDL_strrev00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* str = ((char*)  tolua_tostring(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  SDL_strrev(str);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strrev'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strupr */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strupr00
static int tolua_SDL_SDL_SDL_strupr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* str = ((char*)  tolua_tostring(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  SDL_strupr(str);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strupr'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strlwr */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strlwr00
static int tolua_SDL_SDL_SDL_strlwr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* str = ((char*)  tolua_tostring(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  SDL_strlwr(str);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strlwr'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strchr */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strchr00
static int tolua_SDL_SDL_SDL_strchr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		int c = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			char* tolua_ret = (char*)  SDL_strchr(str,c);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strchr'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strrchr */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strrchr00
static int tolua_SDL_SDL_SDL_strrchr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		int c = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			char* tolua_ret = (char*)  SDL_strrchr(str,c);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strrchr'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strstr */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strstr00
static int tolua_SDL_SDL_SDL_strstr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* haystack = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* needle = ((const char*)  tolua_tostring(tolua_S,2,0));
		{
			char* tolua_ret = (char*)  SDL_strstr(haystack,needle);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strstr'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_itoa */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_itoa00
static int tolua_SDL_SDL_SDL_itoa00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int value = ((int)  tolua_tonumber(tolua_S,1,0));
		char* str = ((char*)  tolua_tostring(tolua_S,2,0));
		int radix = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			char* tolua_ret = (char*)  SDL_itoa(value,str,radix);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_itoa'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ltoa */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ltoa00
static int tolua_SDL_SDL_SDL_ltoa00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		long value = ((long)  tolua_tonumber(tolua_S,1,0));
		char* str = ((char*)  tolua_tostring(tolua_S,2,0));
		int radix = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			char* tolua_ret = (char*)  SDL_ltoa(value,str,radix);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ltoa'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_uitoa */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_uitoa00
static int tolua_SDL_SDL_SDL_uitoa00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int value = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
		char* str = ((char*)  tolua_tostring(tolua_S,2,0));
		int radix = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			char* tolua_ret = (char*)  SDL_uitoa(value,str,radix);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_uitoa'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ultoa */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ultoa00
static int tolua_SDL_SDL_SDL_ultoa00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned long value = ((unsigned long)  tolua_tonumber(tolua_S,1,0));
		char* str = ((char*)  tolua_tostring(tolua_S,2,0));
		int radix = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			char* tolua_ret = (char*)  SDL_ultoa(value,str,radix);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ultoa'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strtol */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strtol00
static int tolua_SDL_SDL_SDL_strtol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		char* endp = ((char*)  tolua_tostring(tolua_S,2,0));
		int base = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			long tolua_ret = (long)  SDL_strtol(str,&endp,base);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushstring(tolua_S,(const char*)endp);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strtol'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strtoul */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strtoul00
static int tolua_SDL_SDL_SDL_strtoul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		char* endp = ((char*)  tolua_tostring(tolua_S,2,0));
		int base = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			unsigned long tolua_ret = (unsigned long)  SDL_strtoul(str,&endp,base);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushstring(tolua_S,(const char*)endp);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strtoul'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strtod */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strtod00
static int tolua_SDL_SDL_SDL_strtod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		char* endp = ((char*)  tolua_tostring(tolua_S,2,0));
		{
			double tolua_ret = (double)  SDL_strtod(str,&endp);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushstring(tolua_S,(const char*)endp);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strtod'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_atoi */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_atoi00
static int tolua_SDL_SDL_SDL_atoi00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_atoi(str);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_atoi'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_atof */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_atof00
static int tolua_SDL_SDL_SDL_atof00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			double tolua_ret = (double)  SDL_atof(str);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_atof'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strcmp */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strcmp00
static int tolua_SDL_SDL_SDL_strcmp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str1 = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* str2 = ((const char*)  tolua_tostring(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_strcmp(str1,str2);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strcmp'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strncmp */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strncmp00
static int tolua_SDL_SDL_SDL_strncmp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str1 = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* str2 = ((const char*)  tolua_tostring(tolua_S,2,0));
		unsigned int maxlen = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_strncmp(str1,str2,maxlen);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strncmp'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strcasecmp */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strcasecmp00
static int tolua_SDL_SDL_SDL_strcasecmp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str1 = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* str2 = ((const char*)  tolua_tostring(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_strcasecmp(str1,str2);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strcasecmp'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_strncasecmp */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_strncasecmp00
static int tolua_SDL_SDL_SDL_strncasecmp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* str1 = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* str2 = ((const char*)  tolua_tostring(tolua_S,2,0));
		unsigned int maxlen = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_strncasecmp(str1,str2,maxlen);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_strncasecmp'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_iconv_open */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_iconv_open00
static int tolua_SDL_SDL_SDL_iconv_open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* tocode = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* fromcode = ((const char*)  tolua_tostring(tolua_S,2,0));
		{
			struct _SDL_iconv_t* tolua_ret = (struct _SDL_iconv_t*)  SDL_iconv_open(tocode,fromcode);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_SDL_iconv_t");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_iconv_open'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_iconv_close */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_iconv_close00
static int tolua_SDL_SDL_SDL_iconv_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_iconv_t",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_iconv_t* cd = ((struct _SDL_iconv_t*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_iconv_close(cd);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_iconv_close'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_iconv */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_iconv00
static int tolua_SDL_SDL_SDL_iconv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_iconv_t",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isstring(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,6,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_iconv_t* cd = ((struct _SDL_iconv_t*)  tolua_tousertype(tolua_S,1,0));
		const char* inbuf = ((const char*)  tolua_tostring(tolua_S,2,0));
		unsigned int inbytesleft = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
		char* outbuf = ((char*)  tolua_tostring(tolua_S,4,0));
		unsigned int outbytesleft = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
		{
			unsigned int tolua_ret = ( unsigned int)  SDL_iconv(cd,&inbuf,&inbytesleft,&outbuf,&outbytesleft);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushstring(tolua_S,(const char*)inbuf);
			tolua_pushnumber(tolua_S,(lua_Number)inbytesleft);
			tolua_pushstring(tolua_S,(const char*)outbuf);
			tolua_pushnumber(tolua_S,(lua_Number)outbytesleft);
		}
	}
	return 5;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_iconv'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_iconv_string */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_iconv_string00
static int tolua_SDL_SDL_SDL_iconv_string00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isstring(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* tocode = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* fromcode = ((const char*)  tolua_tostring(tolua_S,2,0));
		char* inbuf = ((char*)  tolua_tostring(tolua_S,3,0));
		unsigned int inbytesleft = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
		{
			char* tolua_ret = (char*)  SDL_iconv_string(tocode,fromcode,inbuf,inbytesleft);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_iconv_string'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_iconv_string */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_utf8_decode00
static int tolua_SDL_SDL_SDL_utf8_decode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		size_t len = 0;
		size_t pos = 0;
		unsigned long value = 0;
		unsigned long index = 1;
		const char* str = ((const char*)  lua_tolstring(tolua_S,1,&len));
		{
			lua_newtable(tolua_S);
			while (pos<len){
				if ((str[pos]	   & 0x80)==0x00){
					value = (unsigned long)(str[pos] & 0x7F);
					//0xxxxxxx
					pos++;
				}else if ((str[pos] & 0xE0)==0xC0){
					value = (unsigned long)((str[pos] & 0x1F)<<6 | (str[pos+1] & 0x3F));
					//110xxxxx 10xxxxxx
					pos+=2;
				}else if ((str[pos] & 0xF0)==0xE0){
					value = (unsigned long)((str[pos] & 0x0F)<<12 | (str[pos+1] & 0x3F)<<6 | (str[pos+2] & 0x3F));
					//1110xxxx 10xxxxxx 10xxxxxx
					pos+=3;
				}else if ((str[pos] & 0xF8)==0xF0){
					value = (unsigned long)((str[pos] & 0x07)<<18 | (str[pos+1] & 0x3F)<<12 | (str[pos+2] & 0x3F)<<6 | (str[pos+3] & 0x3F));
					//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
					pos+=4;
				}else if ((str[pos] & 0xFC)==0xF8){
					value = (unsigned long)((str[pos] & 0x03)<<24 | (str[pos+1] & 0x3F)<<18 | (str[pos+2] & 0x3F)<<12 | (str[pos+3] & 0x3F)<<6 | (str[pos+4] & 0x3F));
					//111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
					pos+=5;
				}else if ((str[pos] & 0xFE)==0xFC){
					value = (unsigned long)((str[pos] & 0x01)<<30 | (str[pos+1] & 0x3F)<<24 | (str[pos+2] & 0x3F)<<18 | (str[pos+3] & 0x3F)<<12 | (str[pos+4] & 0x3F)<<6 | (str[pos+5] & 0x3F));
					//1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
					pos+=6;
				}
				lua_pushinteger(tolua_S,index);
				lua_pushinteger(tolua_S,value);
				lua_settable(tolua_S,-3);
				
				if (pos>=len)
					break;
				index++;
			}
			lua_pushinteger(tolua_S,index);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_utf8_decode'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_iconv_utf8_locale */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_iconv_utf8_locale00
static int tolua_SDL_SDL_SDL_iconv_utf8_locale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* inbuf = ((char*)  tolua_tostring(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  SDL_iconv_utf8_locale(inbuf);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_iconv_utf8_locale'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_iconv_utf8_ucs2 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_iconv_utf8_ucs200
static int tolua_SDL_SDL_SDL_iconv_utf8_ucs200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* inbuf = ((char*)  tolua_tostring(tolua_S,1,0));
		{
			void* tolua_ret = (void*)  SDL_iconv_utf8_ucs2(inbuf);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_iconv_utf8_ucs2'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_iconv_utf8_ucs4 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_iconv_utf8_ucs400
static int tolua_SDL_SDL_SDL_iconv_utf8_ucs400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* inbuf = ((char*)  tolua_tostring(tolua_S,1,0));
		{
			void* tolua_ret = (void*)  SDL_iconv_utf8_ucs4(inbuf);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_iconv_utf8_ucs4'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: freq of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_freq
static int tolua_get_SDL_AudioSpec_freq(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'freq'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->freq);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: freq of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_freq
static int tolua_set_SDL_AudioSpec_freq(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'freq'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->freq = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: format of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_unsigned_format
static int tolua_get_SDL_AudioSpec_unsigned_format(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'format'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->format);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: format of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_unsigned_format
static int tolua_set_SDL_AudioSpec_unsigned_format(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'format'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->format = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: channels of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_unsigned_channels
static int tolua_get_SDL_AudioSpec_unsigned_channels(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'channels'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->channels);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: channels of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_unsigned_channels
static int tolua_set_SDL_AudioSpec_unsigned_channels(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'channels'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->channels = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: silence of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_unsigned_silence
static int tolua_get_SDL_AudioSpec_unsigned_silence(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'silence'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->silence);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: silence of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_unsigned_silence
static int tolua_set_SDL_AudioSpec_unsigned_silence(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'silence'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->silence = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: samples of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_unsigned_samples
static int tolua_get_SDL_AudioSpec_unsigned_samples(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'samples'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->samples);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: samples of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_unsigned_samples
static int tolua_set_SDL_AudioSpec_unsigned_samples(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'samples'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->samples = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: padding of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_unsigned_padding
static int tolua_get_SDL_AudioSpec_unsigned_padding(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'padding'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->padding);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: padding of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_unsigned_padding
static int tolua_set_SDL_AudioSpec_unsigned_padding(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'padding'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->padding = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: size of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_unsigned_size
static int tolua_get_SDL_AudioSpec_unsigned_size(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->size);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: size of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_unsigned_size
static int tolua_set_SDL_AudioSpec_unsigned_size(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->size = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: callback of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_callback
static int tolua_get_SDL_AudioSpec_callback(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'callback'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->callback);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: callback of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_callback
static int tolua_set_SDL_AudioSpec_callback(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'callback'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->callback = ((void (__cdecl *)(void *,Uint8 *,int))  tolua_touserdata(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: userdata of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioSpec_userdata
static int tolua_get_SDL_AudioSpec_userdata(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'userdata'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->userdata);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: userdata of class  SDL_AudioSpec */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioSpec_userdata
static int tolua_set_SDL_AudioSpec_userdata(lua_State* tolua_S)
{
	SDL_AudioSpec* self = (SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'userdata'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->userdata = ((void*)  tolua_touserdata(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: needed of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_needed
static int tolua_get_SDL_AudioCVT_needed(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'needed'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->needed);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: needed of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_needed
static int tolua_set_SDL_AudioCVT_needed(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'needed'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->needed = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: src_format of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_unsigned_src_format
static int tolua_get_SDL_AudioCVT_unsigned_src_format(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'src_format'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->src_format);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: src_format of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_unsigned_src_format
static int tolua_set_SDL_AudioCVT_unsigned_src_format(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'src_format'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->src_format = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dst_format of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_unsigned_dst_format
static int tolua_get_SDL_AudioCVT_unsigned_dst_format(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dst_format'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->dst_format);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dst_format of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_unsigned_dst_format
static int tolua_set_SDL_AudioCVT_unsigned_dst_format(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dst_format'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->dst_format = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rate_incr of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_rate_incr
static int tolua_get_SDL_AudioCVT_rate_incr(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rate_incr'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->rate_incr);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rate_incr of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_rate_incr
static int tolua_set_SDL_AudioCVT_rate_incr(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rate_incr'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->rate_incr = ((double)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: buf of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_buf
static int tolua_get_SDL_AudioCVT_buf(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buf'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->buf);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: buf of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_buf
static int tolua_set_SDL_AudioCVT_buf(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buf'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->buf = ((Uint8*)  tolua_touserdata(tolua_S,2,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: len of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_len
static int tolua_get_SDL_AudioCVT_len(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->len);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: len of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_len
static int tolua_set_SDL_AudioCVT_len(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->len = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: len_cvt of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_len_cvt
static int tolua_get_SDL_AudioCVT_len_cvt(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len_cvt'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->len_cvt);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: len_cvt of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_len_cvt
static int tolua_set_SDL_AudioCVT_len_cvt(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len_cvt'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->len_cvt = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: len_mult of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_len_mult
static int tolua_get_SDL_AudioCVT_len_mult(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len_mult'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->len_mult);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: len_mult of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_len_mult
static int tolua_set_SDL_AudioCVT_len_mult(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len_mult'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->len_mult = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: len_ratio of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_get_SDL_AudioCVT_len_ratio
static int tolua_get_SDL_AudioCVT_len_ratio(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len_ratio'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->len_ratio);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: len_ratio of class  SDL_AudioCVT */
#ifndef TOLUA_DISABLE_tolua_set_SDL_AudioCVT_len_ratio
static int tolua_set_SDL_AudioCVT_len_ratio(lua_State* tolua_S)
{
	SDL_AudioCVT* self = (SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len_ratio'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->len_ratio = ((double)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_AudioDriverName */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_AudioDriverName00
static int tolua_SDL_SDL_SDL_AudioDriverName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* namebuf = ((char*)  tolua_tostring(tolua_S,1,0));
		int maxlen = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			char* tolua_ret = (char*)  SDL_AudioDriverName(namebuf,maxlen);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_AudioDriverName'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_OpenAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_OpenAudio00
static int tolua_SDL_SDL_SDL_OpenAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_AudioSpec",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_AudioSpec",1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_AudioSpec* desired = ((SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0));
		SDL_AudioSpec* obtained = ((SDL_AudioSpec*)  tolua_tousertype(tolua_S,2,NULL));
		{
			int tolua_ret = (int)  SDL_OpenAudio(desired,obtained);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_OpenAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetAudioStatus */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetAudioStatus00
static int tolua_SDL_SDL_SDL_GetAudioStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_audiostatus tolua_ret = (SDL_audiostatus)  SDL_GetAudioStatus();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetAudioStatus'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_PauseAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_PauseAudio00
static int tolua_SDL_SDL_SDL_PauseAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int pause_on = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			SDL_PauseAudio(pause_on);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_PauseAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: _SDL_LoadWAV_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL__SDL_LoadWAV_RW00
static int tolua_SDL_SDL__SDL_LoadWAV_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_AudioSpec",0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,6,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		int freesrc = ((int)  tolua_tonumber(tolua_S,2,0));
		SDL_AudioSpec* spec = ((SDL_AudioSpec*)  tolua_tousertype(tolua_S,3,0));
		void* audio_buf = ((void*)  tolua_touserdata(tolua_S,4,0));
		unsigned int audio_len = ((  unsigned int)  tolua_tonumber(tolua_S,5,0));
		{
			SDL_AudioSpec* tolua_ret = (SDL_AudioSpec*)  _SDL_LoadWAV_RW(src,freesrc,spec,&audio_buf,&audio_len);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_AudioSpec");
			tolua_pushuserdata(tolua_S,(void*)audio_buf);
			tolua_pushnumber(tolua_S,(lua_Number)audio_len);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function '_SDL_LoadWAV_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: _SDL_LoadWAV */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_LoadWAV00
static int tolua_SDL_SDL_SDL_LoadWAV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_AudioSpec",0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
		SDL_AudioSpec* spec = ((SDL_AudioSpec*)  tolua_tousertype(tolua_S,2,0));
		void* audio_buf = ((void*)  tolua_touserdata(tolua_S,3,0));
		unsigned int audio_len = ((  unsigned int)  tolua_tonumber(tolua_S,4,0));
		{
			SDL_AudioSpec* tolua_ret = (SDL_AudioSpec*)  _SDL_LoadWAV(file,spec,&audio_buf,&audio_len);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_AudioSpec");
			tolua_pushuserdata(tolua_S,(void*)audio_buf);
			tolua_pushnumber(tolua_S,(lua_Number)audio_len);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_LoadWAV'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_FreeWAV */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_FreeWAV00
static int tolua_SDL_SDL_SDL_FreeWAV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* audio_buf = ((void*)  tolua_touserdata(tolua_S,1,0));
		{
			SDL_FreeWAV((Uint8*)audio_buf);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_FreeWAV'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_BuildAudioCVT */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_BuildAudioCVT00
static int tolua_SDL_SDL_SDL_BuildAudioCVT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_AudioCVT",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,6,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,7,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,8,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_AudioCVT* cvt = ((SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0));
		unsigned short src_format = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		unsigned char src_channels = ((  unsigned char)  tolua_tonumber(tolua_S,3,0));
		int src_rate = ((int)  tolua_tonumber(tolua_S,4,0));
		unsigned short dst_format = ((  unsigned short)  tolua_tonumber(tolua_S,5,0));
		unsigned char dst_channels = ((  unsigned char)  tolua_tonumber(tolua_S,6,0));
		int dst_rate = ((int)  tolua_tonumber(tolua_S,7,0));
		{
			int tolua_ret = (int)  SDL_BuildAudioCVT(cvt,src_format,src_channels,src_rate,dst_format,dst_channels,dst_rate);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_BuildAudioCVT'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ConvertAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ConvertAudio00
static int tolua_SDL_SDL_SDL_ConvertAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_AudioCVT",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_AudioCVT* cvt = ((SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_ConvertAudio(cvt);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ConvertAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_MixAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_MixAudio00
static int tolua_SDL_SDL_SDL_MixAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* dst = ((void*)  tolua_touserdata(tolua_S,1,0));
		const void* src = ((const void*)  tolua_touserdata(tolua_S,2,0));
		unsigned int len = ((  unsigned int)  tolua_tonumber(tolua_S,3,0));
		int volume = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			SDL_MixAudio((Uint8*)dst,(const Uint8*)src,len,volume);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_MixAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_LockAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_LockAudio00
static int tolua_SDL_SDL_SDL_LockAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_LockAudio();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_LockAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_UnlockAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_UnlockAudio00
static int tolua_SDL_SDL_SDL_UnlockAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_UnlockAudio();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_UnlockAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CloseAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CloseAudio00
static int tolua_SDL_SDL_SDL_CloseAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_CloseAudio();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CloseAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: id of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CDtrack_unsigned_id
static int tolua_get_SDL_CDtrack_unsigned_id(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->id);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: id of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CDtrack_unsigned_id
static int tolua_set_SDL_CDtrack_unsigned_id(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->id = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CDtrack_unsigned_type
static int tolua_get_SDL_CDtrack_unsigned_type(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CDtrack_unsigned_type
static int tolua_set_SDL_CDtrack_unsigned_type(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: unused of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CDtrack_unsigned_unused
static int tolua_get_SDL_CDtrack_unsigned_unused(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unused'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->unused);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: unused of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CDtrack_unsigned_unused
static int tolua_set_SDL_CDtrack_unsigned_unused(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unused'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->unused = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: length of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CDtrack_unsigned_length
static int tolua_get_SDL_CDtrack_unsigned_length(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->length);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: length of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CDtrack_unsigned_length
static int tolua_set_SDL_CDtrack_unsigned_length(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->length = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: offset of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CDtrack_unsigned_offset
static int tolua_get_SDL_CDtrack_unsigned_offset(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offset'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->offset);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: offset of class  SDL_CDtrack */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CDtrack_unsigned_offset
static int tolua_set_SDL_CDtrack_unsigned_offset(lua_State* tolua_S)
{
	SDL_CDtrack* self = (SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offset'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->offset = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: id of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CD_id
static int tolua_get_SDL_CD_id(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->id);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: id of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CD_id
static int tolua_set_SDL_CD_id(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->id = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: status of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CD_status
static int tolua_get_SDL_CD_status(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'status'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->status);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: status of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CD_status
static int tolua_set_SDL_CD_status(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'status'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->status = ((CDstatus) (int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: numtracks of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CD_numtracks
static int tolua_get_SDL_CD_numtracks(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'numtracks'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->numtracks);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: numtracks of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CD_numtracks
static int tolua_set_SDL_CD_numtracks(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'numtracks'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->numtracks = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cur_track of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CD_cur_track
static int tolua_get_SDL_CD_cur_track(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cur_track'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->cur_track);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cur_track of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CD_cur_track
static int tolua_set_SDL_CD_cur_track(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cur_track'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->cur_track = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cur_frame of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_get_SDL_CD_cur_frame
static int tolua_get_SDL_CD_cur_frame(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cur_frame'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->cur_frame);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cur_frame of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_set_SDL_CD_cur_frame
static int tolua_set_SDL_CD_cur_frame(lua_State* tolua_S)
{
	SDL_CD* self = (SDL_CD*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cur_frame'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->cur_frame = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: track of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_get_SDL_SDL_SDL_CD_track
static int tolua_get_SDL_SDL_SDL_CD_track(lua_State* tolua_S)
{
	int tolua_index;
	SDL_CD* self;
	lua_pushstring(tolua_S,".self");
	lua_rawget(tolua_S,1);
	self = (SDL_CD*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
	{
		tolua_Error tolua_err;
		if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
			tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
	}
#endif
	tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
	if (tolua_index<0)
		tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->track[tolua_index],"SDL_CDtrack");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: track of class  SDL_CD */
#ifndef TOLUA_DISABLE_tolua_set_SDL_SDL_SDL_CD_track
static int tolua_set_SDL_SDL_SDL_CD_track(lua_State* tolua_S)
{
	int tolua_index;
	SDL_CD* self;
	lua_pushstring(tolua_S,".self");
	lua_rawget(tolua_S,1);
	self = (SDL_CD*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
	{
		tolua_Error tolua_err;
		if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
			tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
	}
#endif
	tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
	if (tolua_index<0)
		tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
	self->track[tolua_index] = *((SDL_CDtrack*)  tolua_tousertype(tolua_S,3,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: CD_INDRIVE */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_CD_INDRIVE00
static int tolua_SDL_SDL_CD_INDRIVE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		CDstatus status = ((CDstatus) (int)  tolua_tonumber(tolua_S,1,0));
		{
			SDL_bool tolua_ret = (SDL_bool)  CD_INDRIVE(status);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'CD_INDRIVE'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: FRAMES_TO_MSF */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_FRAMES_TO_MSF00
static int tolua_SDL_SDL_FRAMES_TO_MSF00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int frames = ((int)  tolua_tonumber(tolua_S,1,0));
		int min = ((int)  tolua_tonumber(tolua_S,2,0));
		int sec = ((int)  tolua_tonumber(tolua_S,3,0));
		int fr = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			FRAMES_TO_MSF(frames,&min,&sec,&fr);
			tolua_pushnumber(tolua_S,(lua_Number)min);
			tolua_pushnumber(tolua_S,(lua_Number)sec);
			tolua_pushnumber(tolua_S,(lua_Number)fr);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'FRAMES_TO_MSF'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MSF_TO_FRAMES */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_MSF_TO_FRAMES00
static int tolua_SDL_SDL_MSF_TO_FRAMES00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int min = ((int)  tolua_tonumber(tolua_S,1,0));
		int sec = ((int)  tolua_tonumber(tolua_S,2,0));
		int frac = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  MSF_TO_FRAMES(min,sec,frac);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'MSF_TO_FRAMES'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDNumDrives */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDNumDrives00
static int tolua_SDL_SDL_SDL_CDNumDrives00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  SDL_CDNumDrives();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDNumDrives'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDName */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDName00
static int tolua_SDL_SDL_SDL_CDName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int drive = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			const char* tolua_ret = (const char*)  SDL_CDName(drive);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDName'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDOpen */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDOpen00
static int tolua_SDL_SDL_SDL_CDOpen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int drive = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			SDL_CD* tolua_ret = (SDL_CD*)  SDL_CDOpen(drive);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_CD");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDOpen'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDStatus */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDStatus00
static int tolua_SDL_SDL_SDL_CDStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* cdrom = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		{
			CDstatus tolua_ret = (CDstatus)  SDL_CDStatus(cdrom);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDStatus'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDPlayTracks */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDPlayTracks00
static int tolua_SDL_SDL_SDL_CDPlayTracks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,6,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* cdrom = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		int start_track = ((int)  tolua_tonumber(tolua_S,2,0));
		int start_frame = ((int)  tolua_tonumber(tolua_S,3,0));
		int ntracks = ((int)  tolua_tonumber(tolua_S,4,0));
		int nframes = ((int)  tolua_tonumber(tolua_S,5,0));
		{
			int tolua_ret = (int)  SDL_CDPlayTracks(cdrom,start_track,start_frame,ntracks,nframes);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDPlayTracks'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDPlay */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDPlay00
static int tolua_SDL_SDL_SDL_CDPlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* cdrom = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		int start = ((int)  tolua_tonumber(tolua_S,2,0));
		int length = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_CDPlay(cdrom,start,length);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDPlay'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDPause */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDPause00
static int tolua_SDL_SDL_SDL_CDPause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* cdrom = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_CDPause(cdrom);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDPause'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDResume */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDResume00
static int tolua_SDL_SDL_SDL_CDResume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* cdrom = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_CDResume(cdrom);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDResume'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDStop */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDStop00
static int tolua_SDL_SDL_SDL_CDStop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* cdrom = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_CDStop(cdrom);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDStop'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDEject */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDEject00
static int tolua_SDL_SDL_SDL_CDEject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* cdrom = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_CDEject(cdrom);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDEject'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDClose */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDClose00
static int tolua_SDL_SDL_SDL_CDClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* cdrom = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_CDClose(cdrom);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDClose'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_HasRDTSC */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_HasRDTSC00
static int tolua_SDL_SDL_SDL_HasRDTSC00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_HasRDTSC();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_HasRDTSC'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_HasMMX */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_HasMMX00
static int tolua_SDL_SDL_SDL_HasMMX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_HasMMX();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_HasMMX'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_HasMMXExt */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_HasMMXExt00
static int tolua_SDL_SDL_SDL_HasMMXExt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_HasMMXExt();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_HasMMXExt'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Has3DNow */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Has3DNow00
static int tolua_SDL_SDL_SDL_Has3DNow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_Has3DNow();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Has3DNow'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Has3DNowExt */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Has3DNowExt00
static int tolua_SDL_SDL_SDL_Has3DNowExt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_Has3DNowExt();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Has3DNowExt'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_HasSSE */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_HasSSE00
static int tolua_SDL_SDL_SDL_HasSSE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_HasSSE();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_HasSSE'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_HasSSE2 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_HasSSE200
static int tolua_SDL_SDL_SDL_HasSSE200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_HasSSE2();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_HasSSE2'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_HasAltiVec */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_HasAltiVec00
static int tolua_SDL_SDL_SDL_HasAltiVec00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_HasAltiVec();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_HasAltiVec'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Swap16 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Swap1600
static int tolua_SDL_SDL_SDL_Swap1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned short x = ((  unsigned short)  tolua_tonumber(tolua_S,1,0));
		{
			unsigned short tolua_ret = (  unsigned short)  SDL_Swap16(x);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Swap16'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Swap32 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Swap3200
static int tolua_SDL_SDL_SDL_Swap3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int x = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_Swap32(x);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Swap32'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Pass16 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Pass1600
static int tolua_SDL_SDL_SDL_Pass1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned short x = ((  unsigned short)  tolua_tonumber(tolua_S,1,0));
		{
			unsigned short tolua_ret = (  unsigned short)  SDL_Pass16(x);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Pass16'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Pass32 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Pass3200
static int tolua_SDL_SDL_SDL_Pass3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int x = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_Pass32(x);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Pass32'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetError */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL__SDL_SetError00
static int tolua_SDL_SDL__SDL_SetError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* msg = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			SDL_SetError(msg);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function '_SDL_SetError'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetError */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetError00
static int tolua_SDL_SDL_SDL_GetError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			char* tolua_ret = (char*)  SDL_GetError();
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetError'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ClearError */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ClearError00
static int tolua_SDL_SDL_SDL_ClearError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_ClearError();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ClearError'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetAppState */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetAppState00
static int tolua_SDL_SDL_SDL_GetAppState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			unsigned char tolua_ret = (  unsigned char)  SDL_GetAppState();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetAppState'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scancode of class  SDL_keysym */
#ifndef TOLUA_DISABLE_tolua_get_SDL_keysym_unsigned_scancode
static int tolua_get_SDL_keysym_unsigned_scancode(lua_State* tolua_S)
{
	SDL_keysym* self = (SDL_keysym*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scancode'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->scancode);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scancode of class  SDL_keysym */
#ifndef TOLUA_DISABLE_tolua_set_SDL_keysym_unsigned_scancode
static int tolua_set_SDL_keysym_unsigned_scancode(lua_State* tolua_S)
{
	SDL_keysym* self = (SDL_keysym*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scancode'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->scancode = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sym of class  SDL_keysym */
#ifndef TOLUA_DISABLE_tolua_get_SDL_keysym_sym
static int tolua_get_SDL_keysym_sym(lua_State* tolua_S)
{
	SDL_keysym* self = (SDL_keysym*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sym'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->sym);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sym of class  SDL_keysym */
#ifndef TOLUA_DISABLE_tolua_set_SDL_keysym_sym
static int tolua_set_SDL_keysym_sym(lua_State* tolua_S)
{
	SDL_keysym* self = (SDL_keysym*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sym'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->sym = ((SDLKey) (int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mod of class  SDL_keysym */
#ifndef TOLUA_DISABLE_tolua_get_SDL_keysym_mod
static int tolua_get_SDL_keysym_mod(lua_State* tolua_S)
{
	SDL_keysym* self = (SDL_keysym*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mod'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->mod);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mod of class  SDL_keysym */
#ifndef TOLUA_DISABLE_tolua_set_SDL_keysym_mod
static int tolua_set_SDL_keysym_mod(lua_State* tolua_S)
{
	SDL_keysym* self = (SDL_keysym*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mod'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->mod = ((SDLMod) (int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: unicode of class  SDL_keysym */
#ifndef TOLUA_DISABLE_tolua_get_SDL_keysym_unsigned_unicode
static int tolua_get_SDL_keysym_unsigned_unicode(lua_State* tolua_S)
{
	SDL_keysym* self = (SDL_keysym*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unicode'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->unicode);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: unicode of class  SDL_keysym */
#ifndef TOLUA_DISABLE_tolua_set_SDL_keysym_unsigned_unicode
static int tolua_set_SDL_keysym_unsigned_unicode(lua_State* tolua_S)
{
	SDL_keysym* self = (SDL_keysym*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unicode'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->unicode = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_EnableUNICODE */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_EnableUNICODE00
static int tolua_SDL_SDL_SDL_EnableUNICODE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int enable = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_EnableUNICODE(enable);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_EnableUNICODE'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_EnableKeyRepeat */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_EnableKeyRepeat00
static int tolua_SDL_SDL_SDL_EnableKeyRepeat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int delay = ((int)  tolua_tonumber(tolua_S,1,0));
		int interval = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_EnableKeyRepeat(delay,interval);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_EnableKeyRepeat'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetKeyRepeat */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetKeyRepeat00
static int tolua_SDL_SDL_SDL_GetKeyRepeat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int delay = ((int)  tolua_tonumber(tolua_S,1,0));
		int interval = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			SDL_GetKeyRepeat(&delay,&interval);
			tolua_pushnumber(tolua_S,(lua_Number)delay);
			tolua_pushnumber(tolua_S,(lua_Number)interval);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetKeyRepeat'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetModState */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetModState00
static int tolua_SDL_SDL_SDL_GetModState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDLMod tolua_ret = (SDLMod)  SDL_GetModState();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetModState'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetModState */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetModState00
static int tolua_SDL_SDL_SDL_SetModState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDLMod modstate = ((SDLMod) (int)  tolua_tonumber(tolua_S,1,0));
		{
			SDL_SetModState(modstate);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetModState'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetKeyName */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetKeyName00
static int tolua_SDL_SDL_SDL_GetKeyName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDLKey key = ((SDLKey) (int)  tolua_tonumber(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  SDL_GetKeyName(key);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetKeyName'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: area of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Cursor_area
static int tolua_get_SDL_Cursor_area(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'area'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->area,"SDL_Rect");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: area of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Cursor_area
static int tolua_set_SDL_Cursor_area(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'area'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_Rect",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->area = *((SDL_Rect*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hot_x of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Cursor_hot_x
static int tolua_get_SDL_Cursor_hot_x(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hot_x'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->hot_x);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hot_x of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Cursor_hot_x
static int tolua_set_SDL_Cursor_hot_x(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hot_x'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->hot_x = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hot_y of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Cursor_hot_y
static int tolua_get_SDL_Cursor_hot_y(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hot_y'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->hot_y);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hot_y of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Cursor_hot_y
static int tolua_set_SDL_Cursor_hot_y(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hot_y'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->hot_y = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: data of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Cursor_data
static int tolua_get_SDL_Cursor_data(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->data);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: data of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Cursor_data
static int tolua_set_SDL_Cursor_data(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->data = ((Uint8*)  tolua_touserdata(tolua_S,2,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mask of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Cursor_mask
static int tolua_get_SDL_Cursor_mask(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mask'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->mask);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mask of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Cursor_mask
static int tolua_set_SDL_Cursor_mask(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mask'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->mask = ((Uint8*)  tolua_touserdata(tolua_S,2,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wm_cursor of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Cursor_wm_cursor_ptr
static int tolua_get_SDL_Cursor_wm_cursor_ptr(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wm_cursor'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)self->wm_cursor,"WMcursor");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wm_cursor of class  SDL_Cursor */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Cursor_wm_cursor_ptr
static int tolua_set_SDL_Cursor_wm_cursor_ptr(lua_State* tolua_S)
{
	SDL_Cursor* self = (SDL_Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wm_cursor'",NULL);
	if (!tolua_isusertype(tolua_S,2,"WMcursor",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->wm_cursor = ((WMcursor*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetMouseState */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetMouseState00
static int tolua_SDL_SDL_SDL_GetMouseState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int x = ((int)  tolua_tonumber(tolua_S,1,0));
		int y = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			unsigned char tolua_ret = (  unsigned char)  SDL_GetMouseState(&x,&y);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)x);
			tolua_pushnumber(tolua_S,(lua_Number)y);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetMouseState'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetRelativeMouseState */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetRelativeMouseState00
static int tolua_SDL_SDL_SDL_GetRelativeMouseState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int x = ((int)  tolua_tonumber(tolua_S,1,0));
		int y = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			unsigned char tolua_ret = (  unsigned char)  SDL_GetRelativeMouseState(&x,&y);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)x);
			tolua_pushnumber(tolua_S,(lua_Number)y);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetRelativeMouseState'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WarpMouse */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WarpMouse00
static int tolua_SDL_SDL_SDL_WarpMouse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned short x = ((  unsigned short)  tolua_tonumber(tolua_S,1,0));
		unsigned short y = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		{
			SDL_WarpMouse(x,y);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WarpMouse'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CreateCursor */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CreateCursor00
static int tolua_SDL_SDL_SDL_CreateCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,6,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,7,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* data = ((void*)  tolua_touserdata(tolua_S,1,0));
		void* mask = ((void*)  tolua_touserdata(tolua_S,2,0));
		int w = ((int)  tolua_tonumber(tolua_S,3,0));
		int h = ((int)  tolua_tonumber(tolua_S,4,0));
		int hot_x = ((int)  tolua_tonumber(tolua_S,5,0));
		int hot_y = ((int)  tolua_tonumber(tolua_S,6,0));
		{
			SDL_Cursor* tolua_ret = (SDL_Cursor*)  SDL_CreateCursor((Uint8*)data,(Uint8*)mask,w,h,hot_x,hot_y);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Cursor");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CreateCursor'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetCursor */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetCursor00
static int tolua_SDL_SDL_SDL_SetCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Cursor",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Cursor* cursor = ((SDL_Cursor*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_SetCursor(cursor);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetCursor'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetCursor */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetCursor00
static int tolua_SDL_SDL_SDL_GetCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_Cursor* tolua_ret = (SDL_Cursor*)  SDL_GetCursor();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Cursor");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetCursor'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_FreeCursor */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_FreeCursor00
static int tolua_SDL_SDL_SDL_FreeCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Cursor",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Cursor* cursor = ((SDL_Cursor*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_FreeCursor(cursor);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_FreeCursor'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ShowCursor */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ShowCursor00
static int tolua_SDL_SDL_SDL_ShowCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int toggle = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_ShowCursor(toggle);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ShowCursor'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_NumJoysticks */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_NumJoysticks00
static int tolua_SDL_SDL_SDL_NumJoysticks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  SDL_NumJoysticks();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_NumJoysticks'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickName */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickName00
static int tolua_SDL_SDL_SDL_JoystickName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int device_index = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			const char* tolua_ret = (const char*)  SDL_JoystickName(device_index);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickName'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickOpen */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickOpen00
static int tolua_SDL_SDL_SDL_JoystickOpen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int device_index = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			struct _SDL_Joystick* tolua_ret = ( struct _SDL_Joystick*)  SDL_JoystickOpen(device_index);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_SDL_Joystick");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickOpen'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickOpened */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickOpened00
static int tolua_SDL_SDL_SDL_JoystickOpened00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int device_index = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_JoystickOpened(device_index);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickOpened'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickIndex */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickIndex00
static int tolua_SDL_SDL_SDL_JoystickIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_JoystickIndex(joystick);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickIndex'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickNumAxes */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickNumAxes00
static int tolua_SDL_SDL_SDL_JoystickNumAxes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_JoystickNumAxes(joystick);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickNumAxes'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickNumBalls */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickNumBalls00
static int tolua_SDL_SDL_SDL_JoystickNumBalls00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_JoystickNumBalls(joystick);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickNumBalls'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickNumHats */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickNumHats00
static int tolua_SDL_SDL_SDL_JoystickNumHats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_JoystickNumHats(joystick);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickNumHats'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickNumButtons */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickNumButtons00
static int tolua_SDL_SDL_SDL_JoystickNumButtons00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_JoystickNumButtons(joystick);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickNumButtons'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickUpdate */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickUpdate00
static int tolua_SDL_SDL_SDL_JoystickUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_JoystickUpdate();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickUpdate'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickEventState */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickEventState00
static int tolua_SDL_SDL_SDL_JoystickEventState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int state = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_JoystickEventState(state);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickEventState'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickGetAxis */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickGetAxis00
static int tolua_SDL_SDL_SDL_JoystickGetAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		int axis = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			signed short tolua_ret = (  signed short)  SDL_JoystickGetAxis(joystick,axis);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickGetAxis'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickGetHat */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickGetHat00
static int tolua_SDL_SDL_SDL_JoystickGetHat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		int hat = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			unsigned char tolua_ret = (  unsigned char)  SDL_JoystickGetHat(joystick,hat);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickGetHat'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickGetBall */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickGetBall00
static int tolua_SDL_SDL_SDL_JoystickGetBall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		int ball = ((int)  tolua_tonumber(tolua_S,2,0));
		int dx = ((int)  tolua_tonumber(tolua_S,3,0));
		int dy = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  SDL_JoystickGetBall(joystick,ball,&dx,&dy);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)dx);
			tolua_pushnumber(tolua_S,(lua_Number)dy);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickGetBall'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickGetButton */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickGetButton00
static int tolua_SDL_SDL_SDL_JoystickGetButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		int button = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			unsigned char tolua_ret = (  unsigned char)  SDL_JoystickGetButton(joystick,button);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickGetButton'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_JoystickClose */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_JoystickClose00
static int tolua_SDL_SDL_SDL_JoystickClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_Joystick",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_Joystick* joystick = (( struct _SDL_Joystick*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_JoystickClose(joystick);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_JoystickClose'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_QuitRequested */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_QuitRequested00
static int tolua_SDL_SDL_SDL_QuitRequested00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  SDL_QuitRequested();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_QuitRequested'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_ActiveEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_ActiveEvent_unsigned_type
static int tolua_get_SDL_ActiveEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_ActiveEvent* self = (SDL_ActiveEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_ActiveEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_ActiveEvent_unsigned_type
static int tolua_set_SDL_ActiveEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_ActiveEvent* self = (SDL_ActiveEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: gain of class  SDL_ActiveEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_ActiveEvent_unsigned_gain
static int tolua_get_SDL_ActiveEvent_unsigned_gain(lua_State* tolua_S)
{
	SDL_ActiveEvent* self = (SDL_ActiveEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gain'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->gain);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: gain of class  SDL_ActiveEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_ActiveEvent_unsigned_gain
static int tolua_set_SDL_ActiveEvent_unsigned_gain(lua_State* tolua_S)
{
	SDL_ActiveEvent* self = (SDL_ActiveEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gain'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->gain = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: state of class  SDL_ActiveEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_ActiveEvent_unsigned_state
static int tolua_get_SDL_ActiveEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_ActiveEvent* self = (SDL_ActiveEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->state);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: state of class  SDL_ActiveEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_ActiveEvent_unsigned_state
static int tolua_set_SDL_ActiveEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_ActiveEvent* self = (SDL_ActiveEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->state = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_KeyboardEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_KeyboardEvent_unsigned_type
static int tolua_get_SDL_KeyboardEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_KeyboardEvent* self = (SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_KeyboardEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_KeyboardEvent_unsigned_type
static int tolua_set_SDL_KeyboardEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_KeyboardEvent* self = (SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: which of class  SDL_KeyboardEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_KeyboardEvent_unsigned_which
static int tolua_get_SDL_KeyboardEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_KeyboardEvent* self = (SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->which);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: which of class  SDL_KeyboardEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_KeyboardEvent_unsigned_which
static int tolua_set_SDL_KeyboardEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_KeyboardEvent* self = (SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->which = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: state of class  SDL_KeyboardEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_KeyboardEvent_unsigned_state
static int tolua_get_SDL_KeyboardEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_KeyboardEvent* self = (SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->state);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: state of class  SDL_KeyboardEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_KeyboardEvent_unsigned_state
static int tolua_set_SDL_KeyboardEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_KeyboardEvent* self = (SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->state = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: keysym of class  SDL_KeyboardEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_KeyboardEvent_keysym
static int tolua_get_SDL_KeyboardEvent_keysym(lua_State* tolua_S)
{
	SDL_KeyboardEvent* self = (SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'keysym'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->keysym,"SDL_keysym");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: keysym of class  SDL_KeyboardEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_KeyboardEvent_keysym
static int tolua_set_SDL_KeyboardEvent_keysym(lua_State* tolua_S)
{
	SDL_KeyboardEvent* self = (SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'keysym'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_keysym",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->keysym = *((SDL_keysym*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseMotionEvent_unsigned_type
static int tolua_get_SDL_MouseMotionEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseMotionEvent_unsigned_type
static int tolua_set_SDL_MouseMotionEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: which of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseMotionEvent_unsigned_which
static int tolua_get_SDL_MouseMotionEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->which);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: which of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseMotionEvent_unsigned_which
static int tolua_set_SDL_MouseMotionEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->which = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: state of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseMotionEvent_unsigned_state
static int tolua_get_SDL_MouseMotionEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->state);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: state of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseMotionEvent_unsigned_state
static int tolua_set_SDL_MouseMotionEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->state = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseMotionEvent_unsigned_x
static int tolua_get_SDL_MouseMotionEvent_unsigned_x(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->x);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseMotionEvent_unsigned_x
static int tolua_set_SDL_MouseMotionEvent_unsigned_x(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->x = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseMotionEvent_unsigned_y
static int tolua_get_SDL_MouseMotionEvent_unsigned_y(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->y);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseMotionEvent_unsigned_y
static int tolua_set_SDL_MouseMotionEvent_unsigned_y(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->y = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: xrel of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseMotionEvent_xrel
static int tolua_get_SDL_MouseMotionEvent_xrel(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'xrel'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->xrel);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: xrel of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseMotionEvent_xrel
static int tolua_set_SDL_MouseMotionEvent_xrel(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'xrel'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->xrel = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: yrel of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseMotionEvent_yrel
static int tolua_get_SDL_MouseMotionEvent_yrel(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'yrel'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->yrel);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: yrel of class  SDL_MouseMotionEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseMotionEvent_yrel
static int tolua_set_SDL_MouseMotionEvent_yrel(lua_State* tolua_S)
{
	SDL_MouseMotionEvent* self = (SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'yrel'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->yrel = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseButtonEvent_unsigned_type
static int tolua_get_SDL_MouseButtonEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseButtonEvent_unsigned_type
static int tolua_set_SDL_MouseButtonEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: which of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseButtonEvent_unsigned_which
static int tolua_get_SDL_MouseButtonEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->which);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: which of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseButtonEvent_unsigned_which
static int tolua_set_SDL_MouseButtonEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->which = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: button of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseButtonEvent_unsigned_button
static int tolua_get_SDL_MouseButtonEvent_unsigned_button(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'button'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->button);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: button of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseButtonEvent_unsigned_button
static int tolua_set_SDL_MouseButtonEvent_unsigned_button(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'button'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->button = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: state of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseButtonEvent_unsigned_state
static int tolua_get_SDL_MouseButtonEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->state);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: state of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseButtonEvent_unsigned_state
static int tolua_set_SDL_MouseButtonEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->state = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseButtonEvent_unsigned_x
static int tolua_get_SDL_MouseButtonEvent_unsigned_x(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->x);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseButtonEvent_unsigned_x
static int tolua_set_SDL_MouseButtonEvent_unsigned_x(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->x = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MouseButtonEvent_unsigned_y
static int tolua_get_SDL_MouseButtonEvent_unsigned_y(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->y);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  SDL_MouseButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_MouseButtonEvent_unsigned_y
static int tolua_set_SDL_MouseButtonEvent_unsigned_y(lua_State* tolua_S)
{
	SDL_MouseButtonEvent* self = (SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->y = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_JoyAxisEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyAxisEvent_unsigned_type
static int tolua_get_SDL_JoyAxisEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_JoyAxisEvent* self = (SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_JoyAxisEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyAxisEvent_unsigned_type
static int tolua_set_SDL_JoyAxisEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_JoyAxisEvent* self = (SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: which of class  SDL_JoyAxisEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyAxisEvent_unsigned_which
static int tolua_get_SDL_JoyAxisEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_JoyAxisEvent* self = (SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->which);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: which of class  SDL_JoyAxisEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyAxisEvent_unsigned_which
static int tolua_set_SDL_JoyAxisEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_JoyAxisEvent* self = (SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->which = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: axis of class  SDL_JoyAxisEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyAxisEvent_unsigned_axis
static int tolua_get_SDL_JoyAxisEvent_unsigned_axis(lua_State* tolua_S)
{
	SDL_JoyAxisEvent* self = (SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'axis'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->axis);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: axis of class  SDL_JoyAxisEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyAxisEvent_unsigned_axis
static int tolua_set_SDL_JoyAxisEvent_unsigned_axis(lua_State* tolua_S)
{
	SDL_JoyAxisEvent* self = (SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'axis'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->axis = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: value of class  SDL_JoyAxisEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyAxisEvent_value
static int tolua_get_SDL_JoyAxisEvent_value(lua_State* tolua_S)
{
	SDL_JoyAxisEvent* self = (SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'value'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->value);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: value of class  SDL_JoyAxisEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyAxisEvent_value
static int tolua_set_SDL_JoyAxisEvent_value(lua_State* tolua_S)
{
	SDL_JoyAxisEvent* self = (SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'value'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->value = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyBallEvent_unsigned_type
static int tolua_get_SDL_JoyBallEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyBallEvent_unsigned_type
static int tolua_set_SDL_JoyBallEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: which of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyBallEvent_unsigned_which
static int tolua_get_SDL_JoyBallEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->which);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: which of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyBallEvent_unsigned_which
static int tolua_set_SDL_JoyBallEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->which = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ball of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyBallEvent_unsigned_ball
static int tolua_get_SDL_JoyBallEvent_unsigned_ball(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ball'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->ball);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ball of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyBallEvent_unsigned_ball
static int tolua_set_SDL_JoyBallEvent_unsigned_ball(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ball'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->ball = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: xrel of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyBallEvent_xrel
static int tolua_get_SDL_JoyBallEvent_xrel(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'xrel'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->xrel);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: xrel of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyBallEvent_xrel
static int tolua_set_SDL_JoyBallEvent_xrel(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'xrel'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->xrel = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: yrel of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyBallEvent_yrel
static int tolua_get_SDL_JoyBallEvent_yrel(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'yrel'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->yrel);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: yrel of class  SDL_JoyBallEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyBallEvent_yrel
static int tolua_set_SDL_JoyBallEvent_yrel(lua_State* tolua_S)
{
	SDL_JoyBallEvent* self = (SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'yrel'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->yrel = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_JoyHatEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyHatEvent_unsigned_type
static int tolua_get_SDL_JoyHatEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_JoyHatEvent* self = (SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_JoyHatEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyHatEvent_unsigned_type
static int tolua_set_SDL_JoyHatEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_JoyHatEvent* self = (SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: which of class  SDL_JoyHatEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyHatEvent_unsigned_which
static int tolua_get_SDL_JoyHatEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_JoyHatEvent* self = (SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->which);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: which of class  SDL_JoyHatEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyHatEvent_unsigned_which
static int tolua_set_SDL_JoyHatEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_JoyHatEvent* self = (SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->which = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hat of class  SDL_JoyHatEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyHatEvent_unsigned_hat
static int tolua_get_SDL_JoyHatEvent_unsigned_hat(lua_State* tolua_S)
{
	SDL_JoyHatEvent* self = (SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hat'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->hat);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hat of class  SDL_JoyHatEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyHatEvent_unsigned_hat
static int tolua_set_SDL_JoyHatEvent_unsigned_hat(lua_State* tolua_S)
{
	SDL_JoyHatEvent* self = (SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hat'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->hat = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: value of class  SDL_JoyHatEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyHatEvent_unsigned_value
static int tolua_get_SDL_JoyHatEvent_unsigned_value(lua_State* tolua_S)
{
	SDL_JoyHatEvent* self = (SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'value'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->value);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: value of class  SDL_JoyHatEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyHatEvent_unsigned_value
static int tolua_set_SDL_JoyHatEvent_unsigned_value(lua_State* tolua_S)
{
	SDL_JoyHatEvent* self = (SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'value'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->value = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_JoyButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyButtonEvent_unsigned_type
static int tolua_get_SDL_JoyButtonEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_JoyButtonEvent* self = (SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_JoyButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyButtonEvent_unsigned_type
static int tolua_set_SDL_JoyButtonEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_JoyButtonEvent* self = (SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: which of class  SDL_JoyButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyButtonEvent_unsigned_which
static int tolua_get_SDL_JoyButtonEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_JoyButtonEvent* self = (SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->which);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: which of class  SDL_JoyButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyButtonEvent_unsigned_which
static int tolua_set_SDL_JoyButtonEvent_unsigned_which(lua_State* tolua_S)
{
	SDL_JoyButtonEvent* self = (SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'which'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->which = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: button of class  SDL_JoyButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyButtonEvent_unsigned_button
static int tolua_get_SDL_JoyButtonEvent_unsigned_button(lua_State* tolua_S)
{
	SDL_JoyButtonEvent* self = (SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'button'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->button);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: button of class  SDL_JoyButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyButtonEvent_unsigned_button
static int tolua_set_SDL_JoyButtonEvent_unsigned_button(lua_State* tolua_S)
{
	SDL_JoyButtonEvent* self = (SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'button'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->button = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: state of class  SDL_JoyButtonEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_JoyButtonEvent_unsigned_state
static int tolua_get_SDL_JoyButtonEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_JoyButtonEvent* self = (SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->state);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: state of class  SDL_JoyButtonEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_JoyButtonEvent_unsigned_state
static int tolua_set_SDL_JoyButtonEvent_unsigned_state(lua_State* tolua_S)
{
	SDL_JoyButtonEvent* self = (SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'state'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->state = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_ResizeEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_ResizeEvent_unsigned_type
static int tolua_get_SDL_ResizeEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_ResizeEvent* self = (SDL_ResizeEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_ResizeEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_ResizeEvent_unsigned_type
static int tolua_set_SDL_ResizeEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_ResizeEvent* self = (SDL_ResizeEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: w of class  SDL_ResizeEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_ResizeEvent_w
static int tolua_get_SDL_ResizeEvent_w(lua_State* tolua_S)
{
	SDL_ResizeEvent* self = (SDL_ResizeEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->w);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: w of class  SDL_ResizeEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_ResizeEvent_w
static int tolua_set_SDL_ResizeEvent_w(lua_State* tolua_S)
{
	SDL_ResizeEvent* self = (SDL_ResizeEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->w = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: h of class  SDL_ResizeEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_ResizeEvent_h
static int tolua_get_SDL_ResizeEvent_h(lua_State* tolua_S)
{
	SDL_ResizeEvent* self = (SDL_ResizeEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'h'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->h);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: h of class  SDL_ResizeEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_ResizeEvent_h
static int tolua_set_SDL_ResizeEvent_h(lua_State* tolua_S)
{
	SDL_ResizeEvent* self = (SDL_ResizeEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'h'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->h = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_ExposeEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_ExposeEvent_unsigned_type
static int tolua_get_SDL_ExposeEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_ExposeEvent* self = (SDL_ExposeEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_ExposeEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_ExposeEvent_unsigned_type
static int tolua_set_SDL_ExposeEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_ExposeEvent* self = (SDL_ExposeEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_QuitEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_QuitEvent_unsigned_type
static int tolua_get_SDL_QuitEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_QuitEvent* self = (SDL_QuitEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_QuitEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_QuitEvent_unsigned_type
static int tolua_set_SDL_QuitEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_QuitEvent* self = (SDL_QuitEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_UserEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_UserEvent_unsigned_type
static int tolua_get_SDL_UserEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_UserEvent* self = (SDL_UserEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_UserEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_UserEvent_unsigned_type
static int tolua_set_SDL_UserEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_UserEvent* self = (SDL_UserEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: code of class  SDL_UserEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_UserEvent_code
static int tolua_get_SDL_UserEvent_code(lua_State* tolua_S)
{
	SDL_UserEvent* self = (SDL_UserEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'code'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->code);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: code of class  SDL_UserEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_UserEvent_code
static int tolua_set_SDL_UserEvent_code(lua_State* tolua_S)
{
	SDL_UserEvent* self = (SDL_UserEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'code'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->code = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: data1 of class  SDL_UserEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_UserEvent_data1
static int tolua_get_SDL_UserEvent_data1(lua_State* tolua_S)
{
	SDL_UserEvent* self = (SDL_UserEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data1'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->data1);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: data1 of class  SDL_UserEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_UserEvent_data1
static int tolua_set_SDL_UserEvent_data1(lua_State* tolua_S)
{
	SDL_UserEvent* self = (SDL_UserEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data1'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->data1 = ((void*)  tolua_touserdata(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: data2 of class  SDL_UserEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_UserEvent_data2
static int tolua_get_SDL_UserEvent_data2(lua_State* tolua_S)
{
	SDL_UserEvent* self = (SDL_UserEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data2'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->data2);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: data2 of class  SDL_UserEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_UserEvent_data2
static int tolua_set_SDL_UserEvent_data2(lua_State* tolua_S)
{
	SDL_UserEvent* self = (SDL_UserEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data2'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->data2 = ((void*)  tolua_touserdata(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_SysWMEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_SysWMEvent_unsigned_type
static int tolua_get_SDL_SysWMEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_SysWMEvent* self = (SDL_SysWMEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_SysWMEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_SysWMEvent_unsigned_type
static int tolua_set_SDL_SysWMEvent_unsigned_type(lua_State* tolua_S)
{
	SDL_SysWMEvent* self = (SDL_SysWMEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: msg of class  SDL_SysWMEvent */
#ifndef TOLUA_DISABLE_tolua_get_SDL_SysWMEvent_msg_ptr
static int tolua_get_SDL_SysWMEvent_msg_ptr(lua_State* tolua_S)
{
	SDL_SysWMEvent* self = (SDL_SysWMEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'msg'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)self->msg,"SDL_SysWMmsg");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: msg of class  SDL_SysWMEvent */
#ifndef TOLUA_DISABLE_tolua_set_SDL_SysWMEvent_msg_ptr
static int tolua_set_SDL_SysWMEvent_msg_ptr(lua_State* tolua_S)
{
	SDL_SysWMEvent* self = (SDL_SysWMEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'msg'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_SysWMmsg",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->msg = ((SDL_SysWMmsg*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_unsigned_type
static int tolua_get_SDL_Event_unsigned_type(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_unsigned_type
static int tolua_set_SDL_Event_unsigned_type(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: active of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_active
static int tolua_get_SDL_Event_active(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'active'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->active,"SDL_ActiveEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: active of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_active
static int tolua_set_SDL_Event_active(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'active'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_ActiveEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->active = *((SDL_ActiveEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: key of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_key
static int tolua_get_SDL_Event_key(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'key'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->key,"SDL_KeyboardEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: key of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_key
static int tolua_set_SDL_Event_key(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'key'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_KeyboardEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->key = *((SDL_KeyboardEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: motion of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_motion
static int tolua_get_SDL_Event_motion(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'motion'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->motion,"SDL_MouseMotionEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: motion of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_motion
static int tolua_set_SDL_Event_motion(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'motion'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_MouseMotionEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->motion = *((SDL_MouseMotionEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: button of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_button
static int tolua_get_SDL_Event_button(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'button'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->button,"SDL_MouseButtonEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: button of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_button
static int tolua_set_SDL_Event_button(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'button'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_MouseButtonEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->button = *((SDL_MouseButtonEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: jaxis of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_jaxis
static int tolua_get_SDL_Event_jaxis(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jaxis'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->jaxis,"SDL_JoyAxisEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: jaxis of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_jaxis
static int tolua_set_SDL_Event_jaxis(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jaxis'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_JoyAxisEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->jaxis = *((SDL_JoyAxisEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: jball of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_jball
static int tolua_get_SDL_Event_jball(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jball'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->jball,"SDL_JoyBallEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: jball of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_jball
static int tolua_set_SDL_Event_jball(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jball'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_JoyBallEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->jball = *((SDL_JoyBallEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: jhat of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_jhat
static int tolua_get_SDL_Event_jhat(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jhat'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->jhat,"SDL_JoyHatEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: jhat of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_jhat
static int tolua_set_SDL_Event_jhat(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jhat'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_JoyHatEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->jhat = *((SDL_JoyHatEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: jbutton of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_jbutton
static int tolua_get_SDL_Event_jbutton(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jbutton'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->jbutton,"SDL_JoyButtonEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: jbutton of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_jbutton
static int tolua_set_SDL_Event_jbutton(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jbutton'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_JoyButtonEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->jbutton = *((SDL_JoyButtonEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: resize of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_resize
static int tolua_get_SDL_Event_resize(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'resize'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->resize,"SDL_ResizeEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: resize of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_resize
static int tolua_set_SDL_Event_resize(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'resize'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_ResizeEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->resize = *((SDL_ResizeEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: expose of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_expose
static int tolua_get_SDL_Event_expose(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'expose'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->expose,"SDL_ExposeEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: expose of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_expose
static int tolua_set_SDL_Event_expose(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'expose'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_ExposeEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->expose = *((SDL_ExposeEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: quit of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_quit
static int tolua_get_SDL_Event_quit(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'quit'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->quit,"SDL_QuitEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: quit of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_quit
static int tolua_set_SDL_Event_quit(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'quit'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_QuitEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->quit = *((SDL_QuitEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: user of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_user
static int tolua_get_SDL_Event_user(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'user'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->user,"SDL_UserEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: user of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_user
static int tolua_set_SDL_Event_user(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'user'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_UserEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->user = *((SDL_UserEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: syswm of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Event_syswm
static int tolua_get_SDL_Event_syswm(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'syswm'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->syswm,"SDL_SysWMEvent");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: syswm of class  SDL_Event */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Event_syswm
static int tolua_set_SDL_Event_syswm(lua_State* tolua_S)
{
	SDL_Event* self = (SDL_Event*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'syswm'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_SysWMEvent",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->syswm = *((SDL_SysWMEvent*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_PumpEvents */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_PumpEvents00
static int tolua_SDL_SDL_SDL_PumpEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_PumpEvents();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_PumpEvents'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_PeepEvents */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_PeepEvents00
static int tolua_SDL_SDL_SDL_PeepEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Event",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Event* events = ((SDL_Event*)  tolua_tousertype(tolua_S,1,0));
		int numevents = ((int)  tolua_tonumber(tolua_S,2,0));
		SDL_eventaction action = ((SDL_eventaction) (int)  tolua_tonumber(tolua_S,3,0));
		unsigned int mask = ((  unsigned int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  SDL_PeepEvents(events,numevents,action,mask);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_PeepEvents'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_PollEvent */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_PollEvent00
static int tolua_SDL_SDL_SDL_PollEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Event",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Event* event = ((SDL_Event*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_PollEvent(event);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_PollEvent'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WaitEvent */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WaitEvent00
static int tolua_SDL_SDL_SDL_WaitEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Event",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Event* event = ((SDL_Event*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_WaitEvent(event);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WaitEvent'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_PushEvent */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_PushEvent00
static int tolua_SDL_SDL_SDL_PushEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Event",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Event* event = ((SDL_Event*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_PushEvent(event);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_PushEvent'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_EventState */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_EventState00
static int tolua_SDL_SDL_SDL_EventState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned char type = ((  unsigned char)  tolua_tonumber(tolua_S,1,0));
		int state = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			unsigned char tolua_ret = (  unsigned char)  SDL_EventState(type,state);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_EventState'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SDL_RWops */
#ifndef TOLUA_DISABLE_tolua_get_SDL_RWops_unsigned_type
static int tolua_get_SDL_RWops_unsigned_type(lua_State* tolua_S)
{
	SDL_RWops* self = (SDL_RWops*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->type);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SDL_RWops */
#ifndef TOLUA_DISABLE_tolua_set_SDL_RWops_unsigned_type
static int tolua_set_SDL_RWops_unsigned_type(lua_State* tolua_S)
{
	SDL_RWops* self = (SDL_RWops*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->type = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RWFromFile */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RWFromFile00
static int tolua_SDL_SDL_SDL_RWFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* mode = ((const char*)  tolua_tostring(tolua_S,2,0));
		{
			SDL_RWops* tolua_ret = (SDL_RWops*)  SDL_RWFromFile(file,mode);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_RWops");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RWFromFile'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RWFromMem */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RWFromMem00
static int tolua_SDL_SDL_SDL_RWFromMem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* mem = ((void*)  tolua_touserdata(tolua_S,1,0));
		int size = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			SDL_RWops* tolua_ret = (SDL_RWops*)  SDL_RWFromMem(mem,size);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_RWops");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RWFromMem'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RWFromConstMem */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RWFromConstMem00
static int tolua_SDL_SDL_SDL_RWFromConstMem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const void* mem = ((const void*)  tolua_touserdata(tolua_S,1,0));
		int size = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			SDL_RWops* tolua_ret = (SDL_RWops*)  SDL_RWFromConstMem(mem,size);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_RWops");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RWFromConstMem'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_AllocRW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_AllocRW00
static int tolua_SDL_SDL_SDL_AllocRW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_RWops* tolua_ret = (SDL_RWops*)  SDL_AllocRW();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_RWops");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_AllocRW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_FreeRW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_FreeRW00
static int tolua_SDL_SDL_SDL_FreeRW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* area = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_FreeRW(area);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_FreeRW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RWseek */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RWseek00
static int tolua_SDL_SDL_SDL_RWseek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct SDL_RWops* context = ((struct SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		int offset = ((int)  tolua_tonumber(tolua_S,2,0));
		int whence = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_RWseek(context,offset,whence);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RWseek'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RWtell */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RWtell00
static int tolua_SDL_SDL_SDL_RWtell00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct SDL_RWops* context = ((struct SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_RWtell(context);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RWtell'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RWread */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RWread00
static int tolua_SDL_SDL_SDL_RWread00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct SDL_RWops* context = ((struct SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		void* ptr = ((void*)  tolua_touserdata(tolua_S,2,0));
		int size = ((int)  tolua_tonumber(tolua_S,3,0));
		int maxnum = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  SDL_RWread(context,ptr,size,maxnum);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RWread'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RWwrite */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RWwrite00
static int tolua_SDL_SDL_SDL_RWwrite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct SDL_RWops* context = ((struct SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		const void* ptr = ((const void*)  tolua_touserdata(tolua_S,2,0));
		int size = ((int)  tolua_tonumber(tolua_S,3,0));
		int num = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  SDL_RWwrite(context,ptr,size,num);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RWwrite'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RWclose */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RWclose00
static int tolua_SDL_SDL_SDL_RWclose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct SDL_RWops* context = ((struct SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_RWclose(context);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RWclose'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ReadLE16 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ReadLE1600
static int tolua_SDL_SDL_SDL_ReadLE1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			unsigned short tolua_ret = (  unsigned short)  SDL_ReadLE16(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ReadLE16'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ReadBE16 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ReadBE1600
static int tolua_SDL_SDL_SDL_ReadBE1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			unsigned short tolua_ret = (  unsigned short)  SDL_ReadBE16(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ReadBE16'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ReadLE32 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ReadLE3200
static int tolua_SDL_SDL_SDL_ReadLE3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_ReadLE32(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ReadLE32'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ReadBE32 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ReadBE3200
static int tolua_SDL_SDL_SDL_ReadBE3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_ReadBE32(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ReadBE32'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WriteLE16 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WriteLE1600
static int tolua_SDL_SDL_SDL_WriteLE1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* dst = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		unsigned short value = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_WriteLE16(dst,value);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WriteLE16'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WriteBE16 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WriteBE1600
static int tolua_SDL_SDL_SDL_WriteBE1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* dst = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		unsigned short value = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_WriteBE16(dst,value);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WriteBE16'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WriteLE32 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WriteLE3200
static int tolua_SDL_SDL_SDL_WriteLE3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* dst = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		unsigned int value = ((  unsigned int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_WriteLE32(dst,value);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WriteLE32'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WriteBE32 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WriteBE3200
static int tolua_SDL_SDL_SDL_WriteBE3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* dst = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		unsigned int value = ((  unsigned int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_WriteBE32(dst,value);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WriteBE32'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetTicks */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetTicks00
static int tolua_SDL_SDL_SDL_GetTicks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_GetTicks();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetTicks'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Delay */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Delay00
static int tolua_SDL_SDL_SDL_Delay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int ms = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		{
			SDL_Delay(ms);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Delay'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: _SDL_AddTimer */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_AddTimer00
static int tolua_SDL_SDL_SDL_AddTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_Event",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int interval = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		SDL_Event* param = ((SDL_Event*)  tolua_tousertype(tolua_S,2,0));
		{
			struct _SDL_TimerID* tolua_ret = (struct _SDL_TimerID*)  _SDL_AddTimer(interval,param);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_SDL_TimerID");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_AddTimer'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_RemoveTimer */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_RemoveTimer00
static int tolua_SDL_SDL_SDL_RemoveTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDL_TimerID",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDL_TimerID* t = ((struct _SDL_TimerID*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_RemoveTimer(t);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_RemoveTimer'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  SDL_Rect */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Rect_x
static int tolua_get_SDL_Rect_x(lua_State* tolua_S)
{
	SDL_Rect* self = (SDL_Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->x);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  SDL_Rect */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Rect_x
static int tolua_set_SDL_Rect_x(lua_State* tolua_S)
{
	SDL_Rect* self = (SDL_Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->x = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  SDL_Rect */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Rect_y
static int tolua_get_SDL_Rect_y(lua_State* tolua_S)
{
	SDL_Rect* self = (SDL_Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->y);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  SDL_Rect */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Rect_y
static int tolua_set_SDL_Rect_y(lua_State* tolua_S)
{
	SDL_Rect* self = (SDL_Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->y = ((  signed short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: w of class  SDL_Rect */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Rect_unsigned_w
static int tolua_get_SDL_Rect_unsigned_w(lua_State* tolua_S)
{
	SDL_Rect* self = (SDL_Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->w);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: w of class  SDL_Rect */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Rect_unsigned_w
static int tolua_set_SDL_Rect_unsigned_w(lua_State* tolua_S)
{
	SDL_Rect* self = (SDL_Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->w = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: h of class  SDL_Rect */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Rect_unsigned_h
static int tolua_get_SDL_Rect_unsigned_h(lua_State* tolua_S)
{
	SDL_Rect* self = (SDL_Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'h'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->h);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: h of class  SDL_Rect */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Rect_unsigned_h
static int tolua_set_SDL_Rect_unsigned_h(lua_State* tolua_S)
{
	SDL_Rect* self = (SDL_Rect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'h'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->h = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: r of class  SDL_Color */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Color_unsigned_r
static int tolua_get_SDL_Color_unsigned_r(lua_State* tolua_S)
{
	SDL_Color* self = (SDL_Color*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->r);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: r of class  SDL_Color */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Color_unsigned_r
static int tolua_set_SDL_Color_unsigned_r(lua_State* tolua_S)
{
	SDL_Color* self = (SDL_Color*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->r = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: g of class  SDL_Color */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Color_unsigned_g
static int tolua_get_SDL_Color_unsigned_g(lua_State* tolua_S)
{
	SDL_Color* self = (SDL_Color*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->g);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: g of class  SDL_Color */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Color_unsigned_g
static int tolua_set_SDL_Color_unsigned_g(lua_State* tolua_S)
{
	SDL_Color* self = (SDL_Color*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->g = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  SDL_Color */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Color_unsigned_b
static int tolua_get_SDL_Color_unsigned_b(lua_State* tolua_S)
{
	SDL_Color* self = (SDL_Color*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->b);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  SDL_Color */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Color_unsigned_b
static int tolua_set_SDL_Color_unsigned_b(lua_State* tolua_S)
{
	SDL_Color* self = (SDL_Color*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->b = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: unused of class  SDL_Color */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Color_unsigned_unused
static int tolua_get_SDL_Color_unsigned_unused(lua_State* tolua_S)
{
	SDL_Color* self = (SDL_Color*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unused'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->unused);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: unused of class  SDL_Color */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Color_unsigned_unused
static int tolua_set_SDL_Color_unsigned_unused(lua_State* tolua_S)
{
	SDL_Color* self = (SDL_Color*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unused'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->unused = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ncolors of class  SDL_Palette */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Palette_ncolors
static int tolua_get_SDL_Palette_ncolors(lua_State* tolua_S)
{
	SDL_Palette* self = (SDL_Palette*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ncolors'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->ncolors);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ncolors of class  SDL_Palette */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Palette_ncolors
static int tolua_set_SDL_Palette_ncolors(lua_State* tolua_S)
{
	SDL_Palette* self = (SDL_Palette*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ncolors'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->ncolors = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: colors of class  SDL_Palette */
#ifndef TOLUA_DISABLE_tolua_get_SDL_SDL_SDL_Palette_colors
static int tolua_get_SDL_SDL_SDL_Palette_colors(lua_State* tolua_S)
{
	int tolua_index;
	SDL_Palette* self;
	lua_pushstring(tolua_S,".self");
	lua_rawget(tolua_S,1);
	self = (SDL_Palette*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
	{
		tolua_Error tolua_err;
		if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
			tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
	}
#endif
	tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
	if (tolua_index<0)
		tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->colors[tolua_index],"SDL_Color");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: colors of class  SDL_Palette */
#ifndef TOLUA_DISABLE_tolua_set_SDL_SDL_SDL_Palette_colors
static int tolua_set_SDL_SDL_SDL_Palette_colors(lua_State* tolua_S)
{
	int tolua_index;
	SDL_Palette* self;
	lua_pushstring(tolua_S,".self");
	lua_rawget(tolua_S,1);
	self = (SDL_Palette*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
	{
		tolua_Error tolua_err;
		if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
			tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
	}
#endif
	tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
	if (tolua_index<0)
		tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
	self->colors[tolua_index] = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: palette of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_palette_ptr
static int tolua_get_SDL_PixelFormat_palette_ptr(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'palette'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)self->palette,"SDL_Palette");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: palette of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_palette_ptr
static int tolua_set_SDL_PixelFormat_palette_ptr(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'palette'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_Palette",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->palette = ((SDL_Palette*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: BitsPerPixel of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_BitsPerPixel
static int tolua_get_SDL_PixelFormat_unsigned_BitsPerPixel(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BitsPerPixel'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->BitsPerPixel);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: BitsPerPixel of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_BitsPerPixel
static int tolua_set_SDL_PixelFormat_unsigned_BitsPerPixel(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BitsPerPixel'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->BitsPerPixel = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: BytesPerPixel of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_BytesPerPixel
static int tolua_get_SDL_PixelFormat_unsigned_BytesPerPixel(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BytesPerPixel'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->BytesPerPixel);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: BytesPerPixel of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_BytesPerPixel
static int tolua_set_SDL_PixelFormat_unsigned_BytesPerPixel(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'BytesPerPixel'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->BytesPerPixel = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Rloss of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Rloss
static int tolua_get_SDL_PixelFormat_unsigned_Rloss(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Rloss'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Rloss);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Rloss of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Rloss
static int tolua_set_SDL_PixelFormat_unsigned_Rloss(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Rloss'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Rloss = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Gloss of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Gloss
static int tolua_get_SDL_PixelFormat_unsigned_Gloss(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gloss'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Gloss);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Gloss of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Gloss
static int tolua_set_SDL_PixelFormat_unsigned_Gloss(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gloss'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Gloss = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Bloss of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Bloss
static int tolua_get_SDL_PixelFormat_unsigned_Bloss(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Bloss'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Bloss);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Bloss of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Bloss
static int tolua_set_SDL_PixelFormat_unsigned_Bloss(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Bloss'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Bloss = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Aloss of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Aloss
static int tolua_get_SDL_PixelFormat_unsigned_Aloss(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Aloss'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Aloss);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Aloss of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Aloss
static int tolua_set_SDL_PixelFormat_unsigned_Aloss(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Aloss'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Aloss = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Rshift of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Rshift
static int tolua_get_SDL_PixelFormat_unsigned_Rshift(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Rshift'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Rshift);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Rshift of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Rshift
static int tolua_set_SDL_PixelFormat_unsigned_Rshift(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Rshift'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Rshift = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Gshift of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Gshift
static int tolua_get_SDL_PixelFormat_unsigned_Gshift(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gshift'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Gshift);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Gshift of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Gshift
static int tolua_set_SDL_PixelFormat_unsigned_Gshift(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gshift'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Gshift = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Bshift of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Bshift
static int tolua_get_SDL_PixelFormat_unsigned_Bshift(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Bshift'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Bshift);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Bshift of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Bshift
static int tolua_set_SDL_PixelFormat_unsigned_Bshift(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Bshift'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Bshift = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Ashift of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Ashift
static int tolua_get_SDL_PixelFormat_unsigned_Ashift(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Ashift'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Ashift);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Ashift of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Ashift
static int tolua_set_SDL_PixelFormat_unsigned_Ashift(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Ashift'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Ashift = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Rmask of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Rmask
static int tolua_get_SDL_PixelFormat_unsigned_Rmask(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Rmask'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Rmask);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Rmask of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Rmask
static int tolua_set_SDL_PixelFormat_unsigned_Rmask(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Rmask'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Rmask = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Gmask of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Gmask
static int tolua_get_SDL_PixelFormat_unsigned_Gmask(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gmask'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Gmask);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Gmask of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Gmask
static int tolua_set_SDL_PixelFormat_unsigned_Gmask(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gmask'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Gmask = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Bmask of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Bmask
static int tolua_get_SDL_PixelFormat_unsigned_Bmask(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Bmask'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Bmask);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Bmask of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Bmask
static int tolua_set_SDL_PixelFormat_unsigned_Bmask(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Bmask'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Bmask = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Amask of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_Amask
static int tolua_get_SDL_PixelFormat_unsigned_Amask(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Amask'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->Amask);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Amask of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_Amask
static int tolua_set_SDL_PixelFormat_unsigned_Amask(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Amask'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->Amask = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: colorkey of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_colorkey
static int tolua_get_SDL_PixelFormat_unsigned_colorkey(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorkey'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->colorkey);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: colorkey of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_colorkey
static int tolua_set_SDL_PixelFormat_unsigned_colorkey(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorkey'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->colorkey = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: alpha of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_get_SDL_PixelFormat_unsigned_alpha
static int tolua_get_SDL_PixelFormat_unsigned_alpha(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alpha'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->alpha);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: alpha of class  SDL_PixelFormat */
#ifndef TOLUA_DISABLE_tolua_set_SDL_PixelFormat_unsigned_alpha
static int tolua_set_SDL_PixelFormat_unsigned_alpha(lua_State* tolua_S)
{
	SDL_PixelFormat* self = (SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alpha'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->alpha = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: flags of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_unsigned_flags
static int tolua_get_SDL_Surface_unsigned_flags(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flags'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->flags);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: flags of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_unsigned_flags
static int tolua_set_SDL_Surface_unsigned_flags(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flags'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->flags = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: format of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_format_ptr
static int tolua_get_SDL_Surface_format_ptr(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'format'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)self->format,"SDL_PixelFormat");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: format of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_format_ptr
static int tolua_set_SDL_Surface_format_ptr(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'format'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_PixelFormat",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->format = ((SDL_PixelFormat*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: w of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_w
static int tolua_get_SDL_Surface_w(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->w);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: w of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_w
static int tolua_set_SDL_Surface_w(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->w = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: h of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_h
static int tolua_get_SDL_Surface_h(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'h'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->h);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: h of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_h
static int tolua_set_SDL_Surface_h(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'h'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->h = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pitch of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_unsigned_pitch
static int tolua_get_SDL_Surface_unsigned_pitch(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pitch'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->pitch);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pitch of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_unsigned_pitch
static int tolua_set_SDL_Surface_unsigned_pitch(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pitch'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->pitch = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pixels of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_pixels
static int tolua_get_SDL_Surface_pixels(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pixels'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->pixels);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pixels of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_pixels
static int tolua_set_SDL_Surface_pixels(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pixels'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->pixels = ((void*)  tolua_touserdata(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: clip_rect of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_clip_rect
static int tolua_get_SDL_Surface_clip_rect(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'clip_rect'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->clip_rect,"SDL_Rect");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: clip_rect of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_clip_rect
static int tolua_set_SDL_Surface_clip_rect(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'clip_rect'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_Rect",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->clip_rect = *((SDL_Rect*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: unused1 of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_unsigned_unused1
static int tolua_get_SDL_Surface_unsigned_unused1(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unused1'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->unused1);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: unused1 of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_unsigned_unused1
static int tolua_set_SDL_Surface_unsigned_unused1(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unused1'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->unused1 = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: refcount of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Surface_refcount
static int tolua_get_SDL_Surface_refcount(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'refcount'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->refcount);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: refcount of class  SDL_Surface */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Surface_refcount
static int tolua_set_SDL_Surface_refcount(lua_State* tolua_S)
{
	SDL_Surface* self = (SDL_Surface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'refcount'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->refcount = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_MUSTLOCK */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_MUSTLOCK00
static int tolua_SDL_SDL_SDL_MUSTLOCK00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_MUSTLOCK(surface);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_MUSTLOCK'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hw_available of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_hw_available
static int tolua_get_SDL_VideoInfo_unsigned_hw_available(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hw_available'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->hw_available);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hw_available of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_hw_available
static int tolua_set_SDL_VideoInfo_unsigned_hw_available(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hw_available'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->hw_available = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wm_available of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_wm_available
static int tolua_get_SDL_VideoInfo_unsigned_wm_available(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wm_available'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->wm_available);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wm_available of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_wm_available
static int tolua_set_SDL_VideoInfo_unsigned_wm_available(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wm_available'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->wm_available = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UnusedBits1 of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_UnusedBits1
static int tolua_get_SDL_VideoInfo_unsigned_UnusedBits1(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UnusedBits1'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->UnusedBits1);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UnusedBits1 of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_UnusedBits1
static int tolua_set_SDL_VideoInfo_unsigned_UnusedBits1(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UnusedBits1'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->UnusedBits1 = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UnusedBits2 of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_UnusedBits2
static int tolua_get_SDL_VideoInfo_unsigned_UnusedBits2(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UnusedBits2'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->UnusedBits2);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UnusedBits2 of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_UnusedBits2
static int tolua_set_SDL_VideoInfo_unsigned_UnusedBits2(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UnusedBits2'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->UnusedBits2 = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blit_hw of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_blit_hw
static int tolua_get_SDL_VideoInfo_unsigned_blit_hw(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_hw'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->blit_hw);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blit_hw of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_blit_hw
static int tolua_set_SDL_VideoInfo_unsigned_blit_hw(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_hw'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->blit_hw = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blit_hw_CC of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_blit_hw_CC
static int tolua_get_SDL_VideoInfo_unsigned_blit_hw_CC(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_hw_CC'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->blit_hw_CC);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blit_hw_CC of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_blit_hw_CC
static int tolua_set_SDL_VideoInfo_unsigned_blit_hw_CC(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_hw_CC'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->blit_hw_CC = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blit_hw_A of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_blit_hw_A
static int tolua_get_SDL_VideoInfo_unsigned_blit_hw_A(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_hw_A'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->blit_hw_A);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blit_hw_A of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_blit_hw_A
static int tolua_set_SDL_VideoInfo_unsigned_blit_hw_A(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_hw_A'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->blit_hw_A = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blit_sw of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_blit_sw
static int tolua_get_SDL_VideoInfo_unsigned_blit_sw(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_sw'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->blit_sw);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blit_sw of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_blit_sw
static int tolua_set_SDL_VideoInfo_unsigned_blit_sw(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_sw'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->blit_sw = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blit_sw_CC of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_blit_sw_CC
static int tolua_get_SDL_VideoInfo_unsigned_blit_sw_CC(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_sw_CC'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->blit_sw_CC);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blit_sw_CC of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_blit_sw_CC
static int tolua_set_SDL_VideoInfo_unsigned_blit_sw_CC(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_sw_CC'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->blit_sw_CC = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blit_sw_A of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_blit_sw_A
static int tolua_get_SDL_VideoInfo_unsigned_blit_sw_A(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_sw_A'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->blit_sw_A);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blit_sw_A of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_blit_sw_A
static int tolua_set_SDL_VideoInfo_unsigned_blit_sw_A(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_sw_A'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->blit_sw_A = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blit_fill of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_blit_fill
static int tolua_get_SDL_VideoInfo_unsigned_blit_fill(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_fill'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->blit_fill);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blit_fill of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_blit_fill
static int tolua_set_SDL_VideoInfo_unsigned_blit_fill(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blit_fill'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->blit_fill = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UnusedBits3 of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_UnusedBits3
static int tolua_get_SDL_VideoInfo_unsigned_UnusedBits3(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UnusedBits3'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->UnusedBits3);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UnusedBits3 of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_UnusedBits3
static int tolua_set_SDL_VideoInfo_unsigned_UnusedBits3(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UnusedBits3'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->UnusedBits3 = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: video_mem of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_unsigned_video_mem
static int tolua_get_SDL_VideoInfo_unsigned_video_mem(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'video_mem'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->video_mem);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: video_mem of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_unsigned_video_mem
static int tolua_set_SDL_VideoInfo_unsigned_video_mem(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'video_mem'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->video_mem = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vfmt of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_vfmt_ptr
static int tolua_get_SDL_VideoInfo_vfmt_ptr(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vfmt'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)self->vfmt,"SDL_PixelFormat");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vfmt of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_vfmt_ptr
static int tolua_set_SDL_VideoInfo_vfmt_ptr(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vfmt'",NULL);
	if (!tolua_isusertype(tolua_S,2,"SDL_PixelFormat",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->vfmt = ((SDL_PixelFormat*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: current_w of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_current_w
static int tolua_get_SDL_VideoInfo_current_w(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'current_w'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->current_w);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: current_w of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_current_w
static int tolua_set_SDL_VideoInfo_current_w(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'current_w'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->current_w = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: current_h of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_get_SDL_VideoInfo_current_h
static int tolua_get_SDL_VideoInfo_current_h(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'current_h'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->current_h);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: current_h of class  SDL_VideoInfo */
#ifndef TOLUA_DISABLE_tolua_set_SDL_VideoInfo_current_h
static int tolua_set_SDL_VideoInfo_current_h(lua_State* tolua_S)
{
	SDL_VideoInfo* self = (SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'current_h'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->current_h = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: format of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Overlay_unsigned_format
static int tolua_get_SDL_Overlay_unsigned_format(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'format'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->format);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: format of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Overlay_unsigned_format
static int tolua_set_SDL_Overlay_unsigned_format(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'format'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->format = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: w of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Overlay_w
static int tolua_get_SDL_Overlay_w(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->w);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: w of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Overlay_w
static int tolua_set_SDL_Overlay_w(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'w'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->w = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: h of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Overlay_h
static int tolua_get_SDL_Overlay_h(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'h'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->h);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: h of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Overlay_h
static int tolua_set_SDL_Overlay_h(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'h'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->h = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: planes of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Overlay_planes
static int tolua_get_SDL_Overlay_planes(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'planes'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->planes);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: planes of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Overlay_planes
static int tolua_set_SDL_Overlay_planes(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'planes'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->planes = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pitches of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_get_SDL_SDL_SDL_Overlay_pitches
static int tolua_get_SDL_SDL_SDL_Overlay_pitches(lua_State* tolua_S)
{
	int tolua_index;
	SDL_Overlay* self;
	lua_pushstring(tolua_S,".self");
	lua_rawget(tolua_S,1);
	self = (SDL_Overlay*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
	{
		tolua_Error tolua_err;
		if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
			tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
	}
#endif
	tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
	if (tolua_index<0)
		tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->pitches[tolua_index]);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pitches of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_set_SDL_SDL_SDL_Overlay_pitches
static int tolua_set_SDL_SDL_SDL_Overlay_pitches(lua_State* tolua_S)
{
	int tolua_index;
	SDL_Overlay* self;
	lua_pushstring(tolua_S,".self");
	lua_rawget(tolua_S,1);
	self = (SDL_Overlay*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
	{
		tolua_Error tolua_err;
		if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
			tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
	}
#endif
	tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
	if (tolua_index<0)
		tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
	self->pitches[tolua_index] = ((  unsigned short)  tolua_tonumber(tolua_S,3,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pixels of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_get_SDL_SDL_SDL_Overlay_pixels
static int tolua_get_SDL_SDL_SDL_Overlay_pixels(lua_State* tolua_S)
{
	int tolua_index;
	SDL_Overlay* self;
	lua_pushstring(tolua_S,".self");
	lua_rawget(tolua_S,1);
	self = (SDL_Overlay*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
	{
		tolua_Error tolua_err;
		if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
			tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
	}
#endif
	tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
	if (tolua_index<0)
		tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->pixels[tolua_index]);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pixels of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_set_SDL_SDL_SDL_Overlay_pixels
static int tolua_set_SDL_SDL_SDL_Overlay_pixels(lua_State* tolua_S)
{
	int tolua_index;
	SDL_Overlay* self;
	lua_pushstring(tolua_S,".self");
	lua_rawget(tolua_S,1);
	self = (SDL_Overlay*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
	{
		tolua_Error tolua_err;
		if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
			tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
	}
#endif
	tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
	if (tolua_index<0)
		tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
	self->pixels[tolua_index] = ((Uint8*)  tolua_touserdata(tolua_S,3,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hw_overlay of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Overlay_unsigned_hw_overlay
static int tolua_get_SDL_Overlay_unsigned_hw_overlay(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hw_overlay'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->hw_overlay);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hw_overlay of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Overlay_unsigned_hw_overlay
static int tolua_set_SDL_Overlay_unsigned_hw_overlay(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hw_overlay'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->hw_overlay = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UnusedBits of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_get_SDL_Overlay_unsigned_UnusedBits
static int tolua_get_SDL_Overlay_unsigned_UnusedBits(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UnusedBits'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->UnusedBits);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UnusedBits of class  SDL_Overlay */
#ifndef TOLUA_DISABLE_tolua_set_SDL_Overlay_unsigned_UnusedBits
static int tolua_set_SDL_Overlay_unsigned_UnusedBits(lua_State* tolua_S)
{
	SDL_Overlay* self = (SDL_Overlay*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UnusedBits'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->UnusedBits = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_VideoDriverName */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_VideoDriverName00
static int tolua_SDL_SDL_SDL_VideoDriverName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* namebuf = ((char*)  tolua_tostring(tolua_S,1,0));
		int maxlen = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			char* tolua_ret = (char*)  SDL_VideoDriverName(namebuf,maxlen);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_VideoDriverName'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetVideoSurface */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetVideoSurface00
static int tolua_SDL_SDL_SDL_GetVideoSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_GetVideoSurface();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetVideoSurface'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetVideoInfo */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetVideoInfo00
static int tolua_SDL_SDL_SDL_GetVideoInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			const SDL_VideoInfo* tolua_ret = (const SDL_VideoInfo*)  SDL_GetVideoInfo();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"const SDL_VideoInfo");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetVideoInfo'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_VideoModeOK */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_VideoModeOK00
static int tolua_SDL_SDL_SDL_VideoModeOK00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int width = ((int)  tolua_tonumber(tolua_S,1,0));
		int height = ((int)  tolua_tonumber(tolua_S,2,0));
		int bpp = ((int)  tolua_tonumber(tolua_S,3,0));
		unsigned int flags = ((  unsigned int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  SDL_VideoModeOK(width,height,bpp,flags);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_VideoModeOK'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetVideoMode */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetVideoMode00
static int tolua_SDL_SDL_SDL_SetVideoMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int width = ((int)  tolua_tonumber(tolua_S,1,0));
		int height = ((int)  tolua_tonumber(tolua_S,2,0));
		int bpp = ((int)  tolua_tonumber(tolua_S,3,0));
		unsigned int flags = ((  unsigned int)  tolua_tonumber(tolua_S,4,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_SetVideoMode(width,height,bpp,flags);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetVideoMode'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_UpdateRect */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_UpdateRect00
static int tolua_SDL_SDL_SDL_UpdateRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,6,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* screen = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		signed int x = ((  signed int)  tolua_tonumber(tolua_S,2,0));
		signed int y = ((  signed int)  tolua_tonumber(tolua_S,3,0));
		unsigned int w = ((  unsigned int)  tolua_tonumber(tolua_S,4,0));
		unsigned int h = ((  unsigned int)  tolua_tonumber(tolua_S,5,0));
		{
			SDL_UpdateRect(screen,x,y,w,h);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_UpdateRect'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Flip */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Flip00
static int tolua_SDL_SDL_SDL_Flip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* screen = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_Flip(screen);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Flip'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetGamma */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetGamma00
static int tolua_SDL_SDL_SDL_SetGamma00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		float red = ((float)  tolua_tonumber(tolua_S,1,0));
		float green = ((float)  tolua_tonumber(tolua_S,2,0));
		float blue = ((float)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_SetGamma(red,green,blue);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetGamma'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetGammaRamp */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetGammaRamp00
static int tolua_SDL_SDL_SDL_SetGammaRamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned const short red = ((unsigned const short)  tolua_tonumber(tolua_S,1,0));
		unsigned const short green = ((unsigned const short)  tolua_tonumber(tolua_S,2,0));
		unsigned const short blue = ((unsigned const short)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_SetGammaRamp(&red,&green,&blue);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)red);
			tolua_pushnumber(tolua_S,(lua_Number)green);
			tolua_pushnumber(tolua_S,(lua_Number)blue);
		}
	}
	return 4;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetGammaRamp'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetGammaRamp */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetGammaRamp00
static int tolua_SDL_SDL_SDL_GetGammaRamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned short red = ((  unsigned short)  tolua_tonumber(tolua_S,1,0));
		unsigned short green = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		unsigned short blue = ((  unsigned short)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_GetGammaRamp(&red,&green,&blue);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)red);
			tolua_pushnumber(tolua_S,(lua_Number)green);
			tolua_pushnumber(tolua_S,(lua_Number)blue);
		}
	}
	return 4;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetGammaRamp'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetColors */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetColors00
static int tolua_SDL_SDL_SDL_SetColors00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_Color",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		SDL_Color* colors = ((SDL_Color*)  tolua_tousertype(tolua_S,2,0));
		int firstcolor = ((int)  tolua_tonumber(tolua_S,3,0));
		int ncolors = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  SDL_SetColors(surface,colors,firstcolor,ncolors);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetColors'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetPalette */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetPalette00
static int tolua_SDL_SDL_SDL_SetPalette00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,6,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		int flags = ((int)  tolua_tonumber(tolua_S,2,0));
		SDL_Color* colors = ((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		int firstcolor = ((int)  tolua_tonumber(tolua_S,4,0));
		int ncolors = ((int)  tolua_tonumber(tolua_S,5,0));
		{
			int tolua_ret = (int)  SDL_SetPalette(surface,flags,colors,firstcolor,ncolors);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetPalette'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_MapRGB */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_MapRGB00
static int tolua_SDL_SDL_SDL_MapRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"const SDL_PixelFormat",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const SDL_PixelFormat* format = ((const SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0));
		unsigned const char r = ((unsigned const char)  tolua_tonumber(tolua_S,2,0));
		unsigned const char g = ((unsigned const char)  tolua_tonumber(tolua_S,3,0));
		unsigned const char b = ((unsigned const char)  tolua_tonumber(tolua_S,4,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_MapRGB(format,r,g,b);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_MapRGB'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_MapRGBA */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_MapRGBA00
static int tolua_SDL_SDL_SDL_MapRGBA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"const SDL_PixelFormat",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,6,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const SDL_PixelFormat* format = ((const SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0));
		unsigned const char r = ((unsigned const char)  tolua_tonumber(tolua_S,2,0));
		unsigned const char g = ((unsigned const char)  tolua_tonumber(tolua_S,3,0));
		unsigned const char b = ((unsigned const char)  tolua_tonumber(tolua_S,4,0));
		unsigned const char a = ((unsigned const char)  tolua_tonumber(tolua_S,5,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_MapRGBA(format,r,g,b,a);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_MapRGBA'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetRGB */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetRGB00
static int tolua_SDL_SDL_SDL_GetRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_PixelFormat",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,6,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int pixel = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		SDL_PixelFormat* fmt = ((SDL_PixelFormat*)  tolua_tousertype(tolua_S,2,0));
		unsigned char r = ((  unsigned char)  tolua_tonumber(tolua_S,3,0));
		unsigned char g = ((  unsigned char)  tolua_tonumber(tolua_S,4,0));
		unsigned char b = ((  unsigned char)  tolua_tonumber(tolua_S,5,0));
		{
			SDL_GetRGB(pixel,fmt,&r,&g,&b);
			tolua_pushnumber(tolua_S,(lua_Number)r);
			tolua_pushnumber(tolua_S,(lua_Number)g);
			tolua_pushnumber(tolua_S,(lua_Number)b);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetRGB'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetRGBA */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetRGBA00
static int tolua_SDL_SDL_SDL_GetRGBA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_PixelFormat",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,6,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,7,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int pixel = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		SDL_PixelFormat* fmt = ((SDL_PixelFormat*)  tolua_tousertype(tolua_S,2,0));
		unsigned char r = ((  unsigned char)  tolua_tonumber(tolua_S,3,0));
		unsigned char g = ((  unsigned char)  tolua_tonumber(tolua_S,4,0));
		unsigned char b = ((  unsigned char)  tolua_tonumber(tolua_S,5,0));
		unsigned char a = ((  unsigned char)  tolua_tonumber(tolua_S,6,0));
		{
			SDL_GetRGBA(pixel,fmt,&r,&g,&b,&a);
			tolua_pushnumber(tolua_S,(lua_Number)r);
			tolua_pushnumber(tolua_S,(lua_Number)g);
			tolua_pushnumber(tolua_S,(lua_Number)b);
			tolua_pushnumber(tolua_S,(lua_Number)a);
		}
	}
	return 4;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetRGBA'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CreateRGBSurface */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CreateRGBSurface00
static int tolua_SDL_SDL_SDL_CreateRGBSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,6,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,7,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,8,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,9,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int flags = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		int width = ((int)  tolua_tonumber(tolua_S,2,0));
		int height = ((int)  tolua_tonumber(tolua_S,3,0));
		int depth = ((int)  tolua_tonumber(tolua_S,4,0));
		unsigned int Rmask = ((  unsigned int)  tolua_tonumber(tolua_S,5,0));
		unsigned int Gmask = ((  unsigned int)  tolua_tonumber(tolua_S,6,0));
		unsigned int Bmask = ((  unsigned int)  tolua_tonumber(tolua_S,7,0));
		unsigned int Amask = ((  unsigned int)  tolua_tonumber(tolua_S,8,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_CreateRGBSurface(flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CreateRGBSurface'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CreateRGBSurfaceFrom */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CreateRGBSurfaceFrom00
static int tolua_SDL_SDL_SDL_CreateRGBSurfaceFrom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,6,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,7,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,8,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,9,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,10,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* pixels = ((void*)  tolua_touserdata(tolua_S,1,0));
		int width = ((int)  tolua_tonumber(tolua_S,2,0));
		int height = ((int)  tolua_tonumber(tolua_S,3,0));
		int depth = ((int)  tolua_tonumber(tolua_S,4,0));
		int pitch = ((int)  tolua_tonumber(tolua_S,5,0));
		unsigned int Rmask = ((  unsigned int)  tolua_tonumber(tolua_S,6,0));
		unsigned int Gmask = ((  unsigned int)  tolua_tonumber(tolua_S,7,0));
		unsigned int Bmask = ((  unsigned int)  tolua_tonumber(tolua_S,8,0));
		unsigned int Amask = ((  unsigned int)  tolua_tonumber(tolua_S,9,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_CreateRGBSurfaceFrom(pixels,width,height,depth,pitch,Rmask,Gmask,Bmask,Amask);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CreateRGBSurfaceFrom'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_FreeSurface */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_FreeSurface00
static int tolua_SDL_SDL_SDL_FreeSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_FreeSurface(surface);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_FreeSurface'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_LockSurface */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_LockSurface00
static int tolua_SDL_SDL_SDL_LockSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_LockSurface(surface);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_LockSurface'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_UnlockSurface */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_UnlockSurface00
static int tolua_SDL_SDL_SDL_UnlockSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_UnlockSurface(surface);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_UnlockSurface'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_LoadBMP_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_LoadBMP_RW00
static int tolua_SDL_SDL_SDL_LoadBMP_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		int freesrc = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_LoadBMP_RW(src,freesrc);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_LoadBMP_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SaveBMP_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SaveBMP_RW00
static int tolua_SDL_SDL_SDL_SaveBMP_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		SDL_RWops* dst = ((SDL_RWops*)  tolua_tousertype(tolua_S,2,0));
		int freedst = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_SaveBMP_RW(surface,dst,freedst);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SaveBMP_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_LoadBMP */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_LoadBMP00
static int tolua_SDL_SDL_SDL_LoadBMP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_LoadBMP(file);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_LoadBMP'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SaveBMP */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SaveBMP00
static int tolua_SDL_SDL_SDL_SaveBMP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_SaveBMP(surface,file);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SaveBMP'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetColorKey */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetColorKey00
static int tolua_SDL_SDL_SDL_SetColorKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		unsigned int flag = ((  unsigned int)  tolua_tonumber(tolua_S,2,0));
		unsigned int key = ((  unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_SetColorKey(surface,flag,key);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetColorKey'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetAlpha */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetAlpha00
static int tolua_SDL_SDL_SDL_SetAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		unsigned int flag = ((  unsigned int)  tolua_tonumber(tolua_S,2,0));
		unsigned char alpha = ((  unsigned char)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_SetAlpha(surface,flag,alpha);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetAlpha'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetAlpha */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetAlphaChannel00
static int tolua_SDL_SDL_SDL_SetAlphaChannel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		unsigned char alpha = ((  unsigned char)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_SetAlphaChannel(surface,alpha);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetAlphaChannel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_SetClipRect */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_SetClipRect00
static int tolua_SDL_SDL_SDL_SetClipRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"const SDL_Rect",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		const SDL_Rect* rect = ((const SDL_Rect*)  tolua_tousertype(tolua_S,2,0));
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_SetClipRect(surface,rect);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_SetClipRect'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetClipRect */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetClipRect00
static int tolua_SDL_SDL_SDL_GetClipRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_Rect",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		SDL_Rect* rect = ((SDL_Rect*)  tolua_tousertype(tolua_S,2,0));
		{
			SDL_GetClipRect(surface,rect);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetClipRect'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_ConvertSurface */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_ConvertSurface00
static int tolua_SDL_SDL_SDL_ConvertSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_PixelFormat",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* src = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		SDL_PixelFormat* fmt = ((SDL_PixelFormat*)  tolua_tousertype(tolua_S,2,0));
		unsigned int flags = ((  unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_ConvertSurface(src,fmt,flags);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_ConvertSurface'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_UpperBlit */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_UpperBlit00
static int tolua_SDL_SDL_SDL_UpperBlit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_Rect",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,4,"SDL_Rect",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* src = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		SDL_Rect* srcrect = ((SDL_Rect*)  tolua_tousertype(tolua_S,2,0));
		SDL_Surface* dst = ((SDL_Surface*)  tolua_tousertype(tolua_S,3,0));
		SDL_Rect* dstrect = ((SDL_Rect*)  tolua_tousertype(tolua_S,4,0));
		{
			int tolua_ret = (int)  SDL_UpperBlit(src,srcrect,dst,dstrect);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_UpperBlit'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_LowerBlit */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_LowerBlit00
static int tolua_SDL_SDL_SDL_LowerBlit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_Rect",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,4,"SDL_Rect",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* src = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		SDL_Rect* srcrect = ((SDL_Rect*)  tolua_tousertype(tolua_S,2,0));
		SDL_Surface* dst = ((SDL_Surface*)  tolua_tousertype(tolua_S,3,0));
		SDL_Rect* dstrect = ((SDL_Rect*)  tolua_tousertype(tolua_S,4,0));
		{
			int tolua_ret = (int)  SDL_LowerBlit(src,srcrect,dst,dstrect);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_LowerBlit'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_FillRect */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_FillRect00
static int tolua_SDL_SDL_SDL_FillRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_Rect",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* dst = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		SDL_Rect* dstrect = ((SDL_Rect*)  tolua_tousertype(tolua_S,2,0));
		unsigned int color = ((  unsigned int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_FillRect(dst,dstrect,color);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_FillRect'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

#define TOLUA_DISABLE_tolua_SDL_SDL_GFX_zoomSurface00 1

/* function: SDL_GFX_zoomSurface */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_GFX_zoomSurface00
static int tolua_SDL_SDL_GFX_zoomSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		double sx = tolua_tonumber(tolua_S,2,1);
		double sy = tolua_tonumber(tolua_S,3,1);
		int smooth = tolua_tonumber(tolua_S,4,1);

		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  zoomSurface(surface,sx,sy,smooth);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'zoomSurface'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_DisplayFormat */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_DisplayFormat00
static int tolua_SDL_SDL_SDL_DisplayFormat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_DisplayFormat(surface);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_DisplayFormat'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_DisplayFormatAlpha */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_DisplayFormatAlpha00
static int tolua_SDL_SDL_SDL_DisplayFormatAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  SDL_DisplayFormatAlpha(surface);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_DisplayFormatAlpha'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CreateYUVOverlay */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CreateYUVOverlay00
static int tolua_SDL_SDL_SDL_CreateYUVOverlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,4,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int width = ((int)  tolua_tonumber(tolua_S,1,0));
		int height = ((int)  tolua_tonumber(tolua_S,2,0));
		unsigned int format = ((  unsigned int)  tolua_tonumber(tolua_S,3,0));
		SDL_Surface* display = ((SDL_Surface*)  tolua_tousertype(tolua_S,4,0));
		{
			SDL_Overlay* tolua_ret = (SDL_Overlay*)  SDL_CreateYUVOverlay(width,height,format,display);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Overlay");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CreateYUVOverlay'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_LockYUVOverlay */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_LockYUVOverlay00
static int tolua_SDL_SDL_SDL_LockYUVOverlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Overlay",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Overlay* overlay = ((SDL_Overlay*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_LockYUVOverlay(overlay);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_LockYUVOverlay'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_UnlockYUVOverlay */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_UnlockYUVOverlay00
static int tolua_SDL_SDL_SDL_UnlockYUVOverlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Overlay",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Overlay* overlay = ((SDL_Overlay*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_UnlockYUVOverlay(overlay);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_UnlockYUVOverlay'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_DisplayYUVOverlay */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_DisplayYUVOverlay00
static int tolua_SDL_SDL_SDL_DisplayYUVOverlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Overlay",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_Rect",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Overlay* overlay = ((SDL_Overlay*)  tolua_tousertype(tolua_S,1,0));
		SDL_Rect* dstrect = ((SDL_Rect*)  tolua_tousertype(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_DisplayYUVOverlay(overlay,dstrect);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_DisplayYUVOverlay'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_FreeYUVOverlay */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_FreeYUVOverlay00
static int tolua_SDL_SDL_SDL_FreeYUVOverlay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Overlay",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Overlay* overlay = ((SDL_Overlay*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_FreeYUVOverlay(overlay);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_FreeYUVOverlay'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GL_LoadLibrary */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_LoadLibrary00
static int tolua_SDL_SDL_SDL_GL_LoadLibrary00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_GL_LoadLibrary(path);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_LoadLibrary'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GL_GetProcAddress */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_GetProcAddress00
static int tolua_SDL_SDL_SDL_GL_GetProcAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* proc = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			void* tolua_ret = (void*)  SDL_GL_GetProcAddress(proc);
			tolua_pushuserdata(tolua_S,(void*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_GetProcAddress'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GL_SetAttribute */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_SetSubData00
static int tolua_SDL_SDL_SDL_GL_SetSubData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,6,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,7,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,8,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,9,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		GLenum target = ((GLenum) (int)  tolua_tonumber(tolua_S,1,0));
		GLint level = ((GLint) (int)  tolua_tonumber(tolua_S,2,0));
		GLint x = ((GLint) (int)  tolua_tonumber(tolua_S,3,0));
		GLint y = ((GLint) (int)  tolua_tonumber(tolua_S,4,0));
		GLsizei w = ((GLsizei) (int)  tolua_tonumber(tolua_S,5,0));
		GLsizei h = ((GLsizei) (int)  tolua_tonumber(tolua_S,6,0));
		GLenum format = ((GLenum) (int)  tolua_tonumber(tolua_S,7,0));
		GLenum type = ((GLenum) (int)  tolua_tonumber(tolua_S,8,0));

		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,9,0));
		
		SDL_glTexSubImage2D(target,level,x,y,w,h,format,type,surface->pixels);
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_SetSubData'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE
/* function: SDL_GL_SetAttribute */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_SetAttribute00
static int tolua_SDL_SDL_SDL_GL_SetAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_GLattr attr = ((SDL_GLattr) (int)  tolua_tonumber(tolua_S,1,0));
		int value = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_GL_SetAttribute(attr,value);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_SetAttribute'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GL_GetAttribute */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_GetAttribute00
static int tolua_SDL_SDL_SDL_GL_GetAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_GLattr attr = ((SDL_GLattr) (int)  tolua_tonumber(tolua_S,1,0));
		int value = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDL_GL_GetAttribute(attr,&value);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)value);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_GetAttribute'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GL_SwapBuffers */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_SwapBuffers00
static int tolua_SDL_SDL_SDL_GL_SwapBuffers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_GL_SwapBuffers();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_SwapBuffers'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GL_UpdateRects */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_UpdateRects00
static int tolua_SDL_SDL_SDL_GL_UpdateRects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"SDL_Rect",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int numrects = ((int)  tolua_tonumber(tolua_S,1,0));
		SDL_Rect* rects = ((SDL_Rect*)  tolua_tousertype(tolua_S,2,0));
		{
			SDL_GL_UpdateRects(numrects,rects);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_UpdateRects'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GL_Lock */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_Lock00
static int tolua_SDL_SDL_SDL_GL_Lock00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_GL_Lock();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_Lock'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GL_Unlock */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GL_Unlock00
static int tolua_SDL_SDL_SDL_GL_Unlock00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_GL_Unlock();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GL_Unlock'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WM_SetCaption */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WM_SetCaption00
static int tolua_SDL_SDL_SDL_WM_SetCaption00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* title = ((const char*)  tolua_tostring(tolua_S,1,0));
		const char* icon = ((const char*)  tolua_tostring(tolua_S,2,0));
		{
			SDL_WM_SetCaption(title,icon);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WM_SetCaption'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WM_GetCaption */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WM_GetCaption00
static int tolua_SDL_SDL_SDL_WM_GetCaption00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		char* title = ((char*)  tolua_tostring(tolua_S,1,0));
		char* icon = ((char*)  tolua_tostring(tolua_S,2,0));
		{
			SDL_WM_GetCaption(&title,&icon);
			tolua_pushstring(tolua_S,(const char*)title);
			tolua_pushstring(tolua_S,(const char*)icon);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WM_GetCaption'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WM_SetIcon */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WM_SetIcon00
static int tolua_SDL_SDL_SDL_WM_SetIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* icon = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		unsigned char mask = ((  unsigned char)  tolua_tonumber(tolua_S,2,0));
		{
			SDL_WM_SetIcon(icon,&mask);
			tolua_pushnumber(tolua_S,(lua_Number)mask);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WM_SetIcon'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WM_IconifyWindow */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WM_IconifyWindow00
static int tolua_SDL_SDL_SDL_WM_IconifyWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  SDL_WM_IconifyWindow();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WM_IconifyWindow'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WM_ToggleFullScreen */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WM_ToggleFullScreen00
static int tolua_SDL_SDL_SDL_WM_ToggleFullScreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_WM_ToggleFullScreen(surface);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WM_ToggleFullScreen'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WM_GrabInput */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WM_GrabInput00
static int tolua_SDL_SDL_SDL_WM_GrabInput00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_GrabMode mode = ((SDL_GrabMode) (int)  tolua_tonumber(tolua_S,1,0));
		{
			SDL_GrabMode tolua_ret = (SDL_GrabMode)  SDL_WM_GrabInput(mode);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WM_GrabInput'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: major of class  SDL_version */
#ifndef TOLUA_DISABLE_tolua_get_SDL_version_unsigned_major
static int tolua_get_SDL_version_unsigned_major(lua_State* tolua_S)
{
	SDL_version* self = (SDL_version*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'major'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->major);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: major of class  SDL_version */
#ifndef TOLUA_DISABLE_tolua_set_SDL_version_unsigned_major
static int tolua_set_SDL_version_unsigned_major(lua_State* tolua_S)
{
	SDL_version* self = (SDL_version*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'major'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->major = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: minor of class  SDL_version */
#ifndef TOLUA_DISABLE_tolua_get_SDL_version_unsigned_minor
static int tolua_get_SDL_version_unsigned_minor(lua_State* tolua_S)
{
	SDL_version* self = (SDL_version*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'minor'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->minor);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: minor of class  SDL_version */
#ifndef TOLUA_DISABLE_tolua_set_SDL_version_unsigned_minor
static int tolua_set_SDL_version_unsigned_minor(lua_State* tolua_S)
{
	SDL_version* self = (SDL_version*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'minor'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->minor = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: patch of class  SDL_version */
#ifndef TOLUA_DISABLE_tolua_get_SDL_version_unsigned_patch
static int tolua_get_SDL_version_unsigned_patch(lua_State* tolua_S)
{
	SDL_version* self = (SDL_version*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'patch'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->patch);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: patch of class  SDL_version */
#ifndef TOLUA_DISABLE_tolua_set_SDL_version_unsigned_patch
static int tolua_set_SDL_version_unsigned_patch(lua_State* tolua_S)
{
	SDL_version* self = (SDL_version*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'patch'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->patch = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_VERSION */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_VERSION00
static int tolua_SDL_SDL_SDL_VERSION00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_version",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_version* ver_info = ((SDL_version*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_VERSION(ver_info);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_VERSION'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_VERSIONNUM */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_VERSIONNUM00
static int tolua_SDL_SDL_SDL_VERSIONNUM00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int major = ((int)  tolua_tonumber(tolua_S,1,0));
		int minor = ((int)  tolua_tonumber(tolua_S,2,0));
		int patchlevel = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDL_VERSIONNUM(major,minor,patchlevel);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_VERSIONNUM'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_VERSION_ATLEAST */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_VERSION_ATLEAST00
static int tolua_SDL_SDL_SDL_VERSION_ATLEAST00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int major = ((int)  tolua_tonumber(tolua_S,1,0));
		int minor = ((int)  tolua_tonumber(tolua_S,2,0));
		int patchlevel = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			SDL_bool tolua_ret = (SDL_bool)  SDL_VERSION_ATLEAST(major,minor,patchlevel);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_VERSION_ATLEAST'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Init */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Init00
static int tolua_SDL_SDL_SDL_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int flags = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_Init(flags);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Init'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_InitSubSystem */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_InitSubSystem00
static int tolua_SDL_SDL_SDL_InitSubSystem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int flags = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  SDL_InitSubSystem(flags);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_InitSubSystem'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_QuitSubSystem */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_QuitSubSystem00
static int tolua_SDL_SDL_SDL_QuitSubSystem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int flags = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		{
			SDL_QuitSubSystem(flags);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_QuitSubSystem'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_WasInit */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_WasInit00
static int tolua_SDL_SDL_SDL_WasInit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int flags = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_WasInit(flags);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_WasInit'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Quit */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Quit00
static int tolua_SDL_SDL_SDL_Quit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_Quit();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Quit'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_IMAGE_VERSION */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_IMAGE_VERSION00
static int tolua_SDL_SDL_SDL_IMAGE_VERSION00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_version",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_version* ver_info = ((SDL_version*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_IMAGE_VERSION(ver_info);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_IMAGE_VERSION'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadTyped_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadTyped_RW00
static int tolua_SDL_SDL_IMG_LoadTyped_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isstring(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		int freesrc = ((int)  tolua_tonumber(tolua_S,2,0));
		char* type = ((char*)  tolua_tostring(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadTyped_RW(src,freesrc,type);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadTyped_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_Load */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_Load00
static int tolua_SDL_SDL_IMG_Load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_Load(file);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_Load'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_Load_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_Load_RW00
static int tolua_SDL_SDL_IMG_Load_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		int freesrc = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_Load_RW(src,freesrc);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_Load_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_InvertAlpha */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_InvertAlpha00
static int tolua_SDL_SDL_IMG_InvertAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int on = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_InvertAlpha(on);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_InvertAlpha'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isBMP */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isBMP00
static int tolua_SDL_SDL_IMG_isBMP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isBMP(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isBMP'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isGIF */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isGIF00
static int tolua_SDL_SDL_IMG_isGIF00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isGIF(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isGIF'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isJPG */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isJPG00
static int tolua_SDL_SDL_IMG_isJPG00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isJPG(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isJPG'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isLBM */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isLBM00
static int tolua_SDL_SDL_IMG_isLBM00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isLBM(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isLBM'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isPCX */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isPCX00
static int tolua_SDL_SDL_IMG_isPCX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isPCX(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isPCX'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isPNG */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isPNG00
static int tolua_SDL_SDL_IMG_isPNG00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isPNG(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isPNG'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isPNM */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isPNM00
static int tolua_SDL_SDL_IMG_isPNM00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isPNM(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isPNM'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isTIF */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isTIF00
static int tolua_SDL_SDL_IMG_isTIF00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isTIF(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isTIF'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isXCF */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isXCF00
static int tolua_SDL_SDL_IMG_isXCF00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isXCF(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isXCF'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isXPM */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isXPM00
static int tolua_SDL_SDL_IMG_isXPM00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isXPM(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isXPM'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_isXV */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_isXV00
static int tolua_SDL_SDL_IMG_isXV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  IMG_isXV(src);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_isXV'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadBMP_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadBMP_RW00
static int tolua_SDL_SDL_IMG_LoadBMP_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadBMP_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadBMP_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadGIF_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadGIF_RW00
static int tolua_SDL_SDL_IMG_LoadGIF_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadGIF_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadGIF_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadJPG_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadJPG_RW00
static int tolua_SDL_SDL_IMG_LoadJPG_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadJPG_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadJPG_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadLBM_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadLBM_RW00
static int tolua_SDL_SDL_IMG_LoadLBM_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadLBM_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadLBM_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadPCX_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadPCX_RW00
static int tolua_SDL_SDL_IMG_LoadPCX_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadPCX_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadPCX_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadPNG_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadPNG_RW00
static int tolua_SDL_SDL_IMG_LoadPNG_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadPNG_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadPNG_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadPNM_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadPNM_RW00
static int tolua_SDL_SDL_IMG_LoadPNM_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadPNM_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadPNM_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadTGA_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadTGA_RW00
static int tolua_SDL_SDL_IMG_LoadTGA_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadTGA_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadTGA_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadTIF_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadTIF_RW00
static int tolua_SDL_SDL_IMG_LoadTIF_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadTIF_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadTIF_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadXCF_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadXCF_RW00
static int tolua_SDL_SDL_IMG_LoadXCF_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadXCF_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadXCF_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadXPM_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadXPM_RW00
static int tolua_SDL_SDL_IMG_LoadXPM_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadXPM_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadXPM_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_LoadXV_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_LoadXV_RW00
static int tolua_SDL_SDL_IMG_LoadXV_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_LoadXV_RW(src);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_LoadXV_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IMG_ReadXPMFromArray */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IMG_ReadXPMFromArray00
static int tolua_SDL_SDL_IMG_ReadXPMFromArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* xpm = ((void*)  tolua_touserdata(tolua_S,1,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  IMG_ReadXPMFromArray((char**)xpm);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IMG_ReadXPMFromArray'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_MIXER_VERSION */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_MIXER_VERSION00
static int tolua_SDL_SDL_SDL_MIXER_VERSION00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_version",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_version* ver_info = ((SDL_version*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_MIXER_VERSION(ver_info);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_MIXER_VERSION'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: allocated of class  Mix_Chunk */
#ifndef TOLUA_DISABLE_tolua_get_Mix_Chunk_allocated
static int tolua_get_Mix_Chunk_allocated(lua_State* tolua_S)
{
	Mix_Chunk* self = (Mix_Chunk*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'allocated'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->allocated);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: allocated of class  Mix_Chunk */
#ifndef TOLUA_DISABLE_tolua_set_Mix_Chunk_allocated
static int tolua_set_Mix_Chunk_allocated(lua_State* tolua_S)
{
	Mix_Chunk* self = (Mix_Chunk*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'allocated'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->allocated = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: abuf of class  Mix_Chunk */
#ifndef TOLUA_DISABLE_tolua_get_Mix_Chunk_abuf
static int tolua_get_Mix_Chunk_abuf(lua_State* tolua_S)
{
	Mix_Chunk* self = (Mix_Chunk*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'abuf'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->abuf);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: abuf of class  Mix_Chunk */
#ifndef TOLUA_DISABLE_tolua_set_Mix_Chunk_abuf
static int tolua_set_Mix_Chunk_abuf(lua_State* tolua_S)
{
	Mix_Chunk* self = (Mix_Chunk*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'abuf'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->abuf = ((Uint8*)  tolua_touserdata(tolua_S,2,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: alen of class  Mix_Chunk */
#ifndef TOLUA_DISABLE_tolua_get_Mix_Chunk_unsigned_alen
static int tolua_get_Mix_Chunk_unsigned_alen(lua_State* tolua_S)
{
	Mix_Chunk* self = (Mix_Chunk*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alen'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->alen);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: alen of class  Mix_Chunk */
#ifndef TOLUA_DISABLE_tolua_set_Mix_Chunk_unsigned_alen
static int tolua_set_Mix_Chunk_unsigned_alen(lua_State* tolua_S)
{
	Mix_Chunk* self = (Mix_Chunk*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alen'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->alen = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: volume of class  Mix_Chunk */
#ifndef TOLUA_DISABLE_tolua_get_Mix_Chunk_unsigned_volume
static int tolua_get_Mix_Chunk_unsigned_volume(lua_State* tolua_S)
{
	Mix_Chunk* self = (Mix_Chunk*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'volume'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->volume);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: volume of class  Mix_Chunk */
#ifndef TOLUA_DISABLE_tolua_set_Mix_Chunk_unsigned_volume
static int tolua_set_Mix_Chunk_unsigned_volume(lua_State* tolua_S)
{
	Mix_Chunk* self = (Mix_Chunk*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'volume'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->volume = ((  unsigned char)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_OpenAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_OpenAudio00
static int tolua_SDL_SDL_Mix_OpenAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int frequency = ((int)  tolua_tonumber(tolua_S,1,0));
		unsigned short format = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		int channels = ((int)  tolua_tonumber(tolua_S,3,0));
		int chunksize = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  Mix_OpenAudio(frequency,format,channels,chunksize);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_OpenAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_AllocateChannels */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_AllocateChannels00
static int tolua_SDL_SDL_Mix_AllocateChannels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int numchans = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_AllocateChannels(numchans);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_AllocateChannels'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_QuerySpec */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_QuerySpec00
static int tolua_SDL_SDL_Mix_QuerySpec00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int frequency = ((int)  tolua_tonumber(tolua_S,1,0));
		unsigned short format = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		int channels = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  Mix_QuerySpec(&frequency,&format,&channels);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)frequency);
			tolua_pushnumber(tolua_S,(lua_Number)format);
			tolua_pushnumber(tolua_S,(lua_Number)channels);
		}
	}
	return 4;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_QuerySpec'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_LoadWAV_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_LoadWAV_RW00
static int tolua_SDL_SDL_Mix_LoadWAV_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		int freesrc = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			Mix_Chunk* tolua_ret = (Mix_Chunk*)  Mix_LoadWAV_RW(src,freesrc);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"Mix_Chunk");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_LoadWAV_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_LoadWAV */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_LoadWAV00
static int tolua_SDL_SDL_Mix_LoadWAV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			Mix_Chunk* tolua_ret = (Mix_Chunk*)  Mix_LoadWAV(file);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"Mix_Chunk");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_LoadWAV'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_LoadMUS */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_LoadMUS00
static int tolua_SDL_SDL_Mix_LoadMUS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			struct _Mix_Music* tolua_ret = ( struct _Mix_Music*)  Mix_LoadMUS(file);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_Mix_Music");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_LoadMUS'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_LoadMUS_RW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_LoadMUS_RW00
static int tolua_SDL_SDL_Mix_LoadMUS_RW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* rw = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		{
			struct _Mix_Music* tolua_ret = ( struct _Mix_Music*)  Mix_LoadMUS_RW(rw);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_Mix_Music");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_LoadMUS_RW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_QuickLoad_WAV */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_QuickLoad_WAV00
static int tolua_SDL_SDL_Mix_QuickLoad_WAV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* mem = ((void*)  tolua_touserdata(tolua_S,1,0));
		{
			Mix_Chunk* tolua_ret = (Mix_Chunk*)  Mix_QuickLoad_WAV((Uint8*)mem);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"Mix_Chunk");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_QuickLoad_WAV'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_QuickLoad_RAW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_QuickLoad_RAW00
static int tolua_SDL_SDL_Mix_QuickLoad_RAW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* mem = ((void*)  tolua_touserdata(tolua_S,1,0));
		unsigned int len = ((  unsigned int)  tolua_tonumber(tolua_S,2,0));
		{
			Mix_Chunk* tolua_ret = (Mix_Chunk*)  Mix_QuickLoad_RAW((Uint8*)mem,len);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"Mix_Chunk");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_QuickLoad_RAW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FreeChunk */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FreeChunk00
static int tolua_SDL_SDL_Mix_FreeChunk00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"Mix_Chunk",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		Mix_Chunk* chunk = ((Mix_Chunk*)  tolua_tousertype(tolua_S,1,0));
		{
			Mix_FreeChunk(chunk);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FreeChunk'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FreeMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FreeMusic00
static int tolua_SDL_SDL_Mix_FreeMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_Mix_Music",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _Mix_Music* music = (( struct _Mix_Music*)  tolua_tousertype(tolua_S,1,0));
		{
			Mix_FreeMusic(music);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FreeMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _MIX_EFFECTSMAXSPEED */
#ifndef TOLUA_DISABLE_tolua_get_SDL_MIX_EFFECTSMAXSPEED
static int tolua_get_SDL_MIX_EFFECTSMAXSPEED(lua_State* tolua_S)
{
	tolua_pushstring(tolua_S,(const char*)_MIX_EFFECTSMAXSPEED);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_SetPanning */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_SetPanning00
static int tolua_SDL_SDL_Mix_SetPanning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		unsigned char left = ((  unsigned char)  tolua_tonumber(tolua_S,2,0));
		unsigned char right = ((  unsigned char)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  Mix_SetPanning(channel,left,right);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_SetPanning'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_SetPosition */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_SetPosition00
static int tolua_SDL_SDL_Mix_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		signed short angle = ((  signed short)  tolua_tonumber(tolua_S,2,0));
		unsigned char distance = ((  unsigned char)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  Mix_SetPosition(channel,angle,distance);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_SetPosition'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_SetDistance */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_SetDistance00
static int tolua_SDL_SDL_Mix_SetDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		unsigned char distance = ((  unsigned char)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_SetDistance(channel,distance);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_SetDistance'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_SetReverseStereo */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_SetReverseStereo00
static int tolua_SDL_SDL_Mix_SetReverseStereo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		int flip = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_SetReverseStereo(channel,flip);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_SetReverseStereo'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_ReserveChannels */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_ReserveChannels00
static int tolua_SDL_SDL_Mix_ReserveChannels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int num = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_ReserveChannels(num);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_ReserveChannels'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_GroupChannel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_GroupChannel00
static int tolua_SDL_SDL_Mix_GroupChannel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int which = ((int)  tolua_tonumber(tolua_S,1,0));
		int tag = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_GroupChannel(which,tag);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_GroupChannel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_GroupChannels */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_GroupChannels00
static int tolua_SDL_SDL_Mix_GroupChannels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int from = ((int)  tolua_tonumber(tolua_S,1,0));
		int to = ((int)  tolua_tonumber(tolua_S,2,0));
		int tag = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  Mix_GroupChannels(from,to,tag);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_GroupChannels'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_GroupAvailable */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_GroupAvailable00
static int tolua_SDL_SDL_Mix_GroupAvailable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int tag = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_GroupAvailable(tag);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_GroupAvailable'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_GroupCount */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_GroupCount00
static int tolua_SDL_SDL_Mix_GroupCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int tag = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_GroupCount(tag);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_GroupCount'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_GroupOldest */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_GroupOldest00
static int tolua_SDL_SDL_Mix_GroupOldest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int tag = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_GroupOldest(tag);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_GroupOldest'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_GroupNewer */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_GroupNewer00
static int tolua_SDL_SDL_Mix_GroupNewer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int tag = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_GroupNewer(tag);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_GroupNewer'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_PlayChannelTimed */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_PlayChannelTimed00
static int tolua_SDL_SDL_Mix_PlayChannelTimed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"Mix_Chunk",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		Mix_Chunk* chunk = ((Mix_Chunk*)  tolua_tousertype(tolua_S,2,0));
		int loops = ((int)  tolua_tonumber(tolua_S,3,0));
		int ticks = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  Mix_PlayChannelTimed(channel,chunk,loops,ticks);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_PlayChannelTimed'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_PlayMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_PlayMusic00
static int tolua_SDL_SDL_Mix_PlayMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_Mix_Music",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _Mix_Music* music = (( struct _Mix_Music*)  tolua_tousertype(tolua_S,1,0));
		int loops = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_PlayMusic(music,loops);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_PlayMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadeInMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadeInMusic00
static int tolua_SDL_SDL_Mix_FadeInMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_Mix_Music",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _Mix_Music* music = (( struct _Mix_Music*)  tolua_tousertype(tolua_S,1,0));
		int loops = ((int)  tolua_tonumber(tolua_S,2,0));
		int ms = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  Mix_FadeInMusic(music,loops,ms);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadeInMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadeInMusicPos */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadeInMusicPos00
static int tolua_SDL_SDL_Mix_FadeInMusicPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_Mix_Music",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _Mix_Music* music = (( struct _Mix_Music*)  tolua_tousertype(tolua_S,1,0));
		int loops = ((int)  tolua_tonumber(tolua_S,2,0));
		int ms = ((int)  tolua_tonumber(tolua_S,3,0));
		double position = ((double)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  Mix_FadeInMusicPos(music,loops,ms,position);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadeInMusicPos'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadeInChannelTimed */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadeInChannelTimed00
static int tolua_SDL_SDL_Mix_FadeInChannelTimed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"Mix_Chunk",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,6,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		Mix_Chunk* chunk = ((Mix_Chunk*)  tolua_tousertype(tolua_S,2,0));
		int loops = ((int)  tolua_tonumber(tolua_S,3,0));
		int ms = ((int)  tolua_tonumber(tolua_S,4,0));
		int ticks = ((int)  tolua_tonumber(tolua_S,5,0));
		{
			int tolua_ret = (int)  Mix_FadeInChannelTimed(channel,chunk,loops,ms,ticks);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadeInChannelTimed'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_PlayChannel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_PlayChannel00
static int tolua_SDL_SDL_Mix_PlayChannel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"Mix_Chunk",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		Mix_Chunk* chunk = ((Mix_Chunk*)  tolua_tousertype(tolua_S,2,0));
		int loops = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  Mix_PlayChannel(channel,chunk,loops);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_PlayChannel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadeInChannel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadeInChannel00
static int tolua_SDL_SDL_Mix_FadeInChannel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"Mix_Chunk",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		Mix_Chunk* chunk = ((Mix_Chunk*)  tolua_tousertype(tolua_S,2,0));
		int loops = ((int)  tolua_tonumber(tolua_S,3,0));
		int ms = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  Mix_FadeInChannel(channel,chunk,loops,ms);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadeInChannel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_Volume */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_Volume00
static int tolua_SDL_SDL_Mix_Volume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		int volume = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_Volume(channel,volume);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_Volume'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_VolumeChunk */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_VolumeChunk00
static int tolua_SDL_SDL_Mix_VolumeChunk00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"Mix_Chunk",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		Mix_Chunk* chunk = ((Mix_Chunk*)  tolua_tousertype(tolua_S,1,0));
		int volume = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_VolumeChunk(chunk,volume);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_VolumeChunk'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_VolumeMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_VolumeMusic00
static int tolua_SDL_SDL_Mix_VolumeMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int volume = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_VolumeMusic(volume);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_VolumeMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_HaltChannel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_HaltChannel00
static int tolua_SDL_SDL_Mix_HaltChannel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_HaltChannel(channel);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_HaltChannel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_HaltGroup */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_HaltGroup00
static int tolua_SDL_SDL_Mix_HaltGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int tag = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_HaltGroup(tag);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_HaltGroup'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_HaltMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_HaltMusic00
static int tolua_SDL_SDL_Mix_HaltMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  Mix_HaltMusic();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_HaltMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_ExpireChannel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_ExpireChannel00
static int tolua_SDL_SDL_Mix_ExpireChannel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		int ticks = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_ExpireChannel(channel,ticks);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_ExpireChannel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadeOutChannel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadeOutChannel00
static int tolua_SDL_SDL_Mix_FadeOutChannel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int which = ((int)  tolua_tonumber(tolua_S,1,0));
		int ms = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_FadeOutChannel(which,ms);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadeOutChannel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadeOutGroup */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadeOutGroup00
static int tolua_SDL_SDL_Mix_FadeOutGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int tag = ((int)  tolua_tonumber(tolua_S,1,0));
		int ms = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  Mix_FadeOutGroup(tag,ms);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadeOutGroup'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadeOutMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadeOutMusic00
static int tolua_SDL_SDL_Mix_FadeOutMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int ms = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_FadeOutMusic(ms);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadeOutMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadingMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadingMusic00
static int tolua_SDL_SDL_Mix_FadingMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			Mix_Fading tolua_ret = (Mix_Fading)  Mix_FadingMusic();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadingMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_FadingChannel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_FadingChannel00
static int tolua_SDL_SDL_Mix_FadingChannel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int which = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			Mix_Fading tolua_ret = (Mix_Fading)  Mix_FadingChannel(which);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_FadingChannel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_Pause */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_Pause00
static int tolua_SDL_SDL_Mix_Pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			Mix_Pause(channel);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_Pause'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_Resume */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_Resume00
static int tolua_SDL_SDL_Mix_Resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			Mix_Resume(channel);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_Resume'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_Paused */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_Paused00
static int tolua_SDL_SDL_Mix_Paused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_Paused(channel);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_Paused'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_PauseMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_PauseMusic00
static int tolua_SDL_SDL_Mix_PauseMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			Mix_PauseMusic();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_PauseMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_ResumeMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_ResumeMusic00
static int tolua_SDL_SDL_Mix_ResumeMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			Mix_ResumeMusic();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_ResumeMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_RewindMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_RewindMusic00
static int tolua_SDL_SDL_Mix_RewindMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			Mix_RewindMusic();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_RewindMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_PausedMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_PausedMusic00
static int tolua_SDL_SDL_Mix_PausedMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  Mix_PausedMusic();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_PausedMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_SetMusicPosition */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_SetMusicPosition00
static int tolua_SDL_SDL_Mix_SetMusicPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		double position = ((double)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_SetMusicPosition(position);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_SetMusicPosition'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_Playing */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_Playing00
static int tolua_SDL_SDL_Mix_Playing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_Playing(channel);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_Playing'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_PlayingMusic */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_PlayingMusic00
static int tolua_SDL_SDL_Mix_PlayingMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  Mix_PlayingMusic();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_PlayingMusic'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_SetMusicCMD */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_SetMusicCMD00
static int tolua_SDL_SDL_Mix_SetMusicCMD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* command = ((const char*)  tolua_tostring(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_SetMusicCMD(command);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_SetMusicCMD'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_SetSynchroValue */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_SetSynchroValue00
static int tolua_SDL_SDL_Mix_SetSynchroValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int value = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			int tolua_ret = (int)  Mix_SetSynchroValue(value);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_SetSynchroValue'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_GetSynchroValue */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_GetSynchroValue00
static int tolua_SDL_SDL_Mix_GetSynchroValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  Mix_GetSynchroValue();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_GetSynchroValue'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_GetChunk */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_GetChunk00
static int tolua_SDL_SDL_Mix_GetChunk00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int channel = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			Mix_Chunk* tolua_ret = (Mix_Chunk*)  Mix_GetChunk(channel);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"Mix_Chunk");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_GetChunk'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Mix_CloseAudio */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_Mix_CloseAudio00
static int tolua_SDL_SDL_Mix_CloseAudio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			Mix_CloseAudio();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'Mix_CloseAudio'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_NET_VERSION */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_NET_VERSION00
static int tolua_SDL_SDL_SDL_NET_VERSION00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_version",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_version* ver_info = ((SDL_version*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_NET_VERSION(ver_info);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_NET_VERSION'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_Init */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_Init00
static int tolua_SDL_SDL_SDLNet_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  SDLNet_Init();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_Init'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_Quit */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_Quit00
static int tolua_SDL_SDL_SDLNet_Quit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDLNet_Quit();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_Quit'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: host of class  IPaddress */
#ifndef TOLUA_DISABLE_tolua_get_IPaddress_unsigned_host
static int tolua_get_IPaddress_unsigned_host(lua_State* tolua_S)
{
	IPaddress* self = (IPaddress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'host'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->host);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: host of class  IPaddress */
#ifndef TOLUA_DISABLE_tolua_set_IPaddress_unsigned_host
static int tolua_set_IPaddress_unsigned_host(lua_State* tolua_S)
{
	IPaddress* self = (IPaddress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'host'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->host = ((  unsigned int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: port of class  IPaddress */
#ifndef TOLUA_DISABLE_tolua_get_IPaddress_unsigned_port
static int tolua_get_IPaddress_unsigned_port(lua_State* tolua_S)
{
	IPaddress* self = (IPaddress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->port);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: port of class  IPaddress */
#ifndef TOLUA_DISABLE_tolua_set_IPaddress_unsigned_port
static int tolua_set_IPaddress_unsigned_port(lua_State* tolua_S)
{
	IPaddress* self = (IPaddress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->port = ((  unsigned short)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_ResolveHost */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_ResolveHost00
static int tolua_SDL_SDL_SDLNet_ResolveHost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"IPaddress",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		IPaddress* address = ((IPaddress*)  tolua_tousertype(tolua_S,1,0));
		const char* host = ((const char*)  tolua_tostring(tolua_S,2,0));
		unsigned short port = ((  unsigned short)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDLNet_ResolveHost(address,host,port);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_ResolveHost'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_ResolveIP */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_ResolveIP00
static int tolua_SDL_SDL_SDLNet_ResolveIP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"IPaddress",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		IPaddress* ip = ((IPaddress*)  tolua_tousertype(tolua_S,1,0));
		{
			const char* tolua_ret = (const char*)  SDLNet_ResolveIP(ip);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_ResolveIP'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_TCP_Open */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_TCP_Open00
static int tolua_SDL_SDL_SDLNet_TCP_Open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"IPaddress",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		IPaddress* ip = ((IPaddress*)  tolua_tousertype(tolua_S,1,0));
		{
			struct _TCPsocket* tolua_ret = (struct _TCPsocket*)  SDLNet_TCP_Open(ip);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_TCPsocket");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_TCP_Open'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_TCP_Accept */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_TCP_Accept00
static int tolua_SDL_SDL_SDLNet_TCP_Accept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TCPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TCPsocket* server = ((struct _TCPsocket*)  tolua_tousertype(tolua_S,1,0));
		{
			struct _TCPsocket* tolua_ret = (struct _TCPsocket*)  SDLNet_TCP_Accept(server);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_TCPsocket");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_TCP_Accept'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_TCP_GetPeerAddress */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_TCP_GetPeerAddress00
static int tolua_SDL_SDL_SDLNet_TCP_GetPeerAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TCPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TCPsocket* sock = ((struct _TCPsocket*)  tolua_tousertype(tolua_S,1,0));
		{
			IPaddress* tolua_ret = (IPaddress*)  SDLNet_TCP_GetPeerAddress(sock);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"IPaddress");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_TCP_GetPeerAddress'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_TCP_Send */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_TCP_Send00
static int tolua_SDL_SDL_SDLNet_TCP_Send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TCPsocket",0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TCPsocket* sock = ((struct _TCPsocket*)  tolua_tousertype(tolua_S,1,0));
		const void* data = ((const void*)  tolua_touserdata(tolua_S,2,0));
		int len = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDLNet_TCP_Send(sock,data,len);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_TCP_Send'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_TCP_Recv */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_TCP_Recv00
static int tolua_SDL_SDL_SDLNet_TCP_Recv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TCPsocket",0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TCPsocket* sock = ((struct _TCPsocket*)  tolua_tousertype(tolua_S,1,0));
		void* data = ((void*)  tolua_touserdata(tolua_S,2,0));
		int maxlen = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDLNet_TCP_Recv(sock,data,maxlen);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_TCP_Recv'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_TCP_Close */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_TCP_Close00
static int tolua_SDL_SDL_SDLNet_TCP_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TCPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TCPsocket* sock = ((struct _TCPsocket*)  tolua_tousertype(tolua_S,1,0));
		{
			SDLNet_TCP_Close(sock);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_TCP_Close'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: channel of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_get_UDPpacket_channel
static int tolua_get_UDPpacket_channel(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'channel'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->channel);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: channel of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_set_UDPpacket_channel
static int tolua_set_UDPpacket_channel(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'channel'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->channel = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: data of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_get_UDPpacket_data
static int tolua_get_UDPpacket_data(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data'",NULL);
#endif
	tolua_pushuserdata(tolua_S,(void*)self->data);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: data of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_set_UDPpacket_data
static int tolua_set_UDPpacket_data(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data'",NULL);
	if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->data = ((Uint8*)  tolua_touserdata(tolua_S,2,0));
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: len of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_get_UDPpacket_len
static int tolua_get_UDPpacket_len(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->len);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: len of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_set_UDPpacket_len
static int tolua_set_UDPpacket_len(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'len'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->len = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxlen of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_get_UDPpacket_maxlen
static int tolua_get_UDPpacket_maxlen(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxlen'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->maxlen);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxlen of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_set_UDPpacket_maxlen
static int tolua_set_UDPpacket_maxlen(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxlen'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->maxlen = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: status of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_get_UDPpacket_status
static int tolua_get_UDPpacket_status(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'status'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->status);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: status of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_set_UDPpacket_status
static int tolua_set_UDPpacket_status(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'status'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->status = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: address of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_get_UDPpacket_address
static int tolua_get_UDPpacket_address(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'address'",NULL);
#endif
	tolua_pushusertype(tolua_S,(void*)&self->address,"IPaddress");
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: address of class  UDPpacket */
#ifndef TOLUA_DISABLE_tolua_set_UDPpacket_address
static int tolua_set_UDPpacket_address(lua_State* tolua_S)
{
	UDPpacket* self = (UDPpacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'address'",NULL);
	if (!tolua_isusertype(tolua_S,2,"IPaddress",0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->address = *((IPaddress*)  tolua_tousertype(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_AllocPacket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_AllocPacket00
static int tolua_SDL_SDL_SDLNet_AllocPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int size = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			UDPpacket* tolua_ret = (UDPpacket*)  SDLNet_AllocPacket(size);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"UDPpacket");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_AllocPacket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_ResizePacket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_ResizePacket00
static int tolua_SDL_SDL_SDLNet_ResizePacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"UDPpacket",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		UDPpacket* packet = ((UDPpacket*)  tolua_tousertype(tolua_S,1,0));
		int newsize = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_ResizePacket(packet,newsize);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_ResizePacket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_FreePacket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_FreePacket00
static int tolua_SDL_SDL_SDLNet_FreePacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"UDPpacket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		UDPpacket* packet = ((UDPpacket*)  tolua_tousertype(tolua_S,1,0));
		{
			SDLNet_FreePacket(packet);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_FreePacket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_Open */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_Open00
static int tolua_SDL_SDL_SDLNet_UDP_Open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned short port = ((  unsigned short)  tolua_tonumber(tolua_S,1,0));
		{
			struct _UDPsocket* tolua_ret = (struct _UDPsocket*)  SDLNet_UDP_Open(port);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_UDPsocket");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_Open'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_Bind */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_Bind00
static int tolua_SDL_SDL_SDLNet_UDP_Bind00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_UDPsocket",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"IPaddress",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,1,0));
		int channel = ((int)  tolua_tonumber(tolua_S,2,0));
		IPaddress* address = ((IPaddress*)  tolua_tousertype(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDLNet_UDP_Bind(sock,channel,address);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_Bind'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_Unbind */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_Unbind00
static int tolua_SDL_SDL_SDLNet_UDP_Unbind00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_UDPsocket",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,1,0));
		int channel = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			SDLNet_UDP_Unbind(sock,channel);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_Unbind'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_GetPeerAddress */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_GetPeerAddress00
static int tolua_SDL_SDL_SDLNet_UDP_GetPeerAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_UDPsocket",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,1,0));
		int channel = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			IPaddress* tolua_ret = (IPaddress*)  SDLNet_UDP_GetPeerAddress(sock,channel);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"IPaddress");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_GetPeerAddress'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_Send */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_Send00
static int tolua_SDL_SDL_SDLNet_UDP_Send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_UDPsocket",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"UDPpacket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,1,0));
		int channel = ((int)  tolua_tonumber(tolua_S,2,0));
		UDPpacket* packet = ((UDPpacket*)  tolua_tousertype(tolua_S,3,0));
		{
			int tolua_ret = (int)  SDLNet_UDP_Send(sock,channel,packet);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_Send'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_Recv */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_Recv00
static int tolua_SDL_SDL_SDLNet_UDP_Recv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_UDPsocket",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"UDPpacket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,1,0));
		UDPpacket* packet = ((UDPpacket*)  tolua_tousertype(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_UDP_Recv(sock,packet);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_Recv'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_Close */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_Close00
static int tolua_SDL_SDL_SDLNet_UDP_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_UDPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,1,0));
		{
			SDLNet_UDP_Close(sock);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_Close'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ready of class  _SDLNet_GenericSocket */
#ifndef TOLUA_DISABLE_tolua_get__SDLNet_GenericSocket_ready
static int tolua_get__SDLNet_GenericSocket_ready(lua_State* tolua_S)
{
	_SDLNet_GenericSocket* self = (_SDLNet_GenericSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ready'",NULL);
#endif
	tolua_pushnumber(tolua_S,(lua_Number)self->ready);
	return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ready of class  _SDLNet_GenericSocket */
#ifndef TOLUA_DISABLE_tolua_set__SDLNet_GenericSocket_ready
static int tolua_set__SDLNet_GenericSocket_ready(lua_State* tolua_S)
{
	_SDLNet_GenericSocket* self = (_SDLNet_GenericSocket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ready'",NULL);
	if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
		tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
	self->ready = ((int)  tolua_tonumber(tolua_S,2,0))
		;
	return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_AllocSocketSet */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_AllocSocketSet00
static int tolua_SDL_SDL_SDLNet_AllocSocketSet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int maxsockets = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			struct _SDLNet_SocketSet* tolua_ret = (struct _SDLNet_SocketSet*)  SDLNet_AllocSocketSet(maxsockets);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_SDLNet_SocketSet");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_AllocSocketSet'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_AddSocket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_AddSocket00
static int tolua_SDL_SDL_SDLNet_AddSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_SocketSet",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"_SDLNet_GenericSocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_SocketSet* set = ((struct _SDLNet_SocketSet*)  tolua_tousertype(tolua_S,1,0));
		struct _SDLNet_GenericSocket* sock = ((struct _SDLNet_GenericSocket*)  tolua_tousertype(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_AddSocket(set,(SDLNet_GenericSocket)sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_AddSocket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_DelSocket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_DelSocket00
static int tolua_SDL_SDL_SDLNet_DelSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_SocketSet",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"_SDLNet_GenericSocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_SocketSet* set = ((struct _SDLNet_SocketSet*)  tolua_tousertype(tolua_S,1,0));
		struct _SDLNet_GenericSocket* sock = ((struct _SDLNet_GenericSocket*)  tolua_tousertype(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_DelSocket(set,(SDLNet_GenericSocket)sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_DelSocket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_CheckSockets */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_CheckSockets00
static int tolua_SDL_SDL_SDLNet_CheckSockets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_SocketSet",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_SocketSet* set = ((struct _SDLNet_SocketSet*)  tolua_tousertype(tolua_S,1,0));
		unsigned int timeout = ((  unsigned int)  tolua_tonumber(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_CheckSockets(set,timeout);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_CheckSockets'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_FreeSocketSet */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_FreeSocketSet00
static int tolua_SDL_SDL_SDLNet_FreeSocketSet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_SocketSet",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_SocketSet* set = ((struct _SDLNet_SocketSet*)  tolua_tousertype(tolua_S,1,0));
		{
			SDLNet_FreeSocketSet(set);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_FreeSocketSet'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_TCP_AddSocket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_TCP_AddSocket00
static int tolua_SDL_SDL_SDLNet_TCP_AddSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_SocketSet",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"_TCPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_SocketSet* set = ((struct _SDLNet_SocketSet*)  tolua_tousertype(tolua_S,1,0));
		struct _TCPsocket* sock = ((struct _TCPsocket*)  tolua_tousertype(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_TCP_AddSocket(set,sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_TCP_AddSocket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_AddSocket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_AddSocket00
static int tolua_SDL_SDL_SDLNet_UDP_AddSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_SocketSet",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"_UDPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_SocketSet* set = ((struct _SDLNet_SocketSet*)  tolua_tousertype(tolua_S,1,0));
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_UDP_AddSocket(set,sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_AddSocket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_TCP_DelSocket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_TCP_DelSocket00
static int tolua_SDL_SDL_SDLNet_TCP_DelSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_SocketSet",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"_TCPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_SocketSet* set = ((struct _SDLNet_SocketSet*)  tolua_tousertype(tolua_S,1,0));
		struct _TCPsocket* sock = ((struct _TCPsocket*)  tolua_tousertype(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_TCP_DelSocket(set,sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_TCP_DelSocket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_UDP_DelSocket */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_UDP_DelSocket00
static int tolua_SDL_SDL_SDLNet_UDP_DelSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_SocketSet",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,2,"_UDPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_SocketSet* set = ((struct _SDLNet_SocketSet*)  tolua_tousertype(tolua_S,1,0));
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,2,0));
		{
			int tolua_ret = (int)  SDLNet_UDP_DelSocket(set,sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_UDP_DelSocket'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: _SDLNet_SocketReady */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_SocketReady00
static int tolua_SDL_SDL_SDLNet_SocketReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_SDLNet_GenericSocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _SDLNet_GenericSocket* sock = ((struct _SDLNet_GenericSocket*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_bool tolua_ret = (SDL_bool)  _SDLNet_SocketReady((SDLNet_GenericSocket)sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_SocketReady'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: _SDLNet_TCP_SocketReady */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_SocketReady01
static int tolua_SDL_SDL_SDLNet_SocketReady01(lua_State* tolua_S)
{
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TCPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
	{
		struct _TCPsocket* sock = ((struct _TCPsocket*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_bool tolua_ret = (SDL_bool)  _SDLNet_TCP_SocketReady(sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
tolua_lerror:
	return tolua_SDL_SDL_SDLNet_SocketReady00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: _SDLNet_UDP_SocketReady */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_SocketReady02
static int tolua_SDL_SDL_SDLNet_SocketReady02(lua_State* tolua_S)
{
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_UDPsocket",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
	{
		struct _UDPsocket* sock = ((struct _UDPsocket*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_bool tolua_ret = (SDL_bool)  _SDLNet_UDP_SocketReady(sock);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
tolua_lerror:
	return tolua_SDL_SDL_SDLNet_SocketReady01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_Write16 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_Write1600
static int tolua_SDL_SDL_SDLNet_Write1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned short value = ((  unsigned short)  tolua_tonumber(tolua_S,1,0));
		void* area = ((void*)  tolua_touserdata(tolua_S,2,0));
		{
			SDLNet_Write16(value,area);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_Write16'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_Write32 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_Write3200
static int tolua_SDL_SDL_SDLNet_Write3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		unsigned int value = ((  unsigned int)  tolua_tonumber(tolua_S,1,0));
		void* area = ((void*)  tolua_touserdata(tolua_S,2,0));
		{
			SDLNet_Write32(value,area);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_Write32'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_Read16 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_Read1600
static int tolua_SDL_SDL_SDLNet_Read1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* area = ((void*)  tolua_touserdata(tolua_S,1,0));
		{
			unsigned short tolua_ret = (  unsigned short)  SDLNet_Read16(area);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_Read16'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDLNet_Read32 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDLNet_Read3200
static int tolua_SDL_SDL_SDLNet_Read3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* area = ((void*)  tolua_touserdata(tolua_S,1,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDLNet_Read32(area);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDLNet_Read32'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_TTF_VERSION */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_TTF_VERSION00
static int tolua_SDL_SDL_SDL_TTF_VERSION00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_version",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_version* ver_info = ((SDL_version*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_TTF_VERSION(ver_info);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_TTF_VERSION'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_ByteSwappedUNICODE */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_ByteSwappedUNICODE00
static int tolua_SDL_SDL_TTF_ByteSwappedUNICODE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnumber(tolua_S,1,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		int swapped = ((int)  tolua_tonumber(tolua_S,1,0));
		{
			TTF_ByteSwappedUNICODE(swapped);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_ByteSwappedUNICODE'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_Init */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_Init00
static int tolua_SDL_SDL_TTF_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  TTF_Init();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_Init'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_OpenFont */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_OpenFont00
static int tolua_SDL_SDL_TTF_OpenFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
		int ptsize = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			struct _TTF_Font* tolua_ret = ( struct _TTF_Font*)  TTF_OpenFont(file,ptsize);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_TTF_Font");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_OpenFont'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_OpenFontIndex */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_OpenFontIndex00
static int tolua_SDL_SDL_TTF_OpenFontIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isstring(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
		int ptsize = ((int)  tolua_tonumber(tolua_S,2,0));
		long index = ((long)  tolua_tonumber(tolua_S,3,0));
		{
			struct _TTF_Font* tolua_ret = ( struct _TTF_Font*)  TTF_OpenFontIndex(file,ptsize,index);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_TTF_Font");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_OpenFontIndex'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_OpenFontRW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_OpenFontRW00
static int tolua_SDL_SDL_TTF_OpenFontRW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		int freesrc = ((int)  tolua_tonumber(tolua_S,2,0));
		int ptsize = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			struct _TTF_Font* tolua_ret = ( struct _TTF_Font*)  TTF_OpenFontRW(src,freesrc,ptsize);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_TTF_Font");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_OpenFontRW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_OpenFontIndexRW */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_OpenFontIndexRW00
static int tolua_SDL_SDL_TTF_OpenFontIndexRW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_RWops",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_RWops* src = ((SDL_RWops*)  tolua_tousertype(tolua_S,1,0));
		int freesrc = ((int)  tolua_tonumber(tolua_S,2,0));
		int ptsize = ((int)  tolua_tonumber(tolua_S,3,0));
		long index = ((long)  tolua_tonumber(tolua_S,4,0));
		{
			struct _TTF_Font* tolua_ret = ( struct _TTF_Font*)  TTF_OpenFontIndexRW(src,freesrc,ptsize,index);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"_TTF_Font");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_OpenFontIndexRW'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_GetFontStyle */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_GetFontStyle00
static int tolua_SDL_SDL_TTF_GetFontStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  TTF_GetFontStyle(font);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_GetFontStyle'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_SetFontStyle */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_SetFontStyle00
static int tolua_SDL_SDL_TTF_SetFontStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,3,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		int style = ((int)  tolua_tonumber(tolua_S,2,0));
		{
			TTF_SetFontStyle(font,style);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_SetFontStyle'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_FontHeight */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_FontHeight00
static int tolua_SDL_SDL_TTF_FontHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  TTF_FontHeight(font);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_FontHeight'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_FontAscent */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_FontAscent00
static int tolua_SDL_SDL_TTF_FontAscent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  TTF_FontAscent(font);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_FontAscent'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_FontDescent */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_FontDescent00
static int tolua_SDL_SDL_TTF_FontDescent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  TTF_FontDescent(font);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_FontDescent'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_FontLineSkip */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_FontLineSkip00
static int tolua_SDL_SDL_TTF_FontLineSkip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  TTF_FontLineSkip(font);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_FontLineSkip'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_FontFaces */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_FontFaces00
static int tolua_SDL_SDL_TTF_FontFaces00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			long tolua_ret = (long)  TTF_FontFaces(font);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_FontFaces'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_FontFaceIsFixedWidth */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_FontFaceIsFixedWidth00
static int tolua_SDL_SDL_TTF_FontFaceIsFixedWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			int tolua_ret = (int)  TTF_FontFaceIsFixedWidth(font);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_FontFaceIsFixedWidth'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_FontFaceFamilyName */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_FontFaceFamilyName00
static int tolua_SDL_SDL_TTF_FontFaceFamilyName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  TTF_FontFaceFamilyName(font);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_FontFaceFamilyName'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_FontFaceStyleName */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_FontFaceStyleName00
static int tolua_SDL_SDL_TTF_FontFaceStyleName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			char* tolua_ret = (char*)  TTF_FontFaceStyleName(font);
			tolua_pushstring(tolua_S,(const char*)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_FontFaceStyleName'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_GlyphMetrics */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_GlyphMetrics00
static int tolua_SDL_SDL_TTF_GlyphMetrics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,6,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,7,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,8,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		unsigned short ch = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		int minx = ((int)  tolua_tonumber(tolua_S,3,0));
		int maxx = ((int)  tolua_tonumber(tolua_S,4,0));
		int miny = ((int)  tolua_tonumber(tolua_S,5,0));
		int maxy = ((int)  tolua_tonumber(tolua_S,6,0));
		int advance = ((int)  tolua_tonumber(tolua_S,7,0));
		{
			int tolua_ret = (int)  TTF_GlyphMetrics(font,ch,&minx,&maxx,&miny,&maxy,&advance);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)minx);
			tolua_pushnumber(tolua_S,(lua_Number)maxx);
			tolua_pushnumber(tolua_S,(lua_Number)miny);
			tolua_pushnumber(tolua_S,(lua_Number)maxy);
			tolua_pushnumber(tolua_S,(lua_Number)advance);
		}
	}
	return 6;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_GlyphMetrics'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_SizeText */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_SizeText00
static int tolua_SDL_SDL_TTF_SizeText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
		int w = ((int)  tolua_tonumber(tolua_S,3,0));
		int h = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  TTF_SizeText(font,text,&w,&h);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)w);
			tolua_pushnumber(tolua_S,(lua_Number)h);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_SizeText'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_SizeUTF8 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_SizeUTF800
static int tolua_SDL_SDL_TTF_SizeUTF800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
		int w = ((int)  tolua_tonumber(tolua_S,3,0));
		int h = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  TTF_SizeUTF8(font,text,&w,&h);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)w);
			tolua_pushnumber(tolua_S,(lua_Number)h);
		}
	}
	return 3;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_SizeUTF8'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_SizeUNICODE */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_SizeUNICODE00
static int tolua_SDL_SDL_TTF_SizeUNICODE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		unsigned const short text = ((unsigned const short)  tolua_tonumber(tolua_S,2,0));
		int w = ((int)  tolua_tonumber(tolua_S,3,0));
		int h = ((int)  tolua_tonumber(tolua_S,4,0));
		{
			int tolua_ret = (int)  TTF_SizeUNICODE(font,&text,&w,&h);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
			tolua_pushnumber(tolua_S,(lua_Number)text);
			tolua_pushnumber(tolua_S,(lua_Number)w);
			tolua_pushnumber(tolua_S,(lua_Number)h);
		}
	}
	return 4;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_SizeUNICODE'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderText_Solid */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderText_Solid00
static int tolua_SDL_SDL_TTF_RenderText_Solid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderText_Solid(font,text,fg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderText_Solid'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderUTF8_Solid */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderUTF8_Solid00
static int tolua_SDL_SDL_TTF_RenderUTF8_Solid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderUTF8_Solid(font,text,fg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderUTF8_Solid'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderUNICODE_Solid */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderUNICODE_Solid00
static int tolua_SDL_SDL_TTF_RenderUNICODE_Solid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		unsigned const short text = ((unsigned const short)  tolua_tonumber(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderUNICODE_Solid(font,&text,fg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
			tolua_pushnumber(tolua_S,(lua_Number)text);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderUNICODE_Solid'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderGlyph_Solid */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderGlyph_Solid00
static int tolua_SDL_SDL_TTF_RenderGlyph_Solid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		unsigned short ch = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderGlyph_Solid(font,ch,fg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderGlyph_Solid'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderText_Shaded */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderText_Shaded00
static int tolua_SDL_SDL_TTF_RenderText_Shaded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,4,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		SDL_Color bg = *((SDL_Color*)  tolua_tousertype(tolua_S,4,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderText_Shaded(font,text,fg,bg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderText_Shaded'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderUTF8_Shaded */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderUTF8_Shaded00
static int tolua_SDL_SDL_TTF_RenderUTF8_Shaded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,4,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		SDL_Color bg = *((SDL_Color*)  tolua_tousertype(tolua_S,4,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderUTF8_Shaded(font,text,fg,bg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderUTF8_Shaded'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderUNICODE_Shaded */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderUNICODE_Shaded00
static int tolua_SDL_SDL_TTF_RenderUNICODE_Shaded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,4,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		unsigned const short text = ((unsigned const short)  tolua_tonumber(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		SDL_Color bg = *((SDL_Color*)  tolua_tousertype(tolua_S,4,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderUNICODE_Shaded(font,&text,fg,bg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
			tolua_pushnumber(tolua_S,(lua_Number)text);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderUNICODE_Shaded'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderGlyph_Shaded */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderGlyph_Shaded00
static int tolua_SDL_SDL_TTF_RenderGlyph_Shaded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isusertype(tolua_S,4,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		unsigned short ch = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		SDL_Color bg = *((SDL_Color*)  tolua_tousertype(tolua_S,4,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderGlyph_Shaded(font,ch,fg,bg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderGlyph_Shaded'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderText_Blended */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderText_Blended00
static int tolua_SDL_SDL_TTF_RenderText_Blended00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderText_Blended(font,text,fg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderText_Blended'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderUTF8_Blended */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderUTF8_Blended00
static int tolua_SDL_SDL_TTF_RenderUTF8_Blended00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderUTF8_Blended(font,text,fg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderUTF8_Blended'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderUNICODE_Blended */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderUNICODE_Blended00
static int tolua_SDL_SDL_TTF_RenderUNICODE_Blended00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		unsigned const short text = ((unsigned const short)  tolua_tonumber(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderUNICODE_Blended(font,&text,fg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
			tolua_pushnumber(tolua_S,(lua_Number)text);
		}
	}
	return 2;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderUNICODE_Blended'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_RenderGlyph_Blended */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_RenderGlyph_Blended00
static int tolua_SDL_SDL_TTF_RenderGlyph_Blended00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isusertype(tolua_S,3,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		unsigned short ch = ((  unsigned short)  tolua_tonumber(tolua_S,2,0));
		SDL_Color fg = *((SDL_Color*)  tolua_tousertype(tolua_S,3,0));
		{
			SDL_Surface* tolua_ret = (SDL_Surface*)  TTF_RenderGlyph_Blended(font,ch,fg);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Surface");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_RenderGlyph_Blended'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_CloseFont */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_CloseFont00
static int tolua_SDL_SDL_TTF_CloseFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"_TTF_Font",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		struct _TTF_Font* font = (( struct _TTF_Font*)  tolua_tousertype(tolua_S,1,0));
		{
			TTF_CloseFont(font);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_CloseFont'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_Quit */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_Quit00
static int tolua_SDL_SDL_TTF_Quit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			TTF_Quit();
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_Quit'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TTF_WasInit */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_TTF_WasInit00
static int tolua_SDL_SDL_TTF_WasInit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			int tolua_ret = (int)  TTF_WasInit();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'TTF_WasInit'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_GetPixel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_GetPixel00
static int tolua_SDL_SDL_SDL_GetPixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,4,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		int x = ((int)  tolua_tonumber(tolua_S,2,0));
		int y = ((int)  tolua_tonumber(tolua_S,3,0));
		{
			unsigned int tolua_ret = (  unsigned int)  SDL_GetPixel(surface,x,y);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_GetPixel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_PutPixel */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_PutPixel00
static int tolua_SDL_SDL_SDL_PutPixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Surface",0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,1,0));
		int x = ((int)  tolua_tonumber(tolua_S,2,0));
		int y = ((int)  tolua_tonumber(tolua_S,3,0));
		unsigned int pixel = ((  unsigned int)  tolua_tonumber(tolua_S,4,0));
		{
			SDL_PutPixel(surface,x,y,pixel);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_PutPixel'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LuaSDL_AudioCh1 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_LuaSDL_AudioCh100
static int tolua_SDL_SDL_LuaSDL_AudioCh100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* audio_buf = ((void*)  tolua_touserdata(tolua_S,1,0));
		unsigned int audio_len = ((  unsigned int)  tolua_tonumber(tolua_S,2,0));
		int loop = ((int)  tolua_tonumber(tolua_S,3,0));
		int volume = ((int)  tolua_tonumber(tolua_S,4,SDL_MIX_MAXVOLUME));
		{
			LuaSDL_AudioCh1(audio_buf,audio_len,loop,volume);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'LuaSDL_AudioCh1'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LuaSDL_AudioCh2 */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_LuaSDL_AudioCh200
static int tolua_SDL_SDL_LuaSDL_AudioCh200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,3,1,&tolua_err) ||
		!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
		!tolua_isnoobj(tolua_S,5,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		void* audio_buf = ((void*)  tolua_touserdata(tolua_S,1,0));
		unsigned int audio_len = ((  unsigned int)  tolua_tonumber(tolua_S,2,0));
		int loop = ((int)  tolua_tonumber(tolua_S,3,0));
		int volume = ((int)  tolua_tonumber(tolua_S,4,SDL_MIX_MAXVOLUME));
		{
			LuaSDL_AudioCh2(audio_buf,audio_len,loop,volume);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'LuaSDL_AudioCh2'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_AudioSpec_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_AudioSpec_new00
static int tolua_SDL_SDL_SDL_AudioSpec_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_AudioSpec* tolua_ret = (SDL_AudioSpec*)  SDL_AudioSpec_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_AudioSpec");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_AudioSpec_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_AudioSpec_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_AudioSpec_delete00
static int tolua_SDL_SDL_SDL_AudioSpec_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_AudioSpec",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_AudioSpec* obj = ((SDL_AudioSpec*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_AudioSpec_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_AudioSpec_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_AudioCVT_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_AudioCVT_new00
static int tolua_SDL_SDL_SDL_AudioCVT_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_AudioCVT* tolua_ret = (SDL_AudioCVT*)  SDL_AudioCVT_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_AudioCVT");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_AudioCVT_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_AudioCVT_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_AudioCVT_delete00
static int tolua_SDL_SDL_SDL_AudioCVT_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_AudioCVT",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_AudioCVT* obj = ((SDL_AudioCVT*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_AudioCVT_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_AudioCVT_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDtrack_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDtrack_new00
static int tolua_SDL_SDL_SDL_CDtrack_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_CDtrack* tolua_ret = (SDL_CDtrack*)  SDL_CDtrack_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_CDtrack");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDtrack_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CDtrack_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CDtrack_delete00
static int tolua_SDL_SDL_SDL_CDtrack_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CDtrack",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CDtrack* obj = ((SDL_CDtrack*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_CDtrack_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CDtrack_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CD_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CD_new00
static int tolua_SDL_SDL_SDL_CD_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_CD* tolua_ret = (SDL_CD*)  SDL_CD_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_CD");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CD_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_CD_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CD_delete00
static int tolua_SDL_SDL_SDL_CD_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_CD",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_CD* obj = ((SDL_CD*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_CD_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CD_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Event_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Event_new00
static int tolua_SDL_SDL_SDL_Event_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_Event* tolua_ret = (SDL_Event*)  SDL_Event_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Event");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Event_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Event_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Event_delete00
static int tolua_SDL_SDL_SDL_Event_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Event",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Event* obj = ((SDL_Event*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Event_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Event_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_keysym_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_keysym_new00
static int tolua_SDL_SDL_SDL_keysym_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_keysym* tolua_ret = (SDL_keysym*)  SDL_keysym_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_keysym");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_keysym_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_keysym_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_keysym_delete00
static int tolua_SDL_SDL_SDL_keysym_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_keysym",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_keysym* obj = ((SDL_keysym*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_keysym_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_keysym_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Cursor_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Cursor_new00
static int tolua_SDL_SDL_SDL_Cursor_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_Cursor* tolua_ret = (SDL_Cursor*)  SDL_Cursor_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Cursor");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Cursor_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Cursor_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Cursor_delete00
static int tolua_SDL_SDL_SDL_Cursor_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Cursor",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Cursor* obj = ((SDL_Cursor*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Cursor_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Cursor_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IPaddress_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IPaddress_new00
static int tolua_SDL_SDL_IPaddress_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			IPaddress* tolua_ret = (IPaddress*)  IPaddress_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"IPaddress");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IPaddress_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IPaddress_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_IPaddress_delete00
static int tolua_SDL_SDL_IPaddress_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"IPaddress",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		IPaddress* obj = ((IPaddress*)  tolua_tousertype(tolua_S,1,0));
		{
			IPaddress_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'IPaddress_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_version_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_version_new00
static int tolua_SDL_SDL_SDL_version_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_version* tolua_ret = (SDL_version*)  SDL_version_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_version");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_version_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_version_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_version_delete00
static int tolua_SDL_SDL_SDL_version_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_version",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_version* obj = ((SDL_version*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_version_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_version_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Rect_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Rect_new00
static int tolua_SDL_SDL_SDL_Rect_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_Rect* tolua_ret = (SDL_Rect*)  SDL_Rect_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Rect");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Rect_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Rect_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Rect_delete00
static int tolua_SDL_SDL_SDL_Rect_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Rect",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Rect* obj = ((SDL_Rect*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Rect_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Rect_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Color_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Color_new00
static int tolua_SDL_SDL_SDL_Color_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_Color* tolua_ret = (SDL_Color*)  SDL_Color_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Color");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Color_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Color_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_Color_delete00
static int tolua_SDL_SDL_SDL_Color_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Color",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_Color* obj = ((SDL_Color*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_Color_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_Color_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_CreateMutex
static int tolua_SDL_SDL_SDL_CreateMutex(lua_State * tolua_S){
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_mutex* tolua_ret = (SDL_mutex*) SDL_CreateMutex();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_Mutex");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_CreateMutex'.",&tolua_err);
	return 0;
#endif
}
#endif

#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_DestroyMutex
static int tolua_SDL_SDL_SDL_DestroyMutex(lua_State * tolua_S){
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Mutex",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_mutex* tolua_ret = (SDL_mutex*)  tolua_tousertype(tolua_S,1,0);
			SDL_DestroyMutex(tolua_ret);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_DestroyMutex'.",&tolua_err);
	return 0;
#endif
}
#endif

#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_LockMutex
static int tolua_SDL_SDL_SDL_LockMutex(lua_State * tolua_S){
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Mutex",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_mutex* tolua_ret = (SDL_mutex*)  tolua_tousertype(tolua_S,1,0);
			SDL_LockMutex(tolua_ret);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_LockMutex'.",&tolua_err);
	return 0;
#endif
}
#endif

#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_UnlockMutex
static int tolua_SDL_SDL_SDL_UnlockMutex(lua_State * tolua_S){
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_Mutex",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_mutex* tolua_ret = (SDL_mutex*)  tolua_tousertype(tolua_S,1,0);
			SDL_UnlockMutex(tolua_ret);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_UnlockMutex'.",&tolua_err);
	return 0;
#endif
}
#endif


/* function: SDL_PixelFormat_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_PixelFormat_new00
static int tolua_SDL_SDL_SDL_PixelFormat_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_PixelFormat",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_PixelFormat* tolua_ret = (SDL_PixelFormat*)  SDL_PixelFormat_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_PixelFormat");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_PixelFormat_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_PixelFormat_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_PixelFormat_delete00
static int tolua_SDL_SDL_SDL_PixelFormat_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_PixelFormat",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_PixelFormat* obj = ((SDL_PixelFormat*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_PixelFormat_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_PixelFormat_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_VideoInfo_new */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_VideoInfo_new00
static int tolua_SDL_SDL_SDL_VideoInfo_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isnoobj(tolua_S,1,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		{
			SDL_VideoInfo* tolua_ret = (SDL_VideoInfo*)  SDL_VideoInfo_new();
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"SDL_VideoInfo");
		}
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_VideoInfo_new'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_VideoInfo_delete */
#ifndef TOLUA_DISABLE_tolua_SDL_SDL_SDL_VideoInfo_delete00
static int tolua_SDL_SDL_SDL_VideoInfo_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"SDL_VideoInfo",0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,2,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		SDL_VideoInfo* obj = ((SDL_VideoInfo*)  tolua_tousertype(tolua_S,1,0));
		{
			SDL_VideoInfo_delete(obj);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'SDL_VideoInfo_delete'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SDL_open (lua_State* tolua_S)
{
	tolua_open(tolua_S);
	tolua_reg_types(tolua_S);
	tolua_module(tolua_S,NULL,0);
	tolua_beginmodule(tolua_S,NULL);
	tolua_module(tolua_S,"SDL",1);
	tolua_beginmodule(tolua_S,"SDL");
	tolua_constant(tolua_S,"__WIN32__",__WIN32__);
	tolua_constant(tolua_S,"SDL_AUDIO_DRIVER_DSOUND",SDL_AUDIO_DRIVER_DSOUND);
	tolua_constant(tolua_S,"SDL_AUDIO_DRIVER_WAVEOUT",SDL_AUDIO_DRIVER_WAVEOUT);
	tolua_constant(tolua_S,"SDL_AUDIO_DRIVER_DISK",SDL_AUDIO_DRIVER_DISK);
	tolua_constant(tolua_S,"SDL_AUDIO_DRIVER_DUMMY",SDL_AUDIO_DRIVER_DUMMY);
	tolua_constant(tolua_S,"SDL_CDROM_WIN32",SDL_CDROM_WIN32);
	tolua_constant(tolua_S,"SDL_JOYSTICK_WINMM",SDL_JOYSTICK_WINMM);
	tolua_constant(tolua_S,"SDL_LOADSO_WIN32",SDL_LOADSO_WIN32);
	tolua_constant(tolua_S,"SDL_THREAD_WIN32",SDL_THREAD_WIN32);
	tolua_constant(tolua_S,"SDL_TIMER_WIN32",SDL_TIMER_WIN32);
	tolua_constant(tolua_S,"SDL_VIDEO_DRIVER_DDRAW",SDL_VIDEO_DRIVER_DDRAW);
	tolua_constant(tolua_S,"SDL_VIDEO_DRIVER_DUMMY",SDL_VIDEO_DRIVER_DUMMY);
	tolua_constant(tolua_S,"SDL_VIDEO_DRIVER_WINDIB",SDL_VIDEO_DRIVER_WINDIB);
	tolua_constant(tolua_S,"SDL_VIDEO_OPENGL",SDL_VIDEO_OPENGL);
	tolua_constant(tolua_S,"SDL_VIDEO_OPENGL_WGL",SDL_VIDEO_OPENGL_WGL);
	tolua_constant(tolua_S,"SDL_ASSEMBLY_ROUTINES",SDL_ASSEMBLY_ROUTINES);
	tolua_constant(tolua_S,"SDL_BYTEORDER",SDL_BYTEORDER);
	tolua_constant(tolua_S,"SDL_FALSE",SDL_FALSE);
	tolua_constant(tolua_S,"SDL_TRUE",SDL_TRUE);
#ifdef __WIN32__
	tolua_function(tolua_S,"SDL_shellExecute",tolua_SDL_SDL_SDL_shell_execute00);
#endif
	tolua_function(tolua_S,"SDL_malloc",tolua_SDL_SDL_SDL_malloc00);
	tolua_function(tolua_S,"SDL_calloc",tolua_SDL_SDL_SDL_calloc00);
	tolua_function(tolua_S,"SDL_realloc",tolua_SDL_SDL_SDL_realloc00);
	tolua_function(tolua_S,"SDL_free",tolua_SDL_SDL_SDL_free00);
	tolua_function(tolua_S,"SDL_getenv",tolua_SDL_SDL_SDL_getenv00);
	tolua_function(tolua_S,"SDL_putenv",tolua_SDL_SDL_SDL_putenv00);
	tolua_function(tolua_S,"SDL_isdigit",tolua_SDL_SDL_SDL_isdigit00);
	tolua_function(tolua_S,"SDL_isspace",tolua_SDL_SDL_SDL_isspace00);
	tolua_function(tolua_S,"SDL_toupper",tolua_SDL_SDL_SDL_toupper00);
	tolua_function(tolua_S,"SDL_tolower",tolua_SDL_SDL_SDL_tolower00);
	tolua_function(tolua_S,"SDL_memset",tolua_SDL_SDL_SDL_memset00);
	tolua_function(tolua_S,"SDL_memcpy",tolua_SDL_SDL_SDL_memcpy00);
	tolua_function(tolua_S,"SDL_revcpy",tolua_SDL_SDL_SDL_revcpy00);
	tolua_function(tolua_S,"SDL_memmove",tolua_SDL_SDL_SDL_memmove00);
	tolua_function(tolua_S,"SDL_memcmp",tolua_SDL_SDL_SDL_memcmp00);
	tolua_function(tolua_S,"SDL_strlen",tolua_SDL_SDL_SDL_strlen00);
	tolua_function(tolua_S,"SDL_strlcpy",tolua_SDL_SDL_SDL_strlcpy00);
	tolua_function(tolua_S,"SDL_strlcat",tolua_SDL_SDL_SDL_strlcat00);
	tolua_function(tolua_S,"SDL_strdup",tolua_SDL_SDL_SDL_strdup00);
	tolua_function(tolua_S,"SDL_strrev",tolua_SDL_SDL_SDL_strrev00);
	tolua_function(tolua_S,"SDL_strupr",tolua_SDL_SDL_SDL_strupr00);
	tolua_function(tolua_S,"SDL_strlwr",tolua_SDL_SDL_SDL_strlwr00);
	tolua_function(tolua_S,"SDL_strchr",tolua_SDL_SDL_SDL_strchr00);
	tolua_function(tolua_S,"SDL_strrchr",tolua_SDL_SDL_SDL_strrchr00);
	tolua_function(tolua_S,"SDL_strstr",tolua_SDL_SDL_SDL_strstr00);
	tolua_function(tolua_S,"SDL_itoa",tolua_SDL_SDL_SDL_itoa00);
	tolua_function(tolua_S,"SDL_ltoa",tolua_SDL_SDL_SDL_ltoa00);
	tolua_function(tolua_S,"SDL_uitoa",tolua_SDL_SDL_SDL_uitoa00);
	tolua_function(tolua_S,"SDL_ultoa",tolua_SDL_SDL_SDL_ultoa00);
	tolua_function(tolua_S,"SDL_strtol",tolua_SDL_SDL_SDL_strtol00);
	tolua_function(tolua_S,"SDL_strtoul",tolua_SDL_SDL_SDL_strtoul00);
	tolua_function(tolua_S,"SDL_strtod",tolua_SDL_SDL_SDL_strtod00);
	tolua_function(tolua_S,"SDL_atoi",tolua_SDL_SDL_SDL_atoi00);
	tolua_function(tolua_S,"SDL_atof",tolua_SDL_SDL_SDL_atof00);
	tolua_function(tolua_S,"SDL_strcmp",tolua_SDL_SDL_SDL_strcmp00);
	tolua_function(tolua_S,"SDL_strncmp",tolua_SDL_SDL_SDL_strncmp00);
	tolua_function(tolua_S,"SDL_strcasecmp",tolua_SDL_SDL_SDL_strcasecmp00);
	tolua_function(tolua_S,"SDL_strncasecmp",tolua_SDL_SDL_SDL_strncasecmp00);
	tolua_constant(tolua_S,"SDL_ICONV_ERROR",SDL_ICONV_ERROR);
	tolua_constant(tolua_S,"SDL_ICONV_E2BIG",SDL_ICONV_E2BIG);
	tolua_constant(tolua_S,"SDL_ICONV_EILSEQ",SDL_ICONV_EILSEQ);
	tolua_constant(tolua_S,"SDL_ICONV_EINVAL",SDL_ICONV_EINVAL);
	tolua_cclass(tolua_S,"_SDL_iconv_t","_SDL_iconv_t","",NULL);
	tolua_beginmodule(tolua_S,"_SDL_iconv_t");
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDL_iconv_open",tolua_SDL_SDL_SDL_iconv_open00);
	tolua_function(tolua_S,"SDL_iconv_close",tolua_SDL_SDL_SDL_iconv_close00);
	tolua_function(tolua_S,"SDL_iconv",tolua_SDL_SDL_SDL_iconv00);
	tolua_function(tolua_S,"SDL_iconv_string",tolua_SDL_SDL_SDL_iconv_string00);
	tolua_function(tolua_S,"SDL_utf8_decode",tolua_SDL_SDL_SDL_utf8_decode00);
	tolua_function(tolua_S,"SDL_iconv_utf8_locale",tolua_SDL_SDL_SDL_iconv_utf8_locale00);
	tolua_function(tolua_S,"SDL_iconv_utf8_ucs2",tolua_SDL_SDL_SDL_iconv_utf8_ucs200);
	tolua_function(tolua_S,"SDL_iconv_utf8_ucs4",tolua_SDL_SDL_SDL_iconv_utf8_ucs400);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10, 83, 68, 76, 46, 83, 68, 76, 95, 97, 98,115, 32, 61, 32,
			109, 97,116,104, 46, 97, 98,115, 10, 83, 68, 76, 46, 83, 68,
			76, 95,109,105,110, 32, 61, 32,109, 97,116,104, 46,109,105,
			110, 10, 83, 68, 76, 46, 83, 68, 76, 95,109, 97,120, 32, 61,
			32,109, 97,116,104, 46,109, 97,120, 10, 83, 68, 76, 46, 83,
			68, 76, 95,109,101,109,115,101,116, 52, 32, 61, 32, 83, 68,
			76, 46, 83, 68, 76, 95,109,101,109,115,101,116, 10, 83, 68,
			76, 46, 83, 68, 76, 95,109,101,109, 99,112,121, 52, 32, 61,
			32, 83, 68, 76, 46, 83, 68, 76, 95,109,101,109, 99,112,121,
			32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 1");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_cclass(tolua_S,"SDL_AudioSpec","SDL_AudioSpec","",NULL);
	tolua_beginmodule(tolua_S,"SDL_AudioSpec");
	tolua_variable(tolua_S,"freq",tolua_get_SDL_AudioSpec_freq,tolua_set_SDL_AudioSpec_freq);
	tolua_variable(tolua_S,"format",tolua_get_SDL_AudioSpec_unsigned_format,tolua_set_SDL_AudioSpec_unsigned_format);
	tolua_variable(tolua_S,"channels",tolua_get_SDL_AudioSpec_unsigned_channels,tolua_set_SDL_AudioSpec_unsigned_channels);
	tolua_variable(tolua_S,"silence",tolua_get_SDL_AudioSpec_unsigned_silence,tolua_set_SDL_AudioSpec_unsigned_silence);
	tolua_variable(tolua_S,"samples",tolua_get_SDL_AudioSpec_unsigned_samples,tolua_set_SDL_AudioSpec_unsigned_samples);
	tolua_variable(tolua_S,"padding",tolua_get_SDL_AudioSpec_unsigned_padding,tolua_set_SDL_AudioSpec_unsigned_padding);
	tolua_variable(tolua_S,"size",tolua_get_SDL_AudioSpec_unsigned_size,tolua_set_SDL_AudioSpec_unsigned_size);
	tolua_variable(tolua_S,"callback",tolua_get_SDL_AudioSpec_callback,tolua_set_SDL_AudioSpec_callback);
	tolua_variable(tolua_S,"userdata",tolua_get_SDL_AudioSpec_userdata,tolua_set_SDL_AudioSpec_userdata);
	tolua_endmodule(tolua_S);
	tolua_constant(tolua_S,"AUDIO_U8",AUDIO_U8);
	tolua_constant(tolua_S,"AUDIO_S8",AUDIO_S8);
	tolua_constant(tolua_S,"AUDIO_U16LSB",AUDIO_U16LSB);
	tolua_constant(tolua_S,"AUDIO_S16LSB",AUDIO_S16LSB);
	tolua_constant(tolua_S,"AUDIO_U16MSB",AUDIO_U16MSB);
	tolua_constant(tolua_S,"AUDIO_S16MSB",AUDIO_S16MSB);
	tolua_constant(tolua_S,"AUDIO_U16",AUDIO_U16);
	tolua_constant(tolua_S,"AUDIO_S16",AUDIO_S16);
	tolua_cclass(tolua_S,"SDL_AudioCVT","SDL_AudioCVT","",NULL);
	tolua_beginmodule(tolua_S,"SDL_AudioCVT");
	tolua_variable(tolua_S,"needed",tolua_get_SDL_AudioCVT_needed,tolua_set_SDL_AudioCVT_needed);
	tolua_variable(tolua_S,"src_format",tolua_get_SDL_AudioCVT_unsigned_src_format,tolua_set_SDL_AudioCVT_unsigned_src_format);
	tolua_variable(tolua_S,"dst_format",tolua_get_SDL_AudioCVT_unsigned_dst_format,tolua_set_SDL_AudioCVT_unsigned_dst_format);
	tolua_variable(tolua_S,"rate_incr",tolua_get_SDL_AudioCVT_rate_incr,tolua_set_SDL_AudioCVT_rate_incr);
	tolua_variable(tolua_S,"buf",tolua_get_SDL_AudioCVT_buf,tolua_set_SDL_AudioCVT_buf);
	tolua_variable(tolua_S,"len",tolua_get_SDL_AudioCVT_len,tolua_set_SDL_AudioCVT_len);
	tolua_variable(tolua_S,"len_cvt",tolua_get_SDL_AudioCVT_len_cvt,tolua_set_SDL_AudioCVT_len_cvt);
	tolua_variable(tolua_S,"len_mult",tolua_get_SDL_AudioCVT_len_mult,tolua_set_SDL_AudioCVT_len_mult);
	tolua_variable(tolua_S,"len_ratio",tolua_get_SDL_AudioCVT_len_ratio,tolua_set_SDL_AudioCVT_len_ratio);
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDL_AudioDriverName",tolua_SDL_SDL_SDL_AudioDriverName00);
	tolua_function(tolua_S,"SDL_OpenAudio",tolua_SDL_SDL_SDL_OpenAudio00);
	tolua_constant(tolua_S,"SDL_AUDIO_STOPPED",SDL_AUDIO_STOPPED);
	tolua_constant(tolua_S,"SDL_AUDIO_PLAYING",SDL_AUDIO_PLAYING);
	tolua_constant(tolua_S,"SDL_AUDIO_PAUSED",SDL_AUDIO_PAUSED);
	tolua_function(tolua_S,"SDL_GetAudioStatus",tolua_SDL_SDL_SDL_GetAudioStatus00);
	tolua_function(tolua_S,"SDL_PauseAudio",tolua_SDL_SDL_SDL_PauseAudio00);
	tolua_function(tolua_S,"_SDL_LoadWAV_RW",tolua_SDL_SDL__SDL_LoadWAV_RW00);
	tolua_function(tolua_S,"SDL_LoadWAV",tolua_SDL_SDL_SDL_LoadWAV00);
	tolua_function(tolua_S,"SDL_FreeWAV",tolua_SDL_SDL_SDL_FreeWAV00);
	tolua_function(tolua_S,"SDL_BuildAudioCVT",tolua_SDL_SDL_SDL_BuildAudioCVT00);
	tolua_function(tolua_S,"SDL_ConvertAudio",tolua_SDL_SDL_SDL_ConvertAudio00);
	tolua_constant(tolua_S,"SDL_MIX_MAXVOLUME",SDL_MIX_MAXVOLUME);
	tolua_function(tolua_S,"SDL_MixAudio",tolua_SDL_SDL_SDL_MixAudio00);
	tolua_function(tolua_S,"SDL_LockAudio",tolua_SDL_SDL_SDL_LockAudio00);
	tolua_function(tolua_S,"SDL_UnlockAudio",tolua_SDL_SDL_SDL_UnlockAudio00);
	tolua_function(tolua_S,"SDL_CloseAudio",tolua_SDL_SDL_SDL_CloseAudio00);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10,105,102, 32, 83, 68, 76, 46, 83, 68, 76, 95, 66, 89, 84,
			69, 79, 82, 68, 69, 82, 32, 61, 61, 32, 83, 68, 76, 46, 83,
			68, 76, 95, 76, 73, 76, 95, 69, 78, 68, 73, 65, 78, 32,116,
			104,101,110, 10, 83, 68, 76, 46, 65, 85, 68, 73, 79, 95, 85,
			49, 54, 83, 89, 83, 32, 61, 32, 83, 68, 76, 46, 65, 85, 68,
			73, 79, 95, 85, 49, 54, 76, 83, 66, 10, 83, 68, 76, 46, 65,
			85, 68, 73, 79, 95, 83, 49, 54, 83, 89, 83, 32, 61, 32, 83,
			68, 76, 46, 65, 85, 68, 73, 79, 95, 83, 49, 54, 76, 83, 66,
			10,101,108,115,101, 10, 83, 68, 76, 46, 65, 85, 68, 73, 79,
			95, 85, 49, 54, 83, 89, 83, 32, 61, 32, 83, 68, 76, 46, 65,
			85, 68, 73, 79, 95, 85, 49, 54, 77, 83, 66, 10, 83, 68, 76,
			46, 65, 85, 68, 73, 79, 95, 83, 49, 54, 83, 89, 83, 32, 61,
			32, 83, 68, 76, 46, 65, 85, 68, 73, 79, 95, 83, 49, 54, 77,
			83, 66, 10,101,110,100,32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 2");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_constant(tolua_S,"SDL_MAX_TRACKS",SDL_MAX_TRACKS);
	tolua_constant(tolua_S,"SDL_AUDIO_TRACK",SDL_AUDIO_TRACK);
	tolua_constant(tolua_S,"SDL_DATA_TRACK",SDL_DATA_TRACK);
	tolua_constant(tolua_S,"CD_TRAYEMPTY",CD_TRAYEMPTY);
	tolua_constant(tolua_S,"CD_STOPPED",CD_STOPPED);
	tolua_constant(tolua_S,"CD_PLAYING",CD_PLAYING);
	tolua_constant(tolua_S,"CD_PAUSED",CD_PAUSED);
	tolua_constant(tolua_S,"CD_ERROR",CD_ERROR);
	tolua_cclass(tolua_S,"SDL_CDtrack","SDL_CDtrack","",NULL);
	tolua_beginmodule(tolua_S,"SDL_CDtrack");
	tolua_variable(tolua_S,"id",tolua_get_SDL_CDtrack_unsigned_id,tolua_set_SDL_CDtrack_unsigned_id);
	tolua_variable(tolua_S,"type",tolua_get_SDL_CDtrack_unsigned_type,tolua_set_SDL_CDtrack_unsigned_type);
	tolua_variable(tolua_S,"unused",tolua_get_SDL_CDtrack_unsigned_unused,tolua_set_SDL_CDtrack_unsigned_unused);
	tolua_variable(tolua_S,"length",tolua_get_SDL_CDtrack_unsigned_length,tolua_set_SDL_CDtrack_unsigned_length);
	tolua_variable(tolua_S,"offset",tolua_get_SDL_CDtrack_unsigned_offset,tolua_set_SDL_CDtrack_unsigned_offset);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_CD","SDL_CD","",NULL);
	tolua_beginmodule(tolua_S,"SDL_CD");
	tolua_variable(tolua_S,"id",tolua_get_SDL_CD_id,tolua_set_SDL_CD_id);
	tolua_variable(tolua_S,"status",tolua_get_SDL_CD_status,tolua_set_SDL_CD_status);
	tolua_variable(tolua_S,"numtracks",tolua_get_SDL_CD_numtracks,tolua_set_SDL_CD_numtracks);
	tolua_variable(tolua_S,"cur_track",tolua_get_SDL_CD_cur_track,tolua_set_SDL_CD_cur_track);
	tolua_variable(tolua_S,"cur_frame",tolua_get_SDL_CD_cur_frame,tolua_set_SDL_CD_cur_frame);
	tolua_array(tolua_S,"track",tolua_get_SDL_SDL_SDL_CD_track,tolua_set_SDL_SDL_SDL_CD_track);
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"CD_INDRIVE",tolua_SDL_SDL_CD_INDRIVE00);
	tolua_function(tolua_S,"FRAMES_TO_MSF",tolua_SDL_SDL_FRAMES_TO_MSF00);
	tolua_function(tolua_S,"MSF_TO_FRAMES",tolua_SDL_SDL_MSF_TO_FRAMES00);
	tolua_constant(tolua_S,"CD_FPS",CD_FPS);
	tolua_function(tolua_S,"SDL_CDNumDrives",tolua_SDL_SDL_SDL_CDNumDrives00);
	tolua_function(tolua_S,"SDL_CDName",tolua_SDL_SDL_SDL_CDName00);
	tolua_function(tolua_S,"SDL_CDOpen",tolua_SDL_SDL_SDL_CDOpen00);
	tolua_function(tolua_S,"SDL_CDStatus",tolua_SDL_SDL_SDL_CDStatus00);
	tolua_function(tolua_S,"SDL_CDPlayTracks",tolua_SDL_SDL_SDL_CDPlayTracks00);
	tolua_function(tolua_S,"SDL_CDPlay",tolua_SDL_SDL_SDL_CDPlay00);
	tolua_function(tolua_S,"SDL_CDPause",tolua_SDL_SDL_SDL_CDPause00);
	tolua_function(tolua_S,"SDL_CDResume",tolua_SDL_SDL_SDL_CDResume00);
	tolua_function(tolua_S,"SDL_CDStop",tolua_SDL_SDL_SDL_CDStop00);
	tolua_function(tolua_S,"SDL_CDEject",tolua_SDL_SDL_SDL_CDEject00);
	tolua_function(tolua_S,"SDL_CDClose",tolua_SDL_SDL_SDL_CDClose00);
	tolua_function(tolua_S,"SDL_HasRDTSC",tolua_SDL_SDL_SDL_HasRDTSC00);
	tolua_function(tolua_S,"SDL_HasMMX",tolua_SDL_SDL_SDL_HasMMX00);
	tolua_function(tolua_S,"SDL_HasMMXExt",tolua_SDL_SDL_SDL_HasMMXExt00);
	tolua_function(tolua_S,"SDL_Has3DNow",tolua_SDL_SDL_SDL_Has3DNow00);
	tolua_function(tolua_S,"SDL_Has3DNowExt",tolua_SDL_SDL_SDL_Has3DNowExt00);
	tolua_function(tolua_S,"SDL_HasSSE",tolua_SDL_SDL_SDL_HasSSE00);
	tolua_function(tolua_S,"SDL_HasSSE2",tolua_SDL_SDL_SDL_HasSSE200);
	tolua_function(tolua_S,"SDL_HasAltiVec",tolua_SDL_SDL_SDL_HasAltiVec00);
	tolua_constant(tolua_S,"SDL_LIL_ENDIAN",SDL_LIL_ENDIAN);
	tolua_constant(tolua_S,"SDL_BIG_ENDIAN",SDL_BIG_ENDIAN);
	tolua_function(tolua_S,"SDL_Swap16",tolua_SDL_SDL_SDL_Swap1600);
	tolua_function(tolua_S,"SDL_Swap32",tolua_SDL_SDL_SDL_Swap3200);
	tolua_function(tolua_S,"SDL_Pass16",tolua_SDL_SDL_SDL_Pass1600);
	tolua_function(tolua_S,"SDL_Pass32",tolua_SDL_SDL_SDL_Pass3200);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10,108,111, 99, 97,108, 32, 83, 68, 76, 32, 61, 32, 83, 68,
			76, 10,105,102, 32, 83, 68, 76, 46, 83, 68, 76, 95, 66, 89,
			84, 69, 79, 82, 68, 69, 82, 32, 61, 61, 32, 83, 68, 76, 46,
			83, 68, 76, 95, 76, 73, 76, 95, 69, 78, 68, 73, 65, 78, 32,
			116,104,101,110, 10, 83, 68, 76, 46, 83, 68, 76, 95, 83,119,
			97,112, 76, 69, 49, 54, 32, 61, 32, 83, 68, 76, 46, 83, 68,
			76, 95, 80, 97,115,115, 49, 54, 10, 83, 68, 76, 46, 83, 68,
			76, 95, 83,119, 97,112, 76, 69, 51, 50, 32, 61, 32, 83, 68,
			76, 46, 83, 68, 76, 95, 80, 97,115,115, 51, 50, 10, 83, 68,
			76, 46, 83, 68, 76, 95, 83,119, 97,112, 66, 69, 49, 54, 32,
			61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 83,119, 97,112, 49,
			54, 10, 83, 68, 76, 46, 83, 68, 76, 95, 83,119, 97,112, 66,
			69, 51, 50, 32, 61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 83,
			119, 97,112, 51, 50, 10,101,108,115,101, 10, 83, 68, 76, 46,
			83, 68, 76, 95, 83,119, 97,112, 76, 69, 49, 54, 32, 61, 32,
			83, 68, 76, 46, 83, 68, 76, 95, 83,119, 97,112, 49, 54, 10,
			83, 68, 76, 46, 83, 68, 76, 95, 83,119, 97,112, 76, 69, 51,
			50, 32, 61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 83,119, 97,
			112, 51, 50, 10, 83, 68, 76, 46, 83, 68, 76, 95, 83,119, 97,
			112, 66, 69, 49, 54, 32, 61, 32, 83, 68, 76, 46, 83, 68, 76,
			95, 80, 97,115,115, 49, 54, 10, 83, 68, 76, 46, 83, 68, 76,
			95, 83,119, 97,112, 66, 69, 51, 50, 32, 61, 32, 83, 68, 76,
			46, 83, 68, 76, 95, 80, 97,115,115, 51, 50, 10,101,110,100,
			32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 3");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_function(tolua_S,"_SDL_SetError",tolua_SDL_SDL__SDL_SetError00);
	tolua_function(tolua_S,"SDL_GetError",tolua_SDL_SDL_SDL_GetError00);
	tolua_function(tolua_S,"SDL_ClearError",tolua_SDL_SDL_SDL_ClearError00);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10,108,111, 99, 97,108, 32, 83, 68, 76, 32, 61, 32, 83, 68,
			76, 10, 83, 68, 76, 46, 83, 68, 76, 95, 83,101,116, 69,114,
			114,111,114, 32, 61, 32,102,117,110, 99,116,105,111,110, 40,
			102,109,116, 44, 32, 46, 46, 46, 41, 10, 83, 68, 76, 46, 95,
			83, 68, 76, 95, 83,101,116, 69,114,114,111,114, 40,115,116,
			114,105,110,103, 46,102,111,114,109, 97,116, 40,102,109,116,
			44, 32, 46, 46, 46, 41, 41, 10,101,110,100,32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 4");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_constant(tolua_S,"SDL_APPMOUSEFOCUS",SDL_APPMOUSEFOCUS);
	tolua_constant(tolua_S,"SDL_APPINPUTFOCUS",SDL_APPINPUTFOCUS);
	tolua_constant(tolua_S,"SDL_APPACTIVE",SDL_APPACTIVE);
	tolua_function(tolua_S,"SDL_GetAppState",tolua_SDL_SDL_SDL_GetAppState00);
	tolua_constant(tolua_S,"SDLK_LAST",SDLK_LAST);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10,108,111, 99, 97,108, 32, 83, 68, 76, 95,107,101,121,115,
			121,109, 95,108,105,115,116, 32, 61, 32, 91, 91, 10, 85, 78,
			75, 78, 79, 87, 78, 61, 48, 10, 70, 73, 82, 83, 84, 61, 48,
			10, 66, 65, 67, 75, 83, 80, 65, 67, 69, 61, 56, 10, 84, 65,
			66, 61, 57, 10, 67, 76, 69, 65, 82, 61, 49, 50, 10, 82, 69,
			84, 85, 82, 78, 61, 49, 51, 10, 80, 65, 85, 83, 69, 61, 49,
			57, 10, 69, 83, 67, 65, 80, 69, 61, 50, 55, 10, 83, 80, 65,
			67, 69, 61, 51, 50, 10, 69, 88, 67, 76, 65, 73, 77, 61, 51,
			51, 10, 81, 85, 79, 84, 69, 68, 66, 76, 61, 51, 52, 10, 72,
			65, 83, 72, 61, 51, 53, 10, 68, 79, 76, 76, 65, 82, 61, 51,
			54, 10, 65, 77, 80, 69, 82, 83, 65, 78, 68, 61, 51, 56, 10,
			81, 85, 79, 84, 69, 61, 51, 57, 10, 76, 69, 70, 84, 80, 65,
			82, 69, 78, 61, 52, 48, 10, 82, 73, 71, 72, 84, 80, 65, 82,
			69, 78, 61, 52, 49, 10, 65, 83, 84, 69, 82, 73, 83, 75, 61,
			52, 50, 10, 80, 76, 85, 83, 61, 52, 51, 10, 67, 79, 77, 77,
			65, 61, 52, 52, 10, 77, 73, 78, 85, 83, 61, 52, 53, 10, 80,
			69, 82, 73, 79, 68, 61, 52, 54, 10, 83, 76, 65, 83, 72, 61,
			52, 55, 10, 48, 61, 52, 56, 10, 49, 61, 52, 57, 10, 50, 61,
			53, 48, 10, 51, 61, 53, 49, 10, 52, 61, 53, 50, 10, 53, 61,
			53, 51, 10, 54, 61, 53, 52, 10, 55, 61, 53, 53, 10, 56, 61,
			53, 54, 10, 57, 61, 53, 55, 10, 67, 79, 76, 79, 78, 61, 53,
			56, 10, 83, 69, 77, 73, 67, 79, 76, 79, 78, 61, 53, 57, 10,
			76, 69, 83, 83, 61, 54, 48, 10, 69, 81, 85, 65, 76, 83, 61,
			54, 49, 10, 71, 82, 69, 65, 84, 69, 82, 61, 54, 50, 10, 81,
			85, 69, 83, 84, 73, 79, 78, 61, 54, 51, 10, 65, 84, 61, 54,
			52, 10, 76, 69, 70, 84, 66, 82, 65, 67, 75, 69, 84, 61, 57,
			49, 10, 66, 65, 67, 75, 83, 76, 65, 83, 72, 61, 57, 50, 10,
			82, 73, 71, 72, 84, 66, 82, 65, 67, 75, 69, 84, 61, 57, 51,
			10, 67, 65, 82, 69, 84, 61, 57, 52, 10, 85, 78, 68, 69, 82,
			83, 67, 79, 82, 69, 61, 57, 53, 10, 66, 65, 67, 75, 81, 85,
			79, 84, 69, 61, 57, 54, 10, 97, 61, 57, 55, 10, 98, 61, 57,
			56, 10, 99, 61, 57, 57, 10,100, 61, 49, 48, 48, 10,101, 61,
			49, 48, 49, 10,102, 61, 49, 48, 50, 10,103, 61, 49, 48, 51,
			10,104, 61, 49, 48, 52, 10,105, 61, 49, 48, 53, 10,106, 61,
			49, 48, 54, 10,107, 61, 49, 48, 55, 10,108, 61, 49, 48, 56,
			10,109, 61, 49, 48, 57, 10,110, 61, 49, 49, 48, 10,111, 61,
			49, 49, 49, 10,112, 61, 49, 49, 50, 10,113, 61, 49, 49, 51,
			10,114, 61, 49, 49, 52, 10,115, 61, 49, 49, 53, 10,116, 61,
			49, 49, 54, 10,117, 61, 49, 49, 55, 10,118, 61, 49, 49, 56,
			10,119, 61, 49, 49, 57, 10,120, 61, 49, 50, 48, 10,121, 61,
			49, 50, 49, 10,122, 61, 49, 50, 50, 10, 68, 69, 76, 69, 84,
			69, 61, 49, 50, 55, 10, 87, 79, 82, 76, 68, 95, 48, 61, 49,
			54, 48, 10, 87, 79, 82, 76, 68, 95, 49, 61, 49, 54, 49, 10,
			87, 79, 82, 76, 68, 95, 50, 61, 49, 54, 50, 10, 87, 79, 82,
			76, 68, 95, 51, 61, 49, 54, 51, 10, 87, 79, 82, 76, 68, 95,
			52, 61, 49, 54, 52, 10, 87, 79, 82, 76, 68, 95, 53, 61, 49,
			54, 53, 10, 87, 79, 82, 76, 68, 95, 54, 61, 49, 54, 54, 10,
			87, 79, 82, 76, 68, 95, 55, 61, 49, 54, 55, 10, 87, 79, 82,
			76, 68, 95, 56, 61, 49, 54, 56, 10, 87, 79, 82, 76, 68, 95,
			57, 61, 49, 54, 57, 10, 87, 79, 82, 76, 68, 95, 49, 48, 61,
			49, 55, 48, 10, 87, 79, 82, 76, 68, 95, 49, 49, 61, 49, 55,
			49, 10, 87, 79, 82, 76, 68, 95, 49, 50, 61, 49, 55, 50, 10,
			87, 79, 82, 76, 68, 95, 49, 51, 61, 49, 55, 51, 10, 87, 79,
			82, 76, 68, 95, 49, 52, 61, 49, 55, 52, 10, 87, 79, 82, 76,
			68, 95, 49, 53, 61, 49, 55, 53, 10, 87, 79, 82, 76, 68, 95,
			49, 54, 61, 49, 55, 54, 10, 87, 79, 82, 76, 68, 95, 49, 55,
			61, 49, 55, 55, 10, 87, 79, 82, 76, 68, 95, 49, 56, 61, 49,
			55, 56, 10, 87, 79, 82, 76, 68, 95, 49, 57, 61, 49, 55, 57,
			10, 87, 79, 82, 76, 68, 95, 50, 48, 61, 49, 56, 48, 10, 87,
			79, 82, 76, 68, 95, 50, 49, 61, 49, 56, 49, 10, 87, 79, 82,
			76, 68, 95, 50, 50, 61, 49, 56, 50, 10, 87, 79, 82, 76, 68,
			95, 50, 51, 61, 49, 56, 51, 10, 87, 79, 82, 76, 68, 95, 50,
			52, 61, 49, 56, 52, 10, 87, 79, 82, 76, 68, 95, 50, 53, 61,
			49, 56, 53, 10, 87, 79, 82, 76, 68, 95, 50, 54, 61, 49, 56,
			54, 10, 87, 79, 82, 76, 68, 95, 50, 55, 61, 49, 56, 55, 10,
			87, 79, 82, 76, 68, 95, 50, 56, 61, 49, 56, 56, 10, 87, 79,
			82, 76, 68, 95, 50, 57, 61, 49, 56, 57, 10, 87, 79, 82, 76,
			68, 95, 51, 48, 61, 49, 57, 48, 10, 87, 79, 82, 76, 68, 95,
			51, 49, 61, 49, 57, 49, 10, 87, 79, 82, 76, 68, 95, 51, 50,
			61, 49, 57, 50, 10, 87, 79, 82, 76, 68, 95, 51, 51, 61, 49,
			57, 51, 10, 87, 79, 82, 76, 68, 95, 51, 52, 61, 49, 57, 52,
			10, 87, 79, 82, 76, 68, 95, 51, 53, 61, 49, 57, 53, 10, 87,
			79, 82, 76, 68, 95, 51, 54, 61, 49, 57, 54, 10, 87, 79, 82,
			76, 68, 95, 51, 55, 61, 49, 57, 55, 10, 87, 79, 82, 76, 68,
			95, 51, 56, 61, 49, 57, 56, 10, 87, 79, 82, 76, 68, 95, 51,
			57, 61, 49, 57, 57, 10, 87, 79, 82, 76, 68, 95, 52, 48, 61,
			50, 48, 48, 10, 87, 79, 82, 76, 68, 95, 52, 49, 61, 50, 48,
			49, 10, 87, 79, 82, 76, 68, 95, 52, 50, 61, 50, 48, 50, 10,
			87, 79, 82, 76, 68, 95, 52, 51, 61, 50, 48, 51, 10, 87, 79,
			82, 76, 68, 95, 52, 52, 61, 50, 48, 52, 10, 87, 79, 82, 76,
			68, 95, 52, 53, 61, 50, 48, 53, 10, 87, 79, 82, 76, 68, 95,
			52, 54, 61, 50, 48, 54, 10, 87, 79, 82, 76, 68, 95, 52, 55,
			61, 50, 48, 55, 10, 87, 79, 82, 76, 68, 95, 52, 56, 61, 50,
			48, 56, 10, 87, 79, 82, 76, 68, 95, 52, 57, 61, 50, 48, 57,
			10, 87, 79, 82, 76, 68, 95, 53, 48, 61, 50, 49, 48, 10, 87,
			79, 82, 76, 68, 95, 53, 49, 61, 50, 49, 49, 10, 87, 79, 82,
			76, 68, 95, 53, 50, 61, 50, 49, 50, 10, 87, 79, 82, 76, 68,
			95, 53, 51, 61, 50, 49, 51, 10, 87, 79, 82, 76, 68, 95, 53,
			52, 61, 50, 49, 52, 10, 87, 79, 82, 76, 68, 95, 53, 53, 61,
			50, 49, 53, 10, 87, 79, 82, 76, 68, 95, 53, 54, 61, 50, 49,
			54, 10, 87, 79, 82, 76, 68, 95, 53, 55, 61, 50, 49, 55, 10,
			87, 79, 82, 76, 68, 95, 53, 56, 61, 50, 49, 56, 10, 87, 79,
			82, 76, 68, 95, 53, 57, 61, 50, 49, 57, 10, 87, 79, 82, 76,
			68, 95, 54, 48, 61, 50, 50, 48, 10, 87, 79, 82, 76, 68, 95,
			54, 49, 61, 50, 50, 49, 10, 87, 79, 82, 76, 68, 95, 54, 50,
			61, 50, 50, 50, 10, 87, 79, 82, 76, 68, 95, 54, 51, 61, 50,
			50, 51, 10, 87, 79, 82, 76, 68, 95, 54, 52, 61, 50, 50, 52,
			10, 87, 79, 82, 76, 68, 95, 54, 53, 61, 50, 50, 53, 10, 87,
			79, 82, 76, 68, 95, 54, 54, 61, 50, 50, 54, 10, 87, 79, 82,
			76, 68, 95, 54, 55, 61, 50, 50, 55, 10, 87, 79, 82, 76, 68,
			95, 54, 56, 61, 50, 50, 56, 10, 87, 79, 82, 76, 68, 95, 54,
			57, 61, 50, 50, 57, 10, 87, 79, 82, 76, 68, 95, 55, 48, 61,
			50, 51, 48, 10, 87, 79, 82, 76, 68, 95, 55, 49, 61, 50, 51,
			49, 10, 87, 79, 82, 76, 68, 95, 55, 50, 61, 50, 51, 50, 10,
			87, 79, 82, 76, 68, 95, 55, 51, 61, 50, 51, 51, 10, 87, 79,
			82, 76, 68, 95, 55, 52, 61, 50, 51, 52, 10, 87, 79, 82, 76,
			68, 95, 55, 53, 61, 50, 51, 53, 10, 87, 79, 82, 76, 68, 95,
			55, 54, 61, 50, 51, 54, 10, 87, 79, 82, 76, 68, 95, 55, 55,
			61, 50, 51, 55, 10, 87, 79, 82, 76, 68, 95, 55, 56, 61, 50,
			51, 56, 10, 87, 79, 82, 76, 68, 95, 55, 57, 61, 50, 51, 57,
			10, 87, 79, 82, 76, 68, 95, 56, 48, 61, 50, 52, 48, 10, 87,
			79, 82, 76, 68, 95, 56, 49, 61, 50, 52, 49, 10, 87, 79, 82,
			76, 68, 95, 56, 50, 61, 50, 52, 50, 10, 87, 79, 82, 76, 68,
			95, 56, 51, 61, 50, 52, 51, 10, 87, 79, 82, 76, 68, 95, 56,
			52, 61, 50, 52, 52, 10, 87, 79, 82, 76, 68, 95, 56, 53, 61,
			50, 52, 53, 10, 87, 79, 82, 76, 68, 95, 56, 54, 61, 50, 52,
			54, 10, 87, 79, 82, 76, 68, 95, 56, 55, 61, 50, 52, 55, 10,
			87, 79, 82, 76, 68, 95, 56, 56, 61, 50, 52, 56, 10, 87, 79,
			82, 76, 68, 95, 56, 57, 61, 50, 52, 57, 10, 87, 79, 82, 76,
			68, 95, 57, 48, 61, 50, 53, 48, 10, 87, 79, 82, 76, 68, 95,
			57, 49, 61, 50, 53, 49, 10, 87, 79, 82, 76, 68, 95, 57, 50,
			61, 50, 53, 50, 10, 87, 79, 82, 76, 68, 95, 57, 51, 61, 50,
			53, 51, 10, 87, 79, 82, 76, 68, 95, 57, 52, 61, 50, 53, 52,
			10, 87, 79, 82, 76, 68, 95, 57, 53, 61, 50, 53, 53, 10, 75,
			80, 48, 61, 50, 53, 54, 10, 75, 80, 49, 61, 50, 53, 55, 10,
			75, 80, 50, 61, 50, 53, 56, 10, 75, 80, 51, 61, 50, 53, 57,
			10, 75, 80, 52, 61, 50, 54, 48, 10, 75, 80, 53, 61, 50, 54,
			49, 10, 75, 80, 54, 61, 50, 54, 50, 10, 75, 80, 55, 61, 50,
			54, 51, 10, 75, 80, 56, 61, 50, 54, 52, 10, 75, 80, 57, 61,
			50, 54, 53, 10, 75, 80, 95, 80, 69, 82, 73, 79, 68, 61, 50,
			54, 54, 10, 75, 80, 95, 68, 73, 86, 73, 68, 69, 61, 50, 54,
			55, 10, 75, 80, 95, 77, 85, 76, 84, 73, 80, 76, 89, 61, 50,
			54, 56, 10, 75, 80, 95, 77, 73, 78, 85, 83, 61, 50, 54, 57,
			10, 75, 80, 95, 80, 76, 85, 83, 61, 50, 55, 48, 10, 75, 80,
			95, 69, 78, 84, 69, 82, 61, 50, 55, 49, 10, 75, 80, 95, 69,
			81, 85, 65, 76, 83, 61, 50, 55, 50, 10, 85, 80, 61, 50, 55,
			51, 10, 68, 79, 87, 78, 61, 50, 55, 52, 10, 82, 73, 71, 72,
			84, 61, 50, 55, 53, 10, 76, 69, 70, 84, 61, 50, 55, 54, 10,
			73, 78, 83, 69, 82, 84, 61, 50, 55, 55, 10, 72, 79, 77, 69,
			61, 50, 55, 56, 10, 69, 78, 68, 61, 50, 55, 57, 10, 80, 65,
			71, 69, 85, 80, 61, 50, 56, 48, 10, 80, 65, 71, 69, 68, 79,
			87, 78, 61, 50, 56, 49, 10, 70, 49, 61, 50, 56, 50, 10, 70,
			50, 61, 50, 56, 51, 10, 70, 51, 61, 50, 56, 52, 10, 70, 52,
			61, 50, 56, 53, 10, 70, 53, 61, 50, 56, 54, 10, 70, 54, 61,
			50, 56, 55, 10, 70, 55, 61, 50, 56, 56, 10, 70, 56, 61, 50,
			56, 57, 10, 70, 57, 61, 50, 57, 48, 10, 70, 49, 48, 61, 50,
			57, 49, 10, 70, 49, 49, 61, 50, 57, 50, 10, 70, 49, 50, 61,
			50, 57, 51, 10, 70, 49, 51, 61, 50, 57, 52, 10, 70, 49, 52,
			61, 50, 57, 53, 10, 70, 49, 53, 61, 50, 57, 54, 10, 78, 85,
			77, 76, 79, 67, 75, 61, 51, 48, 48, 10, 67, 65, 80, 83, 76,
			79, 67, 75, 61, 51, 48, 49, 10, 83, 67, 82, 79, 76, 76, 79,
			67, 75, 61, 51, 48, 50, 10, 82, 83, 72, 73, 70, 84, 61, 51,
			48, 51, 10, 76, 83, 72, 73, 70, 84, 61, 51, 48, 52, 10, 82,
			67, 84, 82, 76, 61, 51, 48, 53, 10, 76, 67, 84, 82, 76, 61,
			51, 48, 54, 10, 82, 65, 76, 84, 61, 51, 48, 55, 10, 76, 65,
			76, 84, 61, 51, 48, 56, 10, 82, 77, 69, 84, 65, 61, 51, 48,
			57, 10, 76, 77, 69, 84, 65, 61, 51, 49, 48, 10, 76, 83, 85,
			80, 69, 82, 61, 51, 49, 49, 10, 82, 83, 85, 80, 69, 82, 61,
			51, 49, 50, 10, 77, 79, 68, 69, 61, 51, 49, 51, 10, 67, 79,
			77, 80, 79, 83, 69, 61, 51, 49, 52, 10, 72, 69, 76, 80, 61,
			51, 49, 53, 10, 80, 82, 73, 78, 84, 61, 51, 49, 54, 10, 83,
			89, 83, 82, 69, 81, 61, 51, 49, 55, 10, 66, 82, 69, 65, 75,
			61, 51, 49, 56, 10, 77, 69, 78, 85, 61, 51, 49, 57, 10, 80,
			79, 87, 69, 82, 61, 51, 50, 48, 10, 69, 85, 82, 79, 61, 51,
			50, 49, 10, 85, 78, 68, 79, 61, 51, 50, 50, 10, 93, 93, 10,
			102,111,114, 32,107, 44,118, 32,105,110, 32,115,116,114,105,
			110,103, 46,103,109, 97,116, 99,104, 40, 83, 68, 76, 95,107,
			101,121,115,121,109, 95,108,105,115,116, 44, 32, 34, 40, 91,
			94, 61, 93, 43, 41, 61, 40, 91, 94, 61, 93, 43, 41, 37,115,
			34, 41, 32,100,111, 10, 83, 68, 76, 91, 34, 83, 68, 76, 75,
			95, 34, 46, 46,107, 93, 32, 61, 32,118, 43, 48, 10,101,110,
			100,32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 5");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_constant(tolua_S,"KMOD_NONE",KMOD_NONE);
	tolua_constant(tolua_S,"KMOD_LSHIFT",KMOD_LSHIFT);
	tolua_constant(tolua_S,"KMOD_RSHIFT",KMOD_RSHIFT);
	tolua_constant(tolua_S,"KMOD_LCTRL",KMOD_LCTRL);
	tolua_constant(tolua_S,"KMOD_RCTRL",KMOD_RCTRL);
	tolua_constant(tolua_S,"KMOD_LALT",KMOD_LALT);
	tolua_constant(tolua_S,"KMOD_RALT",KMOD_RALT);
	tolua_constant(tolua_S,"KMOD_LMETA",KMOD_LMETA);
	tolua_constant(tolua_S,"KMOD_RMETA",KMOD_RMETA);
	tolua_constant(tolua_S,"KMOD_NUM",KMOD_NUM);
	tolua_constant(tolua_S,"KMOD_CAPS",KMOD_CAPS);
	tolua_constant(tolua_S,"KMOD_MODE",KMOD_MODE);
	tolua_constant(tolua_S,"KMOD_RESERVED",KMOD_RESERVED);
	tolua_constant(tolua_S,"KMOD_CTRL",KMOD_CTRL);
	tolua_constant(tolua_S,"KMOD_SHIFT",KMOD_SHIFT);
	tolua_constant(tolua_S,"KMOD_ALT",KMOD_ALT);
	tolua_constant(tolua_S,"KMOD_META",KMOD_META);
	tolua_cclass(tolua_S,"SDL_keysym","SDL_keysym","",NULL);
	tolua_beginmodule(tolua_S,"SDL_keysym");
	tolua_variable(tolua_S,"scancode",tolua_get_SDL_keysym_unsigned_scancode,tolua_set_SDL_keysym_unsigned_scancode);
	tolua_variable(tolua_S,"sym",tolua_get_SDL_keysym_sym,tolua_set_SDL_keysym_sym);
	tolua_variable(tolua_S,"mod",tolua_get_SDL_keysym_mod,tolua_set_SDL_keysym_mod);
	tolua_variable(tolua_S,"unicode",tolua_get_SDL_keysym_unsigned_unicode,tolua_set_SDL_keysym_unsigned_unicode);
	tolua_endmodule(tolua_S);
	tolua_constant(tolua_S,"SDL_ALL_HOTKEYS",SDL_ALL_HOTKEYS);
	tolua_function(tolua_S,"SDL_EnableUNICODE",tolua_SDL_SDL_SDL_EnableUNICODE00);
	tolua_constant(tolua_S,"SDL_DEFAULT_REPEAT_DELAY",SDL_DEFAULT_REPEAT_DELAY);
	tolua_constant(tolua_S,"SDL_DEFAULT_REPEAT_INTERVAL",SDL_DEFAULT_REPEAT_INTERVAL);
	tolua_function(tolua_S,"SDL_EnableKeyRepeat",tolua_SDL_SDL_SDL_EnableKeyRepeat00);
	tolua_function(tolua_S,"SDL_GetKeyRepeat",tolua_SDL_SDL_SDL_GetKeyRepeat00);
	tolua_function(tolua_S,"SDL_GetModState",tolua_SDL_SDL_SDL_GetModState00);
	tolua_function(tolua_S,"SDL_SetModState",tolua_SDL_SDL_SDL_SetModState00);
	tolua_function(tolua_S,"SDL_GetKeyName",tolua_SDL_SDL_SDL_GetKeyName00);
	tolua_cclass(tolua_S,"WMcursor","WMcursor","",NULL);
	tolua_beginmodule(tolua_S,"WMcursor");
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_Cursor","SDL_Cursor","",NULL);
	tolua_beginmodule(tolua_S,"SDL_Cursor");
	tolua_variable(tolua_S,"area",tolua_get_SDL_Cursor_area,tolua_set_SDL_Cursor_area);
	tolua_variable(tolua_S,"hot_x",tolua_get_SDL_Cursor_hot_x,tolua_set_SDL_Cursor_hot_x);
	tolua_variable(tolua_S,"hot_y",tolua_get_SDL_Cursor_hot_y,tolua_set_SDL_Cursor_hot_y);
	tolua_variable(tolua_S,"data",tolua_get_SDL_Cursor_data,tolua_set_SDL_Cursor_data);
	tolua_variable(tolua_S,"mask",tolua_get_SDL_Cursor_mask,tolua_set_SDL_Cursor_mask);
	tolua_variable(tolua_S,"wm_cursor",tolua_get_SDL_Cursor_wm_cursor_ptr,tolua_set_SDL_Cursor_wm_cursor_ptr);
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDL_GetMouseState",tolua_SDL_SDL_SDL_GetMouseState00);
	tolua_function(tolua_S,"SDL_GetRelativeMouseState",tolua_SDL_SDL_SDL_GetRelativeMouseState00);
	tolua_function(tolua_S,"SDL_WarpMouse",tolua_SDL_SDL_SDL_WarpMouse00);
	tolua_function(tolua_S,"SDL_CreateCursor",tolua_SDL_SDL_SDL_CreateCursor00);
	tolua_function(tolua_S,"SDL_SetCursor",tolua_SDL_SDL_SDL_SetCursor00);
	tolua_function(tolua_S,"SDL_GetCursor",tolua_SDL_SDL_SDL_GetCursor00);
	tolua_function(tolua_S,"SDL_FreeCursor",tolua_SDL_SDL_SDL_FreeCursor00);
	tolua_function(tolua_S,"SDL_ShowCursor",tolua_SDL_SDL_SDL_ShowCursor00);
	tolua_constant(tolua_S,"SDL_BUTTON_LEFT",SDL_BUTTON_LEFT);
	tolua_constant(tolua_S,"SDL_BUTTON_MIDDLE",SDL_BUTTON_MIDDLE);
	tolua_constant(tolua_S,"SDL_BUTTON_RIGHT",SDL_BUTTON_RIGHT);
	tolua_constant(tolua_S,"SDL_BUTTON_WHEELUP",SDL_BUTTON_WHEELUP);
	tolua_constant(tolua_S,"SDL_BUTTON_WHEELDOWN",SDL_BUTTON_WHEELDOWN);
	tolua_constant(tolua_S,"SDL_BUTTON_LMASK",SDL_BUTTON_LMASK);
	tolua_constant(tolua_S,"SDL_BUTTON_MMASK",SDL_BUTTON_MMASK);
	tolua_constant(tolua_S,"SDL_BUTTON_RMASK",SDL_BUTTON_RMASK);
	tolua_cclass(tolua_S,"_SDL_Joystick","_SDL_Joystick","",NULL);
	tolua_beginmodule(tolua_S,"_SDL_Joystick");
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDL_NumJoysticks",tolua_SDL_SDL_SDL_NumJoysticks00);
	tolua_function(tolua_S,"SDL_JoystickName",tolua_SDL_SDL_SDL_JoystickName00);
	tolua_function(tolua_S,"SDL_JoystickOpen",tolua_SDL_SDL_SDL_JoystickOpen00);
	tolua_function(tolua_S,"SDL_JoystickOpened",tolua_SDL_SDL_SDL_JoystickOpened00);
	tolua_function(tolua_S,"SDL_JoystickIndex",tolua_SDL_SDL_SDL_JoystickIndex00);
	tolua_function(tolua_S,"SDL_JoystickNumAxes",tolua_SDL_SDL_SDL_JoystickNumAxes00);
	tolua_function(tolua_S,"SDL_JoystickNumBalls",tolua_SDL_SDL_SDL_JoystickNumBalls00);
	tolua_function(tolua_S,"SDL_JoystickNumHats",tolua_SDL_SDL_SDL_JoystickNumHats00);
	tolua_function(tolua_S,"SDL_JoystickNumButtons",tolua_SDL_SDL_SDL_JoystickNumButtons00);
	tolua_function(tolua_S,"SDL_JoystickUpdate",tolua_SDL_SDL_SDL_JoystickUpdate00);
	tolua_function(tolua_S,"SDL_JoystickEventState",tolua_SDL_SDL_SDL_JoystickEventState00);
	tolua_function(tolua_S,"SDL_JoystickGetAxis",tolua_SDL_SDL_SDL_JoystickGetAxis00);
	tolua_constant(tolua_S,"SDL_HAT_CENTERED",SDL_HAT_CENTERED);
	tolua_constant(tolua_S,"SDL_HAT_UP",SDL_HAT_UP);
	tolua_constant(tolua_S,"SDL_HAT_RIGHT",SDL_HAT_RIGHT);
	tolua_constant(tolua_S,"SDL_HAT_DOWN",SDL_HAT_DOWN);
	tolua_constant(tolua_S,"SDL_HAT_LEFT",SDL_HAT_LEFT);
	tolua_constant(tolua_S,"SDL_HAT_RIGHTUP",SDL_HAT_RIGHTUP);
	tolua_constant(tolua_S,"SDL_HAT_RIGHTDOWN",SDL_HAT_RIGHTDOWN);
	tolua_constant(tolua_S,"SDL_HAT_LEFTUP",SDL_HAT_LEFTUP);
	tolua_constant(tolua_S,"SDL_HAT_LEFTDOWN",SDL_HAT_LEFTDOWN);
	tolua_function(tolua_S,"SDL_JoystickGetHat",tolua_SDL_SDL_SDL_JoystickGetHat00);
	tolua_function(tolua_S,"SDL_JoystickGetBall",tolua_SDL_SDL_SDL_JoystickGetBall00);
	tolua_function(tolua_S,"SDL_JoystickGetButton",tolua_SDL_SDL_SDL_JoystickGetButton00);
	tolua_function(tolua_S,"SDL_JoystickClose",tolua_SDL_SDL_SDL_JoystickClose00);
	tolua_function(tolua_S,"SDL_QuitRequested",tolua_SDL_SDL_SDL_QuitRequested00);
	tolua_constant(tolua_S,"SDL_RELEASED",SDL_RELEASED);
	tolua_constant(tolua_S,"SDL_PRESSED",SDL_PRESSED);
	tolua_constant(tolua_S,"SDL_NOEVENT",SDL_NOEVENT);
	tolua_constant(tolua_S,"SDL_ACTIVEEVENT",SDL_ACTIVEEVENT);
	tolua_constant(tolua_S,"SDL_KEYDOWN",SDL_KEYDOWN);
	tolua_constant(tolua_S,"SDL_KEYUP",SDL_KEYUP);
	tolua_constant(tolua_S,"SDL_MOUSEMOTION",SDL_MOUSEMOTION);
	tolua_constant(tolua_S,"SDL_MOUSEBUTTONDOWN",SDL_MOUSEBUTTONDOWN);
	tolua_constant(tolua_S,"SDL_MOUSEBUTTONUP",SDL_MOUSEBUTTONUP);
	tolua_constant(tolua_S,"SDL_JOYAXISMOTION",SDL_JOYAXISMOTION);
	tolua_constant(tolua_S,"SDL_JOYBALLMOTION",SDL_JOYBALLMOTION);
	tolua_constant(tolua_S,"SDL_JOYHATMOTION",SDL_JOYHATMOTION);
	tolua_constant(tolua_S,"SDL_JOYBUTTONDOWN",SDL_JOYBUTTONDOWN);
	tolua_constant(tolua_S,"SDL_JOYBUTTONUP",SDL_JOYBUTTONUP);
	tolua_constant(tolua_S,"SDL_QUIT",SDL_QUIT);
	tolua_constant(tolua_S,"SDL_SYSWMEVENT",SDL_SYSWMEVENT);
	tolua_constant(tolua_S,"SDL_EVENT_RESERVEDA",SDL_EVENT_RESERVEDA);
	tolua_constant(tolua_S,"SDL_EVENT_RESERVEDB",SDL_EVENT_RESERVEDB);
	tolua_constant(tolua_S,"SDL_VIDEORESIZE",SDL_VIDEORESIZE);
	tolua_constant(tolua_S,"SDL_VIDEOEXPOSE",SDL_VIDEOEXPOSE);
	tolua_constant(tolua_S,"SDL_EVENT_RESERVED2",SDL_EVENT_RESERVED2);
	tolua_constant(tolua_S,"SDL_EVENT_RESERVED3",SDL_EVENT_RESERVED3);
	tolua_constant(tolua_S,"SDL_EVENT_RESERVED4",SDL_EVENT_RESERVED4);
	tolua_constant(tolua_S,"SDL_EVENT_RESERVED5",SDL_EVENT_RESERVED5);
	tolua_constant(tolua_S,"SDL_EVENT_RESERVED6",SDL_EVENT_RESERVED6);
	tolua_constant(tolua_S,"SDL_EVENT_RESERVED7",SDL_EVENT_RESERVED7);
	tolua_constant(tolua_S,"SDL_USEREVENT",SDL_USEREVENT);
	tolua_constant(tolua_S,"SDL_NUMEVENTS",SDL_NUMEVENTS);
	tolua_constant(tolua_S,"SDL_ACTIVEEVENTMASK",SDL_ACTIVEEVENTMASK);
	tolua_constant(tolua_S,"SDL_KEYDOWNMASK",SDL_KEYDOWNMASK);
	tolua_constant(tolua_S,"SDL_KEYUPMASK",SDL_KEYUPMASK);
	tolua_constant(tolua_S,"SDL_KEYEVENTMASK",SDL_KEYEVENTMASK);
	tolua_constant(tolua_S,"SDL_MOUSEMOTIONMASK",SDL_MOUSEMOTIONMASK);
	tolua_constant(tolua_S,"SDL_MOUSEBUTTONDOWNMASK",SDL_MOUSEBUTTONDOWNMASK);
	tolua_constant(tolua_S,"SDL_MOUSEBUTTONUPMASK",SDL_MOUSEBUTTONUPMASK);
	tolua_constant(tolua_S,"SDL_MOUSEEVENTMASK",SDL_MOUSEEVENTMASK);
	tolua_constant(tolua_S,"SDL_JOYAXISMOTIONMASK",SDL_JOYAXISMOTIONMASK);
	tolua_constant(tolua_S,"SDL_JOYBALLMOTIONMASK",SDL_JOYBALLMOTIONMASK);
	tolua_constant(tolua_S,"SDL_JOYHATMOTIONMASK",SDL_JOYHATMOTIONMASK);
	tolua_constant(tolua_S,"SDL_JOYBUTTONDOWNMASK",SDL_JOYBUTTONDOWNMASK);
	tolua_constant(tolua_S,"SDL_JOYBUTTONUPMASK",SDL_JOYBUTTONUPMASK);
	tolua_constant(tolua_S,"SDL_JOYEVENTMASK",SDL_JOYEVENTMASK);
	tolua_constant(tolua_S,"SDL_VIDEORESIZEMASK",SDL_VIDEORESIZEMASK);
	tolua_constant(tolua_S,"SDL_VIDEOEXPOSEMASK",SDL_VIDEOEXPOSEMASK);
	tolua_constant(tolua_S,"SDL_QUITMASK",SDL_QUITMASK);
	tolua_constant(tolua_S,"SDL_SYSWMEVENTMASK",SDL_SYSWMEVENTMASK);
	tolua_constant(tolua_S,"SDL_ALLEVENTS",SDL_ALLEVENTS);
	tolua_cclass(tolua_S,"SDL_ActiveEvent","SDL_ActiveEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_ActiveEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_ActiveEvent_unsigned_type,tolua_set_SDL_ActiveEvent_unsigned_type);
	tolua_variable(tolua_S,"gain",tolua_get_SDL_ActiveEvent_unsigned_gain,tolua_set_SDL_ActiveEvent_unsigned_gain);
	tolua_variable(tolua_S,"state",tolua_get_SDL_ActiveEvent_unsigned_state,tolua_set_SDL_ActiveEvent_unsigned_state);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_KeyboardEvent","SDL_KeyboardEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_KeyboardEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_KeyboardEvent_unsigned_type,tolua_set_SDL_KeyboardEvent_unsigned_type);
	tolua_variable(tolua_S,"which",tolua_get_SDL_KeyboardEvent_unsigned_which,tolua_set_SDL_KeyboardEvent_unsigned_which);
	tolua_variable(tolua_S,"state",tolua_get_SDL_KeyboardEvent_unsigned_state,tolua_set_SDL_KeyboardEvent_unsigned_state);
	tolua_variable(tolua_S,"keysym",tolua_get_SDL_KeyboardEvent_keysym,tolua_set_SDL_KeyboardEvent_keysym);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_MouseMotionEvent","SDL_MouseMotionEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_MouseMotionEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_MouseMotionEvent_unsigned_type,tolua_set_SDL_MouseMotionEvent_unsigned_type);
	tolua_variable(tolua_S,"which",tolua_get_SDL_MouseMotionEvent_unsigned_which,tolua_set_SDL_MouseMotionEvent_unsigned_which);
	tolua_variable(tolua_S,"state",tolua_get_SDL_MouseMotionEvent_unsigned_state,tolua_set_SDL_MouseMotionEvent_unsigned_state);
	tolua_variable(tolua_S,"x",tolua_get_SDL_MouseMotionEvent_unsigned_x,tolua_set_SDL_MouseMotionEvent_unsigned_x);
	tolua_variable(tolua_S,"y",tolua_get_SDL_MouseMotionEvent_unsigned_y,tolua_set_SDL_MouseMotionEvent_unsigned_y);
	tolua_variable(tolua_S,"xrel",tolua_get_SDL_MouseMotionEvent_xrel,tolua_set_SDL_MouseMotionEvent_xrel);
	tolua_variable(tolua_S,"yrel",tolua_get_SDL_MouseMotionEvent_yrel,tolua_set_SDL_MouseMotionEvent_yrel);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_MouseButtonEvent","SDL_MouseButtonEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_MouseButtonEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_MouseButtonEvent_unsigned_type,tolua_set_SDL_MouseButtonEvent_unsigned_type);
	tolua_variable(tolua_S,"which",tolua_get_SDL_MouseButtonEvent_unsigned_which,tolua_set_SDL_MouseButtonEvent_unsigned_which);
	tolua_variable(tolua_S,"button",tolua_get_SDL_MouseButtonEvent_unsigned_button,tolua_set_SDL_MouseButtonEvent_unsigned_button);
	tolua_variable(tolua_S,"state",tolua_get_SDL_MouseButtonEvent_unsigned_state,tolua_set_SDL_MouseButtonEvent_unsigned_state);
	tolua_variable(tolua_S,"x",tolua_get_SDL_MouseButtonEvent_unsigned_x,tolua_set_SDL_MouseButtonEvent_unsigned_x);
	tolua_variable(tolua_S,"y",tolua_get_SDL_MouseButtonEvent_unsigned_y,tolua_set_SDL_MouseButtonEvent_unsigned_y);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_JoyAxisEvent","SDL_JoyAxisEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_JoyAxisEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_JoyAxisEvent_unsigned_type,tolua_set_SDL_JoyAxisEvent_unsigned_type);
	tolua_variable(tolua_S,"which",tolua_get_SDL_JoyAxisEvent_unsigned_which,tolua_set_SDL_JoyAxisEvent_unsigned_which);
	tolua_variable(tolua_S,"axis",tolua_get_SDL_JoyAxisEvent_unsigned_axis,tolua_set_SDL_JoyAxisEvent_unsigned_axis);
	tolua_variable(tolua_S,"value",tolua_get_SDL_JoyAxisEvent_value,tolua_set_SDL_JoyAxisEvent_value);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_JoyBallEvent","SDL_JoyBallEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_JoyBallEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_JoyBallEvent_unsigned_type,tolua_set_SDL_JoyBallEvent_unsigned_type);
	tolua_variable(tolua_S,"which",tolua_get_SDL_JoyBallEvent_unsigned_which,tolua_set_SDL_JoyBallEvent_unsigned_which);
	tolua_variable(tolua_S,"ball",tolua_get_SDL_JoyBallEvent_unsigned_ball,tolua_set_SDL_JoyBallEvent_unsigned_ball);
	tolua_variable(tolua_S,"xrel",tolua_get_SDL_JoyBallEvent_xrel,tolua_set_SDL_JoyBallEvent_xrel);
	tolua_variable(tolua_S,"yrel",tolua_get_SDL_JoyBallEvent_yrel,tolua_set_SDL_JoyBallEvent_yrel);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_JoyHatEvent","SDL_JoyHatEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_JoyHatEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_JoyHatEvent_unsigned_type,tolua_set_SDL_JoyHatEvent_unsigned_type);
	tolua_variable(tolua_S,"which",tolua_get_SDL_JoyHatEvent_unsigned_which,tolua_set_SDL_JoyHatEvent_unsigned_which);
	tolua_variable(tolua_S,"hat",tolua_get_SDL_JoyHatEvent_unsigned_hat,tolua_set_SDL_JoyHatEvent_unsigned_hat);
	tolua_variable(tolua_S,"value",tolua_get_SDL_JoyHatEvent_unsigned_value,tolua_set_SDL_JoyHatEvent_unsigned_value);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_JoyButtonEvent","SDL_JoyButtonEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_JoyButtonEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_JoyButtonEvent_unsigned_type,tolua_set_SDL_JoyButtonEvent_unsigned_type);
	tolua_variable(tolua_S,"which",tolua_get_SDL_JoyButtonEvent_unsigned_which,tolua_set_SDL_JoyButtonEvent_unsigned_which);
	tolua_variable(tolua_S,"button",tolua_get_SDL_JoyButtonEvent_unsigned_button,tolua_set_SDL_JoyButtonEvent_unsigned_button);
	tolua_variable(tolua_S,"state",tolua_get_SDL_JoyButtonEvent_unsigned_state,tolua_set_SDL_JoyButtonEvent_unsigned_state);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_ResizeEvent","SDL_ResizeEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_ResizeEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_ResizeEvent_unsigned_type,tolua_set_SDL_ResizeEvent_unsigned_type);
	tolua_variable(tolua_S,"w",tolua_get_SDL_ResizeEvent_w,tolua_set_SDL_ResizeEvent_w);
	tolua_variable(tolua_S,"h",tolua_get_SDL_ResizeEvent_h,tolua_set_SDL_ResizeEvent_h);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_ExposeEvent","SDL_ExposeEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_ExposeEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_ExposeEvent_unsigned_type,tolua_set_SDL_ExposeEvent_unsigned_type);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_QuitEvent","SDL_QuitEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_QuitEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_QuitEvent_unsigned_type,tolua_set_SDL_QuitEvent_unsigned_type);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_UserEvent","SDL_UserEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_UserEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_UserEvent_unsigned_type,tolua_set_SDL_UserEvent_unsigned_type);
	tolua_variable(tolua_S,"code",tolua_get_SDL_UserEvent_code,tolua_set_SDL_UserEvent_code);
	tolua_variable(tolua_S,"data1",tolua_get_SDL_UserEvent_data1,tolua_set_SDL_UserEvent_data1);
	tolua_variable(tolua_S,"data2",tolua_get_SDL_UserEvent_data2,tolua_set_SDL_UserEvent_data2);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_SysWMmsg","SDL_SysWMmsg","",NULL);
	tolua_beginmodule(tolua_S,"SDL_SysWMmsg");
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_SysWMEvent","SDL_SysWMEvent","",NULL);
	tolua_beginmodule(tolua_S,"SDL_SysWMEvent");
	tolua_variable(tolua_S,"type",tolua_get_SDL_SysWMEvent_unsigned_type,tolua_set_SDL_SysWMEvent_unsigned_type);
	tolua_variable(tolua_S,"msg",tolua_get_SDL_SysWMEvent_msg_ptr,tolua_set_SDL_SysWMEvent_msg_ptr);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_Event","SDL_Event","",NULL);
	tolua_beginmodule(tolua_S,"SDL_Event");
	tolua_variable(tolua_S,"type",tolua_get_SDL_Event_unsigned_type,tolua_set_SDL_Event_unsigned_type);
	tolua_variable(tolua_S,"active",tolua_get_SDL_Event_active,tolua_set_SDL_Event_active);
	tolua_variable(tolua_S,"key",tolua_get_SDL_Event_key,tolua_set_SDL_Event_key);
	tolua_variable(tolua_S,"motion",tolua_get_SDL_Event_motion,tolua_set_SDL_Event_motion);
	tolua_variable(tolua_S,"button",tolua_get_SDL_Event_button,tolua_set_SDL_Event_button);
	tolua_variable(tolua_S,"jaxis",tolua_get_SDL_Event_jaxis,tolua_set_SDL_Event_jaxis);
	tolua_variable(tolua_S,"jball",tolua_get_SDL_Event_jball,tolua_set_SDL_Event_jball);
	tolua_variable(tolua_S,"jhat",tolua_get_SDL_Event_jhat,tolua_set_SDL_Event_jhat);
	tolua_variable(tolua_S,"jbutton",tolua_get_SDL_Event_jbutton,tolua_set_SDL_Event_jbutton);
	tolua_variable(tolua_S,"resize",tolua_get_SDL_Event_resize,tolua_set_SDL_Event_resize);
	tolua_variable(tolua_S,"expose",tolua_get_SDL_Event_expose,tolua_set_SDL_Event_expose);
	tolua_variable(tolua_S,"quit",tolua_get_SDL_Event_quit,tolua_set_SDL_Event_quit);
	tolua_variable(tolua_S,"user",tolua_get_SDL_Event_user,tolua_set_SDL_Event_user);
	tolua_variable(tolua_S,"syswm",tolua_get_SDL_Event_syswm,tolua_set_SDL_Event_syswm);
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDL_PumpEvents",tolua_SDL_SDL_SDL_PumpEvents00);
	tolua_constant(tolua_S,"SDL_ADDEVENT",SDL_ADDEVENT);
	tolua_constant(tolua_S,"SDL_PEEKEVENT",SDL_PEEKEVENT);
	tolua_constant(tolua_S,"SDL_GETEVENT",SDL_GETEVENT);
	tolua_function(tolua_S,"SDL_PeepEvents",tolua_SDL_SDL_SDL_PeepEvents00);
	tolua_function(tolua_S,"SDL_PollEvent",tolua_SDL_SDL_SDL_PollEvent00);
	tolua_function(tolua_S,"SDL_WaitEvent",tolua_SDL_SDL_SDL_WaitEvent00);
	tolua_function(tolua_S,"SDL_PushEvent",tolua_SDL_SDL_SDL_PushEvent00);
	tolua_constant(tolua_S,"SDL_QUERY",SDL_QUERY);
	tolua_constant(tolua_S,"SDL_IGNORE",SDL_IGNORE);
	tolua_constant(tolua_S,"SDL_DISABLE",SDL_DISABLE);
	tolua_constant(tolua_S,"SDL_ENABLE",SDL_ENABLE);
	tolua_function(tolua_S,"SDL_EventState",tolua_SDL_SDL_SDL_EventState00);
	tolua_cclass(tolua_S,"SDL_RWops","SDL_RWops","",NULL);
	tolua_beginmodule(tolua_S,"SDL_RWops");
	tolua_variable(tolua_S,"type",tolua_get_SDL_RWops_unsigned_type,tolua_set_SDL_RWops_unsigned_type);
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDL_RWFromFile",tolua_SDL_SDL_SDL_RWFromFile00);
	tolua_function(tolua_S,"SDL_RWFromMem",tolua_SDL_SDL_SDL_RWFromMem00);
	tolua_function(tolua_S,"SDL_RWFromConstMem",tolua_SDL_SDL_SDL_RWFromConstMem00);
	tolua_function(tolua_S,"SDL_AllocRW",tolua_SDL_SDL_SDL_AllocRW00);
	tolua_function(tolua_S,"SDL_FreeRW",tolua_SDL_SDL_SDL_FreeRW00);
	tolua_constant(tolua_S,"RW_SEEK_SET",RW_SEEK_SET);
	tolua_constant(tolua_S,"RW_SEEK_CUR",RW_SEEK_CUR);
	tolua_constant(tolua_S,"RW_SEEK_END",RW_SEEK_END);
	tolua_function(tolua_S,"SDL_RWseek",tolua_SDL_SDL_SDL_RWseek00);
	tolua_function(tolua_S,"SDL_RWtell",tolua_SDL_SDL_SDL_RWtell00);
	tolua_function(tolua_S,"SDL_RWread",tolua_SDL_SDL_SDL_RWread00);
	tolua_function(tolua_S,"SDL_RWwrite",tolua_SDL_SDL_SDL_RWwrite00);
	tolua_function(tolua_S,"SDL_RWclose",tolua_SDL_SDL_SDL_RWclose00);
	tolua_function(tolua_S,"SDL_ReadLE16",tolua_SDL_SDL_SDL_ReadLE1600);
	tolua_function(tolua_S,"SDL_ReadBE16",tolua_SDL_SDL_SDL_ReadBE1600);
	tolua_function(tolua_S,"SDL_ReadLE32",tolua_SDL_SDL_SDL_ReadLE3200);
	tolua_function(tolua_S,"SDL_ReadBE32",tolua_SDL_SDL_SDL_ReadBE3200);
	tolua_function(tolua_S,"SDL_WriteLE16",tolua_SDL_SDL_SDL_WriteLE1600);
	tolua_function(tolua_S,"SDL_WriteBE16",tolua_SDL_SDL_SDL_WriteBE1600);
	tolua_function(tolua_S,"SDL_WriteLE32",tolua_SDL_SDL_SDL_WriteLE3200);
	tolua_function(tolua_S,"SDL_WriteBE32",tolua_SDL_SDL_SDL_WriteBE3200);
	tolua_constant(tolua_S,"SDL_TIMESLICE",SDL_TIMESLICE);
	tolua_constant(tolua_S,"TIMER_RESOLUTION",TIMER_RESOLUTION);
	tolua_function(tolua_S,"SDL_GetTicks",tolua_SDL_SDL_SDL_GetTicks00);
	tolua_function(tolua_S,"SDL_Delay",tolua_SDL_SDL_SDL_Delay00);
	tolua_cclass(tolua_S,"_SDL_TimerID","_SDL_TimerID","",NULL);
	tolua_beginmodule(tolua_S,"_SDL_TimerID");
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDL_AddTimer",tolua_SDL_SDL_SDL_AddTimer00);
	tolua_function(tolua_S,"SDL_RemoveTimer",tolua_SDL_SDL_SDL_RemoveTimer00);
	tolua_constant(tolua_S,"SDL_ALPHA_OPAQUE",SDL_ALPHA_OPAQUE);
	tolua_constant(tolua_S,"SDL_ALPHA_TRANSPARENT",SDL_ALPHA_TRANSPARENT);
	tolua_cclass(tolua_S,"SDL_Rect","SDL_Rect","",NULL);
	tolua_beginmodule(tolua_S,"SDL_Rect");
	tolua_variable(tolua_S,"x",tolua_get_SDL_Rect_x,tolua_set_SDL_Rect_x);
	tolua_variable(tolua_S,"y",tolua_get_SDL_Rect_y,tolua_set_SDL_Rect_y);
	tolua_variable(tolua_S,"w",tolua_get_SDL_Rect_unsigned_w,tolua_set_SDL_Rect_unsigned_w);
	tolua_variable(tolua_S,"h",tolua_get_SDL_Rect_unsigned_h,tolua_set_SDL_Rect_unsigned_h);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_Color","SDL_Color","",NULL);
	tolua_beginmodule(tolua_S,"SDL_Color");
	tolua_variable(tolua_S,"r",tolua_get_SDL_Color_unsigned_r,tolua_set_SDL_Color_unsigned_r);
	tolua_variable(tolua_S,"g",tolua_get_SDL_Color_unsigned_g,tolua_set_SDL_Color_unsigned_g);
	tolua_variable(tolua_S,"b",tolua_get_SDL_Color_unsigned_b,tolua_set_SDL_Color_unsigned_b);
	tolua_variable(tolua_S,"unused",tolua_get_SDL_Color_unsigned_unused,tolua_set_SDL_Color_unsigned_unused);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_Palette","SDL_Palette","",NULL);
	tolua_beginmodule(tolua_S,"SDL_Palette");
	tolua_variable(tolua_S,"ncolors",tolua_get_SDL_Palette_ncolors,tolua_set_SDL_Palette_ncolors);
	tolua_array(tolua_S,"colors",tolua_get_SDL_SDL_SDL_Palette_colors,tolua_set_SDL_SDL_SDL_Palette_colors);
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"SDL_PixelFormat","SDL_PixelFormat","",NULL);
	tolua_beginmodule(tolua_S,"SDL_PixelFormat");
	tolua_variable(tolua_S,"palette",tolua_get_SDL_PixelFormat_palette_ptr,tolua_set_SDL_PixelFormat_palette_ptr);
	tolua_variable(tolua_S,"BitsPerPixel",tolua_get_SDL_PixelFormat_unsigned_BitsPerPixel,tolua_set_SDL_PixelFormat_unsigned_BitsPerPixel);
	tolua_variable(tolua_S,"BytesPerPixel",tolua_get_SDL_PixelFormat_unsigned_BytesPerPixel,tolua_set_SDL_PixelFormat_unsigned_BytesPerPixel);
	tolua_variable(tolua_S,"Rloss",tolua_get_SDL_PixelFormat_unsigned_Rloss,tolua_set_SDL_PixelFormat_unsigned_Rloss);
	tolua_variable(tolua_S,"Gloss",tolua_get_SDL_PixelFormat_unsigned_Gloss,tolua_set_SDL_PixelFormat_unsigned_Gloss);
	tolua_variable(tolua_S,"Bloss",tolua_get_SDL_PixelFormat_unsigned_Bloss,tolua_set_SDL_PixelFormat_unsigned_Bloss);
	tolua_variable(tolua_S,"Aloss",tolua_get_SDL_PixelFormat_unsigned_Aloss,tolua_set_SDL_PixelFormat_unsigned_Aloss);
	tolua_variable(tolua_S,"Rshift",tolua_get_SDL_PixelFormat_unsigned_Rshift,tolua_set_SDL_PixelFormat_unsigned_Rshift);
	tolua_variable(tolua_S,"Gshift",tolua_get_SDL_PixelFormat_unsigned_Gshift,tolua_set_SDL_PixelFormat_unsigned_Gshift);
	tolua_variable(tolua_S,"Bshift",tolua_get_SDL_PixelFormat_unsigned_Bshift,tolua_set_SDL_PixelFormat_unsigned_Bshift);
	tolua_variable(tolua_S,"Ashift",tolua_get_SDL_PixelFormat_unsigned_Ashift,tolua_set_SDL_PixelFormat_unsigned_Ashift);
	tolua_variable(tolua_S,"Rmask",tolua_get_SDL_PixelFormat_unsigned_Rmask,tolua_set_SDL_PixelFormat_unsigned_Rmask);
	tolua_variable(tolua_S,"Gmask",tolua_get_SDL_PixelFormat_unsigned_Gmask,tolua_set_SDL_PixelFormat_unsigned_Gmask);
	tolua_variable(tolua_S,"Bmask",tolua_get_SDL_PixelFormat_unsigned_Bmask,tolua_set_SDL_PixelFormat_unsigned_Bmask);
	tolua_variable(tolua_S,"Amask",tolua_get_SDL_PixelFormat_unsigned_Amask,tolua_set_SDL_PixelFormat_unsigned_Amask);
	tolua_variable(tolua_S,"colorkey",tolua_get_SDL_PixelFormat_unsigned_colorkey,tolua_set_SDL_PixelFormat_unsigned_colorkey);
	tolua_variable(tolua_S,"alpha",tolua_get_SDL_PixelFormat_unsigned_alpha,tolua_set_SDL_PixelFormat_unsigned_alpha);
	tolua_endmodule(tolua_S);
	
	tolua_cclass(tolua_S,"SDL_Mutex","SDL_Mutex","",NULL);
	tolua_beginmodule(tolua_S,"SDL_Mutex");
	tolua_endmodule(tolua_S);

	tolua_function(tolua_S,"SDL_CreateMutex",tolua_SDL_SDL_SDL_CreateMutex);
	tolua_function(tolua_S,"SDL_DestroyMutex",tolua_SDL_SDL_SDL_DestroyMutex);
	tolua_function(tolua_S,"SDL_LockMutex",tolua_SDL_SDL_SDL_LockMutex);
	tolua_function(tolua_S,"SDL_UnlockMutex",tolua_SDL_SDL_SDL_UnlockMutex);

	tolua_cclass(tolua_S,"SDL_Surface","SDL_Surface","",NULL);
	tolua_beginmodule(tolua_S,"SDL_Surface");
	tolua_variable(tolua_S,"flags",tolua_get_SDL_Surface_unsigned_flags,tolua_set_SDL_Surface_unsigned_flags);
	tolua_variable(tolua_S,"format",tolua_get_SDL_Surface_format_ptr,tolua_set_SDL_Surface_format_ptr);
	tolua_variable(tolua_S,"w",tolua_get_SDL_Surface_w,tolua_set_SDL_Surface_w);
	tolua_variable(tolua_S,"h",tolua_get_SDL_Surface_h,tolua_set_SDL_Surface_h);
	tolua_variable(tolua_S,"pitch",tolua_get_SDL_Surface_unsigned_pitch,tolua_set_SDL_Surface_unsigned_pitch);
	tolua_variable(tolua_S,"pixels",tolua_get_SDL_Surface_pixels,tolua_set_SDL_Surface_pixels);
	tolua_variable(tolua_S,"clip_rect",tolua_get_SDL_Surface_clip_rect,tolua_set_SDL_Surface_clip_rect);
	tolua_variable(tolua_S,"unused1",tolua_get_SDL_Surface_unsigned_unused1,tolua_set_SDL_Surface_unsigned_unused1);
	tolua_variable(tolua_S,"refcount",tolua_get_SDL_Surface_refcount,tolua_set_SDL_Surface_refcount);
	tolua_endmodule(tolua_S);
	tolua_constant(tolua_S,"SDL_SWSURFACE",SDL_SWSURFACE);
	tolua_constant(tolua_S,"SDL_HWSURFACE",SDL_HWSURFACE);
	tolua_constant(tolua_S,"SDL_ASYNCBLIT",SDL_ASYNCBLIT);
	tolua_constant(tolua_S,"SDL_ANYFORMAT",SDL_ANYFORMAT);
	tolua_constant(tolua_S,"SDL_HWPALETTE",SDL_HWPALETTE);
	tolua_constant(tolua_S,"SDL_DOUBLEBUF",SDL_DOUBLEBUF);
	tolua_constant(tolua_S,"SDL_FULLSCREEN",SDL_FULLSCREEN);
	tolua_constant(tolua_S,"SDL_OPENGL",SDL_OPENGL);
	tolua_constant(tolua_S,"SDL_OPENGLBLIT",SDL_OPENGLBLIT);
	tolua_constant(tolua_S,"SDL_RESIZABLE",SDL_RESIZABLE);
	tolua_constant(tolua_S,"SDL_NOFRAME",SDL_NOFRAME);
	tolua_constant(tolua_S,"SDL_HWACCEL",SDL_HWACCEL);
	tolua_constant(tolua_S,"SDL_SRCCOLORKEY",SDL_SRCCOLORKEY);
	tolua_constant(tolua_S,"SDL_RLEACCELOK",SDL_RLEACCELOK);
	tolua_constant(tolua_S,"SDL_RLEACCEL",SDL_RLEACCEL);
	tolua_constant(tolua_S,"SDL_SRCALPHA",SDL_SRCALPHA);
	tolua_constant(tolua_S,"SDL_PREALLOC",SDL_PREALLOC);
	tolua_function(tolua_S,"SDL_MUSTLOCK",tolua_SDL_SDL_SDL_MUSTLOCK00);
	tolua_cclass(tolua_S,"SDL_VideoInfo","SDL_VideoInfo","",NULL);
	tolua_beginmodule(tolua_S,"SDL_VideoInfo");
	tolua_variable(tolua_S,"hw_available",tolua_get_SDL_VideoInfo_unsigned_hw_available,tolua_set_SDL_VideoInfo_unsigned_hw_available);
	tolua_variable(tolua_S,"wm_available",tolua_get_SDL_VideoInfo_unsigned_wm_available,tolua_set_SDL_VideoInfo_unsigned_wm_available);
	tolua_variable(tolua_S,"UnusedBits1",tolua_get_SDL_VideoInfo_unsigned_UnusedBits1,tolua_set_SDL_VideoInfo_unsigned_UnusedBits1);
	tolua_variable(tolua_S,"UnusedBits2",tolua_get_SDL_VideoInfo_unsigned_UnusedBits2,tolua_set_SDL_VideoInfo_unsigned_UnusedBits2);
	tolua_variable(tolua_S,"blit_hw",tolua_get_SDL_VideoInfo_unsigned_blit_hw,tolua_set_SDL_VideoInfo_unsigned_blit_hw);
	tolua_variable(tolua_S,"blit_hw_CC",tolua_get_SDL_VideoInfo_unsigned_blit_hw_CC,tolua_set_SDL_VideoInfo_unsigned_blit_hw_CC);
	tolua_variable(tolua_S,"blit_hw_A",tolua_get_SDL_VideoInfo_unsigned_blit_hw_A,tolua_set_SDL_VideoInfo_unsigned_blit_hw_A);
	tolua_variable(tolua_S,"blit_sw",tolua_get_SDL_VideoInfo_unsigned_blit_sw,tolua_set_SDL_VideoInfo_unsigned_blit_sw);
	tolua_variable(tolua_S,"blit_sw_CC",tolua_get_SDL_VideoInfo_unsigned_blit_sw_CC,tolua_set_SDL_VideoInfo_unsigned_blit_sw_CC);
	tolua_variable(tolua_S,"blit_sw_A",tolua_get_SDL_VideoInfo_unsigned_blit_sw_A,tolua_set_SDL_VideoInfo_unsigned_blit_sw_A);
	tolua_variable(tolua_S,"blit_fill",tolua_get_SDL_VideoInfo_unsigned_blit_fill,tolua_set_SDL_VideoInfo_unsigned_blit_fill);
	tolua_variable(tolua_S,"UnusedBits3",tolua_get_SDL_VideoInfo_unsigned_UnusedBits3,tolua_set_SDL_VideoInfo_unsigned_UnusedBits3);
	tolua_variable(tolua_S,"video_mem",tolua_get_SDL_VideoInfo_unsigned_video_mem,tolua_set_SDL_VideoInfo_unsigned_video_mem);
	tolua_variable(tolua_S,"vfmt",tolua_get_SDL_VideoInfo_vfmt_ptr,tolua_set_SDL_VideoInfo_vfmt_ptr);
	tolua_variable(tolua_S,"current_w",tolua_get_SDL_VideoInfo_current_w,tolua_set_SDL_VideoInfo_current_w);
	tolua_variable(tolua_S,"current_h",tolua_get_SDL_VideoInfo_current_h,tolua_set_SDL_VideoInfo_current_h);
	tolua_endmodule(tolua_S);
	tolua_constant(tolua_S,"SDL_YV12_OVERLAY",SDL_YV12_OVERLAY);
	tolua_constant(tolua_S,"SDL_IYUV_OVERLAY",SDL_IYUV_OVERLAY);
	tolua_constant(tolua_S,"SDL_YUY2_OVERLAY",SDL_YUY2_OVERLAY);
	tolua_constant(tolua_S,"SDL_UYVY_OVERLAY",SDL_UYVY_OVERLAY);
	tolua_constant(tolua_S,"SDL_YVYU_OVERLAY",SDL_YVYU_OVERLAY);
	tolua_cclass(tolua_S,"SDL_Overlay","SDL_Overlay","",NULL);
	tolua_beginmodule(tolua_S,"SDL_Overlay");
	tolua_variable(tolua_S,"format",tolua_get_SDL_Overlay_unsigned_format,tolua_set_SDL_Overlay_unsigned_format);
	tolua_variable(tolua_S,"w",tolua_get_SDL_Overlay_w,tolua_set_SDL_Overlay_w);
	tolua_variable(tolua_S,"h",tolua_get_SDL_Overlay_h,tolua_set_SDL_Overlay_h);
	tolua_variable(tolua_S,"planes",tolua_get_SDL_Overlay_planes,tolua_set_SDL_Overlay_planes);
	tolua_array(tolua_S,"pitches",tolua_get_SDL_SDL_SDL_Overlay_pitches,tolua_set_SDL_SDL_SDL_Overlay_pitches);
	tolua_array(tolua_S,"pixels",tolua_get_SDL_SDL_SDL_Overlay_pixels,tolua_set_SDL_SDL_SDL_Overlay_pixels);
	tolua_variable(tolua_S,"hw_overlay",tolua_get_SDL_Overlay_unsigned_hw_overlay,tolua_set_SDL_Overlay_unsigned_hw_overlay);
	tolua_variable(tolua_S,"UnusedBits",tolua_get_SDL_Overlay_unsigned_UnusedBits,tolua_set_SDL_Overlay_unsigned_UnusedBits);
	tolua_endmodule(tolua_S);
	tolua_constant(tolua_S,"SDL_GL_RED_SIZE",SDL_GL_RED_SIZE);
	tolua_constant(tolua_S,"SDL_GL_GREEN_SIZE",SDL_GL_GREEN_SIZE);
	tolua_constant(tolua_S,"SDL_GL_BLUE_SIZE",SDL_GL_BLUE_SIZE);
	tolua_constant(tolua_S,"SDL_GL_ALPHA_SIZE",SDL_GL_ALPHA_SIZE);
	tolua_constant(tolua_S,"SDL_GL_BUFFER_SIZE",SDL_GL_BUFFER_SIZE);
	tolua_constant(tolua_S,"SDL_GL_DOUBLEBUFFER",SDL_GL_DOUBLEBUFFER);
	tolua_constant(tolua_S,"SDL_GL_DEPTH_SIZE",SDL_GL_DEPTH_SIZE);
	tolua_constant(tolua_S,"SDL_GL_STENCIL_SIZE",SDL_GL_STENCIL_SIZE);
	tolua_constant(tolua_S,"SDL_GL_ACCUM_RED_SIZE",SDL_GL_ACCUM_RED_SIZE);
	tolua_constant(tolua_S,"SDL_GL_ACCUM_GREEN_SIZE",SDL_GL_ACCUM_GREEN_SIZE);
	tolua_constant(tolua_S,"SDL_GL_ACCUM_BLUE_SIZE",SDL_GL_ACCUM_BLUE_SIZE);
	tolua_constant(tolua_S,"SDL_GL_ACCUM_ALPHA_SIZE",SDL_GL_ACCUM_ALPHA_SIZE);
	tolua_constant(tolua_S,"SDL_GL_STEREO",SDL_GL_STEREO);
	tolua_constant(tolua_S,"SDL_GL_MULTISAMPLEBUFFERS",SDL_GL_MULTISAMPLEBUFFERS);
	tolua_constant(tolua_S,"SDL_GL_MULTISAMPLESAMPLES",SDL_GL_MULTISAMPLESAMPLES);
	tolua_constant(tolua_S,"SDL_GL_ACCELERATED_VISUAL",SDL_GL_ACCELERATED_VISUAL);
	tolua_constant(tolua_S,"SDL_GL_SWAP_CONTROL",SDL_GL_SWAP_CONTROL);
	tolua_constant(tolua_S,"SDL_LOGPAL",SDL_LOGPAL);
	tolua_constant(tolua_S,"SDL_PHYSPAL",SDL_PHYSPAL);
	tolua_function(tolua_S,"SDL_VideoDriverName",tolua_SDL_SDL_SDL_VideoDriverName00);
	tolua_function(tolua_S,"SDL_GetVideoSurface",tolua_SDL_SDL_SDL_GetVideoSurface00);
	tolua_function(tolua_S,"SDL_GetVideoInfo",tolua_SDL_SDL_SDL_GetVideoInfo00);
	tolua_function(tolua_S,"SDL_VideoModeOK",tolua_SDL_SDL_SDL_VideoModeOK00);
	tolua_function(tolua_S,"SDL_SetVideoMode",tolua_SDL_SDL_SDL_SetVideoMode00);
	tolua_function(tolua_S,"SDL_UpdateRect",tolua_SDL_SDL_SDL_UpdateRect00);
	tolua_function(tolua_S,"SDL_Flip",tolua_SDL_SDL_SDL_Flip00);
	tolua_function(tolua_S,"SDL_SetGamma",tolua_SDL_SDL_SDL_SetGamma00);
	tolua_function(tolua_S,"SDL_SetGammaRamp",tolua_SDL_SDL_SDL_SetGammaRamp00);
	tolua_function(tolua_S,"SDL_GetGammaRamp",tolua_SDL_SDL_SDL_GetGammaRamp00);
	tolua_function(tolua_S,"SDL_SetColors",tolua_SDL_SDL_SDL_SetColors00);
	tolua_function(tolua_S,"SDL_SetPalette",tolua_SDL_SDL_SDL_SetPalette00);
	tolua_function(tolua_S,"SDL_MapRGB",tolua_SDL_SDL_SDL_MapRGB00);
	tolua_function(tolua_S,"SDL_MapRGBA",tolua_SDL_SDL_SDL_MapRGBA00);
	tolua_function(tolua_S,"SDL_GetRGB",tolua_SDL_SDL_SDL_GetRGB00);
	tolua_function(tolua_S,"SDL_GetRGBA",tolua_SDL_SDL_SDL_GetRGBA00);
	tolua_function(tolua_S,"SDL_CreateRGBSurface",tolua_SDL_SDL_SDL_CreateRGBSurface00);
	tolua_function(tolua_S,"SDL_CreateRGBSurfaceFrom",tolua_SDL_SDL_SDL_CreateRGBSurfaceFrom00);
	tolua_function(tolua_S,"SDL_FreeSurface",tolua_SDL_SDL_SDL_FreeSurface00);
	tolua_function(tolua_S,"SDL_LockSurface",tolua_SDL_SDL_SDL_LockSurface00);
	tolua_function(tolua_S,"SDL_UnlockSurface",tolua_SDL_SDL_SDL_UnlockSurface00);
	tolua_function(tolua_S,"SDL_LoadBMP_RW",tolua_SDL_SDL_SDL_LoadBMP_RW00);
	tolua_function(tolua_S,"SDL_SaveBMP_RW",tolua_SDL_SDL_SDL_SaveBMP_RW00);
	tolua_function(tolua_S,"SDL_LoadBMP",tolua_SDL_SDL_SDL_LoadBMP00);
	tolua_function(tolua_S,"SDL_SaveBMP",tolua_SDL_SDL_SDL_SaveBMP00);
	tolua_function(tolua_S,"SDL_SetColorKey",tolua_SDL_SDL_SDL_SetColorKey00);
	tolua_function(tolua_S,"SDL_SetAlpha",tolua_SDL_SDL_SDL_SetAlpha00);
	tolua_function(tolua_S,"SDL_SetAlphaChannel",tolua_SDL_SDL_SDL_SetAlphaChannel00);
	tolua_function(tolua_S,"SDL_SetClipRect",tolua_SDL_SDL_SDL_SetClipRect00);
	tolua_function(tolua_S,"SDL_GetClipRect",tolua_SDL_SDL_SDL_GetClipRect00);
	tolua_function(tolua_S,"SDL_ConvertSurface",tolua_SDL_SDL_SDL_ConvertSurface00);
	tolua_function(tolua_S,"SDL_UpperBlit",tolua_SDL_SDL_SDL_UpperBlit00);
	tolua_function(tolua_S,"SDL_LowerBlit",tolua_SDL_SDL_SDL_LowerBlit00);
	tolua_function(tolua_S,"SDL_FillRect",tolua_SDL_SDL_SDL_FillRect00);

/*
	tolua_function(tolua_S,"GFX_pixelColor",tolua_SDL_SDL_GFX_pixelColor00);
	tolua_function(tolua_S,"GFX_pixelRGBA",tolua_SDL_SDL_GFX_pixelRGBA00);
	tolua_function(tolua_S,"GFX_hlineColor",tolua_SDL_SDL_GFX_hlineColor00);
	tolua_function(tolua_S,"GFX_hlineRGBA",tolua_SDL_SDL_GFX_hlineRGBA00);
	tolua_function(tolua_S,"GFX_vlineColor",tolua_SDL_SDL_GFX_vlineColor00);
	tolua_function(tolua_S,"GFX_vlineRGBA",tolua_SDL_SDL_GFX_vlineRGBA00);
	tolua_function(tolua_S,"GFX_rectangleColor",tolua_SDL_SDL_GFX_rectangleColor00);
	tolua_function(tolua_S,"GFX_rectangleRGBA",tolua_SDL_SDL_GFX_rectangleRGBA00);
	tolua_function(tolua_S,"GFX_roundedRectangleColor",tolua_SDL_SDL_GFX_roundedRectangleColor00);
	tolua_function(tolua_S,"GFX_roundedRectangleRGBA",tolua_SDL_SDL_GFX_roundedRectangleRGBA00);
	tolua_function(tolua_S,"GFX_boxColor",tolua_SDL_SDL_GFX_boxColor00);
	tolua_function(tolua_S,"GFX_boxRGBA",tolua_SDL_SDL_GFX_boxRGBA00);
	tolua_function(tolua_S,"GFX_roundedBoxColor",tolua_SDL_SDL_GFX_roundedBoxColor00);
	tolua_function(tolua_S,"GFX_roundedBoxRGBA",tolua_SDL_SDL_GFX_roundedBoxRGBA00);
	tolua_function(tolua_S,"GFX_lineColor",tolua_SDL_SDL_GFX_lineColor00);
	tolua_function(tolua_S,"GFX_lineRGBA",tolua_SDL_SDL_GFX_lineRGBA00);
	tolua_function(tolua_S,"GFX_aalineColor",tolua_SDL_SDL_GFX_aalineColor00);
	tolua_function(tolua_S,"GFX_aalineRGBA",tolua_SDL_SDL_GFX_aalineRGBA00);
	tolua_function(tolua_S,"GFX_thickLineColor",tolua_SDL_SDL_GFX_thickLineColor00);
	tolua_function(tolua_S,"GFX_thickLineRGBA",tolua_SDL_SDL_GFX_thickLineRGBA00);
	tolua_function(tolua_S,"GFX_circleColor",tolua_SDL_SDL_GFX_circleColor00);
	tolua_function(tolua_S,"GFX_circleRGBA",tolua_SDL_SDL_GFX_circleRGBA00);
	tolua_function(tolua_S,"GFX_arcColor",tolua_SDL_SDL_GFX_arcColor00);
	tolua_function(tolua_S,"GFX_arcRGBA",tolua_SDL_SDL_GFX_arcRGBA00);
	tolua_function(tolua_S,"GFX_aacircleColor",tolua_SDL_SDL_GFX_aacircleColor00);
	tolua_function(tolua_S,"GFX_aacircleRGBA",tolua_SDL_SDL_GFX_aacircleRGBA00);
	tolua_function(tolua_S,"GFX_filledCircleColor",tolua_SDL_SDL_GFX_filledCircleColor00);
	tolua_function(tolua_S,"GFX_filledCircleRGBA",tolua_SDL_SDL_GFX_filledCircleRGBA00);
	tolua_function(tolua_S,"GFX_ellipseColor",tolua_SDL_SDL_GFX_ellipseColor00);
	tolua_function(tolua_S,"GFX_ellipseRGBA",tolua_SDL_SDL_GFX_ellipseRGBA00);
	tolua_function(tolua_S,"GFX_aaellipseColor",tolua_SDL_SDL_GFX_aaellipseColor00);
	tolua_function(tolua_S,"GFX_aaellipseRGBA",tolua_SDL_SDL_GFX_aaellipseRGBA00);
	tolua_function(tolua_S,"GFX_filledEllipseColor",tolua_SDL_SDL_GFX_filledEllipseColor00);
	tolua_function(tolua_S,"GFX_filledEllipseRGBA",tolua_SDL_SDL_GFX_filledEllipseRGBA00);
	tolua_function(tolua_S,"GFX_pieColor",tolua_SDL_SDL_GFX_pieColor00);
	tolua_function(tolua_S,"GFX_pieRGBA",tolua_SDL_SDL_GFX_pieRGBA00);
	tolua_function(tolua_S,"GFX_filledPieColor",tolua_SDL_SDL_GFX_filledPieColor00);
	tolua_function(tolua_S,"GFX_filledPieRGBA",tolua_SDL_SDL_GFX_filledPieRGBA00);
	tolua_function(tolua_S,"GFX_trigonColor",tolua_SDL_SDL_GFX_trigonColor00);
	tolua_function(tolua_S,"GFX_trigonRGBA",tolua_SDL_SDL_GFX_trigonRGBA00);
	tolua_function(tolua_S,"GFX_aatrigonColor",tolua_SDL_SDL_GFX_aatrigonColor00);
	tolua_function(tolua_S,"GFX_aatrigonRGBA",tolua_SDL_SDL_GFX_aatrigonRGBA00);
	tolua_function(tolua_S,"GFX_filledTrigonColor",tolua_SDL_SDL_GFX_filledTrigonColor00);
	tolua_function(tolua_S,"GFX_filledTrigonRGBA",tolua_SDL_SDL_GFX_filledtrigonRGBA00);
	tolua_function(tolua_S,"GFX_polygonColor",tolua_SDL_SDL_GFX_polygonColor00);
	tolua_function(tolua_S,"GFX_polygonRGBA",tolua_SDL_SDL_GFX_polygonRGBA00);
	tolua_function(tolua_S,"GFX_aapolygonColor",tolua_SDL_SDL_GFX_aapolygonColor00);
	tolua_function(tolua_S,"GFX_aapolygonRGBA",tolua_SDL_SDL_GFX_aapolygonRGBA00);
	tolua_function(tolua_S,"GFX_filledPolygonColor",tolua_SDL_SDL_GFX_filledPolygonColor00);
	tolua_function(tolua_S,"GFX_filledPolygonRGBA",tolua_SDL_SDL_GFX_filledPolygonRGBA00);
	tolua_function(tolua_S,"GFX_texturedPolygon",tolua_SDL_SDL_GFX_texturedPolygon00);
	tolua_function(tolua_S,"GFX_polygonRGBA",tolua_SDL_SDL_GFX_polygonRGBA00);
	tolua_function(tolua_S,"GFX_rotozoomSurface",tolua_SDL_SDL_GFX_rotozoomSurface00);
	tolua_function(tolua_S,"GFX_rotozoomSurfaceXY",tolua_SDL_SDL_GFX_rotozoomSurfaceXY00);
	tolua_function(tolua_S,"GFX_rotozoomSurfaceSize",tolua_SDL_SDL_GFX_rotozoomSurfaceSize00);
	tolua_function(tolua_S,"GFX_rotozoomSurfaceSizeXY",tolua_SDL_SDL_GFX_rotozoomSurfaceSizeXY00);
*/
	//tolua_function(tolua_S,"GFX_zoomSurface",tolua_SDL_SDL_GFX_zoomSurface00);
/*
	tolua_function(tolua_S,"GFX_zoomSurfaceSize",tolua_SDL_SDL_GFX_zoomSurfaceSize00);
	tolua_function(tolua_S,"GFX_shrinkSurface",tolua_SDL_SDL_GFX_shrinkSurface00);
	tolua_function(tolua_S,"GFX_rotateSurface90Degrees",tolua_SDL_SDL_SDL_FillRect00);

	tolua_function(tolua_S,"GFX_SDL_gfxBlitRGBA",tolua_SDL_SDL_GFX_gfxBlitRGBA00);
	tolua_function(tolua_S,"GFX_SDL_gfxSetAlpha",tolua_SDL_SDL_GFX_gfxSetAlpha00);
	tolua_function(tolua_S,"GFX_SDL_gfxMultiplyAlpha",tolua_SDL_SDL_GFX_gfxMultiplyAlpha00);
*/
	tolua_function(tolua_S,"SDL_DisplayFormat",tolua_SDL_SDL_SDL_DisplayFormat00);
	tolua_function(tolua_S,"SDL_DisplayFormatAlpha",tolua_SDL_SDL_SDL_DisplayFormatAlpha00);
	tolua_function(tolua_S,"SDL_CreateYUVOverlay",tolua_SDL_SDL_SDL_CreateYUVOverlay00);
	tolua_function(tolua_S,"SDL_LockYUVOverlay",tolua_SDL_SDL_SDL_LockYUVOverlay00);
	tolua_function(tolua_S,"SDL_UnlockYUVOverlay",tolua_SDL_SDL_SDL_UnlockYUVOverlay00);
	tolua_function(tolua_S,"SDL_DisplayYUVOverlay",tolua_SDL_SDL_SDL_DisplayYUVOverlay00);
	tolua_function(tolua_S,"SDL_FreeYUVOverlay",tolua_SDL_SDL_SDL_FreeYUVOverlay00);
	tolua_function(tolua_S,"SDL_GL_LoadLibrary",tolua_SDL_SDL_SDL_GL_LoadLibrary00);
	tolua_function(tolua_S,"SDL_GL_GetProcAddress",tolua_SDL_SDL_SDL_GL_GetProcAddress00);
	tolua_function(tolua_S,"SDL_GL_SetSubData",tolua_SDL_SDL_SDL_GL_SetSubData00);
	tolua_function(tolua_S,"SDL_GL_SetAttribute",tolua_SDL_SDL_SDL_GL_SetAttribute00);
	tolua_function(tolua_S,"SDL_GL_GetAttribute",tolua_SDL_SDL_SDL_GL_GetAttribute00);
	tolua_function(tolua_S,"SDL_GL_SwapBuffers",tolua_SDL_SDL_SDL_GL_SwapBuffers00);
	tolua_function(tolua_S,"SDL_GL_UpdateRects",tolua_SDL_SDL_SDL_GL_UpdateRects00);
	tolua_function(tolua_S,"SDL_GL_Lock",tolua_SDL_SDL_SDL_GL_Lock00);
	tolua_function(tolua_S,"SDL_GL_Unlock",tolua_SDL_SDL_SDL_GL_Unlock00);
	tolua_function(tolua_S,"SDL_WM_SetCaption",tolua_SDL_SDL_SDL_WM_SetCaption00);
	tolua_function(tolua_S,"SDL_WM_GetCaption",tolua_SDL_SDL_SDL_WM_GetCaption00);
	tolua_function(tolua_S,"SDL_WM_SetIcon",tolua_SDL_SDL_SDL_WM_SetIcon00);
	tolua_function(tolua_S,"SDL_WM_IconifyWindow",tolua_SDL_SDL_SDL_WM_IconifyWindow00);
	tolua_function(tolua_S,"SDL_WM_ToggleFullScreen",tolua_SDL_SDL_SDL_WM_ToggleFullScreen00);
	tolua_constant(tolua_S,"SDL_GRAB_QUERY",SDL_GRAB_QUERY);
	tolua_constant(tolua_S,"SDL_GRAB_OFF",SDL_GRAB_OFF);
	tolua_constant(tolua_S,"SDL_GRAB_ON",SDL_GRAB_ON);
	tolua_constant(tolua_S,"SDL_GRAB_FULLSCREEN",SDL_GRAB_FULLSCREEN);
	tolua_function(tolua_S,"SDL_WM_GrabInput",tolua_SDL_SDL_SDL_WM_GrabInput00);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10, 83, 68, 76, 46, 83, 68, 76, 95, 65,108,108,111, 99, 83,
			117,114,102, 97, 99,101, 32, 61, 32, 83, 68, 76, 46, 83, 68,
			76, 95, 67,114,101, 97,116,101, 82, 71, 66, 83,117,114,102,
			97, 99,101, 10, 83, 68, 76, 46, 83, 68, 76, 95, 66,108,105,
			116, 83,117,114,102, 97, 99,101, 32, 61, 32, 83, 68, 76, 46,
			83, 68, 76, 95, 85,112,112,101,114, 66,108,105,116,32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 6");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_constant(tolua_S,"SDL_MAJOR_VERSION",SDL_MAJOR_VERSION);
	tolua_constant(tolua_S,"SDL_MINOR_VERSION",SDL_MINOR_VERSION);
	tolua_constant(tolua_S,"SDL_PATCHLEVEL",SDL_PATCHLEVEL);
	tolua_cclass(tolua_S,"SDL_version","SDL_version","",NULL);
	tolua_beginmodule(tolua_S,"SDL_version");
	tolua_variable(tolua_S,"major",tolua_get_SDL_version_unsigned_major,tolua_set_SDL_version_unsigned_major);
	tolua_variable(tolua_S,"minor",tolua_get_SDL_version_unsigned_minor,tolua_set_SDL_version_unsigned_minor);
	tolua_variable(tolua_S,"patch",tolua_get_SDL_version_unsigned_patch,tolua_set_SDL_version_unsigned_patch);
	tolua_endmodule(tolua_S);
	tolua_constant(tolua_S,"SDL_COMPILEDVERSION",SDL_COMPILEDVERSION);
	tolua_function(tolua_S,"SDL_VERSION",tolua_SDL_SDL_SDL_VERSION00);
	tolua_function(tolua_S,"SDL_VERSIONNUM",tolua_SDL_SDL_SDL_VERSIONNUM00);
	tolua_function(tolua_S,"SDL_VERSION_ATLEAST",tolua_SDL_SDL_SDL_VERSION_ATLEAST00);
	tolua_constant(tolua_S,"SDL_INIT_TIMER",SDL_INIT_TIMER);
	tolua_constant(tolua_S,"SDL_INIT_AUDIO",SDL_INIT_AUDIO);
	tolua_constant(tolua_S,"SDL_INIT_VIDEO",SDL_INIT_VIDEO);
	tolua_constant(tolua_S,"SDL_INIT_CDROM",SDL_INIT_CDROM);
	tolua_constant(tolua_S,"SDL_INIT_JOYSTICK",SDL_INIT_JOYSTICK);
	tolua_constant(tolua_S,"SDL_INIT_NOPARACHUTE",SDL_INIT_NOPARACHUTE);
	tolua_constant(tolua_S,"SDL_INIT_EVENTTHREAD",SDL_INIT_EVENTTHREAD);
	tolua_constant(tolua_S,"SDL_INIT_EVERYTHING",SDL_INIT_EVERYTHING);
	tolua_function(tolua_S,"SDL_Init",tolua_SDL_SDL_SDL_Init00);
	tolua_function(tolua_S,"SDL_InitSubSystem",tolua_SDL_SDL_SDL_InitSubSystem00);
	tolua_function(tolua_S,"SDL_QuitSubSystem",tolua_SDL_SDL_SDL_QuitSubSystem00);
	tolua_function(tolua_S,"SDL_WasInit",tolua_SDL_SDL_SDL_WasInit00);
	tolua_function(tolua_S,"SDL_Quit",tolua_SDL_SDL_SDL_Quit00);
	tolua_constant(tolua_S,"SDL_IMAGE_MAJOR_VERSION",SDL_IMAGE_MAJOR_VERSION);
	tolua_constant(tolua_S,"SDL_IMAGE_MINOR_VERSION",SDL_IMAGE_MINOR_VERSION);
	tolua_constant(tolua_S,"SDL_IMAGE_PATCHLEVEL",SDL_IMAGE_PATCHLEVEL);
	tolua_function(tolua_S,"SDL_IMAGE_VERSION",tolua_SDL_SDL_SDL_IMAGE_VERSION00);
	tolua_function(tolua_S,"IMG_LoadTyped_RW",tolua_SDL_SDL_IMG_LoadTyped_RW00);
	tolua_function(tolua_S,"IMG_Load",tolua_SDL_SDL_IMG_Load00);
	tolua_function(tolua_S,"IMG_Load_RW",tolua_SDL_SDL_IMG_Load_RW00);
	tolua_function(tolua_S,"IMG_InvertAlpha",tolua_SDL_SDL_IMG_InvertAlpha00);
	tolua_function(tolua_S,"IMG_isBMP",tolua_SDL_SDL_IMG_isBMP00);
	tolua_function(tolua_S,"IMG_isGIF",tolua_SDL_SDL_IMG_isGIF00);
	tolua_function(tolua_S,"IMG_isJPG",tolua_SDL_SDL_IMG_isJPG00);
	tolua_function(tolua_S,"IMG_isLBM",tolua_SDL_SDL_IMG_isLBM00);
	tolua_function(tolua_S,"IMG_isPCX",tolua_SDL_SDL_IMG_isPCX00);
	tolua_function(tolua_S,"IMG_isPNG",tolua_SDL_SDL_IMG_isPNG00);
	tolua_function(tolua_S,"IMG_isPNM",tolua_SDL_SDL_IMG_isPNM00);
	tolua_function(tolua_S,"IMG_isTIF",tolua_SDL_SDL_IMG_isTIF00);
	tolua_function(tolua_S,"IMG_isXCF",tolua_SDL_SDL_IMG_isXCF00);
	tolua_function(tolua_S,"IMG_isXPM",tolua_SDL_SDL_IMG_isXPM00);
	tolua_function(tolua_S,"IMG_isXV",tolua_SDL_SDL_IMG_isXV00);
	tolua_function(tolua_S,"IMG_LoadBMP_RW",tolua_SDL_SDL_IMG_LoadBMP_RW00);
	tolua_function(tolua_S,"IMG_LoadGIF_RW",tolua_SDL_SDL_IMG_LoadGIF_RW00);
	tolua_function(tolua_S,"IMG_LoadJPG_RW",tolua_SDL_SDL_IMG_LoadJPG_RW00);
	tolua_function(tolua_S,"IMG_LoadLBM_RW",tolua_SDL_SDL_IMG_LoadLBM_RW00);
	tolua_function(tolua_S,"IMG_LoadPCX_RW",tolua_SDL_SDL_IMG_LoadPCX_RW00);
	tolua_function(tolua_S,"IMG_LoadPNG_RW",tolua_SDL_SDL_IMG_LoadPNG_RW00);
	tolua_function(tolua_S,"IMG_LoadPNM_RW",tolua_SDL_SDL_IMG_LoadPNM_RW00);
	tolua_function(tolua_S,"IMG_LoadTGA_RW",tolua_SDL_SDL_IMG_LoadTGA_RW00);
	tolua_function(tolua_S,"IMG_LoadTIF_RW",tolua_SDL_SDL_IMG_LoadTIF_RW00);
	tolua_function(tolua_S,"IMG_LoadXCF_RW",tolua_SDL_SDL_IMG_LoadXCF_RW00);
	tolua_function(tolua_S,"IMG_LoadXPM_RW",tolua_SDL_SDL_IMG_LoadXPM_RW00);
	tolua_function(tolua_S,"IMG_LoadXV_RW",tolua_SDL_SDL_IMG_LoadXV_RW00);
	tolua_function(tolua_S,"IMG_ReadXPMFromArray",tolua_SDL_SDL_IMG_ReadXPMFromArray00);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10,108,111, 99, 97,108, 32, 83, 68, 76, 32, 61, 32, 83, 68,
			76, 10, 83, 68, 76, 46, 73, 77, 71, 95, 83,101,116, 69,114,
			114,111,114, 32, 61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 83,
			101,116, 69,114,114,111,114, 10, 83, 68, 76, 46, 73, 77, 71,
			95, 71,101,116, 69,114,114,111,114, 32, 61, 32, 83, 68, 76,
			46, 83, 68, 76, 95, 71,101,116, 69,114,114,111,114,32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 7");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_constant(tolua_S,"SDL_MIXER_MAJOR_VERSION",SDL_MIXER_MAJOR_VERSION);
	tolua_constant(tolua_S,"SDL_MIXER_MINOR_VERSION",SDL_MIXER_MINOR_VERSION);
	tolua_constant(tolua_S,"SDL_MIXER_PATCHLEVEL",SDL_MIXER_PATCHLEVEL);
	tolua_function(tolua_S,"SDL_MIXER_VERSION",tolua_SDL_SDL_SDL_MIXER_VERSION00);
	tolua_constant(tolua_S,"MIX_MAJOR_VERSION",MIX_MAJOR_VERSION);
	tolua_constant(tolua_S,"MIX_MINOR_VERSION",MIX_MINOR_VERSION);
	tolua_constant(tolua_S,"MIX_PATCHLEVEL",MIX_PATCHLEVEL);
	tolua_constant(tolua_S,"MIX_DEFAULT_FREQUENCY",MIX_DEFAULT_FREQUENCY);
	tolua_constant(tolua_S,"MIX_DEFAULT_CHANNELS",MIX_DEFAULT_CHANNELS);
	tolua_constant(tolua_S,"MIX_MAX_VOLUME",MIX_MAX_VOLUME);
	tolua_cclass(tolua_S,"Mix_Chunk","Mix_Chunk","",NULL);
	tolua_beginmodule(tolua_S,"Mix_Chunk");
	tolua_variable(tolua_S,"allocated",tolua_get_Mix_Chunk_allocated,tolua_set_Mix_Chunk_allocated);
	tolua_variable(tolua_S,"abuf",tolua_get_Mix_Chunk_abuf,tolua_set_Mix_Chunk_abuf);
	tolua_variable(tolua_S,"alen",tolua_get_Mix_Chunk_unsigned_alen,tolua_set_Mix_Chunk_unsigned_alen);
	tolua_variable(tolua_S,"volume",tolua_get_Mix_Chunk_unsigned_volume,tolua_set_Mix_Chunk_unsigned_volume);
	tolua_endmodule(tolua_S);
	tolua_constant(tolua_S,"MIX_NO_FADING",MIX_NO_FADING);
	tolua_constant(tolua_S,"MIX_FADING_OUT",MIX_FADING_OUT);
	tolua_constant(tolua_S,"MIX_FADING_IN",MIX_FADING_IN);
	tolua_constant(tolua_S,"MUS_NONE",MUS_NONE);
	tolua_constant(tolua_S,"MUS_CMD",MUS_CMD);
	tolua_constant(tolua_S,"MUS_WAV",MUS_WAV);
	tolua_constant(tolua_S,"MUS_MOD",MUS_MOD);
	tolua_constant(tolua_S,"MUS_MID",MUS_MID);
	tolua_constant(tolua_S,"MUS_OGG",MUS_OGG);
	tolua_constant(tolua_S,"MUS_MP3",MUS_MP3);
	tolua_constant(tolua_S,"MUS_MP3_MAD",MUS_MP3_MAD);
	tolua_function(tolua_S,"Mix_OpenAudio",tolua_SDL_SDL_Mix_OpenAudio00);
	tolua_function(tolua_S,"Mix_AllocateChannels",tolua_SDL_SDL_Mix_AllocateChannels00);
	tolua_function(tolua_S,"Mix_QuerySpec",tolua_SDL_SDL_Mix_QuerySpec00);
	tolua_function(tolua_S,"Mix_LoadWAV_RW",tolua_SDL_SDL_Mix_LoadWAV_RW00);
	tolua_function(tolua_S,"Mix_LoadWAV",tolua_SDL_SDL_Mix_LoadWAV00);
	tolua_function(tolua_S,"Mix_LoadMUS",tolua_SDL_SDL_Mix_LoadMUS00);
	tolua_function(tolua_S,"Mix_LoadMUS_RW",tolua_SDL_SDL_Mix_LoadMUS_RW00);
	tolua_function(tolua_S,"Mix_QuickLoad_WAV",tolua_SDL_SDL_Mix_QuickLoad_WAV00);
	tolua_function(tolua_S,"Mix_QuickLoad_RAW",tolua_SDL_SDL_Mix_QuickLoad_RAW00);
	tolua_function(tolua_S,"Mix_FreeChunk",tolua_SDL_SDL_Mix_FreeChunk00);
	tolua_function(tolua_S,"Mix_FreeMusic",tolua_SDL_SDL_Mix_FreeMusic00);
	tolua_constant(tolua_S,"MIX_CHANNEL_POST",MIX_CHANNEL_POST);
	tolua_variable(tolua_S,"MIX_EFFECTSMAXSPEED",tolua_get_SDL_MIX_EFFECTSMAXSPEED,NULL);
	tolua_function(tolua_S,"Mix_SetPanning",tolua_SDL_SDL_Mix_SetPanning00);
	tolua_function(tolua_S,"Mix_SetPosition",tolua_SDL_SDL_Mix_SetPosition00);
	tolua_function(tolua_S,"Mix_SetDistance",tolua_SDL_SDL_Mix_SetDistance00);
	tolua_function(tolua_S,"Mix_SetReverseStereo",tolua_SDL_SDL_Mix_SetReverseStereo00);
	tolua_function(tolua_S,"Mix_ReserveChannels",tolua_SDL_SDL_Mix_ReserveChannels00);
	tolua_function(tolua_S,"Mix_GroupChannel",tolua_SDL_SDL_Mix_GroupChannel00);
	tolua_function(tolua_S,"Mix_GroupChannels",tolua_SDL_SDL_Mix_GroupChannels00);
	tolua_function(tolua_S,"Mix_GroupAvailable",tolua_SDL_SDL_Mix_GroupAvailable00);
	tolua_function(tolua_S,"Mix_GroupCount",tolua_SDL_SDL_Mix_GroupCount00);
	tolua_function(tolua_S,"Mix_GroupOldest",tolua_SDL_SDL_Mix_GroupOldest00);
	tolua_function(tolua_S,"Mix_GroupNewer",tolua_SDL_SDL_Mix_GroupNewer00);
	tolua_function(tolua_S,"Mix_PlayChannelTimed",tolua_SDL_SDL_Mix_PlayChannelTimed00);
	tolua_function(tolua_S,"Mix_PlayMusic",tolua_SDL_SDL_Mix_PlayMusic00);
	tolua_function(tolua_S,"Mix_FadeInMusic",tolua_SDL_SDL_Mix_FadeInMusic00);
	tolua_function(tolua_S,"Mix_FadeInMusicPos",tolua_SDL_SDL_Mix_FadeInMusicPos00);
	tolua_function(tolua_S,"Mix_FadeInChannelTimed",tolua_SDL_SDL_Mix_FadeInChannelTimed00);
	tolua_function(tolua_S,"Mix_PlayChannel",tolua_SDL_SDL_Mix_PlayChannel00);
	tolua_function(tolua_S,"Mix_FadeInChannel",tolua_SDL_SDL_Mix_FadeInChannel00);
	tolua_function(tolua_S,"Mix_Volume",tolua_SDL_SDL_Mix_Volume00);
	tolua_function(tolua_S,"Mix_VolumeChunk",tolua_SDL_SDL_Mix_VolumeChunk00);
	tolua_function(tolua_S,"Mix_VolumeMusic",tolua_SDL_SDL_Mix_VolumeMusic00);
	tolua_function(tolua_S,"Mix_HaltChannel",tolua_SDL_SDL_Mix_HaltChannel00);
	tolua_function(tolua_S,"Mix_HaltGroup",tolua_SDL_SDL_Mix_HaltGroup00);
	tolua_function(tolua_S,"Mix_HaltMusic",tolua_SDL_SDL_Mix_HaltMusic00);
	tolua_function(tolua_S,"Mix_ExpireChannel",tolua_SDL_SDL_Mix_ExpireChannel00);
	tolua_function(tolua_S,"Mix_FadeOutChannel",tolua_SDL_SDL_Mix_FadeOutChannel00);
	tolua_function(tolua_S,"Mix_FadeOutGroup",tolua_SDL_SDL_Mix_FadeOutGroup00);
	tolua_function(tolua_S,"Mix_FadeOutMusic",tolua_SDL_SDL_Mix_FadeOutMusic00);
	tolua_function(tolua_S,"Mix_FadingMusic",tolua_SDL_SDL_Mix_FadingMusic00);
	tolua_function(tolua_S,"Mix_FadingChannel",tolua_SDL_SDL_Mix_FadingChannel00);
	tolua_function(tolua_S,"Mix_Pause",tolua_SDL_SDL_Mix_Pause00);
	tolua_function(tolua_S,"Mix_Resume",tolua_SDL_SDL_Mix_Resume00);
	tolua_function(tolua_S,"Mix_Paused",tolua_SDL_SDL_Mix_Paused00);
	tolua_function(tolua_S,"Mix_PauseMusic",tolua_SDL_SDL_Mix_PauseMusic00);
	tolua_function(tolua_S,"Mix_ResumeMusic",tolua_SDL_SDL_Mix_ResumeMusic00);
	tolua_function(tolua_S,"Mix_RewindMusic",tolua_SDL_SDL_Mix_RewindMusic00);
	tolua_function(tolua_S,"Mix_PausedMusic",tolua_SDL_SDL_Mix_PausedMusic00);
	tolua_function(tolua_S,"Mix_SetMusicPosition",tolua_SDL_SDL_Mix_SetMusicPosition00);
	tolua_function(tolua_S,"Mix_Playing",tolua_SDL_SDL_Mix_Playing00);
	tolua_function(tolua_S,"Mix_PlayingMusic",tolua_SDL_SDL_Mix_PlayingMusic00);
	tolua_function(tolua_S,"Mix_SetMusicCMD",tolua_SDL_SDL_Mix_SetMusicCMD00);
	tolua_function(tolua_S,"Mix_SetSynchroValue",tolua_SDL_SDL_Mix_SetSynchroValue00);
	tolua_function(tolua_S,"Mix_GetSynchroValue",tolua_SDL_SDL_Mix_GetSynchroValue00);
	tolua_function(tolua_S,"Mix_GetChunk",tolua_SDL_SDL_Mix_GetChunk00);
	tolua_function(tolua_S,"Mix_CloseAudio",tolua_SDL_SDL_Mix_CloseAudio00);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10,105,102, 32,110,111,116, 32, 83, 68, 76, 46, 77, 73, 88,
			95, 67, 72, 65, 78, 78, 69, 76, 83, 32,116,104,101,110, 10,
			83, 68, 76, 46, 77, 73, 88, 95, 67, 72, 65, 78, 78, 69, 76,
			83, 32, 61, 32, 56, 10,101,110,100, 10,105,102, 32, 83, 68,
			76, 46, 83, 68, 76, 95, 66, 89, 84, 69, 79, 82, 68, 69, 82,
			32, 61, 61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 76, 73, 76,
			95, 69, 78, 68, 73, 65, 78, 32,116,104,101,110, 10, 83, 68,
			76, 46, 77, 73, 88, 95, 68, 69, 70, 65, 85, 76, 84, 95, 70,
			79, 82, 77, 65, 84, 32, 61, 32, 83, 68, 76, 46, 65, 85, 68,
			73, 79, 95, 83, 49, 54, 76, 83, 66, 10,101,108,115,101, 10,
			83, 68, 76, 46, 77, 73, 88, 95, 68, 69, 70, 65, 85, 76, 84,
			95, 70, 79, 82, 77, 65, 84, 32, 61, 32, 83, 68, 76, 46, 65,
			85, 68, 73, 79, 95, 83, 49, 54, 77, 83, 66, 10,101,110,100,
			10, 83, 68, 76, 46, 77, 73, 88, 95, 86, 69, 82, 83, 73, 79,
			78, 32, 61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 77, 73, 88,
			69, 82, 95, 86, 69, 82, 83, 73, 79, 78, 10, 83, 68, 76, 46,
			77,105,120, 95, 83,101,116, 69,114,114,111,114, 32, 61, 32,
			83, 68, 76, 46, 83, 68, 76, 95, 83,101,116, 69,114,114,111,
			114, 10, 83, 68, 76, 46, 77,105,120, 95, 71,101,116, 69,114,
			114,111,114, 32, 61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 71,
			101,116, 69,114,114,111,114,32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 8");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_constant(tolua_S,"SDL_NET_MAJOR_VERSION",SDL_NET_MAJOR_VERSION);
	tolua_constant(tolua_S,"SDL_NET_MINOR_VERSION",SDL_NET_MINOR_VERSION);
	tolua_constant(tolua_S,"SDL_NET_PATCHLEVEL",SDL_NET_PATCHLEVEL);
	tolua_function(tolua_S,"SDL_NET_VERSION",tolua_SDL_SDL_SDL_NET_VERSION00);
	tolua_function(tolua_S,"SDLNet_Init",tolua_SDL_SDL_SDLNet_Init00);
	tolua_function(tolua_S,"SDLNet_Quit",tolua_SDL_SDL_SDLNet_Quit00);
	tolua_cclass(tolua_S,"IPaddress","IPaddress","",NULL);
	tolua_beginmodule(tolua_S,"IPaddress");
	tolua_variable(tolua_S,"host",tolua_get_IPaddress_unsigned_host,tolua_set_IPaddress_unsigned_host);
	tolua_variable(tolua_S,"port",tolua_get_IPaddress_unsigned_port,tolua_set_IPaddress_unsigned_port);
	tolua_endmodule(tolua_S);
	tolua_constant(tolua_S,"INADDR_ANY",INADDR_ANY);
	tolua_constant(tolua_S,"INADDR_NONE",INADDR_NONE);
	tolua_constant(tolua_S,"INADDR_BROADCAST",INADDR_BROADCAST);
	tolua_function(tolua_S,"SDLNet_ResolveHost",tolua_SDL_SDL_SDLNet_ResolveHost00);
	tolua_function(tolua_S,"SDLNet_ResolveIP",tolua_SDL_SDL_SDLNet_ResolveIP00);
	tolua_cclass(tolua_S,"_TCPsocket","_TCPsocket","",NULL);
	tolua_beginmodule(tolua_S,"_TCPsocket");
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDLNet_TCP_Open",tolua_SDL_SDL_SDLNet_TCP_Open00);
	tolua_function(tolua_S,"SDLNet_TCP_Accept",tolua_SDL_SDL_SDLNet_TCP_Accept00);
	tolua_function(tolua_S,"SDLNet_TCP_GetPeerAddress",tolua_SDL_SDL_SDLNet_TCP_GetPeerAddress00);
	tolua_function(tolua_S,"SDLNet_TCP_Send",tolua_SDL_SDL_SDLNet_TCP_Send00);
	tolua_function(tolua_S,"SDLNet_TCP_Recv",tolua_SDL_SDL_SDLNet_TCP_Recv00);
	tolua_function(tolua_S,"SDLNet_TCP_Close",tolua_SDL_SDL_SDLNet_TCP_Close00);
	tolua_constant(tolua_S,"SDLNET_MAX_UDPCHANNELS",SDLNET_MAX_UDPCHANNELS);
	tolua_constant(tolua_S,"SDLNET_MAX_UDPADDRESSES",SDLNET_MAX_UDPADDRESSES);
	tolua_cclass(tolua_S,"_UDPsocket","_UDPsocket","",NULL);
	tolua_beginmodule(tolua_S,"_UDPsocket");
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"UDPpacket","UDPpacket","",NULL);
	tolua_beginmodule(tolua_S,"UDPpacket");
	tolua_variable(tolua_S,"channel",tolua_get_UDPpacket_channel,tolua_set_UDPpacket_channel);
	tolua_variable(tolua_S,"data",tolua_get_UDPpacket_data,tolua_set_UDPpacket_data);
	tolua_variable(tolua_S,"len",tolua_get_UDPpacket_len,tolua_set_UDPpacket_len);
	tolua_variable(tolua_S,"maxlen",tolua_get_UDPpacket_maxlen,tolua_set_UDPpacket_maxlen);
	tolua_variable(tolua_S,"status",tolua_get_UDPpacket_status,tolua_set_UDPpacket_status);
	tolua_variable(tolua_S,"address",tolua_get_UDPpacket_address,tolua_set_UDPpacket_address);
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDLNet_AllocPacket",tolua_SDL_SDL_SDLNet_AllocPacket00);
	tolua_function(tolua_S,"SDLNet_ResizePacket",tolua_SDL_SDL_SDLNet_ResizePacket00);
	tolua_function(tolua_S,"SDLNet_FreePacket",tolua_SDL_SDL_SDLNet_FreePacket00);
	tolua_function(tolua_S,"SDLNet_UDP_Open",tolua_SDL_SDL_SDLNet_UDP_Open00);
	tolua_function(tolua_S,"SDLNet_UDP_Bind",tolua_SDL_SDL_SDLNet_UDP_Bind00);
	tolua_function(tolua_S,"SDLNet_UDP_Unbind",tolua_SDL_SDL_SDLNet_UDP_Unbind00);
	tolua_function(tolua_S,"SDLNet_UDP_GetPeerAddress",tolua_SDL_SDL_SDLNet_UDP_GetPeerAddress00);
	tolua_function(tolua_S,"SDLNet_UDP_Send",tolua_SDL_SDL_SDLNet_UDP_Send00);
	tolua_function(tolua_S,"SDLNet_UDP_Recv",tolua_SDL_SDL_SDLNet_UDP_Recv00);
	tolua_function(tolua_S,"SDLNet_UDP_Close",tolua_SDL_SDL_SDLNet_UDP_Close00);
	tolua_cclass(tolua_S,"_SDLNet_SocketSet","_SDLNet_SocketSet","",NULL);
	tolua_beginmodule(tolua_S,"_SDLNet_SocketSet");
	tolua_endmodule(tolua_S);
	tolua_cclass(tolua_S,"_SDLNet_GenericSocket","_SDLNet_GenericSocket","",NULL);
	tolua_beginmodule(tolua_S,"_SDLNet_GenericSocket");
	tolua_variable(tolua_S,"ready",tolua_get__SDLNet_GenericSocket_ready,tolua_set__SDLNet_GenericSocket_ready);
	tolua_endmodule(tolua_S);
	tolua_function(tolua_S,"SDLNet_AllocSocketSet",tolua_SDL_SDL_SDLNet_AllocSocketSet00);
	tolua_function(tolua_S,"SDLNet_AddSocket",tolua_SDL_SDL_SDLNet_AddSocket00);
	tolua_function(tolua_S,"SDLNet_DelSocket",tolua_SDL_SDL_SDLNet_DelSocket00);
	tolua_function(tolua_S,"SDLNet_CheckSockets",tolua_SDL_SDL_SDLNet_CheckSockets00);
	tolua_function(tolua_S,"SDLNet_FreeSocketSet",tolua_SDL_SDL_SDLNet_FreeSocketSet00);
	tolua_function(tolua_S,"SDLNet_TCP_AddSocket",tolua_SDL_SDL_SDLNet_TCP_AddSocket00);
	tolua_function(tolua_S,"SDLNet_UDP_AddSocket",tolua_SDL_SDL_SDLNet_UDP_AddSocket00);
	tolua_function(tolua_S,"SDLNet_TCP_DelSocket",tolua_SDL_SDL_SDLNet_TCP_DelSocket00);
	tolua_function(tolua_S,"SDLNet_UDP_DelSocket",tolua_SDL_SDL_SDLNet_UDP_DelSocket00);
	tolua_function(tolua_S,"SDLNet_SocketReady",tolua_SDL_SDL_SDLNet_SocketReady00);
	tolua_function(tolua_S,"SDLNet_SocketReady",tolua_SDL_SDL_SDLNet_SocketReady01);
	tolua_function(tolua_S,"SDLNet_SocketReady",tolua_SDL_SDL_SDLNet_SocketReady02);
	tolua_function(tolua_S,"SDLNet_Write16",tolua_SDL_SDL_SDLNet_Write1600);
	tolua_function(tolua_S,"SDLNet_Write32",tolua_SDL_SDL_SDLNet_Write3200);
	tolua_function(tolua_S,"SDLNet_Read16",tolua_SDL_SDL_SDLNet_Read1600);
	tolua_function(tolua_S,"SDLNet_Read32",tolua_SDL_SDL_SDLNet_Read3200);
	tolua_constant(tolua_S,"SDL_DATA_ALIGNED",SDL_DATA_ALIGNED);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10,108,111, 99, 97,108, 32, 83, 68, 76, 32, 61, 32, 83, 68,
			76, 10, 83, 68, 76, 46, 83, 68, 76, 78,101,116, 95, 83,101,
			116, 69,114,114,111,114, 32, 61, 32, 83, 68, 76, 46, 83, 68,
			76, 95, 83,101,116, 69,114,114,111,114, 10, 83, 68, 76, 46,
			83, 68, 76, 78,101,116, 95, 71,101,116, 69,114,114,111,114,
			32, 61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 71,101,116, 69,
			114,114,111,114,32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 9");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_constant(tolua_S,"SDL_TTF_MAJOR_VERSION",SDL_TTF_MAJOR_VERSION);
	tolua_constant(tolua_S,"SDL_TTF_MINOR_VERSION",SDL_TTF_MINOR_VERSION);
	tolua_constant(tolua_S,"SDL_TTF_PATCHLEVEL",SDL_TTF_PATCHLEVEL);
	tolua_function(tolua_S,"SDL_TTF_VERSION",tolua_SDL_SDL_SDL_TTF_VERSION00);
	tolua_constant(tolua_S,"TTF_MAJOR_VERSION",TTF_MAJOR_VERSION);
	tolua_constant(tolua_S,"TTF_MINOR_VERSION",TTF_MINOR_VERSION);
	tolua_constant(tolua_S,"TTF_PATCHLEVEL",TTF_PATCHLEVEL);
	tolua_constant(tolua_S,"UNICODE_BOM_NATIVE",UNICODE_BOM_NATIVE);
	tolua_constant(tolua_S,"UNICODE_BOM_SWAPPED",UNICODE_BOM_SWAPPED);
	tolua_function(tolua_S,"TTF_ByteSwappedUNICODE",tolua_SDL_SDL_TTF_ByteSwappedUNICODE00);
	tolua_function(tolua_S,"TTF_Init",tolua_SDL_SDL_TTF_Init00);
	tolua_function(tolua_S,"TTF_OpenFont",tolua_SDL_SDL_TTF_OpenFont00);
	tolua_function(tolua_S,"TTF_OpenFontIndex",tolua_SDL_SDL_TTF_OpenFontIndex00);
	tolua_function(tolua_S,"TTF_OpenFontRW",tolua_SDL_SDL_TTF_OpenFontRW00);
	tolua_function(tolua_S,"TTF_OpenFontIndexRW",tolua_SDL_SDL_TTF_OpenFontIndexRW00);
	tolua_constant(tolua_S,"TTF_STYLE_NORMAL",TTF_STYLE_NORMAL);
	tolua_constant(tolua_S,"TTF_STYLE_BOLD",TTF_STYLE_BOLD);
	tolua_constant(tolua_S,"TTF_STYLE_ITALIC",TTF_STYLE_ITALIC);
	tolua_constant(tolua_S,"TTF_STYLE_UNDERLINE",TTF_STYLE_UNDERLINE);
	tolua_function(tolua_S,"TTF_GetFontStyle",tolua_SDL_SDL_TTF_GetFontStyle00);
	tolua_function(tolua_S,"TTF_SetFontStyle",tolua_SDL_SDL_TTF_SetFontStyle00);
	tolua_function(tolua_S,"TTF_FontHeight",tolua_SDL_SDL_TTF_FontHeight00);
	tolua_function(tolua_S,"TTF_FontAscent",tolua_SDL_SDL_TTF_FontAscent00);
	tolua_function(tolua_S,"TTF_FontDescent",tolua_SDL_SDL_TTF_FontDescent00);
	tolua_function(tolua_S,"TTF_FontLineSkip",tolua_SDL_SDL_TTF_FontLineSkip00);
	tolua_function(tolua_S,"TTF_FontFaces",tolua_SDL_SDL_TTF_FontFaces00);
	tolua_function(tolua_S,"TTF_FontFaceIsFixedWidth",tolua_SDL_SDL_TTF_FontFaceIsFixedWidth00);
	tolua_function(tolua_S,"TTF_FontFaceFamilyName",tolua_SDL_SDL_TTF_FontFaceFamilyName00);
	tolua_function(tolua_S,"TTF_FontFaceStyleName",tolua_SDL_SDL_TTF_FontFaceStyleName00);
	tolua_function(tolua_S,"TTF_GlyphMetrics",tolua_SDL_SDL_TTF_GlyphMetrics00);
	tolua_function(tolua_S,"TTF_SizeText",tolua_SDL_SDL_TTF_SizeText00);
	tolua_function(tolua_S,"TTF_SizeUTF8",tolua_SDL_SDL_TTF_SizeUTF800);
	tolua_function(tolua_S,"TTF_SizeUNICODE",tolua_SDL_SDL_TTF_SizeUNICODE00);
	tolua_function(tolua_S,"TTF_RenderText_Solid",tolua_SDL_SDL_TTF_RenderText_Solid00);
	tolua_function(tolua_S,"TTF_RenderUTF8_Solid",tolua_SDL_SDL_TTF_RenderUTF8_Solid00);
	tolua_function(tolua_S,"TTF_RenderUNICODE_Solid",tolua_SDL_SDL_TTF_RenderUNICODE_Solid00);
	tolua_function(tolua_S,"TTF_RenderGlyph_Solid",tolua_SDL_SDL_TTF_RenderGlyph_Solid00);
	tolua_function(tolua_S,"TTF_RenderText_Shaded",tolua_SDL_SDL_TTF_RenderText_Shaded00);
	tolua_function(tolua_S,"TTF_RenderUTF8_Shaded",tolua_SDL_SDL_TTF_RenderUTF8_Shaded00);
	tolua_function(tolua_S,"TTF_RenderUNICODE_Shaded",tolua_SDL_SDL_TTF_RenderUNICODE_Shaded00);
	tolua_function(tolua_S,"TTF_RenderGlyph_Shaded",tolua_SDL_SDL_TTF_RenderGlyph_Shaded00);
	tolua_function(tolua_S,"TTF_RenderText_Blended",tolua_SDL_SDL_TTF_RenderText_Blended00);
	tolua_function(tolua_S,"TTF_RenderUTF8_Blended",tolua_SDL_SDL_TTF_RenderUTF8_Blended00);
	tolua_function(tolua_S,"TTF_RenderUNICODE_Blended",tolua_SDL_SDL_TTF_RenderUNICODE_Blended00);
	tolua_function(tolua_S,"TTF_RenderGlyph_Blended",tolua_SDL_SDL_TTF_RenderGlyph_Blended00);
	tolua_function(tolua_S,"TTF_CloseFont",tolua_SDL_SDL_TTF_CloseFont00);
	tolua_function(tolua_S,"TTF_Quit",tolua_SDL_SDL_TTF_Quit00);
	tolua_function(tolua_S,"TTF_WasInit",tolua_SDL_SDL_TTF_WasInit00);

	{ /* begin embedded lua code */
		int top = lua_gettop(tolua_S);
		static unsigned char B[] = {
			10,108,111, 99, 97,108, 32, 83, 68, 76, 32, 61, 32, 83, 68,
			76, 10, 83, 68, 76, 46, 84, 84, 70, 95, 86, 69, 82, 83, 73,
			79, 78, 32, 61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 84, 84,
			70, 95, 86, 69, 82, 83, 73, 79, 78, 10, 83, 68, 76, 46, 84,
			84, 70, 95, 82,101,110,100,101,114, 84,101,120,116, 32, 61,
			32, 83, 68, 76, 46, 84, 84, 70, 95, 82,101,110,100,101,114,
			84,101,120,116, 95, 83,104, 97,100,101,100, 10, 83, 68, 76,
			46, 84, 84, 70, 95, 82,101,110,100,101,114, 85, 84, 70, 56,
			32, 61, 32, 83, 68, 76, 46, 84, 84, 70, 95, 82,101,110,100,
			101,114, 85, 84, 70, 56, 95, 83,104, 97,100,101,100, 10, 83,
			68, 76, 46, 84, 84, 70, 95, 82,101,110,100,101,114, 85, 78,
			73, 67, 79, 68, 69, 32, 61, 32, 83, 68, 76, 46, 84, 84, 70,
			95, 82,101,110,100,101,114, 85, 78, 73, 67, 79, 68, 69, 95,
			83,104, 97,100,101,100, 10, 83, 68, 76, 46, 84, 84, 70, 95,
			83,101,116, 69,114,114,111,114, 32, 61, 32, 83, 68, 76, 46,
			83, 68, 76, 95, 83,101,116, 69,114,114,111,114, 10, 83, 68,
			76, 46, 84, 84, 70, 95, 71,101,116, 69,114,114,111,114, 32,
			61, 32, 83, 68, 76, 46, 83, 68, 76, 95, 71,101,116, 69,114,
			114,111,114,32
		};
		tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 10");
		lua_settop(tolua_S, top);
	} /* end of embedded lua code */

	tolua_function(tolua_S,"SDL_GetPixel",tolua_SDL_SDL_SDL_GetPixel00);
	tolua_function(tolua_S,"SDL_PutPixel",tolua_SDL_SDL_SDL_PutPixel00);
	tolua_function(tolua_S,"LuaSDL_AudioCh1",tolua_SDL_SDL_LuaSDL_AudioCh100);
	tolua_function(tolua_S,"LuaSDL_AudioCh2",tolua_SDL_SDL_LuaSDL_AudioCh200);
	tolua_function(tolua_S,"SDL_AudioSpec_new",tolua_SDL_SDL_SDL_AudioSpec_new00);
	tolua_function(tolua_S,"SDL_AudioSpec_delete",tolua_SDL_SDL_SDL_AudioSpec_delete00);
	tolua_function(tolua_S,"SDL_AudioCVT_new",tolua_SDL_SDL_SDL_AudioCVT_new00);
	tolua_function(tolua_S,"SDL_AudioCVT_delete",tolua_SDL_SDL_SDL_AudioCVT_delete00);
	tolua_function(tolua_S,"SDL_CDtrack_new",tolua_SDL_SDL_SDL_CDtrack_new00);
	tolua_function(tolua_S,"SDL_CDtrack_delete",tolua_SDL_SDL_SDL_CDtrack_delete00);
	tolua_function(tolua_S,"SDL_CD_new",tolua_SDL_SDL_SDL_CD_new00);
	tolua_function(tolua_S,"SDL_CD_delete",tolua_SDL_SDL_SDL_CD_delete00);
	tolua_function(tolua_S,"SDL_Event_new",tolua_SDL_SDL_SDL_Event_new00);
	tolua_function(tolua_S,"SDL_Event_delete",tolua_SDL_SDL_SDL_Event_delete00);
	tolua_function(tolua_S,"SDL_keysym_new",tolua_SDL_SDL_SDL_keysym_new00);
	tolua_function(tolua_S,"SDL_keysym_delete",tolua_SDL_SDL_SDL_keysym_delete00);
	tolua_function(tolua_S,"SDL_Cursor_new",tolua_SDL_SDL_SDL_Cursor_new00);
	tolua_function(tolua_S,"SDL_Cursor_delete",tolua_SDL_SDL_SDL_Cursor_delete00);
	tolua_function(tolua_S,"IPaddress_new",tolua_SDL_SDL_IPaddress_new00);
	tolua_function(tolua_S,"IPaddress_delete",tolua_SDL_SDL_IPaddress_delete00);
	tolua_function(tolua_S,"SDL_version_new",tolua_SDL_SDL_SDL_version_new00);
	tolua_function(tolua_S,"SDL_version_delete",tolua_SDL_SDL_SDL_version_delete00);
	tolua_function(tolua_S,"SDL_Rect_new",tolua_SDL_SDL_SDL_Rect_new00);
	tolua_function(tolua_S,"SDL_Rect_delete",tolua_SDL_SDL_SDL_Rect_delete00);
	tolua_function(tolua_S,"SDL_Color_new",tolua_SDL_SDL_SDL_Color_new00);
	tolua_function(tolua_S,"SDL_Color_delete",tolua_SDL_SDL_SDL_Color_delete00);
	tolua_function(tolua_S,"SDL_PixelFormat_new",tolua_SDL_SDL_SDL_PixelFormat_new00);
	tolua_function(tolua_S,"SDL_PixelFormat_delete",tolua_SDL_SDL_SDL_PixelFormat_delete00);
	tolua_function(tolua_S,"SDL_VideoInfo_new",tolua_SDL_SDL_SDL_VideoInfo_new00);
	tolua_function(tolua_S,"SDL_VideoInfo_delete",tolua_SDL_SDL_SDL_VideoInfo_delete00);
	tolua_endmodule(tolua_S);
	tolua_endmodule(tolua_S);
	return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_SDL (lua_State* tolua_S) {
	return tolua_SDL_open(tolua_S);
};
#endif

