// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
// Portable byte order detecting and converting utility
//
#ifndef ZBASE__BYTE_ORDER_H
#define ZBASE__BYTE_ORDER_H

namespace zbase
{
	namespace byteorder
	{
		extern const bool kIsHostLE;

		template <typename T> T ByteSwap(T value);
		template <typename T> T HToLE(T value);
		template <typename T> T HToBE(T value);
		template <typename T> T LEToH(T value);
		template <typename T> T BEToH(T value);
	}
}

#endif

