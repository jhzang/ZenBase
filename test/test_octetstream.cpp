#include <gtest/gtest.h>
#include <zbase/octetstream.h>
using namespace zbase;

TEST(OctetStreamTest, DefaultConstructor) {
	OctetStream os;
	EXPECT_FALSE(os.IsAttachMode());
	EXPECT_TRUE(os.GetSize() == 0);
	EXPECT_TRUE(os.IsEmpty());
	EXPECT_TRUE(NULL == os.GetData());
	EXPECT_TRUE(NULL == os.begin());
	EXPECT_TRUE(NULL == os.end());
}

TEST(OctetStreamTest, Constructor1) {
	std::string str("hello");
	OctetStream os(str.c_str(), str.size());
	EXPECT_FALSE(os.IsAttachMode());
	EXPECT_FALSE(os.IsEmpty());
	EXPECT_TRUE(os.GetSize() == str.size());
	EXPECT_TRUE(os.GetData() == os.begin());
	EXPECT_TRUE((size_t)(static_cast<const char*>(os.end()) - static_cast<const char*>(os.begin())) == os.GetSize());
	EXPECT_TRUE(memcmp(os.GetData(), str.c_str(), str.size()) == 0);
}

TEST(OctetStreamTest, Constructor2) {
	Octets str("hello");
	OctetStream os(str);
	EXPECT_FALSE(os.IsAttachMode());
	EXPECT_FALSE(os.IsEmpty());
	EXPECT_TRUE(os.GetSize() == str.GetSize());
	EXPECT_TRUE(os.GetData() == os.begin());
	EXPECT_TRUE((size_t)(static_cast<const char*>(os.end()) - static_cast<const char*>(os.begin())) == os.GetSize());
	EXPECT_TRUE(memcmp(os.GetData(), str.GetData(), str.GetSize()) == 0);
}

TEST(OctetStreamTest, CopyConstructor) {
	char buf[] = "hello";
	OctetStream os1(buf, strlen(buf));
	OctetStream os2(os1);
	EXPECT_TRUE(os1.GetSize() == os2.GetSize());
	EXPECT_TRUE(memcmp(os1.GetData(), os2.GetData(), os1.GetSize()) == 0);
}

TEST(OctetStreamTest, AssignmentOperator) {
	char buf[] = "hello";
	OctetStream os1(buf, strlen(buf));
	OctetStream os2 = os1;
	EXPECT_TRUE(os1.GetSize() == os2.GetSize());
	EXPECT_TRUE(memcmp(os1.GetData(), os2.GetData(), os1.GetSize()) == 0);
}

TEST(OctetStreamTest, AttachMode) {
	char buf[] = "hello";
	{
		OctetStream os(buf, strlen(buf), true);
		EXPECT_TRUE(os.IsAttachMode());
	}
}

TEST(OctetStreamTest, BlockReadWrite) {
	std::string str1("hello");
	std::string str2("C++ world");
	char buf[16] = {0};
	OctetStream os(str1.c_str(), str1.size());
	// block write
	os.Write(str2.c_str(), str2.size());
	EXPECT_TRUE(os.GetSize() == str1.size() + str2.size());
	// block read
	os.Read(buf, 5);
	EXPECT_TRUE(str1 == buf);
	EXPECT_TRUE(os.GetSize() == str2.size());
	EXPECT_TRUE(memcmp(os.GetData(), str2.c_str(), str2.size()) == 0);
	// unget
	os.Unget(5);
	EXPECT_TRUE(os.GetSize() == str1.size() + str2.size());
	os.Unget(5);
	EXPECT_TRUE(os.GetSize() == str1.size() + str2.size());
	// ignore
	os.Ignore(5);
	EXPECT_TRUE(os.GetSize() == str2.size());
}

TEST(OctetStreamTest, BasicInsertionAndExtraction) {
	bool v1 = true, v2 = false;
	int8_t v3 = -100;
	uint8_t v4 = 255;
	int16_t v5 = -100;
	uint16_t v6 = 65535;
	int32_t v7 = -1234567890;
	uint32_t v8 = 1234567890;
	int64_t v9 = -123456789;
	uint64_t v10 = 1234567890;
	float v11 = -123.45;
	double v12 = -123456.7890;
	long double v13 = -123456.7890;
	Octets v14("test");
	std::string v15("test");
	OctetStream os;
	os << v1 << v2 << v3 << v4 << v5 << v6 << v7 << v8 << v9 << v10 << v11 << v12 << v13 << v14 << v15;
	bool t1, t2;
	int8_t t3;
	uint8_t t4;
	int16_t t5;
	uint16_t t6;
	int32_t t7;
	uint32_t t8;
	int64_t t9;
	uint64_t t10;
	float t11;
	double t12;
	long double t13;
	Octets t14;
	std::string t15;
	os >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7 >> t8 >> t9 >> t10 >> t11 >> t12 >> t13 >> t14 >> t15;
	EXPECT_TRUE(v1 == t1);
	EXPECT_TRUE(v2 == t2);
	EXPECT_TRUE(v3 == t3);
	EXPECT_TRUE(v4 == t4);
	EXPECT_TRUE(v5 == t5);
	EXPECT_TRUE(v6 == t6);
	EXPECT_TRUE(v7 == t7);
	EXPECT_TRUE(v8 == t8);
	EXPECT_TRUE(v9 == t9);
	EXPECT_TRUE(v10 == t10);
	EXPECT_TRUE(v11 == t11);
	EXPECT_TRUE(v12 == t12);
	EXPECT_TRUE(v12 == t12);
	EXPECT_TRUE(v13 == t13);
	EXPECT_TRUE(v14 == t14);
	EXPECT_TRUE(v15 == t15);
}

TEST(OctetStreamTest, byteorder) {
	int v1 = -100;
	int v2 = byteorder::HToLE(v1);
	int v3 = byteorder::HToBE(v1);
	OctetStream os;
	os << v1 << v2 << v3;
	int t1, t2, t3;
	os >> t1 >> t2 >> t3;
	EXPECT_TRUE(v1 == t1);
	EXPECT_TRUE(v2 == t2);
	EXPECT_TRUE(v3 == t3);
	if (byteorder::kIsHostLE) {
		EXPECT_TRUE(v1 == t2);
		EXPECT_FALSE(v1 == t3);
	}
	else {
		EXPECT_FALSE(v1 == t2);
		EXPECT_TRUE(v1 == t3);
	}
}

TEST(OctetStreamTest, InsertionAndExtraction_vector) {
	std::vector<int> data1, data2;
	for (int i = -3; i <= 3; ++i) {
		data1.push_back(i);
	}
	OctetStream os;
	os << data1;
	os >> data2;
	EXPECT_TRUE(data1.size() == data2.size());
	for (size_t i = 0; i < data1.size(); ++i) {
		EXPECT_TRUE(data1[i] == data2[i]);
	}
}

TEST(OctetStreamTest, InsertionAndExtraction_list) {
	std::list<int> data1, data2;
	std::list<int>::iterator it1, it2;
	for (int i = -3; i <= 3; ++i) {
		data1.insert(data1.end(), i);
	}
	OctetStream os;
	os << data1;
	os >> data2;
	EXPECT_TRUE(data1.size() == data2.size());
	it1 = data1.begin();
	it2 = data2.begin();
	for (size_t i = 0; i < data1.size(); ++i) {
		EXPECT_TRUE(*it1 == *it2);
		++it1;
		++it2;
	}
}

TEST(OctetStreamTest, InsertionAndExtraction_deque) {
	std::deque<int> data1, data2;
	for (int i = -3; i <= 3; ++i) {
		data1.push_back(i);
	}
	OctetStream os;
	os << data1;
	os >> data2;
	EXPECT_TRUE(data1.size() == data2.size());
	for (size_t i = 0; i < data1.size(); ++i) {
		EXPECT_TRUE(data1[i] == data2[i]);
	}
}

TEST(OctetStreamTest, InsertionAndExtraction_set) {
	std::set<int> data1, data2;
	std::set<int>::iterator it1, it2;
	for (int i = -3; i <= 3; ++i) {
		data1.insert(i);
	}
	OctetStream os;
	os << data1;
	os >> data2;
	EXPECT_TRUE(data1.size() == data2.size());
	it1 = data1.begin();
	it2 = data2.begin();
	for (size_t i = 0; i < data1.size(); ++i) {
		EXPECT_TRUE(*it1 == *it2);
		++it1;
		++it2;
	}
}

TEST(OctetStreamTest, InsertionAndExtraction_multiset) {
	std::multiset<int> data1, data2;
	std::multiset<int>::iterator it1, it2;
	for (int i = -3; i <= 3; ++i) {
		data1.insert(i);
		data1.insert(i);
	}
	OctetStream os;
	os << data1;
	os >> data2;
	EXPECT_TRUE(data1.size() == data2.size());
	it1 = data1.begin();
	it2 = data2.begin();
	for (size_t i = 0; i < data1.size(); ++i) {
		EXPECT_TRUE(*it1 == *it2);
		++it1;
		++it2;
	}
}

TEST(OctetStreamTest, InsertionAndExtraction_pair) {
	std::pair<int, int> data1, data2;
	data1 = std::make_pair(100, -100);
	OctetStream os;
	os << data1;
	os >> data2;
	EXPECT_TRUE(data1 == data2);
}

TEST(OctetStreamTest, InsertionAndExtraction_map) {
	std::map<int, int> data1, data2;
	std::map<int,int>::iterator it1, it2;
	for (int i = -3; i <= 3; ++i) {
		data1.insert(std::make_pair(i,i));
	}
	OctetStream os;
	os << data1;
	os >> data2;
	EXPECT_TRUE(data1.size() == data2.size());
	it1 = data1.begin();
	it2 = data2.begin();
	for (size_t i = 0; i < data1.size(); ++i) {
		EXPECT_TRUE(it1->first == it2->first);
		EXPECT_TRUE(it1->second == it2->second);
		++it1;
		++it2;
	}
}

TEST(OctetStreamTest, InsertionAndExtraction_multimap) {
	std::multimap<int, int> data1, data2;
	std::multimap<int,int>::iterator it1, it2;
	for (int i = -3; i <= 3; ++i) {
		data1.insert(std::make_pair(i,i));
		data1.insert(std::make_pair(i,2*i));
	}
	OctetStream os;
	os << data1;
	os >> data2;
	EXPECT_TRUE(data1.size() == data2.size());
	it1 = data1.begin();
	it2 = data2.begin();
	for (size_t i = 0; i < data1.size(); ++i) {
		EXPECT_TRUE(it1->first == it2->first);
		EXPECT_TRUE(it1->second == it2->second);
		++it1;
		++it2;
	}
}

