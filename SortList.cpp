#include "stdafx.h"
#include "SortList.h"
#include <iostream>
#include <conio.h>
#include "console.h"
#include "PrintList.h"

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

					//print the list after sorting
					drawTable(list->getFirstNode());
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

	switch (sortField)
	{
	case SortField::NAME:	//sort by name
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				std::string firstName1 = students[minIndex]->getFirstName();
				std::string firstName2 = students[j]->getFirstName();

				//compare first names
				if (firstName1.compare(firstName2) > 0)
				{
					minIndex = j;
				}
				else if (firstName1.compare(firstName2) == 0)
				{
					std::string lastName1 = students[minIndex]->getLastName();
					std::string lastName2 = students[j]->getLastName();

					//if two first names are the same then compare last names
					if (lastName1.compare(lastName2) > 0)
					{
						minIndex = j;
					}
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	case SortField::STUDENT_ID:	//sort by studentID
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->getStudentID().compare(students[j]->getStudentID()) > 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	case SortField::STUDY_CLASS:	//sort by studyClass
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->getStudyClass().compare(students[j]->getStudyClass()) > 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	case SortField::DATE_OF_BIRTH:	//sort by DOB
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->getDateOfBirth()->compare(students[j]->getDateOfBirth()) > 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	case SortField::GPA:	//sort by GPA
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->getGPA() > students[j]->getGPA())
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
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
