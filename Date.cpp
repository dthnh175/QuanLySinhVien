#include "stdafx.h"
#include "Date.h"
#include <iostream>
#include <sstream>


Date::Date()
{

}

Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

Date::Date(std::string inputString)
{

}

int Date::getDay()
{
	return this->day;
}

int Date::getMonth()
{
	return this->month;
}

int Date::getYear()
{
	return this->year;
}

std::string Date::toString()
{
	std::stringstream sstream;
	sstream << this->day << "/" << this->month << "/" << this->year;
	return sstream.str();
}

/*Returns 0 if two dates are equal
  Returns < 0 if date1 is before date2
  Returns > 0 if date1 is after date2
  */
int Date::compare(Date * date2)
{
	//compare two years
	if (this->getYear() > date2->getYear())
	{
		return 1;
	}
	else if (this->getYear() < date2->getYear())
	{
		return -1;
	}
	else 
	{
		//compare two months
		if (this->getMonth() > date2->getMonth())
		{
			return 1;
		}
		else if (this->getMonth() < date2->getMonth())
		{
			return -1;
		}
		else
		{
			//compare two days
			if (this->getDay() > date2->getDay())
			{
				return 1;
			}
			else if (this->getDay() < date2->getDay())
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}
}
