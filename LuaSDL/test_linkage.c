/* ================================================================== */
/*
 * test_linkage.c
 * A primitive program to test linkage of the dynamic libraries.
 *
 * This file is part of LuaSDL.
 *
 * PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
 */
/* ================================================================== */

/* ================================================================== */
/*
 * Program should exit with a code of 0, and no news is good news.
 * Any error results in an exit code >0 and messages in stderr.txt.
 */
/* ================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_ttf.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua++.h"

int main(int argc, char *argv[])
{
    SDL_Surface *image;
    int result = 0;

    /* test linkage of SDL */
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* test linkage of SDL_image */
    image = IMG_Load("luasdl.c");
    if (image) {
        fprintf(stderr, "IMG_Load not supposed to work\n");
        result = 1;
    }

    /* test linkage of SDL_mixer */
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Couldn't initialize SDL_mixer\n");
        result = 1;
    }
    Mix_CloseAudio();

    /* test linkage of SDL_net */
    if (SDLNet_Init() == -1) {
        fprintf(stderr, "Couldn't initialize SDL_net: %s\n", SDLNet_GetError());
        result = 1;
    } else {
        SDLNet_Quit();
    }

    /* test linkage of SDL_ttf */
    if (TTF_Init() == -1) {
        fprintf(stderr, "Couldn't initialize SDL_ttf: %s\n", TTF_GetError());
        result = 1;
    } else {
        TTF_Quit();
    }

    /* test linkage of Lua and tolua++ libraries */
    lua_State* L = lua_open();
    if (!L) {
        fprintf(stderr, "Couldn't initialize Lua\n");
        exit(2);
    } else {
        tolua_open(L);
        lua_close(L);
    }

    SDL_Quit();
    return result;
}
