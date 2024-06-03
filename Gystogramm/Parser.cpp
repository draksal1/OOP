#include "parcer.hpp"

using namespace std;


void parse(istream& is, Gystogramm& Gysto)
{
	vector <string> result;
	string line;

	while (getline(is, line))
	{
		size_t prev = 0;
		size_t next;
		bool flag = false;
		while ((next = line.find(' ', prev)) != string::npos)
		{
			string word = line.substr(prev, next - prev);
			Gysto.AddWord(word);
			prev = next + 1;
			flag = true;
		}
		if (line != "")
		{
			string word = line.substr(prev, line.size() - prev+1);
			Gysto.AddWord(word);
		}
	}
}