/* ================================================================== */
/*
 * luasdl.c
 * Main executable for LuaSDL.
 *
 * This file is part of LuaSDL.
 *
 * Copyright (c) 2007 Kein-Hong Man <khman@users.sf.net>
 * The COPYRIGHT-LuaSDL file describes the conditions
 * under which this software may be distributed.
 */
/* ================================================================== */

/* ================================================================== */
/*
 * Console output is always redirected to stdout.txt and stderr.txt.
 * TODO: better handling of return value
 */
/* ================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
#include <windows.h>

#include "SDL.h"
#include "SDL_net.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua++.h"

#include "sdllib.h"

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM < 501
#error "requires Lua 5.1 or better, unless you know what you are doing"
#endif

/* holds information to be passed to LuaSDL library startup */
struct LuaSDL_StartInfo start_info;

/* ================================================================== */
/*
 * argument processing
 */
/* ================================================================== */
static int process_args(lua_State *L, char *argv[], char **app)
{
    int nargs = 0;      /* # arguments sent to script */
    *app = 0;           /* no script found at beginning */
    while (*(++argv)) {
        char c = *argv[0];
        if (c == '-' || *app) {
            luaL_checkstack(L, ++nargs, "too many arguments to script");
            lua_pushstring(L, *argv);
        } else {        /* take first non-option as main script */
            *app = *argv;
        }
    }
    return nargs;
}

/* ================================================================== */
/*
 * support functions for path processing
 */
/* ================================================================== */
/*
 * true if directory separator found, advances path, eats
 * adjacent separators
 */
int is_dir_sep(char **path)
{
    int sep = **path == '/' || **path == '\\';
    if (sep) {
        while (**path == '/' || **path == '\\') (*path)++;      /* skip */
    }
    return sep;
}
/*
 * true if DOS-style drive spec at beginning, advances path,
 * eats adjacent separators
 */
int is_drive_spec(char **path)
{
    int drv = strlen(*path) >= 3 &&     /* find <letter><colon><dir_sep> */
             isalpha(**path) &&
             (*path)[1] == ':' &&
             ((*path)[2] == '/' || (*path)[2] == '\\');
    if (drv) {                          /* skip */
        *path += 2;
        is_dir_sep(path);
    }
    return drv;
}
/*
 * true if a separator found, advances path, returns path segment
 */
int has_dir_sep(char **path, char *part)
{
    char c;
    int sep = 0;
    while ((c = **path) != '\0') {
        if ((sep = is_dir_sep(path))) break;
        *(part++) = c;
        (*path)++;
    }
    *part = '\0';
    return sep;
}
/*
 * remove a segment from a well-formed absolute path spec
 */
void remove_seg(char *path)
{
    /* find root spec */
    char *pos;
    char *root = path;
    char *last = path + strlen(path)-1;
    is_dir_sep(&root) || is_drive_spec(&root);
    /* remove trailing dir_seps */
    while (pos = last, pos >= root && is_dir_sep(&pos)) {
        *last-- = '\0';
    }
    /* remove a segment */
    while (pos = last, pos >= root && !is_dir_sep(&pos)) {
        *last-- = '\0';
    }
}

/* ================================================================== */
/*
 * Get absolute paths so that we can reliably find files. Needed
 * because LuaSDL needs to find the default script in the executable's
 * directory if nothing is specified on comment line. The absolute
 * paths are passed to the LuaSDL library so that scripts can use it.
 */
/* ================================================================== */

static int get_absolute_paths(struct LuaSDL_StartInfo *info)
{
    char c;
    size_t sz;
    char *path;
    /* platform-dependent means to get absolute paths */
#ifdef __WIN32__
    strcpy(info->dir_sep, "\\");
    getcwd(info->dir_cwd, MAX_PATH);
    info->dir_cwd[MAX_PATH] = '\0';
    GetModuleFileName(NULL, info->dir_exe, MAX_PATH);
    info->dir_exe[MAX_PATH] = '\0';
#else
#error "absolute path handling not yet implemented for other platforms"
#endif
    /* ensure trailing dir_sep for dir_cwd */
    path = info->dir_cwd;
    sz = strlen(path);
    c = path[sz-1];
    if (c != '/' && c != '\\') {
        if (sz >= MAX_PATH) return 1;
        strcat(path, info->dir_sep);
    }
    /* remove filename portion for dir_exe */
    remove_seg(info->dir_exe);
    return 0;
}

/* ================================================================== */
/*
 * determine script path, mostly platform-independent
 * directory paths normalized to always have trailing dir_seps
 */
/* ================================================================== */

static int get_script_path(struct LuaSDL_StartInfo *info, char *app)
{
    char spec[MAX_PATH+1];
    char seg[MAX_PATH+1];
    char *path = info->dir_app;
    /*
     * decide on where to grab the main script from, one of:
     * (1) current working directory + script path given in argument
     * (2) executable's directory + standard init file
     */
    if (app) {
        strcpy(path, info->dir_cwd);
        strcpy(spec, app);
    } else {
        strcpy(path, info->dir_exe);
        strcpy(spec, SCRIPT_DEFAULT);
    }
    app = spec;
    /* check for absolute path specification */
    if (is_dir_sep(&app) || is_drive_spec(&app)) {
        size_t sz = app - spec;
        path[sz] = '\0';
        while (sz--) { path[sz] = spec[sz]; }
    }
    /* normalize script path if relative, last seg is actual filename */
    while(has_dir_sep(&app, seg)) {
        if (strcmp(seg, ".") == 0) {
            /* do nothing, consume the segment */
        } else if (strcmp(seg, "..") == 0) {
            /* remove a segment from the path */
            remove_seg(path);
        } else {
            /* path segment, add it to path */
            if (strlen(seg) + strlen(path) < MAX_PATH) {
                strcat(path, seg);
                strcat(path, info->dir_sep);
            } else {
                return 1;
            }
        }
    } /* end while */
    if (*seg == '\0')
        /* no final segment means no file given, use default name */
        strcpy(info->appname, SCRIPT_DEFAULT);
    else
        strcpy(info->appname, seg);
    return 0;
}

/* ================================================================== */
/*
 * protected call to main script
 */
/* ================================================================== */
static int lua_dofile(lua_State *L, const char *filename, int nargs)
{
    int status = luaL_loadfile(L, filename);
    if (status == 0) {
        lua_insert(L, -nargs-1);
        status = lua_pcall(L, nargs, 1, 0);
    }
    if (status && !lua_isnil(L, -1)) {
        const char *msg = lua_tostring(L, -1);
        if (msg == NULL) msg = "(error object is not a string)";
        fprintf(stderr, "%s\n", msg);
        fflush(stderr);
    }
    return status;
}

/* ================================================================== */
/*
 * check if file exists
 */
/* ================================================================== */
int file_exists(const char *path)
{
    FILE *h = fopen(path, "r");
    if (h) {
        fclose(h);
        return 1;
    }
    return 0;
}

/* ================================================================== */
/*
 * make absolute script path
 */
/* ================================================================== */
static int make_script_path(char *path, struct LuaSDL_StartInfo *info, char *app)
{
    if (get_script_path(info, app) ||
        strlen(info->dir_app) + strlen(info->appname) >= MAX_PATH) {
        fprintf(stderr, "Error: absolute script path too long.\n");
        fflush(stderr);
        return 1;
    }
    strcpy(path, info->dir_app);
    strcat(path, info->appname);
    return 0;
}

/* ================================================================== */
/*
 * main function
 */
/* ================================================================== */
int main(int argc, char *argv[])
{
    int nargs, status;
    char *app = 0;
    char path[MAX_PATH+1];
    if (get_absolute_paths(&start_info)) {
        fprintf(stderr, "Error: absolute path too long.\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    /* create Lua state */
    lua_State* L = lua_open();
    /* process arguments and get main script path */
    nargs = process_args(L, argv, &app);
    if (make_script_path(path, &start_info, app)) {
        exit(EXIT_FAILURE);
    }
    /* if script not found, try default script */
    if (!file_exists(path)) {
        if (make_script_path(path, &start_info, NULL)) {
            exit(EXIT_FAILURE);
        }
        start_info.notfound = app;
    } else {
        start_info.notfound = 0;
    }
    /* standard Lua libraries */
    luaL_openlibs(L);
    /* initialize LuaSDL */
    luaopen_LuaSDL(L, &start_info);
    /* ======================= */
    /* add your libraries here */
    /* ======================= */
    /* run main script */
    status = lua_dofile(L, path, nargs);
    lua_close(L);
    return status;
}
