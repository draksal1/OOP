#include "auditor.hpp"






EditRoots::EditRoots(const std::map<std::string, size_t>& Spoofed, const std::map<std::string, size_t>& Prohibited)
{
	SpoofedValues.insert(Spoofed.begin(), Spoofed.end());
}


 
const bool AllRoots::isEdit(const std::string& key)const
{
	return true;
}

const std::pair < auditor::readType, size_t >  AllRoots::Read(const std::string& key)const
{
	return { access, 0 };
}

const bool EditRoots::isEdit(const std::string& key)const
{
	return ProhibitEdit.find(key) == ProhibitEdit.end();
}

const std::pair < auditor::readType, size_t >  EditRoots::Read(const std::string& key)const
{
	auto item = SpoofedValues.find(key);
	if (item == SpoofedValues.end())
	{
		auditor::readType a = no_access;
		return std::make_pair(a, 0);
	}
	auditor::readType a = own_value;
	return std::make_pair(a, item->second);
}

const bool OnlyReadRoots::isEdit(const std::string& key)const
{
	return false;
}

const std::pair < auditor::readType, size_t >  OnlyReadRoots::Read(const std::string& key)const
{
	return { access, 0 };
}