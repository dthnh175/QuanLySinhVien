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
	Student();
	Student(std::string name, std::string studentID, std::string studyClass, int day, int month, int year, double GPA);
	Student(Name * name, std::string studentID, std::string studyClass, Date * dob, double GPA);
	Student(std::string filePath);

	std::string getFullName();
	std::string getFirstName();
	std::string getLastName();
	std::string getStudentID();
	std::string getStudyClass();
	Date * getDateOfBirth();
	double getGPA();
	std::string getFileName();

	void setName(std::string);
	void setStudentID(std::string studentID);
	void setStudyClass(std::string studyClass);
	void setDateOfBirth(int date, int month, int year);
	void setGPA(double GPA);

	std::string toString();
	void printInfo();
	void writeToFile(std::string studentFilePath);
};
