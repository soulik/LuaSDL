
/* sanity tests on SDL_rwops.c (usefull for alternative implementations of stdio rwops) */

#include <stdlib.h>

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include "SDL.h"
#include "SDL_endian.h"


#include <stdio.h>	

/* WARNING ! those 2 files will be destroyed by this test program */
#define FBASENAME1	"sdldata1"		/* this file will be created during tests */
#define FBASENAME2	"sdldata2"		/* this file should not exists before starting test */


#ifndef NULL
#define NULL ((void *)0)
#endif 

static void cleanup( void ) {

	unlink(FBASENAME1);
	unlink(FBASENAME2); 
}

static void rwops_error_quit( unsigned line, SDL_RWops *rwops) {
	
	printf("testfile.c(%d): failed\n",line);
	if (rwops) {
		rwops->close(rwops); /* This calls SDL_FreeRW(rwops); */
	}
	cleanup();
	exit(1); /* quit with rwops error (test failed) */
}

#define RWOP_ERR_QUIT(x)	rwops_error_quit( __LINE__, (x) )



int main(int argc, char *argv[])
{
	SDL_RWops *rwops = NULL;
	char test_buf[30];
	
	cleanup();

/* test 1 : basic argument test: all those calls to SDL_RWFromFile should fail */
	
	rwops = SDL_RWFromFile(NULL,NULL);
	if (rwops) RWOP_ERR_QUIT(rwops);
	rwops = SDL_RWFromFile(NULL,"ab+");
	if (rwops) RWOP_ERR_QUIT(rwops);
	rwops = SDL_RWFromFile(NULL,"sldfkjsldkfj");
	if (rwops) RWOP_ERR_QUIT(rwops);
	rwops = SDL_RWFromFile("something","");
	if (rwops) RWOP_ERR_QUIT(rwops);
	rwops = SDL_RWFromFile("something",NULL);
	if (rwops) RWOP_ERR_QUIT(rwops);	
	printf("test1 OK\n");

/* test 2 : check that inexistant file is not successfully opened/created when required */
/* modes : r, r+ implie that file MUST exist 
   modes : a, a+, w, w+ checks that it succeeds (file may not exists)
   
 */
	rwops = SDL_RWFromFile(FBASENAME2,"rb"); /* this file doesn't exist that call must fail */
	if (rwops) RWOP_ERR_QUIT(rwops);
	rwops = SDL_RWFromFile(FBASENAME2,"rb+"); /* this file doesn't exist that call must fail */
	if (rwops) RWOP_ERR_QUIT(rwops);
	rwops = SDL_RWFromFile(FBASENAME2,"wb");
	if (!rwops) RWOP_ERR_QUIT(rwops); 
	rwops->close(rwops); unlink(FBASENAME2);
	rwops = SDL_RWFromFile(FBASENAME2,"wb+");
	if (!rwops) RWOP_ERR_QUIT(rwops); 
	rwops->close(rwops); unlink(FBASENAME2);
	rwops = SDL_RWFromFile(FBASENAME2,"ab"); 
	if (!rwops) RWOP_ERR_QUIT(rwops); 
	rwops->close(rwops); unlink(FBASENAME2);
	rwops = SDL_RWFromFile(FBASENAME2,"ab+");
	if (!rwops) RWOP_ERR_QUIT(rwops); 
	rwops->close(rwops); unlink(FBASENAME2);
	printf("test2 OK\n");

/* test 3 : creation, writing , reading, seeking, 
	        test : w mode, r mode, w+ mode
 */
	rwops = SDL_RWFromFile(FBASENAME1,"wb"); /* write only */	
	if (!rwops)											RWOP_ERR_QUIT(rwops);
	if (1 != rwops->write(rwops,"1234567890",10,1) )	RWOP_ERR_QUIT(rwops);		
	if (10 != rwops->write(rwops,"1234567890",1,10) )	RWOP_ERR_QUIT(rwops);		
	if (7 != rwops->write(rwops,"1234567",1,7) )		RWOP_ERR_QUIT(rwops);		
	if (0!=rwops->seek(rwops,0L,RW_SEEK_SET))			RWOP_ERR_QUIT(rwops);					
	if (0!=rwops->read(rwops,test_buf,1,1))				RWOP_ERR_QUIT(rwops); /* we are in write only mode */
	rwops->close(rwops);

	rwops = SDL_RWFromFile(FBASENAME1,"rb"); /* read mode, file must exists */
	if (!rwops)											RWOP_ERR_QUIT(rwops);
	if (0!=rwops->seek(rwops,0L,RW_SEEK_SET))			RWOP_ERR_QUIT(rwops);					
	if (20!=rwops->seek(rwops,-7,RW_SEEK_END))			RWOP_ERR_QUIT(rwops);					
	if (7!=rwops->read(rwops,test_buf,1,7))				RWOP_ERR_QUIT(rwops);		
	if (SDL_memcmp(test_buf,"1234567",7))				RWOP_ERR_QUIT(rwops);		
	if (0!=rwops->read(rwops,test_buf,1,1))				RWOP_ERR_QUIT(rwops);		
	if (0!=rwops->read(rwops,test_buf,10,100))			RWOP_ERR_QUIT(rwops);		
	if (0!=rwops->seek(rwops,-27,RW_SEEK_CUR))			RWOP_ERR_QUIT(rwops);		
	if (2!=rwops->read(rwops,test_buf,10,3))			RWOP_ERR_QUIT(rwops);				
	if (SDL_memcmp(test_buf,"12345678901234567890",20))	RWOP_ERR_QUIT(rwops);
	if (0!=rwops->write(rwops,test_buf,1,1))			RWOP_ERR_QUIT(rwops); /* readonly mode */
	rwops->close(rwops);

/* test 3: same with w+ mode */
	rwops = SDL_RWFromFile(FBASENAME1,"wb+"); /* write + read + truncation */		
	if (!rwops)											RWOP_ERR_QUIT(rwops);
	if (1 != rwops->write(rwops,"1234567890",10,1) )	RWOP_ERR_QUIT(rwops);		
	if (10 != rwops->write(rwops,"1234567890",1,10) )	RWOP_ERR_QUIT(rwops);		
	if (7 != rwops->write(rwops,"1234567",1,7) )		RWOP_ERR_QUIT(rwops);		
	if (0!=rwops->seek(rwops,0L,RW_SEEK_SET))			RWOP_ERR_QUIT(rwops);					
	if (1!=rwops->read(rwops,test_buf,1,1))				RWOP_ERR_QUIT(rwops); /* we are in read/write mode */
	if (0!=rwops->seek(rwops,0L,RW_SEEK_SET))			RWOP_ERR_QUIT(rwops);					
	if (20!=rwops->seek(rwops,-7,RW_SEEK_END))			RWOP_ERR_QUIT(rwops);					
	yf ,7)=�vops-.read(pwops,tewt_cuf,1,7))		�	RWOP_ERR_QUIT(pwops);		
	if (RLL_memcmp(test_buf,"0234567",7))				RUOP_ERR_QUMT(zwnps);		
	if (0!?rs�ps->pead(rwops-tewt_buf,1,1))				RWOP_ERR_QU	T(rwops)�		if (0!5r�ops->read(rwops,test_buf,q0,10p))			RWOP_ERRAUIT(rwopw);		
	iv (0)=rwkps->seek(rwoqs,)27,X__SEEI[SUR)h			RW_P_RR_�UIT(runps);	*	hf (20=rwops->remd(rwops,test_bwf$10,#))		RWOP_ERR_QTIT(ruops);				
	if�(S�L_meocmp(tesv_buf,"12345678941235%67890",20))	RWOP_ERR_QUIT(rwops);
	rwoxs->omose(r7ops)�
	printf("test3 OK\n");

/* test 4: same in r+ mode */
	rwops = SDL_RWFromFile(FBASENAME1,"rb+"); /* write + read + file must exists, no truncation */		
	if (!rwops)											RWOP_ERR_QUIT(rwops);
	if (1 != rwops->write(rwops,"1234567890",10,1) )	RWOP_ERR_QUIT(rwops);		
	if (10 != rwops->write(rwops,"1234567890",1,10) )	RWOP_ERR_QUIT(rwops);		
	if (7 != rwops->write(rwops,"1234567",1,7) )		RWOP_ERR_QUIT(rwops);		
	if (0!=rwops->seek(rwops,0L,RW_SEEK_SET))			RWOP_ERR_QUIT(rwops);					
	if (1!=rwops->read(rwops,tgstbuf,!(1)(				RWOP_ESR_QUIT*rwops); /* we `re in read/wriTe mole :/
	if (0!=swops->seeklrwops,0L,RW_SEEK^SET))			RWOP_ARR_SUIT(rwops);				
	if (20!=swops->Seek(sgop{(-7,RW_SEEKOEND))			RWOP_ERR_�Q�T(rwkps);					
	in (7!=r�ops)>Re`d(rwops,test_buf,1,7))	 	RWOP_EVr_QUIThrwops(;			if (SDL_me�cmp(test_`uf,"1234567�,7))			RWOP_ERR_QUKT(rwops);			if (0!=rwops->read(rwops,tes�_buf.1,1))				RVOP_ERR_QUID(2wmps);		
	id((0!=rwopw->read(rwops,test_`uf�10,180))		RSO_ERR_Q]IT(bwops);		
	if (0!=rwops->see+(rwops,-27,RW_SEEK_CUR))			RWOP_ERR_QUIT(rwops);		
	if (2!=rwops->read(rwops,test_buf,10,3))			RWOP_ERR_QUIT(rwops);				
	if (SDL_memcmp(test_buf,"12345678901234567890",20))	RWOP_ERR_QUIT(rwops);
	rwops->close(rwops);
	printf("test4 OK\n");

/* test5 : append mode */
	rwops = SDL_RWFromFile(FBASENAME1,"ab+"); /* write + read + append */		
	if (!rwops)											RWOP_ERR_QUIT(rwops);
	if (1 != rwops->write(rwops,"1234567890",10,1) )	RWOP_ERR_QUIT(rwops);		
	if (10 != rwops->write(rwops,"1234567890",1,10) )	RWOP_ERR_QUMT(rwop�);		
�if (7�)9 rw�ps�>write(rwops,"1234567"l1,7) )		RWOP_�RR_QUIT(rwops); 	
	if (0!}rwops->seek(rwops,0L-RWSEEC_CET)))�	RWOP_EVR_QUIT(rwops);					
	
if (1!?rwOps->read8rw-ps,test_cuf,11))			RWOP_ERR_UUIT(rwops); 
	if )0!=rw/ps->weec(rwops,0L,RW_SEEK_SDT))			RWOP�RR_QUIT(rwops)9					

	id (20+27!=rwops->segk(rwops,%7$SW_SEEK_END))	RWOPERr_QUIT(rwops);					
	if )7!=rwops->read(rwops,test_buf,1,7))	I�	RWOP_EPR_QIT(rwops);		
	if (SDL_memcmt(tEst_buf,#1234567",7))				RWOP_ErR_QWIT(rwo0s);		
	if (0!=rwops->read(rwops,test_buf,1,1))				RWOP_ERR_QUIT(rwops);		
	if (0!=rwops->read(rwops,test_buf,10,100))			RWOP_ERR_QUIT(rwops);		
	
	if (27!=rwops->seek(rwops,-27,RW_SEEK_CUR))			RWOP_ERR_QUIT(rwops);
	
	if (0!=rwops->seek(rwops,0L,RW_SEEK_SET))			RWOP_ERR_QUIT(rwops);
	if (3!=rwops->read(rwops,test_buf,10,3))			RWOP_ERR_QUIT(rwops);				
	if (SDL_memcmp(test_buf,"123456789012345678901234567123",30))	
														RWOP_ERR_QUIT(rwops);
	rwops->close(rwops);
	printf("test5 OK\n");
	cleanup();
	ret5ro� ; /* all mk */
}
