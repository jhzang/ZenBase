// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/atomic.h>
#include <zbase/inttypes.h>

#ifdef ZFR_WINDOWS
#  include <windows.h>
#endif

namespace zbase
{
	namespace atomic
	{
		//
		// Specializations
		//

#ifdef ZFR_WINDOWS

		template <> int32_t FetchAndAdd<int32_t>(int32_t *ptr, int32_t value)
		{ return _InterlockedExchangeAdd(ptr, value); }

		template <> int32_t FetchAndSub<int32_t>(int32_t *ptr, int32_t value)
		{ return _InterlockedExchangeSub(ptr, value); }

		template <> int32_t FetchAndInc<int32_t>(int32_t *ptr)
		{ return _InterlockedExchangeIncrement(ptr); }

		template <> int32_t FetchAndDec<int32_t>(int32_t *ptr)
		{ return _InterlockedExchangeDecrement(ptr); }


		template <> int32_t AddAndFetch<int32_t>(int32_t *ptr, int32_t value)
		{ return _InterlockedAdd(ptr, value); }

		template <> int32_t SubAndFetch<int32_t>(int32_t *ptr, int32_t value)
		{ return _InterlockedSub(ptr, value); }

		template <> int32_t IncAndFetch<int32_t>(int32_t *ptr)
		{ return _InterlockedIncrement(ptr, value); }

		template <> int32_t DecAndFetch<int32_t>(int32_t *ptr)
		{ return _InterlockedDecrement(ptr); }


		template <> int32_t FetchAndAnd<int32_t>(int32_t *ptr, int32_t value)
		{ return _InterlockedAnd(ptr, value); }

		template <> int32_t FetchAndOr<int32_t>(int32_t *ptr, int32_t value)
		{ return _InterlockedOr(ptr, value); }

		template <> int32_t FetchAndXor<int32_t>(int32_t *ptr, int32_t value)
		{ return _InterlockedXor(ptr, value); }

		template <> int32_t AndAndFetch<int32_t>(int32_t *ptr, int32_t value)
		{ int32_t new_value =_InterlockedAnd(ptr, value); return new_value; }

		template <> int32_t OrAndFetch<int32_t>(int32_t *ptr, int32_t value)
		{ int32_t new_value =_InterlockedOr(ptr, value); return new_value; }

		template <> int32_t XorAndFetch<int32_t>(int32_t *ptr, int32_t value)
		{ int32_t new_value =_InterlockedXor(ptr, value); return new_value; }


		template <> int32_t CompareAndSwap<int32_t>(int32_t *ptr, int32_t old_value, int32_t new_value)
		{ return InterlockedCompareExchange(ptr, new_value, old_value); }


		template <> int64_t FetchAndAdd<int64_t>(int64_t *ptr, int64_t value)
		{ return _InterlockedExchangeAdd64(ptr, value); }

		template <> int64_t FetchAndSub<int64_t>(int64_t *ptr, int64_t value)
		{ return _InterlockedExchangeSub64(ptr, value); }

		template <> int64_t FetchAndInc<int64_t>(int64_t *ptr)
		{ return _InterlockedExchangeIncrement64(ptr); }

		template <> int64_t FetchAndDec<int64_t>(int64_t *ptr)
		{ return _InterlockedExchangeDecrement64(ptr); }


		template <> int64_t AddAndFetch<int64_t>(int64_t *ptr, int64_t value)
		{ return _InterlockedAdd64(ptr, value); }

		template <> int64_t SubAndFetch<int64_t>(int64_t *ptr, int64_t value)
		{ return _InterlockedSub64(ptr, value); }

		template <> int64_t IncAndFetch<int64_t>(int64_t *ptr)
		{ return _InterlockedIncrement64(ptr); }

		template <> int64_t DecAndFetch<int64_t>(int64_t *ptr)
		{ return _InterlockedDecrement64(ptr); }


		template <> int64_t FetchAndAnd<int64_t>(int64_t *ptr, int64_t value)
		{ return _InterlockedAnd64(ptr, value); }

		template <> int64_t FetchAndOr<int64_t>(int64_t *ptr, int64_t value)
		{ return _InterlockedOr64(ptr, value); }

		template <> int64_t FetchAndXor<int64_t>(int64_t *ptr, int64_t value)
		{ return _InterlockedXor64(ptr, value); }

		template <> int64_t AndAndFetch<int64_t>(int64_t *ptr, int64_t value)
		{ int64_t new_value =_InterlockedAnd64(ptr, value); return new_value; }

		template <> int64_t OrAndFetch<int64_t>(int64_t *ptr, int64_t value)
		{ int64_t new_value =_InterlockedOr64(ptr, value); return new_value; }

		template <> int64_t XorAndFetch<int64_t>(int64_t *ptr, int64_t value)
		{ int64_t new_value =_InterlockedXor64(ptr, value); return new_value; }


		template <> int64_t CompareAndSwap<int64_t>(int64_t *ptr, int64_t old_value, int64_t new_value)
		{ return InterlockedCompareExchange64(ptr, new_value, old_value); }

#else // Linux

#  define ATOMIC_IMPLEMENTATION(T_Int)                                \
		template <> T_Int FetchAndAdd<T_Int>(T_Int *ptr, T_Int value) \
		{ return __sync_fetch_and_add(ptr, value); }                  \
		                                                              \
		template <> T_Int FetchAndSub<T_Int>(T_Int *ptr, T_Int value) \
		{ return __sync_fetch_and_sub(ptr, value); }                  \
		                                                              \
		template <> T_Int FetchAndInc<T_Int>(T_Int *ptr)              \
		{ return __sync_fetch_and_add(ptr, static_cast<T_Int>(1)); }  \
		                                                              \
		template <> T_Int FetchAndDec<T_Int>(T_Int *ptr)              \
		{ return __sync_fetch_and_sub(ptr, static_cast<T_Int>(1)); }  \
		                                                              \
		                                                              \
		template <> T_Int AddAndFetch<T_Int>(T_Int *ptr, T_Int value) \
		{ return __sync_add_and_fetch(ptr, value); }                  \
		                                                              \
		template <> T_Int SubAndFetch<T_Int>(T_Int *ptr, T_Int value) \
		{ return __sync_sub_and_fetch(ptr, value); }                  \
		                                                              \
		template <> T_Int IncAndFetch<T_Int>(T_Int *ptr)              \
		{ return __sync_add_and_fetch(ptr, static_cast<T_Int>(1)); }  \
		                                                              \
		template <> T_Int DecAndFetch<T_Int>(T_Int *ptr)              \
		{ return __sync_sub_and_fetch(ptr, static_cast<T_Int>(1)); }  \
		                                                              \
		                                                              \
		template <> T_Int FetchAndAnd<T_Int>(T_Int *ptr, T_Int value) \
		{ return __sync_fetch_and_and(ptr, value); }                  \
		                                                              \
		template <> T_Int FetchAndOr<T_Int>(T_Int *ptr, T_Int value)  \
		{ return __sync_fetch_and_or(ptr, value); }                   \
		                                                              \
		template <> T_Int FetchAndXor<T_Int>(T_Int *ptr, T_Int value) \
		{ return __sync_fetch_and_xor(ptr, value); }                  \
		                                                              \
		                                                              \
		template <> T_Int AndAndFetch<T_Int>(T_Int *ptr, T_Int value) \
		{ return __sync_and_and_fetch(ptr, value); }                  \
		                                                              \
		template <> T_Int OrAndFetch<T_Int>(T_Int *ptr, T_Int value)  \
		{ return __sync_or_and_fetch(ptr, value); }                   \
		                                                              \
		template <> T_Int XorAndFetch<T_Int>(T_Int *ptr, T_Int value) \
		{ return __sync_xor_and_fetch(ptr, value); }                  \
		                                                              \
		                                                              \
		template <> T_Int CompareAndSwap<T_Int>(T_Int *ptr, T_Int old_value, T_Int new_value) \
		{ return __sync_val_compare_and_swap(ptr, old_value, new_value); }


		ATOMIC_IMPLEMENTATION(char)
		ATOMIC_IMPLEMENTATION(short)
		ATOMIC_IMPLEMENTATION(int)
		ATOMIC_IMPLEMENTATION(long)
		ATOMIC_IMPLEMENTATION(long long)
		ATOMIC_IMPLEMENTATION(unsigned char)
		ATOMIC_IMPLEMENTATION(unsigned short)
		ATOMIC_IMPLEMENTATION(unsigned int)
		ATOMIC_IMPLEMENTATION(unsigned long)
		ATOMIC_IMPLEMENTATION(unsigned long long)

#endif

	} // namespace atomic
} // namespace zbase

