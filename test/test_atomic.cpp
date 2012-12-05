#include <gtest/gtest.h>
#include <zbase/atomic.h>
#include <zbase/inttypes.h>
using namespace zbase;

TEST(AtomicTest, FetchAndAdd) {
	int32_t value10 = 100;
	int32_t value11 = value10;
	int32_t value12 = 100;
	int32_t value13 = 200;
	int64_t value20 = 100;
	int64_t value21 = value20;
	int64_t value22 = 100;
	int64_t value23 = 200;
	EXPECT_EQ(atomic::FetchAndAdd(&value11, value12), value10);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::FetchAndAdd(&value21, value22), value20);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, FetchAndSub) {
	int32_t value10 = 100;
	int32_t value11 = value10;
	int32_t value12 = 100;
	int32_t value13 = 0;
	int64_t value20 = 100;
	int64_t value21 = value20;
	int64_t value22 = 100;
	int64_t value23 = 0;
	EXPECT_EQ(atomic::FetchAndSub(&value11, value12), value10);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::FetchAndSub(&value21, value22), value20);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, FetchAndInc) {
	int32_t value10 = 0;
	int32_t value11 = value10;
	int32_t value12 = 1;
	int64_t value20 = 0;
	int64_t value21 = value20;
	int64_t value22 = 1;
	EXPECT_EQ(atomic::FetchAndInc(&value11), value10);
	EXPECT_EQ(value11, value12);
	EXPECT_EQ(atomic::FetchAndInc(&value21), value20);
	EXPECT_EQ(value21, value22);
}

TEST(AtomicTest, FetchAndDec) {
	int32_t value10 = 0;
	int32_t value11 = value10;
	int32_t value12 = -1;
	int64_t value20 = 0;
	int64_t value21 = value20;
	int64_t value22 = -1;
	EXPECT_EQ(atomic::FetchAndDec(&value11), value10);
	EXPECT_EQ(value11, value12);
	EXPECT_EQ(atomic::FetchAndDec(&value21), value20);
	EXPECT_EQ(value21, value22);
}

TEST(AtomicTest, AddAndFetch) {
	int32_t value11 = 100;
	int32_t value12 = 100;
	int32_t value13 = 200;
	int64_t value21 = 100;
	int64_t value22 = 100;
	int64_t value23 = 200;
	EXPECT_EQ(atomic::AddAndFetch(&value11, value12), value13);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::AddAndFetch(&value21, value22), value23);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, SubAndFetch) {
	int32_t value11 = 100;
	int32_t value12 = 100;
	int32_t value13 = 0;
	int64_t value21 = 100;
	int64_t value22 = 100;
	int64_t value23 = 0;
	EXPECT_EQ(atomic::SubAndFetch(&value11, value12), value13);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::SubAndFetch(&value21, value22), value23);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, IncAndFetch) {
	int32_t value11 = 0;
	int32_t value12 = 1;
	int64_t value21 = 0;
	int64_t value22 = 1;
	EXPECT_EQ(atomic::IncAndFetch(&value11), value12);
	EXPECT_EQ(value11, value12);
	EXPECT_EQ(atomic::IncAndFetch(&value21), value22);
	EXPECT_EQ(value21, value22);
}

TEST(AtomicTest, DecAndFetch) {
	int32_t value11 = 0;
	int32_t value12 = -1;
	int64_t value21 = 0;
	int64_t value22 = -1;
	EXPECT_EQ(atomic::DecAndFetch(&value11), value12);
	EXPECT_EQ(value11, value12);
	EXPECT_EQ(atomic::DecAndFetch(&value21), value22);
	EXPECT_EQ(value21, value22);
}

TEST(AtomicTest, FetchAndAnd) {
	uint32_t value10 = 0x00FF00FF;
	uint32_t value11 = value10;
	uint32_t value12 = 0xFF00FF00;
	uint32_t value13 = 0x00000000;
	uint64_t value20 = 0x00FF00FF00FF00FFLL;
	uint64_t value21 = value20;
	uint64_t value22 = 0xFF00FF00FF00FF00LL;
	uint64_t value23 = 0x0000000000000000LL;
	EXPECT_EQ(atomic::FetchAndAnd(&value11, value12), value10);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::FetchAndAnd(&value21, value22), value20);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, FetchAndOr) {
	uint32_t value10 = 0x00FF00FF;
	uint32_t value11 = value10;
	uint32_t value12 = 0xFF00FF00;
	uint32_t value13 = 0xFFFFFFFF;
	uint64_t value20 = 0x00FF00FF00FF00FFLL;
	uint64_t value21 = value20;
	uint64_t value22 = 0xFF00FF00FF00FF00LL;
	uint64_t value23 = 0xFFFFFFFFFFFFFFFFLL;
	EXPECT_EQ(atomic::FetchAndOr(&value11, value12), value10);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::FetchAndOr(&value21, value22), value20);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, FetchAndXor) {
	uint32_t value10 = 0x00FF00FF;
	uint32_t value11 = value10;
	uint32_t value12 = 0xFF00FF00;
	uint32_t value13 = 0xFFFFFFFF;
	uint64_t value20 = 0x00FF00FF00FF00FFLL;
	uint64_t value21 = value20;
	uint64_t value22 = 0xFF00FF00FF00FF00LL;
	uint64_t value23 = 0xFFFFFFFFFFFFFFFFLL;
	EXPECT_EQ(atomic::FetchAndXor(&value11, value12), value10);
	EXPECT_EQ(value11, value13); 
	EXPECT_EQ(atomic::FetchAndXor(&value21, value22), value20);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, AndAndFetch) {
	uint32_t value11 = 0x00FF00FF;
	uint32_t value12 = 0xFF00FF00;
	uint32_t value13 = 0x00000000;
	uint64_t value21 = 0x00FF00FF00FF00FFLL;
	uint64_t value22 = 0xFF00FF00FF00FF00LL;
	uint64_t value23 = 0x0000000000000000LL;
	EXPECT_EQ(atomic::AndAndFetch(&value11, value12), value13);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::AndAndFetch(&value21, value22), value23);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, OrAndFetch) {
	uint32_t value11 = 0x00FF00FF;
	uint32_t value12 = 0xFF00FF00;
	uint32_t value13 = 0xFFFFFFFF;
	uint64_t value21 = 0x00FF00FF00FF00FFLL;
	uint64_t value22 = 0xFF00FF00FF00FF00LL;
	uint64_t value23 = 0xFFFFFFFFFFFFFFFFLL;
	EXPECT_EQ(atomic::OrAndFetch(&value11, value12), value13);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::OrAndFetch(&value21, value22), value23);
	EXPECT_EQ(value21, value23);
}

TEST(AtomicTest, XorAndFetch) {
	uint32_t value11 = 0x00FF00FF;
	uint32_t value12 = 0xFF00FF00;
	uint32_t value13 = 0xFFFFFFFF;
	uint64_t value21 = 0x00FF00FF00FF00FFLL;
	uint64_t value22 = 0xFF00FF00FF00FF00LL;
	uint64_t value23 = 0xFFFFFFFFFFFFFFFFLL;
	EXPECT_EQ(atomic::XorAndFetch(&value11, value12), value13);
	EXPECT_EQ(value11, value13);
	EXPECT_EQ(atomic::XorAndFetch(&value21, value22), value23);
	EXPECT_EQ(value21, value23);
}

