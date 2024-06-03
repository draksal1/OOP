#include"Dictory.hpp"
#include<iostream>



void VectorDictory::NWord(const string& S)
{
    if (S.empty())
    {
        return;
    }
    auto it = find_if(data_.begin(), data_.end(), cmp_name(S));
    if (it == data_.end())
    {
        data_.push_back(make_pair(S, 1));
        return;
    }
    it->second++;
}

size_t VectorDictory::CountOfWord(const string& S)
{
    auto it = find_if(data_.begin(), data_.end(), cmp_name(S));
    if (it == data_.end()) {
        return 0;
    }
    return it->second;
}

const pair<const string, size_t>& VectorDictory::GetIterWord(int n)
{
    if (n > data_.size() - 1 || n<0)
    {
        throw::out_of_range("No such element");
    }
    return data_[n];
}


string VectorDictory::GetResult()
{
    string result = "";
    for (auto& it : data_)
    {
        result += it.first + " " + to_string(it.second) + "\n";
    }
    return result;
}