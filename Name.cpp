#include "stdafx.h"
#include "Name.h"

Name::Name()
{

}

Name::Name(std::string fullName)
{
	//full name
	this->fullName = fullName;

	//take out last name from full name
	int i = 0;
	while (fullName[i] != ' ')
	{
		i++;
	}
	lastName = fullName.substr(0, i);

	//take out first name from full name
	i = fullName.length() - 1;
	while (fullName[i] != ' ')
	{
		i--;
	}
	firstName = fullName.substr(i + 1, fullName.length() - 1);
}

std::string Name::getFullName()
{
	return this->fullName;
}

std::string Name::getFirstName()
{
	return this->firstName;
}

std::string Name::getLastName()
{
	return this->lastName;
}
