// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
// Random generators
//
#ifndef ZBASE__RANDOM_H
#define ZBASE__RANDOM_H

#include <limits>
#include <string>
#include <boost/random/mersenne_twister.hpp>

#define DEFAULT_RANDOM_CHAR_TABLE \
	"abcdefghijklmnopqrstuvwxyz" \
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
	"1234567890" \
	"!@#$%^&*()" \
	"`~-_=+[{]{\\|;:'\",<.>/? "

namespace zbase
{
	enum DistributionType
	{
		UNIFORM_DISTRIBUTION,
		NORMAL_DISTRIBUTION,
		GAUSSIAN_DISTRIBUTION = NORMAL_DISTRIBUTION,
	};

	class Random
	{
	public:
		Random() {}
		Random(int seed) : m_generator(seed) {}

		void SetSeed(int seed) { m_generator.seed(seed); }

		template <DistributionType type>
		short GenSmallInt(short min = 0, short max = std::numeric_limits<short>::max());

		template <DistributionType type>
		int GenInt(int min = 0, int max = std::numeric_limits<int>::max());

		template <DistributionType type>
		float GenFloat(float min = 0.0f, float max = 1.0f);

		template <DistributionType type>
		double GenDouble(double min = 0.0, double max = 1.0);

		// the input probabilities will be normalized automatically
		template <typename RealType>
		int RandSelect(RealType *probabilities, size_t count);

		//static std::string GenString(size_t len, const std::string &chars = DEFAULT_RANDOM_CHAR_TABLE);

		static Random* DefaultGenerator();

	private:
		boost::mt19937 m_generator;
	};

} // namespace zbase

#endif

