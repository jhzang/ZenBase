// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
// Portable atomic utility
//
#ifndef ZBASE__ATOMIC_H
#define ZBASE__ATOMIC_H

namespace zbase
{
	// ATTENTION: 
	// On Windows, the variables of the atomic operations must be aligned on a 32-bit boundary, or they will behave unpredictablly.
	// On Linux, GCC will allow any integral scalar or pointer type that is 1, 2, 4 or 8 bytes in length.
	namespace atomic
	{
		template <typename T_Int> T_Int FetchAndAdd(T_Int *ptr, T_Int value);
		template <typename T_Int> T_Int FetchAndSub(T_Int *ptr, T_Int value);
		template <typename T_Int> T_Int FetchAndInc(T_Int *ptr);
		template <typename T_Int> T_Int FetchAndDec(T_Int *ptr);

		template <typename T_Int> T_Int AddAndFetch(T_Int *ptr, T_Int value);
		template <typename T_Int> T_Int SubAndFetch(T_Int *ptr, T_Int value);
		template <typename T_Int> T_Int IncAndFetch(T_Int *ptr);
		template <typename T_Int> T_Int DecAndFetch(T_Int *ptr);

		template <typename T_Int> T_Int FetchAndAnd(T_Int *ptr, T_Int value);
		template <typename T_Int> T_Int FetchAndOr(T_Int *ptr, T_Int value);
		template <typename T_Int> T_Int FetchAndXor(T_Int *ptr, T_Int value);

		template <typename T_Int> T_Int AndAndFetch(T_Int *ptr, T_Int value);
		template <typename T_Int> T_Int OrAndFetch(T_Int *ptr, T_Int value);
		template <typename T_Int> T_Int XorAndFetch(T_Int *ptr, T_Int value);

		template <typename T_Int> T_Int CompareAndSwap(T_Int *ptr, T_Int old_value, T_Int new_value);
	} // namespace atomic
} // namespace zbase
#endif // ZBASE__ATOMIC_H

