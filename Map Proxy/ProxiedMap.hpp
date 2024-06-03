#pragma once
#include<map>
#include<string>
#include<vector>
#include "auditor.hpp"
#include <memory>



class ProxiedMap final
{
public:
	//ProxiedMap(const std::map <std::string, size_t>& DataMap, std::shared_ptr<auditor> Auditors) : data_(DataMap), object(Auditors){}
	ProxiedMap(const std::map <std::string, size_t>& DataMap, const auditor& Auditors): data_(DataMap), object(Auditors) {};
	void edit(const std::string& key, size_t value);
	const size_t read(const std::string& key) const;
private:
	std::map<std::string, size_t> data_;
	//::shared_ptr<auditor> object;
	const auditor& object;
};