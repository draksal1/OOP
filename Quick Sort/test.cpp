#include "gtest/gtest.h"
#include "QuickSort.h"
#include <vector>
#include <deque>
#include <array>
#include <math.h>



TEST(DefaultContainers, Emptyvector)
{
	std::vector<int> Test{};
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_EQ(Test, std::vector<int>{});
}

TEST(DefaultContainers, SingleElementvector) 
{
	std::vector<int> Test{1};
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_EQ(Test, std::vector<int>{1});
}

TEST(DefaultContainers, TwoElementsvector)
{
	std::vector<int> Test{ {13, 2} };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}

TEST(DefaultContainers, vector) {
	std::vector<std::string> Test{{"one", "two", "three", "four"}};
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}

TEST(DefaultContainers, vectorBig) {
	std::vector<int> Test{ {52, 42, 78, 13, 48, 28, 35, 26, 72, 8, 62, 39, 7, 36, 70, 13, 72, 65, 90, 43, 46, 53, 57, 72, 61, 11, 2, 19, 12, 63, 98, 64, 5, 76, 77, 53, 4, 11, 78, 76, 18, 39, 14, 25, 75, 83, 38, 46, 48, 27, 88, 93, 80, 45, 65, 41, 55, 66, 59, 67, 29, 57, 30, 34, 32, 6, 86, 35, 17, 63, 10, 35, 2, 24, 59, 77, 6, 97, 22, 54, 24, 10, 47, 4, 55, 11, 44, 9, 76, 3, 75, 5, 59, 5, 38, 91, 11, 23, 25, 27} };
	quicksort::sort(Test.begin(), Test.end());

	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}

TEST(DefaultContainers, EmptyDeque)
{
	std::deque<int> Test{};
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_EQ(Test, std::deque<int>{});
}

TEST(DefaultContainers, SingleElementDeque)
{
	std::deque<int> Test{ 1 };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_EQ(Test, std::deque<int>{1});
}

TEST(DefaultContainers, Deque) {
	std::deque<bool> Test{ {true, false, false ,true, false, false} };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}




TEST(DefaultContainers, EmptyArray)
{
	std::array<int, 1> Test{ {} };
	quicksort::sort(Test.begin(), Test.end());
	std::array<int, 1> Expectation{ {} };
	EXPECT_EQ(Test, Expectation);
}

TEST(DefaultContainers, SingleElementArray)
{
	std::array<int, 1> Test{ 1 };
	quicksort::sort(Test.begin(), Test.end());
	std::array<int, 1> Expectation{ 1 };
	EXPECT_EQ(Test, Expectation);
}

TEST(DefaultContainers, Array) {
	std::array<char, 6> Test{  'a', 'b', 'k', 'a', '7', '2' };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}




TEST(DefaultContainers, EmptyvectorWithLessComparator)
{
	std::vector<int> Test{ {} };
	quicksort::sort(Test.begin(), Test.end(), std::less<>{});
	EXPECT_EQ(Test, std::vector<int>{{}});
}

TEST(DefaultContainers, SingleElementvectorWithLessComparator)
{
	std::vector<int> Test{ 1 };
	quicksort::sort(Test.begin(), Test.end(), std::less<>{});
	EXPECT_EQ(Test, std::vector<int>{1});
}

TEST(DefaultContainers, vectorWithLessComparator) {
		std::vector<short int> Test{ {63, 123, 32 ,5, 213, 321} };
		quicksort::sort(Test.begin(), Test.end(), std::less<>{});
		EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end(), std::less<>{}));
}




TEST(DefaultContainers, EmptyDequeWithLessComparator)
{
	std::deque<int> Test{};
	quicksort::sort(Test.begin(), Test.end(), std::less<>{});
	EXPECT_EQ(Test, std::deque<int>{});
}

TEST(DefaultContainers, SingleElementDequeWithLessComparator)
{
	std::deque<int> Test{ 1 };
	quicksort::sort(Test.begin(), Test.end(), std::less<>{});
	EXPECT_EQ(Test, std::deque<int>{1});
}

TEST(DefaultContainers, DequeWithLessComparator) {
	std::deque<unsigned int> Test{ {63, 123, 32 ,5, 213, 321} };
	quicksort::sort(Test.begin(), Test.end(), std::less<>{});
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end(), std::less<>{}));
}


TEST(DefaultContainers, CArrayWithLessComparator) {
	unsigned Test[] = {63, 123, 32 ,5, 213, 321};
	quicksort::sort(Test, Test + std::size(Test), std::less<>{});
	EXPECT_TRUE(std::is_sorted(Test, Test + std::size(Test), std::less<>{}));
}

TEST(DefaultContainers, CArrayWithLessComparatorSingleElement) {
	double Test[] = { 90.0 };
	quicksort::sort(Test, Test + std::size(Test), std::less<>{});
	EXPECT_TRUE(std::is_sorted(Test, Test + std::size(Test), std::less<>{}));
}




TEST(DefaultContainers, EmptyArrayWithLessComparator)
{
	std::array<int, 1> Test{ {} };
	quicksort::sort(Test.begin(), Test.end(), std::less<>{});
	std::array<int, 1> Expectation{ {} };
	EXPECT_EQ(Test, Expectation);
}

TEST(DefaultContainers, SingleElementArrayWithLessComparator)
{
	std::array<int, 1> Test{ 1 };
	quicksort::sort(Test.begin(), Test.end(), std::less<>{});
	std::array<int, 1> Expectation{ 1 };
	EXPECT_EQ(Test, Expectation);
}

TEST(DefaultContainers, ArrayWithLessComparator) {
	std::array<int, 6> Test{ {63, 123, 32 ,5, 213, 321} };
	quicksort::sort(Test.begin(), Test.end(), std::less<>{});
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end(), std::less<>{}));
}






TEST(TypeTests, Integer)
{
	std::vector<int> Test{ {63, 123, 32 ,5, 213, 321} };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}



TEST(TypeTests, LongInteger)
{
	std::vector<long int> Test{ {63, 123, 32 ,5, 213, 321} };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}



TEST(TypeTests, LongLongInteger)
{
	std::vector<long long int> Test{ {63, 123, 32 ,5, 213, 321} };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}

TEST(TypeTests, Double)
{
	std::vector<double> Test{ {1.5, 2.8, 321.1 ,5.0, 213.12, 321.5555555} };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}





TEST(TypeTests, Float)
{
	std::vector<float> Test{ {1.5f, 2.8f, 321.1f ,5.0f, 213.12f, 321.5555555f} };
	quicksort::sort(Test.begin(), Test.end());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end()));
}



TEST(ComparatorTest, Greater)
{
	std::vector<int> Test{ 63, 123, 32 ,5, 213, 321 };
	quicksort::sort(Test.begin(), Test.end(), std::greater<>());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end(), std::greater<>()));
}

namespace MyCompareFunction
{
	bool compare(int num1, int num2) {
		int digits1 = 0, digits2 = 0;

		// Находим количество цифр в числе num1
		if (num1 == 0) {
			digits1 = 1;
		}
		else {
			while (num1 != 0) {
				digits1++;
				num1 /= 10;
			}
		}

		// Находим количество цифр в числе num2
		if (num2 == 0) {
			digits2 = 1;
		}
		else {
			while (num2 != 0) {
				digits2++;
				num2 /= 10;
			}
		}

		// Сравниваем количество цифр в числах
		return digits1 < digits2;
	}
}

TEST(MyPropertiesTest, MyComparator)
{
	std::vector<unsigned int> Test{ {1, 1111111111, 1111, 11111, 111111111, 11111111, 1111111, 111111, 11111, 11} };

	quicksort::sort(Test.begin(), Test.end(), MyCompareFunction::compare);
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end(), MyCompareFunction::compare));
}


namespace MyStrcture
{
	class Vect
	{

	private:

		int X{};
		int Y{};
		double Length{};

	public:

		Vect(int x, int y)
		{
			X = x;
			Y = y;
			Length = sqrt(x * x + y * y);
		}




		bool operator > (const Vect& other) const
		{
			return this->Length > other.Length;
		}
		
		bool operator == (const Vect& other) const
		{
			return X==other.X && Y==other.Y;
		}

		static bool Compare(const Vect& first, const Vect& second)
		{
			return !(first > second) && first != second;
		}

		static bool Greater(const Vect& first, const Vect& second)
		{
			return first > second;
		}


	};
}



TEST(MyProperties, MyStrcture)
{
	MyStrcture::Vect V1(1, 2);
	MyStrcture::Vect V2(3, 4);
	MyStrcture::Vect V3(5, 6);
	MyStrcture::Vect V4(7, 8);
	MyStrcture::Vect V5(9, 10);
	
	std::vector<MyStrcture::Vect> Test{ V1, V5, V3, V2, V4 };
	quicksort::sort(Test.begin(), Test.end(), MyStrcture::Vect::Compare);
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end(), MyStrcture::Vect::Compare));
}

TEST(MyProperties, MyStrctureGreater)
{
	MyStrcture::Vect V1(1, 2);
	MyStrcture::Vect V2(3, 4);
	MyStrcture::Vect V3(5, 6);
	MyStrcture::Vect V4(7, 8);
	MyStrcture::Vect V5(9, 10);

	std::vector<MyStrcture::Vect> Test;
	Test = { V1, V5, V3, V2, V4 };
	quicksort::sort(Test.begin(), Test.end(), MyStrcture::Vect::Greater);
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end(), MyStrcture::Vect::Greater));
}



namespace functor {
	template<typename T>

	struct Great
	{

		bool operator()(const T& left, const T& right) { return left > right; }

	};
}



TEST(MyProperties, MyStrctureFunctor)
{
	MyStrcture::Vect V1(1, 2);
	MyStrcture::Vect V2(3, 4);
	MyStrcture::Vect V3(5, 6);
	MyStrcture::Vect V4(7, 8);
	MyStrcture::Vect V5(9, 10);

	std::vector<MyStrcture::Vect> Test;
	Test = { V1, V5, V3, V2, V4 };

	quicksort::sort(Test.begin(), Test.end(), functor::Great<MyStrcture::Vect>());
	EXPECT_TRUE(std::is_sorted(Test.begin(), Test.end(), functor::Great<MyStrcture::Vect>()));
}



struct A {

	int a{};

	int b{};

	bool operator<(const A& other) { return b > other.b; } // сравнение на ваш выбор…


};


TEST(MyProperties, MyAStrctureLessA) {
	std::vector<A> test{ {1, 2},{1,2},{},{1, 432},{1,100},{1, 52},{1,0} };
	quicksort::sort(std::begin(test), std::end(test), std::less<>{});
	EXPECT_TRUE(std::is_sorted(std::begin(test), std::end(test), std::less<>{}));
}




struct B {

	int a{};

	int b{};

	bool operator>(const B& other) { return b > other.b; }

};


TEST(MyProperties, MyStrctureGreaterB) {

	std::vector<B> test{ {1, 2},{1,2},{},{1, 432},{1,100},{1, 52},{1,0} };
	quicksort::sort(std::begin(test), std::end(test), std::greater<>{});
	EXPECT_TRUE(std::is_sorted(std::begin(test), std::end(test), std::greater<>{}));

}

TEST(MyProperties, Lambda) {
	auto mylambda = [](auto left, auto right) {return left < right; };
	std::vector<A> test{ {1, 2},{1,2},{},{1, 432},{1,100},{1, 52},{1,0} };
	quicksort::sort(std::begin(test), std::end(test), mylambda);
	EXPECT_TRUE(std::is_sorted(std::begin(test), std::end(test), mylambda));
}

TEST(Throw, RuntimeError)
{
	std::vector<int> Test{ {63, 123, 32 ,5, 213, 321} };
	EXPECT_THROW(quicksort::sort(std::end(Test), std::begin(Test)), std::out_of_range);
}