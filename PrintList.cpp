#include "stdafx.h"
#include "PrintList.h"
#include "ManagingMenu.h"
#include <iostream>
#include <conio.h>
#include "console.h"
#include "SortList.h"

void printList(StudentList * list)
{
	Menu * printMenu = createPrintMenu();
	int itemSelected = 0;

	do
	{
		printMenu->displayMenu(itemSelected);
		itemSelected = printMenu->getMenuItem(itemSelected);
		//select functions to print list
		switch (itemSelected)
		{
		case 0:
		{
			printStudyClass(list);
			break;
		}
			
		case 1:
		{
			printAllList(list);
			break;
		}
			
		case 2:
		{
			break;
		}
			
		}
	} while (itemSelected != printMenu->getMenuSize() - 1);
}

void printStudyClass(StudentList * list)
{
	//sort list by study class
	selectionSortStudyClass(list);
	//print each class
	TextColor(ColorCode_DarkBlue);
	std::cout << "In danh sach sinh vien theo lop: ";
	TextColor(default_ColorCode);
	printAllList(list);
}

void printAllList(StudentList * list)
{
	if (list->isEmpty())
	{
		std::cout << "Khong co sinh vien. Nhan phim bat ky de quay lai...";
		_getch();
		return;
	}
	
	drawTable(list->getFirstNode());

}

void drawTable(Node * firstNode)
{
	if (firstNode == NULL)
	{
		std::cout << "Khong co sinh vien. Nhan phim bat ky de quay lai...";
		_getch();
		return;
	}

	clrscr();

	//count the list size
	size_t listSize = 0;

	{
		Node * temp = firstNode;
		
		while (temp != NULL)
		{
			listSize++;
			temp = temp->getNextNode();
		}
	}
	
	//calculate each column width to draw table
	size_t orderColumnWidth = 5;
	size_t nameColumnWidth = 0;	//find later
	size_t studentIdColumnWidth = 10;
	size_t studyClassColumnWidth = 0;	//find later
	size_t dobColumnWidth = 12;
	size_t gpaColumnWidth = 9;

	//find the length of each column
	//find the longest name	and longest studyClass name
	Node * currentNode = firstNode;
	while (currentNode != NULL)
	{
		//name length
		size_t length = currentNode->getStudent()->getFullName().length();
		if (length > nameColumnWidth)
		{
			nameColumnWidth = length;
		}

		//studyClass length
		length = currentNode->getStudent()->getFullName().length();
		if (length > studyClassColumnWidth)
		{
			studyClassColumnWidth = length;
		}

		currentNode = currentNode->getNextNode();
	}

	nameColumnWidth += 2;
	studyClassColumnWidth += 2;

	size_t tableWidth = orderColumnWidth + nameColumnWidth + studentIdColumnWidth
		+ studyClassColumnWidth + dobColumnWidth + gpaColumnWidth + 7;

	//draw table
	//draw title
	std::string title = "DANH SACH SINH VIEN";

	size_t indentSpace = (tableWidth - title.length()) / 2;

	gotoXY(indentSpace, 0);
	std::cout << title << std::endl;

	//draw the skeleton

	size_t * xCOORD = new size_t[7];
	xCOORD[0] = 0;
	xCOORD[1] = orderColumnWidth + 1;
	xCOORD[2] = xCOORD[1] + nameColumnWidth + 1;
	xCOORD[3] = xCOORD[2] + studentIdColumnWidth + 1;
	xCOORD[4] = xCOORD[3] + studyClassColumnWidth + 1;
	xCOORD[5] = xCOORD[4] + dobColumnWidth + 1;
	xCOORD[6] = xCOORD[5] + gpaColumnWidth + 1;	

	size_t topEdge = 1;	//the line number of top edge of table

	system("color F0");
	TextColor(240);
	
	//draw top edge
	{
		std::cout << (char)218;
		for (size_t column = 0; column < tableWidth - 2; column++)
		{
			std::cout << (char)196;
		}
		std::cout << (char)191;;
		for (size_t i = 1; i < 6; i++)
		{
			gotoXY(xCOORD[i], 1);
			std::cout << (char)194;
		}
	}
	
	//draw middle of table
	size_t tableLength = listSize * 2 + 1;	//doesnt count the top edge
	for (size_t line = 2; line < tableLength + 2; line += 2)
	{
		//draw the edges between columns and the outside edges of table
		for (size_t j = 0; j < 7; j++)
		{
			gotoXY(xCOORD[j], line);
			std::cout << (char) 179;
		}

		size_t commonEdgeLine = line + 1;
		//draw the common point of two lines on the left edge of the table
		gotoXY(0, commonEdgeLine);
		std::cout << (char)195;

		//draw the common edge between two lines
		for (size_t j = 0; j < tableWidth - 2; j++)
		{
			std::cout << (char)196;
		}

		//draw the common point of two lines on the right edge of the table
		std::cout << (char)180;

		//draw the common point of four boxes in the table
		for (size_t j = 1; j < 6; j++)
		{
			gotoXY(xCOORD[j], commonEdgeLine);
			std::cout << (char)197;
		}

	}

	//fix bottom edge of table
	//fix two bottom corners of the table
	size_t bottomEdge = tableLength + 2;
	gotoXY(0, bottomEdge);
	std::cout << (char)192;
	gotoXY(tableWidth - 1, bottomEdge);
	std::cout << (char)217;

	//fix all the common points of two boxes on the bottom of table
	for (size_t i = 1; i < 6; i++)
	{
		gotoXY(xCOORD[i], bottomEdge);
		std::cout << (char)193;
	}
	
	//print information
	gotoXY(xCOORD[0] + 2, topEdge + 1);
	std::cout << "STT";

	indentSpace = (nameColumnWidth - 6) / 2 + 1;
	gotoXY(xCOORD[1] + 1 + indentSpace, topEdge + 1);
	std::cout << "HO TEN";

	indentSpace = (studentIdColumnWidth - 5) / 2;
	gotoXY(xCOORD[2] + 1 + indentSpace, topEdge + 1);
	std::cout << "MA SV";

	indentSpace = (studyClassColumnWidth - 7) / 2;
	gotoXY(xCOORD[3] + 1 + indentSpace, topEdge + 1);
	std::cout << "LOP HOC";

	indentSpace = (dobColumnWidth - 9) / 2;
	gotoXY(xCOORD[4] + 1 + indentSpace, topEdge + 1);
	std::cout << "NGAY SINH";

	indentSpace = (gpaColumnWidth - 7) / 2;
	gotoXY(xCOORD[5] + 1 + indentSpace, topEdge + 1);
	std::cout << "DIEM TB";

	//print students info
	size_t studentOrder = 1;
	Node * temp = firstNode;
	for (size_t line = topEdge + 3; line < bottomEdge; line += 2)
	{
		gotoXY(xCOORD[0] + 2, line);
		std::cout << studentOrder;

		gotoXY(xCOORD[1] + 1, line);
		std::cout << temp->getStudent()->getFullName();

		gotoXY(xCOORD[2] + 1, line);
		std::cout << temp->getStudent()->getStudentID();

		gotoXY(xCOORD[3] + 1, line);
		std::cout << temp->getStudent()->getStudyClass();

		gotoXY(xCOORD[4] + 1, line);
		std::cout << temp->getStudent()->getDateOfBirth()->toString();

		gotoXY(xCOORD[5] + 1, line);
		std::cout << temp->getStudent()->getGPA();

		temp = temp->getNextNode();
		studentOrder++;
		
	}

	gotoXY(0, bottomEdge + 2);
	std::cout << "Nhan phim bat ky de quay tro lai . . .";
	
	_getch();
}
