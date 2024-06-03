#pragma once
#include <vector>
#include <string>
#include <map>

using namespace std;
class Gystogramm{
public:
	Gystogramm() = default;
	Gystogramm(const vector<string>& s);
	Gystogramm(const Gystogramm&)=default;
	Gystogramm& operator=(const Gystogramm& other) = default;
	auto begin() const { return data_.begin(); };
	auto end() const { return data_.end(); };
	Gystogramm operator+(const Gystogramm&) const;
	Gystogramm operator-(const Gystogramm&) const;
	bool operator==(const Gystogramm& s) const { return data_ == s.data_; };
	bool operator!=(const Gystogramm& s) const { return data_ != s.data_; };
	size_t get_size() const { return data_.size(); }
	void AddWord(const string& s);
	const size_t& at(const std::string& str) const;
	string GetResult();

private:
	map<string, size_t> data_;
};