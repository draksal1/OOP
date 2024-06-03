#include "gtest/gtest.h"
#define _CRTDBG_MAP_ALLOC
#include "ObjectPull.h"


class Point {
    int m_x{};
    int m_y{};
public:
    Point()                // конструктор без параметров
        : m_x(0), m_y(0) {}
    Point(int x, int y)    // конструктор с параметрами
        : m_x(x), m_y(y) {}
    ~Point() {}
    int GetX() {
        return m_x;
    }
    int GetY() {
        return m_y;
    }
};
struct Point2 {
private:
    int m_x{};
    int m_y{};
    char* ptr{};
public:
    Point2() = default;
    Point2(int x, int y, int size)
    {
        m_x = x;
        m_y = y;
        ptr = new char[size];
    }
    ~Point2()
    {
        delete ptr;
    }
    int GetX() {
        return m_x;
    }
    int GetY() {
        return m_y;
    }

};


class MemoryLeaksDetector {
private:
    _CrtMemState last_state{};
public:
    MemoryLeaksDetector()
    {
        _CrtMemCheckpoint(&last_state);
    }
    ~MemoryLeaksDetector()
    {
        _CrtMemState state{};
        _CrtMemCheckpoint(&state);
        _CrtMemState diff{};
        EXPECT_TRUE(_CrtMemDifference(&diff, &last_state, &state) == 0);
    }
};



TEST (ObjectPullTest, TwoPoints) {
    MemoryLeaksDetector Detector;
    {
        ObjectPool<Point> pp(10);
        Point& p1 = pp.alloc();           // сработал конструктор Point()
        Point& p2 = pp.alloc(0, 1);       // сработал конструктор Point(0, 1)
        EXPECT_EQ(pp.GetAllocatedCount(), 2);
        // Использование объектов
        EXPECT_EQ(p2.GetX(), 0);
        EXPECT_EQ(p2.GetY(), 1);
        pp.free(p1);                      // автоматически вызовется деструктор Point()
        pp.free(p2);                      // автоматически вызовется деструктор Point()
        EXPECT_EQ(pp.GetAllocatedCount(), 0);
    }  
}


class ExeptionInConstructor
{
public:
    ExeptionInConstructor(bool flag){
        if (flag) {
            throw std::runtime_error("Cofee break");
    }
    }
};


TEST(ObjectPullTest, TrowInConstructorTest) {
    MemoryLeaksDetector Detector;
    {
        ObjectPool<ExeptionInConstructor> pp(1);
        EXPECT_THROW(pp.alloc(true), std::runtime_error);
        EXPECT_EQ(pp.GetAllocatedCount(), 0);
    }
}

TEST(ObjectPullTest, TwoPointsWithCustomMemory) { 
    MemoryLeaksDetector Detector;
    {
        ObjectPool<Point2> pp(10);
        Point2& p1 = pp.alloc();           // сработал конструктор Point()
        Point2& p2 = pp.alloc(0, 1, 10);       // сработал конструктор Point(0, 1)
        EXPECT_EQ(pp.GetAllocatedCount(), 2);
        EXPECT_EQ(p2.GetX(), 0);
        EXPECT_EQ(p2.GetY(), 1);
        pp.free(p1);                      // автоматически вызовется деструктор Point()
        pp.free(p2);                      // автоматически вызовется деструктор Point()
        EXPECT_EQ(pp.GetAllocatedCount(), 0);
    }
}
TEST(ObjectPullTest, OverflowIntTest) {
    MemoryLeaksDetector Detector;
    {
        ObjectPool<int> pp(10);
        for (int i = 0; i < 10; i++) {
            pp.alloc();
        }
               
        
        EXPECT_THROW(pp.alloc(), std::out_of_range);
    }
}

TEST(ObjectPullTest, FreeNotExistingObject) {
    MemoryLeaksDetector Detector;
    {
        ObjectPool<double> pp(1);
        double test = 4.0;
        EXPECT_THROW(pp.free(test), std::invalid_argument);
    }
}



TEST(ObjectPoolTest, AllocateAndFree) {
    MemoryLeaksDetector Detector;
    {
        ObjectPool<double> pool(3);

        //Выделяем 3 объекта
        double& obj1 = pool.alloc(1.0);
        double& obj2 = pool.alloc(2.0);
        double& obj3 = pool.alloc(3.0);

        //Проверяем, что количество выделенных объектов равно 3
        EXPECT_EQ(pool.GetAllocatedCount(), 3);

        //Освобождаем объекты
        pool.free(obj1);
        pool.free(obj2);

        //Проверяем, что количество выделенных объектов уменьшилось до 1
        EXPECT_EQ(pool.GetAllocatedCount(), 1);

        //Выделяем еще 2 объекта
        double& obj4 = pool.alloc(4.0);
        double& obj5 = pool.alloc(5.0);

        //Проверяем, что количество выделенных объектов стало 3
        EXPECT_EQ(pool.GetAllocatedCount(), 3);

        //Проверяем, что объекты 1 и 2 освобождены, а 3, 4 и 5 выделены
        EXPECT_NO_THROW(pool.free(obj3));
        EXPECT_NO_THROW(pool.free(obj4));
        EXPECT_NO_THROW(pool.free(obj5));
    }
}

TEST(ObjectPoolTest, FreeEven) {
    MemoryLeaksDetector Detector;
    {
        // Create an ObjectPool of char with a capacity of 50
        ObjectPool<char> pool(50);

        // Allocate 50 objects
        std::vector<std::reference_wrapper<char>> references;
        for (int i = 0; i < 50; i++) {
            char& obj = pool.alloc(static_cast<char>('A' + i));
            references.push_back(obj);
        }

        // Free objects at even indices
        for (int i = 0; i < 50; i += 2) {
            EXPECT_NO_THROW(pool.free(references[i]));
        }

        // Check that the count of allocated objects is now 25
        EXPECT_EQ(pool.GetAllocatedCount(), 25);

        // Attempt to free all objects again (even and odd indices)
        for (int i = 0; i < 25; i++) {
            char& obj = pool.alloc(static_cast<char>('A' + i));
        }
        // Check that all objects are freed, and the count is back to 0
        EXPECT_EQ(pool.GetAllocatedCount(), 50);
    }
}

class ExeptionTrower {
public:
    ExeptionTrower(int a){}
    ~ExeptionTrower()noexcept(false) {
        throw std::invalid_argument("Lol");
    }
};



TEST(ObjectPoolTest, DestructorExeption) {
    bool exceptionThrown = false;
    try {
            ExeptionTrower a(1);
    }
    catch (const std::invalid_argument& e) {
        // Исключение успешно поймано
        exceptionThrown = true;
        // Дополнительные проверки, если требуются
    }
    catch (...) {
        // Поймано исключение другого типа
    }

    EXPECT_TRUE(exceptionThrown);
}

//TEST(ObjectPoolTest, DestructorExeption) {
//    {
//        ObjectPool<ExeptionTrower> a(1);
//    }
//}