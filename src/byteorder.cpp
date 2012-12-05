// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/byteorder.h>
#include <zbase/inttypes.h>

#if defined __GNUC__ && __GNUC__ >= 3
//#  include <endian.h>
#  include <byteswap.h>
#  define BYTE_SWAP_16(x) bswap_16(x)
#  define BYTE_SWAP_32(x) bswap_32(x)
#  define BYTE_SWAP_64(x) bswap_64(x)
#else // Portable implementation
#  define BYTE_SWAP_16(x) \
	(((*((uint8_t*)&(x))) << 8) | (*((uint8_t*)&(x)+1)))
#  define BYTE_SWAP_32(x) \
	(((*((uint8_t*)&(x))) << 24) | ((*((uint8_t*)&(x)+1)) << 16) | ((*((uint8_t*)&(x)+2)) << 8) | (*((uint8_t*)&(x)+3)))
#  define BYTE_SWAP_64(x) \
	(((*((uint8_t*)&(x))) << 56) | ((*((uint8_t*)&(x)+1)) << 48) | ((*((uint8_t*)&(x)+2)) << 40) | ((*((uint8_t*)&(x)+3)) << 32) | \
	 ((*((uint8_t*)&(x)+4)) << 24) | ((*((uint8_t*)&(x)+5)) << 16) | ((*((uint8_t*)&(x)+6)) << 8) | (*((uint8_t*)&(x)+7)))
#endif

#define BYTE_SWAP_NBITS(x, n) BYTE_SWAP_##n(x)

namespace zbase
{
	namespace byteorder
	{
		// Check host byte order
		static const uint16_t kByteOrderDetector = 0x1234;
		const bool kIsHostLE = (0x34 == (*(uint8_t*)&kByteOrderDetector));

#define BYTE_ORDER_IMPLEMENTATION(T, N) \
		template <> T ByteSwap(T value) { return BYTE_SWAP_NBITS(value, N); } \
		template <> T HToLE(T value) { return kIsHostLE ? value : BYTE_SWAP_NBITS(value, N); } \
		template <> T HToBE(T value) { return kIsHostLE ? BYTE_SWAP_NBITS(value, N) : value; } \
		template <> T LEToH(T value) { return kIsHostLE ? value : BYTE_SWAP_NBITS(value, N); } \
		template <> T BEToH(T value) { return kIsHostLE ? BYTE_SWAP_NBITS(value, N) : value; }

		BYTE_ORDER_IMPLEMENTATION(short, SHORT_BIT)
		BYTE_ORDER_IMPLEMENTATION(unsigned short, SHORT_BIT)
		BYTE_ORDER_IMPLEMENTATION(int, INT_BIT)
		BYTE_ORDER_IMPLEMENTATION(unsigned int, INT_BIT)
		BYTE_ORDER_IMPLEMENTATION(long, LONG_BIT)
		BYTE_ORDER_IMPLEMENTATION(unsigned long, LONG_BIT)
		BYTE_ORDER_IMPLEMENTATION(long long, LLONG_BIT)
		BYTE_ORDER_IMPLEMENTATION(unsigned long long, LLONG_BIT)
#undef BYTE_ORDER_IMPLEMENTATION
	}
}

