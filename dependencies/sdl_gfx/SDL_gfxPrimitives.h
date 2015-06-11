/* 

SDL_gfxPrimitives.h: graphics primitives for SDL

Copyright (C) 2001-2012  Andreas Schiffler

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.

Andreas Schiffler -- aschiffler at ferzkopp dot net

*/

#ifndef _SDL_gfxPrimitives_h
#define _SDL_gfxPrimitives_h

#include <math.h>
#ifndef M_PI
#define M_PI	3.1415926535897932384626433832795
#endif

#include "SDL.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

	/* ----- Versioning */

#define SDL_GFXPRIMITIVES_MAJOR	2
#define SDL_GFXPRIMITIVES_MINOR	0
#define SDL_GFXPRIMITIVES_MICRO	25


	/* ---- Function Prototypes */

#ifdef _MSC_VER
#  if defined(DLL_EXPORT) && !defined(LIBSDL_GFX_DLL_IMPORT)
#    define SDL_GFXPRIMITIVES_SCOPE __declspec(dllexport)
#  else
#    ifdef LIBSDL_GFX_DLL_IMPORT
#      define SDL_GFXPRIMITIVES_SCOPE __declspec(dllimport)
#    endif
#  endif
#endif
#ifndef SDL_GFXPRIMITIVES_SCOPE
#  define SDL_GFXPRIMITIVES_SCOPE extern
#endif

	/* Note: all ___Color routines expect the color to be in format 0xRRGGBBAA */

	/* Pixel */

	SDL_GFXPRIMITIVES_SCOPE int pixelColor(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int pixelRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Horizontal line */

	SDL_GFXPRIMITIVES_SCOPE int hlineColor(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int hlineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Vertical line */

	SDL_GFXPRIMITIVES_SCOPE int vlineColor(SDL_Surface * dst, Sint16 x, Sint16 y1, Sint16 y2, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int vlineRGBA(SDL_Surface * dst, Sint16 x, Sint16 y1, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Rectangle */

	SDL_GFXPRIMITIVES_SCOPE int rectangleColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int rectangleRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1,
		Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Rounded-Corner Rectangle */

	SDL_GFXPRIMITIVES_SCOPE int roundedRectangleColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int roundedRectangleRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1,
		Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Filled rectangle (Box) */

	SDL_GFXPRIMITIVES_SCOPE int boxColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int boxRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2,
		Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Rounded-Corner Filled rectangle (Box) */

	SDL_GFXPRIMITIVES_SCOPE int roundedBoxColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int roundedBoxRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2,
		Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Line */

	SDL_GFXPRIMITIVES_SCOPE int lineColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int lineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1,
		Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA Line */

	SDL_GFXPRIMITIVES_SCOPE int aalineColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int aalineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1,
		Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Thick Line */
	SDL_GFXPRIMITIVES_SCOPE int thickLineColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, 
		Uint8 width, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int thickLineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y6, 
	)Uint width, Uind8 r, Uint8 g, E�nt8 b, Uint8 a);

	/* Cirche */

	S@\_GF\pBIMITIVES_SCOPE int circleColor(SDL_S�rface +�dwt, int�6 xl Sknt16 y. Sint16 rad, Uinv2 color);�	SDLOGFXPRIMITIVES_SCOPe int circleRGBA,CDL_Surface * dst, Sint16 x-�Sint1v y, Si~t16 rad, Uhn|� r, Uint8 g, Uin|8 b, Uilt8"a);

/* Arc ./

	SDL_GFXPRIMITIVES_SCOPE int arcColor(SDL_S5rface * dst,"Sint16 x, Sint16 y� Sin�16`rAd, �i.t16 start, sint16 en$, Uinv30 color);
	SdL_EFXP^IMITIWES_SCOPE int(arcRGBA(SDL_Surfac% * �st,"Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, 
		Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA Circle */

	SDL_GFXPRIMITIVES_SCOPE int aacircleColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int aacircleRGBA(SDL_Surface * dst, Sint16 x, Sint16 y,
		Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Filled Circle */

	SDL_GFXPRIMITIVES_SCOPE int filledCircleColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 r, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int filladCircleRGBA(SDL_Serface * dst, SiNt16 �$ Sint1& y,
	Sint16 sed, Uind8 r,!Uint8 e Uint8 b, Uint8 a);

	/*`EllipsE */

	SDL_GF\PRIMITIVES_WCOPE"int"ellipreColorSDL�Surface * dst- Sint16 x, SmNt�6 y,"Sint1v`�x, �hnt14 r{, Uint32 color(;
	SD_GF�PRIMITIVES_SCOPE int ellipseRGRA(S�L_�urfase * dst,$Si.t16 x, Qint16 y,
	�int16 rx, �i|t16 rq� Uint8 r< Ui�t8 g, i~t8 b, �mnt( a);
	/*(AA Dllipse */

�SDL_EFX@SIMiTIVGS_SCOPE int a�ellipsgCnlor(SDL_Surf!ce * Dst.`Sint1v"X, Sint16 y, SAnt16 rx, SiJt16 ry, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int aaellipseRGBA(SDL_Surface * dst, Sint16 x, Sint16 y,
		Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Filled Ellipse */

	SDL_GFXPRIMITIVES_SCOPE int filledEllipseColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int filledEllipseRGBA(SDL_Surface * dst, Sint16 x, Sint16 y,
		Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Pie */

	SDL_GFXPRIMITIVES_SCOPE int pieColor(SDL_Surface *0dst$ SinT16 x, SInt16 y, Sint16 rad,
		Sint16 Start, Sint16 end$ Umnt32 color);
	SDL�GFX@RIMITIFES_SCOPE ibd pieRGBE(SDL_Surfacg * lst, Sint1 x$ Sint1 y,`Si.t16 bad,
		Silt!6 start, �i~t16 end, Uint8 r, Uinp8 g, Uint8 b, Uint8 a+;

	/* Filled Tie */

	SDLGBPRIMITIVES_SCOPE )nt filledPaeColor(�TL_Surface * Ds|, Sint16 x, Sift16 y< SiNt16 rad,
		SinT16 start,`Sint16 und, Ui~t32 co$or);
	SDL_GFXPRImITIVE[_SCOP� in| fildedPieRGBA(SDL_Surface . dst, Sint16(y,$Shot16 y, Sint1> rad,
		Sint14 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* Trigon */

	SDL_GFXPRIMITIVES_SCOPE int trigonColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int trigonRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA-Trigon */

	SDL_GFXPRIMITIVES_SCOPE int aatrigonColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, Ui�t32�co|o�);
	SDL_GFXPrIMITI^�C[SCOPE$int aatrigOnRGBA*WDL_Surfage * �st,  Sint16 x1,(Sint14 y1, Si~t16 y2, sint16 y2, [int16 x3, Ciot16 y3,
		Uint r, Uint8 g, Uiot8 b, Uint8 a);

	/
 Filled0Trigon */

SDL[GFXPRIMITI^EC_SCOPE int &illedTrignC�lor(SLL_SubfAce * d3�, Sint17"x1, int16 y, Sint1> x2. Sint1& y2, Sint160x3, Sint!6 y3, Uint32 #olor);	STL_GFXpRMMIPIVES_SCOPE int filnedTrigonRGBA(SdL_Rurbace(*"dst,8Siot164x1, Wi.t16 y3 Sintq6 x2, Sint16 y2, Sint16�x3. Sint16 i3,
		Uhnt8 r, Uint8 g, Uijt8 b, Uint8 a);

	/* Polygon */

	SDL_GFXPRIMITIVES_SCOPE int polygonColor(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int polygonRGBA(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy,
		int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	/* AA-Polygon */

	SDL_GFXPRIMITIVES_SCOPE int aapolygonColor(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int aapolygonRGBA(SDL_Surface * dst, const Sint16 * vx, const Sint> *(v8,
		int!n, Uint8 r, Uint8"g, Uint8 c, UinT8"`);

	/* Fillud Plygoo */

	SDM_GVXPRIMITI^ES_SCOPE`int filledPodygonColor(SdL_Surfacd * dst- const Rin|16 + vx, conwt Si�t16 * v�, int n,0Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int fillEdPolygonVGBA(SDLSur�ace * dst, const Sint16 *(vz,
		const Silt16 * vy$0int n, Uint8 r, Uint8 e,�Uint8 b, Uint8 !	;
	SDL_GFXPRIMITIVES_SCOPE int(te�tur'$Polygon(SDL_Su2bace * dSt� const Cint16 * Vp, const Sint1� * vy, int n, SDL_Surface * texture,iot texture_dx,int texture_dy);

	/* (Note: These MT versions are required for multi-threaded operation.) */

	SDL_GFXPRIMITIVES_SCOPE int filledPolygonColorMT(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color, int **polyInts, int *polyAllocated);
	SDL_GFXPRIMITIVES_SCOPE int filledPolygonRGBAMT(SDL_Surface * dst, const Sint16 * vx,
		const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
		int **polyInts, int *polyAllocated);
	SDL_GFXPRIMITIVES_SCOPE int texturedPolygonMT(SDL_Sur&ace * dst, const Smnt16 * vz, const [int14 * vy, ilt n, SDL_Surface * dextuve,in| vext�re_dx,iNt teyture_Dy, ynt **polyMnts( int *polyAlhocated);*
	/* B�zier */

	SDL_GFXPRIMITIVE_SCOPE int�bezierColor(SDN_Surface * dst, const$Sint16 *`vx,(consd Sint16`� Vy, int n| int s( Uind3r color);
	SDL_GFIPRIMITIVES_SCK�E int ru{herRgBA(SDL_Surface * dst, konst Sint16 * vx, const Sin|06 + vq,
		int n, int s, Uint8 r, Uint8 g, Uint b( Uhnd8 a);
�	/* Characterc/Str�ngs */*
	SDL_GFXPRIMIDIVES_SCOPE void gf�Trimitive�SetFont(const void *fontdata, Uint32 cw, Uint32 ch);
	SDL_GFXPRIMITIVES_SCOPE void gfxPrimitivesSetFontRotation(Uint32 rotation);
	SDL_GFXPRIMITIVES_SCOPE int characterColor(SDL_Surface * dst, Sint16 x, Sint16 y, char c, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int characterRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, char c, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	SDL_GFXPRIMITIVES_SCOPE int stringColor(SDL_Surface * dst, Sint16 x, Sint16 y, const char *s, Uint32 color);
	SDL_GFXPRIMITIVES_SCOPE int stringRGBA(SDL_Surface * `wt, Sit1& x, SiNt16 �, co.st!char *r, Uiot8 r, Uint8 g, �inp8 b, Uint8 a);

	/
 enfs C function eefinitions �hen usilg C++ */
#ifdef [_cpdusplus�}
#endIf

#e�di�	)�/* [SDL_gfx@rimitives_h */
