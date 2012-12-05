// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/random.h>
#include <ctime>
#include <sstream>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/discrete_distribution.hpp>

namespace zbase
{
	Random* Random::DefaultGenerator()
	{
		static Random s_instance(time(NULL));
		return &s_instance;
	}

	template <>
	short Random::GenSmallInt<UNIFORM_DISTRIBUTION>(short min, short max)
	{
		boost::random::uniform_int_distribution<short> dist(min, max);
		return dist(m_generator);
	}

	template <>
	short Random::GenSmallInt<NORMAL_DISTRIBUTION>(short min, short max)
	{
		boost::random::normal_distribution<double> dist(0.0, 0.2);
		short value = (min + max) / 2 + (max - min + 1) / 2.0f * dist(m_generator);
		if (value < min) {
			value = min;
		} else if (value > max) {
			value = max;
		}
		return value;
	}

	template <>
	int Random::GenInt<UNIFORM_DISTRIBUTION>(int min, int max)
	{
		boost::random::uniform_int_distribution<int> dist(min, max);
		return dist(m_generator);
	}

	template <>
	int Random::GenInt<NORMAL_DISTRIBUTION>(int min, int max)
	{
		boost::random::normal_distribution<double> dist(0.0, 0.2);
		int value = (min + max) / 2 + (max - min + 1) / 2.0 * dist(m_generator);
		if (value < min) {
			value = min;
		} else if (value > max) {
			value = max;
		}
		return value;
	}

	template <>
	float Random::GenFloat<UNIFORM_DISTRIBUTION>(float min, float max)
	{
		boost::random::uniform_real_distribution<float> dist(min, max);
		return dist(m_generator);
	}

	template <>
	float Random::GenFloat<NORMAL_DISTRIBUTION>(float min, float max)
	{
		boost::random::normal_distribution<float> dist(0.0, 0.2);
		float value = (min + max) / 2.0f + (max - min) / 2.0f * dist(m_generator);
		if (value < min) {
			value = min;
		} else if (value > max) {
			value = max;
		}
		return value;
	}

	template <>
	double Random::GenDouble<UNIFORM_DISTRIBUTION>(double min, double max)
	{
		boost::random::uniform_real_distribution<double> dist(min, max);
		return dist(m_generator);
	}

	template <>
	double Random::GenDouble<NORMAL_DISTRIBUTION>(double min, double max)
	{
		boost::random::normal_distribution<double> dist(0.0, 0.2);
		double value = (min + max) / 2.0 + (max - min) / 2.0 * dist(m_generator);
		if (value < min) {
			value = min;
		} else if (value > max) {
			value = max;
		}
		return value;
	}

	template <typename RealType>
	int Random::RandSelect(RealType *probabilities, size_t count)
	{
		boost::random::discrete_distribution<RealType> dist(probabilities);
		return dist(m_generator);
	}

	//std::string Random::GenString(size_t len, const std::string &chars)
	//{
	//	assert (len > 0);

	//	// We use random_device as a source of entropy, since we want
	//	// passwords that are not predictable.
	//    boost::random::random_device rng;
	//	boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
	//	std::stringstream ss;
	//	for(size_t i = 0; i < len; ++i) {
	//		ss << chars[index_dist(rng)];
	//	}
	//	return ss.str();
	//}

} // namespace zbase

