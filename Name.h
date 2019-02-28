#pragma once
#include <string>

class Name
{
private:
	std::string fullName;
	std::string firstName, lastName;

public:
	Name();
	Name(std::string);
	std::string getFullName();
	std::string getFirstName();
	std::string getLastName();
};
