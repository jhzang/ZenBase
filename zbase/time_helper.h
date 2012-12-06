#ifndef ZBASE__TIME_HELPER_H
#define ZBASE__TIME_HELPER_H

#include <ctime>

namespace zbase
{
	enum TimeType
	{
		TIME_TYPE_UNSPEC,
		TIME_TYPE_ABSOLUTE_TIME,
		TIME_TYPE_YEARLY,       // yearly: month, mday, hour, min, sec
		TIME_TYPE_MONTHLY_MDAY, // monthly: mday, hour, min, sec
		TIME_TYPE_MONTHLY_WDAY, // monthly: first wday, hour, min, sec
		TIME_TYPE_WEEKLY,       // weekly: wday, hour, min, sec
		TIME_TYPE_DAILY,        // daily: hour, min, sec
	};

	class TimeConfig
	{
		friend class TimeRange;

	public:
		TimeConfig() 
			: m_type(TIME_TYPE_UNSPEC), m_year(0), m_month(0), m_mday(0), 
			  m_wday(0), m_hour(0), m_minute(0), m_second(0)
		{
		}

		void InitAbsTimeConfig(
			short year, 
			unsigned char month, 
			unsigned char mday, 
			unsigned char hour, 
			unsigned char minute, 
			unsigned char second)
		{
			Init(TIME_TYPE_ABSOLUTE_TIME, year, month, mday, 0, hour, minute, second);
		}

		void InitYearlyConfig(
			unsigned char month, 
			unsigned char mday, 
			unsigned char hour, 
			unsigned char minute, 
			unsigned char second)
		{
			Init(TIME_TYPE_YEARLY, 0, month, mday, 0, hour, minute, second);
		}

		void InitMonthlyMDayConfig(
			unsigned char mday, 
			unsigned char hour, 
			unsigned char minute, 
			unsigned char second)
		{
			Init(TIME_TYPE_MONTHLY_MDAY, 0, 0, mday, 0, hour, minute, second);
		}

		void InitMonthlyWDayConfig(
			unsigned char wday, 
			unsigned char hour, 
			unsigned char minute, 
			unsigned char second)
		{
			Init(TIME_TYPE_MONTHLY_WDAY, 0, 0, 0, wday, hour, minute, second);
		}

		void InitWeeklyConfig(
			unsigned char wday, 
			unsigned char hour, 
			unsigned char minute, 
			unsigned char second)
		{
			Init(TIME_TYPE_WEEKLY, 0, 0, 0, wday, hour, minute, second);
		}

		void InitDailyConfig(
			unsigned char hour, 
			unsigned char minute, 
			unsigned char second)
		{
			Init(TIME_TYPE_DAILY, 0, 0, 0, 0, hour, minute, second);
		}

		bool IsTimeToUpdate(time_t cur_time);
		bool IsTimeToUpdate(time_t last_time,  time_t cur_time);

	protected:
		void Init(TimeType type,
			short year, 
			unsigned char month, 
			unsigned char mday, 
			unsigned char wday, 
			unsigned char hour, 
			unsigned char minute, 
			unsigned char second)
		{
			m_type = type;
			m_year = year;
			m_month = month;
			m_mday = mday;
			m_wday = wday;
			m_hour = hour;
			m_minute = minute;
			m_second = second;
		}

		int Compare(const struct tm &local_tm);

	private:
		TimeType m_type;
		short m_year;           // e.g. 2012
		unsigned char m_month;  // [1,12]
		unsigned char m_mday;   // [1,31]
		unsigned char m_wday;   // The number of days since Sunday. [0,6]
		unsigned char m_hour;   // [0,23]
		unsigned char m_minute; // [0,59]
		unsigned char m_second; // [0,60], 60 for leap seconds
	};

	// Time range [start,end]
	class TimeRange
	{
	public:
		TimeRange(const TimeConfig &start, const TimeConfig &end)
			: m_start(start), m_end(end)
		{
		}

		bool IsTimeInRange(const struct tm &local_tm);

	private:
		TimeConfig m_start;
		TimeConfig m_end;
	};

} // namespace zbase
#endif

