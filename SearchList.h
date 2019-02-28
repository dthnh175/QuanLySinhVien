#pragma once
#include <string>
#include "Menu.h"
#include "StudentList.h"

void searchList(StudentList * list);
void searchList(StudentList * list, int searchField, int searchAlgo);

Node * binarySearchName(StudentList * list, std::string keyWord);
Node * binarySearchID(StudentList * list, std::string keyWord);
Node * binarySearchDOB(StudentList * list, int day, int month, int year);
Node * binarySearchGPA(StudentList * list, std::string keyWord);
Node * binarySearchStudyClass(StudentList * list, std::string keyWord);

Node * linearSearchName(StudentList * list, std::string keyWord);
Node * linearSearchID(StudentList * list, std::string keyWord);
Node * linearSearchDOB(StudentList * list, std::string keyWord);
Node * linearSearchGPA(StudentList * list, std::string GPA);
Node * linearSearchStudyClass(StudentList * list, std::string keyWord);

Menu * createSearchResultMenu(Node * searchResult);

