#pragma once
#include "StudentList.h"
#include <string.h>


void statistic(StudentList * list);
void statistic(StudentList * list, int choice);

/*Draw a table to stat all classes's number of students*/
void statAllClass(StudentList * list);

/*Classify all students to five groups: Excellent, Good, Pretty good, average, weak.
Algorithm:
Sort the list by class then classify students in each class.*/
void classifyStudent(StudentList * list);
