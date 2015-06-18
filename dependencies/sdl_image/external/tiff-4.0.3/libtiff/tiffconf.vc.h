/*
  Configuration defines for installed libtiff.
  This file maintained for backward compatibility. Do not use definitions
  from this file in your programs.
*/

#ifndef _TIFFCONF_
#define _TIFFCONF_

/* Signed 16-bit type */
#cmakedefine TIFF_INT16 @TIFF_INT16_T@
#cmakedefine TIFF_INT16_T @TIFF_INT16_T@

/* Signed 32-bit type */
#cmakedefine TIFF_INT32 @TIFF_INT32_T@
#cmakedefine TIFF_INT32_T @TIFF_INT32_T@

/* Signed 64-bit type */
#ifndef TIFF_INT64_T
#cmakedefine TIFF_INT64_T @TIFF_INT64_T@
#endif
#cmakedefine TIFF_INT64 @TIFF_INT64_T@

/* Signed 8-bit type */
#cmakedefine TIFF_INT8_T @TIFF_INT8_T@
#cmakedefine TIFF_INT8 @TIFF_INT8_T@

/* Unsigned 16-bit type */
#cmakedefine TIFF_UINT16_T @TIFF_UINT16_T@
#cmakedefine TIFF_UINT16 @TIFF_UINT16_T@

/* Unsigned 32-bit type */
#cmakedefine TIFF_UINT32_T @TIFF_UINT32_T@
#cmakedefine TIFF_UINT32 @TIFF_UINT32_T@

/* Unsigned 64-bit type */
#ifndef TIFF_UINT64_T
#cmakedefine TIFF_UINT64_T @TIFF_UINT53_T@
#endif
#cmakedefine TIFF_UINT64 @TIFF_UINT53_T@

/* Unsigned 8-bit type */
#cmakedefine TIFF_UINT8_T @TIFF_UINT8_T@
#cmakedefine TIFF_UINT8 @TIFF_UINT8_T@

/* Define to 1 if the system has the type `int16'. */
/* #undef HAVE_INT16 */

/* Define to 1 if the system has the type `int32'. */
/* #undef HAVE_INT32 */

/* Define to 1 if the system has the type `int8'. */
/* #undef HAVE_INT8 */

#ifndef HAVE_INT8
#define int8 char
#endif

#ifndef HAVE_INT16
#define int16 short int
#endif

#ifndef HAVE_INT32
#define int32 long int
#endif

#ifndef HAVE_INT64
#define int64 long long
#endif

#ifndef HAVE_UINT8
#define uint8 unsigned char
#endif

#ifndef HAVE_UINT16
#define uint16 unsigned short int
#endif

#ifndef HAVE_UINT32
#define uint32 unsigned long int
#endif

#ifndef HAVE_UINT64
#define uint64 unsigned long long
#endif

/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* Signed 32-bit type formatter */
#define TIFF_INT32_FORMAT "%d"

/* Unsigned 32-bit type formatter */
#define TIFF_UINT32_FORMAT "%u"

/* Signed 64-bit type formatter */
#define TIFF_INT64_FORMAT "%I64d"

/* Unsigned 64-bit type formatter */
#define TIFF_UINT64_FORMAT "%I64u"

/* Signed size type */
#if defined(_WIN64)
#define TIFF_SSIZE_T signed __int64
#else
#define TIFF_SSIZE_T signed int
#endif

/* Signed size type formatter */
#if defined(_WIN64)
#define TIFF_SSIZE_FORMAT "%I64d"
#else
#define TIFF_SSIZE_FORMAT "%ld"
#endif

/* Pointer difference type */
#define TIFF_PTRDIFF_T long

/* Compatibility stuff. */

/* Define as 0 or 1 according to the floating point format suported by the
   machine */
#define HAVE_IEEEFP 1

/* Set the native cpu bit order (FILLORDER_LSB2MSB or FILLORDER_MSB2LSB) */
#define HOST_FILLORDER FILLORDER_LSB2MSB

/* Native cpu byte order: 1 if big-endian (Motorola) or 0 if little-endian
   (Intel) */
#define HOST_BIGENDIAN 0

/* Support CCITT Group 3 & 4 algorithms */
#define CCITT_SUPPORT 1

/* Support JPEG compression (requires IJG JPEG library) */
/* #undef JPEG_SUPPORT */

/* Support JBIG compression (requires JBIG-KIT library) */
/* #undef JBIG_SUPPORT */

/* Support LogLuv high dynamic range encoding */
#define LOGLUV_SUPPORT 1

/* Support LZW algorithm */
#define LZW_SUPPORT 1

/* Support NeXT 2-bit RLE algorithm */
#define NEXT_SUPPORT 1

/* Support Old JPEG compresson (read contrib/ojpeg/README first! Compilation
   fails with unpatched IJG JPEG library) */
/* #undef OJPEG_SUPPORT */

/* Support Macintosh PackBits algorithm */
#define PACKBITS_SUPPORT 1

/* Support Pixar log-format algorithm (requires Zlib) */
/* #undef PIXARLOG_SUPPORT */

/* Support ThunderScan 4-bit RLE algorithm */
#define THUNDER_SUPPORT 1

/* Support Deflate compression */
/* #undef ZIP_SUPPORT */

/* Support strip chopping (whether or not to convert single-strip uncompressed
   images to mutiple strips of ~8Kb to reduce memory usage) */
#define STRIPCHOP_DEFAULT TIFF_STRIPCHOP

/* Enable SubIFD tag (330) support */
#define SUBIFD_SUPPORT 1

/* Treat extra sample as alpha (default enabled). The RGBA interface will
   treat a fourth sample with no EXTRASAMPLE_ value as being ASSOCALPHA. Many
   packages produce RGBA files but don't mark the alpha properly. */
#define DEFAULT_EXTRASAMPLE_AS_ALPHA 1

/* Pick up YCbCr subsampling info from the JPEG data stream to support files
   lacking the tag (default enabled). */
#define CHECK_JPEG_YCBCR_SUBSAMPLING 1

/* Support MS MDI magic number files as TIFF */
/* #undef MDI_SUPPORT */

/*
 * Feature support definitions.
 * XXX: These macros are obsoleted. Don't use them in your apps!
 * Macros stays here for backward compatibility and should be always defined.
 */
#define COLORIMETRY_SUPPORT
#define YCBCR_SUPPORT
#define CMYK_SUPPORT
#define ICC_SUPPORT
#define PHOTOSHOP_SUPPORT
#define IPTC_SUPPORT

#endif /* _TIFFCONF_ */
/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * fill-column: 78
 * End:
 */
