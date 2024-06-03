#include "Gystogramm.hpp"


Gystogramm::Gystogramm(const vector<string>& s)
{
	for (auto& item : s)
	{
		AddWord(item);
	}
}




void Gystogramm::AddWord(const string& word) 
{

	data_[word]++;

}


Gystogramm Gystogramm::operator+(const Gystogramm& s) const
{
	Gystogramm result{*this};

	for (const auto& kv : s.data_) {
		result.data_[kv.first] += kv.second;
	}

	return result;
}


//Gystogramm& Gystogramm::operator=(const Gystogramm& other)
//{
//	if (this == &other) { // проверка на самоприсваивание
//		return *this;
//	}
//	data_ = other.data_; // копирование членов данных из правого операнда
//	return *this;
//}
//

Gystogramm Gystogramm::operator-(const Gystogramm& s) const
{

	if (*this == Gystogramm())
	{
		return Gystogramm();
	}
	Gystogramm result(*this);
	for (const auto& entry : s.data_) {
		if (result.data_.contains(entry.first)) {
			if (result.data_.at(entry.first) <= entry.second) {
				result.data_.erase(entry.first);
			}
			else {
				result.data_[entry.first] -= entry.second;
			}
		}
	}

	return result;
}


const size_t& Gystogramm::at(const std::string& str) const
{
	return data_.at(str);
}


string Gystogramm::GetResult()
{
	string result = "";
	for (auto& it : data_)
	{
		result += it.first + " " + to_string(it.second) + "\n";
	}
	return result;
}