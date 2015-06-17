message(STATUS "Checking whether system has ANSI C header files")
include (CheckIncludeFiles)

include(CheckPrototypeExists)
check_include_files("dlfcn.h;stdint.h;stddef.h;inttypes.h;stdlib.h;strings.h;string.h;float.h" StandardHeadersExist)
if(StandardHeadersExist)
	check_prototype_exists(memchr string.h memchrExists)
	if(memchrExists)

		check_prototype_exists(free stdlib.h freeExists)
		if(freeExists)
			message(STATUS "ANSI C header files - found")
			set(STDC_HEADERS 1 CACHE INTERNAL "System has ANSI C header files")
			set(HAVE_STRINGS_H 1)
			set(HAVE_STRING_H 1)
			set(HAVE_FLOAT_H 1)
			set(HAVE_STDLIB_H 1)
			set(HAVE_STDDEF_H 1)
			set(HAVE_STDINT_H 1)
			set(HAVE_INTTYPES_H 1)
			set(HAVE_DLFCN_H 1)
		endif(freeExists)
	endif(memchrExists)
endif(StandardHeadersExist)

if(NOT STDC_HEADERS)
	message(STATUS "ANSI C header files - not found")
	set(STDC_HEADERS 0 CACHE INTERNAL "System has ANSI C header files")
endif(NOT STDC_HEADERS)

check_include_files(unistd.h HAVE_UNISTD_H)

include(CheckDIRSymbolExists)
check_dirsymbol_exists("sys/stat.h;sys/types.h;dirent.h" HAVE_DIRENT_H)
if (HAVE_DIRENT_H)
	set(HAVE_SYS_STAT_H 1)
	set(HAVE_SYS_TYPES_H 1)
endif (HAVE_DIRENT_H)

find_package(Libc)

if (LIBC_FOUND)
	set(HAVE_LIBC 1)
	set(STDC_HEADERS 1)
endif()

check_include_files(alloca.h HAVE_ALLOCA_H)
check_include_files(fcntl.h HAVE_FCNTL_H)
check_include_files(stdio.h HAVE_STDIO_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(stdarg.h HAVE_STDARG_H)
check_include_files(malloc.h HAVE_MALLOC_H)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(ctype.h HAVE_CTYPE_H)
check_include_files(math.h HAVE_MATH_H)
check_include_files(iconv.h HAVE_ICONV_H)
check_include_files(signal.h HAVE_SIGNAL_H)

check_prototype_exists(malloc stdlib.h HAVE_MALLOC)
check_prototype_exists(calloc stdlib.h HAVE_CALLOC)
check_prototype_exists(realloc stdlib.h HAVE_REALLOC)
check_prototype_exists(free stdlib.h HAVE_FREE)
check_prototype_exists(alloca alloca.h HAVE_ALLOCA)

check_prototype_exists(qsort stdlib.h HAVE_QSORT)
check_prototype_exists(abs stdlib.h HAVE_ABS)
check_prototype_exists(sinf math.h HAVE_SINF)
check_prototype_exists(bcopy strings.h HAVE_BCOPY)
check_prototype_exists(memset string.h HAVE_MEMSET)
check_prototype_exists(memcpy string.h HAVE_MEMCPY)
check_prototype_exists(memmove string.h HAVE_MEMMOVE)
check_prototype_exists(memcmp string.h HAVE_MEMCMP)
check_prototype_exists(strlen string.h HAVE_STRLEN)
check_prototype_exists(strlcpy bsd/string.h HAVE_STRLCPY)
check_prototype_exists(strlcat bsd/string.h HAVE_STRLCAT)
check_prototype_exists(strdup string.h HAVE_STRDUP)
check_prototype_exists(_strrev string.h HAVE__STRREV)
check_prototype_exists(_strupr string.h HAVE__STRUPR)
check_prototype_exists(_strlwr string.h HAVE__STRLWR)
check_prototype_exists(index string.h HAVE_INDEX)
check_prototype_exists(rindex string.h HAVE_RINDEX)
check_prototype_exists(strchr string.h HAVE_STRCHR)
check_prototype_exists(strrchr string.h HAVE_STRRCHR)
check_prototype_exists(strstr string.h HAVE_STRSTR)
check_prototype_exists(itoa stdlib.h HAVE_ITOA)
check_prototype_exists(_ltoa stdlib.h HAVE__LTOA)
check_prototype_exists(_uitoa stdlib.h HAVE__UITOA)
check_prototype_exists(_ultoa stdlib.h HAVE__ULTOA)
check_prototype_exists(strtol stdlib.h HAVE_STRTOL)
check_prototype_exists(strtoul stdlib.h HAVE_STRTOUL)
check_prototype_exists(_i64toa stdlib.h HAVE__I64TOA)
check_prototype_exists(_ui64toa stdlib.h HAVE__UI64TOA)
check_prototype_exists(strtoll stdlib.h HAVE_STRTOLL)
check_prototype_exists(strtoull stdlib.h HAVE_STRTOULL)
check_prototype_exists(strtod stdlib.h HAVE_STRTOD)
check_prototype_exists(atoi stdlib.h HAVE_ATOI)
check_prototype_exists(atof stdlib.h HAVE_ATOF)
check_prototype_exists(strcmp string.h HAVE_STRCMP)
check_prototype_exists(strncmp string.h HAVE_STRNCMP)
check_prototype_exists(_stricmp string.h HAVE__STRICMP)
check_prototype_exists(strcasecmp string.h HAVE_STRCASECMP)
check_prototype_exists(_strnicmp string.h HAVE__STRNICMP)
check_prototype_exists(strncasecmp string.h HAVE_STRNCASECMP)
check_prototype_exists(sscanf stdio.h HAVE_SSCANF)
check_prototype_exists(snprintf stdio.h HAVE_SNPRINTF)
check_prototype_exists(vsnprintf stdio.h HAVE_VSNPRINTF)

check_prototype_exists(iconv iconv.h HAVE_ICONV)

check_prototype_exists(sigaction signal.h HAVE_SIGACTION)
check_prototype_exists(sa_sigaction signal.h HAVE_SA_SIGACTION)

check_prototype_exists(setjmp setjmp.h HAVE_SETJMP)

check_prototype_exists(nanosleep time.h HAVE_NANOSLEEP)
check_prototype_exists(clock_gettime time.h HAVE_CLOCK_GETTIME)

check_prototype_exists(getpagesize unistd.h HAVE_GETPAGESIZE)
check_prototype_exists(mprotect sys/mman.h HAVE_MPROTECT)
check_prototype_exists(sem_timedwait semaphore.h HAVE_SEM_TIMEDWAIT)

check_prototype_exists(getenv stdlib.h HAVE_GETENV)
check_prototype_exists(putenv stdlib.h HAVE_PUTENV)
check_prototype_exists(setenv stdlib.h HAVE_SETENV)
check_prototype_exists(unsetenv stdlib.h HAVE_UNSETENV)

check_include_files("dlfcn.h;stdint.h;stddef.h;inttypes.h;stdlib.h;strings.h;string.h;float.h" StandardHeadersExist)
set(HAVE_LIBM 1)
