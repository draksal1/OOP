#include "gtest/gtest.h"
#include "../Gistogramm/parcer.hpp"
#include "../Gistogramm/Gystogramm.hpp"
#include <stdexcept>

TEST(ParserTest, Empty) {
	stringstream s;
	s << "";
	Gystogramm test{};
	parse(s, test);
	EXPECT_EQ(test, Gystogramm());
}



TEST(ParserTest, OneElement) {
	stringstream s;
	s << "1";
	Gystogramm test{};
	parse(s, test);
	EXPECT_EQ(1, test.at("1"));
}

TEST(ParserTest, ManyElements) {
	stringstream s;
	s << "1 1 1 2 2 2 3 3 3";
	Gystogramm test{};
	parse(s, test);
	EXPECT_EQ(3, test.at("1"));
	EXPECT_EQ(3, test.at("2"));
	EXPECT_EQ(3, test.at("3"));
}


TEST(GystogrammTest, ConstructorsTestEmpty) 
{
	Gystogramm a = Gystogramm();
	Gystogramm b({});
	Gystogramm c(b);	
	EXPECT_FALSE(a.get_size());
	EXPECT_FALSE(b.get_size());
	EXPECT_FALSE(c.get_size());
}

TEST(GystogrammTest, ConstructorsTestSingle)
{
	Gystogramm b({"1"});
	Gystogramm c(b);
	EXPECT_EQ(b.get_size(), 1);
	EXPECT_EQ(c.get_size(), 1);
}

TEST(GystogrammTest, ConstructorsTestMany)
{
	Gystogramm b({ "1", "2", "3"});
	Gystogramm c(b);
	EXPECT_EQ(b.get_size(), 3);
	EXPECT_EQ(c.get_size(), 3);
}

//size_t get_size() const { return data_.size(); }
//void AddWord(const string& s);
//const size_t& at(const std::string& str) const;
//string GetResult();

TEST(GystogrammTest, get_size)
{
	Gystogramm b({ "1", "2", "3" });
	EXPECT_EQ(b.get_size(), 3);
}

TEST(GystogrammTest, AddWord)
{
	Gystogramm b({ "1", "2", "3" });
	b.AddWord(string("1"));
	EXPECT_EQ(b.at(string("1")), 2);
	b.AddWord(string("4"));
	EXPECT_EQ(b.at(string("4")), 1);
}

TEST(GystogrammTest, At)
{
	Gystogramm b({ "1", "2", "3" });
	
	EXPECT_EQ(b.at(string("1")), 1);

	EXPECT_EQ(b.at(string("2")), 1);

	EXPECT_EQ(b.at(string("3")), 1);

	EXPECT_THROW(b.at("4"), out_of_range);

	EXPECT_THROW(b.at("0"), out_of_range);
}

TEST(GystogrammTest, GetResult)
{
	Gystogramm b({ "1", "2", "3" });

	string test = "1 1\n2 1\n3 1\n";

	EXPECT_EQ(b.GetResult(), test);
}


TEST(GystogrammTest, PlusTestEmpty)
{
	Gystogramm a = Gystogramm();
	Gystogramm b = Gystogramm({ "1" });
	Gystogramm result = a+b;
	Gystogramm result2 = b + a;
	EXPECT_EQ(result, Gystogramm({ "1" }));
	EXPECT_EQ(result2, Gystogramm({ "1" }));
}

TEST(GystogrammTest, PlusTestSingle)
{
	Gystogramm a = Gystogramm({ "1" });
	Gystogramm b = Gystogramm({ "1" });
	Gystogramm result = a + b;
	EXPECT_EQ(result, Gystogramm({"1", "1"}));
}

TEST(GystogrammTest, PlusTestMany)
{
	Gystogramm a = Gystogramm({ "1", "1", "1", "2", "2" , "2" , "3", "3" });
	Gystogramm b = Gystogramm({ "4", "6", "1"});
	Gystogramm result = a + b;
	
	EXPECT_EQ(result.at("1"), 4);

	EXPECT_EQ(result.at("2"), 3);

	EXPECT_EQ(result.at("3"), 2);

	EXPECT_EQ(result.at("4"), 1);

	EXPECT_EQ(result.at("6"), 1);
}

TEST(GystogrammTest, Plus)

{

	Gystogramm a = Gystogramm({ "1", "1", "1" });

	Gystogramm b = a;

	Gystogramm result = a + b;

	EXPECT_EQ(result.begin()->second, 6);

	EXPECT_EQ(result.begin()->first, "1");

}
TEST(GystogrammTest, MinusTestEmpty)
{
	Gystogramm a = Gystogramm();
	Gystogramm b = Gystogramm({ "1" });
	Gystogramm result = a - b;
	EXPECT_EQ(result, Gystogramm());
	Gystogramm result2 = b - a;
	EXPECT_EQ(result2, Gystogramm({ "1" }));
}

TEST(GystogrammTest, MinusTestSingle)
{
	Gystogramm a = Gystogramm({ "1" });
	Gystogramm b = Gystogramm({ "1" });
	Gystogramm result = a - b;
	EXPECT_EQ(result, Gystogramm());
}

TEST(GystogrammTest, MinusTestMany)
{
	Gystogramm a = Gystogramm({ "1", "1", "1", "2", "2" , "2" , "3", "3" });
	Gystogramm b = Gystogramm({ "4", "6", "1" });
	Gystogramm result = a - b;

	EXPECT_EQ(result.at("1"), 2);

	EXPECT_EQ(result.at("2"), 3);

	EXPECT_EQ(result.at("3"), 2);
}


TEST(GystogrammTest, Minus)

{

	Gystogramm a = Gystogramm({ "1" });

	Gystogramm b = Gystogramm({ "1", "1" });

	Gystogramm result = a - b;

	EXPECT_EQ(result.begin(), result.end());

	EXPECT_EQ(result, Gystogramm());

}

TEST(GystogrammTest, Assign)
{
	Gystogramm a{}, b{};
	b = a;
	EXPECT_EQ(b, Gystogramm());

	a = Gystogramm({ "1","1","1","2" });

	EXPECT_EQ(a.at("1"), 3);

	EXPECT_EQ(a.at("2"), 1);

	b = a;

	EXPECT_EQ(b.at("1"), 3);

	EXPECT_EQ(b.at("2"), 1);

}

TEST(GystogrammTest, BeginAndEndEmpty)
{
	Gystogramm a{};
	auto s = a.begin();
	EXPECT_EQ(a.begin(), a.end());
}

TEST(GystogrammTest, BeginAndEndSingle)
{
	Gystogramm a({"1"});
	auto testbeg = a.begin();
	auto testend = a.end();
	EXPECT_EQ(testbeg->first, "1");
	EXPECT_EQ(testbeg->second, 1);
	EXPECT_EQ(++testbeg, testend);
}

TEST(GystogrammTest, BeginAndEndMany)
{
	Gystogramm a({ "1", "2", "3", "4"});
	auto testbeg = a.begin();
	auto testend = a.end();
	EXPECT_EQ(testbeg->first, "1");
	EXPECT_EQ(testbeg->second, 1);
	++testbeg;
	EXPECT_EQ(testbeg->first, "2");
	EXPECT_EQ(testbeg->second, 1);
	++testbeg;
	EXPECT_EQ(testbeg->first, "3");
	EXPECT_EQ(testbeg->second, 1);
	++testbeg;
	EXPECT_EQ(testbeg->first, "4");
	EXPECT_EQ(testbeg->second, 1);
	++testbeg;
	EXPECT_EQ(testbeg, testend);
}

TEST(GystogrammTest, AssignSame)

{

	Gystogramm a{ { "1","1","1","2" } };

	Gystogramm b{};

	b = a;

	EXPECT_EQ(b, a);



	b = b;

	EXPECT_EQ(b.get_size(), a.get_size());

	EXPECT_EQ(b, a);

}