#include "../FilterIterator/FilterIterator.h"
#include "gtest/gtest.h"
#include <array>
#include <deque>
#include <list>
#include <map>



//хранилище РАУ


//проверить, что предикат всегда фолс тогда end=begin
TEST(FilterRangeTest, Emptycase) {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered_range = iterators::filter_range(numbers.begin(), numbers.begin(), [](int num) { return num % 2 == 0; });
    auto test = filtered_range.begin();
    auto filtered_range2 = iterators::filter_range(numbers.end(), numbers.end(), [](int num) { return num % 2 == 0; });
    auto test2 = filtered_range2.begin();
    EXPECT_THROW(*test, std::out_of_range);
    EXPECT_THROW(*test2, std::out_of_range);


}


TEST(FilterRangeTest, SameBasicDifferentPredicate) {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered_range = iterators::filter_range(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });
    auto test = filtered_range.begin();
    auto filtered_range2 = iterators::filter_range(numbers.begin(), numbers.end(), [](int num) { return num < 5 && num > 1 ; });
    auto test2 = filtered_range2.begin();
    EXPECT_TRUE(!(test == test2));

}

TEST(FilterRangeTest, ConstPredicateFalse) {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered_range = iterators::filter_range(numbers.begin(), numbers.end(), [](int num) { return false; });
    EXPECT_TRUE(filtered_range.begin() == filtered_range.end());

}
TEST(FilterRangeTest, EvenNumbers) {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto filtered_range = iterators::filter_range(numbers.begin(), numbers.end(), [](int num) { return num % 2 == 0; });

    auto test = filtered_range.begin();

    EXPECT_EQ(*test++, 2);

    EXPECT_EQ(*test++, 4);

    EXPECT_EQ(*test++, 6);

    EXPECT_EQ(*test++, 8);

    EXPECT_EQ(*test++, 10);

    EXPECT_THROW(*test, std::out_of_range);


}
namespace RegFunction {
    bool is_long(const std::string& word) {
        return word.length() > 4;
    }
}
// Тест 2: Проверка фильтрации строк по длине
TEST(FilterRangeTest, StringLengthRegularFunction) {
    std::vector<std::string> words = { "hello", "world", "cpp", "openai", "gpt" };

    auto filtered_range = iterators::filter_range(words.begin(), words.end(), RegFunction::is_long);

    std::vector<std::string> expected_result = { "hello", "world", "openai" };
    auto test = filtered_range.begin();

    EXPECT_EQ(*test, expected_result[0]);

    ++test;
    EXPECT_EQ(*test, expected_result[1]);

    ++test;
    EXPECT_EQ(*test, expected_result[2]);

    ++test;
    EXPECT_EQ(test, filtered_range.end());
}

class StringLongOrNot
{
public:
    static bool is_long(const std::string& word) {
        return word.length() > 4;
    }
};


TEST(FilterRangeTest, StringLengthRFunctor) {
    std::vector<std::string> words = { "hello", "world", "cpp", "openai", "gpt" };

    auto filtered_range = iterators::filter_range(words.begin(), words.end(), StringLongOrNot::is_long);

    std::vector<std::string> expected_result = { "hello", "world", "openai" };
    auto test = filtered_range.begin();

    EXPECT_EQ(*test, expected_result[0]);

    ++test;
    EXPECT_EQ(*test, expected_result[1]);

    ++test;
    EXPECT_EQ(*test, expected_result[2]);

    ++test;
    EXPECT_EQ(test, filtered_range.end());
}
double square(double x)
{
    return x * x;
}

TEST(FilterRangeTest, TransformTest) {
    std::array<double, 10> test = {2.2, 5.5, 1.0, 10.5, 15.5, 3};
    auto filtered_range = iterators::filter_range(test.begin(), test.end(), [](double num) { return num > 4; });
    std::transform(filtered_range.begin(), filtered_range.end(), filtered_range.begin(), square);
    std::array<double, 10> expected{ 2.2, square(5.5), 1.0, square(10.5), square(15.5), 3 };
    EXPECT_EQ(test, expected);
}





TEST(FilterRangeTest, CopyTest) {
    std::deque<bool> data{ {true, false, false ,true, false, false} };
    auto filtered_range = iterators::filter_range(data.begin(), data.end(), [](bool it) { return it; });
    std::deque<bool> test({ false, false});
    std::copy(filtered_range.begin(), filtered_range.end(), test.begin());
    std::deque<bool> expected{ {true, true} };
    EXPECT_EQ(test, expected);
}

TEST(FilterRangeTest, Copy_ifTest) {
    std::list<long> data{ {1, 2, 5, 6532, 12, 554, 126, 775}};
    auto filtered_range = iterators::filter_range(data.begin(), data.end(), [](long it) { return it%5==0; });
    std::deque<long> test(1);
    std::copy_if(filtered_range.begin(), filtered_range.end(), test.begin(), [](long it) { return it > 5; });
    std::deque<long> expected{ {775} };
    EXPECT_EQ(test, expected);
}



TEST(FilterRangeTest, MapTestKeys) {
     std::map<long long, float> myMap= { {1, 1.0f}, {2, 2.0f}, {3, 3.0f}, {4, 4.0f}, {5, 5.0f}};



    iterators::filter_range filter(myMap.begin(), myMap.end(), [](const std::pair<long long, float>& pair) { return pair.first % 2 == 0;});

    
    for (auto it = filter.begin(); it != filter.end();it++) {
        
        EXPECT_TRUE( (* it).first % 2 == 0);
    }
}


template <typename T>
struct Predicate {
    T a{};

    Predicate(const T& a_) : a{ a_ } {}

    bool operator()(const T& v) {
        return v < a;
    }
};

TEST(FilterRangeTest, TemplateFunctor) {
    size_t A = 15;
    Predicate<size_t> Pred{ A };
    std::vector<size_t> values = { 1, 2, 4, 16, 17, 2, 1, 16 };
    iterators::filter_range filter(values.begin(), values.end(), Pred);
    auto test = filter.begin();
    EXPECT_EQ(*test++, 1);
    EXPECT_EQ(*test++, 2);
    EXPECT_EQ(*test++, 4);
    EXPECT_EQ(*test++, 2);
    EXPECT_EQ(*test++, 1);
}