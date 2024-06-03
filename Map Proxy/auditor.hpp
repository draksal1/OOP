#pragma once
#include <string>
#include <map>



class auditor {
public:
	const virtual bool isEdit(const std::string& key) const = 0;
	//для определённых ключей можно или нет
	enum readType {
		no_access, access, own_value
	};

	const virtual std::pair < readType, size_t > Read(const std::string& key)const = 0;

};

class AllRoots final : public auditor {
public:
	const bool isEdit(const std::string& key) const override;
	const virtual std::pair < readType, size_t > Read(const std::string& key)const;

};

class EditRoots final : public auditor {
public:
	EditRoots(const std::map<std::string, size_t>& Spoofed, const std::map<std::string, size_t>& ProhibitEdit);
	const bool isEdit(const std::string& key) const override;
	const virtual std::pair < readType, size_t > Read(const std::string& key)const;
protected:
	std::map<std::string, size_t> SpoofedValues;
	std::map<std::string, size_t> ProhibitEdit;

};

class OnlyReadRoots final : public auditor {
public:
	const bool isEdit(const std::string& key) const override;
	const virtual std::pair < readType, size_t > Read(const std::string& key)const;
};