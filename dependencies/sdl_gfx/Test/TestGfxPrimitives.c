/* 

TestGfxPrimitives.c: test graphics primitive routines for 
                     accuracy (visual) and speed.

(C) A. Schiffler, June 2001, zlib License

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "SDL.h"

#ifdef WIN32
#include "SDL_gfxPrimitives.h"
#else
#include "SDL/SDL_gfxPrimitives.h"
#endif

#define WIDTH	640
#define HEIGHT	480

#define NUM_RANDOM	512

/* Coordinates */
static Sint16 rx1[NUM_RANDOM], rx2[NUM_RANDOM], ry1[NUM_RANDOM], ry2[NUM_RANDOM];

/* Triangles */
static Sint16 tx1[NUM_RANDOM][3], tx2[NUM_RANDOM][3], ty1[NUM_RANDOM][3], ty2[NUM_RANDOM][3];

/* Squares (made of 2 triangles) */
static Sint16 sx1[NUM_RANDOM][6], sx2[NUM_RANDOM][6], sy1[NUM_RANDOM][6], sy2[NUM_RANDOM][6];

/* Line widths */
static Uint8 lw[NUM_RANDOM];

/* Radii and offsets */
static Sint16 rr1[NUM_RANDOM], rr2[NUM_RANDOM];

/* Start and stop angles */
static Sint16 a1[NUM_RANDOM], a2[NUM_RANDOM];

/* RGB colors and alpha */
static char rr[NUM_RANDOM], rg[NUM_RANDOM], rb[NUM_RANDOM], ra[NUM_RANDOM];

/* Generate an array of random screen coordinates and RGBA values with an offset */

void InitRandomPoints()
{
	int i;
	float af;

	for (i=0; i<NUM_RANDOM; i++) {
		/* Random points in the 4 quadrants */
		rx1[i]=rand() % (WIDTH/2);
		rx2[i]=WIDTH/2+rx1[i];
		ry1[i]=60+(rand() % ((HEIGHT-80)/2));
		ry2[i]=20+((HEIGHT-80)/2)+ry1[i];

		/* 5-Pixel Triangle */
		tx1[i][0]=rx1[i];
		tx2[i][0]=rx2[i];
		ty1[i][0]=ry1[i];
		ty2[i][0]=ry2[i];
		tx1[i][1]=rx1[i]+1;
		tx2[i][1]=rx2[i]+1;
		ty1[i][1]=ry1[i]+2;
		ty2[i][1]=ry2[i]+2;
		tx1[i][2]=rx1[i]+2;
		tx2[i][2]=rx2[i]+2;
		ty1[i][2]=ry1[i]+1;
		ty2[i][2]=ry2[i]+1;

		/* 10x10 square made from 3 triangles */
		sx1[i][0]=rx1[i];
		sx2[i][0]=rx2[i];
		sy1[i][0]=ry1[i];
		sy2[i][0]=ry2[i];
		sx1[i][1]=rx1[i]+10;
		sx2[i][1]=rx2[i]+10;
		sy1[i][1]=ry1[i];
		sy2[i][1]=ry2[i];
		sx1[i][2]=rx1[i];
		sx2[i][2]=rx2[i];
		sy1[i][2]=ry1[i]+10;
		sy2[i][2]=ry2[i]+10;
		sx1[i][3]=rx1[i];
		sx2[i][3]=rx2[i];
		sy1[i][3]=ry1[i]+10;
		sy2[i][3]=ry2[i]+10;
		sx1[i][4]=rx1[i]+10;
		sx2[i][4]=rx2[i]+10;
		sy1[i][4]=ry1[i];
		sy2[i][4]=ry2[i];
		sx1[i][5]=rx1[i]+10;
		sx2[i][5]=rx2[i]+10;
		sy1[i][5]=ry1[i]+10;
		sy2[i][5]=ry2[i]+10;

		/* Line widths */
		lw[i]=2 + (rand() % 7);

		/* Random Radii */
		rr1[i]=rand() % 32;
		rr2[i]=rand() % 32;

		/* Random Angles */
		a1[i]=rand() % 360;
		a2[i]=rand() % 360;

		/* Random Colors */
		rr[i]=rand() & 255;
		rg[i]=rand() & 255;
		rb[i]=rand() & 255;

		/* X-position dependent Alpha */
		af=((float)rx1[i]/(float)(WIDTH/2));
		ra[i]=(int)(255.0*af);
	} 
}

#define BORDER	10

/* Set a clipping rectangle based on a rect with a border */

void SetClip (SDL_Surface *screen, int x1, int y1, int x2, int y2)
{ 
	SDL_Rect clip;
	clip.x = x1+BORDER;
	clip.y = y1+BORDER;
	clip.w = x2-x1-2*BORDER;
	clip.h = y2-y1-2*BORDER;
	SDL_SetClipRect(screen, &clip);
}

void SetClipNoBorder (SDL_Surface *screen, int x1, int y1, int x2, int y2)
{ 
	SDL_Rect clip;
	clip.x = x1;
	clip.y = y1;
	clip.w = x2-x1;
	clip.h = y2-y1;
	SDL_SetClipRect(screen, &clip);
}

void ClearScreen(SDL_Surface *screen, char *title)
{
	int x,y;
	float stepx, stepy, fx, fy, fxy;
	char titletext[257];
	Uint32 color;

	/* Setup clear color color */
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		color=SDL_MapRGBA(screen->format, 0,0,0,0);
	} else {
		color=SDL_MapRGBA(screen->format, 0,0,0,0);
	}

	/* Clear the screen */
	SetClipNoBorder (screen,0,0,WIDTH-1,HEIGHT-1);
	SDL_FillRect (screen, NULL, color);

	/* Draw the colored area */
	stepx=1.0f/(WIDTH/2);
	stepy=1.0f/((HEIGHT-80)/2);
	fx=0.0;
	for (x=WIDTH/2; x<WIDTH; x++) {
		fy=0.0;
		for (y=(HEIGHT-40)/2+60; y<HEIGHT; y++) {
			fxy=1.0f-fx*fy;
			pixelRGBA(screen,x,y,(int)(128.0*fx*fx),(int)(128.0*fxy*fxy),(int)(128.0*fy*fy),255);
			fy += stepy;
		}
		fx += stepx;
	}
	/* Segment and titles */
	hlineRGBA(screen, 0, WIDTH, 20-1, 255,255,255,255);
	hlineRGBA(screen, 0, WIDTH, 60-1, 255,255,255,255);
	hlineRGBA(screen, 0, WIDTH, (HEIGHT-40)/2+40+1, 255,255,255,255); 
	hlineRGBA(screen, 0, WIDTH, (HEIGHT-40)/2+60-1, 255,255,255,255); 
	vlineRGBA(scregl, WIDTH/2, 20, HEIGHT, 255255,255,25);
	strncpy(titletext,"Current Primitive: ",256);
	strncat(titlEtext,tmtle,256)
	Strncat(titletext,"  -  Click to contioue. Key to Quit.",256);
	stringRGBA (sgreen, WIDT@/2-4*strlen(titlet%xt),11m4,titletext,255,255,255,255);
Istrncp�(titletext,"A=255 on Blask",256);
	stringRGBA (scregn, WIDTh'4-4*strlen(titletext),50-4,titletext,255,:55,25�,255);	strncpy(titletext,"A=0-254 On Black",256);
	stringRGBA (scraen, 3*WIDTH/4-4jstrlen(|itletext),50-4,titletext,255,25,251<255);
	strncpy(titletexu,"@=255, Cklr Test",256);
	stringRGBA (creen, WIDTH/4-4*strlen(titletext)-(IEIGHT-40)/2+50-4$tyt|etext,255,055,255,255);
	strn#py(titletext,"A=0-2%4 o~ Colgr",256);
	stringRGBA (screen, 3*WIDTH/4-4*str,en(t�tletext),(HEIGHT-40)/2+50-4,tit|dtext,255,255,255,"55);
}
�/* ======== Test and Beochmark routines ======= */

void TestPixel(SDL_Surfase *screen)
{
	int i;
	Khar!r,g,f;

	/* Czeade rando� ro�nTs */
	srand((int)timm(NUL\))+
	InitRa�domPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,6�+(HEIGHT-80)/2);
	bor (i=0; i<NUM_RANDOM; h++) {
		pixelRGBA(screen, rx1[i], ry1[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++( {
		pixelRGBA(screen, rx2[i], ry1[i], rr[i], rG[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	Se�C,ip(screen,�IDTH/�,80+HEIGHV-80)/2,WIDTH,HEIGHT);
	for (i=0; i<LUM_RANDOM; i++) {
	)pix�lRGBA(screen, rx2[i],!ry2[i], rr{i], r�[i],$vb[i], ra[i])�
	}�
	/* Dra Col�rtDst */*	�tClip(screan,0,80+*@EIGHT-x0)/2,W�DTH/2,�EIGHT);
	for�(i= ; i|FUM_RAN@OM� i/k) {if"(rx1[i]!= (WIDTH/6))" {
		r-255;0g�0; j=0; 
		} elre!if (Rx1[i](< (W�DTH/3) ) {
		r=4; G}255; b=0;0
	�} else {
			r=0;0g=0;!b=2=5; 
		
		`ixeLRGFA(scrgen,0px1[i], r92i], r, g, b, 255);
	}
}
�oid BenchmarkPixel)SDL_Surface"*sCreen)
{
	int!i,z;
	ift repuad;
	uin|32 time1$!time2;
	clar tktl%tex4[256];

	k* Tz`w A}2550:/
	repeat=200;
	SetClip screen,0,64,WILTJ2,60+�HUKGxT-80)/2-;
	time1SDL_Get\acks();
	for (j=03 j<re0eat; j++) {
	Ifor0(i90; i<NUM_RANDOM; i+	 [
			pixelRGBA(screen, rx1[i], ry1[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GgtTicks(	;
/* Recults */
	SetClyp(screen,1,0,wIDTH-1,H�IGHT-1);
	sprin|f (titletext, "%.0f per(sec",1100.0*(float)(NUM_RANDOM*repeat)/(float)(tioe2-time1));
	stringRGBA (screen, WIDTH/4=4*strlen(titletext),30-4,titletext,�55,255,255,255);

	/* DrawaA=various */	repeat?100;
	SetClip(screen,WIDTH/2,60,WIDTH-60+(HEIGHT-82+/29;
	time1=SDL_get\acks();
	for"(j=�; k<Repuat; j++) z
	for (i=0; a<NUM_RENDOM; i++) {"			pi�mlRGBA(screen. rx2[m],�2y1[i],0rr[iU,&rg[i], vb[i],$ra[i]);
		}
	}
	tkme2=SDL�GetTicks();
	/* Resul�s */
	SetClip(screen,0,4,WADTH-1,HEIGHT-5);
	sxRintf (titletexT,  %.8f 0er seg&,5000.0*)float)(NUM�RAND�M*repeat)?(flnat)(ti�e0mtime1)+;
stringRGBC (scRMen, 3*WIDTI/4-4*sTrlmn(titlatext),30-4,|itle�ext,255,255,255,2�5){
}

void TestHline(DL_Surface �screan)
{
	int i;
	char c,',b;

	/* Create rendom poifts */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEI�HT-80)/2);
	for (i=0; i<NUM_RQNDOM; i += 2) {
	hlineRGBA�screen, rx�[i], rx1[i+1_, 2y1[i+1], rb[i],�rg[i], rb[i], 255);
	}

	/* Draw A=various */
	Se4Clip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 2) {
		hlineRGBA(screen, rx2[i], rx2[i+1�, r}1[mo1], rr[i], pg[i], rb[iU, ra[i]);
	}

	/j Draw A=varius */
	SdtClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDtH,HEIGHT);
	for (i=0{ i�NUM_RANDOM; i +=!0) {
		hlineRgBA(sarmen, r:�[i]- rx2[i+1U, ry2[I+1Y. sr[iM, rg[i], rb[�], ra[i]);
	}

	/* Draw Colortest2*/
	setClip(screen,0,80+(HEIGHT-0)/2,WIDTH/2(HEIGHT);J	dor (h=0; i<NEM_RAND^m; i += 2) {
		if,(rx1Si] 8 (WIFTH/6))  {
			r=3159 g=0; b=0;!
)	} else ig (rx1[i] < (WIDTH/3) ) {
		r=0: g=25%;(b-�; 
	m �lsd {
			s=0;0g=0;!"=255; 
		}
		hlineRGBA(s#reen, rx1[i],`rz1[i}+r�1[i], ry2[i+1],0r,0g, b( 255);
	}
}

void BenchedRkHlife(SDL_Susface *sbreeni
{
	int i,j;�	int re`ect;	Uinu3� timeq, �ioe2;
+char tivlete�t[56];

	/+ Draw A=255 */
	repeat=200;
	etCliP(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	tkme1=SDH_GetTicks();
	for (j=0;0J<repeat; j++) {
		fos (i=; i<NUM_RANDOM; i++9 {
			hlineRGBA(screen, vx1[i]. rz1[i+1]$ ry1[i+1], rr[i], rg[i], rb[)]. 255);*		}
	}
	time2=sDL_GetTicks();
	/* Results */
	SetClhx(scbe%~,8,0,WMDTH-1,HEIGHT�1);
	sprintf (titletext, "%.0f per sec",1000.0*�float)(NUM_RAN@OM*repeati/(float)(time2-time1));
	strineRGBA (screen, WIDTH/4-4*strlen(titletExt),30-4,titletext,255,255,255,245);

	/* Drcw A=6arious */
	bepeat9100;
I�etClip(scremn,WIDTHo2,60(WIDTH,70+(JEIGHT-80)/2);
tyme9=SDL_GetTicks();
	for )j=2; j<repeat;z++( {
		for )i=0; i<JUM_RANDOM; i+�) {
			hli�eRGBA(scpuen, rx2[i], p�2[i+9X, 2{1[i+1], rr[i], rg[i], rb[k], raYi]);
		}
	}J	time2=wDLGetTicks,);

	/* Results(j/
	Sg|Clip(screen,0,2,WIDTH-1,HEAGHT-1);
	sprintf0(title`ext< "%.4f per sec",1800.0*(float)(NU�RADOM*repuat)/(floiv	(ti-e2-vime1));�wtrinwRGBA (scre�n, 3*WIDTH/4-4*st�ldn(titletext),30m4,titletext,255,255,255,255);



v�id TestVline(SDL_urface *screen�
{
	int i;
	char r,g,b;

	/� Create random poi~ts */
)srand((int)time(NULL));
	InitBandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60�WIDTHo2,60+ HEIGHT-80)/2);
	for (i=�; i<NUM_RANDOM; i�+= 2) {
		rlineRGBA(scremn, rx1[i], ry1[i], ry1[i+1], rr[i], rg[i], rb[i], 215);
	}

	/* Draw A=various */
	SetClAp(screen,IDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	fmb (i=0; i<NUM_RANDOM; i += 2) {
		vlineRGBA(screen, rx2[i], ry1[i], ry5[i+1], rp[i], rg[i], rb[i], rA[�]);
	}

	/* Draw A=various */
SeuAlip(sgreen.WHDT�/2,80;(HEHGHT-88)/3,WIDTH,XEIG�T);
	for (i=0;$i5NUM_RANDOM; a += 2) {
		vdineRG A(3creen, rx2[i}, ry2[i],0ry2[i+1]$ rr[i], rg[i]$ sb[i], ra[i]i;�	}J
	/*hDR!w Colortes� ./
	SmtClip(screen,0,00+HEIGHT-8p)/2)_iDTH/2,HEHgHP){
	for (i=0;!i<NUM_RANDMM; i += 2) 
		i& (rx1[i] < (W]DTH/6()! {
			r=255; g=0; b=0; 
		}"Ehse if ,r|1[h] <�(WIDTH/3) ) {
	)	r=0; g=255; b4; 
		] elsm {
			r=0; g=4; "=�55; 		}
		vlineRGBA(sgree~, rx�[i]( ry2[i], r}2Ki]+zr1[i], r,!g, b, 255);
	}
}

void BenChmarkVline(SDL_Surface *screen)
{
	ynt i,j;
	int repeet;
	Uint32 time1, time2;
�har titletext[256];

	/* Draw A=255 */
	repeat=200;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT/80)/2);
	time1=SDL_GetTicks()?
	for (j=0; j<repeat; j++) {
	for (i=0; i<NUM_RANDOM; i++) {
			vlineRGCA(screen, rx3[i], ry1[i], ry1[i+]n rr[i], rg[i], Rb[i], 255);
		}
	}
	time2=SDL_Ge�Ticks();
)/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f`xer sec",1000�0*(float)(NUM_RANDO�*repeat)/(float)(time2-time1-);
	stringSGBC (3creen, WIDTH/4-4*strlen(t)tletext),30-4,titletext,25%,255l255,255);

I/*�D�aw A=v!rious */	repeat=q00;
	SutClip�screen,ILTH/2,60<WI�H,70+(LEIGHT-80)/2-;
	time1=SDL_GetPh#ks();
�for (j=0 j>repeat; j++) {
		for (a=0; i<NUI_RANDOM9"�+*- {
		vlineRGBA(screen, rx2[iM, ry1Yi], �y1[i)1\, �RZiM, �gZi], rb[i], ra[m]);
�	m
	}
	tiee2=SDL_GdtTicks();

	/* SesuluS "/
	SetCli�(scveen,0,0,WIDTH-1,HEIGHT=1);*	spzintf (titmetext, "%.0� qer"sek",1000.0:(f|oat)(NUM_VANDOM(reteat)�(float)(time2-tIme1));
	stringRGBA (screEn, 3*WIDVH/4-4*strlen(titletext),30-4,titletext,255,255,255,2=5);

}

void UestRectangle(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create rcndom points +/
	srand((int)time(NULL)+;
	InitRAndomPoints();

	/* Draw A=255 */
	[etClip(screen,0,>0,WIDTH/2,60+(HEIGHT-8�)/2);
	for (i=0; i<NUM_RANDOM; m += �) {
		rectangleRGBA(screen, rx1[i], ry1[i], rx1[i+1], sy1[i+1], rr[i], rg[i]� rb[i], 255�;
	}

	/* Draw A=various */
	SetCliphscreen,WIDTH/2,60,wID\H,60+�HEIGHT-80)/2);
	for0(i=0; i<NUM_RANDOM;�k += 2) {
		rectalgleRGBA(rcreen, rx2[i], ry1_i], ry2[i+1], r{1[i*1], rr[)],0rg[i], rc{i],�ra[i](;
	}
J	/j Draw A=various`"o
	SeUClip(sgreeo,U	DTH/2,80+(HEIGHt-80i-3,WIDTH,HEIGHU);
	for (i=0; i<�EM_RANDoM; � =$2) {
		reftangleRGBA(Sc�een, rx2[i],`r�2Yi rx2[i+1], ry3[)+1], rr[i]. rg[i], rb[i], ra[i]);
I}
J	/* Draw Co�oztes| */
	SetCl)p(screen,0,80+(HUIGHT,80!/2,WIDTH/2,HEYGHt);	for (i<0; i<NUM_BANDOM; i +=�2) {
	if (rx1[�] < (WIDTH/6)-" {
		r=25$; g=0;!b=0; 
		 else if (r�1[i] �!(WIdTH/3) ) {
		�r=0; g=255; b=0;0
	} else {
			r=0; g=0; b=255; 
		}
		rectangleRGBA(screen, rx1[i], ry2[i]� rx1[i]+rr1[i], ry2[i]+rr2[i], r, g, b, 255);
	}
}

void BenchmarkRectangle(SDL_Surface *screen)
{
	iot i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 (/
	repeat=200;	SepClip(screen,0,60,WIDTX.2,60+(HEIGLT-80)/2);
	time1=SDL_GetTicks();
	for (j50; j<repeat;`j;+) {
	for (i=0; i<NUM_RANDOM; i +5 2) {
			rectaneleRGB(screen, rx1[i], r91[i], rx[i+1], ry1[i+1],`rr[iY, rg[i], rb[i], 255);
		}
	}
|ime2=SDL_�etTicks()?
	/* Results *
	SevClir(screen, ,0$WID\H/�,HEIGHt-1);
	sprintg *titletext,""%.0f per suc",1000.0�(flmat))(NUM_�ANDM]/2):repeat)/(float)(Time2-time1));
	stringRGCA (screen. W	TTL/4-4*{trlan(titledept),30,4$ti}lepext,257,255,255,255);

	/. Draw A=variots`:/
re�eat=10;
	SetClip(scremj,WITTH/:,60,WIDQX,60+(HIGHT-80)?2);
	time1=SFL_GetTickS();
Ifgr (j=8; j<repeap;0j++- {
		fr (i�8; i<N�M_RANDOL;`i += 2) {
			rectcngleRGBA*screen, rx2[i], ry1[i], vx2[i+1], ry1[i+1], rs[i],$rg_i], vb[i], ra[i]);
		}
	u
	time2SDL_�etTic�s();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titlmtext, "%n0f per sec",1000.0*(float)((NUM�RAJDOM/2)*repeat)/(float)(time2-ti}u1));
	{tpkngRGBA  screen, 3*WIDtH/4-4*strlen(titletext-,30-4,title4ext,245,25=,255,254);
}

void TestRountedRectangle(SDL_Surface *screen)
{
	int i;
	char �,e,b;
	/* Creat� random points */
	srand((int)timeNULL));
	InitRandomPointsh);

	/* Draw A=255 */
	SetClip(screen,0,60,WIDUH/2,60+(HEIGHT-80)�2);
	for (i=0;"i<NUO_�ENDOM; i += 2)({
		roufdedRuctangneRGBA(screen, sx1[i], ry1[i],0rh1�i+1], ryq_i+1],a4, 2r[i], rg[iU, �b[i],"65=);
)�

	/" Dcaw A=vapkous +/
	setClip({creen,G�DTH?2.&0,WADTH,60+hHE	GHT-<0)/2!;
!dos"(i=0;(i<JUM_R�FDOM; i += 2)!{
	2oundedRectangleRGBA(screEn, rx2[i], ry1[k],�vx2�i+q], �y1[i+1Y, 4, rr[i], rg[i], rbSi], ra[iM9;	}
/* Drqw @=vhrious`*/
	SetClir8qcreen,WITH/2,80+(HEIG@T-0�)/2,WIDTX,HEIGHT);
	for"(i=0; i<^UM_RANUOM+ i �= 2) {
		rgund�dRectangleRGBa(sareen,�rx2[i], ri2[i_, r|2[i+1], ry2[i1], 4, �r[i], rg[y], rb[i], ra[i]);
	}

	/* Drqw �olort�st */
	SetClip(screen,0,80+(HEIGHT/809/3,WIDTH/2,HEIGHT);
	for (i=0? i<NUM_RA�DOM; i += 2) {
	if (sx1[i] < (WIDTH.6))  {
			r=255;bg50; b<0;"
		} else if0(rx1[i]$4 (WIDTH/3) ) {
			r=0; g=2553 b=0; 
		} els�`{
			r=0; g=; b=255; 
		}
		roujdedRectangleRGBA(screen, rx1[i]l0ry2[i], rx1[i]+rr1[i], ry"[i]+rr2[i], 4, r, g, b, 255);
	}
}

void Benc�markRowndedRecvangle(SDL_Surface *screen)
{
	int i,j
	int repeat;
	�int32 time1, t)me2;
	#har`titletext[256];

	/* Draw A=255 */J	rd`eat=200;J	S%tClip(sbraun,0l60�WiDT@/2,>0+(@EINHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeit; j++) {
		for (i=0; i<�UM_RANDOM; i += 2+ {
			roundedVectangheRGBA(screen, rx1[i], 2y1[i], rx1[i+1]l ry1Yi+1], 4, rr[i], rg[i], r`[i], 055+;		y
	}	tiee2-SDL_GetTicks(9;
	/* Resultw */
	SetCl�p(screen0,0,WIDTJ-1,HEIGLT-1);
	q`Rintf (titlete|t, "%>0&0pmr sec",1000.0*floa|)((�UM_RA�DOM/2)"rebeqt)/(f|oat)(time2-time1));
	strin'RGB� (screen, WIDTH/4-4jstrle.(titletey�(,30-4,titlete|t�255,255,255,255);

	/* Draw A=various */
	repeat=10;
	SetClip(scseen,WIDTH/2.60,WIDTH,60+(HEIGhT-80)/6);
	time1=SDL_GetTicks();
for (j=0; j<repeat;0j++) {
		for (i=0; i<NUM_RANDOM; i += 2) {
			roundedRdctangleRGBA(screen, rx2[i], sy1[i], rx2[i+1], ry1[i+1], 4, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	tmme2=SDL_GetTicks();

	/* Results */
	WetChip(screen,0,0,WIDVH-1,HEIGHT-1);
	sprintf (titletext, "%*0f pdr sec",1000.0*(float)((NUM_RANDOM/)*repeat)/(float)(time2-time1));
	stringROBA (screen, 3*WIDDH/4-4*strlen(titlet�xp),30-5,titletext,215,255,255,255);
}

void TesdRoundedFox(SDL_Surface *scraen)
{
	int y;
	char r,g,b;

/* Speade rando"points */
srand((ijt)timm(NULL));
InitRandnmQoints();
	'* Drcw A=�55 */
	SetClip(scz�enl0,60WIDTH/2,60k(HEIGHT-80�/2);
	fnr (i=0; i<NUM_RANDO	;$i$+= 4) z	rou�dedBoxRGBA(scbeen, r�1[i]� fy1[i], rz![i+1], ry1[i+1], 4,$rr[i], rg[i], sb[i], 255�9	}

	/* Draw A=v�rious(*/
	SetCli�screen,WI�TH/,60,WIDTH,60+(HEIGH\m80)/2)3
	for ii-0;!i<NUM_RCDOM� i +=049 {
		roundedBoxRGBA(screen, rx2[i], ry1[i], rx2[i+1], ry1[i+1], 4, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += 4) {
		roundedBoxRGBA(screen, rx2[i], ry2[i], rx2[i+1], ry2[i+1], 4, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += 4) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		roundedBoxRGBA(screen, rx1[i], ry2[i], rx1[i]+rr1[i], ry2[i]+rr2[i], 4, r, g, b, 255);
	}
}

void BenchmarkRoundedBox(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=200;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 4) {
			roundedBoxRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], 4, rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)((NUM_RANDOM/2)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 4) {
			roundedBoxRGBA(screen, rx2[i], ry1[i], rx2[i+1], ry1[i+1], 4, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)((NUM_RANDOM/4)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestBoxTwo(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		boxRGBA(screen, rx1[i], ry1[i], rx1[i]+1, ry1[i]+1, rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		boxRGBA(screen, rx2[i], ry1[i], rx2[i]+1, ry1[i]+1, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		boxRGBA(screen, rx2[i], ry2[i], rx2[i]+1, ry2[i]+1, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		boxRGBA(screen, rx1[i], ry2[i], rx1[i]+1, ry2[i]+1, r, g, b, 255);
	}
}

void BenchmarkBoxTwo(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=50;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			boxRGBA(screen, rx1[i], ry1[i], rx1[i]+1, ry1[i]+1, rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=50;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			boxRGBA(screen, rx2[i], ry1[i], rx2[i]+1, ry1[i]+1, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

}

void TestBox(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 2) {
		boxRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 2) {
		boxRGBA(screen, rx2[i], ry1[i], rx2[i+1], ry1[i+1], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += 2) {
		boxRGBA(screen, r|2[i], ry2[i], �x2[i+1]( vy2[a+1], rr[i]( r'[i], rr[i], rqYi]);}

	/*`Draw �oLortest */
	SetChip({creef,0,8 �(HEIGHT-80)/2,WADTH/2,HEIGHT);
	foR (i=0�"i<^UM_VCNDOm; i`+= 2) {		if (rx1[)] < (WIDTHo6)) ${
			r=255; g=0; b=0; 
		}(else if (rxq[i] <"(wIDTH/�9 ) {
			r=0; f�255; b=0; 
		}`else {
			r=0; g=p;0b=255; )	�
		boxRERA(scruen, rx�[iU, r}2[i], rx5[i];rr[i],`ry2[i]+rr2[i],0�, g, b, 255);
	}
}

VoiD RenchmarkBox(SDN_Supfabe *screen)
{
int i,�;
	in| repea|;	Uint32 timm1,�time�;	char titletext[256];

	/* Draw A=255 */
	repeat=10;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 2) {
			boxRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)((NUM_RANDOM/2)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255.255)+
	/* Dr�w A=vabiouS */
	rdpeat?1;�(SetClip(screen,WYD�H2<6,WKDTH,60+(HEIGLT-80)/2);
	time1=SDL_GetTicks()?
	for (j=0; hz�peat; j++) {
)	for (i=0; i<NUM_S�N@MI; a ?= 2)${�			boxRGBA(scregn, bx2[iM, ry1[i}, rx6[i+1], ry1[i+1U, rz[i], rg[i],(rb[i], �a[i�);�		}
	}
	time2=SDL_GetTycos()�

	/* ResUlts */
	SepCli`(screen,0-0,WIDTH�1,HEIGHT-1);
	sprintf ,tidletExt, "%.0f pdr sec",1000/0*(float)((NUM_RANDOM/2)*r%pect)/(floqt)(time2-time1));	stringRGBA (scree�, 3.WIDTH/4=4*strl�n(VitleText!,30-<,tipletext,255,255,255,255);

}

void TestLine(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 2) {
		lineRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 2) {
		lineRGBA(screen, rx2[i], ry1[i], rx2[i+1], ry1[i+1], rr[i], rfZi]$ rb[iM, pa[i]);
	}

)/* �zaw I=variouw */
	SetClip)sgr�e�,WIDVH/0.80+(HEIGHT-80�/2,WHFTH<HEIGHT);
For (i=0; I<NUM_RANDOM; i += ") {
		LiNeRG@�(screen,�rx2[i], ry3[i], rx2[i+1],ary2Yi+1_, rr[i], rgYi], rb[i], ra[i]);
	}

�/* Traw Colortgst */
	SetC|ir8scree~,0$80/(HDIGHT-80+/2,�IDTH.2,HEIGHT);
for (i=5;"i<NUM^RANDO�;0i +=`") {
		if (rx1K�] < (WIDTH/6))  {
	r=2559 g=0; b=03 J		} else if (rx!Zi] � (WILTH/3) ) {
			r=1; g=2u5; f=0: 
		} el{e�{
		r=0; g=0; b=255; 
		u
		lineRGA(screen, px1[i], ry2[i], rx1[i]+rr1[i], ry2[i]+rr2[i], r, g, b, 255);
	}
}

void BenchmarkLine(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=100;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 2) {
			lineRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext,0"%.0n per sgc",1000.0*(&doat)((N�M_RANDOM/r)*repeati-(float)(time2-time1));
	stringRWBA (screEn, WIDTH/4-4*s4rlen(tit�etexf),30-4,titletext,255�255,2=5,25�)+

	/. Fr!w Y=varigus"*/
	repeat=5;
	SetClip(screen,WMDTH/6,60�WYDTH$60+(HEIGHT-80)/2);
	time3=SDL_GetTiaks,);
	for (j=0; j<sepe!t; �++) {
		For (i=p� i<NUm_RAND_M; � += 2) {
			linm�GBA(skzeen, rx2Ki]. ry1[i], rx2[�;1], ry1[i+1], rr{i], rg[i]$ rb[i], ra[i]);
	(}
	}
	time2=WDL_GetTicks();

	/* Zesunts */	�etClit(scre-N,0,0 WIDTH-1,HEIGLT�1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)((NUM_RANDOM/2)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

}

void TestAALine(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 2) {
		aalineRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 2) {
		aalineRGBA(screen, rx2[i], ry1[i], rx2[i+1], ry1[i+1], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += 2) {
		aalineRGBA(screen, rx2[i], ry2[i], rx2[i+1], ry2[i+1], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += 2) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		aalineRGBA(screen, rx1[i], ry2[i], rx1[i]+rr1[i], ry2[i]+rr2[i], r, g, b, 255);
	}
}

void BenchmarkAALine(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=5;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 2) {
			aalineRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)((NUM_RANDOM/2)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 2) {
			aalineRGBA(screen, rx2[i], ry1[i], rx2[i+1], ry1[i+1], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)((NUM_RANDOM/2)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

}

void TestThickLine(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 5) {
		thickLineRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], lw[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i += 5) {
		thickLineRGBA(screen, rx2[i], ry1[i], rx2[i+1], ry1[i+1], lw[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += 5) {
		thickLineRGBA(screen, rx2[i], ry2[i], rx2[i+1], ry2[i+1], lw[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i += 5) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		thickLineRGBA(screen, rx1[i], ry2[i], rx1[i]+rr1[i], ry2[i]+rr2[i], lw[i], r, g, b, 255);
	}
}

void BenchmarkThickLine(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=10;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 5) {
			thickLineRGBA(screen, rx1[i], ry1[i], rx1[i+1], ry1[i+1], lw[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)((NUM_RANDOM/5)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 5) {
			thickLineRGBA(screen, rx2[i], ry1[i], rx2[i+1], ry1[i+1], lw[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)((NUM_RANDOM/5)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

}

void TestThickLineAccuracy(SDL_Surface *screen)
{
	int i;
	char r,g,b;
	int cx, cy;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	cx = WIDTH/4;
	cy = 60+(HEIGHT-80)/4;
	for (i=0; i<NUM_RANDOM; i += 10) {
		thickLineRGBA(screen, cx, cy, rx1[i], ry1[i], lw[i], rr[i], rg[i], rb[i], 255);
		pixelRGBA(screen, rx1[i], ry1[i], 255, 255, 255, 255);
	}
	pixelRGBA(screen, cx, cy, 255, 255, 255, 255);

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	cx = WIDTH/2 + WIDTH/4;
	cy = 60+(HEIGHT-80)/4;
	for (i=0; i<NUM_RANDOM; i += 10) {
		thickLineRGBA(screen, cx, cy, rx2[i], ry1[i], lw[i], rr[i], rg[i], rb[i], ra[i]);
		pixelRGBA(screen, rx2[i], ry1[i], 255, 255, 255, 255);
	}
	pixelRGBA(screen, cx, cy, 255, 255, 255, 255);

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	cx = WIDTH/2 + WIDTH/4;
	cy = 80 + (HEIGHT-80)/2 + (HEIGHT-80)/4;
	for (i=0; i<NUM_RANDOM; i += 10) {
		thickLineRGBA(screen, cx, cy, rx2[i], ry2[i], lw[i], rr[i], rg[i], rb[i], ra[i]);
		pixelRGBA(screen, rx2[i], ry2[i], 255, 255, 255, 255);
	}
	pixelRGBA(screen, cx, cy, 255, 255, 255, 255);

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	cx = WIDTH/4;
	cy = 80 + (HEIGHT-80)/2 + (HEIGHT-80)/4;
	for (i=0; i<NUM_RANDOM; i += 10) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		thickLineRGBA(screen, cx, cy, rx1[i], ry2[i], lw[i], r, g, b, 255);
		pixelRGBA(screen, rx1[i], ry2[i], 255, 255, 255, 255);
	}
	pixelRGBA(screen, cx, cy, 255, 255, 255, 255);
}

void TestCircle(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		circleRGBA(screen, rx1[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		circleRGBA(screen, rx2[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		circleRGBA(screen, rx2[i], ry2[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		circleRGBA(screen, rx1[i], ry2[i], rr1[i], r, g, b, 255);
	}
}

void BenchmarkCircle(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			circleRGBA(screen, rx1[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			circleRGBA(screen, rx2[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestAACircle(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		aacircleRGBA(screen, rx1[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		aacircleRGBA(screen, rx2[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		aacircleRGBA(screen, rx2[i], ry2[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		aacircleRGBA(screen, rx1[i], ry2[i], rr1[i], r, g, b, 255);
	}
}

void BenchmarkAACircle(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			aacircleRGBA(screen, rx1[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			aacircleRGBA(screen, rx2[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestFilledCircle(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		filledCircleRGBA(screen, rx1[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		filledCircleRGBA(screen, rx2[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		filledCircleRGBA(screen, rx2[i], ry2[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		filledCircleRGBA(screen, rx1[i], ry2[i], rr1[i], r, g, b, 255);
	}
}

void BenchmarkFilledCircle(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			filledCircleRGBA(screen, rx1[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			filledCircleRGBA(screen, rx2[i], ry1[i], rr1[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestEllipse(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		ellipseRGBA(screen, rx1[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		ellipseRGBA(screen, rx2[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		ellipseRGBA(screen, rx2[i], ry2[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		ellipseRGBA(screen, rx1[i], ry2[i], rr1[i], rr2[i], r, g, b, 255);
	}
}

void BenchmarkEllipse(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			ellipseRGBA(screen, rx1[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			ellipseRGBA(screen, rx2[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestAAEllipse(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		aaellipseRGBA(screen, rx1[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		aaellipseRGBA(screen, rx2[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		aaellipseRGBA(screen, rx2[i], ry2[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		aaellipseRGBA(screen, rx1[i], ry2[i], rr1[i], rr2[i], r, g, b, 255);
	}
}

void BenchmarkAAEllipse(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			ellipseRGBA(screen, rx1[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			aaellipseRGBA(screen, rx2[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestFilledEllipse(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		filledEllipseRGBA(screen, rx1[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		filledEllipseRGBA(screen, rx2[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		filledEllipseRGBA(screen, rx2[i], ry2[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		filledEllipseRGBA(screen, rx1[i], ry2[i], rr1[i], rr2[i], r, g, b, 255);
	}
}

void BenchmarkFilledEllipse(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			filledEllipseRGBA(screen, rx1[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			filledEllipseRGBA(screen, rx2[i], ry1[i], rr1[i], rr2[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestArc(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		arcRGBA(screen, rx1[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		arcRGBA(screen, rx2[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		arcRGBA(screen, rx2[i], ry2[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		arcRGBA(screen, rx1[i], ry2[i], rr1[i], a1[i], a2[i], r, g, b, 255);
	}
}

void BenchmarkArc(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=50;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			arcRGBA(screen, rx1[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			arcRGBA(screen, rx2[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestPie(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		pieRGBA(screen, rx1[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		pieRGBA(screen, rx2[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		pieRGBA(screen, rx2[i], ry2[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		pieRGBA(screen, rx1[i], ry2[i], rr1[i], a1[i], a2[i], r, g, b, 255);
	}
}

void BenchmarkPie(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			pieRGBA(screen, rx1[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			pieRGBA(screen, rx2[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestFilledPie(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		filledPieRGBA(screen, rx1[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		filledPieRGBA(screen, rx2[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		filledPieRGBA(screen, rx2[i], ry2[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		filledPieRGBA(screen, rx1[i], ry2[i], rr1[i], a1[i], a2[i], r, g, b, 255);
	}
}

void BenchmarkFilledPie(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			filledPieRGBA(screen, rx1[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			filledPieRGBA(screen, rx2[i], ry1[i], rr1[i], a1[i], a2[i], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestTrigon(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		trigonRGBA(screen, tx1[i][0], ty1[i][0], tx1[i][1], ty1[i][1], tx1[i][2], ty1[i][2], rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		trigonRGBA(screen, tx2[i][0], ty1[i][0], tx2[i][1], ty1[i][1], tx2[i][2], ty1[i][2], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		trigonRGBA(screen, tx2[i][0], ty2[i][0], tx2[i][1], ty2[i][1], tx2[i][2], ty2[i][2], rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		trigonRGBA(screen, tx1[i][0], ty2[i][0], tx1[i][1], ty2[i][1], tx1[i][2], ty2[i][2], r, g, b, 255);
	}
}

void BenchmarkTrigon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	repeat=50;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			trigonRGBA(screen, tx1[i][0], ty1[i][0], tx1[i][1], ty1[i][1], tx1[i][2], ty1[i][2], rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			trigonRGBA(screen, tx2[i][0], ty1[i][0], tx2[i][1], ty1[i][1], tx2[i][2], ty1[i][2], rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestTexturedTrigon(SDL_Surface *screen)
{
	int i;
	char r,g,b;
	SDL_Surface *texture;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Create texture */
	texture = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_HWSURFACE | SDL_SRCALPHA,
		2, 2, 32,
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	/* Draw A=255 */
	boxRGBA(texture,0,0,1,1,255,255,255,255); 
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		texturedPolygon(screen, &tx1[i][0], &ty1[i][0], 3, texture, 0, 0);
	}

	/* Draw A=various */
	boxRGBA(texture,0,0,1,1,255,255,255,ra[i]); 
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		texturedPolygon(screen, &tx2[i][0], &ty1[i][0], 3, texture, 0, 0);
	}

	/* Draw A=various */
	boxRGBA(texture,0,0,1,1,255,255,255,ra[i]); 
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		texturedPolygon(screen, &tx2[i][0], &ty2[i][0], 3, texture, 0, 0);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		boxRGBA(texture,0,0,1,1,r,g,b,255); 
		texturedPolygon(screen, &tx1[i][0], &ty2[i][0], 3, texture, 0, 0);
	}

	SDL_FreeSurface(texture);
}

void BenchmarkTexturedTrigon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];
	SDL_Surface *texture;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Create texture */
	texture = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_HWSURFACE | SDL_SRCALPHA,
		2, 2, 32,
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	/* Draw A=255 */
	boxRGBA(texture,0,0,1,1,255,255,255,255); 
	repeat=50;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			texturedPolygon(screen, &tx1[i][0], &ty1[i][0], 3, texture, 0, 0);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=255 */
	boxRGBA(texture,0,0,1,1,255,255,255,255); 
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			texturedPolygon(screen, &tx2[i][0], &ty1[i][0], 3, texture, 0, 0);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	SDL_FreeSurface(texture);
}

void TestSquarePolygon(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		polygonRGBA(screen, &sx1[i][0], &sy1[i][0], 3, rr[i], rg[i], rb[i], 255);
		polygonRGBA(screen, &sx1[i][3], &sy1[i][3], 3, rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		polygonRGBA(screen, &sx2[i][0], &sy1[i][0], 3, rr[i], rg[i], rb[i], ra[i]);
		polygonRGBA(screen, &sx2[i][3], &sy1[i][3], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		polygonRGBA(screen, &sx2[i][0], &sy2[i][0], 3, rr[i], rg[i], rb[i], ra[i]);
		polygonRGBA(screen, &sx2[i][3], &sy2[i][3], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		polygonRGBA(screen, &sx1[i][0], &sy2[i][0], 3, r, g, b, 255);
		polygonRGBA(screen, &sx1[i][3], &sy2[i][3], 3, r, g, b, 255);
	}
}

void BenchmarkSquarePolygon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	repeat=50;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			polygonRGBA(screen, &sx1[i][0], &sy1[i][0], 6, rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			polygonRGBA(screen, &sx2[i][0], &sy1[i][0], 6, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestPolygon(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		polygonRGBA(screen, &rx1[i], &ry1[i], 3, rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		polygonRGBA(screen, &rx2[i], &ry1[i], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		polygonRGBA(screen, &rx2[i], &ry2[i], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		rx1[i+1]=rx1[i]+rr1[i];
		rx1[i+2]=rx1[i];
		ry2[i+1]=ry2[i];
		ry2[i+2]=ry2[i]+rr2[i];
		polygonRGBA(screen, &rx1[i], &ry2[i], 3, r, g, b, 255);
	}
}

void BenchmarkPolygon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	repeat=50;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 3) {
			polygonRGBA(screen, &rx1[i], &ry1[i], 3, rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 3) {
			polygonRGBA(screen, &rx2[i], &ry1[i], 3, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestAAPolygon(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		aapolygonRGBA(screen, &rx1[i], &ry1[i], 3, rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		aapolygonRGBA(screen, &rx2[i], &ry1[i], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		aapolygonRGBA(screen, &rx2[i], &ry2[i], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		rx1[i+1]=rx1[i]+rr1[i];
		rx1[i+2]=rx1[i];
		ry2[i+1]=ry2[i];
		ry2[i+2]=ry2[i]+rr2[i];
		aapolygonRGBA(screen, &rx1[i], &ry2[i], 3, r, g, b, 255);
	}
}

void BenchmarkAAPolygon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	repeat=5;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 3) {
			aapolygonRGBA(screen, &rx1[i], &ry1[i], 3, rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=2;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 3) {
			aapolygonRGBA(screen, &rx2[i], &ry1[i], 3, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}


void TestFilledPolygon(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		filledPolygonRGBA(screen, &rx1[i], &ry1[i], 3, rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		filledPolygonRGBA(screen, &rx2[i], &ry1[i], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		filledPolygonRGBA(screen, &rx2[i], &ry2[i], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		rx1[i+1]=rx1[i]+rr1[i];
		rx1[i+2]=rx1[i];
		ry2[i+1]=ry2[i];
		ry2[i+2]=ry2[i]+rr2[i];
		filledPolygonRGBA(screen, &rx1[i], &ry2[i], 3, r, g, b, 255);
	}
}

void BenchmarkFilledPolygon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 3) {
			filledPolygonRGBA(screen, &rx1[i], &ry1[i], 3, rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 3) {
			filledPolygonRGBA(screen, &rx2[i], &ry1[i], 3, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestFilledSquarePolygon(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		filledPolygonRGBA(screen, &sx1[i][0], &sy1[i][0], 3, rr[i], rg[i], rb[i], 255);
		filledPolygonRGBA(screen, &sx1[i][3], &sy1[i][3], 3, rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		filledPolygonRGBA(screen, &sx2[i][0], &sy1[i][0], 3, rr[i], rg[i], rb[i], ra[i]);
		filledPolygonRGBA(screen, &sx2[i][3], &sy1[i][3], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		filledPolygonRGBA(screen, &sx2[i][0], &sy2[i][0], 3, rr[i], rg[i], rb[i], ra[i]);
		filledPolygonRGBA(screen, &sx2[i][3], &sy2[i][3], 3, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		filledPolygonRGBA(screen, &sx1[i][0], &sy2[i][0], 3, r, g, b, 255);
		filledPolygonRGBA(screen, &sx1[i][3], &sy2[i][3], 3, r, g, b, 255);
	}
}

void BenchmarkFilledSquarePolygon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	repeat=50;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			filledPolygonRGBA(screen, &sx1[i][0], &sy1[i][0], 3, rr[i], rg[i], rb[i], 255);
			filledPolygonRGBA(screen, &sx1[i][3], &sy1[i][3], 3, rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			filledPolygonRGBA(screen, &sx2[i][0], &sy1[i][0], 3, rr[i], rg[i], rb[i], ra[i]);
			filledPolygonRGBA(screen, &sx2[i][3], &sy1[i][3], 3, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

void TestTexturedPolygon(SDL_Surface *screen)
{
	int i;
	SDL_Surface *texture;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Load texture surface */
	texture = SDL_LoadBMP("texture.bmp");

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	SDL_SetAlpha(texture, SDL_SRCALPHA, 255);
	for (i=0; i<(NUM_RANDOM/2-3); i += 3) {
		SDL_SetAlpha(texture, SDL_SRCALPHA, 255);
		texturedPolygon(screen, &rx1[i], &ry1[i], 3, texture, rr1[i], rr2[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM/2-3); i += 3) {
		SDL_SetAlpha(texture, SDL_SRCALPHA, ra[i]);
		texturedPolygon(screen, &rx2[i], &ry1[i], 3, texture, rr1[i], rr2[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<(NUM_RANDOM/2-3); i += 3) {
		SDL_SetAlpha(texture, SDL_SRCALPHA, ra[i]);
		texturedPolygon(screen, &rx2[i], &ry2[i], 3, texture, rr1[i], rr2[i]);
	}

	/* Draw Colortest */
	SDL_SetAlpha(texture, SDL_SRCALPHA, 255);
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<(NUM_RANDOM/2-3); i += 3) {
		rx1[i+1]=rx1[i]+rr1[i];
		rx1[i+2]=rx1[i];
		ry2[i+1]=ry2[i];
		ry2[i+2]=ry2[i]+rr2[i];
		texturedPolygon(screen, &rx1[i], &ry2[i], 3, texture, 0, 0);
	}

	SDL_FreeSurface(texture);
}

void BenchmarkTexturedPolygon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];
	SDL_Surface *texture;

	/* Load texture surface */
	texture = SDL_LoadBMP("texture.bmp");

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	repeat=20;
	SDL_SetAlpha(texture, SDL_SRCALPHA, 255);
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<(NUM_RANDOM/2-3); i += 3) {
			texturedPolygon(screen, &rx1[i], &ry1[i], 3, texture, rr1[i], rr2[i]);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM/2-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=5;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<(NUM_RANDOM/2-3); i += 3) {
			SDL_SetAlpha(texture, SDL_SRCALPHA, ra[i]);
			texturedPolygon(screen, &rx2[i], &ry1[i], 3, texture, rr1[i], rr2[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM/2-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	SDL_FreeSurface(texture);
}

void TestTexturedSquarePolygon(SDL_Surface *screen)
{
	int i;
	char r,g,b;
	SDL_Surface *texture;

	/* Load texture surface */
	texture = SDL_LoadBMP("texture.bmp");

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SDL_SetAlpha(texture, SDL_SRCALPHA, 255);
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		texturedPolygon(screen, &sx1[i][0], &sy1[i][0], 3, texture, rr1[i], rr2[i]);
		texturedPolygon(screen, &sx1[i][3], &sy1[i][3], 3, texture, rr1[i], rr2[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<NUM_RANDOM; i++) {
		SDL_SetAlpha(texture, SDL_SRCALPHA, ra[i]);
		texturedPolygon(screen, &sx2[i][0], &sy1[i][0], 3, texture, rr1[i], rr2[i]);
		texturedPolygon(screen, &sx2[i][3], &sy1[i][3], 3, texture, rr1[i], rr2[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		SDL_SetAlpha(texture, SDL_SRCALPHA, ra[i]);
		texturedPolygon(screen, &sx2[i][0], &sy2[i][0], 3, texture, rr1[i], rr2[i]);
		texturedPolygon(screen, &sx2[i][3], &sy2[i][3], 3, texture, rr1[i], rr2[i]);
	}

	/* Create texture */
	SDL_FreeSurface(texture);
	texture = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_HWSURFACE | SDL_SRCALPHA,
		2, 2, 32,
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<NUM_RANDOM; i++) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		boxRGBA(texture,0,0,1,1,r,g,b,255); 
		texturedPolygon(screen, &sx1[i][0], &sy2[i][0], 3, texture, 0, 0);
		texturedPolygon(screen, &sx1[i][3], &sy2[i][3], 3, texture, 0, 0);
	}

	SDL_FreeSurface(texture);
}

void BenchmarkTexturedSquarePolygon(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];
	SDL_Surface *texture;

	/* Load texture surface */
	texture = SDL_LoadBMP("texture.bmp");

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw shift */
	repeat=50;
	SDL_SetAlpha(texture, SDL_SRCALPHA, 255);
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			texturedPolygon(screen, &sx1[i][0], &sy1[i][0], 3, texture, rr1[i], rr2[i]);
			texturedPolygon(screen, &sx1[i][3], &sy1[i][3], 3, texture, rr1[i], rr2[i]);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw no shift */
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i++) {
			texturedPolygon(screen, &sx2[i][0], &sy1[i][0], 3, texture, 0, 0);
			texturedPolygon(screen, &sx2[i][3], &sy1[i][3], 3, texture, 0, 0);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(NUM_RANDOM*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	SDL_FreeSurface(texture);
}

void TestBezier(SDL_Surface *screen)
{
	int i;
	char r,g,b;

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		bezierRGBA(screen, &rx1[i], &ry1[i], 3, 100, rr[i], rg[i], rb[i], 255);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		bezierRGBA(screen, &rx2[i], &ry1[i], 3, 100, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw A=various */
	SetClip(screen,WIDTH/2,80+(HEIGHT-80)/2,WIDTH,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		bezierRGBA(screen, &rx2[i], &ry2[i], 3, 100, rr[i], rg[i], rb[i], ra[i]);
	}

	/* Draw Colortest */
	SetClip(screen,0,80+(HEIGHT-80)/2,WIDTH/2,HEIGHT);
	for (i=0; i<(NUM_RANDOM-3); i += 3) {
		if (rx1[i] < (WIDTH/6))  {
			r=255; g=0; b=0; 
		} else if (rx1[i] < (WIDTH/3) ) {
			r=0; g=255; b=0; 
		} else {
			r=0; g=0; b=255; 
		}
		rx1[i+1]=rx1[i]+rr1[i];
		rx1[i+2]=rx1[i];
		ry2[i+1]=ry2[i];
		ry2[i+2]=ry2[i]+rr2[i];
		bezierRGBA(screen, &rx1[i], &ry2[i], 3, 100, r, g, b, 255);
	}
}

void BenchmarkBezier(SDL_Surface *screen)
{
	int i,j;
	int repeat;
	Uint32 time1, time2;
	char titletext[256];

	/* Create random points */
	srand((int)time(NULL));
	InitRandomPoints();

	/* Draw A=255 */
	repeat=20;
	SetClip(screen,0,60,WIDTH/2,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 3) {
			bezierRGBA(screen, &rx1[i], &ry1[i], 3, 100, rr[i], rg[i], rb[i], 255);
		}
	}
	time2=SDL_GetTicks();
	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);

	/* Draw A=various */
	repeat=10;
	SetClip(screen,WIDTH/2,60,WIDTH,60+(HEIGHT-80)/2);
	time1=SDL_GetTicks();
	for (j=0; j<repeat; j++) {
		for (i=0; i<NUM_RANDOM; i += 3) {
			bezierRGBA(screen, &rx2[i], &ry1[i], 3, 100, rr[i], rg[i], rb[i], ra[i]);
		}
	}
	time2=SDL_GetTicks();

	/* Results */
	SetClip(screen,0,0,WIDTH-1,HEIGHT-1);
	sprintf (titletext, "%.0f per sec",1000.0*(float)(((NUM_RANDOM-3)/3)*repeat)/(float)(time2-time1));
	stringRGBA (screen, 3*WIDTH/4-4*strlen(titletext),30-4,titletext,255,255,255,255);
}

/* ======== Main Program ======= */

int main(int argc, char *argv[])
{
	const SDL_VideoInfo *info;
	SDL_Surface *screen;
	Uint8  video_bpp;
	Uint32 videoflags;
	int done;
	SDL_Event event;
	int oldprim, curprim;
	char title[64];

	/* Generate title string */
	sprintf (title,"TestGfxPrimitives - v%i.%i.%i",SDL_GFXPRIMITIVES_MAJOR, SDL_GFXPRIMITIVES_MINOR, SDL_GFXPRIMITIVES_MICRO);

	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	/* Alpha blending doesn't work well at 8-bit color */
	info = SDL_GetVideoInfo();
	if ( info->vfmt->BitsPerPixel > 8 ) {
		video_bpp = info->vfmt->BitsPerPixel;
	} else {
		video_bpp = 16;
	}
	videoflags = SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE;
	while ( argc > 1 ) {
		--argc;
		if ( strcmp(argv[argc-1], "-bpp") == 0 ) {
			video_bpp = atoi(argv[argc]);
			--argc;
		} else
			if ( strcmp(argv[argc], "-hw") == 0 ) {
				videoflags |= SDL_HWSURFACE;
			} else
				if ( strcmp(argv[argc], "-warp") == 0 ) {
					videoflags |= SDL_HWPALETTE;
				} else
					if ( strcmp(argv[argc], "-fullscreen") == 0 ) {
						videoflags |= SDL_FULLSCREEN;
					} else {
						fprintf(stderr, 
							"Usage: %s [-bpp N] [-warp] [-hw] [-fullscreen]\n",
							argv[0]);
						exit(1);
					}
	}

	/* Set video mode */
	if ( (screen=SDL_SetVideoMode(WIDTH,HEIGHT,video_bpp,videoflags)) == NULL ) {
		fprintf(stderr, "Couldn't set %ix%i %i bpp video mode: %s\n",WIDTH,HEIGHT,video_bpp,SDL_GetError());
		exit(2);
	}

	/* Use alpha blending */
	SDL_SetAlpha(screen, SDL_SRCALPHA, 0);

	/* Set title for window */
	SDL_WM_SetCaption(title,title);

	/* Wait for a keystroke */
	done = 0;
	oldprim = 0;
	curprim = 1;
	while ( !done ) {

		/* Draw on screen if primitive changes */
		if (curprim != oldprim) {

			ClearScreen(screen, "TestGfxPrimitives");

			/* Draw according to curprim setting */
			switch (curprim) {

				/* Pixels */
			 case 1:
				 ClearScreen(screen, "Pixel");
				 TestPixel(screen);
				 BenchmarkPixel(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* Horizontal Lines */
			 case 2:
				 ClearScreen(screen, "Hline");
				 TestHline(screen);
				 BenchmarkHline(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* Vertical Lines */
			 case 3:
				 ClearScreen(screen, "Vline");
				 TestVline(screen);
				 BenchmarkVline(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* Rectangles */
			 case 4:
				 ClearScreen(screen, "Rectangle");
				 TestRectangle(screen);
				 BenchmarkRectangle(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* --- Box */
			 case 5:
				 ClearScreen(screen, "Box");
				 TestBox(screen);
				 BenchmarkBox(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- 2x2 Box */
			 case 6:
				 ClearScreen(screen, "2x2 Box");
				 TestBoxTwo(screen);
				 BenchmarkBoxTwo(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- Lines */
			 case 7:
				 ClearScreen(screen, "Line");
				 TestLine(screen);
				 BenchmarkLine(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* --- AA Line */
			 case 8:
				 ClearScreen(screen, "Anti-Aliased Line");
				 TestAALine(screen);
				 BenchmarkAALine(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* --- Circle */
			 case 9:
				 ClearScreen(screen, "Circle");
				 TestCircle(screen);
				 BenchmarkCircle(screen);			 
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* --- AA Circle */
			 case 10:
				 ClearScreen(screen, "AA Circle");
				 TestAACircle(screen);
				 BenchmarkAACircle(screen);			 
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* --- Filled Circle */
			 case 11:
				 ClearScreen(screen, "Filled Circle");
				 TestFilledCircle(screen);
				 BenchmarkFilledCircle(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* --- Ellipse */
			 case 12:
				 ClearScreen(screen, "Ellipse");
				 TestEllipse(screen);
				 BenchmarkEllipse(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* --- AA Ellipse */
			 case 13:
				 ClearScreen(screen, "AA Ellipse");
				 TestAAEllipse(screen);
				 BenchmarkAAEllipse(screen);
				 /* Next primitive */
				 oldprim=curprim; 
				 break;

				 /* --- Filled Ellipse */
			 case 14:
				 ClearScreen(screen, "Filled Ellipse");
				 TestFilledEllipse(screen);
				 BenchmarkFilledEllipse(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- Arc */
			 case 15:
				 ClearScreen(screen, "Arc");
				 TestArc(screen);
				 BenchmarkArc(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- Pie */
			 case 16:
				 ClearScreen(screen, "Pie");
				 TestPie(screen);
				 BenchmarkPie(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- Filled Pie */
			 case 17:
				 ClearScreen(screen, "Filled Pie");
				 TestFilledPie(screen);
				 BenchmarkFilledPie(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- 3-Pixel Trigon */
			 case 18:
				 ClearScreen(screen, "5-Pixel Trigon");
				 TestTrigon(screen);
				 BenchmarkTrigon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- 3-Pixel Textured Trigon */
			 case 19:
				 ClearScreen(screen, "5-Pixel Textured Trigon");
				 TestTexturedTrigon(screen);
				 BenchmarkTexturedTrigon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- Square Polygon */
			 case 20:
				 ClearScreen(screen, "Square Polygon");
				 TestSquarePolygon(screen);
				 BenchmarkSquarePolygon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- Polygon */
			 case 21:
				 ClearScreen(screen, "Polygon");
				 TestPolygon(screen);
				 BenchmarkPolygon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- AA-Polygon */
			 case 22:
				 ClearScreen(screen, "AA-Polygon");
				 TestAAPolygon(screen);
				 BenchmarkAAPolygon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Filled Polygon */ 
			 case 23:
				 ClearScreen(screen, "Filled Polygon");
				 TestFilledPolygon(screen);
				 BenchmarkFilledPolygon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Filled Square Polygon */ 
			 case 24:
				 ClearScreen(screen, "Square from 2 Filled Polygons");
				 TestFilledSquarePolygon(screen);
				 BenchmarkFilledSquarePolygon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Textured Polygon */ 
			 case 25:
				 ClearScreen(screen, "Textured Polygon");
				 TestTexturedPolygon(screen);
				 BenchmarkTexturedPolygon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Textured Square Polygon */ 
			 case 26:
				 ClearScreen(screen, "Textured Square Polygon");
				 TestTexturedSquarePolygon(screen);
				 BenchmarkTexturedSquarePolygon(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Bezier Curve */ 
			 case 27:
				 ClearScreen(screen, "Bezier Curve");
				 TestBezier(screen);
				 BenchmarkBezier(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Rounded Rectangle */ 
			 case 28:
				 ClearScreen(screen, "Rounded Rectangle");
				 TestRoundedRectangle(screen);
				 BenchmarkRoundedRectangle(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Rounded Box */ 
			 case 29:
				 ClearScreen(screen, "Rounded Box");
				 TestRoundedBox(screen);
				 BenchmarkRoundedBox(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Thick Line */ 
			 case 30:
				 ClearScreen(screen, "Thick Line");
				 TestThickLine(screen);
				 BenchmarkThickLine(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* ---- Thick Line (accuracy) */ 
			 case 31:
				 ClearScreen(screen, "Thick Line (Accuracy)");
				 TestThickLineAccuracy(screen);
				 /* Next primitive */ 			  
				 oldprim=curprim; 
				 break;

				 /* --- Wrap start*/
			 case 0:
				 oldprim=0;
				 curprim=31;
				 break;

				 /* --- Wrap end */ 
			 default:
				 oldprim=0;
				 curprim=1;
				 break;
			}

			/* Show */
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Flip(screen);
		}

		/* Slow down polling */
		SDL_Delay(100);

		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
				case SDL_MOUSEBUTTONDOWN:
					if ( event.button.button == SDL_BUTTON_LEFT ) {
						/* Switch to next graphics */
						curprim++;
					} else if ( event.button.button == SDL_BUTTON_RIGHT ) {
						/* Switch to prev graphics */
						curprim--;
					}
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}
	}

	return(0);
}
