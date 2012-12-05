// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
// Misc utilities
//
#ifndef ZBASE__UTILITY_H
#define ZBASE__UTILITY_H

#include <string>
#include <zbase/clock.h>

// Parameter prefix to improve readability
#define __IN
#define __OUT
#define __INOUT

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

namespace zbase
{
	class _NoExternalConstruct
	{
	protected:
		_NoExternalConstruct() {}
	}; // class _NoExternalConstruct

	// Utility to forbid copy constructor and assignment operator overriding
	class _NoCopy
	{
	public:
		_NoCopy() {}

	private:
		_NoCopy(const _NoCopy &other) {}
		_NoCopy& operator = (const _NoCopy &other) { return *this; }
	}; // class _NoCopy

	template <TimeResolution resolution> void Sleep(unsigned int duration);

	std::string GetTempPath();

} // namespace zbase
#endif // ZBASE__UTILITY_H

