#pragma once
#include "Student.h"
#include "StudentList.h"
#include "ManagingMenu.h"


void editList(StudentList * list);
void editList(StudentList * list, int editOption);

void addNewStudent(StudentList * list);
void chooseAndEditStudent(StudentList * list);
void chooseAndDeleteStudent(StudentList * list);

Student * enterStudentInfo(StudentList * list);
bool nameCheck(std::string fullName);
std::string correctName(std::string inputString);
std::string correctStudyClass(std::string inputString);
bool studentIDCheck(StudentList * list, std::string studentID);
bool dateFormatCheck(std::string inputString);
bool dateCheck(int day, int month, int year);
bool gpaCheck(double GPA);

void editStudentInfo(StudentList * list, Student * chosenStudent);

void reprintLine(std::string previousLine, std::string newInfo);

void deleteStudent(StudentList * list, Student * chosenStudent);
void deleteFromLinkedList(Node ** firstNode, Student * student);
void deleteFile(std::string filepath);
void writeToFile(StudentList * list, Student * student);

