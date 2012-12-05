#include <gtest/gtest.h>
#include <zbase/byteorder.h>
#include <zbase/inttypes.h>
using namespace zbase;

uint16_t u16         =             0x1122;
uint16_t u16_reverse =             0x2211;
int16_t  i16         =             0x1122;
int16_t  i16_reverse =             0x2211;
uint32_t u32         =         0x11223344;
uint32_t u32_reverse =         0x44332211;
int32_t  i32         =         0x11223344;
int32_t  i32_reverse =         0x44332211;
uint64_t u64         = 0x1122334455667788LL;
uint64_t u64_reverse = 0x8877665544332211LL;
int64_t  i64         = 0x1122334455667788LL;
int64_t  i64_reverse = 0x8877665544332211LL;

TEST(ByteOrderTest, HostToLittleEndian) {
	if (byteorder::kIsHostLE) {
		EXPECT_EQ(byteorder::HToLE(u16), u16);
		EXPECT_EQ(byteorder::HToLE(i16), i16);
		EXPECT_EQ(byteorder::HToLE(u32), u32);
		EXPECT_EQ(byteorder::HToLE(i32), i32);
		EXPECT_EQ(byteorder::HToLE(u64), u64);
		EXPECT_EQ(byteorder::HToLE(i64), i64);
	} else {
		EXPECT_EQ(byteorder::HToLE(u16), u16_reverse);
		EXPECT_EQ(byteorder::HToLE(i16), i16_reverse);
		EXPECT_EQ(byteorder::HToLE(u32), u32_reverse);
		EXPECT_EQ(byteorder::HToLE(i32), i32_reverse);
		EXPECT_EQ(byteorder::HToLE(u64), u64_reverse);
		EXPECT_EQ(byteorder::HToLE(i64), i64_reverse);
	}
}

TEST(ByteOrderTest, HostToBigEndian) {
	if (!byteorder::kIsHostLE) {
		EXPECT_EQ(byteorder::HToBE(u16), u16);
		EXPECT_EQ(byteorder::HToBE(i16), i16);
		EXPECT_EQ(byteorder::HToBE(u32), u32);
		EXPECT_EQ(byteorder::HToBE(i32), i32);
		EXPECT_EQ(byteorder::HToBE(u64), u64);
		EXPECT_EQ(byteorder::HToBE(i64), i64);
	} else {
		EXPECT_EQ(byteorder::HToBE(u16), u16_reverse);
		EXPECT_EQ(byteorder::HToBE(i16), i16_reverse);
		EXPECT_EQ(byteorder::HToBE(u32), u32_reverse);
		EXPECT_EQ(byteorder::HToBE(i32), i32_reverse);
		EXPECT_EQ(byteorder::HToBE(u64), u64_reverse);
		EXPECT_EQ(byteorder::HToBE(i64), i64_reverse);
	}
}

TEST(ByteOrderTest, LittleEndianToHost) {
	if (byteorder::kIsHostLE) {
		EXPECT_EQ(byteorder::HToLE(u16), u16);
		EXPECT_EQ(byteorder::HToLE(i16), i16);
		EXPECT_EQ(byteorder::HToLE(u32), u32);
		EXPECT_EQ(byteorder::HToLE(i32), i32);
		EXPECT_EQ(byteorder::HToLE(u64), u64);
		EXPECT_EQ(byteorder::HToLE(i64), i64);
	} else {
		EXPECT_EQ(byteorder::HToLE(u16), u16_reverse);
		EXPECT_EQ(byteorder::HToLE(i16), i16_reverse);
		EXPECT_EQ(byteorder::HToLE(u32), u32_reverse);
		EXPECT_EQ(byteorder::HToLE(i32), i32_reverse);
		EXPECT_EQ(byteorder::HToLE(u64), u64_reverse);
		EXPECT_EQ(byteorder::HToLE(i64), i64_reverse);
	}
}

TEST(ByteOrderTest, BigEndianToHost) {
	if (!byteorder::kIsHostLE) {
		EXPECT_EQ(byteorder::HToBE(u16), u16);
		EXPECT_EQ(byteorder::HToBE(i16), i16);
		EXPECT_EQ(byteorder::HToBE(u32), u32);
		EXPECT_EQ(byteorder::HToBE(i32), i32);
		EXPECT_EQ(byteorder::HToBE(u64), u64);
		EXPECT_EQ(byteorder::HToBE(i64), i64);
	} else {
		EXPECT_EQ(byteorder::HToBE(u16), u16_reverse);
		EXPECT_EQ(byteorder::HToBE(i16), i16_reverse);
		EXPECT_EQ(byteorder::HToBE(u32), u32_reverse);
		EXPECT_EQ(byteorder::HToBE(i32), i32_reverse);
		EXPECT_EQ(byteorder::HToBE(u64), u64_reverse);
		EXPECT_EQ(byteorder::HToBE(i64), i64_reverse);
	}
}

