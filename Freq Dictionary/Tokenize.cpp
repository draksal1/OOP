#include "Dictory.hpp"
#include <iostream>
#include <chrono>
using namespace std;

void tokenize(std::istream& in, Dictory& dict)
{
	string str;

	while (in >> str) { // читает до конца файла

		dict.NWord(str);

	}
}

void bench(std::istream& in, const string className, Dictory& dict)
{
    tokenize(in, dict);
    cout << className <<" create time:" << endl;
    string s;
    auto start = std::chrono::high_resolution_clock::now();
    tokenize(in, dict);
    auto end = std::chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;

    cout << "Dict add time:" << endl;
    start = std::chrono::high_resolution_clock::now();
    dict.NWord(string("kek"));
    end = std::chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;

    // сбрасываем флаги ошибок потока после чтения
    if (!in) {
        in.clear();
    }
    // изменяем позицию в потоке
    in.seekg(0, std::ios::beg);
}