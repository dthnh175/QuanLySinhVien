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

int partition(Student** arr, int low, int high, SortField sortField);
void quickSort(Student** arr, int low, int high, SortField sortField);
void quickSort(StudentList * list, SortField sortField);

void merge(Student ** arr, int leftIndex, int midIndex, int rightIndex, SortField sortField);
void mergeSort(Student ** arr, int leftIndex, int rightIndex, SortField sortField);
void mergeSort(StudentList * list, SortField sortField);

void heapSort(StudentList * list, SortField sortField);
void heapifyName(Student ** arr, int n, int i);
void heapifyStudentID(Student ** arr, int n, int i);
void heapifyStudyClass(Student ** arr, int n, int i);
void heapifyDOB(Student ** arr, int n, int i);
void heapifyGPA(Student ** arr, int n, int i);
