/* ================================================================== */
/*
 * SDL_ttf.c
 * Dummy DLL for SDL_ttf.
 *
 * This file is part of LuaSDL.
 *
 * PUBLIC DOMAIN. Author: Kein-Hong Man <khman@users.sf.net> 2007
 */
/* ================================================================== */

/* ================================================================== */
/*
 * NOTE:
 * - No error messages are set, so your app should know that it's
 *   never going to use SDL_ttf.
 */
/* ================================================================== */

#include "SDL_ttf.h"

const SDL_version *TTF_Linked_Version(void)
{
    static SDL_version linked_version;
    linked_version.major = 0;
    linked_version.minor = 0;
    linked_version.patch = 0;
    return(&linked_version);
}

void TTF_ByteSwappedUNICODE(int swapped)
{
}

int TTF_Init(void)
{
    return -1;
}

TTF_Font * TTF_OpenFont(const char *file, int ptsize)
{
    return 0;
}

TTF_Font * TTF_OpenFontIndex(const char *file, int ptsize, long index)
{
    return 0;
}

TTF_Font * TTF_OpenFontRW(SDL_RWops *src, int freesrc, int ptsize)
{
    return 0;
}

TTF_Font * TTF_OpenFontIndexRW(SDL_RWops *src, int freesrc, int ptsize, long index)
{
    return 0;
}

int TTF_GetFontStyle(TTF_Font *font)
{
    return 0;
}

void TTF_SetFontStyle(TTF_Font *font, int style)
{
}

int TTF_FontHeight(TTF_Font *font)
{
    return 0;
}

int TTF_FontAscent(TTF_Font *font)
{
    return 0;
}

int TTF_FontDescent(TTF_Font *font)
{
    return 0;
}

int TTF_FontLineSkip(TTF_Font *font)
{
    return 0;
}

long TTF_FontFaces(TTF_Font *font)
{
    return 0;
}

int TTF_FontFaceIsFixedWidth(TTF_Font *font)
{
    return 0;
}

char * TTF_FontFaceFamilyName(TTF_Font *font)
{
    return 0;
}

char * TTF_FontFaceStyleName(TTF_Font *font)
{
    return 0;
}

int TTF_GlyphMetrics(TTF_Font *font, Uint16 ch,
                     int *minx, int *maxx, int *miny, int *maxy, int *advance)
{
    return 0;
}

int TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h)
{
    return 0;
}

int TTF_SizeUTF8(TTF_Font *font, const char *text, int *w, int *h)
{
    return 0;
}

int TTF_SizeUNICODE(TTF_Font *font, const Uint16 *text, int *w, int *h)
{
    return 0;
}

SDL_Surface * TTF_RenderText_Solid(TTF_Font *font, const char *text, SDL_Color fg)
{
    return 0;
}

SDL_Surface * TTF_RenderUTF8_Solid(TTF_Font *font, const char *text, SDL_Color fg)
{
    return 0;
}

SDL_Surface * TTF_RenderUNICODE_Solid(TTF_Font *font, const Uint16 *text, SDL_Color fg)
{
    return 0;
}

SDL_Surface * TTF_RenderGlyph_Solid(TTF_Font *font, Uint16 ch, SDL_Color fg)
{
    return 0;
}

SDL_Surface * TTF_RenderText_Shaded(TTF_Font *font, const char *text, SDL_Color fg, SDL_Color bg)
{
    return 0;
}

SDL_Surface * TTF_RenderUTF8_Shaded(TTF_Font *font, const char *text, SDL_Color fg, SDL_Color bg)
{
    return 0;
}

SDL_Surface * TTF_RenderUNICODE_Shaded(TTF_Font *font, const Uint16 *text, SDL_Color fg, SDL_Color bg)
{
    return 0;
}

SDL_Surface * TTF_RenderGlyph_Shaded(TTF_Font *font, Uint16 ch, SDL_Color fg, SDL_Color bg)
{
    return 0;
}

SDL_Surface * TTF_RenderText_Blended(TTF_Font *font, const char *text, SDL_Color fg)
{
    return 0;
}

SDL_Surface * TTF_RenderUTF8_Blended(TTF_Font *font, const char *text, SDL_Color fg)
{
    return 0;
}

SDL_Surface * TTF_RenderUNICODE_Blended(TTF_Font *font, const Uint16 *text, SDL_Color fg)
{
    return 0;
}

SDL_Surface * TTF_RenderGlyph_Blended(TTF_Font *font, Uint16 ch, SDL_Color fg)
{
    return 0;
}

void TTF_CloseFont(TTF_Font *font)
{
}

void TTF_Quit(void)
{
}

int TTF_WasInit(void)
{
    return 0;
}
