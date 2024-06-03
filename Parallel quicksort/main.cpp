#include "pquicksort.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <iostream>


class MyPolicy {
private:
    int Threads;
public:
    MyPolicy(int Count) : Threads(Count) {}

    int GetThreads(ptrdiff_t size) const {
        return Threads;
    }
};


template<class T>
void PerfomanceTest() {
    std::string ClassName = typeid(T).name();
    std::vector<int> sizes = { 100, 500, 1000, 1500, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000, 5000000, 10000000, 20000000, 50000000 };
    int ThreadsCount = (int)std::thread::hardware_concurrency();
    // Открытие файла для записи
    std::ofstream outfile("output"+ ClassName + ".csv");
    // Проверка, успешно ли открыт файл
    if (!outfile.is_open()) {
        std::cerr << "Unable to open the output file." << std::endl;
    }
    for (int j = 0; j < 3; j++) {
        // Запись заголовка таблицы в файл
        outfile << "Size \\ Threads";
        for (int threads = 1; threads <= ThreadsCount; ++threads) {
            outfile << "," << threads;
        }
        outfile << std::endl;

        // Запуск сортировки для каждого размера вектора и разного числа потоков
        for (const auto& size : sizes) {
            outfile << size;
            for (int threads = 1; threads <= ThreadsCount; ++threads) {
                using namespace std::chrono;
                std::cout << "(" << size << ")" << " " << threads << std::endl;

                // Создание вектора случайных чисел заданного размера
                std::vector<T> data(size);
                std::generate(data.begin(), data.end(), std::rand);

                // Измерение времени сортировки
                auto start_time = high_resolution_clock::now();
                parallel::sort1(data.begin(), data.end(), MyPolicy(threads));
                auto end_time = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(end_time - start_time);

                // Запись времени выполнения в файл
                outfile << "," << duration.count();
            }

            outfile << std::endl;
        }
        outfile << std::endl << std::endl << std::endl;
    }

    // Закрытие файла
    outfile.close();

}


int main() {
    std::cout << "long int" << std::endl;
    PerfomanceTest<long int>();
    return 0;
}