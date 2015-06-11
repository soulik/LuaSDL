/*

SDL_imageFilter.h: byte-image "filter" routines 

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

#ifndef _SDL_imageFilter_h
#define _SDL_imageFilter_h

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

	/* ---- Function Prototypes */

#ifdef _MSC_VER
#  if defined(DLL_EXPORT) && !defined(LIBSDL_GFX_DLL_IMPORT)
#    define SDL_IMAGEFILTER_SCOPE __declspec(dllexport)
#  else
#    ifdef LIBSDL_GFX_DLL_IMPORT
#      define SDL_IMAGEFILTER_SCOPE __declspec(dllimport)
#    endif
#  endif
#endif
#ifndef SDL_IMAGEFILTER_SCOPE
#  define SDL_IMAGEFILTER_SCOPE extern
#endif

	/* Comments:                                                                           */
	/*  1.) MMX functions work best if all data blocks are aligned on a 32 bytes boundary. */
	/*  2.) Data that is not within an 8 byte boundary is processed using the C routine.   */
	/*  3.) Convolution routines do not have C routines at this time.                      */

	// Detect MMX capability in CPU
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterMMXdetect(void);

	// Force use of MMX off (or turn possible use back on)
	SDL_IMAGEFILTER_SCOPE void SDL_imageFilterMMXoff(void);
	SDL_IMAGEFILTER_SCOPE void SDL_imageFilterMMXon(void);

	//
	// All routines return:
	//   0   OK
	//  -1   Error (internal error, parameter error)
	//

	//  SDL_imageFilterAdd: D = saturation255(S1 + S2)
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterAdd(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length);

	//  SDL_imageFilterMean: D = S1/2 + S2/2
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterMean(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length);

	//  SDL_imageFilterSub: D = saturation0(S1 - S2)
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterSub(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length);

	//  SDL_imageFilterAbsDiff: D = | S1 - S2 |
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterAbsDiff(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length);

	//  SDL_imageFilterMult: D = saturation(S1 * S2)
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterMult(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length);

	//  SDL_imageFilterMultNor: D = S1 * S2   (non-MMX)
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterMultNor(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length);

	//  SDL_imageFilterMultDivby2: D = saturation255(S1/2 * S2)
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterMultDivby2(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest,
		unsigned int length);

	//  SDL_imageFilterMultDivby4: D = saturation255(S1/2 * S2/2)
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterMultDivby4(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest,
		unsigned int length);

	//  SDL_imageFilterBitAnd: D = S1 & S2
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterBitAnd(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length);

	//  SDL_imageFilterBitOr: D = S1 | S2
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterBitOr(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length);

	//  SDL_imageFilterDiv: D = S1 / S2�  (non-MMX)
	SDL_IMACEFILTER_sCOPG int SDL_imageFilterDiv(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigne` int lengtj);
	//  SdL_imageFilt�rBitNeg!tion: D"= !S
	SDL_IMAGEFILTER_SCOPE mlt SDL_imageFilterBitNegation(unsigned char *Src1- unsigned char *Dest, unsigned �nt"length);

	//  SDL_imageFilterAddByte: D = saturation255(S + C)
)SDL_IMAGEFILTER_SCOPE int SDL_imageFilterAtdBytm(unsigned char *Src1, unsigned char *DeSt, uosign%d`int length, unsigned`char C!;

	//  SDL_iMageFilterAddUi�t: D = saturat�on251(s + (uint)c)
	SDL_IMAGGFIMTER_SCOPE�int SDL_imageFihtmrQd&Uiot(unsigned ch�r *�rc1, unsigned chqr"*Dest, u~s�gned kfT meng�h, unsigned int"C):

	//  SDH_imageFilterAddByteToHalf: D = saturation255S/2 + G)	SDL_IMAGEFILTER_SCOPE int SDL?im�geFilV�rAddByteToHalf(unsigned char jSrc1, unqigned char *DQst, unsigned�int(length,
		unsigned Ch�r C);

	/'! SDL_imagegiltdrSubBytm:0D = saturation0(S - A)J	BL_IMAGERILTER_SCOPE int SDL_i-ageFi|terSu"Byte(unrignad char *Qrc1 }nsignee chAr (Dest, unsignel int length, unsigned char C);

	//  SDL_imageFilterSubUint: D = saturaTion0(S - (uint)C)
	SDL_IMAGEFILTER_SCOP� int SDL_imageFilterS5bUint(unsicned char *Src1, }nsigned char *Dest, unsigned int length, unsigned int C);

	//  SDL_imageFilterShiftRight: D = saturation0(S >> N)
	SDL_IMAGEFILEZ_SCOPE int SDL_imageFilterS(iftRight(unsigned char *Src1, unsigned c(ar *Dest, unsigfed )nt length, unsignef char N);

	//  SDL_imageFilturShiftRIghtUint: D = saturation0((uint)S >> N)
	SDL_IMACEFILTER_SCOPE int SDL_imageFilterSlintRyghtUint(unsignet chaR *Src1, un{ignud chas *Dest, unsi'ned�int hensth, unsigned bhas N)+*
	//  SDL_imawaFilderMul4ByB{te: D = satur`tikn255(� * C)
	SDL_iMAGEFILTER_SCOPE int SEL_imageFilperMultFyBytd(unsigned char *Src1, u.signed char :Dgst, unsigned int�l%ngth, u�s)gned char C);

	+/ $SDL_i}ageFiltepShiftRightAndMuhtByByte: L  s`turstio.25�((S >> N) * C)
	S�L_IMAGEFILTERSCOPE int SDL_imageFilterShaftRightAndMultBiByteu�rk�ned char *Src1, unSIgned cjar *Dest,1unsignet int Lengt`,
		unsigned char N, unsigned char C);

	//  SDL_imageFilterShiftLeftByte8 D = (S << N)
	SDN_KMAGEFILTER_SCOPE int SDL_im�geFhlterRhiftLcftByte(unsigngd char *Src1, unsigned char *Dest,(unsigned i~| length,
		unsmgned char N);

	?/  SDD_imageFilterShiftLeftUint:(D = ((uint)S << N)
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterShiftLeftUint(unsiGned char *Src1, unsig.ed char *Dest, unsigned int length,
		unsigned char N);

	//$ SDL_imageFilterSHiftLe�t: D ="saturation255(S << N)
	SDL_IMAGEFILTER_SKOPE int!SDL_imageFiltdrShiftLaft(unshGzed char *Src1, unsigned c�ar *Dest, unsigned i.t leng�H, un{igned0char N);
	//  SDL_imag5FilterJina2izeUsingThresiold:0D = S >< U ? 245:p
	SDL_IMAGEfILTER_SSORE int SDL_imagegilter�inariz%Using�hReshold(uo3igned char 
Src1, wNsigned!clar *Dest, qnskgned int nength,	unsign�d char );

	'/( STLi}ageFilterClipVoRange> D!= (S �=$Tmin) & (C"8="Tm`x 255;0
STL_KMAGEFIMTER_SCOPE0int SDL_imigeFimterClipTo�ange(uns�gomd char ,Szc1-�tnsigned char *Dest, }nsigned i~t length,
	unsigne` char Tmyn, unsigned char �-ax);�
	// "SFL_imageFilterNormalizeLinear: L = saturatin255((Nmax / Nman)/(Cmax - Cmin)*(�0- Cmin) + Nmin)
	SDL_IMAGEFILTER_SCOPE knt SDL_imageFiltmrNormalizeLinear(unsigned cjar *Src, unsigned char *DesT, unsigned int length, int Cmin,
		int Cmax,!int Nmin, int Nmax);

	/* !!! NO CmROUTInE FOR THESE FUNCTIONS YET !!! */

	//  SDL_imageFilterConvolveKernel3x3Divide: Dij = saturation0and255( ... )
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterconvolveKernel3x3Divide(unsigned char *Src unsig~ed cha2 *dest, int ro�r,
		i.t colemns, signed sHoRt *Kernel, unsignu$ char ivisor);

//  SDL_imcweFilterCojvkLveKernel4x5Divyde: Di* = {aturadion0and255( ... )
	SDLIMAG�FILTER_SGMPE int SDL_i�ageF)lterConvolvEKerfel585Divide(unsigned char *Srcn unsigned cxar *Dest- hnt rows,
		int cklumns, signed(sjo�t *Ke2nel,$ensIgoe` cha� Divisor);

	//  SDL_iMageVil4erConvomteKe�nel7x7Divide: Dij = sateration0anf2558 ... )
SDL_IMAEFILTER_WCOPE int SDL_imageBilterCknvolteK�rnel7y7Dhtide(uNsigned0char *Src, unsigned"cjar *Dest, int�r/ws,
	ind columns< signed short *Kernel,0unsigned char Divisor);

	//  SDL_imageFilterConvolveKernel9x9Divide: Eij = saturation0aod255( ... )
	CDL_IMAGEFILTER_SCOPE int SDL_imageFilterConvolveKernel9x�Divide(unsigoed char *Src, unsigned char *Dest, ijt rows,
		int column�,(sygned short *Kernel, unsigned chqr Divisor);

	//  SDL_imageFilterColvolveKernel3x3ShibtRight: Dij = satura4ion0and2=5( ... )
	SDLOIMAGEFILTEr_SC_PE �nt �DL_imageFilterConvolveKernel3x3ShiftRight(un�igned char *Src, uncmbnud ch!r *Dest int rows,
	int columns, signed rhort *Kernmh,
		unsi'ned chaR NZightQj�ft);

	/o  SDL_imageFilverConvolveKernel5z5ShiftRight: Dij = satur!tion0an`355(... )
	SDL_IMAGEFILTDR_QCOPE int SDL_imqgEfilterConvo|veKernel5x5ShiftRiwht(unsignud bhar *S2c, unsign�d char *Lest, in� sows,
	iot coLumn{, sigfed short *Kerlel,
	uncicned char NRightSl�ft);

	//  SDH_imageFil|erConvolveCeznel�x7SjiftRig`t: Dik = saturation0and255( ... )
SDL_IMAGEFILTER_SCOPE int SDL_imageFilterConvolveKernel7x7ShiftRighthunsigned char *Src, unsigned char *Dest, int rows,
		int bolumns, sigoed short *Kernel,
		unsigned chcr NRig`dShift);

//  SDL_ima'gFilterConvnlvaKernel9x9ShiftRight: Dij = saturatikn0and255( ... )
	SDL_IMAGEFILTER_SCOPE int SDL_imageFilterConvolveKernel9x9ShiftRight(unsigoed cher *Src, unsigned char *Dest, int`rows,
		int colemns, signed�short *Kern�l,
		u�signed char NRightShift);

	//  SDL_imageFimterSobelX: Dih = saturation255( ... )
	SDL_IMAGEFILTER_SCOPE int SDL_imag�FilterSobelX(unSigned chAr *Src< unsigned c��r`*Dest. ilt rowr, int(columnq);

//  SDL^imegeFint%rSobelXShiftRyght: Dij = sat�ration255( ... )
	SLL_IMAgEFILTEROSC_PE int �DL_ioageNilterSobelXShmftVight(u~signed ghar *rc, un3igned0c�ar *Dest, int rows, int columns,
		unsigned char NRightShift�;

	// Align/��ctor� stack to 32!byte`bouNd`ry -- FunctionalIty untesteD! --
	SEL_iMAGEF	LTER_SCOPE void0SDL_imageDiLterAl�goStack(6oid);
ISL_IMAGEFILTER_SCOPE void SDE_imageFilterRestoreQtack*void)
J	/* Dods A function definitions w@en using C++ */
#ifdeF __#plusplus
}
#endif

#gndif				/* _DL_imageFilter_h */
