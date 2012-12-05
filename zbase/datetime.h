/**
 * @file      datetime.h
 * @brief     Portable TimeDuration and DateTime implementation
 * @author    Junheng Zang (junheng.zang@gmail.com)
 * @copyright Copyright (c) 2012 Junheng Zang. All Rights Reserved.
 */
#ifndef ZBASE__DATETIME_H
#define ZBASE__DATETIME_H

#include <ctime>
#include <string>
#include <zbase/config.h>
#include <zbase/inttypes.h>

/**
 * @namespace zbase
 */
namespace zbase
{
	/**
	 * @enum  Time Conversion Macros
	 * @brief Time conversion macros
	 */
	enum 
	{
		SECONDS_PER_MINUTE           =         60,
		SECONDS_PER_HOUR             =       3600,
		SECONDS_PER_DAY              =      86400,
		MINUTES_PER_HOUR             =         60,
		MINUTES_PER_DAY              =       1440,
		HOURS_PER_DAY                =         24,
		MILLISECONDS_PER_SECOND      =       1000,
		MILLISECONDS_PER_MINUTE      =      60000,
		MICROSECONDS_PER_MILLISECOND =       1000,
		MICROSECONDS_PER_SECOND      =    1000000,
		MICROSECONDS_PER_MINUTE      =   60000000,
		NANOSECONDS_PER_MICROSECOND  =       1000LL,
		NANOSECONDS_PER_MILLISECOND  =    1000000LL,
		NANOSECONDS_PER_SECOND       = 1000000000LL,
	};

	/**
	 * @class   TimeDuration datetime.h <zbase/datetime.h>
	 * @brief   Time duration in seconds
	 * @details Time duration presentation and comparison
	 */
	class TimeDuration
	{
		friend bool operator > (const TimeDuration &a, const TimeDuration &b);
		friend bool operator >= (const TimeDuration &a, const TimeDuration &b);
		friend bool operator < (const TimeDuration &a, const TimeDuration &b);
		friend bool operator <= (const TimeDuration &a, const TimeDuration &b);
		friend bool operator == (const TimeDuration &a, const TimeDuration &b);
		friend TimeDuration operator + (const TimeDuration &a, const TimeDuration &b);
		friend TimeDuration operator - (const TimeDuration &a, const TimeDuration &b);

	public:
		/**
		 * @brief Constructor
		 */
		TimeDuration(int days, int hours, int minutes, int seconds)
			: m_value(days * SECONDS_PER_DAY + hours * SECONDS_PER_HOUR + minutes * SECONDS_PER_MINUTE + seconds)
		{
		}

		/**
		 * @brief Get time duration in days
		 */
		int GetDays() const    { return m_value / SECONDS_PER_DAY; }
		/**
		 * @brief Get time duration in hours
		 */
		int GetHours() const   { return m_value / SECONDS_PER_HOUR; }
		/**
		 * @brief Get time duration in minutes
		 */
		int GetMinutes() const { return m_value / SECONDS_PER_MINUTE; }
		/**
		 * @brief Get time duration in seconds
		 */
		int GetSeconds() const { return m_value; }

		/**
		 * @brief Get value of days
		 */
		double GetTotalDays() const    { return static_cast<double>(m_value) / SECONDS_PER_DAY; }
		/**
		 * @brief Get value of hours
		 */
		double GetTotalHours() const   { return static_cast<double>(m_value) / SECONDS_PER_HOUR; }
		/**
		 * @brief Get value of minutes
		 */
		double GetTotalMinutes() const { return static_cast<double>(m_value) / SECONDS_PER_MINUTE; }

		/**
		 * @brief Get absolute value of time duration
		 */
		TimeDuration Abs() const    { return TimeDuration(m_value >= 0 ? m_value : -m_value); }
		/**
		 * @brief Get negated value of time duration
		 */
		TimeDuration Negate() const { return TimeDuration(-m_value); }

		/**
		 * @brief Construct a TimeDuration object from seconds
		 */
		static TimeDuration FromSeconds(int value) { return TimeDuration(0, 0, 0, value); }
		/**
		 * @brief Construct a TimeDuration object from minutes
		 */
		static TimeDuration FromMinutes(int value) { return TimeDuration(0, 0, value, 0); }
		/**
		 * @brief Construct a TimeDuration object from hours
		 */
		static TimeDuration FromHours(int value)   { return TimeDuration(0, value, 0, 0); }
		/**
		 * @brief Construct a TimeDuration object from days
		 */
		static TimeDuration FromDays(int value)    { return TimeDuration(value, 0, 0, 0); }
		/**
		 * @brief Construct a zero TimeDuration object
		 */
		static TimeDuration Zero() { return TimeDuration(0); }

		/**
		 * @brief Check if the object is equal to the other TimeDuration object
		 * @return true or false
		 */
		bool Equal(const TimeDuration &other) const { return m_value == other.m_value; }
		/**
		 * @brief Compare the object with the other TimeDuration object
		 * @return -1 for less; 0 for equal; 1 for greater
		 */
		int Compare(const TimeDuration &other) const
		{
			if (m_value > other.m_value) {
				return 1;
			} else if (m_value < other.m_value) {
				return -1;
			} else {
				return 0;
			}
		}
		/**
		 * @brief Compare if two TimeDuration objects are equal
		 * @return -1 for less; 0 for equal; 1 for greater
		 */
		static int Compare(const TimeDuration &a, const TimeDuration &b) { return a.Compare(b); }

		/**
		 * @brief Override += operator
		 */
		TimeDuration& operator += (const TimeDuration &other)
		{
			m_value += other.m_value;
			return *this;
		}

		/**
		 * @brief Override -= operator
		 */
		TimeDuration& operator -= (const TimeDuration &other)
		{
			m_value -= other.m_value;
			return *this;
		}

	private:
		/**
		 * @brief Internal constructor
		 */
		TimeDuration(int value) : m_value(value) {}

	private:
		/**
		 * @brief Internal storage of the time duration value
		 */
		int m_value; // Unit: second
	}; // class TimeDuration

	/**
	 * @brief > operator for two TimeDuration objects
	 */
	bool operator > (const TimeDuration &a, const TimeDuration &b);
	/**
	 * @brief >= operator for two TimeDuration objects
	 */
	bool operator >= (const TimeDuration &a, const TimeDuration &b);
	/**
	 * @brief < operator for two TimeDuration objects
	 */
	bool operator < (const TimeDuration &a, const TimeDuration &b);
	/**
	 * @brief <= operator for two TimeDuration objects
	 */
	bool operator <= (const TimeDuration &a, const TimeDuration &b);
	/**
	 * @brief == operator for two TimeDuration objects
	 */
	bool operator == (const TimeDuration &a, const TimeDuration &b);
	/**
	 * @brief + operator for two TimeDuration objects
	 */
	TimeDuration operator + (const TimeDuration &a, const TimeDuration &b);
	/**
	 * @brief - operator for two TimeDuration objects
	 */
	TimeDuration operator - (const TimeDuration &a, const TimeDuration &b);

	/**
	 * @class   DateTime datetime.h <zbase/datetime.h>
	 * @brief   date and time
	 * @details ATTENTION: Operations won't change DateTime object but create a new one
	 */
	class DateTime
	{
	public:
		/**
		 * @enum Date time kind
		 */
		enum DateTimeKind { DT_UTC, DT_LOCAL };

	public:
		/**
		 * @brief Constructor
		 */
		DateTime(time_t calendar_time, DateTimeKind kind = DT_LOCAL)
			: m_kind(kind), m_calendar_time(calendar_time), m_dt()
		{
			if (DT_UTC == kind) {
				*(const_cast<tm*>(&m_dt)) = *gmtime(&calendar_time);
			} else {
				*(const_cast<tm*>(&m_dt)) = *localtime(&calendar_time);
			}
		}

		/**
		 * @brief Is the date time in UTC expression
		 */
		bool IsUTC() const { return DT_UTC == m_kind; }
		/**
		 * @brief Is the date time in local expression
		 */
		bool IsLocal() const { return DT_LOCAL == m_kind; }

		/**
		 * @brief Check if the object is equal to the other object
		 */
		bool Equal(const DateTime &other) const
		{
			return m_calendar_time == other.m_calendar_time;
		}

		/**
		 * @brief Compare the object with the other DateTime object
		 * @return -1 for less; 0 for equal; 1 for greater
		 */
		int Compare(const DateTime &other) const
		{
			if (m_calendar_time > other.m_calendar_time) {
				return 1;
			} else if (m_calendar_time < other.m_calendar_time) {
				return -1;
			}
			return 0;
		}

		/**
		 * @brief Compare if two DateTime objects are equal
		 * @return -1 for less; 0 for equal; 1 for greater
		 */
		static int Compare(const DateTime &dt1, const DateTime &dt2)
		{
			return dt1.Compare(dt2);
		}

		/**
		 * @brief second component
		 */
		int second() const { return m_dt.tm_sec; } // [0,60]
		/**
		 * @brief minute component
		 */
		int minute() const { return m_dt.tm_min; } // [0,59]
		/**
		 * @brief hour component
		 */
		int hour() const   { return m_dt.tm_hour; } // [0,23]
		/**
		 * @brief month component
		 */
		int month() const  { return m_dt.tm_mon + 1; } // [1,12]
		/**
		 * @brief year component
		 */
		int year() const   { return m_dt.tm_year + 1900; }
		/**
		 * @brief week day component
		 */
		int wday() const   { return m_dt.tm_wday; } // [0,6]
		/**
		 * @brief month day component
		 */
		int mday() const   { return m_dt.tm_mday; } // [1,31]
		/**
		 * @brief year day component
		 */
		int yday() const   { return m_dt.tm_yday + 1; } // [1,366]
		/**
		 * @brief is daylight saving time
		 */
		bool isdst() const { return m_dt.tm_isdst; }
		/**
		 * @brief is leap year
		 */
		bool isLeapYear() const
		{
			if ((m_dt.tm_year % 100) == 0) {
				return (m_dt.tm_year / 400 == 0);
			} else {
				return (m_dt.tm_year / 4);
			}
		}
		/**
		 * @brief Get elapsed seconds in the day
		 */
		int GetSecondsOfDay() const { return m_dt.tm_hour * SECONDS_PER_HOUR + m_dt.tm_min * SECONDS_PER_MINUTE + m_dt.tm_sec; }
		/**
		 * @brief Get elapsed minutes in the day
		 */
		int GetMinutesOfDay() const { return m_dt.tm_hour * MINUTES_PER_HOUR + m_dt.tm_min; }
		/**
		 * @brief Get calendar time
		 */
		time_t GetCalendarTime() const { return m_calendar_time; }

		/**
		 * @brief Add seconds
		 */
		DateTime AddSeconds(int value) const { return DateTime(m_calendar_time + value, m_kind); }
		/**
		 * @brief Add minutes
		 */
		DateTime AddMinutes(int value) const { return DateTime(m_calendar_time + value * SECONDS_PER_MINUTE, m_kind); }
		/**
		 * @brief Add hours
		 */
		DateTime AddHours(int value)   const { return DateTime(m_calendar_time + value * SECONDS_PER_HOUR, m_kind); }
		/**
		 * @brief Add days
		 */
		DateTime AddDays(int value)    const { return DateTime(m_calendar_time + value * SECONDS_PER_DAY, m_kind); }

		/**
		 * @brief Convert to UTC expression
		 */
		DateTime ToUTC() const
		{
			if (DT_UTC == m_kind) {
				return *this;
			}
			return DateTime(m_calendar_time, DT_UTC);
		}

		/**
		 * @brief Convert to local expression
		 */
		DateTime ToLocal() const
		{
			if (DT_LOCAL == m_kind) {
				return *this;
			}
			return DateTime(m_calendar_time, DT_LOCAL);
		}

		/**
		 * @brief Get string expression
		 */
		std::string ToString(const char *format) const
		{
			char str[256] = {0};
			strftime(str, sizeof(str), format, &m_dt);
			return std::string(str, sizeof(str));
		}
		/**
		 * @brief Get date string expression
		 */
		std::string ToDateString() const { return ToString("%Y-%m-%d"); }
		/**
		 * @brief Get time string expression
		 */
		std::string ToShortTimeString() const { return ToString("%H:%M:%S"); }
		/**
		 * @brief Get long time string expression
		 */
		std::string ToLongTimeString() const { return ToString("%Y-%m-%d %H:%M:%S"); }
		/**
		 * @brief Get long time string expression in UTC
		 */
		std::string ToLongTimeStringUTC() const { return ToString("%Y-%m-%d %H:%M:%S"); }

		/**
		 * @brief Get the current time in local expression
		 */
		static DateTime Now()
		{
			return DateTime(time(NULL), DT_LOCAL);
		}

		/**
		 * @brief Get the current time in UTC expression
		 */
		static DateTime NowUTC()
		{
			return DateTime(time(NULL), DT_UTC);
		}

	private:
		const DateTimeKind m_kind;
		const time_t m_calendar_time;
		const struct tm m_dt;
	};

	/**
	 * @brief > operator for two DateTime objects
	 */
	bool operator > (const DateTime &dt1, const DateTime &dt2);
	/**
	 * @brief >= operator for two DateTime objects
	 */
	bool operator >= (const DateTime &dt1, const DateTime &dt2);
	/**
	 * @brief < operator for two DateTime objects
	 */
	bool operator < (const DateTime &dt1, const DateTime &dt2);
	/**
	 * @brief <= operator for two DateTime objects
	 */
	bool operator <= (const DateTime &dt1, const DateTime &dt2);
	/**
	 * @brief == operator for two DateTime objects
	 */
	bool operator == (const DateTime &dt1, const DateTime &dt2);
	DateTime operator + (const DateTime &dt, const TimeDuration &span);
	TimeDuration operator - (const DateTime &dt1, const DateTime &dt2);

	/**
	 * @brief Convert broken-down times to calender time
	 * @param [in] abs_year: absolute year, e.g. 2012
	 * @param [in] month: [1,12]
	 * @param [in] mday: [1,31]
	 * @param [in] hour: [0,23]
	 * @param [in] min: [0,59]
	 * @param [in] sec: [0,60], 60 for leap seconds
	 */
	time_t LocalTimeToCalendarTime(int abs_year, int month, int mday, int hour, int min, int sec);

}  // namespace zbase
#endif // ZBASE__DATETIME_H

