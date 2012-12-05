#include <gtest/gtest.h>
#include <zbase/octets.h>
using namespace zbase;

TEST(OctetsTest, DefaultConstructor) {
	Octets o;
	EXPECT_EQ(o.GetData(), (void*)NULL);
	EXPECT_EQ(o.GetSize(), 0U);
	EXPECT_TRUE(o.IsEmpty());
}

TEST(OctetsTest, ConstructorWithData) {
	char buf[] = "test";
	Octets o(buf, sizeof(buf));
	EXPECT_EQ(o.GetSize(), sizeof(buf));
	EXPECT_FALSE(o.IsEmpty());
	EXPECT_TRUE(memcmp(o.GetData(), buf, o.GetSize()) == 0);
}

TEST(OctetsTest, CopyConstructor) {
	char buf[] = "test";
	Octets o1(buf, sizeof(buf));
	Octets o2(o1);
	EXPECT_EQ(o1.GetSize(), o2.GetSize());
	EXPECT_EQ(o1.Compare(o2), 0);
	EXPECT_EQ(o2.Compare(o1), 0);
}

TEST(OctetsTest, AssignmentOperator) {
	std::string str("test");
	Octets o1(str.c_str(), str.size());
	Octets o2 = o1;
	Octets o3 = str;
	EXPECT_EQ(o1.GetSize(), o2.GetSize());
	EXPECT_EQ(o1.GetSize(), o3.GetSize());
	EXPECT_EQ(o1.Compare(o2), 0);
	EXPECT_EQ(o2.Compare(o1), 0);
	EXPECT_EQ(o2.Compare(o3), 0);
	EXPECT_EQ(o3.Compare(o2), 0);
	EXPECT_EQ(o1.Compare(o3), 0);
	EXPECT_EQ(o3.Compare(o1), 0);
}

TEST(OctetsTest, RelationalOperator) {
	std::string str1("aaad");
	std::string str2("abc");
	Octets o1(str1.c_str(), str1.size());
	Octets o2(str2.c_str(), str2.size());
	Octets o3(str1.c_str(), str1.size());
	EXPECT_TRUE(o1 < o2);
	EXPECT_TRUE(o2 > o1);
	EXPECT_TRUE(o1 <= o2);
	EXPECT_TRUE(o2 >= o1);
	EXPECT_TRUE(o1 != o2);
	EXPECT_TRUE(o1 == o3);
}

TEST(OctetsTest, DataModifier) {
	std::string str1("a");
	std::string str2("b");
	std::string str3("ab");
	Octets o1(str1.c_str(), str1.size());
	Octets o2;
	o2.Assign(str1.c_str(), str1.size());
	EXPECT_TRUE(o1 == o2);
	Octets o3(str3.c_str(), str3.size());
	o1.Append(str2.c_str(), str2.size());
	EXPECT_TRUE(o1 == o3);
	o1.Assign(str1.c_str(), str1.size());
	o2.Assign(str2.c_str(), str2.size());
	o1.Append(o2);
	EXPECT_TRUE(o1 == o3);
}

