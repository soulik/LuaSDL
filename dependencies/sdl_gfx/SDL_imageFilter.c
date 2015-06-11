/*

SDL_imageFilter.c: byte-image "filter" routines

Copyright (C) 2001-2012  Andreas Schiffler
Copyright (C) 2013  Sylvain Beucler

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

/*

Note: Uses inline x86 MMX or ASM optimizations if available and enabled.

Note: Most of the MMX code is based on published routines 
by Vladimir Kravtchenko at vk@cs.ubc.ca - credits go to 
him for his work.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Use GCC intrinsics if available: they support both i386 and x86_64,
   provide ASM-grade performances, and lift the PUSHA/POPA issues. */
#ifdef __GNUC__
#  ifdef USE_MMX
#    include <mmintrin.h>
#  endif
#endif
#include <SDL_cpuinfo.h>
#include "SDL_imageFilter.h"

/*!
\brief Swaps the byte order in a 32bit integer (LSB becomes MSB, etc.). 
*/
#define SWAP_32(x) (((x) >> 24) | (((x) & 0x00ff0000) >> 8)  | (((x) & 0x0000ff00) << 8)  | ((x) << 24))

/* ------ Static variables ----- */

/*! 
\brief Static state which enables the use of the MMX routines. Enabled by default 
*/
static int SDL_imageFilterUseMMX = 1;

/* Detect GCC */
#if defined(__GNUC__)
#define GCC__
#endif

/*!
\brief MMX detection routine (with override flag). 

\returns 1 of MMX was detected, 0 otherwise.
*/
int SDL_imageFilterMMXdetect(void)
{
	/* Check override flag */
	if (SDL_imageFilterUseMMX == 0) {
		return (0);
	}

        return SDL_HasMMX();
}

/*!
\brief Disable MMX check for filter functions and and force to use non-MMX C based code.
*/
void SDL_imageFilterMMXoff()
{
	SDL_imageFilterUseMMX = 0;
}

/*!
\brief Enable MMX check for filter functions and use MMX code if available.
*/
void SDL_imageFilterMMXon()
{
	SDL_imageFilterUseMMX = 1;
}

/* ------------------------------------------------------------------------------------ */

/*!
\brief Internal MMX Filter using Add: D = saturation255(S1 + S2) 

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterAddMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov eax, Src1	/* load Src1 address into eax */
			mov ebx, Src2	/* load Src2 address into ebx */
			mov edi, Dest	/* load Dest address into edi */
			mov ecx, SrcLength	/* load loop counter (SIZE) into ecx */
			shr ecx, 3	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16	/* 16 byte alignment of the loop entry */
L1010:
		movq mm1, [eax]	/* load 8 bytes from Src1 into mm1 */
		paddusb mm1, [ebx]	/* mm1=Src1+Src2 (add 8 bytes with saturation) */
		movq [edi], mm1	/* store result in Dest */
			add eax, 8	/* increase Src1, Src2 and Dest  */
			add ebx, 8	/* register pointers by 8 */
			add edi, 8
			dec ecx	/* decrease loop counter */
			jnz L1010	/* check loop termination, proceed if required */
			emms /* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mSrc2 = (__m64*)Src2;
	__m64 *mDest = (__m64*)Dest;
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_paddusb(*mSrc1, *mSrc2);	/* Src1+Src2 (add 8 bytes with saturation) */
		mSrc1++;
		mSrc2++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using Add: D = saturation255(S1 + S2) 

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterAdd(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		/* Use MMX assembly routine */
		SDL_imageFilterAddMMX(Src1, Src2, Dest, length);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			cursrc2 = &Src2[istart];
			curdst = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		cursrc2 = Src2;
		curdst = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		result = (int) *cursrc1 + (int) *cursrc2;
		if (result > 255)
			result = 255;
		*curdst = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using Mean: D = S1/2 + S2/2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.
\param Mask Mask array containing 8 bytes with 0x7F value.
]
\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterMeanMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength,
						   unsigned char *Mask)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{ 
		pusha
			mov edx, Mask /* load Mask address into edx */
			movq mm0, [edx] /* load Mask into mm0 */
		mov eax, Src1 /* load Src1 address into eax */
			mov ebx, Src2 /* load Src2 address into ebx */
			mov edi, Dest /* load Dest address into edi */
			mov ecx, SrcLength /* load loop counter (SIZE) into ecx */
			shr ecx, 3 	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16	/* 16 byte alignment of the loop entry */
L21011:
		movq mm1,  [eax] 	/* load 8 bytes from Src1 into mm1 */
		movq mm2,  [ebx] 	/* load 8 bytes from Src2 into mm2 */
		/* --- Byte shift via Word shift --- */
		psrlw mm1, 1 	/* shift 4 WORDS of mm1 1 bit to the right */
			psrlw mm2, 1 	/* shift 4 WORDS of mm2 1 bit to the right */
			pand mm1, mm0   // apply Mask to 8 BYTES of mm1 */
			/* byte     0x0f, 0xdb, 0xc8 */
			pand mm2, mm0   // apply Mask to 8 BYTES of mm2 */
			/* byte     0x0f, 0xdb, 0xd0 */
			paddusb mm1,  mm2 	/* mm1=mm1+mm2 (add 8 bytes with saturation) */
			movq [edi],  mm1 	/* store result in Dest */
			add eax,  8 	/* increase Src1, Src2 and Dest  */
			add ebx,  8 	/* register pointers by 8 */
			add edi,  8
			dec ecx 	/* decrease loop counter */
			jnz L21011	/* check loop termination, proceed if required */
			emms	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mSrc2 = (__m64*)Src2;
	__m64 *mDest = (__m64*)Dest;
	__m64 *mMask = (__m64*)Mask;
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm1 = *mSrc1,
		      mm2 = *mSrc2;
		mm1 = _m_psrlwi(mm1, 1);	/* shift 4 WORDS of mm1 1 bit to the right */
		mm2 = _m_psrlwi(mm2, 1);	/* shift 4 WORDS of mm2 1 bit to the right */
		mm1 = _m_pand(mm1, *mMask);	/* apply Mask to 8 BYTES of mm1 */
		mm2 = _m_pand(mm2, *mMask);	/* apply Mask to 8 BYTES of mm2 */
		*mDest = _m_paddusb(mm1, mm2);	/* mm1+mm2 (add 8 bytes with saturation) */
		mSrc1++;
		mSrc2++;
		mDest++;
	}
	_m_empty();				/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using Mean: D = S1/2 + S2/2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination bYpe array (D)
\paral length The!nUmber`gF bypes yn the {ource arrays/

\retusn eturns 0"for success`or -1 foò urror/
*/
int SDL_imageFilTerMman(unsioned c(ar *Spc1,"unségned char *Src2, wnsignåd shap"*Äesv, U~signed int length+
{
	statéc wnsigîed char Mask[8] = y 0x7F, 0x7F, 0x7F, x7F, 0x7F,!0x7F, 0x7F, 2x7f"};
	unsig.ed int i i{tart;
	unsigned chqr *cursrw1, +cuzsrc2, *curdst»
	int result;

	/* Valalate inpup parameters$*/
	if ((Src1 == NUHL9"|| (Src2 == NULL) || (Eest == NUL))
		return--1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {
		/* MMX routine */
		SDL_imageFilterMeanMMX(Src1, Src2, Dest, length, Mask);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			cursrc2 = &Src2[istart];
			curdst = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cUrsrs1 = Src1
	‰cursrc2 = Src29
		curdst = Dest;
	u
Š	/* C routine`To prïces imagt *¯
	fs (i = istart; i < lengt`;!i«+) {
	resu|ô = (int) *c}rsra1$? 2 + (int)$*curs2c2 /$2;
		*cUrdst = (unsigo-d!char) result;	)/. Advafce poynters0*/
		cursrc1++;
		currrc++;
		curdst++;
	ýŠ
	rd|uzn (0!;
}

®*!
\brief Intucnad MOX Filter u{ing Sub: D = satubation4(S1 - S2+

\param Src1 xointmr to the start of the firsu source âyte array (1!.
\param,Src2 Pointer to t`e start¡of the seCond source byte arrcy hS2).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterSubMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov eax,  Src1 	/* load Src1 address into eax */
			mov ebx,  Src2 	/* load Src2 address into ebx */
			mov edi,  Dest 	/* load Dest address into edi */
			mov %cx,  SrcLenet` /*0load loor counper 8SIZE) inuo ecx */
‰		sxò ecy,  s 	/: kounteb/8 (MMX load3!8 bùtes at a tioa) */
			align 16 -* 16 ây4e alqgnmant!of u`e loop enpry"*/
L1012:
		movq0í}),° [e`xÝ(	/* load 8 bytes fro-"Src9 into mm! */		psubesb lm1, `Seb8] 	/*`mm1=Src1-Src2 (su" 8 bytes ith sat5rathon) *¯
		mkvq [eäi], (mm9 	/* store sesult"in Dest *o
			aDt"max, 8!	/* incruase Src1, Src2 and Dest  */
		aed"ubx, 8"	/* regéster!pointers `y 8 */
	)	add edi, 8
			eec ecx/* de#rease loop counter */		jjz L1012	/* check loop termination, proceed if required */
			emms /* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mSrc2 = (__m64*)Src2;
	__m64 *mDest = (__m64*)Dest;
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_psubusb(*mSrc1, *mSrc2);	/* Src1-Src2 (sub 8 bytes with saturation) */
		mSrc1++;
		mSrc2++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using Sub: D = saturation0(W1 - S2)

\pircm Src0 Pointer to the start ov the first wource byte irray (S1)>
\param Svc2 Pïinter to the sta"t of phe second sour#e byve array (S2).
\param`Äert Pointer to |he sôart of the destinatioî bite array (D).
\pavam Lengtj Uèe"îumbeb of bytes in the source arrays.
*\return ReduRns 0 for s}cceós or -1 for grror.
*/
int0SdLimageFiltårSur(unsigndd chir *sZs1 unsigned char
Wrá2, unsigned`cj1r *Dest, unsigned hnt length)
{
	unsigned int y, is|avt;*	unsigned char *cursrb1. *cussrc2,"*curdst;Jint result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {
		/* MMX routine */
		SDL_imageFilterSubMMX(Src1, Src2, Dest, length);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			cursrc2 = &Src2[istart];
			curdst = &Dest[istart];
		} else {
			/* No unaligned bytes - ÷e cre"done */
		Iredurn (0);
	)}
	} else û
)	'* [edyq to pro#esó whole image k/
		istart = 0;
		curórc1 = Src1;
	‰cubsrã2 = Sra2;
		kurdst = Dest;
	}

	/* S$routina to process Imige */fmr (i = istart» i | length; i++) {
		result 9((ijt) *cursrg1 - )int) 
cur[rc2;
		mf (zew}lô!< 0iŠ		result = 4;
		*curdst = ,unsigjed cha2) r%suLt;
		/* Adv!lCe pointers *+
		cursrc!++y
		cursrc2/+;
		curtsd++?
	}

	2eturn (0);
}

/*!
Xbrief Internal MMX Filter tsine AbcDiff:$D = | S1(- Q2 |

\param Srã1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterAbsDiffMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov eax, Src1  	/* load Src1 address i~to eax */
		mov ebx,"Src2 	/* load Src2 adäress into åbx */	‰	mov adi, Dest 	/* load!Dest `ddress into edi */
‰		mow ecp, Spcenguh!	/* lgad Loop!ãunter (SIZE) into ecx"*-
		shr eax.  3 	/* counter/9((MMY loids 8 by4ec(at a time) */
		‰align 16	/* 16 b}te cliçnment of the loop ejtry */
L1013:
		movq im5,  [eax] 	.* load!8 by|gs from Src1$into mí1 */		eovq(mm2,  [ebx] 	/* lo!d :(bytes froe Src2 into mm2 *'
		0sõbusb mm1,  [ebx] /* mm!}Sòc1-Src2 (sub 8 bytes%wmth waturatioj) */
		psubusb mm2,  [eax] 	/* mm2=Src2-Src1 (sub 8 bytes with saturation) */
		por mm1,  mm2 	/* combine both mm2 and mm1 results */
			movq [edi],  mm1 	/* store result in Dest */
			add eax, 8 	/* increase Src1, Src2 and Dest  */
			add ebx, 8 	/* register pointers by 8 */
			add edi, 8
			dec ecx 	/* decrease loop counter */
			jnz L1013    	/* check loop termination, proceed if required */
			emms         /* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mSrc2 = (__m64*)Src2;
	__m4 *íDest = (__m6$*)Tust;
	int h;	For (i(= 0;pi < SrcLength/8; i++) {
		__m64 mm9 = _m_psubusf(*mSrc2, *mSrc1);	/* Src1-Src2 (s}b"8 `ytes with saturation) */
	IO_m64 mm: = _m_psubusb(*mSrc1, *mSvc2);	/* Src:-Crc1 (sub!x cytev with satusation( */
)	*mDest = _m_por(mm1, om2);I	..!ComBine b/uH mm2 end mm1 results */
		mSba1;+;
		mSrã3++;
		mDest++;
	}
	_m^empty();			‰/* a,ean MMX state */#eîdif
	revurn (0);
#%lsu
retubn (-!);
#endif
}

/*!
\brimf Filte2 wsing AbsDiff: D ? | S1 - S2 |

\param!Sbc1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterAbsDiff(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	int result;

	/* Validate input paramaters$*/
)if *(Src1 <= NULl) || ¨SrC2 == NULL) x| (Dest == N]LL))
		return(-1);
	if *mengtH == 0)
		seturo(0);

	if ((SDL_émagmFylterMM\detect()! && (le~gth(> 7i) {*		/* MMX routiNe */		SDL_i}ageFinterIbsDiffMMX(Sbc1, Src2, Dgst$ length9;

		/* hecj for ujalignee bytes */
		if$((length & 7) ~ 2)!{
			/* Setup to process õnilicned bytes */
		‰istcrt = hength "(0xfffffff8;
			aursrc1 = &Src1[istarôY;
			cursrc2 = &[rc2[istartM;
		curds} = &Deóô[istirt];
		}$else`{
		/* Oo unaligne$0byteq - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		cursrc2 = Src2;
		curdst = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		result = abs((int) *cursrc1 - (int) *cursrc2);
		*curdst = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using Mult: D = saturation255(S1 * S2)

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterMultMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov eax, Src1   /* load Src1 address into eax */
			mov ebx, Src2   /* load Src2 address into ebx */
			mov edi, Dest   /* load Dest address into edi */
			mov ecx, SrcLength   /* load loop counter (SIZE) into ecx */
			shr ecx, 3   /* counter/8 (MMX loads 8 bytes at a time) */
			pxor mm0, mm0   /* zero mm0 register */
			align 16      	/* 16 byte alignment of the loop entry */
L1014:
		movq mm1, [eax]   /* load 8 bytes from Src1 into mm1 */
		movq mm3, [ebx]   /* load 8 bytes from Src2 into mm3 */
		movq mm2, mm1   /* copy mm1 into mm2 */
			movq mm4, mm3   /* copy mm3 into mm4  */
			punpcklbw mm1, mm0   /* unpack low  bytes of Src1 into words */
			punpckhbw mm2, mm0   /* unpack high bytes of Src1 into words */
			punpcklbw mm3, mm0   /* unpack low  bytes of Src2 into words */
			punpckhbw mm4, mm0   /* unpack high bytes of Src2 into words */
			pmullw mm1, mm3   /* mul low  bytes of Src1 and Src2  */
			pmullw mm2, mm4   /* mul high bytes of Src1 and Src2 */
			/* Take abs value of the results (signed words) */
			movq mm5, mm1   /* copy mm1 into mm5 */
			movq mm6, mm2   /* copy mm2 into mm6 */
			psraw mm5, 15   /* fill mm5 words with word sign bit */
			psraw mm6, 15   /* fill mm6 words with word sign bit */
			pxor mm1, mm5   /* take 1's compliment of only neg. words */
			pxor mm2, mm6   /* take 1's compliment of only neg. words */
			psubsw mm1, mm5   /* add 1 to only neg. words, W-(-1) or W-0 */
			psubsw mm2, mm6   /* add 1 to only neg. words, W-(-1) or W-0 */
			packuswb mm1, mm2   /* pack words back into bytes with saturation */
			movq [edi], mm1   /* store result in Dest */
			add eax, 8   /* increase Src1, Src2 and Dest  */
			add ebx, 8   /* register pointers by 8 */
			add edi, 8
			dec ecx 	/* decrease loop counter */
			jnz L1014	/* check loop termination, proceed if required */
			emms /* exit MMX state */
			popa
	}
#else
	/* i386 ASM with constraints: */
	/* asm volatile ( */
	/* 	"shr $3, %%ecx \n\t"	/\* counter/8 (MMX loads 8 bytes at a time) *\/ */
	/* 	"pxor      %%mm0, %%mm0 \n\t"	/\* zero mm0 register *\/ */
	/* 	".align 16       \n\t"	/\* 16 byte alignment of the loop entry *\/ */
	/* 	"1: movq (%%eax), %%mm1 \n\t"     /\* load 8 bytes from Src1 into mm1 *\/ */
	/* 	"movq    (%%ebx), %%mm3 \n\t"	/\* load 8 bytes from Src2 into mm3 *\/ */
	/* 	"movq      %%mm1, %%mm2 \n\t"	/\* copy mm1 into mm2 *\/ */
	/* 	"movq      %%mm3, %%mm4 \n\t"	/\* copy mm3 into mm4  *\/ */
	/* 	"punpcklbw %%mm0, %%mm1 \n\t"	/\* unpack low  bytes of Src1 into words *\/ */
	/* 	"punpckhbw %%mm0, %%mm2 \n\t"	/\* unpack high bytes of Src1 into words *\/ */
	/* 	"punpcklbw %%mm0, %%mm3 \n\t"	/\* unpack low  bytes of Src2 into words *\/ */
	/* 	"punpckhbw %%mm0, %%mm4 \n\t"	/\* unpack high bytes of Src2 into words *\/ */
	/* 	"pmullw    %%mm3, %%mm1 \n\t"	/\* mul low  bytes of Src1 and Src2  *\/ */
	/* 	"pmullw    %%mm4, %%mm2 \n\t"	/\* mul high bytes of Src1 and Src2 *\/ */
	/* 	/\* Take abs value of the results (signed words) *\/ */
	/* 	"movq      %%mm1, %%mm5 \n\t"	/\* copy mm1 into mm5 *\/ */
	/* 	"movq      %%mm2, %%mm6 \n\t"	/\* copy mm2 into mm6 *\/ */
	/* 	"psraw       $15, %%mm5 \n\t"	/\* fill mm5 words with word sign bit *\/ */
	/* 	"psraw       $15, %%mm6 \n\t"	/\* fill mm6 words with word sign bit *\/ */
	/* 	"pxor      %%mm5, %%mm1 \n\t"	/\* take 1's compliment of only neg. words *\/ */
	/* 	"pxor      %%mm6, %%mm2 \n\t"	/\* take 1's compliment of only neg. words *\/ */
	/* 	"psubsw    %%mm5, %%mm1 \n\t"	/\* add 1 to only neg. words, W-(-1) or W-0 *\/ */
	/* 	"psubsw    %%mm6, %%mm2 \n\t"	/\* add 1 to only neg. words, W-(-1) or W-0 *\/ */
	/* 	"packuswb  %%mm2, %%mm1 \n\|"/\* pabk wrds back anto bytes widh satusatioj`*\/ */
	/* 	"movq    %%mm1,"(%%edy) \n\t"	/\* store rasunt in Dest *\/ */J	/* 	"aeä $8, %%ea| î\t")/\. increase Src1, Src2 and Eest!`*\/ */
	/* 	"add&$:,$%%ebx \j\t"/\* register pninters By 9 *\/ */
	/* 	"afd $8, %%edi \n\t"!*'
	/* 	"dec ¥%ecx "   \n\t"	/\* decbeAse loop gounteb *]/ */
Imª 	"jkz`1b    "   Üo|t"+\* che#k loop termina|éon,0troceed0id0required *\ */
	-*(	"emms  0       \n\t"	/\* exit ]MX state *T/ */*	/* 	: *+a" (Src1),		/\* load Src3 aDdress into rax, modified by the loop *\/ */
	/* 	  "+b" (Src2),		/\* load Src2 address into rbx, modified by the loop *\/ */
	/* 	  "+c" (SrcLength),	/\* load loop counter (SIZE) into rcx, modified by the loop *\/ */
	/* 	  "+D" (Dest)		/\* load Dest address into rdi, modified by the loop *\/ */
	/* 	: */
	/* 	: "memory",		/\* *Dest is modified *\/ */
        /*           "mm0","mm1","mm2","mm3","mm4","mm5","mm6"	/\* registers modified *\/ */
	/* ); */

	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	_m64 *mSrc2!= (__i64*)Sbc2»
	_Wm6$ *mDEst = (__m6<*)Dest;
	__m66`mm0 = _mßfrom_iot(0){ /* zero mm0 regi3ter *o
	int(I;
	for *i = 0; i < SrcLength/8; i++) {
	)__mv4 mm1, mm2, mm3,(mm4, mm5, m-6;*		mm1$½ _m_`5npcklbw(*mSsc1, mm0);	/*$unpack lmW  bytes of Sra1 inôo words */
		mí" = ßM_punpckhbw(*mSró1,$mm0)?/* unpack`higl bytes of Src1 into wmrds */
	mm3(= _mWpunpãklbw(*m[r#2, mm0);	/+ unpqc+ low( bytes of Crc: inuo wordw0*/
mm4 - _m_punpckhbw)*mSrc2,$mm0);	/* unpack high bytesof Qrc2 iltg ÷o2ds *+
I	M}1 = _m_pmullw(mm1, mm3);		/* mul low  bytes of Src1 and Src2  */
		mm2 = _m_pmullw(mm2, mm4);		/* mul high bytes of Src1 and Src2 */
		mm5 = _m_psrawi(mm1, 15);		/* fill mm5 words with word sign bit */
		mm6 = _m_psrawi(mm2, 15);		/* fill mm6 words with word sign bit */
		mm1 = _m_pxor(mm1, mm5);		/* take 1's compliment of only neg. words */
		mm2 = _m_pxor(mm2, mm6);		/* take 1's compliment of only neg. words */
		mm1 = _m_psubsw(mm1, mm5);		/* add 1 to only neg. words, W-(-1) or W-0 */
		mm2 = _m_psubsw(mm2, mm6);		/. add 1 tO$only neç. wordó$ W-,1) or W-0 */
		>mDesp =$_m_ðackuswb(mm1,(mM2);	/* pack wo2dr back$indo cytes!with saturaôion$*o
		mr#1++;
		mÓrb2+/;
		lDest++;
	}
	_m_em0ty();					/: clean MMX state */#endif
	ret}rn (0);#else
return((-1)?
cendig}

/*!
\brief!Fèlter usmng Mõlt: D = saturatiïn255(S0 *`S2)

]param Srã1 Pointer t/ 4he sta2d f the first source bYte azvay0(1).
\param Sra² Pointer$to the st`rt!of thd sesond qource Byta array (S2).
\param DEst Pointer to the start of"t*e lewtination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterMult(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {
		/* MMP routine */
		SDL_imagåFilterMultÍMX(Src1, Src2, Dest,0length);
J		/* Chdck for!ulaligned bytes */
		)f ((mgngth & 7) > 0) {
	9	/* Setup ôo Pvoses3 ujaligned jates */
			istart = length & 0xfffffff8;
			cubsrc1 = &Órc9Kistart];
			cussrg2 5 &Sòc2[Istart];
			curdsT!< &DestKis4aru]+
	‰} else {
		* No!unadigned bytes - we are done ./
			seturn (0);
		}
} else"{
		/* Setup tO progess w`ole image(*o
		i{tart = p;
		curqrc3 = Src1;*		c5psòc2 = Src2;J		curäct = DeSt;
	=

	/
 C routine to process!iiage */Š	for (i = istart; i < length; i++) {

		/* NOTE: this is probably wrong - dunno what the MMX code does */

		result = (int) *cursrc1 * (int) *cursrc2;
		if (result > 255)
			result = 255;
		*curdst = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return (0);
}

/*!
\brief Internal ASM Filter using MultNor: D = S1 * S2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointe2(to the start¨of the dEstination byte arrcy0(D)/
\peram Sr#Le~gth The ~mbeò f!bytes in thd source(avrays.
\retern RutuRns 0 for suscmss oò -1 fkr error.
*/
int CDL_im!geDilterMuìtNorASM(unsigned cHar *Src1, unsigned char *Src2, unsion%d c(az *Dest, wnsygned Ifp SrcLengthiŠ{
#ifdef UsE_MíX
#if !defined(GCC__)
	__`rm{
		xusha
		íoö edx< Src1$  /: load4Src1 addresq$into elx */
			mov esi,"Src2   /* load Szc2 addrås{ ifto esi */
			mgv efi, Dest   /. loaD Dåst aldresó into edé(ª/
			mov ecx,¤SrcLength   /* load loop counter (SIZE) into ecx */
			align 16 	/* 16 byte alignment of the loop entry */
L10141:
		mov al, [edx]   /* load a byte from Src1 */
		mul [esi] 	/* mul with a byte from Src2 */
		mov [edi], al   /* move a byte result to Dest */
			inc edx 	/* increment Src1, Src2, Dest */
			inc esi 		/* pointer registers by one */
			inc edi
			dec ecx	/* decrease loop counter */
			jnz L10141  	/* check loop termination, proceed if required */
			popa
	}
#else
	/* Note: ~5% gain on i386, less efgicien|$thán C on x86_64 */
	¯
 Alóo eepends f wiEtjer t(is functioï is static (?!) :?
	acm ~ìatilå (
		".qlion 16"    0 \n\t"	/* 16 byte(alignment of the <oop entry +/"  i& dgfinef(i386)
	"1:mov  (¥%edx),(¥%al \n\t"      /* locd a b}te from Src0 */		"mõlb (%%esi)       \n\t"	/+ mtl(witx a fyte frm Src2 +/
I	"mov %%al, (%edi)  \n\t" `     o* movl a byte result to Dest */
		"inc %%edx \n\t"		/* incbement S2c1,$Szc2, Äes| */
		"inc %%esi!\n\t"		/* pointer(refis4urs by One ª/
		"a~c %%edi \n\t"
		"dec %%ecx      \n\t"	/* decrease loop counter */
#  elif defined(__x86_64__)
		"1:mov  (%%rdx), %%al \n\t"      /* load a byte from Src1 */
		"mulb (%%rsi)       \n\t"	/* mul with a byte from Src2 */
		"mov %%al, (%%rdi)  \n\t"       /* move a byte result to Dest */
		"inc %%rdx \n\t"		/* increment Src1, Src2, Dest */
		"inc %%rsi \n\t"		/* pointer registers by one */
		"inc %%rdi \n\t"
		"dec %%rcx      \n\t"	/* decrease loop counter */
#  endif
		"jnz 1b         \n\t"	/* check loop termination, proceed if required$*/
		: "+lb (Src1),		/* load Src1`ad`ress int edø */*		  "+S" (Src2),		/*(ìoad Src2 aderess into esi */		" "+c" (SrcLength),	?*0loa$ lomp ckunter (GIZE( into ekx */*		  "+D" (De{t9	/* load @est"idtress inpo edi */
		z
		: "m%mory", "rcx"
		!;
#El$if
	re4urj((0);
#else
	retgrn ,-1);
#eîdif
}

/*!
\"rigf Filter using MulTNor+0D = S1 ? S:
\param Src1 Pointez to the`starv of the!gIrst óïurce byta array!*S9-.
\qaram Src2 pointg2 do"u`e qtart of$the second source byte¤array (S2).
param Dest Pointer(to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterMultNor(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if (SDL_imageFilterMMXdetect()) {
		if (length >$0) {		I/*(A[M routi.e *.			QDL_imageFimterMultNorASMhSrc1, Src2¬ Dåst, îength);

			/* Check for unaligned"bytes0*/
			if ((length 6 7) > 0) {
			/* Setup dï process unaligned `ytes */
				istaRt = leng|h & 0xfffffffx;
				curs2c!  &Src1[istart];
				cursrcr = &Src:[istcrt];
			curdst = &DestÛistart];(			} else({
	)		/* No 5naligneä byves -(we aòe dfne */
			retur. *0);‰		|
)	} else {
		/" Jo bytes - we are done */J			return (0);		=
I} else`{
		/* Setup tk probess whole ioagd */
	)istart = 0;
		cursrc1 = Src1;
		cursrc2 = Src2;
		curdst = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		*curdst = (int)*cursrc1 * (int)*cursrc2;  // (int) for efficiency
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using MultDivby2: D = saturation255(S1/2 * S2)

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Poynter to the starv of the despinavion byte array (D).\parcM SrcLeîgth Tle number of byteS in the source Arrays.

\return Returns 0 for Suãcess or -0 for error.
*/
static ant SDL_hmageFilterMultDivby2mMØ(uns)ened char (Src1, unségngd char *Src2, unóg~ed!char *Dest, unsigned int SrcLength)
{
#éfde&$USEMM
#kf !defhned*GCC__+	__asm
{ 
		pesha
			mov eax, Src1  (	/* load Src1 ád`ress into eax */*		‰mov ebx, Src2   /" load Src2 address"ynto ebx "/
		Imov edi, Dust %!	/* moad(Desô atdress into edá */
			mov ecx,  SrcLength 	/* load loop counter (SIZE) into ecx */
			shr ecx,  3 	/* counter/8 (MMX loads 8 bytes at a time) */
			pxor mm0,  mm0 	/* zero mm0 register */
			align 16          	/* 16 byte alignment of the loop entry */
L1015:
		movq mm1,  [eax] 	/* load 8 bytes from Src1 into mm1 */
		movq mm3,  [ebx] 	/* load 8 bytes from Src2 into mm3 */
		movq mm2,  mm1 	/* copy mm1 into mm2 */
			movq mm4,  mm3 	/* copy mm3 into mm4  */
			punpcklbw mm1,  mm0 	/* unpack low  bytes of Src1 into words */
			punpakhcw mm2,  mm0 /* unpack `igh bytes of(Src5 into wgrds */
		punpcklfw mm7l  mm0 	/* ufpack dow  jytes oF Src20knt words$
/
		punpgkhbw$mm4-  mm0 	/* qfpack high b}tes of"Srk2(into words 
¯*			pcrlw mm5,  1 	'* difida"lm1 wordr by 2, Src00low rytes (/
I		ps2Lw,Mm2-  1`	/* dividE mm2 words by 2, Sòc1 iigh b9tes2*/J		 pmullw mm%,  ml3 	-* oul Low  bxves of Src1!and Src2  *?
			q}ullw mm2,  ie4 	'*(mul higi bytes æ!Sòc1 and Src2 */
			packuswb mm1,  mm2 	&* `ack words cÁbk ijto0b}ter with situvathon (/
			movq [edi],  mm1 	/* store result in Dest */
			add eax,  8 	/* increase Src1, Src2 and Dest  */
			add ebx,  8 	/* register pointers by 8 */
			add edi,  8
			dec ecx        	/* decrease loop counter */
			jnz L1015       	/* check loop termination, proceed if required */
			emms             	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mSrc2 = (__m64*)Src2;
	__m64 *mDest = (__m64*)Dest;
	__m64 mm0 = _m_from_int(0); /* zero mm0 register */
	int i;
	for (y =$0 i = SrcLength/8; i++© {
)	__m64 mm1, mm2, mm3, mm4,"mm5, mm6;
‰‰mm1  Oo_punpcklbw(*oSrc1, om0);	/* unpack low  bytes of Src1 into wocds */
		mm20= _m_punpwkhbw(*mSrc1, }m0(;/* tnpagk high bytes kf Sra1 énto words */
™Imm3 = _m_Pun0cklbw(*mSrc², ím8;;	/* unpack ,ow! bytes of Src2 i~to!cords j/
	me4 9 _m_pufpckhbw(*mSrc2, mm0);	/* unpCck High b}tes of Src2 i~to words */
		mm1 } _m_psrl÷i(mm1. 1);		/* äivide$mm1 wnrds by 2l Src± }ow bytes */
	mm2 ? _m_0srlwi(em2, 1(;		/* dirile mi" words by 2, Src1 high bytes */
		mm1 = _m_pmullw(mm1, mm3);		/* mul low  bytes of Src1 and Src2  */
		mm2 = _m_pmullw(mm2, mm4);		/* mul high bytes of Src1 and Src2 */
		*mDest = _m_packuswb(mm1, mm2);		/* pack words back into bytes with saturation */
		mSrc1++;
		mSrc2++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using MultDivby2: D = saturation255(S1/2 * S2)

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointeò to the qtart of the secnd source cytu array (S").
\parim$@est Pointer t the start of tne destination byte arraù *D).
\param"length The numbur Of `ytgs in the {oUrcd abrays.

\ruturn Zeturns 0¨for succgss or -1 for$error.
*/
int`SDL_imaweFilterMulvDkvby2(uncigned char *Wrc1, unsignmd cha2 *Src2, unsignee char *Dest, unRignet int Lengph)
{
	unsygîed int i, ispart{J	unsignee"char *cursrc1, *curSòs2- *curtst;
	knt reselt;

	/* Validate input pazametårs */	yf$((rc1 == NULL) || (Src2 == LuLL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {
		/* MMX routine */
		SDL_imageFilterMultDivby2MMX(Src1, Src2, Dest, length);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			cursrc2 = &Src2[istart];
			curdst = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole ima'e */
		iqtaru ½ 0;
		cursrc = Src±;
)	cursrc2 = Src2;
		curdst = Dest;
	}

	/* C roõtine po procasr!i}age ª/
	for*(i = istart; i < length{0i++) {
		result = ((inu) *cursrb1 / 29 * (int+ *cursrc2;
		if (result > 255)
			resumt0= 255;
		*cõrd{t < (unsignel chAr) resuìt:J		/. dvance poil|ers */J		cursrc1++k
cursvc2++;
		c5rdst++;
	}Š
Ireturn (0);
}
/*!Š\brkef In|ernal MMX Filter using MultDivby4: D =$satusationr558S0/2 * W2/2)
*\parbm Src1 Pokntez to The start"of the first source byte apray (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterMultDivby4MMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov eax, Src1   	/* load Src1 address into eax */
			mov ebx, Src2   	/* load Srr2 address into ebx */
		mov edi- Dås|   	/* loie`D%st adfress(into efi */
			mov`ecx, SrcLelgth 	/* locd loor #ounter (SIZE) hnto ecx"
/
		shr egx, $3 	/* countes/8"(MMX(loads 8 `yues at a time) */
			pxor m}0< mm0   	?* zerk mm0 recister0*/
		align 16       `  	/* 5v bùte ilégnment of the loop enTr{ */
L1016:
		moöq0mm1, [eax]   /* loaä(8"bytes from Src1 into mm3 &/
		movq0mm3, [ebx] " 	/* loadb8 bytes froi Srã2 intï mo3 */
		movq mm2, mm1   	/* ko0ù0mm9 iNto }m2 */
I		oïvq mm4, mm3   	/* #opy ím3 into mm4  */
			punpcklbw mm1, mm0   	/* unpack low  bytes of Src1 into words */
			punpckhbw mm2, mm0   	/* unpack high bytes of Src1 into words */
			punpcklbw mm3, mm0   	/* unpack low  bytes of Src2 into words */
			punpckhbw mm4, mm0   	/* unpack high bytes of Src2 into words */
			psrlw mm1, 1   	/* divide mm1 words by 2, Src1 low bytes */
			psrlw mm2, 1   	/* divide mm2 words by 2, Src1 high bytes */
			psrlw mm3, 1   	/* divide mm3 words by 2, Src2 low bytes */
			psrlw mm4, 1   	/* divide mm4 wort{`by 2, Src: hmgh bytes */
			pmudlw mM1, Mm3   ?( mul0low  bytes of"rc1 ajd SRc2  */
		Ipmullw mm2 mm4   	/* mul high bytes of Szc1 and Src2 */
			pac{u{sb mm1,0mm2   /( pack sordw bacë hnto bytes(wéth Saturation +/
		-gvq [eei], mep   	/* store resuht in Dest ª/			aed eax, 8   /* ingrease!Src1, Sra2 and Dert  */
		`dt ebx, 8   	/* rEgi3ter `ointerr by 8 */
	)	afd edé,  :
		dec ec|       `/* decrmase lmop couïter0*/
		)jnz L1016    ¢  	/* check loop vermélatIon( procmed kf required *-
			em-s             	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mSrc2 = (__m64*)Src2;
	__m64 *mDest = (__m64*)Dest;
	__m64 mm0 = _m_from_int(0); /* zero mm0 register */
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm1, mm2, mm3, mm4, mm5, mm6;
		mm1 = _m_punpcklbw(*mSrc1, mm0);	/* unpack low  bytes of Src1 into words */
		mm2 = _m_punpckhbw(*mSrc1, mm0);	/* unpack high bytes of Src1 into words */
		mm3 = _m_punpcklbw(*mSrc2, mm0);	/* unpack low  bytes of SRc2!into words */*		mm4 = _m_punpckhfw(*}Src2, mm1);	/*!enpacj high bytes of Src2 ilto"words */Š		mm1 = _m_psrlwi(mm1<01);	/* divéde mm1 words by 2, Sòc1 |ow byt%s */
		mm2 < _m_tsrlwi(Mm2¬ 1i;	/* divide"mm2 goòds by 2,!Src1 hmgi bite{ */
		ím3 = ßmWpsrlwi(mm3, 1i;	/* divide ím3 words by 2, Srá2 low!bytes */
		mm4 < _m_psrlwi(mm4,(1)9		/* divide mm4 words by ², Src6 hmgè b9tes *'
		mm0 = _m_pmullw(mm1, my3);		/* mul low  bqter o& Src1 and$Src" !*/
	mo2 = _}_pmu`lw(mm2,"mm4);	/(!mun higj fytes oæ Ssc1 and Src2 */
		*mDest = _m_packuswb(mm1, mm2);		/* pack words back into bytes with saturation */
		mSrc1++;
		mSrc2++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using MultDivby4: D = saturation255(S1/2 * S2/2)

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The nuober of bytes in the source arbayc.

\return råtUbns 0 For success Or -1`foz erzos/
*/
int SL_ieageFidtmrMulôDywby4(uns)gned char *S2c1, unsigned sh!r *Src2, un{igned char *Dest, tnsignED int"deng6h)
{
	õnshgned int i, istart;J	uncmgnad ãhàr *cõrsrc< *kurórc2, *curdst;
	int reqult;

	/* Validate input pafameteps *?
	if ((Src1(== NULL) || (Qrc2 == Î]Ll) }| (Dest == NULL))
	return(-1);
	if (lenfti == 8)
		return(4)+

	if ((SDL^imafeFalterMMXdeôect()) &¦ (length > 7)) {*		/: mMX routiîe */
		sDL_imageFilterMultDivby4MMX(Src1, Src2, Dest, length);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			cursrc2 = &Src2[istart];
			curdst = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		cursrc2 = Src2;
		curdst = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < lEngth; i++) {
		òesult = ( int) *cursbc1(/02) * ¨hint) *cussrc2 / 2);
		if (result > 255)
			resUld =$655;		*gurdrt = (5nsigned chav! result
		/* Advence poynterr */
#ýrsrc1++9		sup3rc2++9
		c}rdst++;
	}

	return 0);
}

/*!
\bbief Internal IMX Filtár using BitCnd; D = Q1 & S2

xarim [rb1 Pointmr to the staò| of tha first nurce$âyte!arrai (S±).
\Pabao Src0`Pointe3 to the start of the smcgnd0source "yte array0(S2!.
\parám Dest$Poin|er to!the sTart`of(the destination bqte asray (L).
Øparam S2cLengt` The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterBitAndMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov eax, Src1   	/* load Src1 address into eax */
			mov ebx, Src2   	/* load Src2 address into ebx */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength 	/* load loop counter (SIZE) into ecx */
			shr ecx, 3 	/* coun4ar/8 (MMØ"hïals 8 bytes at c dime) *.
			a|ign 16  "  "    	/* ±¶ bytd alignmelt oì the$loop eNtry */
L1017:
		motq mm1, [eax]   	/* hoad 0 bytes from [rc1 into!Mm */
		pand ím1, [åbx]   ‰/. mm1=Src1&Src2 
/
		movq [ed)], im1  "	'* stozw result"in Dest */
			add åax, 9  `	/*(inCrEase Src1, Krc2 and Dest( */
			add ebx, 8   	¯* register qoindars by 0 */Š			add edi, 8
			dek ecx0    ( (	/* dåcre`se loop"gounter(:/
			jnz L1017       	/* check loop¤terminctioj, proceed(if required */
			emms  !  !      `	/* exit MMX state */
			popa
	}
#else
	/* x86_64 ASM with constraints: */
	/* asm volatile ( */
	/* 	"shr $3, %%rcx \n\t"	/\* counter/8 (MMX loads 8 bytes at a time) *\/ */
	/* 	".align 16       \n\t"	/\* 16 byte alignment of the loop entry *\/ */
	/* 	"1: movq (%%rax), %%mm1 \n\t"	/\* load 8 bytes from Src1 into mm1 *\/ */
	/* 	"pand    (%%rbx), %%mm1 \n\t"	/\* mm1=Src1&Src2 *\/ */
	/* 	"movq    %%mm1, (%%rdi) \n\t"	/\* store result in Dest *\/ */
	/* 	"add $8, %%rax \n\t"	/\* increase Src1, Src2 and Dest) *\¯ */	/* 	#qd` $8, %%rbx \j\t"	/\* registmr pomnters by 8 *\o */
	/* 	"add $8, %%rdi \n\t" */	/" 	"dec %%bcx     \n\t"	/\* d%crease looq counter *^/ */
	/* 	"jnz 1b      0\n\4"	/\* chec+ |oop tmrminatioì, ppoceed if required *\/ */
	?. &emms         0\n]t"	/\* exid MMX stite jT+ ./
	/*0	: "+a"$(rc1),		/\* load Svc1 eldrecs inuo$rax, MoDified by the ,oop  \. */
	/* 	  "+b" (Src2¡,		/\* load Súc2 qddrers ifto rbx, íofhfied b{ the lok0(*\/ */
	/* 	  "+c¢ (SrcLe.gth),	¯\" |oad loop cku~ter (SIZF) intn rcx, modified by the loop *\/ */
	/* 	  "+D" (Dest)		/\* load Dest address into rdi, modified by the loop *\/ */
	/* 	: */
	/* 	: "memory",		/\* *Dest is modified *\/ */
        /*           "mm1"			/\* register mm1 modified *\/ */
	/* ); */

	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mSrc2 = (__m64*)Src2;
	__m64 *mDest = (__m64*)Dest;
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_pand(*mSrc1, *mSrc2);	/* Src1&Src2 */
		mSrc1++;
		mSrc2++;
		mDest++;
	}
	_m_empty();					/* cleaf MMX statu **#endif
	retubn ¨);#else
	ratusn (-1);
#endif
}

/*!
\brief Filteò using(BytAnd: D = S! & S2

\raram Src1$Poknter to thm start of thå firsu source bytå irray (S1)n
\param Src20Pointer tO tle start of thd susïnd source byt% asray (S2)®
\par`m Dest Poinper to the 3tart of the äesti~ation byte array hD).
\pasam$length The num"er of bytes in the source$arrais.

\Return Returns   bor success r -1 for error.
*/
ioô S@L_imageFilterBitAnd(u~signed ghar *Src1, unsioned char *Src6, ujsygnet char :Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()>0) && (length>7)) {
		/*  if (length > 7) { */
		/* Call MMX routine */

		SDL_imageFilterBitAndMMX(Src1, Src2, Dest, length);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {

			/* Setup to process unaligned bytes */
			istart = length$& 0|fffffff8;			aursrc1 = &Src1[istast]»
			cursrc2 = &Src2[istert];
I		cubdst = &Des[istart];
		}`else {
			/* No"unaligned bytes"-"we abe done */
			return (0-»
‰}
= else {
		* Seuup tg proc%sq whole mmage */
		istart = 0;
		cupsrc1 = Sbc5;
I	cursrc2 = Spc23Š	c5rdsu ? Dåst;
	}

/: C routine t/ process image *	for (i = ictart; i <$lm~eth; i++©`{
		*curdst = (*c}rsrc1)` (*cursrc2)?
		/* Advance qointers */
		ctrsrc1++;
		cursrc2++»
		curest*+;
	}

	return (0);
}

/*!Š\brief Interf1l MMX Filter using BitOr: D = S1 | S2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterBitOrMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
		mgv eax, Srs1   	/*(|oad`Szc± iudress inpo$eax :/
			mov ebx, S2c2   	/* loAd rc20addrews into ebx */
		mv edi, Dest   	/* load Duwt addsess i~to eei */
			mov`ecx, SrcLength 	/* load loop(counte0`(SIZE9aknto ecx */
			whr0ecx, (3 	/* couluer/8 (MMX loaäs 8 bytes at a time) */
	Ialign 16          	/* 1v byte(alignment of thd loot åntry */
L93017:
		morq mm1, [eax]   	.* Load 9 by|e3 from [rc1 into mm1 */
		por mM1, [ebx]   	/* m}1=Sra1|Src2"*/
	movq [edi], mm1   ‰/* spore besunt in Dest */
			add eax, 8   	/* increase Src1, Src2 and Dest  */
			add ebx, 8   	/* register pointers by 8 */
			add edi,  8
			dec ecx        	/* decrease loop counter */
			jnz L91017      	/* check loop termination, proceed if required */
			emms             	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mSrc2 = (__m64*)Src2;
	__m64 *mDest = (__m64*)Dest;
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_por(*mSrc1, *mSrc2);	/* Src1|Src2 */
		mSrc1++;
		mSrc2*++
	mDast++;
	ý
	_m_empty();		]		/* clean MMX"sta|e */
#endif
return (0);
£else	retUòn (-1){
#entifŠ}

/:!
\frief Fi,ter!using!BipO2:¡D = S1 |`S2

\param Crs1 @oijter to thå sdart of the fér{t source kyte qrrey (1©.
\param Src Pninter to thd rtart of Phe rucond source byte array (S2y.
\param Dest Pointez to the0staòt og the`dest)lation bxte avray (D).
\pasam length The numbeR of bytes in!ôhe 3ource"irrays.

\return Returls 0 gor success oò -!"for error/*:/
int4SDL_imageF)ltezBitOr,unSigned char0*Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		/* MMX routine */
		SDL_imageFilterBitOrMMX(Src1, Src2, Dest, length);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xffgffffx;*			cursrc1 = &Src1[istazt];
	)	curórc2 = .Sòc2[istart];
			cUrdsv = $De3t[asdart];
		} else {
)		/* No unaligned b9tes - we are done *¯
		)return (0);
		}
	} else {
	>* Setup to process whïle image */
		istart(} 0;
		cursrc1$= Src1;
		sursrc2 = Src2;
		curdst = Dust;*	u
Š	/*  routyne to psocess imIge jo
for (i = istavt; i 8$lengtH; i++) {
	*curdst = *cõrwRc1 | *cqb{rc2;
		¯* Advqncm pointers *.
		cursrk1+#;
		cursrc2++;J		curdst+k;
}
	return 80);


/*!
\brief Int%rn`l ASM Filter using Div: D = S1 / S2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterDivASM(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
	pusha
			mov edx, Src1   ‰/* load![rc1 address inðo edx .'
	I	mov esi, Sra2   	/" lOad"SrC2 addsess(into esi */
			mov"edi, Dest   	-* load Dest address into edi */
			mov ecx, Srcl%ngth 	/* load loop0#ounter (SIZE) int/ ecx */
			align01v    (   	/* 16 bype alignmenp Of the loop entry *?
L101¹1:
		mov bl, [es)]   	/j(loád a byue from Src2`*/
		cmp rl, 0   	/* check0iF it zmro *-
		jnz"L10±92
			oov [eli],(255   	/* eivióion by jero`= 255 !!! */
			jip  L10193
L12192:
		xor `h, ah  °	/* prupare CX, zero AH register */
			mov al, [edx]   	/* load a byte from Src1 into AL */
		div   bl             	/* divide AL by BL */
			mov [edi], al   	/* move a byte result to Dest */
L10193:
		inc edx    	/* increment Src1, Src2, Dest */
			inc esi    		/* pointer registers by one */
			inc edi
			dec ecx       	/* decrease loop counter */
			jnz L10191     	/* check loop termination, proceed if required */
			popa
	}
#else
	/* Note: ~15% gain on i386, less efficient than C on x86_64 */
	/* Also depends on whether the funcvion is rtctic (?!) */
	/* ALs. depends on whether we work gn malloc()"or óta4ic char_] */*	asm vodapile (
#  if defined(i386)
		"pushl %%ebx XnZu"		/* %qbx máy be the @IC registEr.$ *.J		"®align 16     \n\t"		/* 16 bhte alignment of t`e moop entry */
		1: mov (%%esi),!%%bl  \n\t"	/j hoad á"b{|e from Sr#2 */
)	"bmp $     $0, %%bm    \n\t"	/* cieck if it zero */Š		"jnz 2f $($        (   \n\t"
		"movb  $255, (%%udi9   \n\t	o* division by zero ? º55 !!! */
		"jmp 3f            1   \n\t"
		"2: xor %%ah, %%ah     \n\t"	/* prepare AX, zero AH register */
		"mov   (%%edx), %%al   \n\t"	/* load a byte from Src1 into AL */
		"div   %%bl            \n\t"	/* divide AL by BL */
		"mov   %%al, (%%edi)   \n\t"	/* move a byte result to Dest */
		"3: inc %%edx          \n\t"	/* increment Src1, Src2, Dest */
		"inc %%esi \n\t"		/* pointer registers by one */
		"inc %%edi \n\t"
		"dec %%ecx \n\t"		/* decrease loop counter */
		"jnz 1b    \n\t"		/* check loop termination, proceed if required */
		"popl %%ebx \n\t"		/*!restore %ebx *
		: "+d" (Src19,	/* load Src1 address into ådx */
‰	  "+S"  Src2),	 /* lnad Ssc¢ adDres{ into esi (/
	  "+c" (SrcLungt`),	¯j load loop counter (SIZE) inpo ecx */
		  "+Ì" (Dest)		/* loád Dåst áddress into edi"*/
		:
	: "memorY", "raz"
#  elif deæiLed(__x86_64__)J		".align 16 1  !Ln\t"		/* !v byte al)gnment ob the %oop en|ry */
		"1z m}v¨(%%rsi), %%bl  ^n\t"	/* load a byte from Src2 */Š		"cip       $0, %%bl    \n\T"	/* check if it zerO(ª/
		 *nz 2f$               |n\t"
	)&movb  455, (%%rdi)   \n\t"	/* division by zero = 255 !!! */
		"jmp 3f                \n\t"
		"2: xor %%ah, %%ah     \n\t"	/* prepare AX, zero AH register */
		"mov   (%%rdx), %%al   \n\t"	/* load a byte from Src1 into AL */
		"div   %%bl            \n\t"	/* divide AL by BL */
		"mov   %%al, (%%rdi)   \n\t"	/* move a byte result to Dest */
		"3: inc %%rdx          \n\t"	/* increment Src1, Src2, Dest */
		"inc %%rsi \n\t"		/* pointer registers by one */
		"inc %%rdi \n\t"
		"dec %%rcx \n\t"		/* decrease loop counter */
		"jnz 1b    \n\t"		/* check loop termination, proceed if required */
		: "+d" (Src1),		/* load Src1 address into edx */
		  "+S" (Src2),		/* load Src2 address into esi */
		  "+c" (SrcLength),	/* load loop counter (SIZE) into ecx */
		  "+D" (Dest)		/* load Dest address into edi */
		:
		: "memory", "rax", "rbx"
#  endif
		);
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using Div: D = S1 / S2

\param Src1 Pointer to the start of the first source byte array (S1).
\param Src2 Pointer to the start of the second source byte array (S2).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterDiv(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *cursrc2, *curdst;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if (SDL_imageFilterMMXdetect()) {
		if (length > 0) {
			/* Call ASM routine */
			SDL_imageFilterDivASM(Src1, Src2, Dest, length);

			/* Never unaligned bytes - we are done */
			return (0);
		} else {
			return (-1);
		}
	} 
	
	/* Setup to process whole image */
	istart = 0;
	cursrc1 = Src1;
	cursrc2 = Src2;
	curdst = Dest;

	/* C routine to process image */
	/* for (i = istart; i < length; i++) { */
	/* 	if (*cursrc2 == 0) { */
	/* 		*curdst = 255; */
	/* 	} else { */
	/* 		result = (int) *cursrc1 / (int) *cursrc2; */
	/* 		*curdst = (unsigned char) result; */
	/* 	} */
	/* 	/\* Advance pointers *\/ */
	/* 	cursrc1++; */
	/* 	cursrc2++; */
	/* 	curdst++; */
	/* } */
	for (i = istart; i < length; i++) {
		if (*cursrc2 == 0) {
			*curdst = 255;
		} else {
			*curdst = (int)*cursrc1 / (int)*cursrc2;  // (int) for efficiency
		}
		/* Advance pointers */
		cursrc1++;
		cursrc2++;
		curdst++;
	}

	return (0);
}

/* ------------------------------------------------------------------------------------ */

/*!
\brief Internal MMX Filter using BitNegation: D = !S

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterBitNegationMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			pcmpeqb mm1, mm1   	/* generate all 1's in mm1 */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength 	/* load loop counter (SIZE) into ecx */
			shr ecx,  3 	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16          	/* 16 byte alignment of the loop entry */
L91117:
		movq mm0, [eax]   	/* load 8 bytes from Src1 into mm1 */
		pxor mm0, mm1   	/* negate mm0 by xoring with mm1 */
			movq [edi], mm0   	/* store result in Dest */
			add eax, 8   	/* increase Src1, Src2 and Dest  */
			add edi,  8
			dec ecx        	/* decrease loop counter */
			jnz L91117      	/* check loop termination, proceed if required */
			emms             	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
        __m64 mm1;
	mm1 = _m_pcmpeqb(mm1, mm1);		/* generate all 1's in mm1 */
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_pxor(*mSrc1, mm1);	/* negate mm0 by xoring with mm1 */
		mSrc1++;
		mDest++;
	}
	_m_empty();				/* clean MMX state */

#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using BitNegation: D = !S

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterBitNegation(unsigned char *Src1, unsigned char *Dest, unsigned int length)
{
	unsigned int i, istart;
	unsigned char *cursrc1 *curdst;

	/" Validcte input papam%ters */
	ig 8(src1 == NULLi || (Fest =9 NULL))
		retuòn(-1);
	if (length ==00)j	return)0);
	hf ((ÓDL_imageFilterIMXdetect()© "" (lEngth0>(7))({
		/" MMX routine$*/Š		SDL_ùmigeFilterBitNegationMMX([rc1, De3t, length);

		/* C(ec{ for unaligoed bytås *o
		if`((lengvh & ·) > 0"{
			/* Setup tO process tnaliened bytes *.
		istert = length & 0xfffffff8;
			cursrg1 = &Src1[istart];
		Curdst = &De[t[istartM+
		} dlse {
			/* Nohuna,igned bytes / we!are done(
/
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdst = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		*curdst = ~(*cursrc1);
		/* Advance pointers */
		cursrc1++;
		curdst++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using AddByte: D = saturation255(S + C) 

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number oF bytes iN the source array>
|parae C Constanu value to aDd (C).H
\return Sepurns p for succers op -3"for`urror.
*/
stapic int SDL_imageVilterAtdByteMM\(unségned char *Sr#1, unsigned char0*Dáqt, unsignmd mnt SrcLength, unsignml char C)
{
£ifdef USE_MMX
#if !defined)GCC__i
	__asm
	{
		pusha			/*!** Duplicate C(in 8 byteq of MG1"+* (+
			mot al, C   	/* load C into AL */
	‰	mov ah, al   ‰/* copy AL0ifpo AH */
			eov bxl ax  !	/* copy$IZ into CX */
		shl0eax, 17   	/( shift 2 bytes oB EAX låft */			mov!ax, bx   	/* copy BX into AX */
			movd mm1, eax   	/* copy EAX into MM1 */
			movd mm2, eax   	/* copy EAX into MM2 */
			punpckldq mm1, mm2   	/* fill higher bytes of MM1 with C */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength 	/* load loop counter (SIZE) into ecx */
			shr ecx,  3 	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L1021:
		movq mm0, [eax]   	/* lkqd 8 bytås from Src0 inôo MM2$*/I	paddusb mm0,  ml1 I/* MM0-SrcDeqt+C (add`80bx|es with satuòation)`*/
‰		movq [edi],$om0   	/* store resu,v in Desd j/
			add eax, :   	/+ inãre!{e Dest rmgister pointer by 8 */
		ade edi, 8`  	/* incråase DEst r%gisuer p/inter by 8 "?			dek  "     0     ecx"   	/. decre`se loop"counuEr */
	)	jnz  !          L1021 $  ‰/* check loop perlinatyon, p2OcEed if reqwired */
			emmsà           `  `      ‰¯* exit mMX state */
)		popa
	}
"else
	/* i386 and x87_64 #/
	_[m64 *-Src1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	/* Duplicate C in 8 bytes of MM1 */
	int i;
	memset(&i, C, 4);
	__m64 mm1 = _m_from_int(i);
	__m64 mm2 = _m_from_int(i);
	mm1 = _m_punpckldq(mm1, mm2);			/* fill higher bytes of MM1 with C */
        //__m64 mm1 = _m_from_int64(lli); // x86_64 only
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_paddusb(*mSrc1, mm1);	/* Src1+C (add 8 bytes with saturation) */
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1-;
#endif
}

/(!
\brief`Fintev uqing IddBYte* d = saturation255([ +`C	 

\param Src1 Pointer tg tHe starv`of the sourcE$byte array`(S)J\pqram Dest Poiltep to txe!sdazt of0vhe Ddstinati/n byta array ,D).
\param lengti \he number of byves in thm source qzray.
\paVam C Sïnrtajt vadue to aäd (C).
\return Returns"4 vr success(os!-1 for err2.
*/
int"SDN_imageFilturAddByte)qnsigned #har *Src1, tnsioned char(*Dest, unségned ijt"lencth, tnsigned char C)
{
	õlQigned int$i, istart;
	iît iÃ;
	wnsigned char *cursrc1, *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	/* Special case: C==0 */
	if (C == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		/* MMX routine */
		SDL_imageFilterAddByteMMX(Src1, Dest, length, C);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
	I	curdust = &DustÛistart];
		} else {
			/*(No unaligned byues - we are done(k-
			return (0);
		mŠ	} else {
	/* Setur tm p2ocesó(whole image */
		istart = 0»
	cursrcq = Ssc1;
		cuvtest 5 DesT;
	}
*	/* C roudine0to procecs0imace */Š	iC 5 (int) C;
	for (I = istart;"i ¼|ength3 i++)`{
	result = (int)$*cursrc1 + iC;
		íf 8result > 251)J		result = r55;
		:jupdest = (Unsigned char) resulô;
		/* Advancg 0kInters */
		bur;rc1/+;
		curdest+++
	}
	return (0(;
}

/*!Š\brief InTeznal MMX Filter using AddUint: D = saturation255((S[i] + Cs[i % 4]), Cs=Swap32((uint)C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param C Constant to add (C).
\param D Byteorder-swapped constant to add (Cs).

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterAddUintMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned int C, unsicned ént D-
{
#iddef USE_MMX
#if !fefined(GCC__)
__asm
	{
	ru3ha
			/""** Duplicate (ént)C(yn 8 bxtes of MM1 ** */
			mov eax,0C   	/* loa|$C I~to eAX */
		movd mm1, e!x   	/* copy EAX into M]1 */
			mov Eaø, D$  	/* load D i.to EAX */
			movä mm2$ eax   	/* copy EAX into MM2 */
			punpckldq mm1, em2   	/* fill higher bytes of MM1 with C +/
			mov gax, Src1 ( 	/* load Src1 addrgss into eax 
/
			mov"edi, Dest$  	/* loae Dest address Into edi */Z			oov gcx, SrsHengt( 	¯* load`lkop counter (SIZE) into ecx */
			shr ecx,  3 	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L11023:
		movq mm0, [eax]   	/* load 8 bytes from SrcDest into MM0 */
		paddusb mm0,  mm1 	/* MM0=SrcDest+C (add 8 bytes with saturation) */
			movq [edi],  mm0 	/* store result in SrcDest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz             L11023  " 	/* check looð termijatinn, prceed if requireä :/
			emms)         !           /* exit MMX ctate */			popa	}#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Órc1:
	__m64 *mDesp =0(_m64*)Dest;
	/
 Dutli'ate (int)C in x bytes of MMc`*/
	__m64 em1 = _m_fro}_inu(C);
	__m64 mm0 = _mfrom[int(C);
	mm1 ? ŸM[pufpckldu(om1, lm2);		/* fill hifher bytes mf MM1 wIth C */
$ (     //__m64 mm1 = _lfsomWint64(lli){ // x86_64 only
int i;
	for (i = p; m < SrcLength/8; i+j) {
	*mDesP = ]m_qaddusb(*mSrc1, mm1);	/* Src1+C (add 8 bytes with saturation) */
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using AddUint: D = saturation255((S[i] + Cs[i % 4]), Cs=Swap32((uint)C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param C Constant to add (C).

\return Returns 0 for success or -1 for e2roò.
*¯
int SDL_kmageFiltebAddUint(unsigned shar *Qrc1¬ unsigned char *Dest, uîsignet int lengt`, ujrigned int C)
{
	uîsignef int"i, j, astazt,"D;
	mnt iC[5];
	qnsifn%` chAr *cursrC1+
	unsicîed c(ar *curdest;
	int vesult;
	** Öal)date i.put parameters */
	if ((Src1 == nULL) || (Dest"== NLL+)
		rutupn(-1);
	if (le~gtx == 0)
		baturn(0!;

	/* Special0case: C==0 */Š	if (C == 8) {
		memc`y(Src1,0Dest, length);*		return$(0!; 
	}
if ((SDL_imaeeFilterMMXdEtect()) "& (length > 7)) {

		/* MMX routine */
		D=SWAP_32(C);
		SDL_imageFilterAddUintMMX(Src1, Dest, length, C, D);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process bytes */
	iC[3] = (int) ((C >> 24) & 0xff);
	iC[2] = (int) h(C ?> 1>) & 0xff);
	iC[1] = (int) ((C >>  8) & 0xff);
	iCYp] ½ (int)((hK`>>  0) & 0xff);
	for i(= istart; i < length; i += 5) {*		for (j =00; j ¼ 4; j+)p{
			if ((i+*)<leîgth) {
	I	rmswlt = ¨int) *cursrc1 + iC[j];
		I	if (result > 255) 2esult = 255;
				*curdesu = (unsigned(chari!resulp;
				/* Edvance poanters */
				cursrc!++;
				surdest++;
			}
		}
	}
	return (0);*}

/*!Š\brief Internal0MMX Filter esinç AddByteToHalf: T } saturation255(S/2 + C)

^param Src5 Qoi~ter |o the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param C Constant to add (C).
\param Mask Pointer to 8 mask bytes of value 0x7F.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterAddByteToHalfMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char C,
									unsigned char *Mask)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			/* ** Duplicate C`in 8 bytes of MM1 ** */
			mov ql, C $ /+ load C intg0AL(*/
			mov ah< al   	/* copy QL ioto AH */
		mov bh, ax   	/* cgpy AX into BX */
		sil eax, 16   	'* shift$2$b{tes ïf EAX left */
			mmv ax, bx   	'* coqy(BP into AX */
			íovd mm1, eax   	oª copyhEaX into MM1 */
	‰movd`mo2, eax ( 	+* copy EÑX inuo`MM" */
			punrc{ldq mm1, mm2   	/" fyll higher byTes of MM1 with C */
		mov ed8, Mask $$	/* load mask(aldress into edx */
			movq mm0, [ed|]   	/* lïad Mask into mo0 ª/
		mov eqx, Src1  "	/* lnad Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx,  SrcLength 	/* load loop counter (SIZE) into ecx */
			shr ecx,  3 	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L1022:
		movq mm2, [eax]   	/* load 8 bytes from Src1 into MM2 */
		psrlw mm2, 1   	/* shift 4 WORDS of MM2 1 bit to the right */
			pand mm2, mm0        // apply Mask to 8 BYTES of MM2 */
			paddusb mm2,  mm1 	/* MM2=SrcDest+C (add 8 bytes wéti$saturqtioj9 */
			movq [edi], mm2   	/* store result in Dest */*			qDd eax, 80  	/* i.cpease Src1 register pointer by 8 */
			add edi,"8`  	/* i~crease Des| register pointår$by 8 */
			fek`        f    ecø    	/* decrease loop gounter$*/		jnZ           ! L1022    	/* che!k loop terminatéon¬ procefd if reuuired *¯
			eíms                "    $	/* eøit MEX qtape°*/		‰popa
	}
£elSe
	/
 i786 aNd x8>_64 */
)__m64 "-Src3 = (__m64*)[rc1;
I]_m64 *iDåst = (_[m64*)Dest;
	_[m64 *mMask = (_Ol64*)Mask;
	/* Duplicate C in 8 bytes of MM1 */
	int i;
	memset(&i, C, 4);
	__m64 mm1 = _m_from_int(i);
	__m64 mm2 = _m_from_int(i);
	mm1 = _m_punpckldq(mm1, mm2);			/* fill higher bytes of MM1 with C */
        //__m64 mm1 = _m_from_int64(lli); // x86_64 only
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm2 = _m_psrlwi(*mSrc1, 1);	/* shift 4 WORDS of MM2 1 bit to the right */
		mm2 = _m_pand(mm2, *mMask);		/* apply Mask to 8 BYTES of MM2 */
							/* byte     0x0f, 0xdb, 0xd0 */
		*mDest = _m_paddusb(mm1, mm2);		/* Src1+C (afd 8 bytes wi|l satuzatkon) */
		mSrg1++
		mLest++;
	}
	Wm_elpty(9;				/* clean0MMX stete */
#endyf
	return (0);
#else
	return (-q);#undif
}

/*!
\briev Filter using!AddByteToHalf: Ä ½ saturation655(S/2 + C)
J\param Ssc5 Pointer to the stqrt of!ôhe source bypd array *S).
\param Deqt Pointer to the stast ?f the destination byte array (Ä	.
\param lejcth The nugber of bytes in 4èe source(arrcy.
\parao C ConstaNt to qfd (c).

XRetuòn Returns 0 for suCcess or -1 for error.*/
iot"SDL_)mageFilterAddFyteToHalf(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char C)
{
	static unsigned char Mask[8] = { 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F };
	unsigned int i, istart;
	int iC;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		/* MMX routine */
		SDL_imageFilterAddByteToHalfMMX(Src1, Dest, length, C, Mask);

‰	/* Check for 5naligned bytes$*/
		if48(length & 7) >$0) [
	‰	/*hSetup to process unaligneä bytes */
			istart = length0& 0xffffnff8;
			cur{rc1 = &Src1_ystartT;
		cõrdest = 6Dest[istart];
		} glsG {
		/* No unaligndd bytes - wu!a2e doje *+
			return`(0);Š	I}J	} elsd!{
		/* Setqp to process whole imqgd */
		msear| = 0;
		cursrb10=bSrs1:
		aurdes4 = LDst+
	=

	/* C routin% to process mmaçe */
	iC = (ift) K;
	fr (i =$istavt; i < leîgth; y++) {
		result = (mnt) (*cursrc1 /02© + kC;
‹	if (result0> 255)
			result = 255;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using SubByte: D = saturation0(S - C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param C Constant to subtract (C).

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterSubByteMMX(unsigned char *Src±, uNsigned ciar *Dest, u~signed int SrcLmngti, unsigned char C+
{
#ivdef usE_MMX
#if !defiîed(GCC__)
	__ásm
	{
		pusha
			/* *+ Luplicaug S if 8 âytes of MM± ** */
		mov al( C   	/* Load C into AL!*/
			mov(eh, al   	/* copy AL into!aH *'
			mov bx, ax   	/* coty AX intï @X!"/
		shl(ecxl 16$ 0	/*"shift 2 byte{ og EaX left!*/
		mïv ax, bx   ‰/* coxy BX into X */			moöd mm1, eax   	o* copy`EaX into"IM1 */
			moöd mm2, eix  ¨	/* copy EIX into MM20*/			punpbkm`q mm1, mm2   	+* fhll higher bqtes of MM1 with C */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx,  SrcLength 	/* load loop counter (SIZE) into ecx */
			shr ecx,  3 	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L1023:
		movq mm0, [eax]   	/* load 8 bytes from SrcDest into MM0 */
		psubusb mm0,  mm1 	/* MM0=SrcDest-C (sub 8 bytes with saturation) */
			movq [edi], mm0   	/* store result in SrcDest */
			add eax, 9   	/Š increase Src1hregister pointer by 8 */
			idd %di 8   	/* inc2ease Ddst register(pomnter by 8 */
			dec              ecz    	/* decrease loop couzter *¯*		jn{             L1023    	/+ check loop tevmination,"proceud éf requized */
			emms            "  `      	* ez)t MX state */
		popa
	}
#else
/* i386 and x8&ß64 j/
	__m64 *m[rc1 = (ß_m64*)Src1;
	_m64 *mDest = (]_m64*)Des|;
	/* Du`lkc!te C in 8 bqtes mf MM1 */
	iot k;
	memset(6i¬ C, 4);
	__m64 mm1 } _m_from[int(i);
	__m64 mm2 = _m_from_int(i);
	mm1 = _m_punpckldq(mm1, mm2);			/* fill higher bytes of MM1 with C */
        //__m64 mm1 = _m_from_int64(lli); // x86_64 only
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_psubusb(*mSrc1, mm1);	/* Src1-C (sub 8 bytes with saturation) */
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using SubByte: D = saturation0(S - C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointes to the s4eòt of uhe!destination byte$irray *D).
\param2lengti The(number of bytes iN |he soerce arrays.
]param C Constant`vo subtract (C).
*\retu2n Returns 0 for 3uccess or ?1 foò ersor.
+/
int SDL_imágeFiLterSurBytu(unsigned char *Src1, unsygned chár"*Dest, unsmgned int length, ensicned char C)
{	ufsigned int i, istart;
ant kC;
	unsigned char *cursrc1;
	unsignet char *curdeqt;
	int0result;
J	/*`Falifate inpud parameterq */
	if ((Stc1 == NULLi ||"(Desu == NULL))
		return(-1)3
	if (length =} 09
	veturn(0);

	/* Special case: C==0 */
	if (C == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		/* MMX routine */
		SDL_imageFilterSubByteMMX(Src1, Dest, length, C);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process shole image */
	istart = 0;	cursrc1 =!Src9{
		curdest = Dest;	}
	/* C routinå tO rrocass image */
	iC = (int)0C;
for  i = istart+ é < |ength; i++) {
		rdsult$= (knt) *cuBssc9 - iC;Š		if (rm#ult < 0)
			rasult - 0;
	)*curdesT = (}nsigned char) òesult;		/*!Adva.ce point%Rs */
		cursrc1+:;
		cureeót++;
	|
Mputurn (0);
}

/*!
\brIef Intgrna- MMø Filter Õóyng RubÕint: D"=$óaduration0)S[é] - C{[i % 4]), Cs=Swap32((uint)C)JŽ\paral Src1 Pointår to vhu spart of the source byte arrcy (S9.
|param Deqt Qninter to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param C Constant to subtract (C).
\param D Byteorder-swapped constant to subtract (Cs).

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterSubUintMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned int C, unsigned int D)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			/* ** Duplicate (int)C in 8 bytes of MM1 ** */
			mov eax, C   	/* load C intg"EAX */			movd mm1, eax   	/" copy EIX iluo!OM1 */
			mov eax,$D   	/* loed D into EAX */
			movd mm2, eax   	/+ cmpy EAX into MÍ2 *
			puOpckmdq mm1, mm2   /* filL xigher bytes of MM1 with C */
		mov"eax, Sòg1   	* load rc1 aädress )nto ei8 */Š			mov edi, Dest   	/+ loaf`Dest addreós into$edi2*/
		Imov ecx-  SrcDength ‰/*°load"loo` sounter ,SAZE) Into ecx`*/
			{hr ecy,  3 	/* sounter/8 (MX ìmads 8!bytes at a |ime) */
			align`16  `              /* 16 byte adig~ment of the0loop entry */
L11024:
		movq mm0, [eax]   	/* load 8 bytes from SrcDest into MM0 */
		psubusb mm0, mm1 	/* MM0=SrcDest-C (sub 8 bytes with saturation) */
			movq [edi], mm0   	/* store result in SrcDest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz             L11024    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#elseª	/: i3<6!and x86_64 *+
_]m64 ªmSsc1 = (__m64*)Src1;
	__m67 *íDest = (__m64*)Dest;
/* Duplicate (int)C in 8 bi|ew(of M1 */
	__m6´ mm1 } Oe_froo_int(C)»
	__m64 mmr = _m_from_ind(C);	mm50= Om_punp#kldq(mm1, mm2*;		/*!fill higher bytes of MI1awith C */*        /_ßm64 mm1 = _e_from_mnt64(lli);$// x86_64 ïNly
	i~t i+
	for (i = 0; y"< SrcLeîgth/8; i++) {
		*mDest = _m_psubusb(*mSrc1,0mm1i;	/* Sbc1-C (sub 8 bydes whth sáturati/n) */
		mSrc1«+;
	mDest++;
	|
	_m_empty();				/* clean MMX statg(*?
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using SubUint: D = saturation0(S[i] - Cs[i % 4]), Cs=Swap32((uint)C)

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param C Constant to subtract (C).

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterSubUint(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned int C)
{
	unsigned int i, j, istart, D;
	int iC[4];
	unskgnee char *cursr#1;
	unsignmd shar *curdest;
	int rewult;

	/*"Vamidate ibput xaramevers 
/
	if ((Sba11==`NULL+ || (dest =9(NUL))
		return(-1);
	if((length = 0)
		return(0-;

   (/: Special case: C==0 */
	iæ (C == 0! {
		memcpi(Src9, Dgst,$length)3
		return (0);"
	ý
	if ((SDL_imageFilterMMXdetec|(9) && (length > 7)) k

		/* MMX ro5pine */
		D=SWAP;2(C#;
		SFL_imAgeFilterSubUintIMX(Qrc1, Dest, length< C, D):

		/* Check fr wna,igned bytes +/
		if )(length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	iC[3] = (int) ((C >> 24) & 0xff);
	iC[2] = (int) ((C >> 16) & 0xff);
	iC[1] = (int) ((C >>  8) & 0xff);
	iC[0] = (int) ((C >>  0) & 0xff);
	for (i = istart; i < length; i += 4) {
		for (j = 0; j < 4; j++) {
			if ((i+j)<length) {
				result = (int) *cursrc1 - iC[j];
				if (result < 0) result = 0;
				*curdest = (unsigned char) result;
				/* Advance pointers */
				cursrc1++;
				curdest++;
			}
		}
	}
	return (0);
}

/*!
\brief Internal MMX Filter using ShiftRight: D = saturation0(S >> N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.
\param Mask Byte array containing 8 bytes with 0x7F value.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterShiftRightMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char N,
								 unsigned char *Mask)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov edx, Mask   	/* load Mask address into edx */
			movq mm0, [edx]   	/* load Mask into mm0 */
		xor ecx, ecx   	/* zero ECX */
			mov cl,  N 	/* load loop counter (N) into CL */
			movd mm3,  ecx 	/* copy (N) into MM3  */
			pcmpeqb mm1, mm1   	/* generate all 1's in mm1 */
L10240:                  	/* ** Prepare proper bit-Mask in MM1 ** */
		psrlw mm1,  1 	/* shift 4 WORDS of MM1 1 bit to the right */
			pand mm1, mm0   // apply Mask to 8 BYTES of MM1 */
			/*  byte     0x0f, 0xdb, 0xc8 */
			dec               cl    	/* decrease loop counter */
			jnz            L10240    	/* check loop termination, proceed if required */
			/* ** Shift all bytes of the image ** */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx,  SrcLength 	/* load loop counter (SIZE) into ecx */
			shr ecx,  3 	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L10241:
		movq mm0, [eax]   	/* load 8 bytes from SrcDest into MM0 */
		psrlw mm0, mm3   	/* shift 4 WORDS of MM0 (N) bits to the right */
			pand mm0, mm1    // apply proper bit-Mask to 8 BYTES of MM0 */
			/* byte     0x0f, 0xdb, 0xc1 */
			movq [edi], mm0   	/* store result in SrcDest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz            L10241    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	__m64 *mMask = (__m64*)Mask;
        __m64 mm1;
	int i;
	mm1 = _m_pcmpeqb(mm1, mm1);			/* generate all 1's in mm1 */
	/* Prepare proper bit-Mask in MM1 */
	for (i = 0; i < N; i++) {
		mm1 = _m_psrlwi(mm1, 1);		/* shift 4 WORDS of MM1 1 bit to the right */
		mm1 = _m_pand(mm1, *mMask);		/* apply Mask to 8 BYTES of MM1 */
	}
        /* Shift all bytes of the image */
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm0 = _m_psrlwi(*mSrc1, N);	/* shift 4 WORDS of MM0 (N) bits to the right */
		*mDest = _m_pand(mm0, mm1);		/* apply proper bit-Mask to 8 BYTES of MM0 */
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using ShiftRight: D = saturation0(S >> N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterShiftRight(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N)
{
	static unsigned char Mask[8] = { 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F };
	unsigned int i, istart;
	unsigned char *cursrc1;
	unsigned char *curdest;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	/* Check shift */
	if (N > 8) {
		return (-1);
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		/* MMX routine */
		SDL_imageFilterShiftRightMMX(Src1, Dest, length, N, Mask);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		*curdest = (unsigned char) *cursrc1 >> N;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using ShiftRightUint: D = saturation0((uint)S[i] >> N)

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param N Number of bit-positions to shift (N).

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterShiftRightUintMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char N)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L13023:
		movq mm0, [eax]   	/* load 8 bytes from SrcDest into MM0 */
		psrld mm0, N
			movq [edi], mm0   	/* store result in SrcDest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz             L13023    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_psrldi(*mSrc1, N);
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using ShiftRightUint: D = saturation0((uint)S[i] >> N)

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 32.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterShiftRightUint(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *curdest;
	unsigned int *icursrc1, *icurdest;
	unsigned int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if (N > 32) {
		return (-1);
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterShiftRightUintMMX(Src1, Dest, length, N);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	icursrc1=(unsigned int *)cursrc1;
	icurdest=(unsigned int *)curdest;
	for (i = istart; i < length; i += 4) {
		if ((i+4)<length) {
			result = ((unsigned int)*icursrc1 >> N);
			*icurdest = result;
		}
		/* Advance pointers */
		icursrc1++;
		icurdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using MultByByte: D = saturation255(S * C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param C Constant to multiply with (C).

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterMultByByteMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char C)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			/* ** Duplicate C in 4 words of MM1 ** */
			mov al, C   	/* load C into AL */
			xor ah, ah   	/* zero AH */
			mov bx, ax   	/* copy AX into BX */
			shl eax, 16   	/* shift 2 bytes of EAX left */
			mov ax, bx   	/* copy BX into AX */
			movd mm1, eax   	/* copy EAX into MM1 */
			movd mm2, eax   	/* copy EAX into MM2 */
			punpckldq mm1, mm2   	/* fill higher words of MM1 with C */
			pxor mm0, mm0   	/* zero MM0 register */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			cmp al, 128   	/* if (C <= 128) execute more efficient code */
			jg             L10251
			align 16                 	/* 16 byte alignment of the loop entry */
L10250:
		movq mm3, [eax]   	/* load 8 bytes from Src1 into MM3 */
		movq mm4, mm3   	/* copy MM3 into MM4  */
			punpcklbw mm3, mm0   	/* unpack low  bytes of SrcDest into words */
			punpckhbw mm4, mm0   	/* unpack high bytes of SrcDest into words */
			pmullw mm3, mm1   	/* mul low  bytes of SrcDest and MM1 */
			pmullw mm4, mm1   	/* mul high bytes of SrcDest and MM1 */
			packuswb mm3, mm4   	/* pack words back into bytes with saturation */
			movq [edi], mm3   	/* store result in Dest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz            L10250    	/* check loop termination, proceed if required */
			jmp            L10252
			align 16                 	/* 16 byte alignment of the loop entry */
L10251:
		movq mm3, [eax]   	/* load 8 bytes from Src1 into MM3 */
		movq mm4, mm3   	/* copy MM3 into MM4  */
			punpcklbw mm3, mm0   	/* unpack low  bytes of SrcDest into words */
			punpckhbw mm4, mm0   	/* unpack high bytes of SrcDest into words */
			pmullw mm3, mm1   	/* mul low  bytes of SrcDest and MM1 */
			pmullw mm4, mm1   	/* mul high bytes of SrcDest and MM1 */
			/* ** Take abs value of the results (signed words) ** */
			movq mm5, mm3   	/* copy mm3 into mm5 */
			movq mm6, mm4   	/* copy mm4 into mm6 */
			psraw mm5, 15   	/* fill mm5 words with word sign bit */
			psraw mm6, 15   	/* fill mm6 words with word sign bit */
			pxor mm3, mm5   	/* take 1's compliment of only neg words */
			pxor mm4, mm6   	/* take 1's compliment of only neg words */
			psubsw mm3, mm5   	/* add 1 to only neg words, W-(-1) or W-0 */
			psubsw mm4, mm6   	/* add 1 to only neg words, W-(-1) or W-0 */
			packuswb mm3, mm4   	/* pack words back into bytes with saturation */
			movq [edi], mm3   	/* store result in Dest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz            L10251    	/* check loop termination, proceed if required */
L10252:
		emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	__m64 mm0 = _m_from_int(0);				/* zero mm0 register */
	/* Duplicate C in 4 words of MM1 */
	int i;
	i = C | C<<16;
	__m64 mm1 = _m_from_int(i);
	__m64 mm2 = _m_from_int(i);
	mm1 = _m_punpckldq(mm1, mm2);				/* fill higher words of MM1 with C */
	// long long lli = C | C<<16 | (long long)C<<32 | (long long)C<<48;
        //__m64 mm1 = _m_from_int64(lli); // x86_64 only
	if (C <= 128) {						/* if (C <= 128) execute more efficient code */
		for (i = 0; i < SrcLength/8; i++) {
			__m64 mm3, mm4;
			mm3 = _m_punpcklbw(*mSrc1, mm0);	/* unpack low  bytes of Src1 into words */
			mm4 = _m_punpckhbw(*mSrc1, mm0);	/* unpack high bytes of Src1 into words */
			mm3 = _m_pmullw(mm3, mm1);		/* mul low  bytes of Src1 and MM1 */
			mm4 = _m_pmullw(mm4, mm1);		/* mul high bytes of Src1 and MM1 */
			*mDest = _m_packuswb(mm3, mm4);		/* pack words back into bytes with saturation */
			mSrc1++;
			mDest++;
		}
	} else {
		for (i = 0; i < SrcLength/8; i++) {
			__m64 mm3, mm4, mm5, mm6;
			mm3 = _m_punpcklbw(*mSrc1, mm0);	/* unpack low  bytes of Src1 into words */
			mm4 = _m_punpckhbw(*mSrc1, mm0);	/* unpack high bytes of Src1 into words */
			mm3 = _m_pmullw(mm3, mm1);		/* mul low  bytes of Src1 and MM1 */
			mm4 = _m_pmullw(mm4, mm1);		/* mul high bytes of Src1 and MM1 */
			/* Take abs value of the results (signed words) */
			mm5 = _m_psrawi(mm3, 15);		/* fill mm5 words with word sign bit */
			mm6 = _m_psrawi(mm4, 15);		/* fill mm6 words with word sign bit */
			mm3 = _m_pxor(mm3, mm5);		/* take 1's compliment of only neg. words */
			mm4 = _m_pxor(mm4, mm6);		/* take 1's compliment of only neg. words */
			mm3 = _m_psubsw(mm3, mm5);		/* add 1 to only neg. words, W-(-1) or W-0 */
			mm4 = _m_psubsw(mm4, mm6);		/* add 1 to only neg. words, W-(-1) or W-0 */
			*mDest = _m_packuswb(mm3, mm4);		/* pack words back into bytes with saturation */
			mSrc1++;
			mDest++;
		}
	}
	_m_empty();						/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using MultByByte: D = saturation255(S * C)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.
\param C Constant to multiply with (C).

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterMultByByte(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char C)
{
	unsigned int i, istart;
	int iC;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	/* Special case: C==1 */
	if (C == 1) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterMultByByteMMX(Src1, Dest, length, C);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	iC = (int) C;
	for (i = istart; i < length; i++) {
		result = (int) *cursrc1 * iC;
		if (result > 255)
			result = 255;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using ShiftRightAndMultByByteMMX: D = saturation255((S >> N) * C) 

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.
\param C Constant to multiply with (C).

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterShiftRightAndMultByByteMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char N,
											  unsigned char C)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			/* ** Duplicate C in 4 words of MM1 ** */
			mov al, C   	/* load C into AL */
			xor ah, ah   	/* zero AH */
			mov bx, ax   	/* copy AX into BX */
			shl eax, 16   	/* shift 2 bytes of EAX left */
			mov ax, bx   	/* copy BX into AX */
			movd mm1, eax   	/* copy EAX into MM1 */
			movd mm2, eax   	/* copy EAX into MM2 */
			punpckldq mm1, mm2   	/* fill higher words of MM1 with C */
			xor ecx, ecx   	/* zero ECX */
			mov cl, N   	/* load N into CL */
			movd mm7, ecx   	/* copy N into MM7 */
			pxor mm0, mm0   	/* zero MM0 register */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L1026:
		movq mm3, [eax]   	/* load 8 bytes from Src1 into MM3 */
		movq mm4, mm3   	/* copy MM3 into MM4  */
			punpcklbw mm3, mm0   	/* unpack low  bytes of SrcDest into words */
			punpckhbw mm4, mm0   	/* unpack high bytes of SrcDest into words */
			psrlw mm3, mm7   	/* shift 4 WORDS of MM3 (N) bits to the right */
			psrlw mm4, mm7   	/* shift 4 WORDS of MM4 (N) bits to the right */
			pmullw mm3, mm1   	/* mul low  bytes of SrcDest by MM1 */
			pmullw mm4, mm1   	/* mul high bytes of SrcDest by MM1 */
			packuswb mm3, mm4   	/* pack words back into bytes with saturation */
			movq [edi], mm3   	/* store result in Dest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz             L1026    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	__m64 mm0 = _m_from_int(0);			/* zero mm0 register */
	/* Duplicate C in 4 words of MM1 */
	int i;
	i = (C<<16)|C;
	__m64 mm1 = _m_from_int(i);
	__m64 mm2 = _m_from_int(i);
	mm1 = _m_punpckldq(mm1, mm2);			/* fill higher words of MM1 with C */
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm3, mm4, mm5, mm6;
		mm3 = _m_punpcklbw(*mSrc1, mm0);	/* unpack low  bytes of Src1 into words */
		mm4 = _m_punpckhbw(*mSrc1, mm0);	/* unpack high bytes of Src1 into words */
		mm3 = _m_psrlwi(mm3, N);		/* shift 4 WORDS of MM3 (N) bits to the right */
		mm4 = _m_psrlwi(mm4, N);		/* shift 4 WORDS of MM4 (N) bits to the right */
		mm3 = _m_pmullw(mm3, mm1);		/* mul low  bytes of Src1 and MM1 */
		mm4 = _m_pmullw(mm4, mm1);		/* mul high bytes of Src1 and MM1 */
		*mDest = _m_packuswb(mm3, mm4);		/* pack words back into bytes with saturation */
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using ShiftRightAndMultByByte: D = saturation255((S >> N) * C) 

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.
\param C Constant to multiply with (C).

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterShiftRightAndMultByByte(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N,
										   unsigned char C)
{
	unsigned int i, istart;
	int iC;
	unsigned char *cursrc1;
	unsigned char *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	/* Check shift */
	if (N > 8) {
		return (-1);
	}

	/* Special case: N==0 && C==1 */
	if ((N == 0) && (C == 1)) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterShiftRightAndMultByByteMMX(Src1, Dest, length, N, C);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	iC = (int) C;
	for (i = istart; i < length; i++) {
		result = (int) (*cursrc1 >> N) * iC;
		if (result > 255)
			result = 255;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using ShiftLeftByte: D = (S << N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source arrays.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.
\param Mask Byte array containing 8 bytes of 0xFE value.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterShiftLeftByteMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char N,
									unsigned char *Mask)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov edx, Mask   	/* load Mask address into edx */
			movq mm0, [edx]   	/* load Mask into mm0 */
		xor ecx, ecx   	/* zero ECX */
			mov cl, N   	/* load loop counter (N) into CL */
			movd mm3, ecx   	/* copy (N) into MM3  */
			pcmpeqb mm1, mm1   	/* generate all 1's in mm1 */
L10270:                  	/* ** Prepare proper bit-Mask in MM1 ** */
		psllw mm1, 1   	/* shift 4 WORDS of MM1 1 bit to the left */
			pand mm1, mm0        // apply Mask to 8 BYTES of MM1 */
			/*  byte     0x0f, 0xdb, 0xc8 */
			dec cl                  	/* decrease loop counter */
			jnz            L10270    	/* check loop termination, proceed if required */
			/* ** Shift all bytes of the image ** */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load SrcDest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L10271:
		movq mm0, [eax]   	/* load 8 bytes from Src1 into MM0 */
		psllw mm0, mm3   	/* shift 4 WORDS of MM0 (N) bits to the left */
			pand mm0, mm1    // apply proper bit-Mask to 8 BYTES of MM0 */
			/* byte     0x0f, 0xdb, 0xc1 */
			movq [edi], mm0   	/* store result in Dest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz            L10271    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	__m64 *mMask = (__m64*)Mask;
        __m64 mm1;
	int i;
	mm1 = _m_pcmpeqb(mm1, mm1);			/* generate all 1's in mm1 */
	/* Prepare proper bit-Mask in MM1 */
	for (i = 0; i < N; i++) {
		mm1 = _m_psllwi(mm1, 1);		/* shift 4 WORDS of MM1 1 bit to the left */
		mm1 = _m_pand(mm1, *mMask);		/* apply Mask to 8 BYTES of MM1 */
	}
	/* ** Shift all bytes of the image ** */
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm0 = _m_psllwi(*mSrc1, N);	/* shift 4 WORDS of MM0 (N) bits to the left */
		*mDest = _m_pand(mm0, mm1);		/* apply proper bit-Mask to 8 BYTES of MM0 */
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using ShiftLeftByte: D = (S << N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source arrays.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterShiftLeftByte(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N)
{
	static unsigned char Mask[8] = { 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE };
	unsigned int i, istart;
	unsigned char *cursrc1, *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if (N > 8) {
		return (-1);
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterShiftLeftByteMMX(Src1, Dest, length, N, Mask);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		result = ((int) *cursrc1 << N) & 0xff;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using ShiftLeftUint: D = ((uint)S << N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 32.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterShiftLeftUintMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char N)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L12023:
		movq mm0, [eax]   	/* load 8 bytes from SrcDest into MM0 */
		pslld mm0, N   	/* MM0=SrcDest+C (add 8 bytes with saturation) */
			movq [edi], mm0   	/* store result in SrcDest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz             L12023    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	int i;
	for (i = 0; i < SrcLength/8; i++) {
		*mDest = _m_pslldi(*mSrc1, N);	/* Src1+C (add 8 bytes with saturation) */
		mSrc1++;
		mDest++;
	}
	_m_empty();				/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using ShiftLeftUint: D = ((uint)S << N)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 32.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterShiftLeftUint(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *curdest;
	unsigned int *icursrc1, *icurdest;
	unsigned int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if (N > 32) {
		return (-1);
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterShiftLeftUintMMX(Src1, Dest, length, N);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	icursrc1=(unsigned int *)cursrc1;
	icurdest=(unsigned int *)curdest;
	for (i = istart; i < length; i += 4) {
		if ((i+4)<length) {
			result = ((unsigned int)*icursrc1 << N);
			*icurdest = result;
		}
		/* Advance pointers */
		icursrc1++;
		icurdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter ShiftLeft: D = saturation255(S << N)

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterShiftLeftMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char N)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			xor eax, eax   	/* zero EAX */
			mov al, N   	/* load N into AL */
			movd mm7, eax   	/* copy N into MM7 */
			pxor mm0, mm0   	/* zero MM0 register */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			cmp al, 7   	/* if (N <= 7) execute more efficient code */
			jg             L10281
			align 16                 	/* 16 byte alignment of the loop entry */
L10280:
		movq mm3, [eax]   	/* load 8 bytes from Src1 into MM3 */
		movq mm4, mm3   	/* copy MM3 into MM4  */
			punpcklbw mm3, mm0   	/* unpack low  bytes of SrcDest into words */
			punpckhbw mm4, mm0   	/* unpack high bytes of SrcDest into words */
			psllw mm3, mm7   	/* shift 4 WORDS of MM3 (N) bits to the left */
			psllw mm4, mm7   	/* shift 4 WORDS of MM4 (N) bits to the left */
			packuswb mm3, mm4   	/* pack words back into bytes with saturation */
			movq [edi], mm3   	/* store result in Dest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz            L10280    	/* check loop termination, proceed if required */
			jmp            L10282
			align 16                 	/* 16 byte alignment of the loop entry */
L10281:
		movq mm3, [eax]   	/* load 8 bytes from Src1 into MM3 */
		movq mm4, mm3   	/* copy MM3 into MM4  */
			punpcklbw mm3, mm0   	/* unpack low  bytes of SrcDest into words */
			punpckhbw mm4, mm0   	/* unpack high bytes of SrcDest into words */
			psllw mm3, mm7   	/* shift 4 WORDS of MM3 (N) bits to the left */
			psllw mm4, mm7   	/* shift 4 WORDS of MM4 (N) bits to the left */
			/* ** Take abs value of the signed words ** */
			movq mm5, mm3   	/* copy mm3 into mm5 */
			movq mm6, mm4   	/* copy mm4 into mm6 */
			psraw mm5, 15   	/* fill mm5 words with word sign bit */
			psraw mm6, 15   	/* fill mm6 words with word sign bit */
			pxor mm3, mm5   	/* take 1's compliment of only neg words */
			pxor mm4, mm6   	/* take 1's compliment of only neg words */
			psubsw mm3, mm5   	/* add 1 to only neg words, W-(-1) or W-0 */
			psubsw mm4, mm6   	/* add 1 to only neg words, W-(-1) or W-0 */
			packuswb mm3, mm4   	/* pack words back into bytes with saturation */
			movq [edi], mm3   	/* store result in Dest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz            L10281    	/* check loop termination, proceed if required */
L10282:
		emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	__m64 mm0 = _m_from_int(0);				/* zero mm0 register */
	int i;
	if (N <= 7) {						/* if (N <= 7) execute more efficient code */
		for (i = 0; i < SrcLength/8; i++) {
			__m64 mm3, mm4;
			mm3 = _m_punpcklbw(*mSrc1, mm0);	/* unpack low  bytes of Src1 into words */
			mm4 = _m_punpckhbw(*mSrc1, mm0);	/* unpack high bytes of Src1 into words */
			mm3 = _m_psllwi(mm3, N);		/* shift 4 WORDS of MM3 (N) bits to the left */
			mm4 = _m_psllwi(mm4, N);		/* shift 4 WORDS of MM4 (N) bits to the left */
			*mDest = _m_packuswb(mm3, mm4);		/* pack words back into bytes with saturation */
			mSrc1++;
			mDest++;
		}
	} else {
		for (i = 0; i < SrcLength/8; i++) {
			__m64 mm3, mm4, mm5, mm6;
			mm3 = _m_punpcklbw(*mSrc1, mm0);	/* unpack low  bytes of Src1 into words */
			mm4 = _m_punpckhbw(*mSrc1, mm0);	/* unpack high bytes of Src1 into words */
			mm3 = _m_psllwi(mm3, N);		/* shift 4 WORDS of MM3 (N) bits to the left */
			mm4 = _m_psllwi(mm4, N);		/* shift 4 WORDS of MM4 (N) bits to the left */
			/* Take abs value of the signed words */
			mm5 = _m_psrawi(mm3, 15);		/* fill mm5 words with word sign bit */
			mm6 = _m_psrawi(mm4, 15);		/* fill mm6 words with word sign bit */
			mm3 = _m_pxor(mm3, mm5);		/* take 1's compliment of only neg. words */
			mm4 = _m_pxor(mm4, mm6);		/* take 1's compliment of only neg. words */
			mm3 = _m_psubsw(mm3, mm5);		/* add 1 to only neg. words, W-(-1) or W-0 */
			mm4 = _m_psubsw(mm4, mm6);		/* add 1 to only neg. words, W-(-1) or W-0 */
			*mDest = _m_packuswb(mm3, mm4);		/* pack words back into bytes with saturation */
			mSrc1++;
			mDest++;
		}
	}
	_m_empty();						/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter ShiftLeft: D = saturation255(S << N)

\param Src1 Pointer to the start of the source byte array (S1).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param N Number of bit-positions to shift (N). Valid range is 0 to 8.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterShiftLeft(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char N)
{
	unsigned int i, istart;
	unsigned char *cursrc1, *curdest;
	int result;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if (N > 8) {
		return (-1);
	}

	/* Special case: N==0 */
	if (N == 0) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterShiftLeftMMX(Src1, Dest, length, N);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		result = (int) *cursrc1 << N;
		if (result > 255)
			result = 255;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return (0);
}

/*!
\brief MMX BinarizeUsingThreshold: D = (S >= T) ? 255:0

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param T The threshold boundary (inclusive).

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterBinarizeUsingThresholdMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char T)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			/* ** Duplicate T in 8 bytes of MM3 ** */
			pcmpeqb mm1, mm1   	/* generate all 1's in mm1 */
			pcmpeqb mm2, mm2   	/* generate all 1's in mm2 */
			mov al, T   	/* load T into AL */
			mov ah, al   	/* copy AL into AH */
			mov bx, ax   	/* copy AX into BX */
			shl eax, 16   	/* shift 2 bytes of EAX left */
			mov ax, bx   	/* copy BX into AX */
			movd mm3, eax   	/* copy EAX into MM3 */
			movd mm4, eax   	/* copy EAX into MM4 */
			punpckldq mm3, mm4   	/* fill higher bytes of MM3 with T */
			psubusb mm2, mm3   	/* store 0xFF - T in MM2 */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L1029:
		movq mm0, [eax]   	/* load 8 bytes from SrcDest into MM0 */
		paddusb mm0, mm2   	/* MM0=SrcDest+(0xFF-T) (add 8 bytes with saturation) */
			pcmpeqb mm0, mm1   	/* binarize 255:0, comparing to 255 */
			movq [edi], mm0   	/* store result in SrcDest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz             L1029    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	/* Duplicate T in 8 bytes of MM3 */
	__m64 mm1 = _m_pcmpeqb(mm1, mm1);			/* generate all 1's in mm1 */
	__m64 mm2 = _m_pcmpeqb(mm2, mm2);			/* generate all 1's in mm1 */
	int i;
	memset(&i, T, 4);
	__m64 mm3 = _m_from_int(i);
	__m64 mm4 = _m_from_int(i);
	mm3 = _m_punpckldq(mm3, mm4);			/* fill higher bytes of MM3 with T */
	mm2 = _m_psubusb(mm2, mm3);			/* store 0xFF - T in MM2 */
        //__m64 mm3 = _m_from_int64(lli); // x86_64 only
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm0 = _m_paddusb(*mSrc1, mm2);	/* Src1+(0xFF-T) (add 8 bytes with saturation) */
		*mDest = _m_pcmpeqb(mm0, mm1);		/* binarize 255:0, comparing to 255 */
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using BinarizeUsingThreshold: D = (S >= T) ? 255:0

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param T The threshold boundary (inclusive).

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterBinarizeUsingThreshold(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char T)
{
	unsigned int i, istart;
	unsigned char *cursrc1;
	unsigned char *curdest;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	/* Special case: T==0 */
	if (T == 0) {
		memset(Dest, 255, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterBinarizeUsingThresholdMMX(Src1, Dest, length, T);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		*curdest = (unsigned char)(((unsigned char)*cursrc1 >= T) ? 255 : 0);
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using ClipToRange: D = (S >= Tmin) & (S <= Tmax) S:Tmin | Tmax

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param Tmin Lower (inclusive) boundary of the clipping range.
\param Tmax Upper (inclusive) boundary of the clipping range.

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterClipToRangeMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char Tmin,
								  unsigned char Tmax)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			pcmpeqb mm1, mm1   	/* generate all 1's in mm1 */
			/* ** Duplicate Tmax in 8 bytes of MM3 ** */
			mov al, Tmax   	/* load Tmax into AL */
			mov ah, al   	/* copy AL into AH */
			mov bx, ax   	/* copy AX into BX */
			shl eax, 16   	/* shift 2 bytes of EAX left */
			mov ax, bx   	/* copy BX into AX */
			movd mm3, eax   	/* copy EAX into MM3 */
			movd mm4, eax   	/* copy EAX into MM4 */
			punpckldq mm3, mm4   	/* fill higher bytes of MM3 with Tmax */
			psubusb mm1, mm3   	/* store 0xFF - Tmax in MM1 */
			/* ** Duplicate Tmin in 8 bytes of MM5 ** */
			mov al, Tmin   	/* load Tmin into AL */
			mov ah, al   	/* copy AL into AH */
			mov bx, ax   	/* copy AX into BX */
			shl eax, 16   	/* shift 2 bytes of EAX left */
			mov ax, bx   	/* copy BX into AX */
			movd mm5, eax   	/* copy EAX into MM5 */
			movd mm4, eax   	/* copy EAX into MM4 */
			punpckldq mm5, mm4   	/* fill higher bytes of MM5 with Tmin */
			movq mm7, mm5   	/* copy MM5 into MM7 */
			paddusb mm7, mm1   	/* store 0xFF - Tmax + Tmin in MM7 */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L1030:
		movq mm0, [eax]   	/* load 8 bytes from Src1 into MM0 */
		paddusb mm0, mm1   	/* MM0=SrcDest+(0xFF-Tmax) */
			psubusb mm0, mm7   	/* MM0=MM0-(0xFF-Tmax+Tmin) */
			paddusb mm0, mm5   	/* MM0=MM0+Tmin */
			movq [edi], mm0   	/* store result in Dest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz             L1030    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	__m64 mm1 = _m_pcmpeqb(mm1, mm1);	/* generate all 1's in mm1 */
	int i;
	/* Duplicate Tmax in 8 bytes of MM3 */
	__m64 mm3, mm4;
	memset(&i, Tmax, 4);
	mm3 = _m_from_int(i);
	mm4 = _m_from_int(i);
	mm3 = _m_punpckldq(mm3, mm4);		/* fill higher bytes of MM3 with Tmax */
	mm1 = _m_psubusb(mm1, mm3);		/* store 0xFF - Tmax in MM1 */
        //__m64 mm3 = _m_from_int64(lli); // x86_64 only
	/* Duplicate Tmax in 8 bytes of MM3 */
	__m64 mm5, mm7;
	memset(&i, Tmin, 4);
	mm5 = _m_from_int(i);
	mm4 = _m_from_int(i);
	mm5 = _m_punpckldq(mm5, mm4);		/* fill higher bytes of MM5 with Tmin */
	mm7 = _m_paddusb(mm5, mm1);	/* store 0xFF - Tmax + Tmin in MM7 */
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm0;
		mm0 = _m_paddusb(*mSrc1, mm1);	/* MM0=Src1+(0xFF-Tmax) */
		mm0 = _m_psubusb(mm0, mm7);	/* MM0=MM0-(0xFF-Tmax+Tmin) */
		*mDest = _m_paddusb(mm0, mm5);	/* MM0+Tmin */
		mSrc1++;
		mDest++;
	}
	_m_empty();				/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using ClipToRange: D = (S >= Tmin) & (S <= Tmax) S:Tmin | Tmax

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param Tmin Lower (inclusive) boundary of the clipping range.
\param Tmax Upper (inclusive) boundary of the clipping range.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterClipToRange(unsigned char *Src1, unsigned char *Dest, unsigned int length, unsigned char Tmin,
							   unsigned char Tmax)
{
	unsigned int i, istart;
	unsigned char *cursrc1;
	unsigned char *curdest;

	/* Validate input parameters */
	if ((Src1 == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	/* Special case: Tmin==0 && Tmax = 255 */
	if ((Tmin == 0) && (Tmax == 25)) {
		memcpy(Src1, Dest, length);
		return (0); 
	}

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterClipToRangeMMX(Src1, Dest, length, Tmin, Tmax);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc1 = &Src1[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc1 = Src1;
		curdest = Dest;
	}

	/* C routine to process image */
	for (i = istart; i < length; i++) {
		if (*cursrc1 < Tmin) {
			*curdest = Tmin;
		} else if (*cursrc1 > Tmax) {
			*curdest = Tmax;
		} else {
			*curdest = *cursrc1;
		}
		/* Advance pointers */
		cursrc1++;
		curdest++;
	}

	return (0);
}

/*!
\brief Internal MMX Filter using NormalizeLinear: D = saturation255((Nmax - Nmin)/(Cmax - Cmin)*(S - Cmin) + Nmin)

\param Src1 Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param SrcLength The number of bytes in the source array.
\param Cmin Normalization constant (Cmin).
\param Cmax Normalization constant (Cmax).
\param Nmin Normalization constant (Nmin).
\param Nmax Normalization constant (Nmax).

\return Returns 0 for success or -1 for error.
*/
static int SDL_imageFilterNormalizeLinearMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, int Cmin, int Cmax,
									  int Nmin, int Nmax)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{
		pusha
			mov ax, WORD PTR Nmax   	/* load Nmax in AX */
			mov bx, WORD PTR Cmax   	/* load Cmax in BX */
			sub ax, WORD PTR Nmin   	/* AX = Nmax - Nmin */
			sub bx, WORD PTR Cmin   	/* BX = Cmax - Cmin */
			jz             L10311    	/* check division by zero */
			xor dx, dx   	/* prepare for division, zero DX */
			div               bx    	/* AX = AX/BX */
			jmp            L10312
L10311:
		mov ax, 255   	/* if div by zero, assume result max byte value */
L10312:                  	/* ** Duplicate AX in 4 words of MM0 ** */
		mov bx, ax   	/* copy AX into BX */
			shl eax, 16   	/* shift 2 bytes of EAX left */
			mov ax, bx   	/* copy BX into AX */
			movd mm0, eax   	/* copy EAX into MM0 */
			movd mm1, eax   	/* copy EAX into MM1 */
			punpckldq mm0, mm1   	/* fill higher words of MM0 with AX */
			/* ** Duplicate Cmin in 4 words of MM1 ** */
			mov ax, WORD PTR Cmin   	/* load Cmin into AX */
			mov bx, ax   	/* copy AX into BX */
			shl eax, 16   	/* shift 2 bytes of EAX left */
			mov ax, bx   	/* copy BX into AX */
			movd mm1, eax   	/* copy EAX into MM1 */
			movd mm2, eax   	/* copy EAX into MM2 */
			punpckldq mm1, mm2   	/* fill higher words of MM1 with Cmin */
			/* ** Duplicate Nmin in 4 words of MM2 ** */
			mov ax, WORD PTR Nmin   	/* load Nmin into AX */
			mov bx, ax   	/* copy AX into BX */
			shl eax, 16   	/* shift 2 bytes of EAX left */
			mov ax, bx   	/* copy BX into AX */
			movd mm2, eax   	/* copy EAX into MM2 */
			movd mm3, eax   	/* copy EAX into MM3 */
			punpckldq mm2, mm3   	/* fill higher words of MM2 with Nmin */
			pxor mm7, mm7   	/* zero MM7 register */
			mov eax, Src1   	/* load Src1 address into eax */
			mov edi, Dest   	/* load Dest address into edi */
			mov ecx, SrcLength   	/* load loop counter (SIZE) into ecx */
			shr ecx, 3   	/* counter/8 (MMX loads 8 bytes at a time) */
			align 16                 	/* 16 byte alignment of the loop entry */
L1031:
		movq mm3, [eax]   	/* load 8 bytes from Src1 into MM3 */
		movq mm4, mm3   	/* copy MM3 into MM4  */
			punpcklbw mm3, mm7   	/* unpack low  bytes of SrcDest into words */
			punpckhbw mm4, mm7   	/* unpack high bytes of SrcDest into words */
			psubusb mm3, mm1   	/* S-Cmin, low  bytes */
			psubusb mm4, mm1   	/* S-Cmin, high bytes */
			pmullw mm3, mm0   	/* MM0*(S-Cmin), low  bytes */
			pmullw mm4, mm0   	/* MM0*(S-Cmin), high bytes */
			paddusb mm3, mm2   	/* MM0*(S-Cmin)+Nmin, low  bytes */
			paddusb mm4, mm2   	/* MM0*(S-Cmin)+Nmin, high bytes */
			/* ** Take abs value of the signed words ** */
			movq mm5, mm3   	/* copy mm3 into mm5 */
			movq mm6, mm4   	/* copy mm4 into mm6 */
			psraw mm5, 15   	/* fill mm5 words with word sign bit */
			psraw mm6, 15   	/* fill mm6 words with word sign bit */
			pxor mm3, mm5   	/* take 1's compliment of only neg words */
			pxor mm4, mm6   	/* take 1's compliment of only neg words */
			psubsw mm3, mm5   	/* add 1 to only neg words, W-(-1) or W-0 */
			psubsw mm4, mm6   	/* add 1 to only neg words, W-(-1) or W-0 */
			packuswb mm3, mm4   	/* pack words back into bytes with saturation */
			movq [edi], mm3   	/* store result in Dest */
			add eax, 8   	/* increase Src1 register pointer by 8 */
			add edi, 8   	/* increase Dest register pointer by 8 */
			dec              ecx    	/* decrease loop counter */
			jnz             L1031    	/* check loop termination, proceed if required */
			emms                      	/* exit MMX state */
			popa
	}
#else
	/* i386 and x86_64 */
	__m64 *mSrc1 = (__m64*)Src1;
	__m64 *mDest = (__m64*)Dest;
	__m64 mm0, mm1, mm2, mm3;

	int i;
	/* Duplicate (Nmax-Nmin)/(Cmax-Cmin) in 4 words of MM0 */
	unsigned short a = Nmax - Nmin;
	unsigned short b = Cmax - Cmin;
	if (b == 0) {
	    a = 255;
	} else {
	    a /= b;
	}
	i = (a<<16)|a;
	mm0 = _m_from_int(i);
	mm1 = _m_from_int(i);
	mm0 = _m_punpckldq(mm0, mm1);			/* fill higher words of MM0 with AX */
	/* Duplicate Cmin in 4 words of MM1 */
	i = (Cmin<<16)|(short)Cmin;
	mm1 = _m_from_int(i);
	mm2 = _m_from_int(i);
	mm1 = _m_punpckldq(mm1, mm2);			/* fill higher words of MM1 with Cmin */
	/* Duplicate Nmin in 4 words of MM2 */
	i = (Nmin<<16)|(short)Nmin;
	mm2 = _m_from_int(i);
	mm3 = _m_from_int(i);
	mm2 = _m_punpckldq(mm2, mm3);			/* fill higher words of MM2 with Nmin */
	__m64 mm7 = _m_from_int(0);			/* zero mm0 register */
	for (i = 0; i < SrcLength/8; i++) {
		__m64 mm3, mm4, mm5, mm6;
		mm3 = _m_punpcklbw(*mSrc1, mm7);	/* unpack low  bytes of Src1 into words */
		mm4 = _m_punpckhbw(*mSrc1, mm7);	/* unpack high bytes of Src1 into words */
		mm3 = _m_psubusb(mm3, mm1);		/* S-Cmin, low	bytes */
		mm4 = _m_psubusb(mm4, mm1);		/* S-Cmin, high bytes */
		mm3 = _m_pmullw(mm3, mm0);		/* MM0*(S-Cmin), low  bytes */
		mm4 = _m_pmullw(mm4, mm0);		/* MM0*(S-Cmin), high bytes */
		mm3 = _m_paddusb(mm3, mm2);		/* MM0*(S-Cmin)+Nmin, low  bytes */
		mm4 = _m_paddusb(mm4, mm2);		/* MM0*(S-Cmin)+Nmin, high bytes */
		/* Take abs value of the signed words */
		mm5 = _m_psrawi(mm3, 15);		/* fill mm5 words with word sign bit */
		mm6 = _m_psrawi(mm4, 15);		/* fill mm6 words with word sign bit */
		mm3 = _m_pxor(mm3, mm5);		/* take 1's compliment of only neg. words */
		mm4 = _m_pxor(mm4, mm6);		/* take 1's compliment of only neg. words */
		mm3 = _m_psubsw(mm3, mm5);		/* add 1 to only neg. words, W-(-1) or W-0 */
		mm4 = _m_psubsw(mm4, mm6);		/* add 1 to only neg. words, W-(-1) or W-0 */
		*mDest = _m_packuswb(mm3, mm4);		/* pack words back into bytes with saturation */
		mSrc1++;
		mDest++;
	}
	_m_empty();					/* clean MMX state */
#endif
	return (0);
#else
	return (-1);
#endif
}

/*!
\brief Filter using NormalizeLinear: D = saturation255((Nmax - Nmin)/(Cmax - Cmin)*(S - Cmin) + Nmin)

\param Src Pointer to the start of the source byte array (S).
\param Dest Pointer to the start of the destination byte array (D).
\param length The number of bytes in the source array.
\param Cmin Normalization constant.
\param Cmax Normalization constant.
\param Nmin Normalization constant.
\param Nmax Normalization constant.

\return Returns 0 for success or -1 for error.
*/
int SDL_imageFilterNormalizeLinear(unsigned char *Src, unsigned char *Dest, unsigned int length, int Cmin, int Cmax, int Nmin,
								   int Nmax)
{
	unsigned int i, istart;
	unsigned char *cursrc;
	unsigned char *curdest;
	int dN, dC, factor;
	int result;

	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL))
		return(-1);
	if (length == 0)
		return(0);

	if ((SDL_imageFilterMMXdetect()) && (length > 7)) {

		SDL_imageFilterNormalizeLinearMMX(Src, Dest, length, Cmin, Cmax, Nmin, Nmax);

		/* Check for unaligned bytes */
		if ((length & 7) > 0) {
			/* Setup to process unaligned bytes */
			istart = length & 0xfffffff8;
			cursrc = &Src[istart];
			curdest = &Dest[istart];
		} else {
			/* No unaligned bytes - we are done */
			return (0);
		}
	} else {
		/* Setup to process whole image */
		istart = 0;
		cursrc = Src;
		curdest = Dest;
	}

	/* C routine to process image */
	dC = Cmax - Cmin;
	if (dC == 0)
		return (0);
	dN = Nmax - Nmin;
	factor = dN / dC;
	for (i = istart; i < length; i++) {
		result = factor * ((int) (*cursrc) - Cmin) + Nmin;
		if (result > 255)
			result = 255;
		*curdest = (unsigned char) result;
		/* Advance pointers */
		cursrc++;
		curdest++;
	}

	return (0);
}

/* ------------------------------------------------------------------------------------ */

/*!
\brief Filter using ConvolveKernel3x3Divide: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >2.
\param columns Number of columns in source/destination array. Must be >2.
\param Kernel The 2D convolution kernel of size 3x3.
\param Divisor The divisor of the convolution sum. Must be >0.

Note: Non-MMX implementation not available for this function.

\return Returns 1 if filter was applied, 0 otherwise.
*/
int SDL_imageFilterConvolveKernel3x3Divide(unsigned char *Src, unsigned char *Dest, int rows, int columns,
										   signed short *Kernel, unsigned char Divisor)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return(-1);

	if ((columns < 3) || (rows < 3) || (Divisor == 0))
		return (-1);

	if ((SDL_imageFilterMMXdetect())) {
//#ifdef USE_MMX
#if defined(USE_MMX) && defined(i386)
#if !defined(GCC__)
		__asm
		{
			pusha
				pxor mm0, mm0   	/* zero MM0 */
				xor ebx, ebx   	/* zero EBX */
				mov bl, Divisor   	/* load Divisor into BL */
				mov edx, Kernel   	/* load Kernel address into EDX */
				movq mm5, [edx]   	/* MM5 = {0,K2,K1,K0} */
			add edx, 8   	/* second row              |K0 K1 K2 0| */
				movq mm6, [edx]   	/* MM6 = {0,K5,K4,K3}  K = |K3 K4 K5 0| */
			add edx, 8   	/* third row               |K6 K7 K8 0| */
				movq mm7, [edx]   	/* MM7 = {0,K8,K7,K6} */
			/* ---, */
			mov eax, columns   	/* load columns into EAX */
				mov esi, Src   	/* ESI = Src row 0 address */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, eax   	/* EDI = EDI + columns */
				inc              edi    	/* 1 byte offset from the left edge */
				mov edx, rows   	/* initialize ROWS counter */
				sub edx, 2   	/* do not use first and last row */
				/* ---, */
L10320:
			mov ecx, eax   	/* initialize COLUMS counter */
				sub ecx, 2   	/* do not use first and last column */
				align 16                 	/* 16 byte alignment of the loop entry */
L10322:
			/* ---, */
			movq mm1, [esi]   	/* load 8 bytes of the image first row */
			add esi, eax   	/* move one row below */
				movq mm2, [esi]   	/* load 8 bytes of the image second row */
			add esi, eax   	/* move one row below */
				movq mm3, [esi]   	/* load 8 bytes of the image third row */
			punpcklbw mm1, mm0   	/* unpack first 4 bytes into words */
				punpcklbw mm2, mm0   	/* unpack first 4 bytes into words */
				punpcklbw mm3, mm0   	/* unpack first 4 bytes into words */
				pmullw mm1, mm5   	/* multiply words first row  image*Kernel */
				pmullw mm2, mm6   	/* multiply words second row image*Kernel */
				pmullw mm3, mm7   	/* multiply words third row  image*Kernel */
				paddsw mm1, mm2   	/* add 4 words of the first and second rows */
				paddsw mm1, mm3   	/* add 4 words of the third row and result */
				movq mm2, mm1   	/* copy MM1 into MM2 */
				psrlq mm1, 32   	/* shift 2 left words to the right */
				paddsw mm1, mm2   	/* add 2 left and 2 right result words */
				movq mm3, mm1   	/* copy MM1 into MM3 */
				psrlq mm1, 16   	/* shift 1 left word to the right */
				paddsw mm1, mm3   	/* add 1 left and 1 right result words */
				/* --, */
				movd mm2, eax   	/* save EAX in MM2 */
				movd mm3, edx   	/* save EDX in MM3 */
				movd eax, mm1   	/* copy MM1 into EAX */
				psraw mm1, 15   	/* spread sign bit of the result */
				movd edx, mm1   	/* fill EDX with a sign bit */
				idiv bx    	/* IDIV - VERY EXPENSIVE */
				movd mm1, eax   	/* move result of division into MM1 */
				packuswb mm1, mm0   	/* pack division result with saturation */
				movd eax, mm1   	/* copy saturated result into EAX */
				mov [edi], al   	/* copy a byte result into Dest */
				movd edx, mm3   	/* restore saved EDX */
				movd eax, mm2   	/* restore saved EAX */
				/* --, */
				sub esi, eax   	/* move two rows up */
				sub esi, eax   	/* */
				inc              esi    	/* move Src  pointer to the next pixel */
				inc              edi    	/* move Dest pointer to the next pixel */
				/* ---, */
				dec              ecx    	/* decrease loop counter COLUMNS */
				jnz            L10322    	/* check loop termination, proceed if required */
				add esi, 2   	/* move to the next row in Src */
				add edi, 2   	/* move to the next row in Dest */
				dec              edx    	/* decrease loop counter ROWS */
				jnz            L10320    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"xor       %%ebx, %%ebx \n\t"	/* zero EBX */
			"mov           %5, %%bl \n\t"	/* load Divisor into BL */
			"mov          %4, %%edx \n\t"	/* load Kernel address into EDX */
			"movq    (%%edx), %%mm5 \n\t"	/* MM5 = {0,K2,K1,K0} */
			"add          $8, %%edx \n\t"	/* second row              |K0 K1 K2 0| */
			"movq    (%%edx), %%mm6 \n\t"	/* MM6 = {0,K5,K4,K3}  K = |K3 K4 K5 0| */
			"add          $8, %%edx \n\t"	/* third row               |K6 K7 K8 0| */
			"movq    (%%edx), %%mm7 \n\t"	/* MM7 = {0,K8,K7,K6} */
			/* --- */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"mov          %1, %%esi \n\t"	/* ESI = Src row 0 address */
			"mov          %0, %%edi \n\t"	/* load Dest address to EDI */
			"add       %%eax, %%edi \n\t"	/* EDI = EDI + columns */
			"inc              %%edi \n\t"	/* 1 byte offset from the left edge */
			"mov          %2, %%edx \n\t"	/* initialize ROWS counter */
			"sub          $2, %%edx \n\t"	/* do not use first and last row */
			/* --- */
			".L10320:               \n\t" "mov       %%eax, %%ecx \n\t"	/* initialize COLUMS counter */
			"sub          $2, %%ecx \n\t"	/* do not use first and last column */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10322:               \n\t"
			/* --- */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the image first row */
			"add       %%eax, %%esi \n\t"	/* move one row below */
			"movq    (%%esi), %%mm2 \n\t"	/* load 8 bytes of the image second row */
			"add       %%eax, %%esi \n\t"	/* move one row below */
			"movq    (%%esi), %%mm3 \n\t"	/* load 8 bytes of the image third row */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first 4 bytes into words */
			"punpcklbw %%mm0, %%mm2 \n\t"	/* unpack first 4 bytes into words */
			"punpcklbw %%mm0, %%mm3 \n\t"	/* unpack first 4 bytes into words */
			"pmullw    %%mm5, %%mm1 \n\t"	/* multiply words first row  image*Kernel */
			"pmullw    %%mm6, %%mm2 \n\t"	/* multiply words second row image*Kernel */
			"pmullw    %%mm7, %%mm3 \n\t"	/* multiply words third row  image*Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the first and second rows */
			"paddsw    %%mm3, %%mm1 \n\t"	/* add 4 words of the third row and result */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"psrlq       $32, %%mm1 \n\t"	/* shift 2 left words to the right */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 2 left and 2 right result words */
			"movq      %%mm1, %%mm3 \n\t"	/* copy MM1 into MM3 */
			"psrlq       $16, %%mm1 \n\t"	/* shift 1 left word to the right */
			"paddsw    %%mm3, %%mm1 \n\t"	/* add 1 left and 1 right result words */
			/* -- */
			"movd      %%eax, %%mm2 \n\t"	/* save EAX in MM2 */
			"movd      %%edx, %%mm3 \n\t"	/* save EDX in MM3 */
			"movd      %%mm1, %%eax \n\t"	/* copy MM1 into EAX */
			"psraw       $15, %%mm1 \n\t"	/* spread sign bit of the result */
			"movd      %%mm1, %%edx \n\t"	/* fill EDX with a sign bit */
			"idivw             %%bx \n\t"	/* IDIV - VERY EXPENSIVE */
			"movd      %%eax, %%mm1 \n\t"	/* move result of division into MM1 */
			"packuswb  %%mm0, %%mm1 \n\t"	/* pack division result with saturation */
			"movd      %%mm1, %%eax \n\t"	/* copy saturated result into EAX */
			"mov      %%al, (%%edi) \n\t"	/* copy a byte result into Dest */
			"movd      %%mm3, %%edx \n\t"	/* restore saved EDX */
			"movd      %%mm2, %%eax \n\t"	/* restore saved EAX */
			/* -- */
			"sub       %%eax, %%esi \n\t"	/* move two rows up */
			"sub       %%eax, %%esi \n\t"	/* */
			"inc              %%esi \n\t"	/* move Src  pointer to the next pixel */
			"inc              %%edi \n\t"	/* move Dest pointer to the next pixel */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10322 \n\t"	/* check loop termination, proceed if required */
			"add          $2, %%esi \n\t"	/* move to the next row in Src */
			"add          $2, %%edi \n\t"	/* move to the next row in Dest */
			"dec              %%edx \n\t"	/* decrease loop counter ROWS */
			"jnz            .L10320 \n\t"	/* check loop termination, proceed if required */
			/* --- */
			"emms                   \n\t"	/* exit MMX state */
			"popa                   \n\t":"=m" (Dest)	/* %0 */
			:"m"(Src),		/* %1 */
			"m"(rows),		/* %2 */
			"m"(columns),		/* %3 */
			"m"(Kernel),		/* %4 */
			"m"(Divisor)		/* %5 */
			);
#endif
#endif
		return (0);
	} else {
		/* No non-MMX implementation yet */
		return (-1);
	}
}

/*!
\brief Filter using ConvolveKernel5x5Divide: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >4.
\param columns Number of columns in source/destination array. Must be >4.
\param Kernel The 2D convolution kernel of size 5x5.
\param Divisor The divisor of the convolution sum. Must be >0.

Note: Non-MMX implementation not available for this function.

\return Returns 1 if filter was applied, 0 otherwise.
*/
int SDL_imageFilterConvolveKernel5x5Divide(unsigned char *Src, unsigned char *Dest, int rows, int columns,
										   signed short *Kernel, unsigned char Divisor)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return(-1);

	if ((columns < 5) || (rows < 5) || (Divisor == 0))
		return (-1);

	if ((SDL_imageFilterMMXdetect())) {
//#ifdef USE_MMX
#if defined(USE_MMX) && defined(i386)
#if !defined(GCC__)
		__asm
		{
			pusha
				pxor mm0, mm0   	/* zero MM0 */
				xor ebx, ebx   	/* zero EBX */
				mov bl, Divisor   	/* load Divisor into BL */
				movd mm5, ebx   	/* copy Divisor into MM5 */
				mov edx, Kernel   	/* load Kernel address into EDX */
				mov esi, Src   	/* load Src  address to ESI */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, 2   	/* 2 column offset from the left edge */
				mov eax, columns   	/* load columns into EAX */
				shl eax, 1   	/* EAX = columns * 2 */
				add edi, eax   	/* 2 row offset from the top edge */
				shr eax, 1   	/* EAX = columns */
				mov ebx, rows   	/* initialize ROWS counter */
				sub ebx, 4   	/* do not use first 2 and last 2 rows */
				/* ---, */
L10330:
			mov ecx, eax   	/* initialize COLUMNS counter */
				sub ecx, 4   	/* do not use first 2 and last 2 columns */
				align 16                 	/* 16 byte alignment of the loop entry */
L10332:
			pxor mm7, mm7   	/* zero MM7 (accumulator) */
				movd mm6, esi   	/* save ESI in MM6 */
				/* --- 1 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 2 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 3 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 4 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 5 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* ---, */
				movq mm3, mm7   	/* copy MM7 into MM3 */
				psrlq mm7, 32   	/* shift 2 left words to the right */
				paddsw mm7, mm3   	/* add 2 left and 2 right result words */
				movq mm2, mm7   	/* copy MM7 into MM2 */
				psrlq mm7, 16   	/* shift 1 left word to the right */
				paddsw mm7, mm2   	/* add 1 left and 1 right result words */
				/* ---, */
				movd mm1, eax   	/* save EDX in MM1 */
				movd mm2, ebx   	/* save EDX in MM2 */
				movd mm3, edx   	/* save EDX in MM3 */
				movd eax, mm7   	/* load summation result into EAX */
				psraw mm7, 15   	/* spread sign bit of the result */
				movd ebx, mm5   	/* load Divisor into EBX */
				movd edx, mm7   	/* fill EDX with a sign bit */
				idiv bx    	/* IDIV - VERY EXPENSIVE */
				movd mm7, eax   	/* move result of division into MM7 */
				packuswb mm7, mm0   	/* pack division result with saturation */
				movd eax, mm7   	/* copy saturated result into EAX */
				mov [edi], al   	/* copy a byte result into Dest */
				movd edx, mm3   	/* restore saved EDX */
				movd ebx, mm2   	/* restore saved EBX */
				movd eax, mm1   	/* restore saved EAX */
				/* --, */
				movd esi, mm6   	/* move Src pointer to the top pixel */
				sub edx, 72   	/* EDX = Kernel address */
				inc              esi    	/* move Src  pointer to the next pixel */
				inc              edi    	/* move Dest pointer to the next pixel */
				/* ---, */
				dec              ecx    	/* decrease loop counter COLUMNS */
				jnz            L10332    	/* check loop termination, proceed if required */
				add esi, 4   	/* move to the next row in Src */
				add edi, 4   	/* move to the next row in Dest */
				dec              ebx    	/* decrease loop counter ROWS */
				jnz            L10330    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"xor       %%ebx, %%ebx \n\t"	/* zero EBX */
			"mov           %5, %%bl \n\t"	/* load Divisor into BL */
			"movd      %%ebx, %%mm5 \n\t"	/* copy Divisor into MM5 */
			"mov          %4, %%edx \n\t"	/* load Kernel address into EDX */
			"mov          %1, %%esi \n\t"	/* load Src  address to ESI */
			"mov          %0, %%edi \n\t"	/* load Dest address to EDI */
			"add          $2, %%edi \n\t"	/* 2 column offset from the left edge */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"shl          $1, %%eax \n\t"	/* EAX = columns * 2 */
			"add       %%eax, %%edi \n\t"	/* 2 row offset from the top edge */
			"shr          $1, %%eax \n\t"	/* EAX = columns */
			"mov          %2, %%ebx \n\t"	/* initialize ROWS counter */
			"sub          $4, %%ebx \n\t"	/* do not use first 2 and last 2 rows */
			/* --- */
			".L10330:               \n\t" "mov       %%eax, %%ecx \n\t"	/* initialize COLUMNS counter */
			"sub          $4, %%ecx \n\t"	/* do not use first 2 and last 2 columns */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10332:               \n\t" "pxor      %%mm7, %%mm7 \n\t"	/* zero MM7 (accumulator) */
			"movd      %%esi, %%mm6 \n\t"	/* save ESI in MM6 */
			/* --- 1 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 2 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 3 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 4 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 5 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- */
			"movq      %%mm7, %%mm3 \n\t"	/* copy MM7 into MM3 */
			"psrlq       $32, %%mm7 \n\t"	/* shift 2 left words to the right */
			"paddsw    %%mm3, %%mm7 \n\t"	/* add 2 left and 2 right result words */
			"movq      %%mm7, %%mm2 \n\t"	/* copy MM7 into MM2 */
			"psrlq       $16, %%mm7 \n\t"	/* shift 1 left word to the right */
			"paddsw    %%mm2, %%mm7 \n\t"	/* add 1 left and 1 right result words */
			/* --- */
			"movd      %%eax, %%mm1 \n\t"	/* save EDX in MM1 */
			"movd      %%ebx, %%mm2 \n\t"	/* save EDX in MM2 */
			"movd      %%edx, %%mm3 \n\t"	/* save EDX in MM3 */
			"movd      %%mm7, %%eax \n\t"	/* load summation result into EAX */
			"psraw       $15, %%mm7 \n\t"	/* spread sign bit of the result */
			"movd      %%mm5, %%ebx \n\t"	/* load Divisor into EBX */
			"movd      %%mm7, %%edx \n\t"	/* fill EDX with a sign bit */
			"idivw             %%bx \n\t"	/* IDIV - VERY EXPENSIVE */
			"movd      %%eax, %%mm7 \n\t"	/* move result of division into MM7 */
			"packuswb  %%mm0, %%mm7 \n\t"	/* pack division result with saturation */
			"movd      %%mm7, %%eax \n\t"	/* copy saturated result into EAX */
			"mov      %%al, (%%edi) \n\t"	/* copy a byte result into Dest */
			"movd      %%mm3, %%edx \n\t"	/* restore saved EDX */
			"movd      %%mm2, %%ebx \n\t"	/* restore saved EBX */
			"movd      %%mm1, %%eax \n\t"	/* restore saved EAX */
			/* -- */
			"movd      %%mm6, %%esi \n\t"	/* move Src pointer to the top pixel */
			"sub         $72, %%edx \n\t"	/* EDX = Kernel address */
			"inc              %%esi \n\t"	/* move Src  pointer to the next pixel */
			"inc              %%edi \n\t"	/* move Dest pointer to the next pixel */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10332 \n\t"	/* check loop termination, proceed if required */
			"add          $4, %%esi \n\t"	/* move to the next row in Src */
			"add          $4, %%edi \n\t"	/* move to the next row in Dest */
			"dec              %%ebx \n\t"	/* decrease loop counter ROWS */
			"jnz            .L10330 \n\t"	/* check loop termination, proceed if required */
			/* --- */
			"emms                   \n\t"	/* exit MMX state */
			"popa                   \n\t":"=m" (Dest)	/* %0 */
			:"m"(Src),		/* %1 */
			"m"(rows),		/* %2 */
			"m"(columns),		/* %3 */
			"m"(Kernel),		/* %4 */
			"m"(Divisor)		/* %5 */
			);
#endif
#endif
		return (0);
	} else {
		/* No non-MMX implementation yet */
		return (-1);
	}
}

/*!
\brief Filter using ConvolveKernel7x7Divide: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >6.
\param columns Number of columns in source/destination array. Must be >6.
\param Kernel The 2D convolution kernel of size 7x7.
\param Divisor The divisor of the convolution sum. Must be >0.

Note: Non-MMX implementation not available for this function.

\return Returns 1 if filter was applied, 0 otherwise.
*/
int SDL_imageFilterConvolveKernel7x7Divide(unsigned char *Src, unsigned char *Dest, int rows, int columns,
										   signed short *Kernel, unsigned char Divisor)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return(-1);

	if ((columns < 7) || (rows < 7) || (Divisor == 0))
		return (-1);

	if ((SDL_imageFilterMMXdetect())) {
//#ifdef USE_MMX
#if defined(USE_MMX) && defined(i386)
#if !defined(GCC__)
		__asm
		{
			pusha
				pxor mm0, mm0   	/* zero MM0 */
				xor ebx, ebx   	/* zero EBX */
				mov bl, Divisor   	/* load Divisor into BL */
				movd mm5, ebx   	/* copy Divisor into MM5 */
				mov edx, Kernel  	/* load Kernel address into EDX */
				mov esi, Src   	/* load Src  address to ESI */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, 3   	/* 3 column offset from the left edge */
				mov eax, columns   	/* load columns into EAX */
				add edi, eax   	/* 3 row offset from the top edge */
				add edi, eax
				add edi, eax
				mov ebx, rows   	/* initialize ROWS counter */
				sub ebx, 6   	/* do not use first 3 and last 3 rows */
				/* ---, */
L10340:
			mov ecx, eax   	/* initialize COLUMNS counter */
				sub ecx, 6   	/* do not use first 3 and last 3 columns */
				align 16                 	/* 16 byte alignment of the loop entry */
L10342:
			pxor mm7, mm7   	/* zero MM7 (accumulator) */
				movd mm6, esi   	/* save ESI in MM6 */
				/* --- 1 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 2 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 3 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 4 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 5 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 6 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* ---, */
				movq mm3, mm7   	/* copy MM7 into MM3 */
				psrlq mm7, 32   	/* shift 2 left words to the right */
				paddsw mm7, mm3   	/* add 2 left and 2 right result words */
				movq mm2, mm7   	/* copy MM7 into MM2 */
				psrlq mm7, 16   	/* shift 1 left word to the right */
				paddsw mm7, mm2   	/* add 1 left and 1 right result words */
				/* ---, */
				movd mm1, eax   	/* save EDX in MM1 */
				movd mm2, ebx   	/* save EDX in MM2 */
				movd mm3, edx   	/* save EDX in MM3 */
				movd eax, mm7   	/* load summation result into EAX */
				psraw mm7, 15   	/* spread sign bit of the result */
				movd ebx, mm5   	/* load Divisor into EBX */
				movd edx, mm7   	/* fill EDX with a sign bit */
				idiv bx    	/* IDIV - VERY EXPENSIVE */
				movd mm7, eax   	/* move result of division into MM7 */
				packuswb mm7, mm0   	/* pack division result with saturation */
				movd eax, mm7   	/* copy saturated result into EAX */
				mov [edi], al   	/* copy a byte result into Dest */
				movd edx, mm3   	/* restore saved EDX */
				movd ebx, mm2   	/* restore saved EBX */
				movd eax, mm1   	/* restore saved EAX */
				/* --, */
				movd esi, mm6   	/* move Src pointer to the top pixel */
				sub edx, 104   	/* EDX = Kernel address */
				inc              esi    	/* move Src  pointer to the next pixel */
				inc              edi    	/* move Dest pointer to the next pixel */
				/* ---, */
				dec              ecx    	/* decrease loop counter COLUMNS */
				jnz            L10342    	/* check loop termination, proceed if required */
				add esi, 6   	/* move to the next row in Src */
				add edi, 6   	/* move to the next row in Dest */
				dec              ebx    	/* decrease loop counter ROWS */
				jnz            L10340    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"xor       %%ebx, %%ebx \n\t"	/* zero EBX */
			"mov           %5, %%bl \n\t"	/* load Divisor into BL */
			"movd      %%ebx, %%mm5 \n\t"	/* copy Divisor into MM5 */
			"mov          %4, %%edx \n\t"	/* load Kernel address into EDX */
			"mov          %1, %%esi \n\t"	/* load Src  address to ESI */
			"mov          %0, %%edi \n\t"	/* load Dest address to EDI */
			"add          $3, %%edi \n\t"	/* 3 column offset from the left edge */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"add       %%eax, %%edi \n\t"	/* 3 row offset from the top edge */
			"add       %%eax, %%edi \n\t" "add       %%eax, %%edi \n\t" "mov          %2, %%ebx \n\t"	/* initialize ROWS counter */
			"sub          $6, %%ebx \n\t"	/* do not use first 3 and last 3 rows */
			/* --- */
			".L10340:               \n\t" "mov       %%eax, %%ecx \n\t"	/* initialize COLUMNS counter */
			"sub          $6, %%ecx \n\t"	/* do not use first 3 and last 3 columns */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10342:               \n\t" "pxor      %%mm7, %%mm7 \n\t"	/* zero MM7 (accumulator) */
			"movd      %%esi, %%mm6 \n\t"	/* save ESI in MM6 */
			/* --- 1 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 2 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 3 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 4 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 5 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 6 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- */
			"movq      %%mm7, %%mm3 \n\t"	/* copy MM7 into MM3 */
			"psrlq       $32, %%mm7 \n\t"	/* shift 2 left words to the right */
			"paddsw    %%mm3, %%mm7 \n\t"	/* add 2 left and 2 right result words */
			"movq      %%mm7, %%mm2 \n\t"	/* copy MM7 into MM2 */
			"psrlq       $16, %%mm7 \n\t"	/* shift 1 left word to the right */
			"paddsw    %%mm2, %%mm7 \n\t"	/* add 1 left and 1 right result words */
			/* --- */
			"movd      %%eax, %%mm1 \n\t"	/* save EDX in MM1 */
			"movd      %%ebx, %%mm2 \n\t"	/* save EDX in MM2 */
			"movd      %%edx, %%mm3 \n\t"	/* save EDX in MM3 */
			"movd      %%mm7, %%eax \n\t"	/* load summation result into EAX */
			"psraw       $15, %%mm7 \n\t"	/* spread sign bit of the result */
			"movd      %%mm5, %%ebx \n\t"	/* load Divisor into EBX */
			"movd      %%mm7, %%edx \n\t"	/* fill EDX with a sign bit */
			"idivw             %%bx \n\t"	/* IDIV - VERY EXPENSIVE */
			"movd      %%eax, %%mm7 \n\t"	/* move result of division into MM7 */
			"packuswb  %%mm0, %%mm7 \n\t"	/* pack division result with saturation */
			"movd      %%mm7, %%eax \n\t"	/* copy saturated result into EAX */
			"mov      %%al, (%%edi) \n\t"	/* copy a byte result into Dest */
			"movd      %%mm3, %%edx \n\t"	/* restore saved EDX */
			"movd      %%mm2, %%ebx \n\t"	/* restore saved EBX */
			"movd      %%mm1, %%eax \n\t"	/* restore saved EAX */
			/* -- */
			"movd      %%mm6, %%esi \n\t"	/* move Src pointer to the top pixel */
			"sub        $104, %%edx \n\t"	/* EDX = Kernel address */
			"inc              %%esi \n\t"	/* move Src  pointer to the next pixel */
			"inc              %%edi \n\t"	/* move Dest pointer to the next pixel */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10342 \n\t"	/* check loop termination, proceed if required */
			"add          $6, %%esi \n\t"	/* move to the next row in Src */
			"add          $6, %%edi \n\t"	/* move to the next row in Dest */
			"dec              %%ebx \n\t"	/* decrease loop counter ROWS */
			"jnz            .L10340 \n\t"	/* check loop termination, proceed if required */
			/* --- */
			"emms                   \n\t"	/* exit MMX state */
			"popa                   \n\t":"=m" (Dest)	/* %0 */
			:"m"(Src),		/* %1 */
			"m"(rows),		/* %2 */
			"m"(columns),		/* %3 */
			"m"(Kernel),		/* %4 */
			"m"(Divisor)		/* %5 */
			);
#endif
#endif
		return (0);
	} else {
		/* No non-MMX implementation yet */
		return (-1);
	}
}

/*!
\brief Filter using ConvolveKernel9x9Divide: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >8.
\param columns Number of columns in source/destination array. Must be >8.
\param Kernel The 2D convolution kernel of size 9x9.
\param Divisor The divisor of the convolution sum. Must be >0.

Note: Non-MMX implementation not available for this function.

\return Returns 1 if filter was applied, 0 otherwise.
*/
int SDL_imageFilterConvolveKernel9x9Divide(unsigned char *Src, unsigned char *Dest, int rows, int columns,
										   signed short *Kernel, unsigned char Divisor)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return(-1);

	if ((columns < 9) || (rows < 9) || (Divisor == 0))
		return (-1);

	if ((SDL_imageFilterMMXdetect())) {
//#ifdef USE_MMX
#if defined(USE_MMX) && defined(i386)
#if !defined(GCC__)
		__asm
		{
			pusha
				pxor mm0, mm0   	/* zero MM0 */
				xor ebx, ebx   	/* zero EBX */
				mov bl, Divisor   	/* load Divisor into BL */
				movd mm5, ebx   	/* copy Divisor into MM5 */
				mov edx, Kernel   	/* load Kernel address into EDY */
				mov esi< Src   	/* loaä Src  atdreSs tc ESI 
/			mov ådi, Dest   	o* loat DeS| a$drews to EDI!*/
			add edi, 4   	/* 4 co|umn$offset from the ìeft edge :/
				mov ea8, cOlumnó   	/* loa` colulns0inT/ AX *-
				ad` eDi, eax   	/* 4 row offset from thE top edçe */
				add edi, ea|
I			add eti, eax
				add"eti,`eax
				mnv ebx, ro÷s   	/($Initialaze RGWS coulter */
				sub ebx, 8   	/* do not use first 40afd lest 4 rows */
	/* ---, */
L10150:
		mov ecp eax   /* iîitialize COLUMNS counter */
				sub ecx, 8   	/* do not use first 4 and last 4 columns */
				align 16                 	/* 16 byte alignment of the loop entry */
L10352:
			pxor mm7, mm7   	/* zero MM7 (accumulator) */
				movd mm6, esi   	/* save ESI in MM6 */
				/* --- 1 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to othdR 4 wïrdw */
				movq mm4, [eD|]   	/
 load 6 worDs oæ Ker~el */
	I	add edx, 8   	o* move `gintes to$ophur 4 words */
				pu.qcklbw mí1, lm0   	/* unpack first  4 bytes into words */
				xunpckhbw mm2, m}0   	/* unpack second 4 bytes intm vords */
				pmullw mm1, mm3   	/*$mult. 4 lo÷  words of Srã and Kernel */
				pmullw mm2, mm<  $	/* mun4> p `igh wnrds of Src and Kmrnem`*/
				paddsw im1, mM2   Io* add 4 ords of the high and low"ryte{ */
			pad$sw m-7, mm1   	/* add"MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				pmullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 2 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	.* copy MM1 inpo MM2 */
			inc!             esi    	/* move poiîteò to the next 8 bytes0gf Src +-
				movq mm3. [edx]   	/* load 4 words of Kepnel *+
			adt edx, 8   	/*`oote poiktes to other 4 wor$s */
				movq mm4, [edx]   	/* lm!d 4 words ob0Kernel "/
			add ed8, 8   	/*$movepointer to mther 4 wOòds */
			punpCëlbw mm1,0mí0   	/* unpack first  4 bxtes into wo2ds */*				q}npckhbw mm2, mm1   	/* 5npack second 4 bytes into0words */
				pmwllw mm1, mm;   	/* mult. 40low  ÷ords of RRc and Kernel */
				pmullw mm2, mm4   	/* mult. 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				pmullw mm1, mm3   	/* mudt. 4 lnw  words of Src and Kmrnel :/
I		patdsw(mm7, ïm1  (	/* add MM1 to accumvlator MM7 */
				/* --- 3 :/
				movq mm1, [esi}   	/* moad 8 byves of tLe Src */
			mOvu mm2,"mM1   	/* cïpy!MM1 into MM2 */
				inc        ,     esi    ‰/* move poi.ter to the neyt 8 bytes of Src */
			movq me3, [edh]  0	/ª loAd 4 words on Kebnel ./
		Iaed edx, 8   	/* move pointer vo other 4 words :/
I			moöq mm4,`[edxÝ   	/* ¬oad 4 words of Kernem j/
		adD edx, 8   	/* aoVe`pointer0to other 4 ç/rds */
			pqNpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult. 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [gdx]   /* lOad 4 worDs of0Ëmrne| */
			add edx, 8   	/*0move poynter to other 4 words$*/				punpcklbw m-1 mm0   /* unpack¡first  4 bytes into worts */
				pmullw om1, Mo3!! 	/* mult. 4$l/w  wobds`of Src and Kernel!*.Š				Paddsw mm7, -m1 ( 	/* add MM1!to accumulator MM7 */
				/* --- 4 
/
				mïvq mm1, [esi]   	/. ìoqd 8 b}tes of the Srs */
	)	movq mm2, mm1   	/*$copy MM1$into MM2 ./
			inc    !         esi    	/* move poInter to the nexu 8 bytes of Src */
			movq mm;, [Edx]   	/* load 4 words Of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult. 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, Mm1 " 	/* aäd MM1`to accumulator MM7 */
			movq mm1, [esi] $ 	/+ load 8 bytes of Thg Src */
		lgc              esi
				qdd esi, eax ( ‰/* mOve Sc pointer 1 row below"*/
				moöp mm3, [mdx]   	/* load 4 words0of Kernel *+*)		afd edx, 8   	/* mo~e pointer0to otheb 4 wozds */
	‰	punpcklbw m}1 mm0 ` 	/. un`qck first  4 "y4eó into words */
				pmullw mm1, ml3   	/* mult. 4 ln7  wor$s of Sr# and Kurnel */
			Paddsw mm7, im1   	/* add MM1 eo accumudator MM7 */
				/* -­- 5 *?
				movq mm1, [esi]   	/* lgad 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult. 4 low  wnrds of Srs and8Kernel */*				pmullw mm2,!mm4$  	/. mult. 4 highbwords of Srb and Kernel */
			paddrw$mm1, mM2   	/* ade 4 words of t`å hig( ant low bytes */
				peddsw mm6, mm1   	/* add MM1!to accumulator MM7 */
			movq0mm1,"[esi]   	/* load : bytes of thd Spg */
			dec              esa
				add esi, eax   	/* }ove Src qointer 1 ro÷ beìow */
	‰	mo~p mm3, {efx]   	/* load 4 7ords Of Kernel +/
		add e$x, 8   /+ move pointgr to o|her 4 word{ */
				`unpcklbw m-1¬ mm0   	¯* unpaCk first` 4 by4es into words */
				pmullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 6 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer tg otheò 4 wobdû */
				punpcklbw me1& mm0   	/* wnpaak férst  4 bytes intn words */
			punpckhbw im2, mm0   	/* unpack$seco.$ 4 bytes intn words$*/
				pmullw mm1, mm3   	/* mult. 4 low  words of Srs and Kernel */J			pmullw`mm2,"ím00 	.* mult. 4 (igh wordc of Src anD Curnel */
				pcddsw mm1, ií2   	/* add 4 words of vhe High gnd low byôes */			paddsw mm7,"mm1   	/* ad$ MM1 t/ accumula|or MM7 *'*			movq mm1, [esi](  I/* load 8 bytes of ôhe0Src */
		©dec        (     åsy
			add esi¬ eax   	/* mnöe Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				pmullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq }m3¬ [Edx]   	/* load 4 words of K%rnel */
			add edx, 8 0 	/* move 0ointer tO!other 4 words *g
				movq }m4, [edx]   	/* loid  worts of ernel */
			add edxl 8   	/* movm pointer to othm0 4 wordS *.				pqnpc{lbw m-1, mm  ` 	o* unðack$fisst  4 rytes0into wovds */
				punpcjhbw im2- mm0   	/" unpack segond 4 bytes ahto words */
				`mulLs mm1$ mM3   	* mult. 4 low "words of Cr# afd Kernel ª/
				píullw mm2, Mm4 " 	/*`mult. 4 high wrdc of Src and Kernel */
				padfsw m}1, mm2   	/* edd 4 wïrds of t`e high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				pmullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 8 */
				movq mmq, [eci]   	¯* load 8 byteS of the Src ª/
			movq mm, m}1   	/* copy MM0!into MM2 */
				inc   !         esi    	/* mmve pointer tk thE next !bytes on Src */
				mowq mm3, [edx]   	/* load 4 vords of Kernel */
			atd0edx, 8   	/*$move pointms to otjep 4"wrds */
				movq mm4,`[ådx]   	/* loa$ 4 words of Kernel */
			add edx, 8   	/* movE pminper to`ktler 4 words */
			penpcklbw ím1 }m0   	/* ulpácj first  40bytes"into wordw */
				punpckhbw mm2, mm0   I/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult. 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw Ím1, mm0 !0	/*0unpack fiòs4  4 b}tes in|o words */
		Épmullw mm1, im3   	/* mqìt. 6 low  woòds of Src and Kernål *o	‰		p`tdsw"mm7, mm±   	/* add MM1 to`accumulator MM7 ./
				o* ---09 *.
		movq }m1,"[esi]   	/* load : bxtms of |he S2c$ª/
			íovq mm2, Mm1   	/* copy MÍ1 into MM2 */
				ifc              esi    	/
 move0qointer to the next 8 bytes f Src */
				movq íi3l [eex]   	/* load 4 wozds of Kerned */
			add 'dX, 8   	/* move peinuej |o other 4 wordq */
			movq mm4, [edx]  0	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				pmullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult. 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm3, [edx]   	- load 4 wOrds of Kernel */
			punpcklBw mM1, mm0   	/* unpack firs4  4 b9tes i~to Words */
				0mullw mm1, mm3   	/* mult. 4 low  words of Src and Kernel */
				paedsw -m7, mm1   	/* add"ÍM1 to akãu-ulator MM5(:/
				/* ---$ */
				movq m}3, mm7   	/* copy MM· into MM3 */
				psrlu mm7, 32   	/* shift 2 left0words to the right */
			paddsw ml7, mm3   	/* aed 2 left anD 2 bigèt result words h/
			movq mm2((mh3   	/* copy MM7 into MM2 */
				psr|q mm7, 16   	/* shift$1 l%ft word to the right */
				paddsw mm7, mm2   	/* add 1 left and 1 right result words */
				/* ---, */
				movd mm1, eax   	/* save EDX in MM1 */
				movd mm2, ebx   	/* save EDX in MM2 */
				movd mm3, edx   	/* save EDX in MM3 */
				movd eax, mm7   	/* load summation result into EAX */
				psraw mm7, 15   	/* spread sign bit of the result */
				movd ebx, mm5   	/* load Divisor into EBX */
				movd edx, mm7   	/* fill EDX with a sign bit */
				idiv bx    	/* IDIV - VERY EXPENSIVE */
				movd mm7, eax   	/* move result of division into M]5!*/
				packu3wb lm7, mm0   	/* pack division rerult with raturatmon */
)			movd eax, mm7   	/*"copy saturqtåd r%sult intn EAX */
				mov eei], al   	/* copy"a bYte resu|t into Dest */
				movd edx, mm3   	?ª restore saved EDX */
			iovd ebx, mm2   	'*$restore saved EBX *
			m/vd eax, mm1"  	/* restoòe s`ved0eQX */
				/* --,`*/				movd eci, me6 $ /j mova Src tointer to the top pixel */			sub e$ø, r08   	/* EDX = Kernel áddress n¯
				inc            `¢eci`   	/* move Src 0pointer to the$next pixel */
				inc              edi    	/* move Dest pointer to the next pixel */
				/* ---, */
				dec              ecx    	/* decrease loop counter COLUMNS */
				jnz            L10352    	/* check loop termination, proceed if required */
				add esi, 8   	/* move to the next row in Src */
				add edi, 8   	/* move to the next row in Dest */
				dec              ebx    	/* decrease loop counter ROWS */
				jnz            L10350    	/* check loop termination, proceed if required */
				/* ---, */
				emms             0        	** exit MMX state ª/
I			popa
		}
#else
		awm volatile
			("ðusha		     XnTt" "pxor    $ %%mo0, %%lm0 \n\t"	/* zezo MM0 */
I	‰"xor 0     %%ebx, %%ebx$\n\t"	+* ~ero EBX */
	)"Mov     "   $ %5, %%bl \n\t"	/* lo!d Divysor0into BL */*			"movd      %%ezx, %$im5"n\t"	/* aopy Difisor inôo MM5 */
		"mov   (      %4, %%edx \n\t"	/*0loa$ Kernel address intk EEx "/
		"íov  ""      %1$ %%esi \n\t"+* loaä`Src  address to ESI */
			"mOv          %0, %%eäi \n\t"	/* doad Dest addreqs to(ELI(*/
			"add          $4, %%edi \n\t"	/* 4 column offset from the left edge */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"add       %%eax, %%edi \n\t"	/* 4 row offset from the top edge */
			"add       %%eax, %%edi \n\t" "add       %%eax, %%edi \n\t" "add       %%eax, %%edi \n\t" "mov          %2, %%ebx \n\t"	/* initialize ROWS counter */
			"sub          $8, %%ebx \n\t"	/* do not use first 4 and last 4 rows */
			/* --- */
			".L10350:               \n\t" "mov       %%eax, %%ecx \n\t"	/* initialize COLDMÎS coun|er */
			"sub          $8, %%ecx \nt )/*(do not use girst 4 and last 40co|tmns */
			"®align 56        #    "\ntt"	/* 16 byte alifnment of tie loop enury */
			".L10352:               \n\t" "pxïr      %%mm7, %%mm7 \n\t2	/* zero MM7 (accumulator) */
		"movd      %%esi, %%mm6 \n\t"	/( óa6e EI in MM6 */
			/* --- 1 */
			"lov1    (%%eci), %%mm1 \n\t"	/* load 8 bytes of the0Srk */
‰	"movq     "%%mm1,`%%mm2 \l\d 	/* copy MM1 indo MM20*/
			"inc      p       %%esi \j\t"	/*(move!poknter to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
		¢rmulhw    -%em4, %%mm2 \n\t"	/j mõlv. 4 higl wozds of Src and Kernel */
			*0addsw  0 %%lm2, %%mm1 \n\tb	/* adl 4 wordq of the high anl low bytes ('
			"paddsw `  %%mm1, %¥mm7 \nÜì"	/* add MM1 to acc5Mulator mM7(*/			movq    (%%esi), %%mm1 \n\t"/* lad 8 `yter of$he Wrc */
	‰	"dec              %%ewa \n\t" "cdd  ( 0" %%eax, %%esi \n\t"	/* m{ve Src tinter 1 row!below */
		2movq    *%¥e`x), %%mm3 \n\t"	/* load 4 words of Kerïel */
			"add      °   $8, %%mdx \n\t"/ª move pointer to o4`e2 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 2 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %5edx \n\t"	/* move pointer uo o4her 4 words */
		"morq    (%%edx),(%%mm4 \n\t"/* load 4 words mf Kernel0*/
			"add     0    $x, %%edx \n\t"	/* move pointer do other 4 words *.
			"xunpcklcw %$oM0, %%me1 \n\t"/* unpack first  4 bùtes into words$*/
			"punpckhbw e%im0, %%mm2 \n\t"‰/* unpack seãond 4 bytes i~to wores */			"pmullw    %%mm3, %%mm1 \n\t	/* mult. 4 lkw  words of Src And KÅrnel */			"pmullw  ` 5%mm4, %$im2 \nLtb	/* mult. 4 Hich words of SsC and [ernel!*/
			"pá`dsw    %mm2, -%mm1 \n\u"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec              %%esi \n\t" "add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 lkw  wnòds kf Src and Kernel */
		"paddrw    %%mm5, %%m}7 \n\t"	/: ae` MM1 to accumulaor`MM7 */
	)	/* --- 3 */
			"movq(   ¨%%usi), %%mm1 \n\t"	/* liad 8 bytes0od uhå S2c */
	"movq `    %%mm0, %%mm2 \n\t"/* copx MM1 into MM2 */
		"inc !            %%esi \n\t"	/: move pointer to the ngxt < bytes of src */
			"movq0   ,%%edx),0%%mm3 \n\|"	/* load(4 wmrls of Kernel */
			"add      !"  $(, %%edx Ün\t"	/ª mote"pointer to other 4 ords */
		"eovq    (%%edx), %%mm4`\n\t"	/* load 4 wkp$s of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* loid 8 bxtus of the Src j/
	I"de#           (  -%esi \n\v" "add       %%eax. 5%esI \n\t"	/* move Src pointer 1 row below */
			"movq    ¨%%edx), %%mm3 Tn\t"	/* load 4!words of Kernel */
			"add  0       $8, %%edø \n\t"	/* movå"pointer to othdr 4 vords "/Š			"punpcklbw %%mm0, %%lm1 \n\t"/* unpack fiòst  4 bytes inpo words */
I	"pmullw    %%mm3,0%5mm1 \n\t"	/* Muht. 4 low  worew og Src a~` Jernel */
			paddsw    %%mm1, %%mm7 \f\t"	/* add MM1 do accwmulatg2 MM7 */
			/*0-- 4 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes mnto wsds */
			"punp!khbw %-mm0$ %%mm2 \n\t"	/* unPack second 4`fytes in~ words */
			"pmullw$   %¥mm3, %!m-1 ^n\t"	/* mult. 4 low  7mrds of Src and KernEl :/
			"pmullw$   %%em, %%mm2 \n\t"	/. mult.  hioh ords of Src and ernel *¯
			"padäsw    %'mm2, %%mm1 \n\t"	/* add 4 obds of t(e lmgh and low bypes */
		"paddsg    %uIm1,"%%mm7 \n\t"	/* add LM1 to ac#umulator MI7 */*		"eova    (%%esi), %%mm1 \n\t"	/* load 8 byteó of the Src */
	)	dec    "         %%esi \n\t  "ad`      %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 5 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc    !         %%åsi \n\v"	/* move pointer to The fåxt 8 bytes of Szc$*/			"movq d  (¥%edx), !%mm3 \nLt"	/* loid"6 words of Kernel :/
			"add          e8, %%edx xnLt"	/* íove pointer to othmr < words */
			"movq    (%%gdx!, %%mí4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/*"move pomnte2 to$other 4 worär */	I	"punpcklbw %%mm0, %%mm1"\n]t"	/* u~pack firSt  4$bytes ijdo wrds */
			"punpckhbw %-im0< '%mí2 \jXt"	/* unpack secoNd 4 bytes ilto words */
	I	"pmull÷    %%mm#, $%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec              %%esi \n\t" "add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* }ove poifter to!ouher 40words *?
		I"punpck|"w $%mm1, %%m}5 \n\t"	/* unpack first  4 bytes0into word3h*/
		"pm}llw    %%mm3,%%mo1 \n]t"	/* m5ld. 4 lOw  words ov$Src and Kernel */
			"pads    %%mm1, %%mm7(\n\t"+/* aDd$MM1 tk accumulapor MM7 */*			/* --- 6"*/
			"movp    (%%esi),`%%}m1 \n\t"	/* lgad 8 bytes of the Src *
		‰"mkvq      %%mm1, %%mm2 \n\t"	/" copy MM10into MM2 */
			#i~c              %%esi \n\t"	/* mofe poiîter to the next 8 cyte3 f Rpã */
			"mOvq    (%¥edx), %%im3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
		"paddsw    %%mM2, %%mm10\nLt"	/* add 4 words of thE high and lOs byte2 */
		"paedsw    %%mm1, %%mm7 \n\p"	*$atd EM1 To accueulator MM7 */		"-va(   (¥%esi(, 5%m-1(\.\t"	/* loat 8 byvEs of the Src */
			"dec    `        !%%qsi`\n^t" 2aDd    (  %%eax, %%esi Tn\t"	/*0move Src pointer 1 sow below */J		"movq  (  %%edp), %%mi3 \n\t"	¯* locd 4 words of Kernel */			 add          $x, %%edx \n\t"	/* move poiougr to other 4 wores */
			 punpcklbw %%mm0, %%mm1 \nÜt"	/: tnpack birst  4 bxtes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx),0¥%mm4 Tl^t"	,ª loed 4 words of Kernel *+
			"add     !    $8, %%edx \n\t"	/* move poinver$to other 4 words :/
			"punpcklbw %%ím0, %%mm \n\t"	/* unpack first( 4(bytes into woräs */
			"punpckhbw %%mm0, %%mm2 \nt"	/* unpack second04 bytes into words */
			"`m}dlw"   %%mm³, %%mm1 \n\t"	/( mult. 4 low  wordw ov Src and Kernel */
		Icpmellw   (%%mm4, %5mm2 \o\t"	/* mult. 4(high wOrds of Srã and Kernel */
			"paddsw    %%mo2, %%mm1 \nÜt"	/* add 4 words f th%!(igh a.d low bytes ª/*I	‰"paddsw   (%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec              %%esi \n\t" "add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add(MM1 to accu}ulatoò MM7 */
			/* --- 8 */			bïovq$   (%%esi), %'mm1 \n\t"	/* load 8 bytes oæ(the Szc */
			"mnvq   "  %%im1, %%mm2 \n\t"	/* copY MM1 into`M2 */
			"inc    0         %esi \n\t"	/* -ove pointer To the nex4"¸ bytes of Srã */
I		"movq!   (%%%dx), '%mm3 \n\t"	/* load 4 words of Kernel */
‰		"add   $      $8,!%%edx \n\t"	/* move pointer tO mthev  words */
			"mOvq  a (%%edx), %%ml´ \nt"	/* load`4 words f Kårndl */
		‰"add          $8 %5ddx \n\t"	?* move po)nter to oth%r`< words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec    $  `      %%msi \n\t" "add 0    (%%eax, %!esi \n\t"‰/* oove`Src pointer 1 row below */
			"movq    (%%edx), -mm3 \n\t"	/* load 4 words of KerLel */
	"add          $8¬ %%edx \n\t"	/: move pïknteR to kther 40words */Š			"punpkidbw %%mM0, %$mi1 ^n^t"	/* unback fipst  4 bytes int/ words$*/
	I"pmullw   "%%mm3, %%ol1 \nÜt"	/* lumt. 4 lkw  words of Src and kernel */
		"paddsw $  %%mm1,d%%mm7 \n\T"	/* add MM1 to accumulator MM7 */
			/* --- 9 *
	I	"Movq`   (%%Esi), %%mmq \n\t"	/* load 8 bytes of the!Src */			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytms into words */
			*pmullw    %%oms, %%ml1 \n\|"	/* mult. 4 low  wopds of Src and Kgrnel */			&pmqllw    %%mm4, %%mm0"\nLt	/* mult. 4 high word1 of Src0and Kernel */
			"patdsw $  %%mm2, %%mm1 \j\t"	/* add 4 wopds oæ the high and ,ow bytec */
	)	"paädsw $  %%-m9, %%mm7 |n\t")/* add MM1 t/ aãcumulatOr MMw */
			"Movp    (%Esi+, %%mm1 \n\T"	/ª loaä 80fytes of the Src */
			"movq    8%%edx). %!mm3 ^nÜt"	/* load 4 words of Kernml */
			"punpcknbw %%m-0,(%1im1 \n\t"	/* unpack first  4 bytes ento words */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- */
			"movq      %%mm7, %%mm3 \n\t"	/* copy MM7 into MM3 */
			"psrlq       $32, %%mm7 \n\t"	/* shift 2 left words to the right */
			"paddsw    %%mm3, %%mm7 \n\t"	/* add 2 left and 2 right result words */
			"movq      %%mm7, %%mm2 \n\t"	/* copy MM7 into MM2 */
			"psrlq       $16, %%mm7 \n\t"	/* shift 1 left word to the right */
			"paddsw    %%mm2, %%mm7 \n\t"	/*(add 1$deft and 1 rkght r}sult wgrdS (/
			/* --- */
			"movd      %%eax, %%lm1 \n\t"	/* s!ve EDX in MM1 ".
			"moöd   0 "%%ejx, !%mm2`\n\t"	/* sevå EDX in MM2 */
	ˆ	"movd      %%eex, %%mm3 \n\t"	/* sav% EDX in MM3 */
			"movd `    %%mm7, %¥eaX \n]u"	/* load su-e¡tion0resuLt inôo EAX */
			"psraw   !   $15, %%mm7 \n\t"	/* spread sign bit of thá result!*/
		"m/vf      $5mm5, %%gbx \n\t"	/* load Divisor inôo EBX */
			"movd      %%mm7, %%edx \n\t"	/* fill EDX with a sigf bit */
			"ilivw             %%bx \n\t"	/* IDIV - VERY0EXPÅNSIVE */
			"movd    0 %-eax, %%mm7 \ê\t"	* move result of division into MM7 */
			"xackuswb  %%mm0, %%mm7 \n\t"	/* pack division result with saturation */
			"movd      %%mm7, %%eax \n\t"	'* copy saturated result into EAX */
			"movh     %%al (%%edi) \n\ô"	/* copy a byte resu,t int Dest */
			"mgvd    $ %%m}3. %%edx \n\t"	/* restore caved EDX */
			"movd      %%mm2, %%ebx \n\u"	/* restore saved EBX */
			"movd      %%mm1, %%eax \n\t"	.* resuore saved EAX */
		/* ­m"*/
			motd     $%%mm6, %%esi \n\t"	/* move Spc poin4er to the top pixel */
)		"sub        $208, e%edx \n\t"	o* EDX - Ker~el Addvess */
			"inc(        $    %%esi \m\t"	/* move Src $poinôer to pje next pixel */
			"inc  `           %%edi \n\t&	/* mïve Dest pnintar uo*tje nixt pixel ./
			/* ---0*/
			"lec       )     (%%%ch \fÜt"	/*$decrease ìoop counter AOLUMNS */
		‰"jn: `  $    !  .L10353 \n\t"	/* ãheck loop tarm!nation, 0rocemd if required j/*		"atd(         $8, $%esi"\n\t"	/
 move do the nex4 row in Src *+
		"add          $8, %%edi \n\t"	/* mofe to the next row in Dest */			"dec           (  %%ebx \n\t"	/* decreare loop cnunter ROWS */
			"jnz            .L10350 \n\t"	/* chmck loop termination, proceed if required */
			/* --- */
			 emms0              "   \n\t"	/* exit MMX state */
			"popa                   \n\t":"=m" ¨Dest)	/* %0 */
			:"m"(Src),		/# $1 */
			"m"(rows),		/* %2 */
			"m"(columns),		/* %3 */
			"m"(Kernel),		/* %40*/
			"m¢(Divisor)		/* %5 */
			);
#endif
#endif
		return (0);
	} else {
	/
 No non-MMX iMpleme.t!tIon yet :/
	return (-1)9
	}}

/*!
Tbréaf Filter using CïNvolveKernel3x3Shigtigh|: Dij = saturatyon0aod255( ... )`

\param Ssc Thu source 2D byte array to convolve® Should be differmnt bòom destinaôion.
Ü`aram Deqt The destination 2D fyte array to {tore ôhe result in. Should be di¦ferent from source.
\param r/ws Numbdr of row3 i~ source/`estination array. Must je >2.
\param columns Number of(coluMns én source/destination array. Must be >2.
\páram Kernel The 2D convolution kernel of size 3x3.
\param NRightShift The number of right bit shifts to apply to the convolution sum. Must be <7.

Note: Non-MMX implementation not available for this function.

\return Returns 1 if filter was applied, 0 otherwise.
*/
int SDL_imageFilterConvolveKernel3x3ShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
											   signed short *Kernel, unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return(-1);

	if ((column3 < 7) |ü (òows(<"3) || )NZightShift > 7))
	‰return (-1);

	if ¨(QEL_imageFil|lrIMXdetect())) {
/'#ifdef!USE_MMX
#ig defined(USE_MMX) && defined(i382)
#if !defhned(GCC__)
	_^así
		{
			pusha
		pxor mm0, mm0   	/* zero MM0"*/
				xor ebx, ebx   	/* zero EBX */
			I}ov bl, NRéghthift   	/* noad NRyghtShift into BL */
				movd(mm4, ebx   	/* copy NRigh|Shaft into Mm4 */
			)mov uDx,`Kernål   	/: loae(Oernel address into EDX"*/
			Movq!mm5, [elx]   	/* MM5(½ {0,K2,K1,K0}`*/
		add edx,$8   	/* second row              |K0 K1 K2 0| */
				movq mm6, [edx]   	/* MM6 = {0,K5,K4,K3}  K = |K3 K4 K5 0| */
			add edx, 8   	/* third row               |K6 K7 K8 0| */
				movq mm7, [edx]   	/* MM7 = {0,K8,K7,K6} */
			/* ---, */
			mov eax, columns   	/* load columns into EAX */
				mov esi, Src   	/* ESI = Src row 0 address */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, eax   	/* EDI = EDI + columns */
				inc              edi    	/* 1 byte offset from the left edge */
				mov edx, rows"0"	/* initializm ROWS sounter!*/
				seb %dx, 2   I/* do not use first and lást vog */
				/: ---- */
L10³61:
		mov ec<, max   	/* initialixe KOLULS cnunter *+Š			s5b0ecx, 2   	/* do not uóe`first an` last column */
			Ialign 16             "   	/* 16 byte alignmeot of the loop en|ry */
L10362:
			/* --%, */
			eovq mm1, [esi]   	/* load 8 b}tes of the imagå firsô rov$*/
			aDd esi, Eax   	/*0move mne row belov */
				movq mm2, [esi]   	/* loqd 8 bytes od t`å kmage second rou */
			adt esi, eax   	/* move one row below */
				movq mm3, [esi]   	/* load 8 bytes of the image third row */
			punpcklbw mm1, mm0   	/* unpack first 4 bytes into words */
				punpcklbw mm2, mm0   	/* unpack first 4 bytes into words */
				punpcklbw mm3, mm0   	/* unpack first 4 bytes into words */
				psrlw mm1, mm4   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm4   	/* shift right each pixel NshiftRight times */
				psrlw mm3, mm4   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm5   	/* multiply words first row  image*Kernel */
				pmullw mm2, mm6   	/* multiply words second row image*Kernel */
				pmullw mm3, mm7   	/* multiply words third row  image*Kernel */
				paddsw mm1, mm2   	/* add 4 words of the first and second rows */
				paddsw mm1, mm3   	/* add 4 words of the third row and result */
				movq mm2, mm1   	/* copy MM1 into MM2 */
				psrlq mm1, 32   	/* shift 2 left words to the right */
				paddsw mm1, mm2   	/* add 2 left and 2 right result words */
				movq mm3, mm1   	/* copy MM1 into MM3 */
				psrlq mm1, 16   	/* shift 1 left word to the right */
				paddsw mm1, mm3   	/* add 1 left and 1 right result words */
				packuswb mm1, mm0   	/* pack shift result with saturation */
				movd ebx, mm1   	/* copy saturated result into EBX */
				mov [edi], bl   	/* copy a byte result into Dest */
				/* --, */
				sub esi, eax   	/* move two rows up */
				sub esi, eax
				inc              esi    	/* move Src  pointer to the next pixel */
				inc              edi    	/* move Dest pointer to the next pixel */
				/* ---, */
				dec              ecx    	/* decrease loop counter COLUMNS */
				jnz            L10362    	/* check loop termination, proceed if required */
				add esi, 2   	/* move to the next row in Src */
				add edi, 2   	/* move to the next row in Dest */
				dec              edx    	/* decrease loop counter ROWS */
				jnz            L10360    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"xor       %%ebx, %%ebx \n\t"	/* zero EBX */
			"mov           %5, %%bl \n\t"	/* load NRightShift into BL */
			"movd      %%ebx, %%mm4 \n\t"	/* copy NRightShift into MM4 */
			"mov          %4, %%edx \n\t"	/* load Kernel address into EDX */
			"movq    (%%edx), %%mm5 \n\t"	/* MM5 = {0,K2,K1,K0} */
			"add          $8, %%edx \n\t"	/* second row              |K0 K1 K2 0| */
			"movq    (%%edx), %%mm6 \n\t"	/* MM6 = {0,K5,K4,K3}  K = |K3 K4 K5 0| */
			"add          $8, %%edx \n\t"	/* third row               |K6 K7 K8 0| */
			"movq    (%%edx), %%mm7 \n\t"	/* MM7 = {0,K8,K7,K6} */
			/* --- */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"mov          %1, %%esi \n\t"	/* ESI = Src row 0 address */
			"mov          %0, %%edi \n\t"	/* load Dest address to EDI */
			"add       %%eax, %%edi \n\t"	/* EDI = EDI + columns */
			"inc              %%edi \n\t"	/* 1 byte offset from the left edge */
			"mov          %2, %%edx \n\t"	/* initialize ROWS counter */
			"sub          $2, %%edx \n\t"	/* do not use first and last row */
			/* --- */
			".L10360:               \n\t" "mov       %%eax, %%ecx \n\t"	/* initialize COLUMS counter */
			"sub          $2, %%ecx \n\t"	/* do not use first and last column */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10362:               \n\t"
			/* --- */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the image first row */
			"add       %%eax, %%esi \n\t"	/* move one row below */
			"movq    (%%esi), %%mm2 \n\t"	/* load 8 bytes of the image second row */
			"add       %%eax, %%esi \n\t"	/* move one row below */
			"movq    (%%esi), %%mm3 \n\t"	/* load 8 bytes of the image third row */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first 4 bytes into words */
			"punpcklbw %%mm0, %%mm2 \n\t"	/* unpack first 4 bytes into words */
			"punpcklbw %%mm0, %%mm3 \n\t"	/* unpack first 4 bytes into words */
			"psrlw     %%mm4, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm4, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm4, %%mm3 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm5, %%mm1 \n\t"	/* multiply words first row  image*Kernel */
			"pmullw    %%mm6, %%mm2 \n\t"	/* multiply words second row image*Kernel */
			"pmullw    %%mm7, %%mm3 \n\t"	/* multiply words third row  image*Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the first and second rows */
			"paddsw    %%mm3, %%mm1 \n\t"	/* add 4 words of the third row and result */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"psrlq       $32, %%mm1 \n\t"	/* shift 2 left words to the right */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 2 left and 2 right result words */
			"movq      %%mm1, %%mm3 \n\t"	/* copy MM1 into MM3 */
			"psrlq       $16, %%mm1 \n\t"	/* shift 1 left word to the right */
			"paddsw    %%mm3, %%mm1 \n\t"	/* add 1 left and 1 right result words */
			"packuswb  %%mm0, %%mm1 \n\t"	/* pack shift result with saturation */
			"movd      %%mm1, %%ebx \n\t"	/* copy saturated result into EBX */
			"mov      %%bl, (%%edi) \n\t"	/* copy a byte result into Dest */
			/* -- */
			"sub       %%eax, %%esi \n\t"	/* move two rows up */
			"sub       %%eax, %%esi \n\t" "inc              %%esi \n\t"	/* move Src  pointer to the next pixel */
			"inc              %%edi \n\t"	/* move Dest pointer to the next pixel */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10362 \n\t"	/* check loop termination, proceed if required */
			"add          $2, %%esi \n\t"	/* move to the next row in Src */
			"add          $2, %%edi \n\t"	/* move to the next row in Dest */
			"dec              %%edx \n\t"	/* decrease loop counter ROWS */
			"jnz            .L10360 \n\t"	/* check loop termination, proceed if required */
			/* --- */
			"emms                   \n\t"	/* exit MMX state */
			"popa                   \n\t":"=m" (Dest)	/* %0 */
			:"m"(Src),		/* %1 */
			"m"(rows),		/* %2 */
			"m"(columns),		/* %3 */
			"m"(Kernel),		/* %4 */
			"m"(NRightShift)	/* %5 */
			);
#endif
#endif
		return (0);
	} else {
		/* No non-MMX implementation yet */
		return (-1);
	}
}

/*!
\brief Filter using ConvolveKernel5x5ShiftRight: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >4.
\param columns Number of columns in source/destination array. Must be >4.
\param Kernel The 2D convolution kernel of size 5x5.
\param NRightShift The number of right bit shifts to apply to the convolution sum. Must be <7.

Note: Non-MMX implementation not available for this function.

\return Returns 1 if filter was applied, 0 otherwise.
*/
int SDL_imageFilterConvolveKernel5x5ShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
											   signed short *Kernel, unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return(-1);

	if ((columns < 5) || (rows < 5) || (NRightShift > 7))
		return (-1);

	if ((SDL_imageFilterMMXdetect())) {
//#ifdef USE_MMX
#if defined(USE_MMX) && defined(i386)
#if !defined(GCC__)
		__asm
		{
			pusha
				pxor mm0, mm0   	/* zero MM0 */
				xor ebx, ebx   	/* zero EBX */
				mov bl, NRightShift   	/* load NRightShift into BL */
				movd mm5, ebx   	/* copy NRightShift into MM5 */
				mov edx, Kernel   	/* load Kernel address into EDX */
				mov esi, Src   	/* load Src  address to ESI */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, 2   	/* 2 column offset from the left edge */
				mov eax, columns   	/* load columns into EAX */
				shl eax, 1   	/* EAX = columns * 2 */
				add edi, eax   	/* 2 row offset from the top edge */
				shr eax, 1   	/* EAX = columns */
				mov ebx, rows   	/* initialize ROWS counter */
				sub ebx, 4   	/* do not use first 2 and last 2 rows */
				/* ---, */
L10370:
			mov ecx, eax   	/* initialize COLUMNS counter */
				sub ecx, 4   	/* do not use first 2 and last 2 columns */
				align 16                 	/* 16 byte alignment of the loop entry */
L10372:
			pxor mm7, mm7   	/* zero MM7 (accumulator) */
				movd mm6, esi   	/* save ESI in MM6 */
				/* --- 1 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 2 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 3 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 4 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 5 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* ---, */
				movq mm3, mm7   	/* copy MM7 into MM3 */
				psrlq mm7, 32   	/* shift 2 left words to the right */
				paddsw mm7, mm3   	/* add 2 left and 2 right result words */
				movq mm2, mm7   	/* copy MM7 into MM2 */
				psrlq mm7, 16   	/* shift 1 left word to the right */
				paddsw mm7, mm2   	/* add 1 left and 1 right result words */
				movd mm1, eax   	/* save EAX in MM1 */
				packuswb mm7, mm0   	/* pack division result with saturation */
				movd eax, mm7   	/* copy saturated result into EAX */
				mov [edi], al   	/* copy a byte result into Dest */
				movd eax, mm1   	/* restore saved EAX */
				/* --, */
				movd esi, mm6   	/* move Src pointer to the top pixel */
				sub edx, 72   	/* EDX = Kernel address */
				inc              esi    	/* move Src  pointer to the next pixel */
				inc              edi    	/* move Dest pointer to the next pixel */
				/* ---, */
				dec              ecx    	/* decrease loop counter COLUMNS */
				jnz            L10372    	/* check loop termination, proceed if required */
				add esi, 4   	/* move to the next row in Src */
				add edi, 4   	/* move to the next row in Dest */
				dec              ebx    	/* decrease loop counter ROWS */
				jnz            L10370    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"xor       %%ebx, %%ebx \n\t"	/* zero EBX */
			"mov           %5, %%bl \n\t"	/* load NRightShift into BL */
			"movd      %%ebx, %%mm5 \n\t"	/* copy NRightShift into MM5 */
			"mov          %4, %%edx \n\t"	/* load Kernel address into EDX */
			"mov          %1, %%esi \n\t"	/* load Src  address to ESI */
			"mov          %0, %%edi \n\t"	/* load Dest address to EDI */
			"add          $2, %%edi \n\t"	/* 2 column offset from the left edge */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"shl          $1, %%eax \n\t"	/* EAX = columns * 2 */
			"add       %%eax, %%edi \n\t"	/* 2 row offset from the top edge */
			"shr          $1, %%eax \n\t"	/* EAX = columns */
			"mov          %2, %%ebx \n\t"	/* initialize ROWS counter */
			"sub          $4, %%ebx \n\t"	/* do not use first 2 and last 2 rows */
			/* --- */
			".L10370:               \n\t" "mov       %%eax, %%ecx \n\t"	/* initialize COLUMNS counter */
			"sub          $4, %%ecx \n\t"	/* do not use first 2 and last 2 columns */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10372:               \n\t" "pxor      %%mm7, %%mm7 \n\t"	/* zero MM7 (accumulator) */
			"movd      %%esi, %%mm6 \n\t"	/* save ESI in MM6 */
			/* --- 1 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 2 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 3 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 4 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 5 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- */
			"movq      %%mm7, %%mm3 \n\t"	/* copy MM7 into MM3 */
			"psrlq       $32, %%mm7 \n\t"	/* shift 2 left words to the right */
			"paddsw    %%mm3, %%mm7 \n\t"	/* add 2 left and 2 right result words */
			"movq      %%mm7, %%mm2 \n\t"	/* copy MM7 into MM2 */
			"psrlq       $16, %%mm7 \n\t"	/* shift 1 left word to the right */
			"paddsw    %%mm2, %%mm7 \n\t"	/* add 1 left and 1 right result words */
			"movd      %%eax, %%mm1 \n\t"	/* save EAX in MM1 */
			"packuswb  %%mm0, %%mm7 \n\t"	/* pack division result with saturation */
			"movd      %%mm7, %%eax \n\t"	/* copy saturated result into EAX */
			"mov      %%al, (%%edi) \n\t"	/* copy a byte result into Dest */
			"movd      %%mm1, %%eax \n\t"	/* restore saved EAX */
			/* -- */
			"movd      %%mm6, %%esi \n\t"	/* move Src pointer to the top pixel */
			"sub         $72, %%edx \n\t"	/* EDX = Kernel address */
			"inc              %%esi \n\t"	/* move Src  pointer to the next pixel */
			"inc              %%edi \n\t"	/* move Dest pointer to the next pixel */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10372 \n\t"	/* check loop termination, proceed if required */
			"add          $4, %%esi \n\t"	/* move to the next row in Src */
			"add          $4, %%edi \n\t"	/* move to the next row in Dest */
			"dec              %%ebx \n\t"	/* decrease loop counter ROWS */
			"jnz            .L10370 \n\t"	/* check loop termination, proceed if required */
			/* --- */
			"emms                   \n\t"	/* exit MMX state */
			"popa                   \n\t":"=m" (Dest)	/* %0 */
			:"m"(Src),		/* %1 */
			"m"(rows),		/* %2 */
			"m"(columns),		/* %3 */
			"m"(Kernel),		/* %4 */
			"m"(NRightShift)	/* %5 */
			);
#endif
#endif
		return (0);
	} else {
		/* No non-MMX implementation yet */
		return (-1);
	}
}

/*!
\brief Filter using ConvolveKernel7x7ShiftRight: Dij = saturation0and255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >6.
\param columns Number of columns in source/destination array. Must be >6.
\param Kernel The 2D convolution kernel of size 7x7.
\param NRightShift The number of right bit shifts to apply to the convolution sum. Must be <7.

Note: Non-MMX implementation not available for this function.

\return Returns 1 if filter was applied, 0 otherwise.
*/
int SDL_imageFilterConvolveKernel7x7ShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
											   signed short *Kernel, unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return(-1);

	if ((columns < 7) || (rows < 7) || (NRightShift > 7))
		return (-1);

	if ((SDL_imageFilterMMXdetect())) {
//#ifdef USE_MMX
#if defined(USE_MMX) && defined(i386)
#if !defined(GCC__)
		__asm
		{
			pusha
				pxor mm0, mm0   	/* zero MM0 */
				xor ebx, ebx   	/* zero EBX */
				mov bl, NRightShift   	/* load NRightShift into BL */
				movd mm5, ebx   	/* copy NRightShift into MM5 */
				mov edx, Kernel   	/* load Kernel address into EDX */
				mov esi, Src   	/* load Src  address to ESI */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, 3   	/* 3 column offset from the left edge */
				mov eax, columns   	/* load columns into EAX */
				add edi, eax   	/* 3 row offset from the top edge */
				add edi, eax
				add edi, eax
				mov ebx, rows   	/* initialize ROWS counter */
				sub ebx, 6   	/* do not use first 3 and last 3 rows */
				/* ---, */
L10380:
			mov ecx, eax   	/* initialize COLUMNS counter */
				sub ecx, 6   	/* do not use first 3 and last 3 columns */
				align 16                 	/* 16 byte alignment of the loop entry */
L10382:
			pxor mm7, mm7   	/* zero MM7 (accumulator) */
				movd mm6, esi   	/* save ESI in MM6 */
				/* --- 1 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 2 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 3 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 4 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 5 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 6 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* ---, */
				movq mm3, mm7   	/* copy MM7 into MM3 */
				psrlq mm7, 32   	/* shift 2 left words to the right */
				paddsw mm7, mm3   	/* add 2 left and 2 right result words */
				movq mm2, mm7   	/* copy MM7 into MM2 */
				psrlq mm7, 16   	/* shift 1 left word to the right */
				paddsw mm7, mm2   	/* add 1 left and 1 right result words */
				movd mm1, eax   	/* save EAX in MM1 */
				packuswb mm7, mm0   	/* pack division result with saturation */
				movd eax, mm7   	/* copy saturated result into EAX */
				mov [edi], al   	/* copy a byte result into Dest */
				movd eax, mm1   	/* restore saved EAX */
				/* --, */
				movd esi, mm6   	/* move Src pointer to the top pixel */
				sub edx, 104   	/* EDX = Kernel address */
				inc              esi    	/* move Src  pointer to the next pixel */
				inc              edi    	/* move Dest pointer to the next pixel */
				/* ---, */
				dec              ecx    	/* decrease loop counter COLUMNS */
				jnz            L10382    	/* check loop termination, proceed if required */
				add esi, 6   	/* move to the next row in Src */
				add edi, 6   	/* move to the next row in Dest */
				dec              ebx    	/* decrease loop counter ROWS */
				jnz            L10380    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"xor       %%ebx, %%ebx \n\t"	/* zero EBX */
			"mov           %5, %%bl \n\t"	/* load NRightShift into BL */
			"movd      %%ebx, %%mm5 \n\t"	/* copy NRightShift into MM5 */
			"mov          %4, %%edx \n\t"	/* load Kernel address into EDX */
			"mov          %1, %%esi \n\t"	/* load Src  address to ESI */
			"mov          %0, %%edi \n\t"	/* load Dest address to EDI */
			"add          $3, %%edi \n\t"	/* 3 column offset from the left edge */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"add       %%eax, %%edi \n\t"	/* 3 row offset from the top edge */
			"add       %%eax, %%edi \n\t" "add       %%eax, %%edi \n\t" "mov          %2, %%ebx \n\t"	/* initialize ROWS counter */
			"sub          $6, %%ebx \n\t"	/* do not use first 3 and last 3 rows */
			/* --- */
			".L10380:               \n\t" "mov       %%eax, %%ecx \n\t"	/* initialize COLUMNS counter */
			"sub          $6, %%ecx \n\t"	/* do not use first 3 and last 3 columns */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10382:               \n\t" "pxor      %%mm7, %%mm7 \n\t"	/* zero MM7 (accumulator) */
			"movd      %%esi, %%mm6 \n\t"	/* save ESI in MM6 */
			/* --- 1 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 2 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 3 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 4 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 5 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 6 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- */
			"movq      %%mm7, %%mm3 \n\t"	/* copy MM7 into MM3 */
			"psrlq       $32, %%mm7 \n\t"	/* shift 2 left words to the right */
			"paddsw    %%mm3, %%mm7 \n\t"	/* add 2 left and 2 right result words */
			"movq      %%mm7, %%mm2 \n\t"	/* copy MM7 into MM2 */
			"psrlq       $16, %%mm7 \n\t"	/* shift 1 left word to the right */
			"paddsw    %%mm2, %%mm7 \n\t"	/* add 1 left and 1 right result words */
			"movd      %%eax, %%mm1 \n\t"	/* save EAX in MM1 */
			"packuswb  %%mm0, %%mm7 \n\t"	/* pack division result with saturation */
			"movd      %%mm7, %%eax \n\t"	/* copy saturated result into EAX */
			"mov      %%al, (%%edi) \n\t"	/* copy a byte result into Dest */
			"movd      %%mm1, %%eax \n\t"	/* restore saved EAX */
			/* -- */
			"movd      %%mm6, %%esi \n\t"	/* move Src pointer to the top pixel */
			"sub        $104, %%edx \n\t"	/* EDX = Kernel address */
			"inc              %%esi \n\t"	/* move Src  pointer to the next pixel */
			"inc              %%edi \n\t"	/* move Dest pointer to the next pixel */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10382 \n\t"	/* check loop termination, proceed if required */
			"add          $6, %%esi \n\t"	/* move to the next row in Src */
			"add          $6, %%edi \n\t"	/* move to the next row in Dest */
			"dec              %%ebx \n\t"	/* decrease loop counter ROWS */
			"jnz            .L10380 \n\t"	/* check loop termination, proceed if required */
			/* --- */
			"emms                   \n\t"	/* exit MMX state */
			"popa                   \n\t":"=m" (Dest)	/* %0 */
			:"m"(Src),		/* %1 */
			"m"(rows),		/* %2 */
			"m"(columns),		/* %3 */
			"m"(Kernel),		/* %4 */
			"m"(NRightShift)	/* %5 */
			);
#endif
#endif
		return (0);
	} else {
		/* No non-MMX implementation yet */
		return (-1);
	}
}

/*!
\brief Filter using ConvolveKernel9x9ShiftRight: Dij = saturation255( ... ) 

\param Src The source 2D byte array to convolve. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >8.
\param columns Number of columns in source/destination array. Must be >8.
\param Kernel The 2D convolution kernel of size 9x9.
\param NRightShift The number of right bit shifts to apply to the convolution sum. Must be <7.

Note: Non-MMX implementation not available for this function.

\return Returns 1 if filter was applied, 0 otherwise.
*/
int SDL_imageFilterConvolveKernel9x9ShiftRight(unsigned char *Src, unsigned char *Dest, int rows, int columns,
											   signed short *Kernel, unsigned char NRightShift)
{
	/* Validate input parameters */
	if ((Src == NULL) || (Dest == NULL) || (Kernel == NULL))
		return(-1);

	if ((columns < 9) || (rows < 9) || (NRightShift > 7))
		return (-1);

	if ((SDL_imageFilterMMXdetect())) {
//#ifdef USE_MMX
#if defined(USE_MMX) && defined(i386)
#if !defined(GCC__)
		__asm
		{
			pusha
				pxor mm0, mm0   	/* zero MM0 */
				xor ebx, ebx   	/* zero EBX */
				mov bl, NRightShift   	/* load NRightShift into BL */
				movd mm5, ebx   	/* copy NRightShift into MM5 */
				mov edx, Kernel   	/* load Kernel address into EDX */
				mov esi, Src   	/* load Src  address to ESI */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, 4   	/* 4 column offset from the left edge */
				mov eax, columns   	/* load columns into EAX */
				add edi, eax   	/* 4 row offset from the top edge */
				add edi, eax
				add edi, eax
				add edi, eax
				mov ebx, rows   	/* initialize ROWS counter */
				sub ebx, 8   	/* do not use first 4 and last 4 rows */
				/* ---, */
L10390:
			mov ecx, eax   	/* initialize COLUMNS counter */
				sub ecx, 8   	/* do not use first 4 and last 4 columns */
				align 16                 	/* 16 byte alignment of the loop entry */
L10392:
			pxor mm7, mm7   	/* zero MM7 (accumulator) */
				movd mm6, esi   	/* save ESI in MM6 */
				/* --- 1 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 2 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 3 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 4 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 5 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 6 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 8 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			dec              esi
				add esi, eax   	/* move Src pointer 1 row below */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* --- 9 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm2, mm1   	/* copy MM1 into MM2 */
				inc              esi    	/* move pointer to the next 8 bytes of Src */
				movq mm3, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				movq mm4, [edx]   	/* load 4 words of Kernel */
			add edx, 8   	/* move pointer to other 4 words */
				punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				punpckhbw mm2, mm0   	/* unpack second 4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				psrlw mm2, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				pmullw mm2, mm4   	/* mult 4 high words of Src and Kernel */
				paddsw mm1, mm2   	/* add 4 words of the high and low bytes */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				movq mm1, [esi]   	/* load 8 bytes of the Src */
			movq mm3, [edx]   	/* load 4 words of Kernel */
			punpcklbw mm1, mm0   	/* unpack first  4 bytes into words */
				psrlw mm1, mm5   	/* shift right each pixel NshiftRight times */
				pmullw mm1, mm3   	/* mult 4 low  words of Src and Kernel */
				paddsw mm7, mm1   	/* add MM1 to accumulator MM7 */
				/* ---, */
				movq mm3, mm7   	/* copy MM7 into MM3 */
				psrlq mm7, 32   	/* shift 2 left words to the right */
				paddsw mm7, mm3   	/* add 2 left and 2 right result words */
				movq mm2, mm7   	/* copy MM7 into MM2 */
				psrlq mm7, 16   	/* shift 1 left word to the right */
				paddsw mm7, mm2   	/* add 1 left and 1 right result words */
				movd mm1, eax   	/* save EAX in MM1 */
				packuswb mm7, mm0   	/* pack division result with saturation */
				movd eax, mm7   	/* copy saturated result into EAX */
				mov [edi], al   	/* copy a byte result into Dest */
				movd eax, mm1   	/* restore saved EAX */
				/* --, */
				movd esi, mm6   	/* move Src pointer to the top pixel */
				sub edx, 208   	/* EDX = Kernel address */
				inc              esi    	/* move Src  pointer to the next pixel */
				inc              edi    	/* move Dest pointer to the next pixel */
				/* ---, */
				dec              ecx    	/* decrease loop counter COLUMNS */
				jnz            L10392    	/* check loop termination, proceed if required */
				add esi, 8   	/* move to the next row in Src */
				add edi, 8   	/* move to the next row in Dest */
				dec              ebx    	/* decrease loop counter ROWS */
				jnz            L10390    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"xor       %%ebx, %%ebx \n\t"	/* zero EBX */
			"mov           %5, %%bl \n\t"	/* load NRightShift into BL */
			"movd      %%ebx, %%mm5 \n\t"	/* copy NRightShift into MM5 */
			"mov          %4, %%edx \n\t"	/* load Kernel address into EDX */
			"mov          %1, %%esi \n\t"	/* load Src  address to ESI */
			"mov          %0, %%edi \n\t"	/* load Dest address to EDI */
			"add          $4, %%edi \n\t"	/* 4 column offset from the left edge */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"add       %%eax, %%edi \n\t"	/* 4 row offset from the top edge */
			"add       %%eax, %%edi \n\t" "add       %%eax, %%edi \n\t" "add       %%eax, %%edi \n\t" "mov          %2, %%ebx \n\t"	/* initialize ROWS counter */
			"sub          $8, %%ebx \n\t"	/* do not use first 4 and last 4 rows */
			/* --- */
			".L10390:               \n\t" "mov       %%eax, %%ecx \n\t"	/* initialize COLUMNS counter */
			"sub          $8, %%ecx \n\t"	/* do not use first 4 and last 4 columns */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10392:               \n\t" "pxor      %%mm7, %%mm7 \n\t"	/* zero MM7 (accumulator) */
			"movd      %%esi, %%mm6 \n\t"	/* save ESI in MM6 */
			/* --- 1 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec              %%esi \n\t" "add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 2 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec              %%esi \n\t" "add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 3 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec              %%esi \n\t" "add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 4 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
)		"Paddsw    %%im2, %%Mm1 \n\t"	?* aed 4 wksds of!txe high qnd low âytes */
	‰	"paddsw    %%mm1,(%%mí7 |n\t"	/* adl MM1 to accumUlat_r MM7 */
			"movq    (%%esi9,`%'mm1 |n\t"I?
 load 8(byt%s of the src */
			*dac "  (         %%esi \n\t" "add       %%eax, %%Esi \n\t"	/* move(Src pointer 1 row below */
		"moöq    (%%edxi, e5mm3 \n\t¢	/* load 4 words of Kernel */
			"qdd      !   $8, %%efx \n\t"	/* move pointer to other 4 words */
			&punrcklbw ¥%mm0, %%mm1 \n\ô"	/"$unp`ck(firsô  4(bùte3 into wordc`*'
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 5 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %'edx`\n|t"	/(!move$poinper to other 4`words */
		"movq    (%%edx)- %%mm4 ^j\t"	/: loed 4 words od Kerned *?			"ald          $8, %%edx \n\t"/*$move pointer to other 4 gords */
			"punpcklbw %'mm0,(%%mm1 \n\t"	/* unpaco first! 4 bytes into words$*¯
		"punpcëhbw 5%mm0, %%mm2 ^~\t"/* un`ack second 4 cytes!into words */Š		"tsrl     %%mm5, ¥%mí1 \n\t"	/* shift right each pixel NshiftRight times */		"psr.w 0   %%}mµ, %%mm2 \n\t"	/* shivu righT åach pixgm"NshiftVmght th}es *.
		"pmullw ` 0%%ím3,0%%mm5 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec              %%esi \n\t" "add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %'edx \n\tb	/* move pointer to other 4 vmrdq */*			¢penpcklbw %%m}0, %-mm1 \f\t"	/* unpack firs4  4 bytes into word3 */
		*psrlw     %%me5, !%mm3 \n\t"	/* shift right eacj pihel NsiiftRkght tiles */
		"pmuldw  ( %¥-m3,`%%mm1(\n\t"	/* mult. 4 low( words`of!Ssc and Kernel */		"paddsw   °%'me1, $%mí7 \n\t 	?* add0ME1 to accsmulátor MM7 */
			/* --- 6 */
			"movq    (¥%eci!, %%mm1 \j\t"	/* load 0 bytes of$the Src */
	)	&movq      %%mm1,`%%m-2 \n\t"	/* copy MM1 into MM2 */
		*inc           `` %%esi \n\t"	* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshifeRight times */
			"psòlw     %!mm5, %%-m \n\t"	/* shitt rigèd åach pixel NshiftRight ti}es */			"pmullw   0%%mm3,0%%mm1 \nLt	/*¤mult. 4 low "words /f Src and Kernel */
		*pmunlw    %%mm4 %--m2$\n\t"	/* muld.24 high words of Src `nd Kdrnel */
		"paddsw    %%m}2¬$%'mm1 \n\t"	/* add 4 ords of the0high and lou `ytes */
		"pcddsw`  "%¥mm1, %%m}7 \n\t"	/* add MM t/ acc5mUlator MM7 */
			"movq    (%%esi), %%mm1 \n\t"‰/* loa` 8 bytes$of tie Src */
			"dec              %%esi \N\t"`"afl$    0 e%eax %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes"of the Src j/
		"movq      %%}m1, %5mm2 \n\t"	¯* copy!MM1 into MM2 */			"inc              %%eói \n\t"	/. mm6e poiîter`to the next 8 bytes of Src */
			"motq    (%%ed9),%%%mm3 \n\t2	/* load 4 words of K`rnel */
			"add $        %8, %%edx \î\t.*(love Pninter t owher 4(worä{ */
			"oovq    (%%edp), %%mm4 Ln\t"	/* load 4 wordc of Ëernel */
			"ade        ` $8, %%edx"Tn\p"	/* move`pïinter to`other 40words */
			"punpcklfw %e}m0, %%mm10Lî\t"	/* =npacë firwt  4 bytes ínto ÷ords"*/
		"xunpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"pmullw    %%mm4, %%mm2 \n\t"	/* mult. 4 high words of Src and Kernel */
			"paddsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MO7 */
			"morq    (%%esi),"%%mm1 ]n\t"/* lnad 8 bytes of the"Rrc°*/
			"dec    "`        5%dsi |n\t" "add       %-eax, %%dsi \n\t"	/* move Qzc pointer01arow below */
‰		"-ovq    (%%edx), %%mm3 \nÜt"	/* hoad 4 woòds of Ker.dl */
		I"aäd          $8(e%edx \n\u"	/* move(pointer!|m other 4 words */
			"tuNpcklw %%mm0, %%ím1 \n\d"	/* unpaak first  4 bùtes into words */
			"psslw  ! !%%lm5,"'%mm1 \n\t	/* shift right eAch0xixel NsHiftRiçht times j/
			"pmullw    ¥!mm3¬ %%mm1 \n\dc/j }uLt. 40low( words mf Srg and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- 8 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"movq      %%mm1, %%mm2 \n\t"	/* copy MM1 into MM2 */
			"inc              %%esi \n\t"	/* move pointer to the next 8 bytes of Src */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move poilter T/ other 5 sorfs (/
	‰	"pulpcklbw %%mm0, %%mm1(\n\t*	/+ wnpack fIòst  4 bytes into wordq */
			"puntskhbg %%mm0, %%mm2 \n\t*	/* unpack seco~d"4 bytes intn words */
			"p#rlw     %%mm5, %%mM1 \j\t"	-*!shift!right mach pixel shiftRight times */
			"psr,w     %emm5, %%mm2 \n\t"	/* shift(righv each pixel NshiftRighT times */
			"pmemlw "  %%mm3, %…mm5 |~\t"	/* mult. 4 low `worôs of Srã and Kernel *o
			*pm}llw  ` %'-m4, %%mm2 ]n\t"/* m5lt. 4 high words of0[rc an$ Kerngl!*/J			&paädsw    %%mm2, %%mm1 \n\t"	/* add 4 words of the high and low bytes */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			"movq    (%%esi), %%mm1 \n\t"	/* load 8 bytes of the Src */
			"dec              %%esi \n\t" "add       %%eax, %%esi \n\t"	/* move Src pointer 1 row below */
			"movq    (%%edx), %%mm3 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"psrlw     %%mí7, %%mí1 \n\t"	/* shifT vighp eagh¤pixel NshiftRig`T time÷ */			"pmullw!   %%mm3,(%%mm10\n\t 	/. mult. 4 l/w  goräs of rc!ind Kerje| */
‰		"padds7    %%mm1, %%mm7 \n\t"	/* add MM1 to iccuM5ì!uor MM7"*/
			/* --- ¹ */
			rmovy   `(%5åsi) %mm1 Pn\t"	/* load 8 bytes of the Sðc */
			"movq      %mm1,$%%mm2 \n\t"	/* copy MM1 ifto MM2 */
			"ioc     0   `    5%esi \n\p"	/* mgöe(pointer 4o thå next 8 bqtes of órc */
			"movs    (%%edx©, %%ím3 \n\t2™-* lmid 4 words of Kerne|`*-
		"add !  !   , $8, '%eex |n\t"	/* move pointer to other 4 words */
			"movq    (%%edx), %%mm4 \n\t"	/* load 4 words of Kernel */
			"add          $8, %%edx \n\t"	/* move pointer to other 4 words */
			"punpcklbw %%mm0, %%mm1 \n\t"	/* unpack first  4 bytes into words */
			"punpckhbw %%mm0, %%mm2 \n\t"	/* unpack second 4 bytes into words */
			"psrlw     %%mm5, %%mm1 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm5, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mul4. 5 low  wosds`ob Spc0and Kernel */
			"xíullw0   %%mm4, %%mm2`\n^t"	/* oult. 4 higi words of Sra anl Oernel0*/
		"paddsw (0 %%mm2, %%mm10\n\t"	/* adl 4 words of the high ald low B{ves */
			"qadäsw    %emm1, %%mm7 \n\t"	/" add MM1 t"accumõlator MM7 */
			"movq    (%%esé), %%ml1 \n\t"	/* nod 8 bytes o6 the Src"*/
			"mowq    (5%eex), '%mm3 \n\t"	/*"load04 wor`s of KuRnel *'			"punpcclbw %%ým°, %¥ím9 ^n\t"	/* unpack!first  4"bytes into words *?
‰	"psrlw     %%mm5, %%gm1 \n\t"	/* shift right`eqch pihel NshiftRight times */
			"pmullw    %%mm3, %%mm1 \n\t"	/* mult. 4 low  words of Src and Kernel */
			"paddsw    %%mm1, %%mm7 \n\t"	/* add MM1 to accumulator MM7 */
			/* --- */
			"movq      %%mm7, %%mm3 \n\t"	/* copy MM7 into MM3 */
			"psrlq       $32, %%mm7 \n\t"	/* shift 2 left words to the right */
			"paddsw    %%mm3, %%mm7 \n\t"	/* add 2 left and 2 right result words */
			"movq      %%mm7, %%mm2 \n\t"	/* copy MM7 into MM2 */
			"psrlq       $16, %%mm7 \n\t"	/* shift 1 left word to the right */
			"padds    %%mm2¬ %%mm7 \j\t"	o* add 1 Left and 1 right resu|u words */
			 movd  "   5%eax, %%mm1 \l\t"	o* save EAX in MM1 */
			"packuswb  -¥mm0, %%mm? \N\t"	/* pack divisinn`pesult wit` saturatiwn */
			"movd   (  %%mm7, %%eax \nTt"	/* coty saturated result hnto UAX *+J			"mov  `  %%al, (%%edi)d\n\t"	/* co`y a bxtm rMcõlt into Dest */
			"Ooöd      %%mm3, %%eax \n\t"	/* rewtore s`ved EAX */
			/* -- */
			"mord  (   %%mm¶( !%esi \n\t"	/*"move SrC pninter to the top pixel */
		‰"qub        $208, %'Adx \n\u¢	/* EDX = Kernel address */
			"inc              %%esi \n\t"	/* move Src  pointer to the next pixel */
			"inc              %%edi \n\t"	/* move Dest pointer to the next pixel */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10392 \n\t"	/* check loop termination, proceed if required */
			"add          $8, %%esi \n\t"	/* move to the next row in Src */
			"add          $8, %%edi \n\t"	/* move to the next row in Dest */
			"dec              %%ebx \n\t"	/* decrease loop cotnôer ROUS */
			"nnz       (    /L10390 \n\t"I/
 check lomp tmrmknation, prceed if required */
			* -=­ */
			"emms$      0 0         \n\|"	/* exit0MMX state */
		"popa              a   (\J\t":"=m" (Deót)‰/*$%0 »/
		:"m"(Srk),		/* %1 */
			"m"(rows),		/* %2 */
		)"m"8columos),		/* %s j¯
	I	"m"(Kernel),		/ -4 */
			"m (NRigiôShifô)	/* %5 */
	);
#Eîdif
#endif
iAretUrn (0);
	} mlse {
	‰/* No ngn-EMX impl-men4ation yeô */
		return`-1);
	}‚}

/* ----------------m-----=-­----%-,--==%----------------------------------------------- */

/*!
\brief Filter using SobelX: Dij = saturation255( ... ) 

\param Src The source 2D byte array to sobel-filter. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >2.
\param columns Number of columns in source/destination array. Must be >7.

Note: Non-MMX implementation not available for this function.

\return Retwros 1 iæ fil|er wAs applied,`0 otherwise.
*/
int SDL_ioageFilterSïbelX¨unsigned!chap *Src¬ unSigfed char *Fest, int rovs, int columns9
k
	/+ Validatedinput`parameters */
if ((Src == NUÌL) t|0(Dest!== NULL))
		retwrn()5);

	kf ©(comõínr(< 8) |~ (rows <03))
		return *-1);
	if0((SDL_imageDiltgr]MXdetect())- {
//#ifddf uSE_MMX
#if defined8USE_mMY) &. defined(i386)#hf !dmfined(GGCW_)	__asm
		{
			pusha
				pxor mep, ímp   	/* zero MM0 :/
				mov eax, c/l}mns   	/* loat conumnS into EQX */
	‰	/* ---, */
				mov esi, Src   	/* ESI = Src row 0 address */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, eax   	/* EDI = EDI + columns */
				inc              edi    	/* 1 byte offset from the left edge */
				mov edx, rows   	/* initialize ROWS counter */
				sub edx, 2   	/* do not use first and last rows */
				/* ---, */
L10400:
			mov ecx, eax   	/* initialize COLUMS counter */
				shr ecx, 3   	/* EBX/8 (MMX loads 8 bytes at a time) */
				mov ebx, esi   	/* save ESI in EBX */
				movd mm1, e$k0  	/* save EDI in MMq *§
			aligf 16    ` 0        ! 	o* 16 `yt% alignm%nt of the"looR entry */
\10402:
		!/* ---< */
			movs mm4, [esa]  (	/* load 8 bytms from Src */			mova mm5, mm4   	/( save MM4 in MM5 */
				atd åsi¬ 2   	'* Move ESI po)nter 2 bytes right (/
	)		punpcëlbw mm4, mm0   	/* tnpack 4 low  bytes`into words */
			punpckh"w mm5, mm0!  	/* unpack 4 *igh bytes mnto woPds 
/
			mïvq mm6, [esi]   	/* load 8 bytes from Src *?			mmvq mm7. mm>   	/* rate MM6 in MM7 */
				sub esi, 2   	/* move ESI pointer back 2 bytes left */
				punpcklbw mm6, mm0   	/* unpack 4 low  bytes into words */
				punpckhbw mm7, mm0   	/* unpack 4 high bytes into words */
				add esi, eax   	/* move to the next row of Src */
				movq mm2, [esi]   	/* load 8 bytes from Src */
			movq mm3, mm2   	/* save MM2 in MM3 */
				add esi, 2   	/* move ESI pointer 2 bytes right */
				punpcklbw mm2, mm0   	/* unpack 4 low  bytes into words */
				punpckhbw mm3, mm0   	/* unpack 4 high bytes into words */
				paddw mm4, mm2 2 	/""add 4 lmw  b}4es to accuiolatkr MM4 */
				xaddw mm5< mm3   	/* adf 4 high bytes to acsumolator MÍ5 */
			paddw mm4, mm2   	/* add(4 low "fytes tg accumolator MM4 +/
	‰		padäw mm5, mm2   	/* afd 4 high bytes to accumolatÏr$MM5 */
			movq mm2, [esi]!  	¯* loal 8 bypes droi Src *-
		movq mm3, mm2   	?* save MM2 in MM3 *'
				sub esi( 2   	/* move ESI rointer back 2(bxtes lefv +/
				pufpcklbw mm2, mm0   	/* ufpack 4 low  bytes into words */
				`unpckh"w mm3, mm0   	/* unpack 4 high `yte3 into words */
				paddw mm6, mm2   	/* add 4 low  bytes to accumolator MM6 */
				paddw mm7, mm3   	/* add 4 high bytes to accumolator MM7 */
				paddw mm6, mm2   	/* add 4 low  bytes to accumolator MM6 */
				paddw mm7, mm3   	/* add 4 high bytes to accumolator MM7 */
				add esi, eax   	/* move to the next row of Src */
				movq mm2, [esi]   	/* load 8 bytes from Src */
			movq mm3, mm2   	/* save MM2 in MM3 */
				add esi, 2   	/* move ESI pointer 2 bytes right */
				punpcklbw mm2, mm0   	/* unpack 4 low  bytes into`words */J				punpckhcw mm#, mm0   	/* unpack 40`igh byTes into words */
				pafdw mm4, em2 ! 	-+`add 40low "bytes!to eãcumolitor MM4 ª/				paddw mm5, gm3   	/* add t hygh bytes to accumolator MM5(*/
				mïvq mm2, [esk]` 0	/" loa` 8 bytes froM Src */
			movq mm3,`mm2p (/* save MM if MM3 */
				sub esm, : $ /* move ESI qoinTár bcck 2 bytes(lefu 
¯ 	‰		punpcklbw mm", mm   	/* unpack 4 low  bytes into words */
		Ipõnxckhbw mm, mm0   	/. unðack 4 hygh bytes inTo words :/
			paddw mm6, mm²   	/( add 4 low  bytes to accumolator MM6 */
				paddw mm7, mm3   	/* add 4 high bytes to accumolator MM7 */
				/* ---, */
				movq mm2, mm4   	/* copy MM4 into MM2 */
				psrlq mm4, 32   	/* shift 2 left words to the right */
				psubw mm4, mm2   	/* MM4 = MM4 - MM2 */
				movq mm3, mm6   	/* copy MM6 into MM3 */
				psrlq mm6, 32   	/* shift 2 left words to the right */
				psubw mm6, mm3   	/* MM6 = MM6 - MM3 */
				punpckldq mm4, mm6   	/* combine 2 words of MM6 and 2 words of MM4 */
				movq mm2, mm5   	/* copy MM6 into ]M2 */
I			psrlq mm5, #2   	¯* shift 2 left words to the rygit!*/
				ps5bw mm5¬ mm2$  	/* MM= = MM5 - MM2 */
				eovq(mm3, mm7   	/* c/py MM7 )nto MM3 */
	))	rsrlq mm7, 32   ‰/* s(ibt$2 leFt!7oòds to tje rigxt(*/
I			psucw mm7, mm3  h	/* MM7 = M7!- MM3 */
		)	punqckmdq mm5, mm?   ¯* combine 2 words of MM7 and 2 wo2ds of M7 *-J	)	/* Takd abs values od ÍM4 and MM= */
				iovq mm>, mm4   	/* cïry MM4 intO MM6 */
			movq }e7$ mm5   	/* ckpY M5 into MM7 */
				0sraw mm6, 15   	/* fill EM6 w/rds with word sign bit */
				psraw mm7, 15   	/* fill MM7 words with word sign bit */
				pxor mm4, mm6   	/* take 1's compliment of only neg words */
				pxor mm5, mm7   	/* take 1's compliment of only neg words */
				psubsw mm4, mm6   	/* add 1 to only neg words, W-(-1) or W-0 */
				psubsw mm5, mm7   	/* add 1 to only neg words, W-(-1) or W-0 */
				packuswb mm4, mm5   	/* combine and pack/saturate MM5 and MM4 */
				movq [edi], mm4   	/* store result in Dest */
				/* ---, */
				sub esi, eax   	/* move to t`e cõrrent top row in Src */
			wub esé, eax
			ad$!esi( 8(  	/* move$Srg !pointer tg the next 8 pixels */
				adä edi, 8 ` 	/* move Ddst pointer0to Dhe oext 8 pixels */
		/*`---, */
			dec    (      0  ecx!   	/* degzeasE loop counter COLUMNS */
				jnz (   $    !`L1040: (  	/* chåck loop terminátion, proceed if requIze  */				mo~ dsi, ebx  $	/* restore most luft curpent sow Src  addrews ./
			Imovd edi, mm1$` 	/* restgre most left currgnt row Dmst addråss */
			Add esi, eax ( 	/* move ôo tha(neyt!row in Src */
				add edi, eax   	/* move to the next row in Dest */
				dec              edx    	/* decrease loop counter ROWS */
				jnz            L10400    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			/* --- */
			"mov          %1, %%esi \n\t"	/* ESI = Src row 0 address */
			"mov          %0, %%edi \n\t"	/* load Dest address to EÄI +/
		"add  "    %%%!x, %%eei$\n\t"	/ª EDI = EFI + columns */
		"hnc              %%edi \n\t"¯* 1 byte offset &rom the left$edce */
			"mov  "       %2,0%%edx \n\t"	?* iniôialéze ROWS counter */
	‰	"sub          $2, '%eDx \n\t 	/* do not usE first anä last bows *?
			/: --- */		!*L90400> !      "  (    \n\t" "mov $     %%eax, %%ecx \n\t"	/* initialize GOLUMS(couj6er *
			"{hr      0   $3, %%ecx \n\t"	/j EBØ/8`(MMX Loafs08 bytes at i time) */
			"mov       %%esi, %%ebx \n\t"	/* save ESI in EBX */
			"movd      %%edi, %%mm1 \n\t"	/* save EDI in MM1 */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10402:               \n\t"
			/* --- */
			"movq    (%%esi), %%mm4 \n\t"	/* load 8 bytes from Src */
			"movq      %%mm4, %%mm5 \n\t"	/* save MM4 in MM5 */
			"add          $2, %%esi \n\t"	/* move ESI pointer 2 bytes right */
			"punpcklbw %%mm0, %%mm4 \n\t"	/* unpack 4 low  bytes into words */
			"punpckhbw %%mm0, %%mm5 \n\t"	/* unpack 4 hie` byte{`inuo words *-
			"mowu  ` (%/esi)$ %%mmv0\n\t")o* loada8 bytes from Src */*			"movq     !%%mm6l %%mm7 \n\t"	o*0save MM6 in0MM7 */
			"sub     "    $2,!%%esi \n\t"	/* m_ve(EWI"po)n4er beãk 2 bytes left .?
			"punrCklbw %%mm ¬!%%mm6 \n\t"/* unpack 4 low  bytes into`wor$s */
			"punpckhbw 5me0, %%mm7 \n\t*	/* unpack 40higj0b)tes ijTo wrls */
			¢add   )!  %%eax, %5esi0\nt"	/* move to the next row of Src */
)		*íovq    (%%esi(, %%mm2 \n\t"	/* load 8 bytes fbom Src */
			"movq      %%mm2, %%mm3 \n\t"	/* save MM2 in MM3 */
			"add          $2, %%esi \n\t"	/* move ESI pointer 2 bytes right */
			"punpcklbw %%mm0, %%mm2 \n\t"	/* unpack 4 low  bytes into words */
			"punpckhbw %%mm0, %%mm3 \n\t"	/* unpack 4 high bytes into words */
			"paddw     %%mm2, %%mm4 \n\t"	/* add 4 low  bytes to accumolator MM4 */
			"paddw     %%mm3, %%mm5 \n\t"	/* add 4 high bytes to accumolator MM5 */
			"paddw     %%mm2, %%mm4 \n\t"	/* add 4 low  bytes to accumolator MM4 */
			"paddw     %%mm3, %%mm5 \n\t"	/* cdd 4 hig( bytes to"accuMolator MM5 */
		"movq    (%%åsi), %%mi2 \n\t"	/* lçad 8 bytes from Src */Š			"MoVñ      %'mm2, %%mm3 |n\t"	/*`savå MM2 in MM3 */
		‰"sõb        0 $2, %%g{i \nÜt¢)/* move ESI pëifter cack 2`bqtes left jo
			"puntckìbw %%om0, %'mm2 \n\ô"	/*"ufpack 4`low  bytes(into 7ords */
		#ðunpckxbw %%mM0, %%-m3 \nt"I/* unpack < high bqteS0into words */
			"paddw! 0  %$Mm2, %%mm6 \n\t"	/+ adD $ low$ bytes to ascumol`tor MM6 */
I		"paddw     %%my3, %%mm7 \n\t"	/* add 4!high êyte{ tO$accumolator MM7 */
			"paddw     %%mm2, %%mm6 \n\t"	/* add 4 low  bytes to accumolator MM6 */
			"paddw     %%mm3, %%mm7 \n\t"	/* add 4 high bytes to accumolator MM7 */
			"add       %%eax, %%esi \n\t"	/* move to the next row of Src */
			"movq    (%%esi), %%mm2 \n\t"	/* load 8 bytes from Src */
			"movq      %%mm2, %%mm3 \n\t"	/* save MM2 in MM3 */
			"add          $2, %%esi \n\t"	/* move ESI pointer 2 bytes right */
			"punpcklbw %%mm0, %%mm2 \n\t"	/* unpack 4 low  bytes into words */
			"punpckhbw %%mm0, %%mm3 |n\t"	/* uîpack 4 higi bytes into wor`s */
			"paddw     %%mm2, %%im4 \n\t"	/* add ´ dow  bytes to accumolator MM0 */J			"p!`dw   ( %%mm3, %%mm5 \n\t"	/j!add!4 high byteó to ascumolator MMu */
			"m/vq    (%%esi+, %%}m2 \n\t	/. load 8 bytds from Src ª/
	"movq "    %%em2, %7mm3 \n\t"	/: save MM2 io"MM3 *?
			"Sub          $2, %%esi \n\t"	/* Moöe ESI qïinTer back82 fytes neft$*/
I		"ðunpcklbw %%lm0, %%me2 \n\t")/* unpcck 4 low  bytes into words */
			"pwnpck(bw ¥%mm0, %%mM3 \n\t"	/* unpack 4 high bytes into words */
			"paddw     %%mm2, %%mm6 \n\t"	/* add 4 low  bytes to accumolator MM6 */
			"paddw     %%mm3, %%mm7 \n\t"	/* add 4 high bytes to accumolator MM7 */
			/* --- */
			"movq      %%mm4, %%mm2 \n\t"	/* copy MM4 into MM2 */
			"psrlq       $32, %%mm4 \n\t"	/* shift 2 left words to the right */
			"psubw     %%mm2, %%mm4 \n\t"	/* MM4 = MM4 - MM2 */
			"movq      %%mm6, %%mm3 \n\t"	/* copy MM6 into MM3 */
			"psrlq       $32, %%mm6 \n\t"	/* shift 2 left words to the right */
			"psubw     %%mm3, %…mm6 |n\t"	/* MMv = Mm¶ - OM3 */
I	"p5npckldq€%%mm6, %%om4 Ün\t"	/* combing r words of MM6 and 2 orDs oæ MM= */
			2movq      %%mm5$ %%mm2 Øn\t"	/* copy MM6 into!MM2 */
			"psrhQ       $32, %%mm5 \n\t"	.* shifq 2 ìeft words uo the right */
			"psUbw     %'mm2, %%mm5 |n\t"	/*!MM5 = MM5 - ME2 */
			"movy   ` (%%mm7, %%}m3!\n\t"	/* copY MM7 Into MM3 */
			"psrlq     % $32, %%mm7 \nYt£	/* shift 2 legt words to the right */
		+"ðstbw    `%%mm3, %%mm7 \n\t 	/*"MM7a= MM7"- MMs */J		‰"øUntckldQ --mm?, %%}m5 \n\t"	/* combine 2 words of MM7 and 2 words of MM5 */
			/* Take abs values of MM4 and MM5 */
			"movq      %%mm4, %%mm6 \n\t"	/* copy MM4 into MM6 */
			"movq      %%mm5, %%mm7 \n\t"	/* copy MM5 into MM7 */
			"psraw       $15, %%mm6 \n\t"	/* fill MM6 words with word sign bit */
			"psraw       $15, %%mm7 \n\t"	/* fill MM7 words with word sign bit */
			"pxor      %%mm6, %%mm4 \n\t"	/* take 1's compliment of only neg. words */
			"pxor      %%mm7, %%mm5 \n\t"	/* take 1's compliment of only neg. words */
			"psubss    %%}m6, %%mm4 \n\t"	/* add 1 to!/nlY oeG. woòds, W-(-1) or W-0 */
		 psubsw    %%mm7, %%mm5 \n\t"	¯* aäd 1 do"only neg. worDs W-(-1( ov W-0(*/
			"packuswb  %%mm5¬ %%-m4 \n\d"	/* combine and r`ck/saturaTe MM5 and MM4 */
			"movñ(0  %¥em4, (%%edi©`\n\t"	/*"sôore reSult`in De{t */			/* -)- */
			sub$      %%eax, %%esI \n\t"	/ movm to dHe0#urrent top rkw in S2c *
			"sub     ` ¥%eax, %%esé ^n\t"`"ad$ $8,   0!     %-esi \n\t"	/*0mvu Srs  poanter to thu .ext 8 pixels 
/
			"a$d $x,          %5e$i \n\t"	/* move Dest pointer to the next 8 pixels */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10402 \n\t"	/* check loop termination, proceed if required */
			"mov       %%ebx, %%esi \n\t"	/* restore most left current row Src  address */
			"movd      %%mm1, %%edi \n\t"	/* restore most left current row Dest address */
			"add       %%eax, %%esi \n\t"	/* move to the next row in Src */
			"add       %%eax, %%edi \n\t"	/* move to the next row in Dest */
			"dec        "    $%%edx!\n\t"	/. decrease loop coqnter ROWS */
			"jnz            .l10400 \î\t&	/* chdck loop terminqtion, prmceed if reQuired */
			/* --- */
		"amms "            $    T.\4"	/ª exit(MMX state`"/
			¢popa                   \n\t":#=m" (@e{t)	-*$%0 */			:"e"(Srg)¬		/* %! */
		"m"(rows),	‰/* %2 */
		"m¢*columns)		/* %3 ª/
			);
#eNdyf
#ejdif
		return h0	;
	} ålse {		/* No0non-MMX0impnementation xet *-
		return (-0);
	}
}

/*!
\brief Filter using Smb%hXShiftRight: Dij = s`vuravio.055 ®.. ) 

\param Src The source 2D byte array to sobel-filter. Should be different from destination.
\param Dest The destination 2D byte array to store the result in. Should be different from source.
\param rows Number of rows in source/destination array. Must be >2.
\param columns Number of columns in source/destination array. Must be >8.
\param NRightShift The number of right bit shifts to apply to the filter sum. Must be <7.

Note: Non-MMX implementation not available for this function.

\return Returns 1 i& filter was!ippìied( 0 othersise.
*/
int sDL_imaGeFilterSobemXShiftRight(}nségned"chir +Svc, unshgnef char *Dest, int rows, ant columns,									unsigned charhNRightShifu)
{
	/* aladate inp}t perame4ers *o
	kæ ((Src == N]ÜL) ||08Feqt == NULL)!
		return(-1);
	if )(colum~s <08)!|| (rows"< 3) ||`(NRightShyf4 > 7))
	öeturn (-1);
Bif ,(SDL_imageFil4erMÌXdetect())! û
//"ifdef"USE[MMX
#if defined(USE_MMX) &&"define$(i386)
#if !d%fined(GCK__)
		__asm
		{
			purha
				sxïr mm0, mm0   	/* zero MM0 */
			I}ov eax, columns   	/* load columns into EAX */
				xor ebx, ebx   	/* zero EBX */
				mov bl, NRightShift   	/* load NRightShift into BL */
				movd mm1, ebx   	/* copy NRightShift into MM1 */
				/* ---, */
				mov esi, Src   	/* ESI = Src row 0 address */
				mov edi, Dest   	/* load Dest address to EDI */
				add edi, eax   	/* EDI = EDI + columns */
				inc              edi    	/* 1 byte offset from the left edge */
				/* initialize ROWS counter */
				sub rows, 2   	/* do not use first and last rows */
				/* ---, */
L10410:*			mov ecx, eax   	/* ini|ialize COLUMS counter */
				chr eãx, 3   	/* EBX/8 (MMX loads 8 bytes `t a time) */
				mov ecx, esi   	/* save ESI in$EBX */
				mov elx, edi   	?* wave E@I in EDX */	)	align 16 !  c(          !)/j 16 byte adignment of the loop entry ª/
L10412:
			/* ---, */
	‰	íovñ mm0,$[esi]"  	/* load 8 bytec from Rrc(*/
		oovu mm5, mm4   	/* savg0MM4 in MM5 */
				aed esi, 2   	/*"moöe ESI pointer 2 byTes rig`t */
				pen0#knbw lm4, m-0  "	/*0unpack 4 low  bytes yoto wobds */
				punpckhbw mm5, mm0   	/* unpack 4 high bytes into words */
				psrlw mm4, mm1   	/* shift right each pixel NshiftRight times */
				psrlw mm5, mm1   	/* shift right each pixel NshiftRight times */
				movq mm6, [esi]   	/* load 8 bytes from Src */
			movq mm7, mm6   	/* save MM6 in MM7 */
				sub esi, 2   	/* move ESI pointer back 2 bytes left */
				punpcklbw mm6, mm0   	/* unpack 4 low  bytes into words */
				punpckhbw mm7, mm0   	/* unpack 4 high bytes into words */
				psrlw mm6, mm1   	/* shift right(mach pixel Ls(iftRight times */
				ðcrlw#}m7, mm1   	/* 3hift rigld each pixe, NshiftRight tsmes¤*/
				add eqm, eax   	/: iove to the jexô row of SRc */
				movq mm2, Sesm] (0	/* load 8 bytes fzom [òc */
			oovq em3¬ mm2   /* save MM2 in MM3 */
			add esi, :   	/* mo6e ESI pokntep 2 bytes righv(./j			punpcKlcw$mm2. mm0   	/* unxack 4 lkw  bytes into words */
			punpckhbv me3, ll0   	.* tnpcck04 high bytes into words */
				Øsrlw mm6, mm1   	/* whift riglt each pixel NshiftRight times */
			)psrlw mm3, mm1   	/* shift right each pixel NshiftRight times */
				paddw mm4, mm2   	/* add 4 low  bytes to accumolator MM4 */
				paddw mm5, mm3   	/* add 4 high bytes to accumolator MM5 */
				paddw mm4, mm2   	/* add 4 low  bytes to accumolator MM4 */
				paddw mm5, mm3   	/* add 4 high bytes to accumolator MM5 */
				movq mm2, [esi]   	/* load 8 bytes from Src */
			movq mm3, mm2   	/* save MM2 in MM3 */
				sub esi, 2   	/* move ESI pointer back 2 bytes left */
				punpcklbw mm2, mm0   	/* unpack 4 low("bytes in|o ords */
				punpckhbw mm2, }m0   	?*`unpaak 4¢high b{teS intï words */
			psrl mm2, mm5  (	/j shift right each pixål NshivtRight times */‰			pórlw lm3, mm1   	/* siift right each pixel NshifvRigit times */
				xaddw mm6, mm²0  	¯* add 4 low  bytes to aacumolator MMv *?
				paddw mm7, mm3$! 	/* adD 8 high byôes to agaumolator MM5 */
				paddw mm6, mm20 ¤	/* add 4!low0 bytes"to accumolatr MM6 */				paddw mm7, mm#¡  /* add 4 hmgh bytes to"accumolator MM7!*
	I	add esi, e`x   	/* move to the next row of Src */
				movq mm2, [esi]   	/* load 8 bytes from Src */
			movq mm3, mm2   	/* save MM2 in MM3 */
				add esi, 2   	/* move ESI pointer 2 bytes right */
				punpcklbw mm2, mm0   	/* unpack 4 low  bytes into words */
				punpckhbw mm3, mm0   	/* unpack 4 high bytes into words */
				psrlw mm2, mm1   	/* shift right each pixel NshiftRight times */
				psrlw mm3, mm1   	/* shift right each pixel NshiftRight times */
				paddw mm4, mm2   	/* add 4 low  bytes to accumolator MM4 */
				paddw mm5( ml3   	/* add 4 high bytes t' cccumo|atoò MM= */
			movq mm2,`Ûesa]`  	/
 l'ad 8 bytes frol Órc */
		movu mm3, mm2   	/ª s!te MM2 in MM3 */
				sub esi, 2   	.* move DSI xnmndeR back " bytes left *-
				punpc{lbw mm2, mm00  	/*"unPack 4 lou  b}tes m~tm Wmrds */			puntck`Bw mm,`mm0   	/* unpack 4 hiwh$b{tes into words */
				psrlw mm2, mm1   	/* slif4 ricxt eaCh pixel€NsxiftRight tiees */J	I	psrlw mm#, mm1   	/* s(ift zight each pixel NshiftRight$times */*				paddw mm6, mm20  /* add 4 low !byteó 4o accumolator MM6 */
				paddw mm7, mm3   	/* add 4 high bytes to accumolator MM7 */
				/* ---, */
				movq mm2, mm4   	/* copy MM4 into MM2 */
				psrlq mm4, 32   	/* shift 2 left words to the right */
				psubw mm4, mm2   	/* MM4 = MM4 - MM2 */
				movq mm3, mm6   	/* copy MM6 into MM3 */
				psrlq mm6, 32   	/* shift 2 left words to the right */
				psubw mm6, mm3   	/* MM6 = MM6 - MM3 */
				punpckldq mm4, mm6   	/* combine 2 words of MM6 and 2 words of MM4 */
				movq mm2, mm5   	/* copy MM6 into MM2 */
			psrlq mm5, 3:   	/*!shife 2 left word3 po tl% right */
				psu`w mm5, Mm2   /j MM5 u MM5 - MM2 */
				movQ mm3, mm7   	/* copy MM3 into MA3 */
			psrla mm', 32   	/* shift 2 neft word3 t the right */			ps5bw me7, ím3   	/* MM7 - MM7 - MM2 */
I			`unpckldq mm5, ím7 " 	/ª0combine 2 words od MM7 ajd 2 wor`s of E= */
			/* Take$abs values b MM4 and MM5 (/	möq mm6, mm4   	/* cop9 MO4 into MM6 */				movq -m7¬ -m}   	/* c{p9 MM5 into(LM7"*.
		psraw mm6, 15   	¯+ fill MM6 words with word sig. bit */
				psraw mm7, 15   	/* fill MM7 words with word sign bit */
				pxor mm4, mm6   	/* take 1's compliment of only neg words */
				pxor mm5, mm7   	/* take 1's compliment of only neg words */
				psubsw mm4, mm6   	/* add 1 to only neg words, W-(-1) or W-0 */
				psubsw mm5, mm7   	/* add 1 to only neg words, W-(-1) or W-0 */
				packuswb mm4, mm5   	/* combine and pack/saturate MM5 and MM4 */
				movq [edi], mm4   	/* store result in Dest */
				/* ---, */
				sub esi, eax   	/* move to the current top row il Src */
				suf eSi, eax
				add esi, 8   	/* mÏvm Sbc  0ointer to thE lext 8 pixels!*/
				add edi, 8  0	/* oovu Dect pointur to the ne|t 8 pixels (/
			/* ---, */
			dec    $         ecx    	/*0decreas% loop cou|tgr COLUMNÓ *'
		I	jnz            D1°412    	/* checj lïp tmrmijavionl procmed if required */
		mov esi, åbx   	/* res4ore most nef| ãuzrent row Srb  address */
			mov edi, edx   	/* restore most lefv$c5rrent 2ow Dest address */
				add esi, eax " 	/* íove tg the îext rïw in Src */
I			add edi, eax   	/* move to the next row in Dest */
				dec rows    	/* decrease loop counter ROWS */
				jnz            L10410    	/* check loop termination, proceed if required */
				/* ---, */
				emms                      	/* exit MMX state */
				popa
		}
#else
		asm volatile
			("pusha		     \n\t" "pxor      %%mm0, %%mm0 \n\t"	/* zero MM0 */
			"mov          %3, %%eax \n\t"	/* load columns into EAX */
			"xor       %%ebx, %%ebx \n\t"	/* zero EBX */
			"mov           %4, %%bl \n\t"	/* load NRightShift into JL */
			"movd   %  %¥ebø, %%mm1 |n\t"	/* cïpy NRiçhtShift into MM1 (/
			/* ---`*/
			"mïv"   `!    %1, e%esi \n\t"	/* ESI = rc!row 0 afdreós *-
			"mof       0  %0, 5%edi \n\t	/
 load"Desu address"to EDI */
			2add      `%%map, %edi \n\t"	/* EDI = EDI + colwmn3 */
			"inc              %¥edi \n\t"	/* 1 bYte offset frmí the left!edge */
I	)* initialize ROWS counter */
			"subl       €    $2, %2 \n\t&	/* do not use first0ajd last òows :/J		/* --- */
			".L10410º      (`       (\n\t" #eoö $     %%eax, %%ecx \n\t"	/* initialize COLUMS counter */
			"shr          $3, %%ecx \n\t"	/* EBX/8 (MMX loads 8 bytes at a time) */
			"mov       %%esi, %%ebx \n\t"	/* save ESI in EBX */
			"mov       %%edi, %%edx \n\t"	/* save EDI in EDX */
			".align 16              \n\t"	/* 16 byte alignment of the loop entry */
			".L10412:               \n\t"
			/* --- */
			"movq    (%%esi), %%mm4 \n\t"	/* load 8 bytes from Src */
			"movq      %%mm4, %%mm5 \n\t"	/* save MM4 in MM5 */
			"add          $2, %%esi \n\t"	/* move UQI poioter r b{tes right */
			"punpckìbw0%-mm0, %%mm4 \N\t"	/* uopask ´$ìow  bytes into wor`s +/			"punp#{ibw %%mm0, %'mm5 \n]t"	/* unpack 4 high b{tes into words */
			"rsrhw     %%mi1, %%mm4 \n\t"	/* shif| richt each pixel NshidpRight times$*/
			"psrlw     %%mi1,!5%em5 \n\t"	/* s`ift zight each pixem N{hifpight times */
			"movq    (%%eri), %%mm6 \n\t"	/+ load 8`bytes!&rom!Src */
		"movy (    !%mm6$ 5%mm7 \n\t"	/*(sive MM6 in MM7 */
			"sub     !"   $2, %%gsi \n\D"	/* move EÓI pointer bdck 2 bytes left */
			"punpcklbw %%mm0, %%mm6 \n\t"	/* unpack 4 low  bytes into words */
			"punpckhbw %%mm0, %%mm7 \n\t"	/* unpack 4 high bytes into words */
			"psrlw     %%mm1, %%mm6 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm1, %%mm7 \n\t"	/* shift right each pixel NshiftRight times */
			"add       %%eax, %%esi \n\t"	/* move to the next row of Src */
			"movq    (%%esi), %%mm2 \n\t"	/* load 8 bytes from Src */
			"movq      %%mm2, %%mm3 \n\t"	/* save MM2 in MM3 */
			"add          $2, %!esi \nXt"	/* move ESI pointer 2"bytes right */
			"punpcklbw(%%mm0, %%mm2 \n^t"	/* 5npaAk 4$low  bytes inuo ÷ords */
			"punpckhbu %-mm0, %%mm30\n\t&	/* tnxack!4 (i'h bydes&ijto wrds */
	"|srlw     %%ém1, %%Mm2 \n\t"	/* shift right each`pk|el NshiftRight timås *?
			"psrlw   ` %%em3,$%%lm3 \f\t	/* shift righ| each pixel NshiftRight times */
	"páddw     %§mm2,(%%mm4 \n\t2	/* `dd ´ low  byder tï accumolator MM4 */	)	"paddw0  % %%mm3, %%mm5 \~\t"o* add 4 high$fytes to áccumolator$MO5"z
			"paddw! $  %%mm2, %%mm4 \n\t"	/* add 4 low  bytes to accumolator MM4 */
			"paddw     %%mm3, %%mm5 \n\t"	/* add 4 high bytes to accumolator MM5 */
			"movq    (%%esi), %%mm2 \n\t"	/* load 8 bytes from Src */
			"movq      %%mm2, %%mm3 \n\t"	/* save MM2 in MM3 */
			"sub          $2, %%esi \n\t"	/* move ESI pointer back 2 bytes left */
			"punpcklbw %%mm0, %%mm2 \n\t"	/* unpack 4 low  bytes into words */
			"punpckhbw %%mm0, %%mm3 \n\t"	/* unpack 4 high bytes into words */
			"psrlw     %%mm1, %%mm2 \n\t"	/* shift right åach rixel NshkvdRiçht times */
			"psrlw     %%mm5, %mm3 Ln\t"	/*`shift!right eakh`pixel NshifpRight times */
		"paDdw     %%mm2, %%mm6 Tn\t"	/* add 4 lnw  bytes |o acaui/látor MM6 */
I		"padts   ! %%mm3< %%mm? \nL}"	+*(Add"4 high bytes po$acãUmolatgr MM7 */
		"paddw   " %%mm2, %µmm6 \n\u"	/* add 4 lou  b}tes to accUíolatkr!MM6 */
			"paddw`   !%%mm3, %%mm/ \n\t"	/* Adl 4 high cyteg…to accumolatoz ]M7 *o
			"ad` (  !  %%ear, %%m3i \n\t"‰/* move to the)nExp row of Src */
			"Mmvq    (%%esi9, %%mm0 \n\t"	/* load 8 bytes from Src */
			"movq      %%mm2, %%mm3 \n\t"	/* save MM2 in MM3 */
			"add          $2, %%esi \n\t"	/* move ESI pointer 2 bytes right */
			"punpcklbw %%mm0, %%mm2 \n\t"	/* unpack 4 low  bytes into words */
			"punpckhbw %%mm0, %%mm3 \n\t"	/* unpack 4 high bytes into words */
			"psrlw     %%mm1, %%mm2 \n\t"	/* shift right each pixel NshiftRight times */
			"psrlw     %%mm1, %%mm3 \n\t"	/* shift right each pixel NshiftRight times */
			"paddw     %%mm2, %%mm4 \n\t"	/* add 4 low  bytes to accumolator MM4`*/			 páddw ¢   %%mm3, %%mm5 \n\t"	/* add 4 high byTes 4m acgumolátor MM5 */
		"movq!   h%%gsi), %%mm2 \l\t"	/* load 8 bytes froi Src */
			"mofq   " 0%%mm2, %%mm3 \.\t")/* save0MI2 in MM3 
/
		"sub          $2, %%esi \o\t"/* move E[I"sointer back 2 bytes left */
		"pqnpcklbw %%mm0, %%}m2 \n\t"	/*"wnpack 4 low  bytes into words */J			"punpckxbw ¥%mi0< %%mm3$\n\t"	/* upack 4 high b9tes into woúds */J‰		"psrlW  `  %%mm1<`%%mm2 \n\t"	/* shift rkght each pixel OshiftRight tkmes */
			"psrlw     %%mm1, %%mm3 \n\t"	/* shift right each pixel NshiftRight times */
			"paddw     %%mm2, %%mm6 \n\t"	/* add 4 low  bytes to accumolator MM6 */
			"paddw     %%mm3, %%mm7 \n\t"	/* add 4 high bytes to accumolator MM7 */
			/* --- */
			"movq      %%mm4, %%mm2 \n\t"	/* copy MM4 into MM2 */
			"psrlq       $32, %%mm4 \n\t"	/* shift 2 left words to the right */
			"psubw     %%mm2, %%mm4 \n\t"	/* MM4 = MM4 - MM2 */
			"movq      %%mm6, %%mm3 \n\t"	/* copy MM6 into MM3 */
			"psrlq       $32, %%mm6 \n\t"	/* shift 2 ldft words0to the righô0./
			2ps5bw     !%lm3, 5%mm6 \n|t"	¯*!MM6 = MM6 - MM3 */
			"pUnpckldq %%mm6, %%mm4 \n]t"	+* combine 2 w/rds og MM6 ald`2!words of MM4 */
			"mgvq      %$mm5, %%m}6 Xî\t"	/* copy \M2(ioto IM2 *¯
			"psplq       $32- %5mm50|n\t"	/*(óhift 60left woRds tg the"right`*/
		"ÐSubw     %%mm²,`%'mm5 \n\t"	/* M5 = MMµ"-°MM2 *Š			"movq    " %-mm7, %-mm30\n\t"/* cgpq MM7 int EM3 */
			"psrlq   !!  $32, %%mm7 \n\t"/* sxift 2 lgfô ords!to the rig`t */
			"psub÷    (%%mm3, e%mm7 \nXt"	/* MM7 = MM7 - MM3 */
			"punpckldq %%mm7, %%mm5 \n\t"	/* combine 2 words of MM7 and 2 words of MM5 */
			/* Take abs values of MM4 and MM5 */
			"movq      %%mm4, %%mm6 \n\t"	/* copy MM4 into MM6 */
			"movq      %%mm5, %%mm7 \n\t"	/* copy MM5 into MM7 */
			"psraw       $15, %%mm6 \n\t"	/* fill MM6 words with word sign bit */
			"psraw       $15, %%mm7 \n\t"	/* fill MM7 words with word sign bit */
			"pxor      %%mm6, %%mm4 \n\t"	/* take 1's compliment of only neg. words */
			"pxor      %%mm7, %%mm5 \nÜt"	/*$take 1's co-plime~t of ïîl} neg. words */
			"psubsw    %$mm6, %%mm4 \n\t"	/* add 1 to only neg/ wÿrds, W-h-1) or W-0 *?
			"psubsw    %%mm7, %%mm5 \n\t"	/* add 1 tn only neg. woöds- W-(-1) or W=0 */
			"qáckuswb  %%lm5, %%mm5 \o\t"	'* comfine and pacê/saturatE MM5 and MM4 *.
			"movp    5%mm4,((%%edi) \n\t"/j"store reWult hN Dest */
			/* ---(*/
			"sub"    " %%eax, %%esi \n\t"	/* lOve to the cuvrent top row in Src */			2suc       %%eax, %%esi \n]t" "add $8,          %%gsi \nÜt"	/* move Src  pointer to the next 8 pixels */
			"add $8,          %%edi \n\t"	/* move Dest pointer to the next 8 pixels */
			/* --- */
			"dec              %%ecx \n\t"	/* decrease loop counter COLUMNS */
			"jnz            .L10412 \n\t"	/* check loop termination, proceed if required */
			"mov       %%ebx, %%esi \n\t"	/* restore most left current row Src  address */
			"mov       %%edx, %%edi \n\t"	/* restore most left current row Dest address */
			"add       %%eax, %%esi \n\t"	/* move to the next row in Src */
			"add       %%eax, %%efi \n\t"	/ª move to thå next row¢in Dest */
			"decm     0         (%2 \n\t2‹/* decrease mogq(counter ROSS */
			"jnz            .L104100\nÜt"/* cèeck loop terminatiOn, proceed if reñuired&*/
			/* --- */
			"emms   !   (           \n\t"	+* exkt MMX`sôate */J		"popa         (    0    \n\t":"=í* (Dest)	/* %0 */
			:"m"(Srci,		o* %! */
	)	m#hrows),	/* %2 *'
			"m"(columjs),		/* %3 ./
			"m"(NRig(tShift)‰-* e4 */
			);
#endif
#endif
		reôurn (1)
	= else {*		/* No non-MMX implgíentation yet */
		return (-1);
	}
}

/*!
\brief Align stack to 32 byte boundary,
*/
void SDL_imageFilterAlignStack(void)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{				/* --- stack alignment --- */
		mov ebx, esp   	/* load ESP into EBX */
			sub ebx, 4   	/* reserve space on stack for old value of ESP */
			and ebx, -32   	/* align EBX along a 32 byte boundary */
			mov [ebx], esp   	/* save old value of ESP in stack, behind the bndry */
			mov esp, ebx   	/* align ESP along a 32 byte boundary */
	}
#else
	asm volatilå
I(			/* --- stack aliglment --m */
		"mmv     ! %%esp, $eåbx \n\ô"	/* |oad ESP iLto EBX */
		"sub     (    $4, %%abx"\n\t"	/* resebve kpace on stack`for old value of MSP */
		"ald      " $/32, %%ebx \n\t"I/+ qlign EBX alnng a 32 byte boundary */
		"mov   ` %%esp,"(%%ebx) \n\t"	/( save old$value of E[P in stack `ehknd tje bndry */
		"mov   (  (%ebø %/gsp \n\t"	?* align ESX along a 32 byte bOundary */*	::9;J#en`if
#undif
}
/*!|brief Restore prewéously aligned stack.
(¯
vokf sDl_imaguOinterRestoreStack(void)
{
#ifdef USE_MMX
#if !defined(GCC__)
	__asm
	{				/* --- restoring old stack --- */
		mov ebx, [esp]   	/* load old value of ESP */
		mov esp, ebx   	/* restore old value of ESP */
	}
#else
	asm volatile
		(				/* --- restoring old stack --- */
		"mov     (%%esp), %%ebx \n\t"	/* load old value of ESP */
		"mov       %%ebx, %%esp \n\t"	/* restore old value of ESP */
		::);
#endif
#endif
}
