/**
 * @file      clock.h
 * @brief     Systemwide realtime clock and monotonic clock with different resolutions. 
 *            Platform independent.
 * @author    Junheng Zang (junheng.zang@gmail.com)
 * @copyright Copyright (c) 2012 Junheng Zang. All Rights Reserved.
 */
#ifndef ZBASE__CLOCK_H
#define ZBASE__CLOCK_H

#include <zbase/config.h>
#include <zbase/inttypes.h>

/**
 * @namespace zbase
 */
namespace zbase
{
	/**
	 * @enum  TimeResolution
	 * @brief Time resolutions 
	 */
	enum TimeResolution
	{
		SECOND, MILLISECOND, MICROSECOND, NANOSECOND
	};

	/**
	 * @class   Clock clock.h <zbase/clock.h>
	 * @brief   Systemwide realtime clock
	 * @details The system time can be adjusted forward or backward by authenticated user.
	 *          It is used for recording and displaying.
	 * @tparam  res Time resolution
	 */
	template <TimeResolution res>
	class Clock
	{
	public:
		/**
		 * @brief Get the current time point
		 */
		static uint64_t GetTime();
		/**
		 * @brief Get seconds west of GMT
		 */
		static int64_t GetGmtOffset();
	}; // class Clock


	/**
	 * @class   MonoClock clock.h <zbase/clock.h>
	 * @brief   High-resolution monotonic clock
	 * @details The monotonic represents monotonic time since some unspecified starting point and can not be set.
	 *          It is used to measure elapsed time
	 */
	class MonoClock
	{
	public:
		/**
		 * @brief Get clock frequency
		 */
		static uint64_t GetFrequency();
		/**
		 * @brief Get clock resolution
		 */
		static uint64_t GetResolution();
		/**
		 * @brief Get the current monotonic time value in nanosecond
		 */
		static uint64_t GetTime(); // ns
		/**
		 * @brief Get the current monotonic time value in different time unit
		 */
		template <TimeResolution res> static double GetElapsed();
	}; // class MonoClock

} // namespace zbase
#endif

