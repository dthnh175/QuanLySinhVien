#pragma once
#include "StudentList.h"

enum class SortField
{
	NAME, STUDENT_ID, STUDY_CLASS, DATE_OF_BIRTH, GPA
};

void sortList(StudentList * list);
void sortList(StudentList * list, int sortField, int sortAlgo);

void swap(Student ** student1, Student ** student2);

void selectionSort(StudentList * list, SortField sortField);
void insertionSort(StudentList * list, SortField sortField);
void quickSort(StudentList * list, SortField sortField);
void mergeSort(StudentList * list, SortField sortField);
void heapSort(StudentList * list, SortField sortField);
