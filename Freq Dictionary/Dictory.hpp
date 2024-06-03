#pragma once
#include<string>
#include<vector>
#include<string>
#include<list>
#include<map>
#include<sstream>
#include <stdexcept>
using namespace std;


struct cmp_name {

	cmp_name(const std::string& n) : name(n) {}

	bool operator()(const std::pair<const std::string, size_t>& param) const {
		return name == param.first;
	}

private:

	std::string name{};

};

class Dictory {
public:
	Dictory()=default;
	virtual size_t CountOfWord(const string& S)=0;
	virtual void NWord(const string& word)=0;
	virtual const pair<const string, size_t>& GetIterWord(int n) = 0;
	void bench(std::istream& in, const string className, Dictory& dict);
	virtual std::string GetResult() = 0;
};

void tokenize(std::istream& in, Dictory& dict);
void bench(std::istream& in, const string className, Dictory& dict);

class VectorDictory final: public Dictory {
public:
	VectorDictory()=default;
	
	size_t CountOfWord(const string& S);
	void NWord(const string& word);
	const pair<const string, size_t>& GetIterWord(int n);
	std::string GetResult();

private:
	vector<pair<const string, size_t>> data_;
};


class ListDictory final: public Dictory {
public:
	ListDictory() = default;
	size_t CountOfWord(const string& S);
	const pair<const string, size_t>& GetIterWord(int n);
	void NWord(const string& word);
	std::string GetResult();
private:
	list<pair<const string, size_t>> data_;
};


class MapDictory final: public Dictory {
public:
	MapDictory() = default;
	size_t CountOfWord(const string& S);
	void NWord(const string& word);
	const pair<const string, size_t>& GetIterWord(int n);
	std::string GetResult();
private:
	map<string, size_t> data_;
};

