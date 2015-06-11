/* 

SDL_gfxPrimitives.c: graphics primitives for SDL surfaces

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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "SDL_gfxPrimitives.h"
#include "SDL_rotozoom.h"
#include "SDL_gfxPrimitives_font.h"
#include "SDL_gfxBlitFunc.h"

/* -===================- */

#define DEFAULT_ALPHA_PIXEL_ROUTINE
#undef EXPERIMENTAL_ALPHA_PIXEL_ROUTINE
#define ALPHA_PIXEL_ADDITIVE_BLEND

/* ---- Structures */

/*!
\brief The structure passed to the internal Bresenham iterator.
*/
typedef struct {
	Sint16 x, y;
	int dx, dy, s1, s2, swapdir, error;
	Uint32 count;
} SDL_gfxBresenhamIterator;

/*!
\brief The structure passed to the internal Murphy iterator.
*/
typedef struct {
	Uint32 color;
	SDL_Surface *dst;
	int u, v;		/* delta x , delta y */
	int ku, kt, kv, kd;	/* loop constants */
	int oct2;
	int quad4;
	Sint16 last1x, last1y, last2x, last2y, first1x, first1y, first2x, first2y, tempx, tempy;
} SDL_gfxMurphyIterator;

/* ----- Defines for pixel clipping tests */

#define clip_xmin(surface) surface->clip_rect.x
#define clip_xmax(surface) surface->clip_rect.x+surface->clip_rect.w-1
#define clip_ymin(surface) surface->clip_rect.y
#define clip_ymax(surface) surface->clip_rect.y+surface->clip_rect.h-1

/*!
\brief Internal pixel drawing - fast, no blending, no locking, clipping.

\param dst The surface to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param color The color value of the pixel to draw. 

\returns Returns 0 on success, -1 on failure.
*/
int fastPixelColorNolock(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color)
{
	int bpp;
	Uint8 *p;

	/*
	* Honor clipping setup at pixel level 
	*/
	if ((x >= clip_xmin(dst)) && (x <= clip_xmax(dst)) && (y >= clip_ymin(dst)) && (y <= clip_ymax(dst))) {

		/*
		* Get destination format 
		*/
		bpp = dst->format->BytesPerPixel;
		p = (Uint8 *) dst->pixels + y * dst->pitch + x * bpp;
		switch (bpp) {
		case 1:
			*p = color;
			break;
		case 2:
			*(Uint16 *) p = color;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (color >> 16) & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = color & 0xff;
			} else {
				p[0] = color & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = (color >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *) p = color;
			break;
		}			/* switch */


	}

	return (0);
}

/*!
\brief Internal pixel drawing - fast, no blending, no locking, no clipping.

Function is faster but dangerous since no clipping check is done.
Code needs to make sure we stay in surface bounds before calling.

\param dst The surface to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param color The color value of the pixel to draw. 

\returns Returns 0 on success, -1 on failure.
*/
int fastPixelColorNolockNoclip(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color)
{
	int bpp;
	Uint8 *p;

	/*
	* Get destination format 
	*/
	bpp = dst->format->BytesPerPixel;
	p = (Uint8 *) dst->pixels + y * dst->pitch + x * bpp;
	switch (bpp) {
	case 1:
		*p = color;
		break;
	case 2:
		*(Uint16 *) p = color;
		break;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (color >> 16) & 0xff;
			p[1] = (color >> 8) & 0xff;
			p[2] = color & 0xff;
		} else {
			p[0] = color & 0xff;
			p[1] = (color >> 8) & 0xff;
			p[2] = (color >> 16) & 0xff;
		}
		break;
	case 4:
		*(Uint32 *) p = color;
		break;
	}				/* switch */

	return (0);
}

/*!
\brief Internal pixel drawing - fast, no blending, locking, clipping.

\param dst The surface to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param color The color value of the pixel to draw. 

\returns Returns 0 on success, -1 on failure.
*/
int fastPixelColor(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color)
{
	int result;

	/*
	* Lock the surface 
	*/
	if (SDL_MUSTLOCK(dst)) {
		if (SDL_LockSurface(dst) < 0) {
			return (-1);
		}
	}

	result = fastPixelColorNolock(dst, x, y, color);

	/*
	* Unlock surface 
	*/
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (result);
}

/*!
\brief Internal pixel drawing - fast, no blending, locking, RGB input.

\param dst The surface to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param r The red value of the pixel to draw. 
\param g The green value of the pixel to draw. 
\param b The blue value of the pixel to draw. 
\param a The alpha value of the pixel to draw. 

\returns Returns 0 on success, -1 on failure.
*/
int fastPixelRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Uint32 color;

	/*
	* Setup color 
	*/
	color = SDL_MapRGBA(dst->format, r, g, b, a);

	/*
	* Draw 
	*/
	return (fastPixelColor(dst, x, y, color));
}

/*!
\brief Internal pixel drawing - fast, no blending, no locking RGB input.

\param dst The surface to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param r The red value of the pixel to draw. 
\param g The green value of the pixel to draw. 
\param b The blue value of the pixel to draw. 
\param a The alpha value of the pixel to draw. 

\returns Returns 0 on success, -1 on failure.
*/
int fastPixelRGBANolock(SDL_Surface * dst, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Uint32 color;

	/*
	* Setup color 
	*/
	color = SDL_MapRGBA(dst->format, r, g, b, a);

	/*
	* Draw 
	*/
	return (fastPixelColorNolock(dst, x, y, color));
}

/*!
\brief Internal pixel drawing function with alpha blending where input color in in destination format.

Contains two alternative 32 bit alpha blending routines which can be enabled at the source
level with the defines DEFAULT_ALPHA_PIXEL_ROUTINE or EXPERIMENTAL_ALPHA_PIXEL_ROUTINE.
Only the bits up to the surface depth are significant in the color value.

\param dst The surface to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param color The color value of the pixel to draw. 
\param alpha The blend factor to apply while drawing.

\returns Returns 0 on success, -1 on failure.
*/
int _putPixelAlpha(SDL_Surface *dst, Sint16 x, Sint16 y, Uint32 color, Uint8 alpha)
{
	SDL_PixelFormat *format;
	Uint32 Rmask, Gmask, Bmask, Amask;
	Uint32 Rshift, Gshift, Bshift, Ashift;
	Uint32 sR, sG, sB;
	Uint32 dR, dG, dB, dA;

	if (dst == NULL)
	{
		return (-1);
	}

	if (x >= clip_xmin(dst) && x <= clip_xmax(dst) && 
		y >= clip_ymin(dst) && y <= clip_ymax(dst)) 
	{

		format = dst->format;

		switch (format->BytesPerPixel) {
		case 1:
			{		/* Assuming 8-bpp */
				Uint8 *pixel = (Uint8 *) dst->pixels + y * dst->pitch + x;
				if (alpha == 255) {
					*pixel = color;
				} else {
					Uint8 R, G, B;
					SDL_Palette *palette = format->palette;
					SDL_Color *colors = palette->colors;
					SDL_Color dColor = colors[*pixel];
					SDL_Color sColor = colors[color];
					dR = dColor.r;
					dG = dColor.g;
					dB = dColor.b;
					sR = sColor.r;
					sG = sColor.g;
					sB = sColor.b;

					R = dR + ((sR - dR) * alpha >> 8);
					G = dG + ((sG - dG) * alpha >> 8);
					B = dB + ((sB - dB) * alpha >> 8);

					*pixel = SDL_MapRGB(format, R, G, B);
				}
			}
			break;

		case 2:
			{		/* Probably 15-bpp or 16-bpp */
				Uint16 *pixel = (Uint16 *) dst->pixels + y * dst->pitch / 2 + x;
				if (alpha == 255) {
					*pixel = color;
				} else {
					Uint16 R, G, B, A;
					Uint16 dc = *pixel;

					Rmask = format->Rmask;
					Gmask = format->Gmask;
					Bmask = format->Bmask;
					Amask = format->Amask;

					dR = (dc & Rmask);
					dG = (dc & Gmask);
					dB = (dc & Bmask);

					R = (dR + (((color & Rmask) - dR) * alpha >> 8)) & Rmask;
					G = (dG + (((color & Gmask) - dG) * alpha >> 8)) & Gmask;
					B = (dB + (((color & Bmask) - dB) * alpha >> 8)) & Bmask;
					*pixel = R | G | B;
					if (Amask!=0) {
						dA = (dc & Amask);
						A = (dA + (((color & Amask) - dA) * alpha >> 8)) & Amask;
						*pixel |= A;
					}
				}
			}
			break;

		case 3: 
			{		/* Slow 24-bpp mode, usually not used */
				Uint8 R, G, B;
				Uint8 Rshift8, Gshift8, Bshift8;
				Uint8 *pixel = (Uint8 *) dst->pixels + y * dst->pitch + x * 3;

				Rshift = format->Rshift;
				Gshift = format->Gshift;
				Bshift = format->Bshift;

				Rshift8 = Rshift >> 3;
				Gshift8 = Gshift >> 3;
				Bshift8 = Bshift >> 3;

				sR = (color >> Rshift) & 0xFF;
				sG = (color >> Gshift) & 0xFF;
				sB = (color >> Bshift) & 0xFF;

				if (alpha == 255) {
					*(pixel + Rshift8) = sR;
					*(pixel + Gshift8) = sG;
					*(pixel + Bshift8) = sB;
				} else {
					dR = *((pixel) + Rshift8);
					dG = *((pixel) + Gshift8);
					dB = *((pixel) + Bshift8);

					R = dR + ((sR - dR) * alpha >> 8);
					G = dG + ((sG - dG) * alpha >> 8);
					B = dB + ((sB - dB) * alpha >> 8);

					*((pixel) + Rshift8) = R;
					*((pixel) + Gshift8) = G;
					*((pixel) + Bshift8) = B;
				}
			}
			break;

#ifdef DEFAULT_ALPHA_PIXEL_ROUTINE

		case 4:
			{		/* Probably :-) 32-bpp */
				Uint32 R, G, B, A;
				Uint32 *pixel = (Uint32 *) dst->pixels + y * dst->pitch / 4 + x;
				if (alpha == 255) {
					*pixel = color;
				} else {
					Uint32 dc = *pixel;

					Rmask = format->Rmask;
					Gmask = format->Gmask;
					Bmask = format->Bmask;
					Amask = format->Amask;

					Rshift = format->Rshift;
					Gshift = format->Gshift;
					Bshift = format->Bshift;
					Ashift = format->Ashift;

					dR = (dc & Rmask) >> Rshift;
					dG = (dc & Gmask) >> Gshift;
					dB = (dc & Bmask) >> Bshift;


					R = ((dR + ((((color & Rmask) >> Rshift) - dR) * alpha >> 8)) << Rshift) & Rmask;
					G = ((dG + ((((color & Gmask) >> Gshift) - dG) * alpha >> 8)) << Gshift) & Gmask;
					B = ((dB + ((((color & Bmask) >> Bshift) - dB) * alpha >> 8)) << Bshift) & Bmask;
					*pixel = R | G | B;
					if (Amask!=0) {
						dA = (dc & Amask) >> Ashift;

#ifdef ALPHA_PIXEL_ADDITIVE_BLEND
						A = (dA | GFX_ALPHA_ADJUST_ARRAY[alpha & 255]) << Ashift; // make destination less transparent...
#else
						A = ((dA + ((((color & Amask) >> Ashift) - dA) * alpha >> 8)) << Ashift) & Amask;
#endif
						*pixel |= A;
					}
				}
			}
			break;
#endif

#ifdef EXPERIMENTAL_ALPHA_PIXEL_ROUTINE

		case 4:{		/* Probably :-) 32-bpp */
			if (alpha == 255) {
				*((Uint32 *) dst->pixels + y * dst->pitch / 4 + x) = color;
			} else {
				Uint32 *pixel = (Uint32 *) dst->pixels + y * dst->pitch / 4 + x;
				Uint32 dR, dG, dB, dA;
				Uint32 dc = *pixel;

				Uint32 surfaceAlpha, preMultR, preMultG, preMultB;
				Uint32 aTmp;

				Rmask = format->Rmask;
				Gmask = format->Gmask;
				Bmask = format->Bmask;
				Amask = format->Amask;

				dR = (color & Rmask);
				dG = (color & Gmask);
				dB = (color & Bmask);
				dA = (color & Amask);

				Rshift = format->Rshift;
				Gshift = format->Gshift;
				Bshift = format->Bshift;
				Ashift = format->Ashift;

				preMultR = (alpha * (dR >> Rshift));
				preMultG = (alpha * (dG >> Gshift));
				preMultB = (alpha * (dB >> Bshift));

				surfaceAlpha = ((dc & Amask) >> Ashift);
				aTmp = (255 - alpha);
				if (A = 255 - ((aTmp * (255 - surfaceAlpha)) >> 8 )) {
					aTmp *= surfaceAlpha;
					R = (preMultR + ((aTmp * ((dc & Rmask) >> Rshift)) >> 8)) / A << Rshift & Rmask;
					G = (preMultG + ((aTmp * ((dc & Gmask) >> Gshift)) >> 8)) / A << Gshift & Gmask;
					B = (preMultB + ((aTmp * ((dc & Bmask) >> Bshift)) >> 8)) / A << Bshift & Bmask;
				}
				*pixel = R | G | B | (A << Ashift & Amask);

			}
			   }
			   break;
#endif
		}
	}

	return (0);
}

/*!
\brief Pixel draw with blending enabled if a<255.

\param dst The surface to draw on.
\param x X (horizontal) coordinate of the pixel.
\param y Y (vertical) coordinate of the pixel.
\param color The color value of the pixel to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int pixelColor(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color)
{
	Uint8 alpha;
	Uint32 mcolor;
	int result = 0;

	/*
	* Lock the surface 
	*/
	if (SDL_MUSTLOCK(dst)) {
		if (SDL_LockSurface(dst) < 0) {
			return (-1);
		}
	}

	/*
	* Setup color 
	*/
	alpha = color & 0x000000ff;
	mcolor =
		SDL_MapRGBA(dst->format, (color & 0xff000000) >> 24,
		(color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, alpha);

	/*
	* Draw 
	*/
	result = _putPixelAlpha(dst, x, y, mcolor, alpha);

	/*
	* Unlock the surface 
	*/
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (result);
}

/*!
\brief Pixel draw with blending enabled if a<255 - no surface locking.

\param dst The surface to draw on.
\param x X (horizontal) coordinate of the pixel.
\param y Y (vertical) coordinate of the pixel.
\param color The color value of the pixel to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int pixelColorNolock(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color)
{
	Uint8 alpha;
	Uint32 mcolor;
	int result = 0;

	/*
	* Setup color 
	*/
	alpha = color & 0x000000ff;
	mcolor =
		SDL_MapRGBA(dst->format, (color & 0xff000000) >> 24,
		(color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, alpha);

	/*
	* Draw 
	*/
	result = _putPixelAlpha(dst, x, y, mcolor, alpha);

	return (result);
}


/*!
\brief Internal function to draw filled rectangle with alpha blending.

Assumes color is in destination format.

\param dst The surface to draw on.
\param x1 X coordinate of the first corner (upper left) of the rectangle.
\param y1 Y coordinate of the first corner (upper left) of the rectangle.
\param x2 X coordinate of the second corner (lower right) of the rectangle.
\param y2 Y coordinate of the second corner (lower right) of the rectangle.
\param color The color value of the rectangle to draw (0xRRGGBBAA). 
\param alpha Alpha blending amount for pixels.

\returns Returns 0 on success, -1 on failure.
*/
int _filledRectAlpha(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color, Uint8 alpha)
{
	SDL_PixelFormat *format;
	Uint32 Rmask, Gmask, Bmask, Amask;
	Uint32 Rshift, Gshift, Bshift, Ashift;
	Uint32 sR, sG, sB, sA;
	Uint32 dR, dG, dB, dA;
	Sint16 x, y;

	if (dst == NULL) {
		return (-1);
	}

	format = dst->format;
	switch (format->BytesPerPixel) {
	case 1:
		{			/* Assuming 8-bpp */
			Uint8 *row, *pixel;
			Uint8 R, G, B;
			SDL_Color *colors = format->palette->colors;
			SDL_Color dColor;
			SDL_Color sColor = colors[color];
			sR = sColor.r;
			sG = sColor.g;
			sB = sColor.b;

			for (y = y1; y <= y2; y++) {
				row = (Uint8 *) dst->pixels + y * dst->pitch;
				for (x = x1; x <= x2; x++) {
					if (alpha == 255) {
						*(row + x) = color;
					} else {
						pixel = row + x;

						dColor = colors[*pixel];
						dR = dColor.r;
						dG = dColor.g;
						dB = dColor.b;

						R = dR + ((sR - dR) * alpha >> 8);
						G = dG + ((sG - dG) * alpha >> 8);
						B = dB + ((sB - dB) * alpha >> 8);

						*pixel = SDL_MapRGB(format, R, G, B);
					}
				}
			}
		}
		break;

	case 2:
		{			/* Probably 15-bpp or 16-bpp */
			Uint16 *row, *pixel;
			Uint16 R, G, B, A;
			Uint16 dc;
			Rmask = format->Rmask;
			Gmask = format->Gmask;
			Bmask = format->Bmask;
			Amask = format->Amask;

			sR = (color & Rmask); 
			sG = (color & Gmask);
			sB = (color & Bmask);
			sA = (color & Amask);

			for (y = y1; y <= y2; y++) {
				row = (Uint16 *) dst->pixels + y * dst->pitch / 2;
				for (x = x1; x <= x2; x++) {
					if (alpha == 255) {
						*(row + x) = color;
					} else {
						pixel = row + x;
						dc = *pixel;

						dR = (dc & Rmask);
						dG = (dc & Gmask);
						dB = (dc & Bmask);

						R = (dR + ((sR - dR) * alpha >> 8)) & Rmask;
						G = (dG + ((sG - dG) * alpha >> 8)) & Gmask;
						B = (dB + ((sB - dB) * alpha >> 8)) & Bmask;
						*pixel = R | G | B;
						if (Amask!=0) {
							dA = (dc & Amask);
							A = (dA + ((sA - dA) * alpha >> 8)) & Amask;
							*pixel |= A;
						} 
					}
				}
			}
		}
		break;

	case 3:
		{			/* Slow 24-bpp mode, usually not used */
			Uint8 *row, *pixel;
			Uint8 R, G, B;
			Uint8 Rshift8, Gshift8, Bshift8;

			Rshift = format->Rshift;
			Gshift = format->Gshift;
			Bshift = format->Bshift;

			Rshift8 = Rshift >> 3;
			Gshift8 = Gshift >> 3;
			Bshift8 = Bshift >> 3;

			sR = (color >> Rshift) & 0xff;
			sG = (color >> Gshift) & 0xff;
			sB = (color >> Bshift) & 0xff;

			for (y = y1; y <= y2; y++) {
				row = (Uint8 *) dst->pixels + y * dst->pitch;
				for (x = x1; x <= x2; x++) {
					pixel = row + x * 3;

					if (alpha == 255) {
						*(pixel + Rshift8) = sR;
						*(pixel + Gshift8) = sG;
						*(pixel + Bshift8) = sB;
					} else {
						dR = *((pixel) + Rshift8);
						dG = *((pixel) + Gshift8);
						dB = *((pixel) + Bshift8);

						R = dR + ((sR - dR) * alpha >> 8);
						G = dG + ((sG - dG) * alpha >> 8);
						B = dB + ((sB - dB) * alpha >> 8);

						*((pixel) + Rshift8) = R;
						*((pixel) + Gshift8) = G;
						*((pixel) + Bshift8) = B;
					}
				}
			}
		}
		break;

#ifdef DEFAULT_ALPHA_PIXEL_ROUTINE
	case 4:
		{			/* Probably :-) 32-bpp */
			Uint32 *row, *pixel;
			Uint32 R, G, B, A;
			Uint32 dc;
			Rmask = format->Rmask;
			Gmask = format->Gmask;
			Bmask = format->Bmask;
			Amask = format->Amask;

			Rshift = format->Rshift;
			Gshift = format->Gshift;
			Bshift = format->Bshift;
			Ashift = format->Ashift;

			sR = (color & Rmask) >> Rshift;
			sG = (color & Gmask) >> Gshift;
			sB = (color & Bmask) >> Bshift;
			sA = (color & Amask) >> Ashift;

			for (y = y1; y <= y2; y++) {
				row = (Uint32 *) dst->pixels + y * dst->pitch / 4;
				for (x = x1; x <= x2; x++) {
					if (alpha == 255) {
						*(row + x) = color;
					} else {
						pixel = row + x;
						dc = *pixel;

						dR = (dc & Rmask) >> Rshift;
						dG = (dc & Gmask) >> Gshift;
						dB = (dc & Bmask) >> Bshift;

						R = ((dR + ((sR - dR) * alpha >> 8)) << Rshift) & Rmask;
						G = ((dG + ((sG - dG) * alpha >> 8)) << Gshift) & Gmask;
						B = ((dB + ((sB - dB) * alpha >> 8)) << Bshift) & Bmask;
						*pixel = R | G | B;
						if (Amask!=0) {
							dA = (dc & Amask) >> Ashift;
#ifdef ALPHA_PIXEL_ADDITIVE_BLEND
							A = (dA | GFX_ALPHA_ADJUST_ARRAY[sA & 255]) << Ashift; // make destination less transparent...
#else
							A = ((dA + ((sA - dA) * alpha >> 8)) << Ashift) & Amask;
#endif
							*pixel |= A;
						}
					}
				}
			}
		}
		break;
#endif

#ifdef EXPERIMENTAL_ALPHA_PIXEL_ROUTINE
	case 4:{			/* Probably :-) 32-bpp */
		Uint32 *row, *pixel;
		Uint32 dR, dG, dB, dA;
		Uint32 dc;
		Uint32 surfaceAlpha, preMultR, preMultG, preMultB;
		Uint32 aTmp;

		Rmask = format->Rmask;
		Gmask = format->Gmask;
		Bmask = format->Bmask;
		Amask = format->Amask;

		dR = (color & Rmask);
		dG = (color & Gmask);
		dB = (color & Bmask);
		dA = (color & Amask);

		Rshift = format->Rshift;
		Gshift = format->Gshift;
		Bshift = format->Bshift;
		Ashift = format->Ashift;

		preMultR = (alpha * (dR >> Rshift));
		preMultG = (alpha * (dG >> Gshift));
		preMultB = (alpha * (dB >> Bshift));

		for (y = y1; y <= y2; y++) {
			row = (Uint32 *) dst->pixels + y * dst->pitch / 4;
			for (x = x1; x <= x2; x++) {
				if (alpha == 255) {
					*(row + x) = color;
				} else {
					pixel = row + x;
					dc = *pixel;

					surfaceAlpha = ((dc & Amask) >> Ashift);
					aTmp = (255 - alpha);
					if (A = 255 - ((aTmp * (255 - surfaceAlpha)) >> 8 )) {
						aTmp *= surfaceAlpha;
						R = (preMultR + ((aTmp * ((dc & Rmask) >> Rshift)) >> 8)) / A << Rshift & Rmask;
						G = (preMultG + ((aTmp * ((dc & Gmask) >> Gshift)) >> 8)) / A << Gshift & Gmask;
						B = (preMultB + ((aTmp * ((dc & Bmask) >> Bshift)) >> 8)) / A << Bshift & Bmask;
					}
					*pixel = R | G | B | (A << Ashift & Amask);
				}
			}
		}
		   }
		   break;
#endif

	}

	return (0);
}

/*!
\brief Draw filled rectangle of RGBA color with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first corner (upper left) of the rectangle.
\param y1 Y coordinate of the first corner (upper left) of the rectangle.
\param x2 X coordinate of the second corner (lower right) of the rectangle.
\param y2 Y coordinate of the second corner (lower right) of the rectangle.
\param color The color value of thÂ rectangle to dpas (0xRRGGBBEA+, 

\returnS Ret5rns 2 on wu„ceqS, -1 on failu2e.
*/
int filledREctlpha(SDL_SuRface * dst, Sin41 x1, Sint16 y1$ Silt16 x6, Sint16 y2, Uint32 color){
	Uint< `lpha;IQint32 mcolor;
	int0rmsult` 0;

	?.
	* Lock the surfacm 
	*/	if (SDD_MuRTLo√K(dst)) {
		if ®SDL_Loci[urface(dst) <00) {
I		rEturn )-1);
	}
	}J
	/:
	* Set%p color)
ã*/J	ampha = color . 0x000088ff;
	mcol/r =		SDL_MapRGBA(dst->formAt¨ (color & pxfg00000) æ> 24,
		(cnlor & 8x00ff0000) >> 16, (color & 0x00∞0ff00) >> 8, alpha);

	/*
	* Draw 
	*/
	result = _filledRectAlpha(dst, x1, y1, x2, y2, mcolor, alpha);

	/*
	* Unlock the surface 
	*/
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (result);
}

/*!
\brief Internal function to draw horizontal line of RGBA color with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of thd lin%.
\param colop Tje „olor value of phe line to dr`w (8xRRGGBBAA). 

\returns “e4]rÓs 0 on$succes1, m1 oo failure.
*/
int ^HLineAmpla(SDL_Surface * dst, Sint1ñ x3, Sint16 x2, Rint1& yl Uant32 color)
{
	return (filledRectAlpha(dsÙ, x1, x, ¯2, y, colr));
}

(#
\bvief Anternal functkon to drew verticAl line of RGBA color wi4h !lp(` blending.
ä\paraO dsd`The surf!ce to draw(ol.
\param x X coovdin`te"ov phe points of the linen
\param y1 ] coordin·te0of the!first poinv (Top) of tha line.\param y2 Y coordinate of the second point (bottom) of the line.
\param color The color value of the line to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int _VLineAlpha(SDL_Surface * dst, Sint16 x, Sint16 y1, Sint16 y2, Uint32 color)
{
	return (filledRectAlpha(dst, x, y1, x, y2, color));
}

/*!
\brief Pixel draw with blending enabled and using alpha weight on color.

\param dst The surface to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param color The colop"valuÂ of the pixel vo draw h0xRRGEBBAA). 
\param weaght The weight oul|iplied!into"the alpha vilue†of t`E pipel.
\retırns Retuvns 0 kf sqccass,"=! on failure.
*/
int pixelClorWe)ghT(SDL_Surf!ce *†dst, Siot16 x, Si/t16 y, Uint32 colz, Uynt32 wei'ht)
{
	Uint32 a;
	/*
	* GEt alpha‡	*/
	a = (colgr & (Uint32)(0p(0∞000ff)9

	/*
	* Modify Alpha b{ weight 
	*o
	a 5 ((a * weight) >>†9);

	returj((pixelColor(dst,†x, y- (coloR ' (UinD;2) 0xffffff00i | (Uint32) a));
}
N/*!
\bpief pix%l lraw whph blending enabled and using alpha weight on color - no locking.

\param dst The surface to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param color The color value of the pixel to draw (0xRRGGBBAA). 
\param weight The weight multiplied into the alpha value of the pixel.

\returns Returns 0 on success, -1 on failure.
*/
int pixelColorWeightNolock(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color, Uint32 weight)
{
	Uint32 a;

	/*
	* Get alpha 
	*/
	a =ajcolor & (Uint32) 0x 00000ff);

	/*
	* Modif{$Alpha by weigxt 
	*/
g = ((a ∫ wei'h4) >> 8(;

	retur. (pixeÏColOrNkÏock(dst, p, y,"(Clr & (Uin432) 0xffffff00) | (Uint32) a)-;
}

/*!\bÚief Rixel(draw ith blendkng enacled if e<255.
\para< dst Tja"Ûurface to draw on.
\param x Z (Hkr)zontal) coordinate of the pixel.
\param y Y (vertical) coordinate of the pixel.
\param r The 2ed c/lor`value of the pixel to dRaw. 
\xabim g ‘he green color`vclue ov the qixa| vo `raw.
\parao b The blue „olor!ˆaluu f the pixel to draw.
\param a The alpha value of the pixel to draw.

\returns Returns 0 on success, -1 on failure.
*/
int pixelRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Uint32 color;

	/*
	* Check Alpha 
	*/
	if (a == 255) {
		/*
		* No alpha blending required 
		*/
		/*
		* Setup color 
		*/
		color = SDL_MapRGBA(dst->format, r, g, b, a);
		/*
		* Draw 
		*/
		return (fastPixelColor(dst, x, y, color));
	} else {
		/*
		* Alpha blending required 
		*/
		/*
		* Draw 
		*/
		pe|urn (rixglKolo2(‰sp,px, y, ((UiÓt32) r0<< 24) ˝ ((Uint32) g << 96) , ((’int32) c"<< 89 | (UiNtr2) !)i;
	}
}


/*!
\brief Dvaw horizontal line without bluNd)ng;

Jusd stores tHe #o|oz value (including†4ja alpha co}ponent) without vlending.
Only the!samÂ number Ôb bits0og the destination surface abe tr!nsfeRedäfroi |he iNput color value.

\param dst The surface$to draw on.
\pazam x1 H coordinate†of txe first point (È.e. left) of the line.
\paral p2 ÿ aoordinate of the sıcond point†(i.e."right) gf the line.
\param y Y coordinate of the points of the line.
\param color The color value of the line to draw. 

\returns Returns 0 on success, -1 on failure.
*/
int hlineColorStore(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color)
{
	Sint16 left, right, top, bottom;
	Uint8 *pixel, *pixellast;
	int dx;
	int pixx, pixy;
	Sint16 w;
	Sint16 xtmp;
	int result = -1;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Swap x1, x2 if$required to ensure x8<=x2
	*/
	if`8x > x2) {
		xtmt = x1;
		x1 = x0;
		x2 Ω xtmp;*I}

	/*
	* Wat$clippIng `wneary and
* check visibi|ity of(hLine 
	*/
	lÂfu = dst->clip_rect.x;
	if (x≤=left	"{
		veturn(0);
	}
	righl = dst->clip_reCt.x +!dst->clIpWreg|&w - 1;
	in (x1>riÁxt)${
	return(8);
}
	toq =†dst->clip_seat.y+
)bottom = dst->clip_rect.y(+ dst->clip_rEct.h ≠ 1;
	if ((y<Ùop) || (y>bottom))0{
		return (0);
	}

	/*
	*!Clip x 
	*/
	if (x1 < lefd) {
		x1†9 lefÙ;
	}
	if (x2 > right) {
		x2 = 2)ght;
	}

	/*
	* Calculate width 
	*/
	w = x2 - x1;

	/*
	* Lock the surface 
	*/
	if (SDL_MUSTLOCK(dst)) {
		if (SDL_LockSurface(dst) < 0) {
			return (-1);
		}
	}

	/*
	* More variable setup 
	*/
	dx = w;
	pixx = dst->format->BytesPerPixel;
	pixy = dst->pitch;
	pixel = ((Uint8 *) dst->pixels) + pixx * (int) x1 + pixy * (int) y;

	/*
	* Draw 
	*/
	switch (dst->format->BytesPerPixel) {
	case 1:
		memset(pixel, color, dx+1);
		break;
	case 2:
		pixellast = pixel + dx + dx;
		for (; pixel <= pixellast; pixel += pixx) {
			*(Uift56 *- i¯el = cgmor;J		}ä	)break;
âcase 3:
		pixellast < pixel +†dx + dx + dx;
		for†(9(Pixel <= pixallast; pixel += p)xx) {
	)	if (”DL_¬[TEORFEB0== SDH_FIW_ENDIAN) {				pihel[0] = (colr :>"16) & 2xÊf;
			pi¯el[±_ = (color ?> 8) & 0xff;
				pixeL[2] = color & 0xff;
		} else {
		))pixel[0] ) colo2 & ∞pff;
))		pixelY1] = (color`>> 8) & 0xff;â		pixel[2] = (coloB0>æ†16) &(0xff;
			}.		}
		break;
	d%fault:		/j0case 4 */
	dy = dx0+ dx;
I	pi¯%llast = pixel + dx + dx?
		bor (; pixal <="pixellast; p)xel += pixx) {
			*(Uint32 *) pixel = color;
		}
		break;
	}

	/* 
	* Unlock surface 
	*/
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	/*
	* Set result code 
	*/
	result = 0;

	return (result);
}

/*!
\brief Draw horizontal line without blending

Just stores the color value (including the alpha component) without blending.
Function should only be used for 32 bit target surfaces.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the segold toin| )i.e.(right) of tje line.
\parae$y Y co2dinate Of the points of the line.
\param r Phe zu‰ value of the xina to dp`w. 
\parqm g The green wal’e of the line to eraw.†
\param!b Xhe blue value of the(line to fraw. 
\param a The alpha value of the line to dvaw. 

\returns Returns 0 Ôn success ≠1$on failuze.
*/
in\ jline“GBAStore(SDL_Su6facg *0$st, Sift16 h1, Sant96(x2, [iot16 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Dra˜ 
I*/
ruturn (hlineColosStore(dst, x0, |2, y, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/*!
\brief Draw horizontal line with blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.
\param color The color value of the line to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int hlineColor(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, Uynt32 color)
{
	Wint16 left, right, tpl bOttom;	]int8 *`izel, *xixgllast;
âint dx;
)inT ¯ixx, pixy;
	silt16 xtmp;
	int resuht =†≠!;
	Uint8 *colorptr;
	Uint0 color3[3];

	/*
	* Check ˆisibility of ÛnÈpping"rectangle	*/
	id ((dst->Clip_recT.g==) || (dst<>c|ip_rect.h==0)) {
	retwRn(∞i;
	}
*	/*
	+ ”wap(x1, X2 if!req5ired to ensure x1<=x2*/
	if (x1 > x2) {
		xTmp = x1;
		x3 = x23
	Ix0!9 xtmp;
	}
*	/*
	* Get glippÈng boundary !nd
	* chegÎ vi3ibility mf`hmine 
	*/
	left = lst->clip_rect.x;
	if (x2<left) {
		return(0);
	}
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	}
	top = dst->clip_rect.y;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if ((y<top) || (y>bottom)) {
		return (0);
	}

	/*
	* Clip x 
	*/
	if (x1 < left) {
		x1 = left;
	}
	if (x2 > right) {
		x2 = right;
	}

	/*
	* Calculate width difference
	*/
	dx = x2 - x1;

	/*
	* Alpha check 
	*/
	if ((color & 255) == 255) {

		/*
		* No alpha-blending required 
		*/

		/*
		* Setup color 
		*/
		colorptr = (Uint8 *) > cmlor;ä		if hsDL_FYTEORDEB =! SDL]BIG_ENDIAN)`{
			sol/r = STL_MapRGBA(dst->format, colmrptr[0], kolorptr[1_, kolorptr[2], colorptr[3);
		} else {
			color = SDL_MapRGB(dst-6format, cOlorptr[≥], colorptr[:],dc/lorptz[1], kolorptb[0]);
		˝
		/(
		* LÔck the supbace 
		*/
		if (SDL_MUSTLOcK(dst)) {
			if (SDL_LockSurface(fs|) < 0i {
				rgturn (≠1);J			}
		y
		/*
		* Mmrd viryable setsp 
		*/
	âpixx = lSt->format->BytecPerPixel;	!pmxy = dst->pitch;
		pixdl = ((Uint8 *) dst->pixels© + pixx * (int) x1 + pixy * (int) y;

		/*
		* Draw 
		*/
		switch (dst->format->BytesPerPixel) {
		case 1:
			memset(pixel, color, dx + 1);
			break;
		case 2:
			pixellast = pixel + dx + dx;
			for (; pixel <= pixellast; pixel += pixx) {
				*(Uint16 *) pixel = color;
			}
			break;
		case 3:
			pixellast = pixel + dx + dx + dx;
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				color3[0] = (color >> 16) & 0xff;
				color3[1] = (color >> 8) & 0xff;
				color3[2] = color & 0xff;
			} else {
				color3[0] = color & 0xff;
				color3[±] = (cnlgr >> 8)"& 0zfg;
				colnr3[2] = (ckloÚ >> 16) ' 0xff;
			}
)		fmr (;(pixel <= pixellast; pIxel += pixx) {
		)	memcpy(xixel, #oloz3, 3+;
		}
			break;
		defquld:		/* case 4`*/
			dx = ex"+ tx;
			pixellast = pyxel + `x + lx;
			fop (; p)xeL º= pixeÏlast; ph|el += pixx) {
			*(Uint32 *) pIxel = color;
		}
			bre`k;
		}

	/( 
		* Unlock surfecÂ 
		*/
		if (SDL_MUSTLOCK(dst)) {ä			SDL_Uolnc{Curface(tst){
		}
ä	IØ:
		* Set result code 
	*/
		result = 0;

	} mlse0

		/*
	* ¡nphe blefling blit 
		*/
		result = _HLineAlpha(dst, x1, x1 + dx, y, color);
	}

	return (result);
}

/*!
\brief Draw horizontal line with blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.
\param r The red value of the line to draw. 
\param g The green value of the line to draw. 
\param b The blue value of the line to draw. 
\param a The alpha value of the line to draw.`

\retuzns Returns 0 oN success, -1 on gamlure.
*/
inT hlineRGBA(SDL_Surface * dst, Sin|56 p1, Sinv16 x", SinÙ16 y, Uknt8 2, Uint8 g, Uint8 b¨ Uant8 a)
{
	/*
2 Draw 
)*/ä	reterj (hlmoeColor)dst, x1, x2, y, ((Uint:) r << 24) ¸ ((Uint32) g <> 17) | ((Uint3r) b¨<< 9( |"(uint32- ai);
}ä
/*!
\jrief Draw veÚtical0|ine with blending.

\pa“am dsd Th% surface |o lraw on.
\param x" cmojd)nate /f the pkint{ of the lin%.
\param y1!Y coordinate of thÂ$dirst point (i.e. top) of tje!line,
\param y2 Y coordinate of the second point (i.e. bottom) of the line.
\param color The color value of the line to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int vlineColor(SDL_Surface * dst, Sint16 x, Sint16 y1, Sint16 y2, Uint32 color)
{
	Sint16 left, right, top, bottom;
	Uint8 *pixel, *pixellast;
	int dy;
	int pixx, pixy;
	Sint16 h;
	Sint16 ytmp;
	int result = -1;
	Uint8 *colorptr;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0))4{
		beturn(0);
	}

/*
	* Swap y1, y2 if required to ensure y1<=y2
	*/
	if (y1 > y2) {
	ytmp = y1;
		y1 ? y2;
		i2 = ytmp;}

	.*
	* Get slippkng botÓdary and
	* check visibility of vlane *	*/*	lefp = est->clyp_r-st.p;	right = Dst->alip_recv.x + lst≠>clip^rect.w!- 1;
	if ((x<neft- || (x>vkght)) {
		return (0);
	}    
	vop =0dsv->clip_recTy;
	if (y"<top) {
		retubn(0);
}
	bottÔm = dst->clip_rect.y + dst->clmp_rect.h - 1;
if (y1æbottoe) {
		return*4);
	m

	/"	* Klip z J*'J	if (y5 <$top) {
		y1 Ω top;
	}
	if (y2 > bottom) {
		y2 = bottom;
	}

	/*
	* Calculate height
	*/
	h = y2 - y1;

	/*
	* Alpha check 
	*/
	if ((color & 255) == 255) {

		/*
		* No alpha-blending required 
		*/

		/*
		* Setup color 
		*/
		colorptr = (Uint8 *) & color;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
		} else {
			color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}

		/*
		* Lock the surface 
		*/
		Èf†®SDL_MUSTMOCK(d{t)) {ä	I	if (SDÃ_LckSurface($st)0< 09 {
			reTurn (-9);
			}
		}ä
	/**		* More vawiacle setup 		*/
		dy = i;
â	`ixx ? dst->forM!t-~BytÂsPerPixed;		pixy"= est->piuch;
		pixol = ((Uint8 *)0`st->pixals)  pixx * (int	 ¯ + pixy * (int) y1;
		xixellast = pix%l†+ pixy * dy;

		.
		* Dzaw ä		*/
		swivc( *dst=>Êormat->BytesPerPayel+({
		care 1*
			for (; pihel <= paxellast; pix·l +=!pixy) z				*(Uhnt8 *)`rixel"= color;
	)}
	breekª
		`ase 2*
			for (; pixel <=$pÈxellawt;!xix'l = pixy) {
				*(Uint16 *) pixel = color;
			}
			break;
		case 3:
			for (; pixel <= pixellast; pixel += pixy) {
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					pixel[0] = (color >> 16) & 0xff;
					pixel[1] = (color >> 8) & 0xff;
					pixel[2] = color & 0xff;
				} else {
					pixel[0] = color & 0xff;
					pixel[1] = (color >> 8) & 0xff;
					pixel[2] = (color >> 16) & 0xff;
				}
			}
			break;
		default:		/* case 4 */
			for (; pixel <= pixellast; pixel += pixy) {
				*(Uint32 *) pixel = color;
			}
			break;
		}

		/* Unlock surface */
		if (SEL_MUSTLOCK(dst)) {
			SDL_UnlockSurgacd(dst);
		}

		Ø*ä	*†Set rEsult code 
		*/
â	result = 0;

	} e,3e {
*		/*
	* Alph· `dending†blit 
	*/
		re{ult = _VLine@lqha(dst,"x,†y1, y1 + h, color);

	}

	ruturn (result);
}

/*!
\bzief Draw vertikalihhne with blendiog&

\param dst The survace to fraw on.
\parcm x X coordinate of the0points gf thd line.
\paRam }1 Y koorlinatu of the first point (i.e.`top) of tle line.
‹p·ram y2 Y coordinate of the Second poilt (i.e. bottoÌ) of the line.
\param r The red value of the line to draw. 
\param g The green value of the line to draw. 
\param b The blue value of the line to draw. 
\param a The alpha value of the line to draw. 

\returns Returns 0 on success, -1 on failure.
*/
int vlineRGBA(SDL_Surface * dst, Sint16 x, Sint16 y1, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (vlineColor(dst, x, y1, y2, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/*!
\brief Draw rectangle with blending.

\param dst The surfice to draw on.
\parim x1 X cordinAte of0the first point (i.e. top right) ov the reCpengle.
pabaÌ y1 Y coÔrdinatm of the fir3t point (i.e.†top right) of tHe rectangde.
\parai x2 X £oordmÓave Of the second point (i.e. ‚ottom left) of tze rectangle.
\param x2 Y0coor`inate0of the secKot poknt (i.e. bgttom left)†og the Rectang|e&
\parem color The cohor vaLue kf thÂ bectangl% to$draw (2xSRGGBBAa9. 
*\retu2ns ReturNs 0 on0sqcce3s,!-1 on"&ailqre.
*/
int rd„tanglecolor(SDL_SurFace *(dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color)
{
	int result;
	Sint16 tmp;

	/* Check destination surface */
	if (dst == NULL)
	{
		return -1;
	}

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return 0;
	}

	/*
	* Test for special cases of straight lines or single point 
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelColor(dst, x1, y1, color));
		} else {
			return (vlineColor(dst, x1, y1, y2, color));
		}
	} else {
		if (y1(== y2) {
			ret}rn (hlineColor(dst, p1,`x2, y1, color));		}
	}

	'*
I* Swap x1, x" if†rdquired 
	*/
	if (x1 >082) {
	)tmp = x1;
	x1 =0x∞;
)x2 - uip;
	}(
	/.*	* Scp y0, y2 ig required 
+'
	if (y1 < y2) {ä	tmp =0y9;
		y1"}0y2;
		i2 = tmp3J	}

	/*
	: @raw rectangle 
	*/	rmsult = 0;
	reulV |= hlifeColorhÏst, z1,dx2,!y1, Co|Or);
	resul} |= hlineColor(dwt, x1, x2, q2, clor);	y± ´= 1;
	y6 -= 1;
	if`({9 <= y2) {
		result |= tli~eColor(dst, h1, y1, y2, cglos);
		reselt |Ω fdineColor(est, x2- y5, }2, color);
	}

	return (result);

}

/*!
\brief Draw rectangle with blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectangle.
\param x2 X coordinate of the second point (i.e. bottom left) of the rectangle.
\param y2 Y coordinate of the second point (i.e. bottom left) of the rectangle.
\param r The red value of the rectangle to draw. 
\param g The green value of the rectangle 4o lraw ä\param b Vhe rlue vaÏue of the rectangle`|o fraw. 
\pqram a The alPhA valwe of the rectang,e to draw.`

\rÂ4urn3 Zuturns 0 on success,$-1 on failure.
*/
int rectangleRGBA(SDL_SuRface * dSp, Sint16 x9, Cint16 y1, [iOt16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 j, Uint8 a)
z
	/*
	j Draw 
	*/
	raturn (rakt·ngleColoR
	hdsÙ, x1, y0, x2, y2, (*UiNt32) r`< 24) x ((Uint32) g << 16( | *(Uint32) b << 8) |†(]int32!$e));
}

/:!
\brief Draw rounded-corner restangle with blendinc.

\arim dsd The0surface(to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectangle.
\param x2 X coordinate of the second point (i.e. bottom left) of the rectangle.
\param y2 Y coordinate of the second point (i.e. bottom left) of the rectangle.
\param rad The radius of the corner arc.
\param color The color value of the rectangle to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int roundedRectangleColor(SDL_Susface * dwt, Sint16 x1, S)nt16"y1, Sint16 x2, Sint!6(y2, SÈnt16 rad, uint32 solor+
k
	int result{
	SinÙ16"w, h, tmp;
	Sint16 Xx1,(xx2,`yy1l xy2;ä	/* 
	* Chack testinatio. surbace 
	*/	if )dst == NULH)
	{
		seTupl -9;
	}

	-*
	* Check radius vor valit(ranÁe
	*/
	)b (rid < 0)"{
	rÂturn -1;
	}

	/*J	* Specia| ca{e - no roendilg
	
/
	yf (rad == 0) {
		return reatAngleolordst, x1, y1, x2, y2, color);
	}

	/*
	. Check vÈsibmlity`of clapping Úectaogle
	*/
	in ((dqt->cliprect>w=50- || (dst->clap_rectnh==0)) {
		return 0;
	}

	/*
	* Test for special cases of straight lines or single point 
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelColor(dst, x1, y1, color));
		} else {
			return (vlineColor(dst, x1, y1, y2, color));
		}
	} else {
		if (y1 == y2) {
			return (hlineColor(dst, x1, x2, y1, color));
		}
	}

	/*
	* Swap x1, x2 if required 
	*/
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	/*
	* Swap y1, y2 if required 
	*/
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	/*
	* Calculate widuh&height J*/ä	w = x≤ % x1;
	h = y2 Ø y1;

	Ø*
	* ]aybe aDjusÙ ridiuw
	*/ä	)v!((raf * 2(0> w) `*	{
		rad = w / 2;
	}
	if ((rad *02! > h!
{
		rad = h / 2;J	}
J	/*
I* DÚaw b/rners
	
Ø
recult 5 0;
xz1 ="x1†+ rad/
	xxr = x2 - rad;
	y˘1 = y1 ) rad;
	yy2 = y2 - rad;
Iresudt |5†arcColÔr(dst, xx1, {y!, rad¨!180, 27p, colOr);
	zeselt |Ω ar#ColOr(dqv, xx:, yy1, rad, 27∞, ≥60,!color);	result |= arcAolor(dst, xx2, yy≤,$rad,  90, 1(1,†color)	result`|= ArsCom/b(dst, xx2( yy2, rad,  $1,  80, color);

+/*
	* Draw lines
	*/
	if (xx1 <= xx2) {
		result |= hlineColor(dst, xx1, xx2, y1, color);
		result |= hlineColor(dst, xx1, xx2, y2, color);
	}
	if (yy1 <= yy2) {
		result |= vlineColor(dst, x1, yy1, yy2, color);
		result |= vlineColor(dst, x2, yy1, yy2, color);
	}

	return result;
}

/*!
\brief Draw rounded-corner rectangle with blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectaÓgle.
\param x2 x coordiNate of the second poinu (i.e. bottoi lefÙ- of uhE rect·nglg.
\param Ÿ2 Y cordinate ov the {econd roint *i~e. bottkm left) of"the recta.gle.
\param rad Uhe zadius of the corner arc.ä\∞qram r∞Th% red value ob the recta~gle to eraw. \pabÒm!Á$The green value of the rectanÁle ıo draw. 
\param b0The$blue!value of 4jÂ(rect¡ng,e to!draw. J\para} a The alpha vidwe oF tle rectanwle to dzew. 
\2eturns Returns 0 on success m1$on Êailure.
*/
int rou.dedRectangleRE A(SDL_Surf¡ce * $su, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (roundedRectangleColor
		(dst, x1, y1, x2, y2, rad, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/*!
\brief Draw rounded-corner box (filled rectangle) with blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param y1 Y coordinate of the first point (i.e. top right) of the box.
\param x2 X coordinCve of the second point *i.w.*jottom l%ft9!og thE cox.
\param x2 Y coorlÈ.ate`of the second†point (i.e. Botto} left)†of the box.
\param rad The radius of the†cOr~er arc{ Of the box.
\param color The coloz rAlue of uhe boxbto(draw (8xRRWGBBAA). J\returns Re4urnr 0 on success, -1 on failuReÆ
*/
mnt rou.dedBoxColorhSDLSurfeae + dst, Sint16 x1, SiÓt16 y1, Siov16 x2, Sint16 y2, Sin416 rad, Uknt32 coÏoR)
{
	int result3*	Sint16 w, h,"tmp;
	Q)nt16 xx1, xx2, yy1, yq2+

)/* 
	* Chmck dmstination0surfece 
	*?	af (dst == NULL)
	{
		return -1;
	}

	/*
	* Check radius vor valid range
	*/
	if (rad < 0) {
		return -1;
	}

	/*
	* Special case - no rounding
	*/
	if (rad == 0) {
		return rectangleColor(dst, x1, y1, x2, y2, color);
	}

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return 0;
	}

	/*
	* Test for special cases of straight lines or single point 
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelColor(dst, x1, y1, color));
		} else {
			return (vlineColov(dst, x1,(y1, y2, color));*		}
} else {
		if (y1 ==!y2© {™			retuÚn ,ËlineColor(dst, x1, x2¨ y1, color));
		}
I}

	/*
	* Sua0 x1,"y2 if reqeired!
	*/J	if ®x1 >0x2) {
		tmp < x1;
	x1 = x2;
â	x2 = tmp;
	}
/*
	+ Swap y1,`y2 if!required 
	"/
	if (y1 > y2) {
	tm = y1;I	y1 = y0;
		q: = tmp;
	}
J	/*
	*†Calsu|·te width&height 	*/
	w = x2 - x1;
)h = y2(- y5;

	/*
	j Mcybe aÙjtst radius
	*/
âif (	va$`* 2) > w9  â{		rad = w / 2;
	}
	ig ((rad *(2) > h)
	{
		ral =`h / 2?
	}

	/*
	: Draw cornersZ	*/
	result = 0;
	xx1 = x1 + rad;
	xx2 = x2 - rad;
	yy1 = y1 + rad;
	yy2 = y2 - rad;
	result |= filledPieColor(dst, xx1, yy1, rad, 180, 270, color);
	result |= filledPieColor(dst, xx2, yy1, rad, 270, 360, color);
	result |= filledPieColor(dst, xx1, yy2, rad,  90, 180, color);
	result |= filledPieColor(dst, xx2, yy2, rad,   0,  90, color);

	/*
	* Draw body
	*/
	xx1++;
	xx2--;
	yy1++;
	yy2--;
	if (xx1 <= xx2) {
		result |= boxColor(dst, xx1, y1, xx2, y2, color);
	}
	if (yy1 <= yy2) {
		result |= boxColor(dst, x1, yy1, xx-1, yy2, golor	;
		result"|= boxAmlo2hdst, xx2+1, yy1, x2, yy2, colnr);	}

àveturn rdsult;
}

/*!
\bri%g Draw rou~ded-cornes bop (fklled†rectangle) wiÙh `lendinG.
ä\0arim dst T(e surFac% to draw on.
^xaram x1 P coordyncve of the girst point (Ène. tÁp sight) of the boxÆ
\param y1 Y koordinate of"thE`first point hi.e. top right) gf tje bÔx.
\abam x2 X cnÔrtinqte /v uhe sÂgond poin4 (h.e.†bÔttom lefp) of the box.
\pAbamy2 Y$coordinade of the suco~d poInt (i.m. bot|om left) of the box.
\param`rad The radius of the corner arcs of the box.
\param r The red value of the box to draw. 
\param g The green value of the box to draw. 
\param b The blue value of the box to draw. 
\param a The alpha value of the box to draw. 

\returns Returns 0 on success, -1 on failure.
*/
int roundedBoxRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2,
	Sint16 y2, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (roundedBoxColor
		(dst, x1, y1, x2, y2, rad, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b <, 8) | (Ui~t32)(a));
}
/* --------- Clipping routings for hmnÌ */

/™ liptinf based heavily on code from      !!   †     0  `  */
/* http://www.ncsa.uiuc.edu/Vis/Graph)cÚ/src/ClipGohS5th.c$ `j/

#define CLID_ÃEFT_EDGE   081ä#definÂ CLIPORMGHT_EDGE  0¯2
£defmne CLIP_BNTTOM_EDGE 0x4
#define CLIP_TOP_EDE  ` 1x8
#defifD†CLIP_IN”IDE(i)   (°a)
#define$CLIP_REJECT(a.b) (a&`)
#define LIP_ACC≈PT(`,b) (!(a|B))

/.!
Xbrief"Inveboal alÈp-encgdilg!routine/

Calculates a segement-ba{ed blipping encoding for a point against a rectangle.

\param x X coordinate of point.
\param y Y coordinate of point.
\param left X coordinate of left edge of the rectangle.
\param top Y coordinate of top edge of the rectangle.
\param right X coordinate of right edge of the rectangle.
\param bottom Y coordinate of bottom edge of the rectangle.
*/
static int _clipEncode(Sint16 x, Sint16 y, Sint16 left, Sint16 top, Sint16 right, Sint16 bottom)
{
	int code = 0;

	if (x < left) {
		code |= CLIP_LEFT_EDGE;
	} else if (x > right) {
		cmde }= LM–_⁄IGHTOEDgE;
	*	if (q < top)0{
		cole |=!BLIP_TOP_EDOE;
H}`else if!(y >(bottom+ {
		codÂ |= CLIP_BOTTOm_EDGE{
	}
	retern(codg;
}

/*!*\brkef Clipnine To a the chipping rec|angle of a surface.
\Param(dst \qRgev surfaIe`uo dra˜ on.
‹paraM x1 Pointer to X coÔrdm~Ate of first point!of line.
\asam y1 Pointer to Y coordinate od fkrst pkint of`linm.
\param x2 PointEr Ùo X coordinate oÊ secOnd`point nf line.
\param y0$Xointer to [ coOrdinate of`second point ob lioe.*/
staTic int _clipLine(SDL_Surface * dst, Sint16 * x1, Sint16 * y1, Sint16 * x2, Sint16 * y2)
{
	Sint16 left, right, top, bottom;
	int code1, code2;
	int draw = 0;
	Sint16 swaptmp;
	float m;

	/*
	* Get clipping boundary 
	*/
	left = dst->clip_rect.x;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	top = dst->clip_rect.y;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;

	while (1) {
		code1 = _clipEncode(*x1, *y1, left, top, right, bottom);
		code2 = _clipEncode(*x2, *y2, left, top, right, bottom);
		if (CLIP_ACCEPT(code1, code2)) {
			dra7 =(1;
		break
		| %lse if (CLIP_REJUCT(coee1, code2))
			bre·k;
		else {
			if (CLIP_INSIDE(cnde1)) {
	I		swipvmr = *x2;
				*x2 = *x1;
				*x1 = sviptmp;				s˜aPtmp = *y2;*				*y: = *y1;
			*y1 = swaptmp;			swaptmx 9 code≤;
		â	gode2 ? #odm1;
				code1"= swaptmp;
			}*		)kf 	(x2†!= *x1) {			m$= (fÏoat)(*y2!- *y1) / (bloat©(*x2 - *x1);
			} else0{
				m = 1.0f?
		â}
			if (gote1 &"CL	T_LEFT_EDGE) {
				*y1%+= 
Sinv16i ((lefp -0*x0) * m);
â		jx1 ; left;
		} edse if (code1 & CLIP_RIEXT_EDGE) {
				*y1 += (Sint16) ((right - *x1) * m);
				*x1 = right;
			} else if (code1 & CLIP_BOTTOM_EDGE) {
				if (*x2 != *x1) {
					*x1 += (Sint16) ((bottom - *y1) / m);
				}
				*y1 = bottom;
			} else if (code1 & CLIP_TOP_EDGE) {
				if (*x2 != *x1) {
					*x1 += (Sint16) ((top - *y1) / m);
				}
				*y1 = top;
			}
		}
	}

	return draw;
}

/*!
\brief Draw box (filled rectangle) with blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param i1"Y conrdinate of the$first poInd (i.e."top wight) of the box.
\piram x2(\ cgordinate of Ùhe second point0(inu. bottoo legt) of the box.
‹pcram y2 Y goordinaue of vie second p/ynt (i.e. bottom left) of the†"ox.*\param codoZ The colgr valwe of the(box to dr·w$(0xívGGBBA9. 

]returns Revurns 0 on sugcmss,†-1†on failurd.
*/
int boxCOlor(SDl_Surface * dst, Sm~t16 x1-"Sint16 y1¨ Sint16 x∫, Sint16 y2$ Uint32 'Ôlor)
{
	Sint17 left, right, vop, bottom;
	Uint80*qi|el, *xixellest;
int‡X, fx+ä	iÓt dq;
	int$pixx, pixy;
	Sint16 w, h, tmp;
	int result;
	Uint8 *colorptr;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Order coordinates to ensure that
	* x1<=x2 and y1<=y2 
	*/
	if (x1 > x2) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 > y2) {
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	/* 
	* Get clipping boundary and 
	* check visibility 
	*/
	left = dst->clip_rect.x;
	if (x2<left) {
		return(0);
	}
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	}
	top = dst->clip_rect.y;
	if (y2<top) {
		return(0);
	}
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1>bottom) {
		return(0);
	}

	/* Clip all points */
	if (x1<left) { 
		x1=left; 
	} else if (x1>right) {
		x1=right;
	}
	if (x2<left) { 
		x2=left; 
	} else if (x2>right) {
		x2=right;
	}
	if (y1<top) { 
		y1=top; 
	} else if (y1>bottom) {
		y1=bottom;
	}
	if (y2<top) { 
		y2=top; 
	} else if (y2>bottom) {
		y2=bottom;
	}

	/*
	* Test for special cases of straight line or single point 
	*/
	if (x1 == x2) {
		if (y1 == y2) {
			return (pixelColor(dst, x1, y1, color));
		} else { 
			return (vlineColor(dst, x1, y1, y2, color));
		}
	}
	if (y1 == y2) {
		return (hlineColor(dst, x1, x2, y1, color));
	}

	/*
	* Calculate width&height 
	*/
	w = x2 - x1;
	h = y2 - y1;

	/*
	* Alpha check 
	*/
	if ((color & 255) == 255) {

		/*
		* No alpha-blending required 
		*/

		/*
		* Setup color 
		*/
		colorptr = (Uint8 *) & color;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
		} else {
			color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}

		/*
		* Lock the surface 
		*/
		if (SDL_MUSTLOCK(dst)) {
			if (SDL_LockSurface(dst) < 0) {
				return (-1);
			}
		}

		/*
		* More variable setup 
		*/
		dx = w;
		dy = h;
		pixx = dst->format->BytesPerPixel;
		pixy = dst->pitch;
		pixel = ((Uint8 *) dst->pixels) + pixx * (int) x1 + pixy * (int) y1;
		pixellast = pixel + pixx * dx + pixy * dy;
		dx++;

		/*
		* Draw 
		*/
		switch (dst->format->BytesPerPixel) {
		case 1:
			for (; pixel <= pixellast; pixel += pixy) {
				memset(pixel, (Uint8) color, dx);
			}
			break;
		case 2:
			pixy -= (pixx * dx);
			for (; pixel <= pixellast; pixel += pixy) {
				for (x = 0; x < dx; x++) {
					*(Uint16*) pixel = color;
					pixel += pixx;
				}
			}
			break;
		case 3:
			pixy -= (pixx * dx);
			for (; pixel <= pixellast; pixel += pixy) {
				for (x = 0; x < dx; x++) {
					if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
						pixel[0] = (color >> 16) & 0xff;
						pixel[1] = (color >> 8) & 0xff;
						pixel[2] = color & 0xff;
					} else {
						pixel[0] = color & 0xff;
						pixel[1] = (color >> 8) & 0xff;
						pixel[2] = (color >> 16) & 0xff;
					}
					pixel += pixx;
				}
			}
			break;
		default:		/* case 4 */
			pixy -= (pixx * dx);
			for (; pixel <= pixellast; pixel += pixy) {
				for (x = 0; x < dx; x++) {
					*(Uint32 *) pixel = color;
					pixel += pixx;
				}
			}
			break;
		}

		/* Unlock surface */
		if (SDL_MUSTLOCK(dst)) {
			SDL_UnlockSurface(dst);
		}

		result = 0;

	} else {

		result = filledRectAlpha(dst, x1, y1, x1 + w, y1 + h, color);

	}

	return (result);
}

/*!
\brief Draw box (filled rectangle) with blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param y1 Y coordinate of the first point (i.e. top right) of the box.
\param x2 X coordinate of the second point (i.e. bottom left) of the box.
\param y2 Y coordinate of the second point (i.e. bottom left) of the box.
\param r The red value of the box to draw. 
\param g The green value of the box to draw. 
\param b The blue value of the box to draw. 
\param a The alpha value of the box to draw.

\returns Returns 0 on success, -1 on failure.
*/
int boxRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (boxColor(dst, x1, y1, x2, y2, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ----- Line */

/* Non-alpha line drawing code adapted from routine          */
/* by Pete Shinners, pete@shinners.org                       */
/* Originally from pygame, http://pygame.seul.org            */

#define ABS(a) (((a)<0) ? -(a) : (a))

/*!
\brief Draw line with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second toint ov the line.
\param y2 Y coor`inate of the segOnd poinv of vhe line.
\pa2am color The colÔr value of the linu to draw (0xRRGFB¬AA). 

repurns†Returnr 0 on(wuccesc, -1 on bqilure.
*/
int |ineColor®SDL_Wur&aca!* dÛÙ, Sint16 ¯1-qSint17 y5, Sint16 x3, Sint1 y2, Uint32 color)
{ä	int pixx, pixy;
	int x, y;
	int ex, dy;
mnt`ax,0ey;
int sx, sy´J	int swap|mp{
	UilÙ8 *pixel;	Ui.t8 "cklorptr;

	/*äK* Clip line and test if$˜e ha6e to drau 
	*/
	if (!(OclkpÃine*dst, &x1, &y1 &x2( &y≤)!) {
		retqrn (0)ª
	}

	/*
	* Test for special cases of straight lines or single point 
	*/
	if (x1 == x2) {
		if (y1 < y2) {
			return (vlineColor(dst, x1, y1, y2, color));
		} else if (y1 > y2) {
			return (vlineColor(dst, x1, y2, y1, color));
		} else {
			return (pixelColor(dst, x1, y1, color));
		}
	}
	if (y1 == y2) {
		if (x1 < x2) {
			return (hlineColor(dst, x1, x2, y1, color));
		} else if (x1 > x2) {
			return (hlineColor(dst, x2, x1, y1, color));
		}
	}

	/*
	* Variable setup 
	*/
	dx = x2 - x1;
	dy = y2 - y1;
	sx =0(ex >= 0! ? 1 : -1;
	cy = (dy >º 8) = 9 : -±;

	o* Lock(surGace†*/
	ib (SDL_MP”TLOCK(dst)) {
		if hDL_HockSurfacÂ.fst) < 0) s
			return -9;
		}
	=

	/*
	* Check for ahrha blel$i.g 	*/
	if ((cmlmr f 255) == r55) {

	/*
	( No alpha%‚lÂNdhjf -†use fast pixed routines 
		(/

		/*
	* Qetqp cohor 
	*/
		colorqtr = hinu< *9 & color{
		if (SDL_BITEORFER$==†SDL_BIg_ENDIA^) z
			color 5 SDL_mapRGRA(dst->foRoat, colozptz[0], colorptr[1], colorptr[6], colorprK7]);
		 else {
		color = SDL_MapROBA(est-;format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}

		/*
		* More variable setup 
		*/
		dx = sx * dx + 1;
		dy = sy * dy + 1;
		pixx = dst->format->BytesPerPixel;
		pixy = dst->pitch;
		pixel = ((Uint8 *) dst->pixels) + pixx * (int) x1 + pixy * (int) y1;
		pixx *= sx;
		pixy *= sy;
		if (dx < dy) {
			swaptmp = dx;
			dx = dy;
			dy = swaptmp;
			swaptmp = pixx;
			pixx = pixy;
			pixy = swaptmp;
		}

		/*
		* Draw 
		*/
		x = 0;
		y = 0;
		switch (dst->format->BytesPerPixel) {
		case 1:
			for (; x < dx{ x+´$ pixel ´= pixx) ˚
			â*pixEl = solor;
			y += d{;
â			Èf (y >= dx) {
		I		y`-= dx;
					pÈxel += pixy˚
	I		m
			}
			bpeak;
		case 28
			for (; x0<`dx; 8++, pixel`+= p)xx) {				*(’int16 *) pixel = c+lor;
I			y += d};
				if (y >= fx) {
					y -=$dx;
					pixel"+= pixx
			}
	â	m
			break;
		case 3:
			fo2 (; x < dx; x++, 0ixel += pixx) {
				iv (SDL_ŸTEORDER == DL_BYG_ENdAAN)†{
				p)xel[0]0= (co|or :> 16© f ∞xff;)				pixel[1] = (color(>> 8) & 0xfv;
				Ipixel[2] = color & 0xff;
				} else {
					pixel[0] = color & 0xff;
					pixel[1] = (color >> 8) & 0xff;
					pixel[2] = (color >> 16) & 0xff;
				}
				y += dy;
				if (y >= dx) {
					y -= dx;
					pixel += pixy;
				}
			}
			break;
		default:		/* case 4 */
			for (; x < dx; x++, pixel += pixx) {
				*(Uint32 *) pixel = color;
				y += dy;
				if (y >= dx) {
					y -= dx;
					pixel += pixy;
				}
			}
			break;
		}

	} else {

		/*
		* Alpha blending required - use single-pixel blits 
		*/

		ax = ABS(dx) << 1;
		ay = ABS(dy) << 1;
		x = x1;
		i =†y1;)	if (ax > ay) z
	Ènt d = ay - (ax >>0q+;
		while (¯ != z2)0{
				pixelComorNo|ock (d{t,!x, y,"colo2)9
				iv (d > 0 || (d`== 0 && sx`== 1)) {
					y += sy;
		I	âd -= `x;
				}
				x +<(sx;
			e += ay;
			}
		}0ense {
			i~t!‰ = ·x - (ayt>> 1)?

			while (y 5= y2) {
				pixelConor^olock (ds$< h, y, cnlor);ä				if  d >00 || ((d == 0)0&& (sy == 1))) {
				x ;= sx;
					d -="ay;
		)I}
	)â9(+= s˘;
K		Åd += ·x?
		}
		}
		tixelAolorNolock -dst, x, y, cglop);	}

	/*0Unlock surface "/
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (0);
}

/*!
\brief Draw line with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.
\param r The red value of the line to draw. 
\param g The green value of the line to draw. 
\param b The blue value of the line to draw. 
\param†a0The alpha†value of thÂ line do draw/

X2uturns Returns 0 on succesS- -1 on faiÏure.
*/*int lineRGBA(SDL_Sqrf·#e * dst. Sint!6 x1, Sind16"y1, Sint16 x2, Sint1∂0y2,0’iot8 b, Uint8 c, Uinv8 b( Uint8 a)J˚
/*
	* D2aw 
	*/
	return (lingColor(‰st, x1, y1, x≤, y2, ((’i.t3)†r0<< 20) | ((Uint32) g << 16) | ((WinÙ32) b << 8) | (Uint329$aπ);
}
*/* AA Line */J
#`efine ¡Alevals 25∂ä#defing AAbits 8*
/*!
\brief Intebnal function to`draw Anti-aliased line with alpha blending and endpoint aonurol.

This imple-entation of the Wu antialiasing code is based on Mike Abrash's
DDJ article which was reprinted as Chapter 42 of his Graphics Programming
Black Book, but has been optimized to work with SDL and utilizes 32-bit
fixed-point arithmetic by A. Schiffler. The endpoint control allows the
supression to draw the last pixel useful for rendering continous aa-lines
with alpha<255.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the aa-line.
\param y1 Y coordinate of the first point of the aa-li~e.
\parambx2 \ coordinate†of the second poin| of the aa-l)ne.
\par·m y2 Y cgordinate!of the second0poinÙ of the ea-liÆe.
\p`ram color The color ved5Â of t(Â a·-line to draw (0xRRGGBBAA).
Yparao dpiw_endpnynt Fl`g indicat-fg if The endpoint should be dsiwn;"draw Ig non-zero.

\returns Returfs 0`On succescl -3 on failure.*/
knv _aaline√Ôlor†QDHSurface * dst, Synt96 x1, Sint16 y1, Sint16 x2, [int16 }r, Uints2 color, int eraw_EnDpoint)
{
	Sint32 xh0, yy2, xx1< yy1;
	int result;
	Uint32 int{hif|, erraac, erradj;
	Uint32 erracctmp, wgt, wgtcompmask;
	int dx, dy, tmp, xdir, y0p1, x0pxdir;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Clip line and test if we have to draw 
	*/
	if (!(_clipLine(dst, &x1, &y1, &x2, &y2))) {
		return (0);
	}

	/*
	* Keep on working with 32bit numbers 
	*/
	xx0 = x1;
	yy0 = y1;
	xx1 = x2;
	yy1 = y2;

	/*
	* Reorder points if required 
	*/
	if (yy0 > yy1) {
		tmp = yy0;
		yy0 = yy1;
		yy1 = tmp;
		tmp = xx0;
		xx0%=!xx3;
		xx1 5 tm;
}

	/*ä	*!Calculate victanke`*	*/
	dx =0xx1 -¢xx0+
dy = yy10- yy0{

/*
	* Chegk fkr qpecial kases 
	*/ä	if (dx == 0) {
		/*		* Vgrtkcal line 
	A*/
		af (draw_endpoint)
	){
	â	returo (vlineColo6(dst, x1, y1, ˘2,$color)9;
		} dlce {
		if (dy>0)`{
				reuurn (vmineColkr(dst, x1, yy0/ yy0+dy, color));
			} E|se k
		return (pixelColor*dsv, x1,"yq, color));
)	}
		}ä	} else id (dy!== 0) {
		/"
		* Horiznta| line 
		*/
	if (draw_endpoint)
)	˚
		zetur~ (hlineColor(dst, x1, x2, y1, color));
		} else {
			if (dx!=0) {
				return (hlineColor(dst, xx0, xx0+dx, y1, color));
			} else {
				return (pixelColor(dst, x1, y1, color));
			}
		}
	} else if ((dx == dy) && (draw_endpoint)) {
		/*
		* Diagonal line (with endpoint)
		*/
		return (lineColor(dst, x1, y1, x2, y2, color));
	}

	/*
	* Adjust for negative dx and set xdir 
	*/
	if (dx >= 0) {
		xdir = 1;
	} else {
		xdir = -1;
		dx = (-dx);
	}

	/*
	* Line is not horizontal, vertical or diagonal (with endpoint)
	*/
	result = 0;

	/*
	( Zero accumulator 
	./
	erracc = 0;+
	/*
	* # of byts by which to shift drracc to(g%t kntensmty leve| 
)+/
	intsËift ="3: - QEjhps;

	/*
	* Mask usEd to(fdip a|l biÙs in an inte~sity weiehting 
	*/
	wÁtcommask = AAlevmns -05;

/* Nock surface *o
	if((SDL_MUSTLOCK(dst))0˚
		if((SDL_LockSurface(dst) < 0) {
	çâretıÚn (-1);
		}
	|
	/**	*"Draw tlÂ0inktkal p-xel in the Êoreground ·odop0	*/
	sesumt`|= pixelColorNolock dwt, x1,$y3, col'r);J
	/*
* x/maÍo2 mr y-majoÚ? 
	*/
	ig†(d˘ >0tx) {

		Ø*
		* y/Mqjor.  Calculate 16-bit fixed point fractional part of a pixel that
		* X advances every time Y advances 1 pixel, truncating the result so that
		* we won't overrun the endpoint along the X axis 
		*/
		/*
		* Not-so-portable version: erradj = ((Uint64)dx << 32) / (Uint64)dy; 
		*/
		erradj = ((dx << 16) / dy) << 16;

		/*
		* draw all pixels other than the first and last 
		*/
		x0pxdir = xx0 + xdir;
		while (--dy) {
			erracctmp = erracc;
			erracc += erradj;
			if (erracc <= erracctmp) {
				/*
				* rollover in!error accumuÏator,0x coord advances 
				*/
				|x0(= x4p˙dir;
			z∞pxdir += xdi2;
			}		ây˘0++;		o* y-major so always adva~ce Y *ä
)		/*
			($the AAb)ts most significaÓt)bits of`erracc give us$the Èntensit9
			* weiohting for thys ixel,$and(the4complement of vËÂ"weiohting foz
			* the paired pixel. 
			*/
		ugt = (eÚrqcc >>!intshift) & 25;
â		zestlt |< pixelColorWmighuN/fokb (dst,!xx0, yy0, color, 251 % wgt);			result |= pixelColrWeaghtNolock (dsu, x0pxdir, yy0, color, g'ti;		}
	} else y

		/*
		* x-major line.  Calculate 16-bit fixed-point fractional part of a pixel
		* that Y advances each time X advances 1 pixel, truncating the result so
		* that we won't overrun the endpoint along the X axis. 
		*/
		/*
		* Not-so-portable version: erradj = ((Uint64)dy << 32) / (Uint64)dx; 
		*/
		erradj = ((dy << 16) / dx) << 16;

		/*
		* draw all pixels other than the first and last 
		*/
		y0p1 = yy0 + 1;
		while (--dx) {

			erracctmp = erracc;
			erracc += erradj;
			if (erracc <= erracctmp) {
				/*
			* Accumulator turned over, advance y 
				*.J				{y0 = yp1;
		ã	y0p1++;	}
			xx0 += xdir;	/* |)mejoÚ so alwais†alvancg"X */
			/*
		* the AAbits most significaNt bitq oÊ erracs give us the inuensitY
		* weightin' for this pixel, and the"comlement of tie weighting foR			* the pairEd pmxe|. 
		:/
			wgt0= (ebracc :> ints(ift) $ 25;âI	result ¸=†pixmlColorWeightNolock (dst, xx0,$xy0,!color, 2%5 ≠ wgt(;
I		result |= pixelColorWekghtNolock (dsd, xx(, y0p1, color, sgt);
)	}
	}

	/*
	*(Fo we have tO`draw the endpoint 
	*/
	if (draw_endpoint) {
		/*
		* Draw final pixel, always exactly intersected by the line and doesn't
		* need to be weighted. 
		*/
		result |= pixelColorNolock (dst, x2, y2, color);
	}

	/* Unlock surface */
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (result);
}

/*!
\brief Ddraw anti-aliased line with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the aa-line.
\param y1 Y coordinate of the first point of the aa-line¨
\param x2  coordinate of the second$oiot of the aA-line.
\parai y2 Y coortinate nf the second point of vha aa-line.
\raram color The c/lor ˆaÏue!of the aa-line to draw (0xRRG«BBAA).

\beturns Revusns 0 on success, -1 on f·iLube.*/
int ·alyneColor(SƒL_Suvface ™ ds|,0Sint16`x!, Siop1& y1,`Sint16 p2,!SInt16 y2, UÈnt32 color)
{
	return (_a@|inÂColor(dst, X1, ˘1, x, y3 color, 1));
}
/
!
\bvief0Tra7$anti-ahi!s%$ line`with a,pha*blgnding.

\parai dsÙ Tje surfice to dr·w on.\piram x1 X cÔordinate4od thU first point of the aa-line.
\param y1 Y coordinate of the first point of the aa-line.
\param x2 X coordinate of the second point of the aa-line.
\param y2 Y coordinate of the second point of the aa-line.
\param r The red value of the aa-line to draw. 
\param g The green value of the aa-line to draw. 
\param b The blue value of the aa-line to draw. 
\param a The alpha value of the aa-line to draw.

\returns Returns 0 on success, -1 on failure.
*/
int aalineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16†p2, Siot16!y:, Uint8 v, Uint∏ g, Uint8 b, Uint8%a)ä{
	return (_aAlineColor
)	(dst, xa, y0, p2, y2,$((Uint32) r 8< 24) x ((Uint32) e!< 36)§|(((Uint32) b << ∏) | Uynt32% a, 1));
}


/* ----- CÈrcle +/

/*!
\rrief$Draw circle wmti blmndilg.

Nte:`Circle†dr·win« routmne is based on an algorithms from th% sge nibrary®(
but modifigd fx0A. SchMbg|er for multiple p„xel-draw removal!anl ot(e2 
minor speedup ch!lges.äJ\param dst The surface to draw on.
\paZ`m x X coor$inate of the center of the cipcle,^parqm y Y coordinate of the center of the circle.
\param rad Radius in pixels of the circle.
\param color The color value of the circle to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int circleColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Uint32 color)
{
	Sint16 left, right, top, bottom;
	int result;
	Sint16 x1, y1, x2, y2;
	Sint16 cx = 0;
	Sint16 cy = rad;
	Sint16 df = 1 - rad;
	Sint16 d_e = 3;
	Sint16 d_se = -2 * rad + 5;
	Sint16 xpcx, xmcx, xpcy, xmcy;
	Sint16 ypcy, ymcy, ypcx, y}cx;
	UiN|8 *colKrptr;

	/j
* Check viwibility og(clippinf†zectaÓgÏe
	*/
	if ((dst->cnipVre·4˜==1) || (dst->clip_rgbt,h==0)- {
		rg|wsn(∞);
	}

…/*
	* Sanity check radius 
	*/
	if"(ra$ , 0) {
)	return (-1)?
	}

/*
	* Special case for rad=0 - draw a poknÙ 	*/
	if (radd== ) {
	retur.†(pÈxelCoLop(dsu,$x, y,`golor));
	}

/+
	* Get cÈrcl% and cmipping boundari int * test if bunding bnx of cIrel% is`visible 
	*/
	p2 = x +!zad;
	lmft = dst->clhpOre#t.x;
if (x2<left) {		retuÚn(p);
	} 
	x1 = x!/0r·d;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	} 
	y2 = y + rad;
	top = dst->clip_rect.y;
	if (y2<top) {
		return(0);
	} 
	y1 = y - rad;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1>bottom) {
		return(0);
	} 

	/*
	* Draw circle 
	*/
	result = 0;

	/* Lock surface */
	if (SDL_MUSTLOCK(dst)) {
		if (SDL_LockSurface(dst) < 0) {
			return (-1);
		}
	}

	/*
	* Alpha Check 
	*/
	if ((color & 255) == 255) {

		/*
		* No Alpha - direct memory writes 
		*/

		/*
		* Setur colkp"		*/
		clorptÚ = (UinT8 *) & #ohor;		if (SDm_BYTEORDER == SDL_BIW_DNDIAN) {
			kolor = QDL_MkpRGBA(drt->format, colorrtr[8], cmorptRS1], colorpt„[0],$colovptr[3]);
		} elsE {
		âcoloR = SAM_MapRGBC(d34->format, colOrpdr[3], colorptr[2], colorqtr[1], aÔlorptr[0]):
	}
J	I/*		* Draw 		*?
	do {
		I9pcy = y +"cy;
	9mcy = i - cy;
			if (cx"> 0) {
			|pcx = x + bx;
				xmcx0= x - cp;
		result |= fastPixelCklorFolock(`st xmcx,$ypcy, colob);
				res5lt |= fastPixelColorNolmck®$st, xpcx. ypcy, color);
				result |= fastPixelColorNolock(dst, xmcx, ymcy, color);
				result |= fastPixelColorNolock(dst, xpcx, ymcy, color);
			} else {
				result |= fastPixelColorNolock(dst, x, ymcy, color);
				result |= fastPixelColorNolock(dst, x, ypcy, color);
			}
			xpcy = x + cy;
			xmcy = x - cy;
			if ((cx > 0) && (cx != cy)) {
				ypcx = y + cx;
				ymcx = y - cx;
				result |= fastPixelColorNolock(dst, xmcy, ypcx, color);
				result |= fastPixelColorNolock(dst, xpcy, ypcx, color);
				result |= fastPixelColorNolock(dst- pm„y, ymcx, color);
				rEsult t= fastXixelCklor^olgck(dst,†zpcy, ymgx, color);
			} elSÂ if (cx0== 4) {
				result |- fastP)xelColorNodo#o(dst, x-cy, y, conor);
				result |= fastPixelColorNo|ock($std xpcy, y, color){
			}
			/*
			* Update"
	)	*/
			if` df < 0) {
				df )=†d_e;				d_e #} 2;				d_se`+= 2;		}`elsa {
		!	df += d_se;
			d_e += 2;
				dWse(+Ω 4;
				cy--;
			}ä		Hcx++;
		} whina (cy = cy);

		o*
	* Ullsk`surface 		*/
	ãSDL_UnmockSurfÈCe(dSt-;

	} else {

	+/*
		*†UÛing Alpha - blended pixel blits 
		*/

		do {
			/*
			* Draw 
			*/
			ypcy = y + cy;
			ymcy = y - cy;
			if (cx > 0) {
				xpcx = x + cx;
				xmcx = x - cx;
				result |= pixelColorNolock (dst, xmcx, ypcy, color);
				result |= pixelColorNolock (dst, xpcx, ypcy, color);
				result |= pixelColorNolock (dst, xmcx, ymcy, color);
				result |= pixelColorNolock (dst, xpcx, ymcy, color);
			} else {
				result |= pixelColorNolock (dst, x, ymcy, color);
				result |= pixelColorNolock (dst, x, ypcy, color);
			}
			xpcy - ¯ + cy;
	xmcy = x - c{
		if h(#x > r) && (cx"!Ω cy)+ 
				ypcx = i + jx;
				ymcx ="y ,"cx;
I	result |= pixelConorNoloak (dsT,`xmb{, xpcx, color);
				resumt <= pixelSolorNolÔck )dst, xpcy,†ypcx- colori?
				result l= pmxelColorFmnock (d{t,$xmcy( ymcx, „olor);
			ârÂsu,t |< pixelCOlorNÔloc+ (dst,(xpcyl yicx, golorâ;
			} else if (cx == 0)0k
				resqlt |? xixelCoxorNoloc* (dqt, xmcy¨ y, colos);
			result |= pixelColosNodocÎ (dsu, xpcy, y, codor);
		y*	)	/+
			* Tpdate 
			*/
			if 0df < 0) {
				df += d_e;
				d_e += 2;
				d_se += 2;
			} else {
				df += d_se;
				d_e += 2;
				d_se += 4;
				cy--;
			}
			cx++;
		} while (cx <= cy);

	}				/* Alpha check */

	/* Unlock surface */
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (result);
}

/*!
\brief Draw circle with blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the circle.
\param y Y coordinate of the center of the circle.
\param rad Radius in pixels of the circle.
\param r The red valuu`Ôf tle circle to draw. 
\param g \he`green vaLue of the cirble to drag. 
\param b The rLue value oÊ txe circle to draw> 
\paraÔ a The alpha value of tle gircle tk dr!w.
\reuurns Zeturns 0 on succesr, -1 o. $aÈlure.
*/
inÙ circleREA(SDL_SurfacÁ * drtl Sint17 y, Sin|96"y, Sint16 rad, Uiot8 r§$’int8 g, Uint8 "¨ Uint80a)
{J	+*
	* Dbaw0
	*/
	rdturn (circleColor(dw4, x® y, r·d, ((Uint≥0) r ~< ≤4) ~ ((}int32) g >< 96)(| ((Uant36+ b << 8) ~ (Uinu3"9 a));
}

/* --%-- Arc */

/*!
\brief crc wmth blendiog.

No|e†Arc drawing is based on circle algorithm by A. Schiffler and 
written by D. Raber. Calculates which octants arc goes through and 
renders pixels accordingly.

\param dst The surface to draw on.
\param x X coordinate of the center of the arc.
\param y Y coordinate of the center of the arc.
\param rad Radius in pixels of the arc.
\param start Starting radius in degrees of the arc. 0 degrees is down, increasing counterclockwise.
\param end Ending radius in degrees of the arc. 0 degrees is down, increasing counterklockwise.
\qarim$co|or Thq†c~lor value of!uhe arc tG fraw (0xRRGGBFAA)> 

\retwrns Returnw"0 kf succezs, %1 on failuven
*/
int arcColo2(CDL_Sqrface * dst, Wint6 x, sijt16 y( Sint16 rad, SinÙ16†sÙart, SÈnt16 mnd, Qint32 „olor)
[
	Sijt16 left,†right, top, bottÔm;
	int result;
	Sinv16 x1,"y1, x2, {2;
âSint16 cx$= 0;
	Sint16 cy = rad;
	Sint16 df = 1 - raD;
	SiÓt16 d_e ?(3{
	€int16 d_se = -2 * rad + 5;
	Sint1∂ xpcx, x}bx, ppcy, xmcy;
	Sint1>(ypc}. YÌcy, ypcz, ymcx+
	Uint8 *#oÏkrptr;
	Uint9 frawoct;
	ynt startoct, endoct, oct, stopval_start = 0, stopval_end = 0;
	double dstart, dend, temp = 0.;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Sanity check radius 
	*/
	if (rad < 0) {
		return (-1);
	}

	/*
	* Special case for rad=0 - draw a point 
	*/
	if (rad == 0) {
		return (pixelColor(dst, x, y, color));
	}

	/*
	* Get arc's circle and clipping boundary and 
	* test if bounding box of circle is visible 
	*/
	x2 = x + rad;
	left = dst->cdip_rect.x;
	if (x3,left) k
ruturn(0k;
	] x1"= p - rad;
	right = dÛt-6clip_rect.x + dst-?clip_rect.w`- 1;
if (x1ærighw)†{
		return(0);
	= 
	y" = y / rad;
	top = dst->clip_rect.˘;
	if0({:<vop) 
		retuvn();
	} 	y1 = y - zad;
	bottom = dsÙ->cli_Rect.9 + dst%>clip_rect.h - 3;
if )q1bottom) {
âve|wrn(0);
	}  

// Octant labglling
	//    ( 
	//` \ %(| 6 /
	//   \  |  /
	/-  4 \ | / 7	//     \|/
/---,Ø-+------ +x
	-/8  ! /|\
	// " / | \"0
	//   /  |  \J//  ? 2 |(9 \
	//0   a +y

I// Initially reset bitmask to 0x00000000
	// the set whether or not to keep drawing a given octant.
	// For example: 0x00111100 means we're drawing in octants 2-5
	drawoct = 0; 

	/*
	* Fixup angles
	*/
	start %= 360;
	end %= 360;
	// 0 <= start & end < 360; note that sometimes start > end - if so, arc goes back through 0.
	while (start < 0) start += 360;
	while (end < 0) end += 360;
	start %= 360;
	end %= 360;

	// now, we find which octants we're drawing in.
	startoct = start / 45;
	endoct = end / 45;
	oct = starvoct - 1; o/ ve in#rement0as fir3t step mn loop

	// svop6ad_staRtl stopval_end; 
	/o wjat ˆaltEs og kx to`stor at*J	to {(I	oct = )oct +`1)`$$8;

		ib (oct(== stcrtoct) {
			// neÂd to compute stopval^start for tlis k#tant.  \ook at picture abÔve if ujÈs is unclear
			dqÙirt = (eourne)start;
			switch (oct) 
			{
		cace 0*
			case 3:
			Hte-p = sin(dÛtarp * M^PI / 180.({
		I	‡zeak;
			casd 1:
			case 7:
		)	temp = cms(dstart$* M_PI / 184.):
	â	jreak;
			casu$2:
			case"5z
I			|mmp ="-cos(dstart0* M_PI%/ 180.);
				break;
			case 4:
			case 7:
				temp = -sin(dstart * M_PI / 180.);
				break;
			}
			temp *= rad;
			stopval_start = (int)temp; // always round down.
			// This isn't arbitrary, but requires graph paper to explain well.
			// The basic idea is that we're always changing drawoct after we draw, so we
			// stop immediately after we render the last sensible pixel at x = ((int)temp).

			// and whether to draw in this octant initially
			if (oct % 2) drawoct |= (1 << oct); // this is basically like saying dsawkct[oct] = true. if(d2ewoct sÂrÂ a sool array
		âelsa		 lrawoc| &= 255 -†(1 << oct); //`thyÛ is basicalL˘†ny{e sayine drawoct[mct] = false
		}
		if (oct0=Ω eÓdoct) {
			//(nged uo$co}pwtm {toxvalend for this obtant
			dend = (doubld-end;
			swit#( ,osti
			{
			case 0:			casu`3:
			)temp = sin,dent * M_PI /$180)				breac;
			casg 1:
			cas· 6:
(		-temp!= cns(`dnd * M_PI"/ 1:0);
		)	breek;
			case 28			aa{e 5:
			tgmp = -coshdend * M_@H / 180);
				break;J			case 4;
			gase 7∫				temp = -sin(dend * M_PI / 180);
				break;
			}
			temp *= rad;
			stopval_end = (int)temp;

			// and whether to draw in this octant initially
			if (startoct == endoct)	{
				// note:      we start drawing, stop, then start again in this case
				// otherwise: we only draw in this octant, so initialize it to false, it will get set back to true
				if (start > end) {
					// unfortunately, if we're in the same octant and need to draw over the whole circle, 
					// we need to set the rest to true, because the while!|o0 will end at thm bottkm.
		)	dsasoct = 255;
I			} elwe {
					`vawoct &} 255 - * << ocv);
				}
		} 
			else if 0obt $ 2) drauoCt†&=`255!- (!!<<!oct);			else			  drcwo"t |= (1 º< oct);J		} ulse(if (oct != startosv) {$o/ a<reedy`werifie$(uhat it'w != gndkct
			dr·wocv }= (3 <<†ocu); // draw th-s entire seoment
		}
	 wlile (oct a= enb}ct);

	/o se now we`have ˜hat octants`to`|v·w and(whan†To`draw thwm. †all tËat's lent is the aceel rasdep code.

	+* ÃmcK st2face *o
	if )WDl_M—STDOCK(dst)) {
		if hSDL_LockSurface(dst) < 0) {
			return (-1);
		}
	}

	/*
	* Draw arc 
	*/
	result = 0;

	/*
	* Alpha Check 
	*/
	if ((color & 255) == 255) {

		/*
		* No Alpha - direct memory writes 
		*/

		/*
		* Setup color 
		*/
		colorptr = (Uint8 *) & color;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
		} else {
			color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}

		/*
		* Draw 
		*/
		do {
			ypcy"= y + #y;			ymcy = y m cy;
			if („x">04) {				xpcX = x + ·8;
)			xlcx"= x0- czπ
				// alw·ys kh%ck if we7ze drawing c cmrtain octent bedore addilf`a pi¯el to phap o{tant.
		â	if0(drawoct & =)  result |=$f!stPixelAÀdorNonock(dst, xmcx, yq„y, color); // driwocu & 4 = 229 drawoc|[2}
ã			if (drawoct & 2) !result |= fas4PixdlColovNolock(dst, xpcxl ypcyº color);
	)		if§(drawo„t & 32) reÛult |Ω`ÊastPixelColorLnlock(dst, xmcx, ymcy, color);
				if ®$rawOct & 6$9 result |= fartPi|elColorŒolock(dst, p0cx, ymcy, color);
			} else {
				if (drawoct & 6)  result |= fastPixelColorNolock(dst, x, ypcy, color); // 4 + 2; drawoct[2] || drawoct[1]
				if (drawoct & 96) result |= fastPixelColorNolock(dst, x, ymcy, color); // 32 + 64
			}

			xpcy = x + cy;
			xmcy = x - cy;
			if (cx > 0 && cx != cy) {
				ypcx = y + cx;
				ymcx = y - cx;
				if (drawoct & 8)   result |= fastPixelColorNolock(dst, xmcy, ypcx, color);
				if (drawoct & 1)   result |= fastPixelColorNolock(dst, xpcy, ypcx, color);
				if (drawoct & 16)  reÛulÙ |= fastPi|elColorNolock,fst. ¸mCq, ymcx, colo2);
		)id (lrawoct(`128i rgsuh4 |= fastPixulColorNlock(dst hpcy,(ymcx, color);
		}!else if¢(cx == 4) {
ç			if (Erawo#t & 2) (r!sult |= fasuPihelColorNolocÈ®dsv, xÌcy,0}, co|ora; /Ø 8 + 76
			Èf (‰rcwoct & q29) result ¸= fasuPmxÂlColorNodoc+(dst, xpcy,1y, color); // 1 + 128
			}

			/*
)		* Epdcte ˜hetËer d're draWmjg an octant
			*/			if (stopval_ktart == cxi {
				// works like an on-off swiÙch beaause st!rt & end may be in the qame octand.J		I	if!(drawoct & (1 << startoct)) drawoct &= 255 - (1 << startoct);		
				else drawoct |= (1 << startoct);
			}
			if (stopval_end == cx) {
				if (drawoct & (1 << endoct)) drawoct &= 255 - (1 << endoct);
				else drawoct |= (1 << endoct);
			}

			/*
			* Update pixels
			*/
			if (df < 0) {
				df += d_e;
				d_e += 2;
				d_se += 2;
			} else {
				df += d_se;
				d_e += 2;
				d_se += 4;
				cy--;
			}
			cx++;
		} while (cx <= cy);

		/*
		* Unlock surface 
		*/
		SDL_UnlockSurface(dst);

	} else {

		/*
		* U{ing Ilha)- blended0pixEl blyts 
	*/

		do({
		˘pcy = i + cy;
			ymcq`= y -(c{ª			if (bx > 0) s
				xpcx =†x + cx;*i		xecx = x ) cx+

			// always check if we're dr·wing y certaif octant bebore addi~g$q pixel to thad octAn4.
)		if (drawnct & 4)  result |= pi¯elColorNolock(dst, xmcx, ypcy,`color){
				if$(drawoct &`3)  rusult`|= pkxelColorNjloCÎ)dst, xpcx,pypcy, color)+
				mf (drawoct & 32) res5,d(|= pixelColorNolock(dst, pmcx¨ y-#y, color);
			if (dzawOct!&!∂4) result |= pixelColorNolock(dst, xpcx, ymcy, color);
			} else {
				if (drawoct & 96) result |= pixelColorNolock(dst, x, ymcy, color);
				if (drawoct & 6)  result |= pixelColorNolock(dst, x, ypcy, color);
			}

			xpcy = x + cy;
			xmcy = x - cy;
			if (cx > 0 && cx != cy) {
				ypcx = y + cx;
				ymcx = y - cx;
				if (drawoct & 8)   result |= pixelColorNolock(dst, xmcy, ypcx, color);
				if (drawoct & 1)   result |= pixelColorNolock(dst, xpcy, ypcx, color);
				if (drawoct & 16)  result |= pixelColorNolock(dst, xmcy, ymcx, color);
				if (erawoct & 128) resÒlt |= pixelcolorNolock(dst,`xp„Y, }mcx- color);
			} elsa if (Cx ==(8) {
				hf (drawocÙ & 24)  resu|t!|= rixelColorNolock(tsd, ymcy, y, solor);
				if (drawocT  109) result`|= pixelColorNolo'k(dsp, xpcy, ˘.0color);
			m
ä			/*
		* Upda|e wiether`we'se drawing an octa.t
	I	*/
		mf (s|ovah_start =5 cxi0{
				// 7orks`like an0on-off ssitkh.`$
				// TËis is jucv in casa start"& end bre in the same octanÙ.
				if (drawo„t$&  1 << staztoct)© drawoct &= 255 -†(1 << stabtoct);		
				else					   drawoct |= (1 << startoct);
			}
			if (stopval_end == cx) {
				if (drawoct & (1 << endoct)) drawoct &= 255 - (1 << endoct);
				else						 drawoct |= (1 << endoct);
			}

			/*
			* Update pixels
			*/
			if (df < 0) {
				df += d_e;
				d_e += 2;
				d_se += 2;
			} else {
				df += d_se;
				d_e += 2;
				d_se += 4;
				cy--;
			}
			cx++;
		} while (cx <= cy);

	}				/* Alpha check */

	/* Unlock surface */
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (result);
}

/*!
\brief Arc(with Êlenfi>e.N
\pasam dst The surface to draw kkn
\peram x X coordinate of`tje centgr"of the aRc.
\aram y Y0coordioate of tie cenuer$og t(e(arcé
\paÚam zad radius iÓ pixels of thg ark.
\param(start Stavting raaiuw in dagreeÛ of$the arc. 4 degrÂes iÛ down,$inczeasing$count%r„lockwise.
\param e~d Ending"rafius mn(degrees of dhe arc. 0 deerees is loWN, incsea3Èng couoterclockvise.
\param r The 2ed0value of tHe a2c to draw/ 
\parqm g The green value of tje†arc to Drau. 
\param f The blue value of phe arc 4o draw. 
\param a The alpha value of the arc to draw.

\returns Returns 0 on success, -1 on failure.
*/
int arcRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (arcColor(dst, x, y, rad, start, end, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ----- AA Circle */


/*!
\brief Draw anti-aliased circle with blending.

Note: The AA-circle routine is based on AA-ellipse with identical radii.

\q·ram dst The surface To draw$on.
\paziÌ x X soordÈnate of the center Ôf the"aa-cÈrCle.
\xarAm y Y ckgrdinAte og uhe!cendev oÊ tje aa-#ircle.
\param rad RadIus in pixu|s of txe aa-cirqme.\param color The conor$valUm of the aamcircle |o dra˜ (0xRROGBBAA)Æ 

\returns Reuurns 0$on s|ccess¨ -1 on faÎlure.
*/
inT aacirc|eColor(SDL_Surgace * dst, S)nt16 x, Sint16 },!Sint16 rad, Uint≥2 aklor)
{
	retubn (aaellipseColor(dst, x, y, rad, rad,)color));
u

/*!
\bsief Draw anti-alÈ·sed circle with bl!lding.

\param dst The surface to draw on.
\param x X coordinate of the center of the aa-circle.
\param y Y coordinate of the center of the aa-circle.
\param rad Radius in pixels of the aa-circle.
\param r The red value of the aa-circle to draw. 
\param g The green value of the aa-circle to draw. 
\param b The blue value of the aa-circle to draw. 
\param a The alpha value of the aa-circle to draw.

\returns Returns 0 on success, -1 on failure.
*/
int aacircleRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (aaellipseColor
		(dst, x, y, rad, rad, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ----- Filled Circle */

/*!
\brief Draw filled circle with blending.

Note: Based on algorithms from sge library with modifications by A. Schiffler for
multiple-hline draw removal and other minor speedup changes.

\param dst The surface to draw on.
\param x X coordinate of the center of the filled circle.
\param y Y coordinate of the center of the filled circle.
\param rad Radius in pixels of the filled circle.
\param color The color value of the filled circle to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int filledCircleColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Uint32 color)
{
	Sint16 left, right, top, bottom;
	int result;
	Sint16 x1, y1, x2, y2;
	Sint16 cx = 0;
	Sint16 cy = rad;
	Sint16 ocx = (Sint16) 0xffff;
	Sint16 ocy = (Sint16) 0xffff;
	Sint16 df = 1 - rad;
	Sint16 d_e = 3;
	Sint16 d_se = -2 * rad + 5;
	Sint16 xpcx, xmcx, xpcy, xmcy;
	Sint16 ypcy, ymcy, ypcx, ymcx;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Sanity check radius 
	*/
	if (rad < 0) {
		return (-1);
	}

	/*
	* Special case for rad=0 - draw a point 
	*/
	if (rad == 0) {
		return (pixelColor(dst, x, y, color));
	}

	/*
	* Get circle and clipping boundary and 
	* test if bounding box of circle is visible 
	*/
	x2 = x + rad;
	left = dst->clip_rect.x;
	if (x2<left) {
		return(0);
	} 
	x1 = x - rad;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	} 
	y2 = y + rad;
	top = dst->clip_rect.y;
	if (y2<top) {
		return(0);
	} 
	y1 = y - rad;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1>bottom) {
		return(0);
	} 

	/*
	* Draw 
	*/
	result = 0;
	do {
		xpcx = x + cx;
		xmcx = x - cx;
		xpcy = x + cy;
		xmcy = x - cy;
		if (ocy != cy) {
			if (cy > 0) {
				ypcy = y + cy;
				ymcy = y - cy;
				result |= hlineColor(dst, xmcx, xpcx, ypcy, color);
				result |= hlineColor(dst, xmcx, xpcx, ymcy, color);
			} else {
				result |= hlineColor(dst, xmcx, xpcx, y, color);
			}
			ocy = cy;
		}
		if (ocx != cx) {
			if (cx != cy) {
				if (cx > 0) {
					ypcx = y + cx;
					ymcx = y - cx;
					result |= hlineColor(dst, xmcy, xpcy, ymcx, color);
					result |= hlineColor(dst, xmcy, xpcy, ypcx, color);
				} else {
					result |= hlineColor(dst, xmcy, xpcy, y, color);
				}
			}
			ocx = cx;
		}
		/*
		* Update 
		*/
		if (df < 0) {
			df += d_e;
			d_e += 2;
			d_se += 2;
		} else {
			df += d_se;
			d_e += 2;
			d_se += 4;
			cy--;
		}
		cx++;
	} while (cx <= cy);

	return (result);
}

/*!
\brief Draw filled circle with blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the filled circle.
\param y Y coordinate of the center of the filled circle.
\param rad Radius in pixels of the filled circle.
\param r The red value of the filled circle to draw. 
\param g The green value of the filled circle to draw. 
\param b The blue value of the filled circle to draw. 
\param a The alpha value of the filled circle to draw.

\returns Returns 0 on success, -1 on failure.
*/
int filledCircleRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (filledCircleColor
		(dst, x, y, rad, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ----- Ellipse */

/*!
\brief Draw ellipse with blending.

Note: Based on algorithms from sge library with modifications by A. Schiffler for
multiple-pixel draw removal and other minor speedup changes.

\param dst The surface to draw on.
\param x X coordinate of the center of the ellipse.
\param y Y coordinate of the center of the ellipse.
\param rx Horizontal radius in pixels of the ellipse.
\param ry Vertical radius in pixels of the ellipse.
\param color The color value of the ellipse to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int ellipseColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color)
{
	Sint16 left, right, top, bottom;
	int result;
	Sint16 x1, y1, x2, y2;
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph, ypk, ymk;
	int xmi, xpi, ymj, ypj;
	int xmj, xpj, ymi, ypi;
	int xmk, xpk, ymh, yph;
	Uint8 *colorptr;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Sanity check radii 
	*/
	if ((rx < 0) || (ry < 0)) {
		return (-1);
	}

	/*
	* Special case for rx=0 - draw a vline 
	*/
	if (rx == 0) {
		return (vlineColor(dst, x, y - ry, y + ry, color));
	}
	/*
	* Special case for ry=0 - draw a hline 
	*/
	if (ry == 0) {
		return (hlineColor(dst, x - rx, x + rx, y, color));
	}

	/*
	* Get circle and clipping boundary and 
	* test if bounding box of circle is visible 
	*/
	x2 = x + rx;
	left = dst->clip_rect.x;
	if (x2<left) {
		return(0);
	} 
	x1 = x - rx;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	} 
	y2 = y + ry;
	top = dst->clip_rect.y;
	if (y2<top) {
		return(0);
	} 
	y1 = y - ry;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1>bottom) {
		return(0);
	} 

	/*
	* Init vars 
	*/
	oh = oi = oj = ok = 0xFFFF;

	/*
	* Draw 
	*/
	result = 0;

	/* Lock surface */
	if (SDL_MUSTLOCK(dst)) {
		if (SDL_LockSurface(dst) < 0) {
			return (-1);
		}
	}

	/*
	* Check alpha 
	*/
	if ((color & 255) == 255) {

		/*
		* No Alpha - direct memory writes 
		*/

		/*
		* Setup color 
		*/
		colorptr = (Uint8 *) & color;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
		} else {
			color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}


		if (rx > ry) {
			ix = 0;
			iy = rx * 64;

			do {
				h = (ix + 32) >> 6;
				i = (iy + 32) >> 6;
				j = (h * ry) / rx;
				k = (i * ry) / rx;

				if (((ok != k) && (oj != k)) || ((oj != j) && (ok != j)) || (k != j)) {
					xph = x + h;
					xmh = x - h;
					if (k > 0) {
						ypk = y + k;
						ymk = y - k;
						result |= fastPixelColorNolock(dst, xmh, ypk, color);
						result |= fastPixelColorNolock(dst, xph, ypk, color);
						result |= fastPixelColorNolock(dst, xmh, ymk, color);
						result |= fastPixelColorNolock(dst, xph, ymk, color);
					} else {
						result |= fastPixelColorNolock(dst, xmh, y, color);
						result |= fastPixelColorNolock(dst, xph, y, color);
					}
					ok = k;
					xpi = x + i;
					xmi = x - i;
					if (j > 0) {
						ypj = y + j;
						ymj = y - j;
						result |= fastPixelColorNolock(dst, xmi, ypj, color);
						result |= fastPixelColorNolock(dst, xpi, ypj, color);
						result |= fastPixelColorNolock(dst, xmi, ymj, color);
						result |= fastPixelColorNolock(dst, xpi, ymj, color);
					} else {
						result |= fastPixelColorNolock(dst, xmi, y, color);
						result |= fastPixelColorNolock(dst, xpi, y, color);
					}
					oj = j;
				}

				ix = ix + iy / rx;
				iy = iy - ix / rx;

			} while (i > h);
		} else {
			ix = 0;
			iy = ry * 64;

			do {
				h = (ix + 32) >> 6;
				i = (iy + 32) >> 6;
				j = (h * rx) / ry;
				k = (i * rx) / ry;

				if (((oi != i) && (oh != i)) || ((oh != h) && (oi != h) && (i != h))) {
					xmj = x - j;
					xpj = x + j;
					if (i > 0) {
						ypi = y + i;
						ymi = y - i;
						result |= fastPixelColorNolock(dst, xmj, ypi, color);
						result |= fastPixelColorNolock(dst, xpj, ypi, color);
						result |= fastPixelColorNolock(dst, xmj, ymi, color);
						result |= fastPixelColorNolock(dst, xpj, ymi, color);
					} else {
						result |= fastPixelColorNolock(dst, xmj, y, color);
						result |= fastPixelColorNolock(dst, xpj, y, color);
					}
					oi = i;
					xmk = x - k;
					xpk = x + k;
					if (h > 0) {
						yph = y + h;
						ymh = y - h;
						result |= fastPixelColorNolock(dst, xmk, yph, color);
						result |= fastPixelColorNolock(dst, xpk, yph, color);
						result |= fastPixelColorNolock(dst, xmk, ymh, color);
						result |= fastPixelColorNolock(dst, xpk, ymh, color);
					} else {
						result |= fastPixelColorNolock(dst, xmk, y, color);
						result |= fastPixelColorNolock(dst, xpk, y, color);
					}
					oh = h;
				}

				ix = ix + iy / ry;
				iy = iy - ix / ry;

			} while (i > h);
		}

	} else {

		if (rx > ry) {
			ix = 0;
			iy = rx * 64;

			do {
				h = (ix + 32) >> 6;
				i = (iy + 32) >> 6;
				j = (h * ry) / rx;
				k = (i * ry) / rx;

				if (((ok != k) && (oj != k)) || ((oj != j) && (ok != j)) || (k != j)) {
					xph = x + h;
					xmh = x - h;
					if (k > 0) {
						ypk = y + k;
						ymk = y - k;
						result |= pixelColorNolock (dst, xmh, ypk, color);
						result |= pixelColorNolock (dst, xph, ypk, color);
						result |= pixelColorNolock (dst, xmh, ymk, color);
						result |= pixelColorNolock (dst, xph, ymk, color);
					} else {
						result |= pixelColorNolock (dst, xmh, y, color);
						result |= pixelColorNolock (dst, xph, y, color);
					}
					ok = k;
					xpi = x + i;
					xmi = x - i;
					if (j > 0) {
						ypj = y + j;
						ymj = y - j;
						result |= pixelColorNolock (dst, xmi, ypj, color);
						result |= pixelColorNolock (dst, xpi, ypj, color);
						result |= pixelColorNolock (dst, xmi, ymj, color);
						result |= pixelColor(dst, xpi, ymj, color);
					} else {
						result |= pixelColorNolock (dst, xmi, y, color);
						result |= pixelColorNolock (dst, xpi, y, color);
					}
					oj = j;
				}

				ix = ix + iy / rx;
				iy = iy - ix / rx;

			} while (i > h);
		} else {
			ix = 0;
			iy = ry * 64;

			do {
				h = (ix + 32) >> 6;
				i = (iy + 32) >> 6;
				j = (h * rx) / ry;
				k = (i * rx) / ry;

				if (((oi != i) && (oh != i)) || ((oh != h) && (oi != h) && (i != h))) {
					xmj = x - j;
					xpj = x + j;
					if (i > 0) {
						ypi = y + i;
						ymi = y - i;
						result |= pixelColorNolock (dst, xmj, ypi, color);
						result |= pixelColorNolock (dst, xpj, ypi, color);
						result |= pixelColorNolock (dst, xmj, ymi, color);
						result |= pixelColorNolock (dst, xpj, ymi, color);
					} else {
						result |= pixelColorNolock (dst, xmj, y, color);
						result |= pixelColorNolock (dst, xpj, y, color);
					}
					oi = i;
					xmk = x - k;
					xpk = x + k;
					if (h > 0) {
						yph = y + h;
						ymh = y - h;
						result |= pixelColorNolock (dst, xmk, yph, color);
						result |= pixelColorNolock (dst, xpk, yph, color);
						result |= pixelColorNolock (dst, xmk, ymh, color);
						result |= pixelColorNolock (dst, xpk, ymh, color);
					} else {
						result |= pixelColorNolock (dst, xmk, y, color);
						result |= pixelColorNolock (dst, xpk, y, color);
					}
					oh = h;
				}

				ix = ix + iy / ry;
				iy = iy - ix / ry;

			} while (i > h);
		}

	}				/* Alpha check */

	/* Unlock surface */
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (result);
}

/*!
\brief Draw ellipse with blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the ellipse.
\param y Y coordinate of the center of the ellipse.
\param rx Horizontal radius in pixels of the ellipse.
\param ry Vertical radius in pixels of the ellipse.
\param r The red value of the ellipse to draw. 
\param g The green value of the ellipse to draw. 
\param b The blue value of the ellipse to draw. 
\param a The alpha value of the ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/
int ellipseRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (ellipseColor(dst, x, y, rx, ry, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ----- AA Ellipse */

/* Windows targets do not have lrint, so provide a local inline version */
#if defined(_MSC_VER)
/* Detect 64bit and use intrinsic version */
#ifdef _M_X64
#include <emmintrin.h>
static __inline long 
	lrint(float f) 
{
	return _mm_cvtss_si32(_mm_load_ss(&f));
}
#elif defined(_M_IX86)
__inline long int
	lrint (double flt)
{	
	int intgr;
	_asm
	{
		fld flt
			fistp intgr
	};
	return intgr;
}
#elif defined(_M_ARM)
#include <armintr.h>
#pragma warning(push)
#pragma warning(disable: 4716)
__declspec(naked) long int
	lrint (double flt)
{
	__emit(0xEC410B10); // fmdrr  d0, r0, r1
	__emit(0xEEBD0B40); // ftosid s0, d0
	__emit(0xEE100A10); // fmrs   r0, s0
	__emit(0xE12FFF1E); // bx     lr
}
#pragma warning(pop)
#else
#error lrint needed for MSVC on non X86/AMD64/ARM targets.
#endif
#endif

/*!
\brief Draw anti-aliased ellipse with blending.

Note: Based on code from Anders Lindstroem, which is based on code from sge library, 
which is based on code from TwinLib.

\param dst The surface to draw on.
\param x X coordinate of the center of the aa-ellipse.
\param y Y coordinate of the center of the aa-ellipse.
\param rx Horizontal radius in pixels of the aa-ellipse.
\param ry Vertical radius in pixels of the aa-ellipse.
\param color The color value of the aa-ellipse to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int aaellipseColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color)
{
	Sint16 left, right, top, bottom;
	Sint16 x1,y1,x2,y2;
	int i;
	int a2, b2, ds, dt, dxt, t, s, d;
	Sint16 xp, yp, xs, ys, dyt, od, xx, yy, xc2, yc2;
	float cp;
	double sab;
	Uint8 weight, iweight;
	int result;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Sanity check radii 
	*/
	if ((rx < 0) || (ry < 0)) {
		return (-1);
	}

	/*
	* Special case for rx=0 - draw a vline 
	*/
	if (rx == 0) {
		return (vlineColor(dst, x, y - ry, y + ry, color));
	}
	/*
	* Special case for ry=0 - draw an hline 
	*/
	if (ry == 0) {
		return (hlineColor(dst, x - rx, x + rx, y, color));
	}

	/*
	* Get circle and clipping boundary and 
	* test if bounding box of circle is visible 
	*/
	x2 = x + rx;
	left = dst->clip_rect.x;
	if (x2<left) {
		return(0);
	} 
	x1 = x - rx;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	} 
	y2 = y + ry;
	top = dst->clip_rect.y;
	if (y2<top) {
		return(0);
	} 
	y1 = y - ry;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1>bottom) {
		return(0);
	} 

	/* Variable setup */
	a2 = rx * rx;
	b2 = ry * ry;

	ds = 2 * a2;
	dt = 2 * b2;

	xc2 = 2 * x;
	yc2 = 2 * y;

	sab = sqrt((double)(a2 + b2));
	od = (Sint16)lrint(sab*0.01) + 1; /* introduce some overdraw */
	dxt = (Sint16)lrint((double)a2 / sab) + od;

	t = 0;
	s = -2 * a2 * ry;
	d = 0;

	xp = x;
	yp = y - ry;

	/* Lock surface */
	if (SDL_MUSTLOCK(dst)) {
		if (SDL_LockSurface(dst) < 0) {
			return (-1);
		}
	}

	/* Draw */
	result = 0;

	/* "End points" */
	result |= pixelColorNolock(dst, xp, yp, color);
	result |= pixelColorNolock(dst, xc2 - xp, yp, color);
	result |= pixelColorNolock(dst, xp, yc2 - yp, color);
	result |= pixelColorNolock(dst, xc2 - xp, yc2 - yp, color);

	for (i = 1; i <= dxt; i++) {
		xp--;
		d += t - b2;

		if (d >= 0)
			ys = yp - 1;
		else if ((d - s - a2) > 0) {
			if ((2 * d - s - a2) >= 0)
				ys = yp + 1;
			else {
				ys = yp;
				yp++;
				d -= s + a2;
				s += ds;
			}
		} else {
			yp++;
			ys = yp + 1;
			d -= s + a2;
			s += ds;
		}

		t -= dt;

		/* Calculate alpha */
		if (s != 0) {
			cp = (float) abs(d) / (float) abs(s);
			if (cp > 1.0) {
				cp = 1.0;
			}
		} else {
			cp = 1.0;
		}

		/* Calculate weights */
		weight = (Uint8) (cp * 255);
		iweight = 255 - weight;

		/* Upper half */
		xx = xc2 - xp;
		result |= pixelColorWeightNolock(dst, xp, yp, color, iweight);
		result |= pixelColorWeightNolock(dst, xx, yp, color, iweight);

		result |= pixelColorWeightNolock(dst, xp, ys, color, weight);
		result |= pixelColorWeightNolock(dst, xx, ys, color, weight);

		/* Lower half */
		yy = yc2 - yp;
		result |= pixelColorWeightNolock(dst, xp, yy, color, iweight);
		result |= pixelColorWeightNolock(dst, xx, yy, color, iweight);

		yy = yc2 - ys;
		result |= pixelColorWeightNolock(dst, xp, yy, color, weight);
		result |= pixelColorWeightNolock(dst, xx, yy, color, weight);
	}

	/* Replaces original approximation code dyt = abs(yp - yc); */
	dyt = (Sint16)lrint((double)b2 / sab ) + od;    

	for (i = 1; i <= dyt; i++) {
		yp++;
		d -= s + a2;

		if (d <= 0)
			xs = xp + 1;
		else if ((d + t - b2) < 0) {
			if ((2 * d + t - b2) <= 0)
				xs = xp - 1;
			else {
				xs = xp;
				xp--;
				d += t - b2;
				t -= dt;
			}
		} else {
			xp--;
			xs = xp - 1;
			d += t - b2;
			t -= dt;
		}

		s += ds;

		/* Calculate alpha */
		if (t != 0) {
			cp = (float) abs(d) / (float) abs(t);
			if (cp > 1.0) {
				cp = 1.0;
			}
		} else {
			cp = 1.0;
		}

		/* Calculate weight */
		weight = (Uint8) (cp * 255);
		iweight = 255 - weight;

		/* Left half */
		xx = xc2 - xp;
		yy = yc2 - yp;
		result |= pixelColorWeightNolock(dst, xp, yp, color, iweight);
		result |= pixelColorWeightNolock(dst, xx, yp, color, iweight);

		result |= pixelColorWeightNolock(dst, xp, yy, color, iweight);
		result |= pixelColorWeightNolock(dst, xx, yy, color, iweight);

		/* Right half */
		xx = xc2 - xs;
		result |= pixelColorWeightNolock(dst, xs, yp, color, weight);
		result |= pixelColorWeightNolock(dst, xx, yp, color, weight);

		result |= pixelColorWeightNolock(dst, xs, yy, color, weight);
		result |= pixelColorWeightNolock(dst, xx, yy, color, weight);

	}

	/* Unlock surface */
	if (SDL_MUSTLOCK(dst)) {
		SDL_UnlockSurface(dst);
	}

	return (result);
}

/*!
\brief Draw anti-aliased ellipse with blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the aa-ellipse.
\param y Y coordinate of the center of the aa-ellipse.
\param rx Horizontal radius in pixels of the aa-ellipse.
\param ry Vertical radius in pixels of the aa-ellipse.
\param r The red value of the aa-ellipse to draw. 
\param g The green value of the aa-ellipse to draw. 
\param b The blue value of the aa-ellipse to draw. 
\param a The alpha value of the aa-ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/
int aaellipseRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (aaellipseColor
		(dst, x, y, rx, ry, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ---- Filled Ellipse */

/* Note: */
/* Based on algorithm from sge library with multiple-hline draw removal */
/* and other speedup changes. */

/*!
\brief Draw filled ellipse with blending.

Note: Based on algorithm from sge library with multiple-hline draw removal
and other speedup changes.

\param dst The surface to draw on.
\param x X coordinate of the center of the filled ellipse.
\param y Y coordinate of the center of the filled ellipse.
\param rx Horizontal radius in pixels of the filled ellipse.
\param ry Vertical radius in pixels of the filled ellipse.
\param color The color value of the filled ellipse to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int filledEllipseColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color)
{
	Sint16 left, right, top, bottom;
	int result;
	Sint16 x1, y1, x2, y2;
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph;
	int xmi, xpi;
	int xmj, xpj;
	int xmk, xpk;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Sanity check radii 
	*/
	if ((rx < 0) || (ry < 0)) {
		return (-1);
	}

	/*
	* Special case for rx=0 - draw a vline 
	*/
	if (rx == 0) {
		return (vlineColor(dst, x, y - ry, y + ry, color));
	}
	/*
	* Special case for ry=0 - draw a hline 
	*/
	if (ry == 0) {
		return (hlineColor(dst, x - rx, x + rx, y, color));
	}

	/*
	* Get circle and clipping boundary and 
	* test if bounding box of circle is visible 
	*/
	x2 = x + rx;
	left = dst->clip_rect.x;
	if (x2<left) {
		return(0);
	} 
	x1 = x - rx;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	} 
	y2 = y + ry;
	top = dst->clip_rect.y;
	if (y2<top) {
		return(0);
	} 
	y1 = y - ry;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1>bottom) {
		return(0);
	} 

	/*
	* Init vars 
	*/
	oh = oi = oj = ok = 0xFFFF;

	/*
	* Draw 
	*/
	result = 0;
	if (rx > ry) {
		ix = 0;
		iy = rx * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * ry) / rx;
			k = (i * ry) / rx;

			if ((ok != k) && (oj != k)) {
				xph = x + h;
				xmh = x - h;
				if (k > 0) {
					result |= hlineColor(dst, xmh, xph, y + k, color);
					result |= hlineColor(dst, xmh, xph, y - k, color);
				} else {
					result |= hlineColor(dst, xmh, xph, y, color);
				}
				ok = k;
			}
			if ((oj != j) && (ok != j) && (k != j)) {
				xmi = x - i;
				xpi = x + i;
				if (j > 0) {
					result |= hlineColor(dst, xmi, xpi, y + j, color);
					result |= hlineColor(dst, xmi, xpi, y - j, color);
				} else {
					result |= hlineColor(dst, xmi, xpi, y, color);
				}
				oj = j;
			}

			ix = ix + iy / rx;
			iy = iy - ix / rx;

		} while (i > h);
	} else {
		ix = 0;
		iy = ry * 64;

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * rx) / ry;
			k = (i * rx) / ry;

			if ((oi != i) && (oh != i)) {
				xmj = x - j;
				xpj = x + j;
				if (i > 0) {
					result |= hlineColor(dst, xmj, xpj, y + i, color);
					result |= hlineColor(dst, xmj, xpj, y - i, color);
				} else {
					result |= hlineColor(dst, xmj, xpj, y, color);
				}
				oi = i;
			}
			if ((oh != h) && (oi != h) && (i != h)) {
				xmk = x - k;
				xpk = x + k;
				if (h > 0) {
					result |= hlineColor(dst, xmk, xpk, y + h, color);
					result |= hlineColor(dst, xmk, xpk, y - h, color);
				} else {
					result |= hlineColor(dst, xmk, xpk, y, color);
				}
				oh = h;
			}

			ix = ix + iy / ry;
			iy = iy - ix / ry;

		} while (i > h);
	}

	return (result);
}

/*!
\brief Draw filled ellipse with blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the filled ellipse.
\param y Y coordinate of the center of the filled ellipse.
\param rx Horizontal radius in pixels of the filled ellipse.
\param ry Vertical radius in pixels of the filled ellipse.
\param r The red value of the filled ellipse to draw. 
\param g The green value of the filled ellipse to draw. 
\param b The blue value of the filled ellipse to draw. 
\param a The alpha value of the filled ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/
int filledEllipseRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (filledEllipseColor
		(dst, x, y, rx, ry, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ----- pie */

/*!
\brief Internal float (low-speed) pie-calc implementation by drawing polygons.

Note: Determines vertex array and uses polygon or filledPolygon drawing routines to render.

\param dst The surface to draw on.
\param x X coordinate of the center of the pie.
\param y Y coordinate of the center of the pie.
\param rad Radius in pixels of the pie.
\param start Starting radius in degrees of the pie.
\param end Ending radius in degrees of the pie.
\param color The color value of the pie to draw (0xRRGGBBAA). 
\param filled Flag indicating if the pie should be filled (=1) or not (=0).

\returns Returns 0 on success, -1 on failure.
*/
int _pieColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint32 color, Uint8 filled)
{
	Sint16 left, right, top, bottom;
	Sint16 x1, y1, x2, y2;
	int result;
	double angle, start_angle, end_angle;
	double deltaAngle;
	double dr;
	int numpoints, i;
	Sint16 *vx, *vy;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Sanity check radii 
	*/
	if (rad < 0) {
		return (-1);
	}

	/*
	* Fixup angles
	*/
	start = start % 360;
	end = end % 360;

	/*
	* Special case for rad=0 - draw a point 
	*/
	if (rad == 0) {
		return (pixelColor(dst, x, y, color));
	}

	/*
	* Clip against circle, not pie (not 100% optimal).
	* Get pie's circle and clipping boundary and 
	* test if bounding box of circle is visible
	*/
	x2 = x + rad;
	left = dst->clip_rect.x;
	if (x2<left) {
		return(0);
	} 
	x1 = x - rad;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	} 
	y2 = y + rad;
	top = dst->clip_rect.y;
	if (y2<top) {
		return(0);
	} 
	y1 = y - rad;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1>bottom) {
		return(0);
	} 

	/*
	* Variable setup 
	*/
	dr = (double) rad;
	deltaAngle = 3.0 / dr;
	start_angle = (double) start *(2.0 * M_PI / 360.0);
	end_angle = (double) end *(2.0 * M_PI / 360.0);
	if (start > end) {
		end_angle += (2.0 * M_PI);
	}

	/* We will always have at least 2 points */
	numpoints = 2;

	/* Count points (rather than calculating it) */
	angle = start_angle;
	while (angle < end_angle) {
		angle += deltaAngle;
		numpoints++;
	}

	/* Allocate combined vertex array */
	vx = vy = (Sint16 *) malloc(2 * sizeof(Uint16) * numpoints);
	if (vx == NULL) {
		return (-1);
	}

	/* Update point to start of vy */
	vy += numpoints;

	/* Center */
	vx[0] = x;
	vy[0] = y;

	/* First vertex */
	angle = start_angle;
	vx[1] = x + (int) (dr * cos(angle));
	vy[1] = y + (int) (dr * sin(angle));

	if (numpoints<3)
	{
		result = lineColor(dst, vx[0], vy[0], vx[1], vy[1], color);
	}
	else
	{
		/* Calculate other vertices */
		i = 2;
		angle = start_angle;
		while (angle < end_angle) {
			angle += deltaAngle;
			if (angle>end_angle)
			{
				angle = end_angle;
			}
			vx[i] = x + (int) (dr * cos(angle));
			vy[i] = y + (int) (dr * sin(angle));
			i++;
		}

		/* Draw */
		if (filled) {
			result = filledPolygonColor(dst, vx, vy, numpoints, color);
		} else {
			result = polygonColor(dst, vx, vy, numpoints, color);
		}
	}

	/* Free combined vertex array */
	free(vx);

	return (result);
}

/*!
\brief Draw pie (outline) with alpha blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the pie.
\param y Y coordinate of the center of the pie.
\param rad Radius in pixels of the pie.
\param start Starting radius in degrees of the pie.
\param end Ending radius in degrees of the pie.
\param color The color value of the pie to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int pieColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, 
	Sint16 start, Sint16 end, Uint32 color) 
{
	return (_pieColor(dst, x, y, rad, start, end, color, 0));

}

/*!
\brief Draw pie (outline) with alpha blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the pie.
\param y Y coordinate of the center of the pie.
\param rad Radius in pixels of the pie.
\param start Starting radius in degrees of the pie.
\param end Ending radius in degrees of the pie.
\param r The red value of the pie to draw. 
\param g The green value of the pie to draw. 
\param b The blue value of the pie to draw. 
\param a The alpha value of the pie to draw.

\returns Returns 0 on success, -1 on failure.
*/
int pieRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad,
	Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return (_pieColor(dst, x, y, rad, start, end,
		((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a, 0));

}

/*!
\brief Draw filled pie with alpha blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the filled pie.
\param y Y coordinate of the center of the filled pie.
\param rad Radius in pixels of the filled pie.
\param start Starting radius in degrees of the filled pie.
\param end Ending radius in degrees of the filled pie.
\param color The color value of the filled pie to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int filledPieColor(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint32 color)
{
	return (_pieColor(dst, x, y, rad, start, end, color, 1));
}

/*!
\brief Draw filled pie with alpha blending.

\param dst The surface to draw on.
\param x X coordinate of the center of the filled pie.
\param y Y coordinate of the center of the filled pie.
\param rad Radius in pixels of the filled pie.
\param start Starting radius in degrees of the filled pie.
\param end Ending radius in degrees of the filled pie.
\param r The red value of the filled pie to draw. 
\param g The green value of the filled pie to draw. 
\param b The blue value of the filled pie to draw. 
\param a The alpha value of the filled pie to draw.

\returns Returns 0 on success, -1 on failure.
*/
int filledPieRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad,
	Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return (_pieColor(dst, x, y, rad, start, end,
		((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a, 1));
}

/* ------ Trigon */

/*!
\brief Draw trigon (triangle outline) with alpha blending.

Note: Creates vertex array and uses polygon routine to render.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the trigon.
\param y1 Y coordinate of the first point of the trigon.
\param x2 X coordinate of the second point of the trigon.
\param y2 Y coordinate of the second point of the trigon.
\param x3 X coordinate of the third point of the trigon.
\param y3 Y coordinate of the third point of the trigon.
\param color The color value of the trigon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int trigonColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, Uint32 color)
{
	Sint16 vx[3]; 
	Sint16 vy[3];

	vx[0]=x1;
	vx[1]=x2;
	vx[2]=x3;
	vy[0]=y1;
	vy[1]=y2;
	vy[2]=y3;

	return(polygonColor(dst,vx,vy,3,color));
}

/*!
\brief Draw trigon (triangle outline) with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the trigon.
\param y1 Y coordinate of the first point of the trigon.
\param x2 X coordinate of the second point of the trigon.
\param y2 Y coordinate of the second point of the trigon.
\param x3 X coordinate of the third point of the trigon.
\param y3 Y coordinate of the third point of the trigon.
\param r The red value of the trigon to draw. 
\param g The green value of the trigon to draw. 
\param b The blue value of the trigon to draw. 
\param a The alpha value of the trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int trigonRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Sint16 vx[3]; 
	Sint16 vy[3];

	vx[0]=x1;
	vx[1]=x2;
	vx[2]=x3;
	vy[0]=y1;
	vy[1]=y2;
	vy[2]=y3;

	return(polygonRGBA(dst,vx,vy,3,r,g,b,a));
}				 

/* ------ AA-Trigon */

/*!
\brief Draw anti-aliased trigon (triangle outline) with alpha blending.

Note: Creates vertex array and uses aapolygon routine to render.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the aa-trigon.
\param y1 Y coordinate of the first point of the aa-trigon.
\param x2 X coordinate of the second point of the aa-trigon.
\param y2 Y coordinate of the second point of the aa-trigon.
\param x3 X coordinate of the third point of the aa-trigon.
\param y3 Y coordinate of the third point of the aa-trigon.
\param color The color value of the aa-trigon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int aatrigonColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, Uint32 color)
{
	Sint16 vx[3]; 
	Sint16 vy[3];

	vx[0]=x1;
	vx[1]=x2;
	vx[2]=x3;
	vy[0]=y1;
	vy[1]=y2;
	vy[2]=y3;

	return(aapolygonColor(dst,vx,vy,3,color));
}

/*!
\brief Draw anti-aliased trigon (triangle outline) with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the aa-trigon.
\param y1 Y coordinate of the first point of the aa-trigon.
\param x2 X coordinate of the second point of the aa-trigon.
\param y2 Y coordinate of the second point of the aa-trigon.
\param x3 X coordinate of the third point of the aa-trigon.
\param y3 Y coordinate of the third point of the aa-trigon.
\param r The red value of the aa-trigon to draw. 
\param g The green value of the aa-trigon to draw. 
\param b The blue value of the aa-trigon to draw. 
\param a The alpha value of the aa-trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int aatrigonRGBA(SDL_Surface * dst,  Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Sint16 vx[3]; 
	Sint16 vy[3];

	vx[0]=x1;
	vx[1]=x2;
	vx[2]=x3;
	vy[0]=y1;
	vy[1]=y2;
	vy[2]=y3;

	return(aapolygonRGBA(dst,vx,vy,3,r,g,b,a));
}				   

/* ------ Filled Trigon */

/*!
\brief Draw filled trigon (triangle) with alpha blending.

Note: Creates vertex array and uses aapolygon routine to render.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the filled trigon.
\param y1 Y coordinate of the first point of the filled trigon.
\param x2 X coordinate of the second point of the filled trigon.
\param y2 Y coordinate of the second point of the filled trigon.
\param x3 X coordinate of the third point of the filled trigon.
\param y3 Y coordinate of the third point of the filled trigon.
\param color The color value of the filled trigon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int filledTrigonColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3, Uint32 color)
{
	Sint16 vx[3]; 
	Sint16 vy[3];

	vx[0]=x1;
	vx[1]=x2;
	vx[2]=x3;
	vy[0]=y1;
	vy[1]=y2;
	vy[2]=y3;

	return(filledPolygonColor(dst,vx,vy,3,color));
}

/*!
\brief Draw filled trigon (triangle) with alpha blending.

Note: Creates vertex array and uses aapolygon routine to render.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the filled trigon.
\param y1 Y coordinate of the first point of the filled trigon.
\param x2 X coordinate of the second point of the filled trigon.
\param y2 Y coordinate of the second point of the filled trigon.
\param x3 X coordinate of the third point of the filled trigon.
\param y3 Y coordinate of the third point of the filled trigon.
\param r The red value of the filled trigon to draw. 
\param g The green value of the filled trigon to draw. 
\param b The blue value of the filled trigon to draw. 
\param a The alpha value of the filled trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int filledTrigonRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 x3, Sint16 y3,
	Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Sint16 vx[3]; 
	Sint16 vy[3];

	vx[0]=x1;
	vx[1]=x2;
	vx[2]=x3;
	vy[0]=y1;
	vy[1]=y2;
	vy[2]=y3;

	return(filledPolygonRGBA(dst,vx,vy,3,r,g,b,a));
}

/* ---- Polygon */

/*!
\brief Draw polygon with alpha blending.

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the polygon.
\param vy Vertex array containing Y coordinates of the points of the polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param color The color value of the polygon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int polygonColor(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color)
{
	int result;
	int i;
	const Sint16 *x1, *y1, *x2, *y2;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Vertex array NULL check 
	*/
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
	* Sanity check 
	*/
	if (n < 3) {
		return (-1);
	}

	/*
	* Pointer setup 
	*/
	x1 = x2 = vx;
	y1 = y2 = vy;
	x2++;
	y2++;

	/*
	* Draw 
	*/
	result = 0;
	for (i = 1; i < n; i++) {
		result |= lineColor(dst, *x1, *y1, *x2, *y2, color);
		x1 = x2;
		y1 = y2;
		x2++;
		y2++;
	}
	result |= lineColor(dst, *x1, *y1, *vx, *vy, color);

	return (result);
}

/*!
\brief Draw polygon with alpha blending.

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the polygon.
\param vy Vertex array containing Y coordinates of the points of the polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the polygon to draw. 
\param g The green value of the polygon to draw. 
\param b The blue value of the polygon to draw. 
\param a The alpha value of the polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int polygonRGBA(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (polygonColor(dst, vx, vy, n, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ---- AA-Polygon */

/*!
\brief Draw anti-aliased polygon with alpha blending.

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the aa-polygon.
\param vy Vertex array containing Y coordinates of the points of the aa-polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param color The color value of the aa-polygon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int aapolygonColor(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color)
{
	int result;
	int i;
	const Sint16 *x1, *y1, *x2, *y2;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Vertex array NULL check 
	*/
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
	* Sanity check 
	*/
	if (n < 3) {
		return (-1);
	}

	/*
	* Pointer setup 
	*/
	x1 = x2 = vx;
	y1 = y2 = vy;
	x2++;
	y2++;

	/*
	* Draw 
	*/
	result = 0;
	for (i = 1; i < n; i++) {
		result |= _aalineColor(dst, *x1, *y1, *x2, *y2, color, 0);
		x1 = x2;
		y1 = y2;
		x2++;
		y2++;
	}
	result |= _aalineColor(dst, *x1, *y1, *vx, *vy, color, 0);

	return (result);
}

/*!
\brief Draw anti-aliased polygon with alpha blending.

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the aa-polygon.
\param vy Vertex array containing Y coordinates of the points of the aa-polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the aa-polygon to draw. 
\param g The green value of the aa-polygon to draw. 
\param b The blue value of the aa-polygon to draw. 
\param a The alpha value of the aa-polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int aapolygonRGBA(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (aapolygonColor(dst, vx, vy, n, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ---- Filled Polygon */

/*!
\brief Internal helper qsort callback functions used in filled polygon drawing.

\param a The surface to draw on.
\param b Vertex array containing X coordinates of the points of the polygon.

\returns Returns 0 if a==b, a negative number if a<b or a positive number if a>b.
*/
int _gfxPrimitivesCompareInt(const void *a, const void *b)
{
	return (*(const int *) a) - (*(const int *) b);
}

/*!
\brief Global vertex array to use if optional parameters are not given in filledPolygonMT calls.

Note: Used for non-multithreaded (default) operation of filledPolygonMT.
*/
static int *gfxPrimitivesPolyIntsGlobal = NULL;

/*!
\brief Flag indicating if global vertex array was already allocated.

Note: Used for non-multithreaded (default) operation of filledPolygonMT.
*/
static int gfxPrimitivesPolyAllocatedGlobal = 0;

/*!
\brief Draw filled polygon with alpha blending (multi-threaded capable).

Note: The last two parameters are optional; but are required for multithreaded operation.  

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param color The color value of the filled polygon to draw (0xRRGGBBAA). 
\param polyInts Preallocated, temporary vertex array used for sorting vertices. Required for multithreaded operation; set to NULL otherwise.
\param polyAllocated Flag indicating if temporary vertex array was allocated. Required for multithreaded operation; set to NULL otherwise.

\returns Returns 0 on success, -1 on failure.
*/
int filledPolygonColorMT(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color, int **polyInts, int *polyAllocated)
{
	int result;
	int i;
	int y, xa, xb;
	int miny, maxy;
	int x1, y1;
	int x2, y2;
	int ind1, ind2;
	int ints;
	int *gfxPrimitivesPolyInts = NULL;
	int *gfxPrimitivesPolyIntsNew = NULL;
	int gfxPrimitivesPolyAllocated = 0;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Vertex array NULL check 
	*/
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
	* Sanity check number of edges
	*/
	if (n < 3) {
		return -1;
	}

	/*
	* Map polygon cache  
	*/
	if ((polyInts==NULL) || (polyAllocated==NULL)) {
		/* Use global cache */
		gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = gfxPrimitivesPolyAllocatedGlobal;
	} else {
		/* Use local cache */
		gfxPrimitivesPolyInts = *polyInts;
		gfxPrimitivesPolyAllocated = *polyAllocated;
	}

	/*
	* Allocate temp array, only grow array 
	*/
	if (!gfxPrimitivesPolyAllocated) {
		gfxPrimitivesPolyInts = (int *) malloc(sizeof(int) * n);
		gfxPrimitivesPolyAllocated = n;
	} else {
		if (gfxPrimitivesPolyAllocated < n) {
			gfxPrimitivesPolyIntsNew = (int *) realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
			if (!gfxPrimitivesPolyIntsNew) {
				if (!gfxPrimitivesPolyInts) {
					free(gfxPrimitivesPolyInts);
					gfxPrimitivesPolyInts = NULL;
				}
				gfxPrimitivesPolyAllocated = 0;
			} else {
				gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
				gfxPrimitivesPolyAllocated = n;
			}
		}
	}

	/*
	* Check temp array
	*/
	if (gfxPrimitivesPolyInts==NULL) {        
		gfxPrimitivesPolyAllocated = 0;
	}

	/*
	* Update cache variables
	*/
	if ((polyInts==NULL) || (polyAllocated==NULL)) { 
		gfxPrimitivesPolyIntsGlobal =  gfxPrimitivesPolyInts;
		gfxPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
	} else {
		*polyInts = gfxPrimitivesPolyInts;
		*polyAllocated = gfxPrimitivesPolyAllocated;
	}

	/*
	* Check temp array again
	*/
	if (gfxPrimitivesPolyInts==NULL) {        
		return(-1);
	}

	/*
	* Determine Y maxima 
	*/
	miny = vy[0];
	maxy = vy[0];
	for (i = 1; (i < n); i++) {
		if (vy[i] < miny) {
			miny = vy[i];
		} else if (vy[i] > maxy) {
			maxy = vy[i];
		}
	}

	/*
	* Draw, scanning y 
	*/
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			} else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			} else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			} else {
				continue;
			}
			if ( ((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)) ) {
				gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			} 	    
		}

		qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

		for (i = 0; (i < ints); i += 2) {
			xa = gfxPrimitivesPolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = gfxPrimitivesPolyInts[i+1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= hlineColor(dst, xa, xb, y, color);
		}
	}

	return (result);
}

/*!
\brief Draw filled polygon with alpha blending (multi-threaded capable).

Note: The last two parameters are optional; but are required for multithreaded operation.  

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the filled polygon to draw. 
\param g The green value of the filled polygon to draw. 
\param b The blue value of the filed polygon to draw. 
\param a The alpha value of the filled polygon to draw.
\param polyInts Preallocated, temporary vertex array used for sorting vertices. Required for multithreaded operation; set to NULL otherwise.
\param polyAllocated Flag indicating if temporary vertex array was allocated. Required for multithreaded operation; set to NULL otherwise.

\returns Returns 0 on success, -1 on failure.
*/
int filledPolygonRGBAMT(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated)
{
	/*
	* Draw 
	*/
	return (filledPolygonColorMT(dst, vx, vy, n, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a, polyInts, polyAllocated));
}

/*!
\brief Draw filled polygon with alpha blending.

Note: Standard filledPolygon function is calling multithreaded version with NULL parameters
to use the global vertex cache.

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param color The color value of the filled polygon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int filledPolygonColor(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color)
{
	/*
	* Draw 
	*/
	return (filledPolygonColorMT(dst, vx, vy, n, color, NULL, NULL));
}

/*!
\brief Draw filled polygon with alpha blending.

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the filled polygon to draw. 
\param g The green value of the filled polygon to draw. 
\param b The blue value of the filed polygon to draw. 
\param a The alpha value of the filled polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/
int filledPolygonRGBA(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (filledPolygonColorMT(dst, vx, vy, n, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a, NULL, NULL));
}

/*!
\brief Internal function to draw a textured horizontal line.

\param dst The surface to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.
\param texture The texture surface to retrieve color information from.
\param texture_dx The X offset for the texture lookup.
\param texture_dy The Y offset for the textured lookup.

\returns Returns 0 on success, -1 on failure.
*/
int _HLineTextured(SDL_Surface * dst, Sint16 x1, Sint16 x2, Sint16 y, SDL_Surface *texture, int texture_dx, int texture_dy)
{
	Sint16 left, right, top, bottom;
	Sint16 w;
	Sint16 xtmp;
	int result = 0;
	int texture_x_walker;    
	int texture_y_start;    
	SDL_Rect source_rect,dst_rect;
	int pixels_written,write_width;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Swap x1, x2 if required to ensure x1<=x2
	*/
	if (x1 > x2) {
		xtmp = x1;
		x1 = x2;
		x2 = xtmp;
	}

	/*
	* Get clipping boundary and
	* check visibility of hline 
	*/
	left = dst->clip_rect.x;
	if (x2<left) {
		return(0);
	}
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1>right) {
		return(0);
	}
	top = dst->clip_rect.y;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if ((y<top) || (y>bottom)) {
		return (0);
	}

	/*
	* Clip x 
	*/
	if (x1 < left) {
		x1 = left;
	}
	if (x2 > right) {
		x2 = right;
	}

	/*
	* Calculate width to draw
	*/
	w = x2 - x1 + 1;

	/*
	* Determine where in the texture we start drawing
	*/
	texture_x_walker =   (x1 - texture_dx)  % texture->w;
	if (texture_x_walker < 0){
		texture_x_walker = texture->w + texture_x_walker ;
	}

	texture_y_start = (y + texture_dy) % texture->h;
	if (texture_y_start < 0){
		texture_y_start = texture->h + texture_y_start;
	}

	// setup the source rectangle; we are only drawing one horizontal line
	source_rect.y = texture_y_start;
	source_rect.x = texture_x_walker;
	source_rect.h = 1;

	// we will draw to the current y
	dst_rect.y = y;

	// if there are enough pixels left in the current row of the texture
	// draw it all at once
	if (w <= texture->w -texture_x_walker){
		source_rect.w = w;
		source_rect.x = texture_x_walker;
		dst_rect.x= x1;
		result = (SDL_BlitSurface  (texture, &source_rect , dst, &dst_rect) == 0);
	} else { // we need to draw multiple times
		// draw the first segment
		pixels_written = texture->w  - texture_x_walker;
		source_rect.w = pixels_written;
		source_rect.x = texture_x_walker;
		dst_rect.x= x1;
		result |= (SDL_BlitSurface (texture, &source_rect , dst, &dst_rect) == 0);
		write_width = texture->w;

		// now draw the rest
		// set the source x to 0
		source_rect.x = 0;
		while (pixels_written < w){
			if (write_width >= w - pixels_written) {
				write_width =  w - pixels_written;
			}
			source_rect.w = write_width;
			dst_rect.x = x1 + pixels_written;
			result  |= (SDL_BlitSurface  (texture,&source_rect , dst, &dst_rect) == 0);
			pixels_written += write_width;
		}
	}

	return result;
}

/*!
\brief Draws a polygon filled with the given texture (Multi-Threading Capable). 

This operation use internally SDL_BlitSurface for lines of the source texture. It supports
alpha drawing.

To get the best performance of this operation you need to make sure the texture and the dst surface have the same format
(see  http://docs.mandragor.org/files/Common_libs_documentation/SDL/SDL_Documentation_project_en/sdlblitsurface.html).
The last two parameters are optional, but required for multithreaded operation. When set to NULL, uses global static temp array.

\param dst the destination surface, 
\param vx array of x vector components
\param vy array of x vector components
\param n the amount of vectors in the vx and vy array
\param texture the sdl surface to use to fill the polygon
\param texture_dx the offset of the texture relative to the screeen. if you move the polygon 10 pixels 
to the left and want the texture to apear the same you need to increase the texture_dx value
\param texture_dy see texture_dx
\param polyInts preallocated temp array storage for vertex sorting (used for multi-threaded operation)
\param polyAllocated flag indicating oif the temp array was allocated (used for multi-threaded operation)

\returns Returns 0 on success, -1 on failure.
*/
int texturedPolygonMT(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, 
	SDL_Surface * texture, int texture_dx, int texture_dy, int **polyInts, int *polyAllocated)
{
	int result;
	int i;
	int y, xa, xb;
	int minx,maxx,miny, maxy;
	int x1, y1;
	int x2, y2;
	int ind1, ind2;
	int ints;
	int *gfxPrimitivesPolyInts = NULL;
	int gfxPrimitivesPolyAllocated = 0;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Sanity check number of edges
	*/
	if (n < 3) {
		return -1;
	}

	/*
	* Map polygon cache  
	*/
	if ((polyInts==NULL) || (polyAllocated==NULL)) {
		/* Use global cache */
		gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = gfxPrimitivesPolyAllocatedGlobal;
	} else {
		/* Use local cache */
		gfxPrimitivesPolyInts = *polyInts;
		gfxPrimitivesPolyAllocated = *polyAllocated;
	}

	/*
	* Allocate temp array, only grow array 
	*/
	if (!gfxPrimitivesPolyAllocated) {
		gfxPrimitivesPolyInts = (int *) malloc(sizeof(int) * n);
		gfxPrimitivesPolyAllocated = n;
	} else {
		if (gfxPrimitivesPolyAllocated < n) {
			gfxPrimitivesPolyInts = (int *) realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
			gfxPrimitivesPolyAllocated = n;
		}
	}

	/*
	* Check temp array
	*/
	if (gfxPrimitivesPolyInts==NULL) {        
		gfxPrimitivesPolyAllocated = 0;
	}

	/*
	* Update cache variables
	*/
	if ((polyInts==NULL) || (polyAllocated==NULL)) { 
		gfxPrimitivesPolyIntsGlobal =  gfxPrimitivesPolyInts;
		gfxPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
	} else {
		*polyInts = gfxPrimitivesPolyInts;
		*polyAllocated = gfxPrimitivesPolyAllocated;
	}

	/*
	* Check temp array again
	*/
	if (gfxPrimitivesPolyInts==NULL) {        
		return(-1);
	}

	/*
	* Determine X,Y minima,maxima 
	*/
	miny = vy[0];
	maxy = vy[0];
	minx = vx[0];
	maxx = vx[0];
	for (i = 1; (i < n); i++) {
		if (vy[i] < miny) {
			miny = vy[i];
		} else if (vy[i] > maxy) {
			maxy = vy[i];
		}
		if (vx[i] < minx) {
			minx = vx[i];
		} else if (vx[i] > maxx) {
			maxx = vx[i];
		}
	}
	if (maxx <0 || minx > dst->w){
		return -1;
	}
	if (maxy <0 || miny > dst->h){
		return -1;
	}

	/*
	* Draw, scanning y 
	*/
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			} else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			} else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			} else {
				continue;
			}
			if ( ((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)) ) {
				gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			} 
		}

		qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

		for (i = 0; (i < ints); i += 2) {
			xa = gfxPrimitivesPolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = gfxPrimitivesPolyInts[i+1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= _HLineTextured(dst, xa, xb, y, texture, texture_dx, texture_dy);
		}
	}

	return (result);
}

/*!
\brief Draws a polygon filled with the given texture. 

This standard version is calling multithreaded versions with NULL cache parameters.

\param dst the destination surface, 
\param vx array of x vector components
\param vy array of x vector components
\param n the amount of vectors in the vx and vy array
\param texture the sdl surface to use to fill the polygon
\param texture_dx the offset of the texture relative to the screeen. if you move the polygon 10 pixels 
to the left and want the texture to apear the same you need to increase the texture_dx value
\param texture_dy see texture_dx

\returns Returns 0 on success, -1 on failure.
*/
int texturedPolygon(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, SDL_Surface *texture, int texture_dx, int texture_dy)
{
	/*
	* Draw
	*/
	return (texturedPolygonMT(dst, vx, vy, n, texture, texture_dx, texture_dy, NULL, NULL));
}


/* ---- Character */

/*!
\brief Global cache for NxM pixel font surfaces created at runtime.
*/
static SDL_Surface *gfxPrimitivesFont[256];

/*!
\brief Global cache of the color used for the font surfaces created at runtime.
*/
static Uint32 gfxPrimitivesFontColor[256];

/*!
\brief Pointer to the current font data. Default is a 8x8 pixel internal font. 
*/
static const unsigned char *currentFontdata = gfxPrimitivesFontdata;

/*!
\brief Width of the current font. Default is 8. 
*/
static Uint32 charWidth = 8;

/*!
\brief Height of the current font. Default is 8. 
*/
static Uint32 charHeight = 8;

/*!
\brief Width for rendering. Autocalculated.
*/
static Uint32 charWidthLocal = 8;

/*!
\brief Height for rendering. Autocalculated.
*/
static Uint32 charHeightLocal = 8;

/*!
\brief Pitch of the current font in bytes. Default is 1. 
*/
static Uint32 charPitch = 1;

/*!
\brief Characters 90deg clockwise rotations. Default is 0. Max is 3. 
*/
static Uint32 charRotation = 0;

/*!
\brief Character data size in bytes of the current font. Default is 8. 
*/
static Uint32 charSize = 8;

/*!
\brief Sets or resets the current global font data.

The font data array is organized in follows: 
[fontdata] = [character 0][character 1]...[character 255] where
[character n] = [byte 1 row 1][byte 2 row 1]...[byte {pitch} row 1][byte 1 row 2] ...[byte {pitch} row height] where
[byte n] = [bit 0]...[bit 7] where 
[bit n] = [0 for transparent pixel|1 for colored pixel]

\param fontdata Pointer to array of font data. Set to NULL, to reset global font to the default 8x8 font.
\param cw Width of character in bytes. Ignored if fontdata==NULL.
\param ch Height of character in bytes. Ignored if fontdata==NULL.
*/
void gfxPrimitivesSetFont(const void *fontdata, Uint32 cw, Uint32 ch)
{
	int i;

	if ((fontdata) && (cw) && (ch)) {
		currentFontdata = fontdata;
		charWidth = cw;
		charHeight = ch;
	} else {
		currentFontdata = gfxPrimitivesFontdata;
		charWidth = 8;
		charHeight = 8;
	}

	charPitch = (charWidth+7)/8;
	charSize = charPitch * charHeight;

	/* Maybe flip width/height for rendering */
	if ((charRotation==1) || (charRotation==3))
	{
		charWidthLocal = charHeight;
		charHeightLocal = charWidth;
	}
	else
	{
		charWidthLocal = charWidth;
		charHeightLocal = charHeight;
	}

	/* Clear character cache */
	for (i = 0; i < 256; i++) {
		if (gfxPrimitivesFont[i]) {
			SDL_FreeSurface(gfxPrimitivesFont[i]);
			gfxPrimitivesFont[i] = NULL;
		}
	}
}

/*!
\brief Sets current global font character rotation steps. 

Default is 0 (no rotation). 1 = 90deg clockwise. 2 = 180deg clockwise. 3 = 270deg clockwise.
Changing the rotation, will reset the character cache.

\param rotation Number of 90deg clockwise steps to rotate
*/
void gfxPrimitivesSetFontRotation(Uint32 rotation)
{
	int i;

	rotation = rotation & 3;
	if (charRotation != rotation)
	{
		/* Store rotation */
		charRotation = rotation;

		/* Maybe flip width/height for rendering */
		if ((charRotation==1) || (charRotation==3))
		{
			charWidthLocal = charHeight;
			charHeightLocal = charWidth;
		}
		else
		{
			charWidthLocal = charWidth;
			charHeightLocal = charHeight;
		}

		/* Clear character cache */
		for (i = 0; i < 256; i++) {
			if (gfxPrimitivesFont[i]) {
				SDL_FreeSurface(gfxPrimitivesFont[i]);
				gfxPrimitivesFont[i] = NULL;
			}
		}
	}
}

/*!
\brief Draw a character of the currently set font.

On first call for a particular character and color combination, the function needs to
generate the character surface (slower. Subsequent calls blit a cached surface (fast). 
Uses alpha blending if A<255 in color.

\param dst The surface to draw on.
\param x X (horizontal) coordinate of the upper left corner of the character.
\param y Y (vertical) coordinate of the upper left corner of the character.
\param c The character to draw.
\param color The color value of the character to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int characterColor(SDL_Surface * dst, Sint16 x, Sint16 y, char c, Uint32 color)
{
	Sint16 left, right, top, bottom;
	Sint16 x1, y1, x2, y2;
	SDL_Rect srect;
	SDL_Rect drect;
	int result;
	Uint32 ix, iy;
	const unsigned char *charpos;
	Uint8 *curpos;
	int forced_redraw;
	Uint8 patt, mask;
	Uint8 *linepos;
	Uint32 pitch;
	SDL_Surface *rotatedCharacter;
	Uint32 ci;

	/*
	* Check visibility of clipping rectangle
	*/
	if ((dst->clip_rect.w==0) || (dst->clip_rect.h==0)) {
		return(0);
	}

	/*
	* Get text and clipping boundary and
	* test if bounding box of character is visible 
	*/

	left = dst->clip_rect.x;
	x2 = x + charWidthLocal;
	if (x2<left) {
		return(0);
	} 
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	x1 = x;
	if (x1>right) {
		return(0);
	} 
	top = dst->clip_rect.y;
	y2 = y + charHeightLocal;
	if (y2<top) {
		return(0);
	} 
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	y1 = y;
	if (y1>bottom) {
		return(0);
	} 

	/*
	* Setup source rectangle
	*/
	srect.x = 0;
	srect.y = 0;
	srect.w = charWidthLocal;
	srect.h = charHeightLocal;

	/*
	* Setup destination rectangle
	*/
	drect.x = x;
	drect.y = y;
	drect.w = charWidthLocal;
	drect.h = charHeightLocal;

	/* Character index in cache */
	ci = (unsigned char) c;

	/*
	* Create new charWidth x charHeight bitmap surface if not already present.
	* Might get rotated later.
	*/
	if (gfxPrimitivesFont[ci] == NULL) {
		gfxPrimitivesFont[ci] =
			SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_HWSURFACE | SDL_SRCALPHA,
			charWidth, charHeight, 32,
			0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		/*
		* Check pointer 
		*/
		if (gfxPrimitivesFont[ci] == NULL) {
			return (-1);
		}
		/*
		* Definitely redraw 
		*/
		forced_redraw = 1;
	} else {
		forced_redraw = 0;
	}

	/*
	* Check if color has changed 
	*/
	if ((gfxPrimitivesFontColor[ci] != color) || (forced_redraw)) {
		/*
		* Redraw character 
		*/
		SDL_SetAlpha(gfxPrimitivesFont[ci], SDL_SRCALPHA, 255);
		gfxPrimitivesFontColor[ci] = color;

		/* Lock font-surface */
		if (SDL_LockSurface(gfxPrimitivesFont[ci]) != 0)
			return (-1);

		/*
		* Variable setup 
		*/
		charpos = currentFontdata + ci * charSize;
		linepos = (Uint8 *) gfxPrimitivesFont[ci]->pixels;
		pitch = gfxPrimitivesFont[ci]->pitch;

		/*
		* Drawing loop 
		*/
		patt = 0;
		for (iy = 0; iy < charHeight; iy++) {
			mask = 0x00;
			curpos = linepos;
			for (ix = 0; ix < charWidth; ix++) {
				if (!(mask >>= 1)) {
					patt = *charpos++;
					mask = 0x80;
				}

				if (patt & mask)
					*(Uint32 *)curpos = color;
				else
					*(Uint32 *)curpos = 0;
				curpos += 4;
			}
			linepos += pitch;
		}

		/* Unlock font-surface */
		SDL_UnlockSurface(gfxPrimitivesFont[ci]);

		/* Maybe rotate and replace cached image */
		if (charRotation>0)
		{
			rotatedCharacter = rotateSurface90Degrees(gfxPrimitivesFont[ci], charRotation);
			SDL_FreeSurface(gfxPrimitivesFont[ci]);
			gfxPrimitivesFont[ci] = rotatedCharacter;
		}
	}

	/*
	* Draw bitmap onto destination surface 
	*/
	result = SDL_BlitSurface(gfxPrimitivesFont[ci], &srect, dst, &drect);

	return (result);
}

/*!
\brief Draw a character of the currently set font.

\param dst The surface to draw on.
\param x X (horizontal) coordinate of the upper left corner of the character.
\param y Y (vertical) coordinate of the upper left corner of the character.
\param c The character to draw.
\param r The red value of the character to draw. 
\param g The green value of the character to draw. 
\param b The blue value of the character to draw. 
\param a The alpha value of the character to draw.

\returns Returns 0 on success, -1 on failure.
*/
int characterRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, char c, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (characterColor(dst, x, y, c, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/*!
\brief Draw a string in the currently set font.

The spacing between consequtive characters in the string is the fixed number of pixels 
of the character width of the current global font.

\param dst The surface to draw on.
\param x X (horizontal) coordinate of the upper left corner of the string.
\param y Y (vertical) coordinate of the upper left corner of the string.
\param s The string to draw.
\param color The color value of the string to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int stringColor(SDL_Surface * dst, Sint16 x, Sint16 y, const char *s, Uint32 color)
{
	int result = 0;
	Sint16 curx = x;
	Sint16 cury = y;
	const char *curchar = s;

	while (*curchar && !result) {
		result |= characterColor(dst, curx, cury, *curchar, color);
		switch (charRotation)
		{
		case 0:
			curx += charWidthLocal;
			break;
		case 2:
			curx -= charWidthLocal;
			break;
		case 1:
			cury += charHeightLocal;
			break;
		case 3:
			cury -= charHeightLocal;
			break;
		}
		curchar++;
	}

	return (result);
}

/*!
\brief Draw a string in the currently set font.

\param dst The surface to draw on.
\param x X (horizontal) coordinate of the upper left corner of the string.
\param y Y (vertical) coordinate of the upper left corner of the string.
\param s The string to draw.
\param r The red value of the string to draw. 
\param g The green value of the string to draw. 
\param b The blue value of the string to draw. 
\param a The alpha value of the string to draw.

\returns Returns 0 on success, -1 on failure.
*/
int stringRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, const char *s, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (stringColor(dst, x, y, s, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

/* ---- Bezier curve */

/*!
\brief Internal function to calculate bezier interpolator of data array with ndata values at position 't'.

\param data Array of values.
\param ndata Size of array.
\param t Position for which to calculate interpolated value. t should be between [0, ndata].

\returns Interpolated value at position t, value[0] when t<0, value[n-1] when t>n.
*/
double _evaluateBezier (double *data, int ndata, double t) 
{
	double mu, result;
	int n,k,kn,nn,nkn;
	double blend,muk,munk;

	/* Sanity check bounds */
	if (t<0.0) {
		return(data[0]);
	}
	if (t>=(double)ndata) {
		return(data[ndata-1]);
	}

	/* Adjust t to the range 0.0 to 1.0 */ 
	mu=t/(double)ndata;

	/* Calculate interpolate */
	n=ndata-1;
	result=0.0;
	muk = 1;
	munk = pow(1-mu,(double)n);
	for (k=0;k<=n;k++) {
		nn = n;
		kn = k;
		nkn = n - k;
		blend = muk * munk;
		muk *= mu;
		munk /= (1-mu);
		while (nn >= 1) {
			blend *= nn;
			nn--;
			if (kn > 1) {
				blend /= (double)kn;
				kn--;
			}
			if (nkn > 1) {
				blend /= (double)nkn;
				nkn--;
			}
		}
		result += data[k] * blend;
	}

	return (result);
}

/*!
\brief Draw a bezier curve with alpha blending.

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the bezier curve.
\param vy Vertex array containing Y coordinates of the points of the bezier curve.
\param n Number of points in the vertex array. Minimum number is 3.
\param s Number of steps for the interpolation. Minimum number is 2.
\param color The color value of the bezier curve to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int bezierColor(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, int s, Uint32 color)
{
	int result;
	int i;
	double *x, *y, t, stepsize;
	Sint16 x1, y1, x2, y2;

	/*
	* Sanity check 
	*/
	if (n < 3) {
		return (-1);
	}
	if (s < 2) {
		return (-1);
	}

	/*
	* Variable setup 
	*/
	stepsize=(double)1.0/(double)s;

	/* Transfer vertices into float arrays */
	if ((x=(double *)malloc(sizeof(double)*(n+1)))==NULL) {
		return(-1);
	}
	if ((y=(double *)malloc(sizeof(double)*(n+1)))==NULL) {
		free(x);
		return(-1);
	}    
	for (i=0; i<n; i++) {
		x[i]=(double)vx[i];
		y[i]=(double)vy[i];
	}      
	x[n]=(double)vx[0];
	y[n]=(double)vy[0];

	/*
	* Draw 
	*/
	result = 0;
	t=0.0;
	x1=(Sint16)lrint(_evaluateBezier(x,n+1,t));
	y1=(Sint16)lrint(_evaluateBezier(y,n+1,t));
	for (i = 0; i <= (n*s); i++) {
		t += stepsize;
		x2=(Sint16)_evaluateBezier(x,n,t);
		y2=(Sint16)_evaluateBezier(y,n,t);
		result |= lineColor(dst, x1, y1, x2, y2, color);
		x1 = x2;
		y1 = y2;
	}

	/* Clean up temporary array */
	free(x);
	free(y);

	return (result);
}

/*!
\brief Draw a bezier curve with alpha blending.

\param dst The surface to draw on.
\param vx Vertex array containing X coordinates of the points of the bezier curve.
\param vy Vertex array containing Y coordinates of the points of the bezier curve.
\param n Number of points in the vertex array. Minimum number is 3.
\param s Number of steps for the interpolation. Minimum number is 2.
\param r The red value of the bezier curve to draw. 
\param g The green value of the bezier curve to draw. 
\param b The blue value of the bezier curve to draw. 
\param a The alpha value of the bezier curve to draw.

\returns Returns 0 on success, -1 on failure.
*/
int bezierRGBA(SDL_Surface * dst, const Sint16 * vx, const Sint16 * vy, int n, int s, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*
	* Draw 
	*/
	return (bezierColor(dst, vx, vy, n, s, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}


/*!
\brief Internal function to initialize the Bresenham line iterator.

Example of use:
SDL_gfxBresenhamIterator b;
_bresenhamInitialize (&b, x1, y1, x2, y2);
do { 
plot(b.x, b.y); 
} while (_bresenhamIterate(&b)==0); 

\param b Pointer to struct for bresenham line drawing state.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.

\returns Returns 0 on success, -1 on failure.
*/
int _bresenhamInitialize(SDL_gfxBresenhamIterator *b, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2)
{
	int temp;

	if (b==NULL) {
		return(-1);
	}

	b->x = x1;
	b->y = y1;

	/* dx = abs(x2-x1), s1 = sign(x2-x1) */
	if ((b->dx = x2 - x1) != 0) {
		if (b->dx < 0) {
			b->dx = -b->dx;
			b->s1 = -1;
		} else {
			b->s1 = 1;
		}
	} else {
		b->s1 = 0;	
	}

	/* dy = abs(y2-y1), s2 = sign(y2-y1)    */
	if ((b->dy = y2 - y1) != 0) {
		if (b->dy < 0) {
			b->dy = -b->dy;
			b->s2 = -1;
		} else {
			b->s2 = 1;
		}
	} else {
		b->s2 = 0;	
	}

	if (b->dy > b->dx) {
		temp = b->dx;
		b->dx = b->dy;
		b->dy = temp;
		b->swapdir = 1;
	} else {
		b->swapdir = 0;
	}

	b->count = (b->dx<0) ? 0 : (unsigned int)b->dx;
	b->dy <<= 1;
	b->error = b->dy - b->dx;
	b->dx <<= 1;	

	return(0);
}


/*!
\brief Internal function to move Bresenham line iterator to the next position.

Maybe updates the x and y coordinates of the iterator struct.

\param b Pointer to struct for bresenham line drawing state.

\returns Returns 0 on success, 1 if last point was reached, 2 if moving past end-of-line, -1 on failure.
*/
int _bresenhamIterate(SDL_gfxBresenhamIterator *b)
{	
	if (b==NULL) {
		return (-1);
	}

	/* last point check */
	if (b->count==0) {
		return (2);
	}

	while (b->error >= 0) {
		if (b->swapdir) {
			b->x += b->s1;
		} else  {
			b->y += b->s2;
		}

		b->error -= b->dx;
	}

	if (b->swapdir) {
		b->y += b->s2;
	} else {
		b->x += b->s1;
	}

	b->error += b->dy;	
	b->count--;		

	/* count==0 indicates "end-of-line" */
	return ((b->count) ? 0 : 1);
}


/*!
\brief Internal function to to draw parallel lines with Murphy algorithm.

\param m Pointer to struct for murphy iterator.
\param x X coordinate of point.
\param y Y coordinate of point.
\param d1 Direction square/diagonal.
*/
void _murphyParaline(SDL_gfxMurphyIterator *m, Sint16 x, Sint16 y, int d1)
{
	int p;
	d1 = -d1;

	/*
	* Lock the surface 
	*/
	if (SDL_MUSTLOCK(m->dst)) {
		SDL_LockSurface(m->dst);
	}

	for (p = 0; p <= m->u; p++) {

		pixelColorNolock(m->dst, x, y, m->color);

		if (d1 <= m->kt) {
			if (m->oct2 == 0) {
				x++;
			} else {
				if (m->quad4 == 0) {
					y++;
				} else {
					y--;
				}
			}
			d1 += m->kv;
		} else {	
			x++;
			if (m->quad4 == 0) {
				y++;
			} else {
				y--;
			}
			d1 += m->kd;
		}
	}

	/* Unlock surface */
	if (SDL_MUSTLOCK(m->dst)) {
		SDL_UnlockSurface(m->dst);
	}

	m->tempx = x;
	m->tempy = y;
}

/*!
\brief Internal function to to draw one iteration of the Murphy algorithm.

\param m Pointer to struct for murphy iterator.
\param miter Iteration count.
\param ml1bx X coordinate of a point.
\param ml1by Y coordinate of a point.
\param ml2bx X coordinate of a point.
\param ml2by Y coordinate of a point.
\param ml1x X coordinate of a point.
\param ml1y Y coordinate of a point.
\param ml2x X coordinate of a point.
\param ml2y Y coordinate of a point.

*/
void _murphyIteration(SDL_gfxMurphyIterator *m, Uint8 miter, 
	Uint16 ml1bx, Uint16 ml1by, Uint16 ml2bx, Uint16 ml2by, 
	Uint16 ml1x, Uint16 ml1y, Uint16 ml2x, Uint16 ml2y)
{
	int atemp1, atemp2;
	int ftmp1, ftmp2;
	Uint16 m1x, m1y, m2x, m2y;	
	Uint16 fix, fiy, lax, lay, curx, cury;
	Uint16 px[4], py[4];
	SDL_gfxBresenhamIterator b;

	if (miter > 1) {
		if (m->first1x != -32768) {
			fix = (m->first1x + m->first2x) / 2;
			fiy = (m->first1y + m->first2y) / 2;
			lax = (m->last1x + m->last2x) / 2;
			lay = (m->last1y + m->last2y) / 2;
			curx = (ml1x + ml2x) / 2;
			cury = (ml1y + ml2y) / 2;

			atemp1 = (fix - curx);
			atemp2 = (fiy - cury);
			ftmp1 = atemp1 * atemp1 + atemp2 * atemp2;
			atemp1 = (lax - curx);
			atemp2 = (lay - cury);
			ftmp2 = atemp1 * atemp1 + atemp2 * atemp2;

			if (ftmp1 <= ftmp2) {
				m1x = m->first1x;
				m1y = m->first1y;
				m2x = m->first2x;
				m2y = m->first2y;
			} else {
				m1x = m->last1x;
				m1y = m->last1y;
				m2x = m->last2x;
				m2y = m->last2y;
			}

			atemp1 = (m2x - ml2x);
			atemp2 = (m2y - ml2y);
			ftmp1 = atemp1 * atemp1 + atemp2 * atemp2;
			atemp1 = (m2x - ml2bx);
			atemp2 = (m2y - ml2by);
			ftmp2 = atemp1 * atemp1 + atemp2 * atemp2;

			if (ftmp2 >= ftmp1) {
				ftmp1 = ml2bx;
				ftmp2 = ml2by;
				ml2bx = ml2x;
				ml2by = ml2y;
				ml2x = ftmp1;
				ml2y = ftmp2;
				ftmp1 = ml1bx;
				ftmp2 = ml1by;
				ml1bx = ml1x;
				ml1by = ml1y;
				ml1x = ftmp1;
				ml1y = ftmp2;
			}

			/*
			* Lock the surface 
			*/
			if (SDL_MUSTLOCK(m->dst)) {
				SDL_LockSurface(m->dst);
			}

			_bresenhamInitialize(&b, m2x, m2y, m1x, m1y);
			do {
				pixelColorNolock(m->dst, b.x, b.y, m->color);
			} while (_bresenhamIterate(&b)==0);

			_bresenhamInitialize(&b, m1x, m1y, ml1bx, ml1by);
			do {
				pixelColorNolock(m->dst, b.x, b.y, m->color);
			} while (_bresenhamIterate(&b)==0);

			_bresenhamInitialize(&b, ml1bx, ml1by, ml2bx, ml2by);
			do {
				pixelColorNolock(m->dst, b.x, b.y, m->color);
			} while (_bresenhamIterate(&b)==0);

			_bresenhamInitialize(&b, ml2bx, ml2by, m2x, m2y);
			do {
				pixelColorNolock(m->dst, b.x, b.y, m->color);
			} while (_bresenhamIterate(&b)==0);

			/* Unlock surface */
			if (SDL_MUSTLOCK(m->dst)) {
				SDL_UnlockSurface(m->dst);
			}

			px[0] = m1x;
			px[1] = m2x;
			px[2] = ml1bx;
			px[3] = ml2bx;
			py[0] = m1y;
			py[1] = m2y;
			py[2] = ml1by;
			py[3] = ml2by;			
			polygonColor(m->dst, px, py, 4, m->color);						
		}
	}

	m->last1x = ml1x;
	m->last1y = ml1y;
	m->last2x = ml2x;
	m->last2y = ml2y;
	m->first1x = ml1bx;
	m->first1y = ml1by;
	m->first2x = ml2bx;
	m->first2y = ml2by;
}


#define HYPOT(x,y) sqrt((double)(x)*(double)(x)+(double)(y)*(double)(y)) 

/*!
\brief Internal function to to draw wide lines with Murphy algorithm.

Draws lines parallel to ideal line.

\param m Pointer to struct for murphy iterator.
\param x1 X coordinate of first point.
\param y1 Y coordinate of first point.
\param x2 X coordinate of second point.
\param y2 Y coordinate of second point.
\param width Width of line.
\param miter Iteration count.

*/
void _murphyWideline(SDL_gfxMurphyIterator *m, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, Uint8 miter)
{	
	float offset = (float)width / 2.f;

	Sint16 temp;
	Sint16 ptx, pty, ptxx, ptxy, ml1x, ml1y, ml2x, ml2y, ml1bx, ml1by, ml2bx, ml2by;

	int d0, d1;		/* difference terms d0=perpendicular to line, d1=along line */

	int q;			/* pel counter,q=perpendicular to line */
	int tmp;

	int dd;			/* distance along line */
	int tk;			/* thickness threshold */
	double ang;		/* angle for initial point calculation */
	double sang, cang;

	/* Initialisation */
	m->u = x2 - x1;	/* delta x */
	m->v = y2 - y1;	/* delta y */

	if (m->u < 0) {	/* swap to make sure we are in quadrants 1 or 4 */
		temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y1;
		y1 = y2;
		y2 = temp;		
		m->u *= -1;
		m->v *= -1;
	}

	if (m->v < 0) {	/* swap to 1st quadrant and flag */
		m->v *= -1;
		m->quad4 = 1;
	} else {
		m->quad4 = 0;
	}

	if (m->v > m->u) {	/* swap things if in 2 octant */
		tmp = m->u;
		m->u = m->v;
		m->v = tmp;
		m->oct2 = 1;
	} else {
		m->oct2 = 0;
	}

	m->ku = m->u + m->u;	/* change in l for square shift */
	m->kv = m->v + m->v;	/* change in d for square shift */
	m->kd = m->kv - m->ku;	/* change in d for diagonal shift */
	m->kt = m->u - m->kv;	/* diag/square decision threshold */

	d0 = 0;
	d1 = 0;
	dd = 0;

	ang = atan((double) m->v / (double) m->u);	/* calc new initial point - offset both sides of ideal */	
	sang = sin(ang);
	cang = cos(ang);

	if (m->oct2 == 0) {
		ptx = x1 + (Sint16)lrint(offset * sang);
		if (m->quad4 == 0) {
			pty = y1 - (Sint16)lrint(offset * cang);
		} else {
			pty = y1 + (Sint16)lrint(offset * cang);
		}
	} else {
		ptx = x1 - (Sint16)lrint(offset * cang);
		if (m->quad4 == 0) {
			pty = y1 + (Sint16)lrint(offset * sang);
		} else {
			pty = y1 - (Sint16)lrint(offset * sang);
		}
	}

	/* used here for constant thickness line */
	tk = (int) (4. * HYPOT(ptx - x1, pty - y1) * HYPOT(m->u, m->v));

	if (miter == 0) {
		m->first1x = -32768;
		m->first1y = -32768;
		m->first2x = -32768;
		m->first2y = -32768;
		m->last1x = -32768;
		m->last1y = -32768;
		m->last2x = -32768;
		m->last2y = -32768;
	}
	ptxx = ptx;
	ptxy = pty;

	for (q = 0; dd <= tk; q++) {	/* outer loop, stepping perpendicular to line */

		_murphyParaline(m, ptx, pty, d1);	/* call to inner loop - right edge */
		if (q == 0) {
			ml1x = ptx;
			ml1y = pty;
			ml1bx = m->tempx;
			ml1by = m->tempy;
		} else {
			ml2x = ptx;
			ml2y = pty;
			ml2bx = m->tempx;
			ml2by = m->tempy;
		}
		if (d0 < m->kt) {	/* square move */
			if (m->oct2 == 0) {
				if (m->quad4 == 0) {
					pty++;
				} else {
					pty--;
				}
			} else {
				ptx++;
			}
		} else {	/* diagonal move */
			dd += m->kv;
			d0 -= m->ku;
			if (d1 < m->kt) {	/* normal diagonal */
				if (m->oct2 == 0) {
					ptx--;
					if (m->quad4 == 0) {
						pty++;
					} else {
						pty--;
					}
				} else {
					ptx++;
					if (m->quad4 == 0) {
						pty--;
					} else {
						pty++;
					}
				}
				d1 += m->kv;
			} else {	/* double square move, extra parallel line */
				if (m->oct2 == 0) {
					ptx--;
				} else {
					if (m->quad4 == 0) {
						pty--;
					} else {
						pty++;
					}
				}
				d1 += m->kd;
				if (dd > tk) {
					_murphyIteration(m, miter, ml1bx, ml1by, ml2bx, ml2by, ml1x, ml1y, ml2x, ml2y);
					return;	/* breakout on the extra line */
				}
				_murphyParaline(m, ptx, pty, d1);
				if (m->oct2 == 0) {
					if (m->quad4 == 0) {
						pty++;
					} else {

						pty--;
					}
				} else {
					ptx++;
				}
			}
		}
		dd += m->ku;
		d0 += m->kv;
	}

	_murphyIteration(m, miter, ml1bx, ml1by, ml2bx, ml2by, ml1x, ml1y, ml2x, ml2y);
}


/*!
\brief Draw a thick line with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.
\param width Width of the line in pixels. Must be >0.
\param color The color value of the line to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/
int thickLineColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, Uint32 color)
{	
	int wh;
	SDL_gfxMurphyIterator m;

	if (dst == NULL) return -1;
	if (width < 1) return -1;

	/* Special case: thick "point" */
	if ((x1 == x2) && (y1 == y2)) {
		wh = width / 2;
		return boxColor(dst, x1 - wh, y1 - wh, x2 + width, y2 + width, color);		
	}

	m.dst = dst;
	m.color = color;

	_murphyWideline(&m, x1, y1, x2, y2, width, 0);
	_murphyWideline(&m, x1, y1, x2, y2, width, 1);

	return(0);
}

/*!
\brief Draw a thick line with alpha blending.

\param dst The surface to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.
\param width Width of the line in pixels. Must be >0.
\param r The red value of the character to draw. 
\param g The green value of the character to draw. 
\param b The blue value of the character to draw. 
\param a The alpha value of the character to draw.

\returns Returns 0 on success, -1 on failure.
*/	
int thickLineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 width, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return (thickLineColor(dst, x1, y1, x2, y2, width, 
		((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}
