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

/*	Returns 0 if two names have the same firstName and lastName
	Returns < 0 if this name is alphabetically before anotherName
	Returns > 0 if this date is alphabetically after anotherName*/
int Name::compare(Name * anotherName)
{
	if ((this->firstName).compare(anotherName->getFirstName()) < 0)
	{
		return -1;
	}
	else if ((this->firstName).compare(anotherName->getFirstName()) > 0)
	{
		return 1;
	}
	else if ((this->firstName).compare(anotherName->getFirstName()) == 0)
	{
		if ((this->lastName).compare(anotherName->getLastName()) < 0)
		{
			return -1;
		}
		else if ((this->lastName).compare(anotherName->getLastName()) > 0)
		{
			return 1;
		}
	}

	return 0;
}

//int pivot = arr[high];    // pivot
//int left = low;
//int right = high - 1;
//while (true) {
//	while (left <= right && arr[left] < pivot) left++; // find element >= arr[pivot]
//	while (right >= left && arr[right] > pivot) right--; // find element <= arr[pivot]
//	if (left >= right) break; //	if done then exit
//	swap(&arr[left], &arr[right]); // if not done, swap
//	left++; // because the current left has been detected then increase
//	right--; //
//}
//swap(&arr[left], &arr[high]);
//return left; // return the index for dividing array.