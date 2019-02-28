#include "stdafx.h"
#include "SortList.h"
#include <iostream>
#include <conio.h>
#include "console.h"

void sortList(StudentList * list)
{
	if (list->isEmpty())
	{
		clrscr();
		std::cout << "Danh sach sinh vien rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}

	//select field to sort
	Menu * sortFieldMenu = createSortFieldMenu();
	int sortField = 0;
	do
	{
		sortFieldMenu->displayMenu(sortField);
		sortField = sortFieldMenu->getMenuItem(sortField);

		if (sortField != sortFieldMenu->getMenuSize() - 1)
		{
			//select algorithm to sort
			Menu * sortAlgoMenu = createSortAlgoMenu();
			int sortAlgo = 0;
			do
			{
				sortAlgoMenu->displayMenu(sortAlgo);
				sortAlgo = sortAlgoMenu->getMenuItem(sortAlgo);
				if (sortAlgo != sortAlgoMenu->getMenuSize() - 1)
				{
					//sort the list with the chosen field and algorithm
					sortList(list, sortField, sortAlgo);
				}
			} while (sortAlgo != sortAlgoMenu->getMenuSize() - 1);
		}

	} while (sortField != sortFieldMenu->getMenuSize() - 1);
}

void sortList(StudentList * list, int sortField, int sortAlgo)
{
	SortField field;
	switch (sortField)
	{
	case 0:
	{
		field = SortField::NAME;
		break;
	}
	case 1:
	{
		field = SortField::STUDENT_ID;
		break;
	}
	case 2:
	{
		field = SortField::STUDY_CLASS;
		break;
	}
	case 3:
	{
		field = SortField::DATE_OF_BIRTH;
		break;
	}
	case 4:
	{
		field = SortField::GPA;
		break;
	}
	}

	switch (sortAlgo)
	{
	case 0:
	{
		selectionSort(list, field);
		break;
	}
	case 1:
	{
		insertionSort(list, field);
		break;
	}
	case 2:
	{
		quickSort(list, field);
		break;
	}
	case 3:
	{
		mergeSort(list, field);
		break;
	}
	case 4:
	{
		heapSort(list, field);
		break;
	}
	}
}

void swap(Student ** student1, Student ** student2)
{
	Student * temp = *student1;
	*student1 = *student2;
	*student2 = temp;
}

void selectionSort(StudentList * list, SortField sortField)
{
	Student ** students = list->getStudentArray();

	if (students == NULL)
	{
		std::cout << "Mang sinh vien rong. Nhan phim bat ky de quay lai.";
		_getch();
		return;
	}

	for (size_t i = 0; i < list->getSize(); i++)
	{
		size_t minIndex = i;
		for (size_t j = i; j < list->getSize(); j++)
		{
			switch (sortField)
			{
			case SortField::NAME:	//sort by name
			{
				if (students[minIndex]->getFullName().compare(students[j]->getFullName()) > 0)
				{
					minIndex = j;
				}
				break;
			}
			case SortField::STUDENT_ID:	//sort by studentID
			{
				if (students[minIndex]->getStudentID().compare(students[j]->getStudentID()) > 0)
				{
					minIndex = j;
				}
				break;
			}
			case SortField::STUDY_CLASS:	//sort by studyClass
			{
				if (students[minIndex]->getStudyClass().compare(students[j]->getStudyClass()) > 0)
				{
					minIndex = j;
				}
				break;
			}
			case SortField::DATE_OF_BIRTH:	//sort by DOB
			{
				if (students[minIndex]->getDateOfBirth()->compare(students[j]->getDateOfBirth()) > 0)
				{
					minIndex = j;
				}
				break;
			}
			case SortField::GPA:	//sort by GPA
			{
				if (students[minIndex]->getGPA() > students[j]->getGPA())
				{
					minIndex = j;
				}
				break;
			}
			}
		}
		if (minIndex != i)
		{
			swap(&students[minIndex], &students[i]);
		}
	}

	Node * firstNode = new Node(students[0]);
	Node * temp = firstNode;
	for (size_t i = 1; i < list->getSize(); i++)
	{
		Node * nextNode = new Node(students[i]);
		temp->setNextNode(nextNode);
		temp = temp->getNextNode();
	}

	list->setFirstNode(firstNode);
}

void insertionSort(StudentList * list, SortField sortField)
{
}

void quickSort(StudentList * list, SortField sortField)
{
}

void mergeSort(StudentList * list, SortField sortField)
{
}

void heapSort(StudentList * list, SortField sortField)
{
}

void selectionSortStudyClass(StudentList * list)
{
	Student ** students = list->getStudentArray();

	if (students == NULL)
	{
		std::cout << "Mang sinh vien rong. Nhan phim bat ky de quay lai.";
		_getch();
		return;
	}

	for (size_t i = 0; i < list->getSize(); i++)
	{
		size_t minIndex = i;
		for (size_t j = i; j < list->getSize(); j++)
		{
			if (students[j]->getStudyClass().compare(students[minIndex]->getStudyClass()) < 0)
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			swap(&students[minIndex], &students[i]);
		}
	}

	Node * firstNode = new Node(students[0]);
	Node * temp = firstNode;
	for (size_t i = 1; i < list->getSize(); i++)
	{
		Node * nextNode = new Node(students[i]);
		temp->setNextNode(nextNode);
		temp = temp->getNextNode();
	}

	list->setFirstNode(firstNode);

}
