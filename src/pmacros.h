/* 
 * Copyright (C) 2010-2013 Alexander Saprykin <xelfium@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
 */

/**
 * @file pmacros.h
 * @brief Miscellaneous macros 
 * @author Alexander Saprykin
 *
 * Contains useful macros for detecting host OS, compiler, etc.
 */


#if !defined (__PLIB_H_INSIDE__) && !defined (PLIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <plib.h> instead."
#endif

#ifndef __PMACROS_H__
#define __PMACROS_H__

#include <stdio.h>

/* Operating systems */
/* Darwin and BSD4 */
#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#  define P_OS_DARWIN
#  define P_OS_BSD4
#  ifdef __LP64__
#    define P_OS_DARWIN64
#  else
#    define P_OS_DARWIN32
#  endif
/* Microsoft Windows */
#elif defined(_WIN64) || defined(_M_X64) || defined(_M_AMD64)
#  define P_OS_WIN64
#elif defined(__WIN32__) || defined(_WIN32) || defined(WIN32)
#  define P_OS_WIN
/* Linux */
#elif defined(__linux) || defined(__linux__)
#  define P_OS_LINUX
/* Sun Solaris */
#elif defined(__sun) || defined(sun)
#  define P_OS_SOLARIS
/* QNX6 */
#elif defined(__QNXNTO__)
#  define P_OS_QNX6
/* QNX */
#elif defined(__QNX__)
#  define P_OS_QNX
#endif

#ifdef P_OS_WIN64
#  define P_OS_WIN
#endif

#if defined(P_OS_DARWIN)
#  define P_OS_MAC
#  if defined(P_OS_DARWIN64)
#     define P_OS_MAC64
#  elif defined(P_OS_DARWIN32)
#     define P_OS_MAC32
#  endif
#endif

/* Compilers */

/* Microsoft Visual C/C++ */
#if defined(_MSC_VER)
# define P_CC_MSVC
# if defined(__INTEL_COMPILER)
#   define P_CC_INTEL
# endif
/* GNU C */
#elif defined(__GNUC__)
#  define P_CC_GNU
#  if defined(__MINGW32__)
#    define P_CC_MINGW
#  endif
#  if defined(__INTEL_COMPILER)
#    define P_CC_INTEL
#  endif
#  if defined(__clang__)
#    define P_CC_CLANG
#  endif
/* Sun WorkShop/Studio */
#elif defined(__SUNPRO_C)
#  define P_CC_SUN
/* Watcom C++ */
#elif defined(__WATCOMC__)
#  define P_CC_WATCOM
/* Intel C/C++ */
#elif defined(__INTEL_COMPILER)
#  define P_CC_INTEL
#endif

/**
 * @def P_GNUC_WARN_UNUSED_RESULT
 * @brief Gives warning if returned from function result is not used
 */
#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  define P_GNUC_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#  define P_GNUC_WARN_UNUSED_RESULT
#endif

/**
 * @def P_LIB_API
 * @brief Export symbols macro
 */
#ifdef P_CC_MSVC
#  define P_LIB_API __declspec(dllexport)
#else
#  define P_LIB_API
#endif

/**
 * @def P_NO_RETURN
 * @brief Notifies compiler that function will never return a value (e.g. abort ())
 */
#ifdef P_CC_MSVC
#  define P_NO_RETURN __declspec(noreturn)
#elif defined(P_CC_GNU)
#  define P_NO_RETURN __attribute__((noreturn))
#else
#  define P_NO_RETURN
#endif

/** Casts int to 32-bit pointer */
#define P_INT_TO_POINTER(i) ((void *) (long)(i))
/** Casts 32-bit pointer to int */
#define P_POINTER_TO_INT(p) ((int) (long)(p))

/**
 * @def P_STRTOK
 * @brief Platform-independent MT-safe strtok()
 */
#ifdef P_OS_WIN
#  ifdef P_CC_MINGW
#    define P_STRTOK(str, delim, buf) strtok(str, delim)
#  else
#    define P_STRTOK(str, delim, buf) strtok_s(str, delim, buf)
#  endif
#else
#  define P_STRTOK(str, delim, buf) strtok_r(str, delim, buf)
#endif

/**
 * @def P_UNUSED
 * @brief Macro to by-pass compiler warning on usused variables
 */
#define P_UNUSED(a) ((void) a)

/**
 * @def P_WARNING
 * @brief Prints warning message
 * @param msg Message to print.
 */
#define P_WARNING(msg) printf ("** Warning: %s **\n", msg)

/**
 * @def P_ERROR
 * @brief Prints error message
 * @param msg Message to print.
 */
#define P_ERROR(msg) printf ("** Error: %s **\n", msg)

/**
 * @def P_DEBUG
 * @brief Prints debug message
 * @param msg Message to print.
 */
#define P_DEBUG(msg) printf ("** Debug: %s **\n", msg)

/**
  * @def P_BEGIN_DECLS
  * @brief Starts .h file declarations to be exported as C functions
  */
/**
  * @def P_END_DECLS
  * @brief Closes .h file declarations to be exported as C functions,
  * should be always used after #P_END_DECLS
  */
#ifdef __cplusplus
#  define P_BEGIN_DECLS extern "C" {
#  define P_END_DECLS }
#else
#  define P_BEGIN_DECLS
#  define P_END_DECLS
#endif

#endif /* __PMACROS_H__ */
