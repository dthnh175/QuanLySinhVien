#pragma once
#include "StudentList.h"

void sortList(StudentList * list);
void sortList(StudentList * list, int sortField, int sortAlgo);

void swap(Student ** student1, Student ** student2);

void slectionSortName(StudentList * list);
void selectionSortStudentID(StudentList * list);
void selectionSortStudyClass(StudentList * list);
void selectionSortDOB(StudentList * list);
void selectionSortGPA(StudentList * list);

void insertionSortName(StudentList * list);
void insertionSortStudentID(StudentList * list);
void insertionSortStudyClass(StudentList * list);
void insertionSortDOB(StudentList * list);
void insertionSortGPA(StudentList * list);

void quickSortName(StudentList * list);
void quickSortStudentID(StudentList * list);
void quickSortStudyClass(StudentList * list);
void quickSortDOB(StudentList * list);
void quickSortGPA(StudentList * list);

void mergeSortName(StudentList * list);
void mergeSortStudentID(StudentList * list);
void mergeSortStudyClass(StudentList * list);
void mergeSortDOB(StudentList * list);
void mergeSortGPA(StudentList * list);

void heapSortName(StudentList * list);
void heapSortStudentID(StudentList * list);
void heapSortStudyClass(StudentList * list);
void heapSortDOB(StudentList * list);
void heapSortGPA(StudentList * list);