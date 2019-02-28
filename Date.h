#pragma once
#include <string>

class Date
{
private:
	int day, month, year;
public:
	Date();
	Date(int date, int month, int year);
	Date(std::string inputString);
	int getDay();
	int getMonth();
	int getYear();

	std::string toString();
	/*Returns 0 if two dates are equal
	Returns < 0 if this date is before date2
	Returns > 0 if this date is after date2
	*/
	int compare(Date date2);
};
