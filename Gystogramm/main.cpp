#include "Gystogramm.hpp"
#include <iostream>
#include <sstream>
#include "parcer.hpp"
#include <fstream>

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
	Gystogramm Gysto;
	parse(input_file, Gysto);
	output_file <<"Keys/Values\n" << Gysto.GetResult();

    input_file.close();
    output_file.close();
}