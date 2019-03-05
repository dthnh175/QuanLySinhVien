#include "stdafx.h"
#include "Student.h"
#include <iostream>
#include <fstream>
#include <sstream>


Student::Student()
{
	//nothing
}

Student::Student(std::string fullName, std::string studentID, std::string studyClass, int day, int month, int year, double GPA)
{
	this->name = new Name(fullName);
	this->studentID = studentID;
	this->studyClass = studyClass;
	this->dateOfBirth = new Date(day, month, year);
	this->GPA = GPA;

	makeFileName();
}

Student::Student(Name * name, std::string studentID, std::string studyClass, Date * dob, double GPA)
{
	this->name = name;
	this->studentID = studentID;
	this->studyClass = studyClass;
	this->dateOfBirth = dob;
	this->GPA = GPA;

	makeFileName();
}

/*Read instance of Student from file*/
Student::Student(std::string filepath)
{
	//read from DAT file
	std::fstream file(filepath.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Data file " << fileName << "not opened.\n";
		return;
	}

	//read each member of Student in binary file

	char* data;
	size_t size;

	//read name
	file.read((char*)&size, sizeof(size_t));
	data = new char[size + 1];
	file.read(data, size);
	data[size] = '\0';
	std::string fullname = data;
	this->name = new Name(fullname);
	delete data;

	//read studentID
	file.read((char*)&size, sizeof(size_t));
	data = new char[size + 1];
	file.read(data, size);
	data[size] = '\0';
	this->studentID = data;
	delete data;

	//read studyClass
	file.read((char*)&size, sizeof(size_t));
	data = new char[size + 1];
	file.read(data, size);
	data[size] = '\0';
	this->studyClass = data;
	delete data;

	//read Date
	int day, month, year;
	file.read((char*)&day, sizeof(int));
	file.read((char*)&month, sizeof(int));
	file.read((char*)&year, sizeof(int));
	this->dateOfBirth = new Date(day, month, year);

	//read GPA
	this->GPA;
	file.read((char*)&(this->GPA), sizeof(double));

	//make file name
	std::string filename = filepath;
	int i = filepath.length() - 1;
	while (filepath[i] != '\\')
	{
		i--;
	}
	this->fileName = filepath.substr(i + 1, filepath.length() - (i + 1));

	//close file
	file.close();	

}

void Student::makeFileName()
{
	this->fileName = this->studentID;
	this->fileName.append("_");
	std::string name = this->name->getFullName();
	for (size_t i = 0; i < name.length(); i++)
	{
		if (name[i] == ' ')
		{
			name.erase(i, 1);
		}
	}
	this->fileName.append(name);
	this->fileName.append(".dat");
}

Name * Student::getName()
{
	return this->name;
}

std::string Student::getFullName()
{
	return this->name->getFullName();
}

std::string Student::getFirstName()
{
	return this->name->getFirstName();
}

std::string Student::getLastName()
{
	return this->name->getLastName();
}

std::string Student::getStudentID()
{
	return this->studentID;
}

std::string Student::getStudyClass()
{
	return this->studyClass;
}

Date * Student::getDateOfBirth()
{
	return this->dateOfBirth;
}

double Student::getGPA()
{
	return this->GPA;
}

std::string Student::getFileName()
{
	return this->fileName;
}

void Student::setName(std::string fullName)
{
	this->name = new Name(fullName);
	this->makeFileName();
}

void Student::setStudentID(std::string studentID)
{
	this->studentID = studentID;
	this->makeFileName();
}

void Student::setStudyClass(std::string studyClass)
{
	this->studyClass = studyClass;
}

void Student::setDateOfBirth(int date, int month, int year)
{
	this->dateOfBirth = new Date(date, month, year);
}

void Student::setGPA(double GPA)
{
	this->GPA = GPA;
}

/*	Returns 0 if two names have the same firstName and lastName
	Returns < 0 if this name is alphabetically before anotherName
	Returns > 0 if this date is alphabetically after anotherName*/
int Student::compareName(Student * anotherStudent)
{
	return this->name->compare(anotherStudent->getName());
}

std::string Student::toString()
{
	std::string studentInfo = "";
	studentInfo.append(this->name->getFullName());
	studentInfo.append(" | ");
	studentInfo.append(this->studentID);
	studentInfo.append(" | ");
	studentInfo.append(this->dateOfBirth->toString());
	studentInfo.append(" | ");
	studentInfo.append(this->studyClass);
	studentInfo.append(" | ");
	std::ostringstream oss;
	oss << this->GPA;
	studentInfo.append(oss.str());

	return studentInfo;
}

void Student::printInfo()
{
	std::cout << "Ho va ten: " << this->name->getFullName() << std::endl;
	std::cout << "Ngay sinh: " << this->dateOfBirth->toString() << std::endl;
	std::cout << "Ma SV    : " << this->studentID << std::endl;
	std::cout << "Lop hoc  : " << this->studyClass << std::endl;
	std::cout << "Diem TB  : " << this->GPA << std::endl;
}

void Student::writeToFile(std::string studentFilePath)
{	

	//if file is not existed, create a new one, if existed override that file
	std::fstream fileOut(studentFilePath.c_str(), std::ios::out | std::ios::binary);
	if (!fileOut.is_open())
	{
		std::cout << "Error opening the file.\n";
		return;
	}

	//write each class member to file

	//write name to file
	size_t size = this->name->getFullName().size();
	fileOut.write((char*)&size, sizeof(size_t));
	fileOut.write((char*)this->name->getFullName().c_str(), size);

	//write studentID to file
	size = this->studentID.size();
	fileOut.write((char*)&size, sizeof(size_t));
	fileOut.write((char*)this->studentID.c_str(), size);

	//write studyClass to file
	size = this->studyClass.size();
	fileOut.write((char*)&size, sizeof(size_t));
	fileOut.write((char*)this->studyClass.c_str(), size);

	//write date of birth to file
	int day = this->dateOfBirth->getDay(),
		month = this->dateOfBirth->getMonth(),
		year = this->dateOfBirth->getYear();
	fileOut.write((char*)&day, sizeof(int));
	fileOut.write((char*)&month, sizeof(int));
	fileOut.write((char*)&year, sizeof(int));

	//write GPA to file
	fileOut.write((char*)&GPA, sizeof(double));

	//close file
	fileOut.close();

}
