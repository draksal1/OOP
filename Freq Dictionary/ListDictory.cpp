#include"Dictory.hpp"
#include<iostream>



void ListDictory::NWord(const string& S)
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

size_t ListDictory::CountOfWord(const string& S)
{
    auto it = find_if(data_.begin(), data_.end(), cmp_name(S));
    if (it == data_.end()) {
        return 0;
    }
    return it->second;
}

const pair<const string, size_t>& ListDictory::GetIterWord(int n)
{
    auto result = data_.begin();
    if (n > data_.size() - 1)
    {
        throw::out_of_range("No such element");
    }

    advance(result , n);

    return *result;
}


string ListDictory::GetResult()
{
    string result = "";
    for (auto& it : data_)
    {
        result += it.first + " " + to_string(it.second) + "\n";
    }
    return result;
}