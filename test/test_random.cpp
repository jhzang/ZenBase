#include <gtest/gtest.h>
#include <zbase/random.h>
#include <zbase/inttypes.h>
using namespace zbase;

TEST(RandomTest, UniformDistribution) {
	Random *gen = Random::DefaultGenerator();
	for (size_t i = 0; i < 100; ++i)
	{
		short r1 = gen->GenSmallInt<UNIFORM_DISTRIBUTION>(100, 200);
		EXPECT_TRUE(r1 >= 100 && r1 <= 200);
		int r2 = gen->GenInt<UNIFORM_DISTRIBUTION>(100, 200);
		EXPECT_TRUE(r2 >= 100 && r2 <= 200);
		float r3 = gen->GenFloat<UNIFORM_DISTRIBUTION>(0.5f, 2.0f);
		EXPECT_TRUE(r3 >= 0.5f && r3 <= 2.0f);
		double r4 = gen->GenDouble<UNIFORM_DISTRIBUTION>(0.5, 2.0);
		EXPECT_TRUE(r4 >= 0.5 && r4 <= 2.0);
	}
}

TEST(RandomTest, NormalDistribution) {
	Random *gen = Random::DefaultGenerator();
	for (size_t i = 0; i < 1000; ++i)
	{
		short r1 = gen->GenSmallInt<NORMAL_DISTRIBUTION>(100, 200);
		EXPECT_TRUE(r1 >= 100 && r1 <= 200);
		int r2 = gen->GenInt<NORMAL_DISTRIBUTION>(100, 200);
		EXPECT_TRUE(r2 >= 100 && r2 <= 200);
		float r3 = gen->GenFloat<NORMAL_DISTRIBUTION>(0.5f, 2.0f);
		EXPECT_TRUE(r3 >= 0.5f && r3 <= 2.0f);
		double r4 = gen->GenDouble<NORMAL_DISTRIBUTION>(0.5, 2.0);
		EXPECT_TRUE(r4 >= 0.5 && r4 <= 2.0);
	}
}

TEST(RandomTest, GaussianDistribution) {
	Random *gen = Random::DefaultGenerator();
	for (size_t i = 0; i < 100; ++i)
	{
		short r1 = gen->GenSmallInt<GAUSSIAN_DISTRIBUTION>(100, 200);
		EXPECT_TRUE(r1 >= 100 && r1 <= 200);
		int r2 = gen->GenInt<GAUSSIAN_DISTRIBUTION>(100, 200);
		EXPECT_TRUE(r2 >= 100 && r2 <= 200);
		float r3 = gen->GenFloat<GAUSSIAN_DISTRIBUTION>(0.5f, 2.0f);
		EXPECT_TRUE(r3 >= 0.5f && r3 <= 2.0f);
		double r4 = gen->GenDouble<GAUSSIAN_DISTRIBUTION>(0.5, 2.0);
		EXPECT_TRUE(r4 >= 0.5 && r4 <= 2.0);
	}
}

//TEST(RandomTest, RandomString) {
//	std::string str = Random::GenString(10);
//	EXPECT_EQ(str.size(), 10);
//}

