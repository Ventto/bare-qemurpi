/*
(C) 2014 EEMBC(R).  All rights reserved.                            

All EEMBC Benchmark Software are products of EEMBC 
and are provided under the terms of the EEMBC Benchmark License Agreements.  
The EEMBC Benchmark Software are proprietary intellectual properties of EEMBC and its Members 
and is protected under all applicable laws, including all applicable copyright laws.  
If you received this EEMBC Benchmark Software without having 
a currently effective EEMBC Benchmark License Agreement, you must discontinue use. 
Please refer to http://www.eembc.org/license.php for the specific license agreement that pertains to this Benchmark Software.
*/

/*==============================================================================
 * File: mith/include/th_cfg.h
 *   Configuration file for the test harness.
 *
 *------------------------------------------------------------------------------
 * Other Copyright Notice (if any): 
 * 
 * For conditions of distribution and use, see the accompanying README file.
 * ===========================================================================*/
/**
@file
@brief Test Harness definitions for all benchmarks.
*/

#ifndef THCFG_H
#define THCFG_H

#include <limits.h>

/**
 * Enable Host specific code for host based execution using an OS.
 * HOST_EXAMPLE_CODE can also be used to mark porting changes
 */
#define	HOST_EXAMPLE_CODE	(0)

/** Target System/Processor Major Revision. */
#define TARGET_MAJOR           0
/** Target System/Processor Minor Revision. */
#define TARGET_MINOR           0
/** Target System/Processor Stepping. */
#define TARGET_STEP            'R'
/** Target System/Processor sub-revision. */
#define TARGET_REVISION        0

/** Target Timer Available */
#define TARGET_TIMER_AVAIL     (1)
/** Target Timer Intrusive (can effect performance score) */
#define TARGET_TIMER_INTRUSIVE (0)

#define EE_MAX_CPU	1
/* Flag: BMDEBUG
 * Set BMDEBUG to a (1) to enable debugging printf's in benchmarks
 * Set it to a (0) for the released version of the BM
 */
#define BMDEBUG (0)

/* Flag: THDEBUG
 * Set THDEBUG to a (1) to enable debugging printf's in the harness
 * Set it to a (0) for the released version of the BM
 */
#define THDEBUG 0
/* Flag: EE_BIG_ENDIAN
 * Define BIG or LITTLE Endian here.  
 * @note If not defined from COMPILER_DEFINES in toolchain file, Set it here. 
 * Default is Little Endian.
 */
#define EE_BIG_ENDIAN    1
#define EE_LITTLE_ENDIAN 0

#if !defined( EE_LITTLE_ENDIAN ) 
#define EE_LITTLE_ENDIAN (!EE_BIG_ENDIAN)
#endif

#if !defined( EE_BIG_ENDIAN )
#define EE_BIG_ENDIAN (!EE_LITTLE_ENDIAN)
#endif

#if EE_BIG_ENDIAN && EE_LITTLE_ENDIAN
#error "Cannot have both Big and Little Endian 1"
#endif

#if ((!EE_BIG_ENDIAN) && (!EE_LITTLE_ENDIAN))
#error "Cannot have both Big and Little Endian 0"
#endif

/* Flag: EE_SIZEOF_PTR
	Define number of bytes for pointer type.
	Default to 4 bytes.
*/
#define EE_SIZEOF_PTR 4
#define EE_PTR_ALIGN 4

/* Flag: EE_SIZEOF_LONG
	Define number of bytes for long type.
	Default to 4 bytes.
*/
#define EE_SIZEOF_LONG 4

/* Flag: EE_SIZEOF_INT
	Define number of bytes for int type.
	Default to 4 bytes.
*/
#define EE_SIZEOF_INT 4

/* Flag: NEED_INT_LIMITS
	Define this if you need INT_MIN and INT_MAX 
	and they are not provided by your compiler header files.
*/
#define NEED_INT_LIMITS 1

/** Floating point supported in compiler.
 * Set FLOAT_SUPPORT to (1) if the target has floating point, or compiler
 * supports floating point emulation.
 *
 * Set FLOAT_SUPPORT to (0) if not.
 *
 */
#define FLOAT_SUPPORT (1)

#define FP_KERNELS_SUPPORT (1)

#define DEBUG_ACCURATE_BITS (0)

#define NEED_SNR (1)

#define USE_FP32 (1)

#define USE_MATH_H (1)

#if ( FLOAT_SUPPORT && !USE_MATH_H )
#error "Floating point suite requires C99 math.h header and associated libm functions!"
#endif

#define FP_FORMAT_NEEDS_LEADING_ONE (1)

#define AL_ISFINITE (1)

/* define if compiler does not support restrict */
#if defined(__MWERKS__) || defined(__DCC__)
#define RESTRICT
#else
#define RESTRICT restrict
#endif

/* default alignment for fp data array */
#define ALIGN_BOUNDARY 64

/* define NO_VAR_ALIGN to avoid variable array alignment */
#if !defined ( NO_VAR_ALIGN )
  #define __ALIGN_PRE(x) 
  #define __ALIGN_POST(x) __attribute__ ((aligned (x)))
#else
 #define __ALIGN_PRE(x)
 #define __ALIGN_POST(x) 
#endif

#define _ALIGN_VAR(type, var) __ALIGN_PRE(ALIGN_BOUNDARY) type var __ALIGN_POST(ALIGN_BOUNDARY) 

#define malloc_aligned(size, align) malloc(size)
#define free_aligned(base) free(base)


/**
 *  HEAP Control Section
 *  @note: See heapport.h for enabling debug on internal heap manager.
 */

/**
 * Set COMPILE_OUT_HEAP to 1 to completely 'compile out' the test harness
 * memory allocation routines.
 * To use compiler's malloc support, set HAVE_MALLOC to 1.
 * @verbatim
 * COMPILE_OUT_HEAP	1,	HAVE_MALLOC 1, use compiler's heap manager.
 * COMPILE_OUT_HEAP	0,	HAVE_MALLOC 0, use internal heap manager.
 * COMPILE_OUT_HEAP	1,	HAVE_MALLOC 0, minimize code size (no malloc).
 * COMPILE_OUT_HEAP	0,	HAVE_MALLOC 1, maximize code size (invalid).
 * @endverbatim
 */
#define COMPILE_OUT_HEAP (1)
/** Your libc has malloc, calloc, realloc, and free.*/
#define HAVE_MALLOC (1)
#define REPORT_THMALLOC_STATS 0

/** Validation of Internal heap manager, and libc heap manager */
#if !COMPILE_OUT_HEAP && HAVE_MALLOC
#error	"COMPILE_OUT_HEAP is 0, and HAVE_MALLOC is 1. Cannot select both internal and compiler malloc functions."
#endif

/**
 * Turn this on to map malloc() and free() calls to th_malloc()
 * and th_free().  Note: you only need to do this if you use
 * functions in your C library that indirectly call malloc() and free().
 *
 * @warning If malloc is called before C program start (by kernel or crt0)
 * this option CANNOT be used. The harness dectects, and attempts to fail with
 * exit code 8 (THE_OUT_OF_MEMORY). Trap code for this case cannot be 
 * guaranteed to work before C program load and initialization.
 */
#define MAP_MALLOC_TO_TH (0)

#if COMPILE_OUT_HEAP && MAP_MALLOC_TO_TH
#error "COMPILE_OUT_HEAP && MAP_MALLOC_TO_TH invalid. Set one to 0"
#endif

/**
 * CRC Verification Section.
 *
 * Set CRC_CHECK to 1 to enable Intrusive CRC checking.
 * When CRC_CHECK is enabled, required # of iterations set during compile.
 * Do NOT use when measuring timing for certification.
 */
#define CRC_CHECK				(0)

/** Non-Intrusive CRC check.
 *
 * Set NON_INTRUSIVE_CRC_CHECK to 1 to enable Non-Intrusive CRC checking.
 * Non Intrusive CRC check is done outside of benchmark timing, and
 * is independent of the number of iterations.
 * You MAY use this when measuring timing for certification.
 */
#define	NON_INTRUSIVE_CRC_CHECK	(1)

#if		CRC_CHECK && NON_INTRUSIVE_CRC_CHECK
#error	"CRC_CHECK and NON_INTRUSIVE_CRC_CHECK are enabled. Set one of them to 0"
#endif

/**
 * Display results in th_report_results using integers.
 * VERIFY_INT - v1, v2, v3, v4 as size_t
 */
#define VERIFY_INT (1)

/**
 * Display results in th_report_results using floating point.
 * VERIFY_FLOAT - v1,v2 -> double v1v2, and v3,v4 -> double v3v4.
 *
 * This is defined on a PER BENCHMARK basis. The bmark, using a union
 * loads two integer fields with one floating point result.
 *
 * @note VERIFY_FLOAT is used in telecom benchmarks to display 
 * automatically calculated diffmeasure results 
 */
#define	VERIFY_FLOAT (FLOAT_SUPPORT)

/**
 * Set USE_TH_PRINTF to (0) to use the printf engine that comes with
 * your compiler's C Library.
 *
 * Set USE_TH_PRINTF to (1) to use the printf engine that is built into
 * the Test Harness.
 */
#define USE_TH_PRINTF (0)

/** Do not Translate CRLF for serial terminal */
#define NO_CRLF_XLATE (1)

/** Use Test Harness Streams calls (RAM File System).
 *
 * Set USE_TH_FILEIO to (0) to use the File System I/O that comes with
 * your compiler's C Library (stdio.h). Make sure your embedded target has a 
 * block device and drivers that can be used.
 *
 * Set USE_TH_FILEIO to (1) to use the RAM file engine that is built into
 * the Test Harness.
 * 
 * Initial version of MITH does not support USE_TH_FILEIO 1
 *
 * For specific needs (i.e. Read from RAM file, ignore Writes) modifiy thal.c
 */
#define USE_TH_FILEIO (1)

#define FAKE_FILEIO (1)

/**
 * Set HAVE_FILEIO to (1) if your compiler's C Library has support for file
 * I/O. 
 * 
 * Set HAVE_FILEIO to (0) if your compiler's C Library does not have support
 * for stdio stream routines: fopen,fclose,fread,fwrite,vfprintf,putc,getc,ungetc, fgets,
 * feof, ferror, and, tmpfile. 
 * These may be individually controlled in thal.c.
 * Initial version of MITH does not support HAVE_FILEIO 0
 *
 * For specific needs modifiy thal.c
 */
#define HAVE_FILEIO (0)

#if (HAVE_FILEIO && !USE_TH_FILEIO && !FAKE_FILEIO) 
	#define ee_FILE FILE
	#define ee_DIR DIR
	#define ee_stat stat
#endif

/** Heap alignment specific to Networking benchmarks. */
#define HEAP_ALIGN_V	8

/** Maximum size of Internal Heap.
@note See thal.c to determine if heap memory is allocated as static array, or with libc malloc.
*/
#define HEAP_SIZE	(1024*1024*4)	/* 4 Mb */

/** Command Line Size (TH Regular only).
 *
 * This define is used to set the size of the buffer used to hold the
 * benchmark command line.  E.g. the 'argc' and 'argv' arguments will
 * be in this buffer.
 *
 * @note that two buffers of CMD_LINE_SIZE are allocated.  Normaly, you will not
 * have to change this.  But, if your system is low on memory, you can make
 * CMD_LINE_SIZE smaller.  
 * @warning It is not a good idea to go below 128 bytes, Some benchmarks may fail.
 */
#define CMD_LINE_SIZE         (1024)
/** Maximum number of argc variables passed through to benchmark. */
#define MAX_ARGC              (128)

/**
 * @todo thconfig.h, thconfig.h. from Autoconf section in thcfg.h.
 * A list of compiler capabilities. Intended usage is
 * to identify POSIX compliant functions and headers, so all tool chains will be
 * able to take advantage of this, and the harness code remains portable.
 *
 * @note This is slightly different in that the 1/0 are used rather than
 * #define 1/#undef. The #ifndef wrapper can then be activated allowing the variable 
 * to be set to 1 or 0 externally. Autoheader does not support this.
 * @warning You cannot use #ifdef/#ifndef with these structures. But most professional
 * Autoheader people use #if's anyway which resolve to 0 on undefined symbols:). It's
 * a necessary tradeoff.
 * @note While strdup is a malloc/free variant, it may be possible for a libc to have malloc,
 * and not have implemented strdup in string.h.
 */

/** Define to 1 if your libc has the `memcpy' function (uses malloc/free). */
#define HAVE_MEMCPY 1

/** Define to 1 if your libc has the `bcopy' function (uses malloc/free). */
#define HAVE_BCOPY 1

/** Define to 1 if your libc has the `strdup' function (uses malloc/free). */
#define HAVE_STRDUP 0

/** Define to 1 if your libc has the `strtoll' function.
@note Harness uses this in doscan.c
*/
#define HAVE_STRTOLL 1

/** Define to 1 if your libc has the `strtod' function.
@note Harness uses this in doscan.c only on long double path.
*/
#define	HAVE_STRTOD	1

/** Set this define to 1 if your compiler has assert.h. */
#define HAVE_ASSERT_H 1

/** Set this define to 1 if your compiler has errno.h. */
#define HAVE_ERRNO_H 1

/** Set this 1 if your compiler has stat.h */
#define	HAVE_STAT_H	0

/** Set this 1 if your compiler has sys/stat.h */
#define	HAVE_SYS_STAT_H	1
#define STUB_STAT 0

/** Set this 1 if declarations of STDERR/STDIN/STDOUT are required */
#define NEED_STD_FILES 1

/** Set this 1 if declarations of SEEK_SET etc are required */
#define NEED_SEEK_PARAMS 0

/** Set this define to 1 if your compiler has getpid.
@note used only in HOST_EXAMPLE_CODE. */
#define HAVE_GETPID 0

/** Set this define to 1 if your compiler has dirent.h*/
#define HAVE_DIRENT_H 0

/** Define to 1 if you have dirent functions.*/
#define HAVE_DIRENT	0

/** Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.*/
#define HAVE_SYS_DIR_H 0

/** Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.*/
#define HAVE_SYS_NDIR_H 0

/** Set this define to 1 if the benchmark is using ee_dirent.
If the benchmark is using a libc defined dirent set this to 0
*/
#define USE_EE_DIRENT	1

/** Set this define to 1 if your compiler has unistd.h (chdir) */
#define HAVE_UNISTD_H 1

/* Define to 1 if `st_blksize' is member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_BLKSIZE 1

/* Define to 1 if `st_blocks' is member of `struct stat'. */
#define HAVE_STRUCT_STAT_ST_BLOCKS 1

/** Set this define to 1 if the benchmark is using ee_stat.
If the benchmark is using a libc defined stat set this to 0
*/
#define USE_EE_STAT	0

#define NEED_MKSTEMP 1

/** Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/** Define to 1 if you have the `vsscanf' function. */
#define HAVE_VSSCANF 1
#define HAVE_VFSCANF 1

/** Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/** @todo break out includes section to define libc header actions for
different tool chain configurations.
*/

/** 
 * @todo Remove eembc_dt.h defines that use common names.
 * The purpose of this section is to disable eembc_dt extended definitions
 * for applications that have conflicts. 
 * @warning USE CAREFULLY, A TH Library compiled
 * with different definitions than an application may have side effects. In 
 * this case, eembc_dt.h itself will need to be changed to support the application.
 * YOU are responsible for this as part of porting.
 *
 * Control for low level definitions, patterned after autoheader.
 * All are wrapped defines so that benchmarks can override in harness.h, or as needed.
 * Also used inside of benchmarks which may internally define these types
 * for different purposes.
 */

/** Use TH Byte define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_BYTE_DEFINE)
#define	USE_TH_BYTE_DEFINE	(1)
#endif
/** Use TH Short define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_SHORT_DEFINE)
#define	USE_TH_SHORT_DEFINE	(1)
#endif
/** Use TH Long define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_LONG_DEFINE)
#define	USE_TH_LONG_DEFINE	(1)
#endif
/** Use TH Bool define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_BOOL_DEFINE)
#define	USE_TH_BOOL_DEFINE	(1)
#endif
/** Use TH SUCCESS define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_SUCCESS_DEFINE)
#define	USE_TH_SUCCESS_DEFINE	(1)
#endif
/** Use TH FAILURE define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_FAILURE_DEFINE)
#define	USE_TH_FAILURE_DEFINE	(1)
#endif
/** Use TH Enable define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_ENABLE_DEFINE)
#define	USE_TH_ENABLE_DEFINE	(1)
#endif
/* disable if toolchain has a define for BlockSize */
#if		!defined(USE_TH_BLOCKSIZE_DEFINE)
#define	USE_TH_BLOCKSIZE_DEFINE	(1)
#endif

#define HAVE_INLINE 0

#if (HAVE_INLINE!=1)
#define NO_INLINE_SUPPORT 1 
#endif

#define USE_CTYPE 1

/* Thread related configuration */
/* #define HAVE_PTHREAD_SETAFFINITY_NP 0
#define HAVE_PTHREAD_SELF 0 */
#define USE_SINGLE_CONTEXT 1
#define MAX_CONTEXTS 1
#define HAVE_PTHREAD 0
#define USE_NATIVE_PTHREAD 0

#endif /* THCFG_H file sentinel */

