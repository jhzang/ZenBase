#include <zbase/time_helper.h>
#include <zbase/datetime.h>
#include <cassert>

namespace zbase
{
	bool TimeConfig::IsTimeToUpdate(time_t cur_time)
	{
		struct tm cur_tm;
		localtime_r(&cur_time, &cur_tm);

		bool retflag = false;
		switch (m_type) {
			case TIME_TYPE_ABSOLUTE_TIME:
				retflag = (cur_tm.tm_year + 1900 == m_year && cur_tm.tm_mon + 1 == m_month && cur_tm.tm_mday == m_mday 
					&& cur_tm.tm_hour == m_hour && cur_tm.tm_min == m_minute && cur_tm.tm_sec == m_second);
				break;
			case TIME_TYPE_YEARLY:
				retflag = (cur_tm.tm_mon + 1 == m_month && cur_tm.tm_mday == m_mday 
					&& cur_tm.tm_hour == m_hour && cur_tm.tm_min == m_minute && cur_tm.tm_sec == m_second);
				break;
			case TIME_TYPE_MONTHLY_MDAY:
				retflag = (cur_tm.tm_mday == m_mday 
					&& cur_tm.tm_hour == m_hour && cur_tm.tm_min == m_minute && cur_tm.tm_sec == m_second);
				break;
			case TIME_TYPE_MONTHLY_WDAY:
				retflag = (cur_tm.tm_mday <= 7 && cur_tm.tm_wday == m_wday
					&& cur_tm.tm_hour == m_hour && cur_tm.tm_min == m_minute && cur_tm.tm_sec == m_second);
				break;
			case TIME_TYPE_WEEKLY:
				retflag = (cur_tm.tm_wday == m_wday
					&& cur_tm.tm_hour == m_hour && cur_tm.tm_min == m_minute && cur_tm.tm_sec == m_second);
				break;
			case TIME_TYPE_DAILY:
				retflag = (cur_tm.tm_hour == m_hour && cur_tm.tm_min == m_minute && cur_tm.tm_sec == m_second);
				break;
			default:
				break;
		}
		return retflag;
	}

	int TimeConfig::Compare(const struct tm &local_tm)
	{
		int retval = 0;
		switch (m_type) {
			case TIME_TYPE_ABSOLUTE_TIME:
				if (m_year < local_tm.tm_year + 1900) {
					retval = -1;
				} else if (m_year > local_tm.tm_year + 1900) {
					retval = 1;
				} else if (m_month < local_tm.tm_mon + 1) {
					retval = -1;
				} else if (m_month > local_tm.tm_mon + 1) {
					retval = 1;
				} else if (m_mday < local_tm.tm_mday) {
					retval = -1;
				} else if (m_mday > local_tm.tm_mday) {
					retval = 1;
				} else if (m_hour < local_tm.tm_hour) {
					retval = -1;
				} else if (m_hour > local_tm.tm_hour) {
					retval = 1;
				} else if (m_minute < local_tm.tm_min) {
					retval = -1;
				} else if (m_minute > local_tm.tm_min) {
					retval = 1;
				} else if (m_second < local_tm.tm_sec) {
					retval = -1;
				} else if (m_second > local_tm.tm_sec) {
					retval = 1;
				}
				break;
			case TIME_TYPE_YEARLY:
				if (m_month < local_tm.tm_mon + 1) {
					retval = -1;
				} else if (m_month > local_tm.tm_mon + 1) {
					retval = 1;
				} else if (m_mday < local_tm.tm_mday) {
					retval = -1;
				} else if (m_mday > local_tm.tm_mday) {
					retval = 1;
				} else if (m_hour < local_tm.tm_hour) {
					retval = -1;
				} else if (m_hour > local_tm.tm_hour) {
					retval = 1;
				} else if (m_minute < local_tm.tm_min) {
					retval = -1;
				} else if (m_minute > local_tm.tm_min) {
					retval = 1;
				} else if (m_second < local_tm.tm_sec) {
					retval = -1;
				} else if (m_second > local_tm.tm_sec) {
					retval = 1;
				}
				break;
			case TIME_TYPE_MONTHLY_MDAY:
				if (m_mday < local_tm.tm_mday) {
					retval = -1;
				} else if (m_mday > local_tm.tm_mday) {
					retval = 1;
				} else if (m_hour < local_tm.tm_hour) {
					retval = -1;
				} else if (m_hour > local_tm.tm_hour) {
					retval = 1;
				} else if (m_minute < local_tm.tm_min) {
					retval = -1;
				} else if (m_minute > local_tm.tm_min) {
					retval = 1;
				} else if (m_second < local_tm.tm_sec) {
					retval = -1;
				} else if (m_second > local_tm.tm_sec) {
					retval = 1;
				}
				break;
			case TIME_TYPE_MONTHLY_WDAY:
				if (local_tm.tm_mday > 7) {
					retval = -1;
				} else if (m_wday < local_tm.tm_wday) {
					retval = -1;
				} else if (m_wday > local_tm.tm_wday) {
					retval = 1;
				} else if (m_hour < local_tm.tm_hour) {
					retval = -1;
				} else if (m_hour > local_tm.tm_hour) {
					retval = 1;
				} else if (m_minute < local_tm.tm_min) {
					retval = -1;
				} else if (m_minute > local_tm.tm_min) {
					retval = 1;
				} else if (m_second < local_tm.tm_sec) {
					retval = -1;
				} else if (m_second > local_tm.tm_sec) {
					retval = 1;
				}
				break;
			case TIME_TYPE_WEEKLY:
				if (m_wday < local_tm.tm_wday) {
					retval = -1;
				} else if (m_wday > local_tm.tm_wday) {
					retval = 1;
				} else if (m_hour < local_tm.tm_hour) {
					retval = -1;
				} else if (m_hour > local_tm.tm_hour) {
					retval = 1;
				} else if (m_minute < local_tm.tm_min) {
					retval = -1;
				} else if (m_minute > local_tm.tm_min) {
					retval = 1;
				} else if (m_second < local_tm.tm_sec) {
					retval = -1;
				} else if (m_second > local_tm.tm_sec) {
					retval = 1;
				}
				break;
			case TIME_TYPE_DAILY:
				if (m_hour < local_tm.tm_hour) {
					retval = -1;
				} else if (m_hour > local_tm.tm_hour) {
					retval = 1;
				} else if (m_minute < local_tm.tm_min) {
					retval = -1;
				} else if (m_minute > local_tm.tm_min) {
					retval = 1;
				} else if (m_second < local_tm.tm_sec) {
					retval = -1;
				} else if (m_second > local_tm.tm_sec) {
					retval = 1;
				}
				break;
			default:
				break;
		}
		return retval;
	}

	bool TimeConfig::IsTimeToUpdate(time_t last_time,  time_t cur_time)
	{
		struct tm last_tm, cur_tm;
		localtime_r(&last_time, &last_tm);
		localtime_r(&cur_time, &cur_tm);
		return (Compare(last_tm) > 0 && Compare(cur_tm) < 0);
	}

	bool TimeRange::IsTimeInRange(const struct tm &local_tm)
	{
		assert(m_start.m_type == m_end.m_type);
		return (m_start.Compare(local_tm) <= 0 && m_end.Compare(local_tm) >= 0);
	}

} // namespace zbase

