#pragma once
#include <string>
#include "Date.h"
#include "Name.h"


class Student
{
private:
	Name * name;
	std::string studentID;
	std::string studyClass;
	Date * dateOfBirth;
	double GPA;

	std::string fileName;
	void makeFileName();
public:
	//constructors

	Student();
	Student(std::string name, std::string studentID, std::string studyClass, int day, int month, int year, double GPA);
	Student(Name * name, std::string studentID, std::string studyClass, Date * dob, double GPA);
	Student(std::string filePath);

	//getters
	Name * getName();
	std::string getFullName();
	std::string getFirstName();
	std::string getLastName();
	std::string getStudentID();
	std::string getStudyClass();
	Date * getDateOfBirth();
	double getGPA();
	std::string getFileName();

	//setters

	void setName(std::string);
	void setStudentID(std::string studentID);
	void setStudyClass(std::string studyClass);
	void setDateOfBirth(int date, int month, int year);
	void setGPA(double GPA);

	/*Returns 0 if two names have the same firstName and lastName.
	 Returns < 0 if this name is alphabetically before anotherName.
	 Returns > 0 if this date is alphabetically after anotherName.*/
	int compareName(Student * anotherStudent);

	std::string toString();
	void printInfo();
	void writeToFile(std::string studentFilePath);
};
