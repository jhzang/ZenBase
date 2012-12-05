/**
 * @file      inttypes.h
 * @brief     Platform-independent integer type definitions
 * @author    Junheng Zang (junheng.zang@gmail.com)
 * @copyright Copyright (c) 2012 Junheng Zang. All Rights Reserved.
 */
#ifndef ZBASE__INTTYPES_H
#define ZBASE__INTTYPES_H

#include <climits>

#if defined(BOOST_HAS_STDINT_H)
#  include <boost/cstdint.hpp>
#elif defined(__GNUC__) && (__GNUC__ >= 3)
#  include <stdint.h>
#elif defined(_MSC_VER) && (_MSC_VER >= 1600) // VS2010
#  include <cstdint>
#else
#  if UCHAR_MAX == 0xFF
	typedef signed char        int8_t;
	typedef unsigned char      uint8_t;
#  else
#    error default width of char is not 8bits; you must hand modify zbase/inttypes.h
#  endif
#  if USHRT_MAX == 0xFFFF
	typedef signed short       int16_t;
	typedef unsigned short     uint16_t;
#  else
#    error default width of short is not 16bits; you must hand modify zbase/inttypes.h
#  endif
#  if UINT_MAX == 0xFFFFFFFF
	typedef signed int         int32_t;
	typedef unsigned int       uint32_t;
#  else
#    error default width of int is not 32bits; you must hand modify zbase/inttypes.h
#  endif
#  if defined(__MSC_VER__) && (__MSC_VER__ < 1300)
	typedef signed __int64     int64_t;
	typedef unsigned __int64   uint64_t;
#  else
	typedef signed long long   int64_t;
	typedef unsigned long long uint64_t;
#  endif
#endif

#ifndef CHAR_BIT
#  if UCHAR_MAX == 0xFF
#    define CHAR_BIT 8
#  endif
#endif

#ifndef SHORT_BIT
#  if USHRT_MAX == 0xFFFF
#    define SHORT_BIT 16
#  endif
#endif

#ifndef INT_BIT
#  if UINT_MAX == 0xFFFFFFFF
#    define INT_BIT 32
#  elif UINT_MAX == 0xFFFF
#    define INT_BIT 16
#  endif
#endif

#ifndef LONG_BIT
#  if ULONG_MAX == 0xFFFFFFFF
#    define LONG_BIT 32
#  elif ULONG_MAX == 0xFFFFFFFFFFFFFFFFULL
#    define LONG_BIT 64
#  endif
#endif

#ifndef LLONG_BIT
#  if defined(ULLONG_MAX) && (ULLONG_MAX == 0xFFFFFFFFFFFFFFFFULL)
#    define LLONG_BIT 64
#  endif
#endif

#endif // ZBASE__INTTYPES_H

