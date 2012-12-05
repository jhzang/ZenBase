// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/utility.h>
#include <zbase/datetime.h>
#include <cstdlib>

#ifdef ZFR_WINDOWS
#	include <windows.h>
#elif defined(ZFR_LINUX)
#	include <unistd.h>
#endif

namespace zbase
{
#ifdef ZFR_WINDOWS

	template <>
	void Sleep<SECOND>(unsigned int duration)
	{
		Sleep(duration * MILLISECONDS_PER_SECOND);
	}

	template <>
	void Sleep<MILLISECOND>(unsigned int duration)
	{
		Sleep(duration);
	}

	std::string GetTempPath()
	{
		chat path[MAX_PATH] = {0};
		GetTempPath(path, MAX_PATH - 1);
		return path;
	}

#elif defined(ZFR_LINUX)

	template <>
	void Sleep<SECOND>(unsigned int duration)
	{
		sleep(duration);
	}

	template <>
	void Sleep<MILLISECOND>(unsigned int duration)
	{
		usleep(duration * MICROSECONDS_PER_MILLISECOND);
	}

	template <>
	void Sleep<MICROSECOND>(unsigned int duration)
	{
		usleep(duration);
	}

	template <>
	void Sleep<NANOSECOND>(unsigned int duration)
	{
		struct timespec req;
		req.tv_sec = duration / NANOSECONDS_PER_SECOND;
		req.tv_nsec = duration % NANOSECONDS_PER_SECOND;
		nanosleep(&req, NULL);
	}

	std::string GetTempPath()
	{
		char *p = NULL;
		if (NULL != (p = getenv("TMPDIR"))) {
			return p;
		} else if (NULL != (p = getenv("TMP"))) {
			return p;
		} else if (NULL != (p = getenv("TEMP"))) {
			return p;
		} else if (NULL != (p = getenv("TEMPDIR"))) {
			return p;
		}
		return "/tmp";
	}

#endif

} // namespace zbase

