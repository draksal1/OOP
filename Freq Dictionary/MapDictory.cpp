#include"Dictory.hpp"
#include <iostream>


void MapDictory::NWord(const string& word)
{
    if (word.empty())
    {
        return;
    }
    data_[word]++;
}

size_t MapDictory::CountOfWord(const string& S)
{
    auto result = data_.find(S);
    if (result == data_.end())
    {
        return 0;
    }
    return result->second;
}

const pair<const string, size_t>& MapDictory::GetIterWord(int n)
{
    auto result = data_.begin();
    if (n > data_.size() - 1)
    {
        throw::out_of_range("No such element");
    }

    advance(result, n);

    return *result;
}

string MapDictory::GetResult()
{
    string result = "";
    for (auto& it : data_)
    {
        result += it.first + " " + to_string(it.second) + "\n";
    }
    return result;
}