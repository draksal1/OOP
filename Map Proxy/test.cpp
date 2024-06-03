#include "gtest/gtest.h"
#include "../MapProxy/ProxiedMap.hpp"
using namespace std;

TEST(ProxiedMapTest, ConstructorsTest) 
{
	const map<string, size_t> keys{};
	AllRoots first;
	map<std::string, size_t> test;
	test.insert({ "1", 1 });
	test.insert({ "2", 1 });
	test.insert({ "3", 1 });
	ProxiedMap Map(test, first);

	EXPECT_EQ(Map.read("1"), 1);
	EXPECT_EQ(Map.read("2"), 1);
	EXPECT_EQ(Map.read("3"), 1);
}




TEST(ProxiedMapTest, RootsTest)
{
	AllRoots first;
	EditRoots second = EditRoots(std::map<string, size_t>(), std::map<string, size_t>());
	OnlyReadRoots third;
	map<std::string, size_t> test;
	test.insert({ "1", 1 });
	test.insert({ "2", 1 });
	test.insert({ "3", 1 });
	ProxiedMap Map(test, first);
	ProxiedMap Map2(test, second);
	ProxiedMap Map3(test, third);

	EXPECT_EQ(Map.read("1"), 1);

	EXPECT_THROW(Map2.read("1"), runtime_error);

	EXPECT_THROW(Map3.edit("1", 5), runtime_error);

}