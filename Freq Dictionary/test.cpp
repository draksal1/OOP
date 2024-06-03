#include "gtest/gtest.h"
#include "../freg_directory/Dictory.hpp"


//int main(int argc, char** argv) 
//{
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}


TEST(MapTest, EmptyStreamTest) 
{
    stringstream ss;
    ss << "";
    MapDictory test{};
    tokenize(ss, test);
    MapDictory s = MapDictory();
    EXPECT_EQ(test.GetResult(), s.GetResult());
}       

TEST(MapTest, SingleStreamTest)
{
    stringstream ss;
    ss << "1";
    MapDictory test{};
    tokenize(ss, test);
    MapDictory s = MapDictory();
    EXPECT_EQ(test.GetResult(), "1 1\n");
}

TEST(MapTest, ManyStreamTest)
{
    stringstream ss;
    ss << "1 1 1 5 5 stream ";
    MapDictory test{};
    tokenize(ss, test);
    MapDictory s = MapDictory();
    EXPECT_EQ(test.GetResult(), "1 3\n5 2\nstream 1\n");
}

TEST(MapTest, NWordTest)
{
    MapDictory test{};
    string s = "test";
    test.NWord(s);
    EXPECT_EQ(test.GetResult(), "test 1\n");
}

TEST(MapTest, NWordEmptyTest)
{
    MapDictory test{};
    string test1 = "";
    test.NWord(test1);
    EXPECT_TRUE(test.GetResult().empty());
}

TEST(MapTest, CountOfWordManyTest)
{
    MapDictory test{};
    test.NWord(string("test1"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    EXPECT_EQ(test.CountOfWord(string("test2")), 2);
    EXPECT_EQ(test.CountOfWord(string("test1")), 1);
    EXPECT_EQ(test.CountOfWord(string("primitezadachu")), 0);
}

TEST(MapTest, GetIterWordTest)
{
    MapDictory test{};
    test.NWord(string("test1"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    test.NWord(string("test3"));
    EXPECT_EQ(test.GetIterWord(0).second,1);
    EXPECT_EQ(test.GetIterWord(1).second, 3);
    EXPECT_EQ(test.GetIterWord(2).second, 1);

    EXPECT_EQ(test.GetIterWord(0).first, "test1");
    EXPECT_EQ(test.GetIterWord(1).first, "test2");
    EXPECT_EQ(test.GetIterWord(2).first, "test3");
    EXPECT_THROW(test.GetIterWord(3), out_of_range);
}

TEST(VectorTest, EmptyStreamTest)
{
    stringstream ss;
    ss << "";
    VectorDictory test{};
    tokenize(ss, test);
    VectorDictory s = VectorDictory();
    EXPECT_EQ(test.GetResult(), s.GetResult());
}

TEST(VectorTest, SingleStreamTest)
{
    stringstream ss;
    ss << "1";
    MapDictory test{};
    tokenize(ss, test);
    VectorDictory s = VectorDictory();
    EXPECT_EQ(test.GetResult(), "1 1\n");
}

TEST(VectorTest, ManyStreamTest)
{
    stringstream ss;
    ss << "1 1 1 5 5 stream ";
    VectorDictory test{};
    tokenize(ss, test);
    VectorDictory s = VectorDictory();
    EXPECT_EQ(test.GetResult(), "1 3\n5 2\nstream 1\n");
}

TEST(VectorTest, NWordTest)
{
    VectorDictory test{};
    test.NWord(string("test"));
    EXPECT_EQ(test.GetResult(), "test 1\n");
}

TEST(VectorTest, NWordEmptyTest)
{
    VectorDictory test{};
    test.NWord(string(""));
    EXPECT_TRUE(test.GetResult().empty());
}

TEST(VectorTest, CountOfWordManyTest)
{
    VectorDictory test{};
    test.NWord(string("test1"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    EXPECT_EQ(test.CountOfWord(string("test2")), 2);
    EXPECT_EQ(test.CountOfWord(string("test1")), 1);
    EXPECT_EQ(test.CountOfWord(string("primitezadachu")), 0);
}

TEST(VectorTest, GetIterWordTest)
{
    VectorDictory test{};
    test.NWord(string("test1"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    test.NWord(string("test3"));
    EXPECT_EQ(test.GetIterWord(0).second, 1);
    EXPECT_EQ(test.GetIterWord(1).second, 3);
    EXPECT_EQ(test.GetIterWord(2).second, 1);

    EXPECT_EQ(test.GetIterWord(0).first, "test1");
    EXPECT_EQ(test.GetIterWord(1).first, "test2");
    EXPECT_EQ(test.GetIterWord(2).first, "test3");
    EXPECT_THROW(test.GetIterWord(3), out_of_range);
}

TEST(ListTest, EmptyStreamTest)
{
    stringstream ss;
    ss << "";
    ListDictory test{};
    tokenize(ss, test);
    ListDictory s = ListDictory();
    EXPECT_EQ(test.GetResult(), s.GetResult());
}

TEST(ListTest, SingleStreamTest)
{
    stringstream ss;
    ss << "1";
    MapDictory test{};
    tokenize(ss, test);
    ListDictory s = ListDictory();
    EXPECT_EQ(test.GetResult(), "1 1\n");
}

TEST(ListTest, ManyStreamTest)
{
    stringstream ss;
    ss << "1 1 1 5 5 stream ";
    ListDictory test{};
    tokenize(ss, test);
    ListDictory s = ListDictory();
    EXPECT_EQ(test.GetResult(), "1 3\n5 2\nstream 1\n");
}

TEST(ListTest, NWordTest)
{
    ListDictory test{};
    test.NWord(string("test"));
    EXPECT_EQ(test.GetResult(), "test 1\n");
}

TEST(ListTest, NWordEmptyTest)
{
    ListDictory test{};
    test.NWord(string(""));
    EXPECT_TRUE(test.GetResult().empty());
}

TEST(ListTest, CountOfWordManyTest)
{
    ListDictory test{};
    test.NWord(string("test1"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    EXPECT_EQ(test.CountOfWord(string("test2")), 2);
    EXPECT_EQ(test.CountOfWord(string("test1")), 1);
    EXPECT_EQ(test.CountOfWord(string("primitezadachu")), 0);
}

TEST(ListTest, GetIterWordTest)
{
    ListDictory test{};
    test.NWord(string("test1"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    test.NWord(string("test2"));
    test.NWord(string("test3"));
    EXPECT_EQ(test.GetIterWord(0).second, 1);
    EXPECT_EQ(test.GetIterWord(1).second, 3);
    EXPECT_EQ(test.GetIterWord(2).second, 1);

    EXPECT_EQ(test.GetIterWord(0).first, "test1");
    EXPECT_EQ(test.GetIterWord(1).first, "test2");
    EXPECT_EQ(test.GetIterWord(2).first, "test3");
    EXPECT_THROW(test.GetIterWord(3), out_of_range);
}