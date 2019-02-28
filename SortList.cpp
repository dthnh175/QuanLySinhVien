#include "stdafx.h"
#include "SortList.h"
#include <iostream>
#include <conio.h>

void sortList(StudentList * list)
{
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
	switch (sortField)
	{

	}
}

void swap(Student ** student1, Student ** student2)
{
	Student * temp = *student1;
	*student1 = *student2;
	*student2 = temp;
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
