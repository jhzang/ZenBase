// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/clock.h>

#ifdef ZBASE_WINDOWS
#  include <windows.h>
#else
#  ifdef ZBASE_LINUX
#    include <linux/version.h>
#  endif
#  include <unistd.h>
#  include <sys/time.h>
#  include <time.h>
#endif

#include <ctime>

#include <zbase/datetime.h>

namespace zbase
{
	static int64_t GetGmtOffset_second()
	{
#ifdef ZBASE_USE_GLIBC
		static timeval tv;
		struct timezone tz;
		gettimeofday(&tv, &tz);
		return tz.tz_minuteswest * SECONDS_PER_MINUTE;
#elif defined(ZBASE_WINDOWS)
		TIME_ZONE_INFORMATION tzi;
		GetTimeZoneInformation(&tzi);
		return tzi.Bias * SECONDS_PER_MINUTE;
#endif
	}

	template <>
	uint64_t Clock<SECOND>::GetTime()
	{
		return time(NULL);
	}

	template <>
	int64_t Clock<SECOND>::GetGmtOffset()
	{
		return GetGmtOffset_second();
	}

	template <>
	uint64_t Clock<MILLISECOND>::GetTime()
	{
#ifdef ZBASE_WINDOWS
		// FILETIME contains a 64-bit value representing the the number of 100-ns intervals since Jan 1, 1601 UTC
		FILETIME filetime;
		GetSystemTimeAsFileTime(&filetime);
		// ATTENTION: DO NOT cast a pointer to FILETIME to LARGE_INTEGER to __int64 because it can cause alignment faults on 64-bit Windows
		ULARGE_INTEGER value;
		value.LowPart = filetime.dwLowDateTime;
		value.HighPart = filetime.dwHighDateTime;
		return value;
#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return static_cast<uint64_t>(tv.tv_sec) * MILLISECONDS_PER_SECOND + tv.tv_usec / MICROSECONDS_PER_MILLISECOND;
#endif
	}

	template <>
	int64_t Clock<MILLISECOND>::GetGmtOffset()
	{
		return GetGmtOffset_second() * MILLISECONDS_PER_SECOND;
	}

	template <>
	uint64_t Clock<MICROSECOND>::GetTime()
	{
#ifdef ZBASE_WINDOWS
		// FIXME: inaccurate implementation for compatibility
		// FILETIME contains a 64-bit value representing the the number of 100-ns intervals since Jan 1, 1601 UTC
		FILETIME filetime;
		GetSystemTimeAsFileTime(&filetime);
		// ATTENTION: DO NOT cast a pointer to FILETIME to LARGE_INTEGER to __int64 because it can cause alignment faults on 64-bit Windows
		ULARGE_INTEGER value;
		value.LowPart = filetime.dwLowDateTime;
		value.HighPart = filetime.dwHighDateTime;
		return static_cast<uint64_t>(value) * 100 / NANOSECONDS_PER_MICROSECOND;
#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return static_cast<uint64_t>(tv.tv_sec) * MICROSECONDS_PER_SECOND + tv.tv_usec;
#endif
	}

	template <>
	int64_t Clock<MICROSECOND>::GetGmtOffset()
	{
		return GetGmtOffset_second() * MICROSECONDS_PER_SECOND;
	}

	template <>
	uint64_t Clock<NANOSECOND>::GetTime()
	{
#ifdef ZBASE_WINDOWS
		// FIXME: inaccurate implementation for compatibility
		// FILETIME contains a 64-bit value representing the the number of 100-ns intervals since Jan 1, 1601 UTC
		FILETIME filetime;
		GetSystemTimeAsFileTime(&filetime);
		// ATTENTION: DO NOT cast a pointer to FILETIME to LARGE_INTEGER to __int64 because it can cause alignment faults on 64-bit Windows
		ULARGE_INTEGER value;
		value.LowPart = filetime.dwLowDateTime;
		value.HighPart = filetime.dwHighDateTime;
		return static_cast<uint64_t>(value) * 100;
#else
		// ATTENTION: link with -lrt
		struct timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		return static_cast<uint64_t>(tp.tv_sec) * NANOSECONDS_PER_SECOND + tp.tv_nsec;
#endif
	}

	template <>
	int64_t Clock<NANOSECOND>::GetGmtOffset()
	{
		return GetGmtOffset_second() * NANOSECONDS_PER_SECOND;
	}


	//
	// MonoClock
	//
#ifdef ZBASE_WINDOWS
	static LARGE_INTEGER s_mono_clock_frequency; // cpu ticks per second
#else
	static struct timespec s_mono_clock_resolution;
#endif

	static bool InitMonoClock()
	{
#ifdef ZBASE_WINDOWS
		// FIXME: QueryPerformanceFrequency is not reliable on multicore CPU or variable frequency CPU
		QueryPerformanceFrequency(&s_mono_clock_frequency);
#elif defined(ZBASE_LINUX)
		clock_getres(CLOCK_MONOTONIC, &s_mono_clock_resolution);
#endif
		return true;
	}

	static bool s_dummy = InitMonoClock();

	uint64_t MonoClock::GetFrequency()
	{
#ifdef ZBASE_WINDOWS
		return s_mono_clock_frequency;
#else
		return NANOSECONDS_PER_SECOND / s_mono_clock_resolution.tv_nsec;
#endif
	}

	uint64_t MonoClock::GetResolution()
	{
#ifdef ZBASE_WINDOWS
		return NANOSECONDS_PER_SECOND / s_mono_clock_frequency;
#else
		return s_mono_clock_resolution.tv_nsec;
#endif
	}

	uint64_t MonoClock::GetTime()
	{
#ifdef ZBASE_WINDOWS
		// FIXME: QueryPerformanceFrequency is not reliable on multicore CPU or variable frequency CPU
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		return static_cast<uint64_t>(counter) * NANOSECONDS_PER_SECOND / s_mono_clock_frequency;
#elif defined(ZBASE_LINUX)
		struct timespec tp;
		clock_gettime(CLOCK_MONOTONIC, &tp);
		return static_cast<uint64_t>(tp.tv_sec) * NANOSECONDS_PER_SECOND + tp.tv_nsec;
#endif
	}

	template <> double MonoClock::GetElapsed<NANOSECOND>()
	{
		return static_cast<double>(GetTime());
	}

	template <> double MonoClock::GetElapsed<MICROSECOND>()
	{
		return GetTime() / static_cast<double>(NANOSECONDS_PER_MICROSECOND);
	}

	template <> double MonoClock::GetElapsed<MILLISECOND>()
	{
		return GetTime() / static_cast<double>(NANOSECONDS_PER_MILLISECOND);
	}

	template <> double MonoClock::GetElapsed<SECOND>()
	{
		return GetTime() / static_cast<double>(NANOSECONDS_PER_SECOND);
	}

} // namespace zbase

