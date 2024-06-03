#include "gtest/gtest.h"
#include "pquicksort.hpp"
#include<deque>
#include<array>


class SchemePolicy {
public:
    int GetThreads(ptrdiff_t size) const {
        return 3;
    }
};




TEST(PQuickSort, SortsVectorInt) {
    std::vector<int> data = { 9, 3, 1, 4, 1, 5 , 2, 6, 5, 3};
    SchemePolicy scheme;

    parallel::sort1(data.begin(), data.end(), scheme);

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}




TEST(PQuickSort, SortsSingleElement) {
    std::vector<int> data = { 42 };
    SchemePolicy scheme;

    parallel::sort1(data.begin(), data.end(), scheme);

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}


TEST(PQuickSort, SortsDequeDoubleWithGreaterComp) {
    std::deque<double> data = { 9.5, 3.12, 1.6, 4.9, 1.243, 5.1 , 2.2, 6.76, 5.5, 3.3, 12.5, 70.5, 132.34, 666.23, 9.5, 3.12, 1.6, 4.9, 1.243, 5.1 , 2.2, 6.76, 5.5, 3.3, 12.5, 70.5, 132.34, 666.23 };
    SchemePolicy scheme;

    parallel::sort2(data.begin(), data.end(), std::greater<>(),  scheme);

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end(), std::greater<>()));
}

TEST(PQuickSort, SortsArrayFloat) {
    std::deque<double> data = { 9.5f, 3.12f, 1.6f, 4.9f, 1.243f, 5.1f, 2.2f, 6.76f, 5.5f, 3.3f, 12.5f, 70.5f, 132.34f, 666.23f, 9.5f, 3.12f, 1.6f, 4.9f, 1.243f, 5.1f , 2.2f, 6.76f, 5.5f, 3.3f, 12.5f, 70.5f, 132.34f, 666.23f };
    SchemePolicy scheme;

    parallel::sort1(data.begin(), data.end(), scheme);

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}