#include"Dictory.hpp"
#include <iostream>
#include <fstream>
#include <chrono>




int main(int argc, char** argv) 
{
    if (argc != 3) {
        cout << "Usage: ./program_name input_file output_file" << endl;
        return 1;
    }

    ifstream input_file;
    input_file.open(argv[1]);
    if (!input_file.is_open()) {
        cout << "Could not open input file " << argv[1] << endl;
        return 1;
    }

    ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        cout << "Could not open output file " << argv[2] << endl;
        return 1;
    }

    // Дальше можно производить операции чтения из input_file
    // и записи в output_file

    MapDictory map{};

    bench(input_file, "Map", map);
    output_file << map.GetResult();

    VectorDictory vector;
    bench(input_file, "Vector", vector);
    output_file << vector.GetResult();


    ListDictory list{};
    bench(input_file, "list", list);
    output_file << list.GetResult();


    input_file.close();
    output_file.close();

    return 0;
}

