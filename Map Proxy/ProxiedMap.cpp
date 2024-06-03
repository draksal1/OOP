#include "ProxiedMap.hpp"
#include <stdexcept>

//ProxiedMap::ProxiedMap(const std::map <std::string, size_t>& DataMap, const auditor& Auditors)
//{
//	object = std::make_unique<auditor>(Auditors);
//	data_.insert(DataMap.begin(), DataMap.end());
//}

void ProxiedMap::edit(const std::string& key, size_t value)
{
	if (!object.isEdit(key))
	{
		throw std::runtime_error("No roots");
	}
	data_[key] = value;
}


const size_t ProxiedMap::read(const std::string& key) const
{
	std::pair < auditor::readType, size_t > A = object.Read(key);
	if (A.first==auditor::own_value)
	{
		return A.second;
	}
	if ((A.first==auditor::no_access))
	{
		throw std::runtime_error("No roots");
	}
	if (A.first != auditor::access)
	{
		throw std::runtime_error("Enum error");
	}
	auto item = data_.find(key);
	if (item == data_.end())
	{
		throw std::runtime_error("No such key");
	}
	return item->second;
}
