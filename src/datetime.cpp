// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/datetime.h>

namespace zbase
{
	bool operator > (const TimeDuration &a, const TimeDuration &b)
	{
		return a.m_value > b.m_value;
	}

	bool operator >= (const TimeDuration &a, const TimeDuration &b)
	{
		return a.m_value >= b.m_value;
	}

	bool operator < (const TimeDuration &a, const TimeDuration &b)
	{
		return a.m_value < b.m_value;
	}

	bool operator <= (const TimeDuration &a, const TimeDuration &b)
	{
		return a.m_value <= b.m_value;
	}

	bool operator == (const TimeDuration &a, const TimeDuration &b)
	{
		return a.m_value == b.m_value;
	}

	TimeDuration operator + (const TimeDuration &a, const TimeDuration &b)
	{
		return TimeDuration(a.m_value + b.m_value);
	}

	TimeDuration operator - (const TimeDuration &a, const TimeDuration &b)
	{
		return TimeDuration(a.m_value - b.m_value);
	}

	bool operator > (const DateTime &dt1, const DateTime &dt2)
	{
		return dt1.GetCalendarTime() > dt2.GetCalendarTime();
	}

	bool operator >= (const DateTime &dt1, const DateTime &dt2)
	{
		return dt1.GetCalendarTime() >= dt2.GetCalendarTime();
	}

	bool operator < (const DateTime &dt1, const DateTime &dt2)
	{
		return dt1.GetCalendarTime() < dt2.GetCalendarTime();
	}

	bool operator <= (const DateTime &dt1, const DateTime &dt2)
	{
		return dt1.GetCalendarTime() <= dt2.GetCalendarTime();
	}

	bool operator == (const DateTime &dt1, const DateTime &dt2)
	{
		return dt1.GetCalendarTime() == dt2.GetCalendarTime();
	}

	DateTime operator + (const DateTime &dt, const TimeDuration &span)
	{
		return dt.AddSeconds(span.GetSeconds());
	}

	TimeDuration operator - (const DateTime &dt1, const DateTime &dt2)
	{
		return TimeDuration::FromSeconds(dt1.GetCalendarTime() - dt2.GetCalendarTime());
	}

	time_t LocalTimeToCalendarTime(int abs_year, int month, int mday, int hour, int min, int sec)
	{
		struct tm local_t;
		local_t.tm_year = abs_year - 1900;
		local_t.tm_mon = month - 1;
		local_t.tm_mday = mday;
		local_t.tm_hour = hour;
		local_t.tm_min = min;
		local_t.tm_sec = sec;
		return mktime(&local_t);
	}
} // namespace zbase

