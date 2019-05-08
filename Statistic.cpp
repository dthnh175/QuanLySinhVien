#include "stdafx.h"
#include "Statistic.h"
#include "ManagingMenu.h"
#include "console.h"
#include "SortList.h"
#include "ClassNode.h"

#include <iostream>
#include <conio.h>


#define GACH_NGANG (char)196
#define GOC_CHU_T_TREN (char)194
#define GOC_CHU_T_DUOI (char)193
#define GOC_CHU_T_NGANG_TRAI (char)195
#define GOC_CHU_THAP (char)197

void statistic(StudentList * list)
{
	Menu * statMenu = createStatMenu();
	int choice = 0;
	do
	{
		statMenu->displayMenu(choice);
		choice = statMenu->getMenuItem(choice);
		if (choice != statMenu->getMenuSize() - 1)
		{
			statistic(list, choice);
		}
	} while (choice != statMenu->getMenuSize() - 1);
}

void statistic(StudentList * list, int choice)
{
	switch (choice)
	{
	case 0:	//print statistic about each study class' number of students
	{
		statAllClass(list);
		break;
	}

	case 1:	//print statistic about students' learning result
	{
		classifyStudent(list);
		break;
	}
	}
}

void statAllClass(StudentList * list)
{
	if (list->isEmpty())
	{
		std::cout << "Khong co sinh vien. Nhan phim bat ky de quay lai. . .";
		_getch();
		return;
	}

	clrscr();

	//sort list by class
	selectionSort(list, SortField::STUDY_CLASS);

	//count number of classes and number of students in each class	
	int classCount = 0;
	
	ClassNode * firstClassNode = new ClassNode();
	ClassNode * tempClassNode = new ClassNode();

	//traverse through the list
	Node * tempNode = list->getFirstNode();
	std::string className;
	size_t longestClassName = 0;
	while (tempNode != NULL)
	{
		if (tempNode == list->getFirstNode())
		{
			className = tempNode->getStudent()->getStudyClass();
			longestClassName = className.length();
			firstClassNode = new ClassNode(className);
			tempClassNode = firstClassNode;

			//increase the number of classes
			classCount++;
		}
		else
		{
			//get the class name of the current student
			std::string currentClassName = tempNode->getStudent()->getStudyClass();

			//if this current class name is different from the previous then create a new class node
			if (currentClassName.compare(className) != 0)
			{
				ClassNode * newClassNode = new ClassNode(currentClassName);
				tempClassNode->setNextClassNode(newClassNode);
				tempClassNode = tempClassNode->getNextClassNode();
				className = currentClassName;

				//increase number of classes
				classCount++;

				//check to find longest class name
				if (currentClassName.length() > longestClassName)
				{
					longestClassName = currentClassName.length();
				}

			}
			else
			{
				//if this current class name is the same as the previous one
				//just increase the number of students by one.
				tempClassNode->incClassSize();
				
			}
		}

		tempNode = tempNode->getNextNode();
	}

	size_t studentCount = list->getSize();
	//draw table
	std::string firstColumnName = "Ten lop",
		secondColumnName = "So sinh vien";

	//draw the skeleton
	//detect the width of each column
	int firstColumnWidth,
		secondColumnWidth;
	if (firstColumnName.length() > longestClassName)
	{
		firstColumnWidth = firstColumnName.length();
	}
	else
	{
		firstColumnWidth = longestClassName;
	}

	secondColumnWidth = secondColumnName.length();	//because it's long enough

	//calculate the width of the table
	size_t tableWidth = 1 + firstColumnWidth + 1 + secondColumnWidth + 1;

	//draw the skeleton
	//draw all horizontal edges
	size_t firstLine = 0;
	size_t lastLine = firstLine + 1 + classCount * 2 + 3;

	{
		size_t edgeCount = 0;
		size_t currentLine = 0;
		while (edgeCount < classCount + 3)
		{
			gotoXY(0, currentLine);
			for (int i = 0; i < tableWidth; i++)
			{
				std::cout << (char)196;
			}
			std::cout << "\n";
			currentLine += 2;
			edgeCount++;
		}		
	}

	//draw all vertical edges
	size_t firstVerticalEdge = 0,
		secondVerticalEdge = firstColumnWidth + 1,
		thirdVerticalEdge = tableWidth - 1;

	{
		size_t lineCount = 0;
		size_t currentLine = 1;
		while (lineCount < classCount + 2)
		{
			gotoXY(firstVerticalEdge, currentLine);
			std::cout << (char)179;
			gotoXY(secondVerticalEdge, currentLine);
			std::cout << (char)179;
			gotoXY(thirdVerticalEdge, currentLine);
			std::cout << (char)179;

			lineCount++;
			currentLine += 2;
		}
	}

	//draw all corners
	{
		//draw top edge conrners
		gotoXY(firstVerticalEdge, firstLine);
		std::cout << (char)218;
		gotoXY(secondVerticalEdge, firstLine);
		std::cout << (char)194;
		gotoXY(thirdVerticalEdge, firstLine);
		std::cout << (char)191;

		//draw bottom edge corners
		gotoXY(firstVerticalEdge, lastLine);
		std::cout << (char)192;
		gotoXY(secondVerticalEdge, lastLine);
		std::cout << (char)193;
		gotoXY(thirdVerticalEdge, lastLine);
		std::cout << (char)217;

		//draw all corners at the middle of the table
		size_t lineCount = 0;
		size_t currentLine = firstLine + 2;
		while (lineCount < classCount + 1)
		{
			gotoXY(firstVerticalEdge, currentLine);
			std::cout << (char)195;
			gotoXY(secondVerticalEdge, currentLine);
			std::cout << (char)197;
			gotoXY(thirdVerticalEdge, currentLine);
			std::cout << (char)180;

			lineCount++;
			currentLine += 2;
		}
		gotoXY(firstVerticalEdge, firstLine + 2);
	}

	//write content into boxes
	//write columns name
	gotoXY(firstVerticalEdge + 1, firstLine + 1);
	std::cout << firstColumnName;
	gotoXY(secondVerticalEdge + 1, firstLine + 1);
	std::cout << secondColumnName;

	//write classes names and their number of students
	{
		ClassNode * temp = firstClassNode;
		size_t currentLine = firstLine + 1 + 2;
		for (int i = 0; i < classCount; i++)
		{
			gotoXY(firstVerticalEdge + 1, currentLine);
			std::cout << temp->getClassName();
			gotoXY(secondVerticalEdge + 1 + secondColumnName.length() / 2, currentLine);
			std::cout << temp->getStudentCount();

			currentLine += 2;
			temp = temp->getNextClassNode();
		}
	}
	
	//write sum column
	{
		std::string sumColumnName = "Tong";
		gotoXY(firstVerticalEdge + (firstColumnName.length() - sumColumnName.length()) / 2, lastLine - 1);
		std::cout << sumColumnName;
		gotoXY(secondVerticalEdge + 1 + secondColumnName.length() / 2, lastLine - 1);
		std::cout << list->getSize();
	}
	
	gotoXY(0, lastLine + 2);
	std::cout << "Nhan phim bat ky de quay lai . . .";

	_getch();

}

void classifyStudent(StudentList * list)
{

	if (list->isEmpty())
	{
		std::cout << "Khong co sinh vien. Nhan phim bat ky de quay lai. . .";
		_getch();
		return;
	}

	clrscr();

	//sort list by class
	selectionSort(list, SortField::STUDY_CLASS);

	//assign all students in the list to an array (so that their data is not changed after this procedure)
	int listSize = list->getSize();
	Student * studentArr = new Student[listSize];

	//calculate the number of classes
	//traverse thru the list to get to each student
	Node * tempNode = list->getFirstNode();
	size_t arrayIndex = 0;
	while (tempNode != NULL)
	{
		studentArr[arrayIndex] = *(tempNode->getStudent());
		
		arrayIndex++;
		tempNode = tempNode->getNextNode();
	}

	/*create all class nodes from the array*/

	//traverse thru the array to count each class size
	std::string className = studentArr[0].getStudyClass();
	int classCount = 1;

	Node * firstStudentNode = new Node(&studentArr[0]);

	ClassNode * firstClassNode = new ClassNode(className, firstStudentNode);
	ClassNode * tempClassNode = firstClassNode;

	for (int i = 1; i < listSize; i++)
	{
		std::string currentClassName = studentArr[i].getStudyClass();

		if (currentClassName.compare(className) != 0)
		{
			//if another class is detected

			//create a new class node
			firstStudentNode = new Node(&studentArr[i]);
			ClassNode * newClassNode = new ClassNode(currentClassName, firstStudentNode);

			//set the temp ClassNode to the next
			tempClassNode->setNextClassNode(newClassNode);
			tempClassNode = tempClassNode->getNextClassNode();

			//update some temporary variables
			classCount++;
			className = currentClassName;
		}
		else
		{
			//still a student in that class

			//increase this class size by one
			tempClassNode->incClassSize();

			//add new student to the current ClassNode
			Node * newStudentNode = new Node(&studentArr[i]);
			tempClassNode->addNewStudentNode(newStudentNode);

		}
	}
	

	/*Classify all students in each class*/

	tempClassNode = firstClassNode;

	while (tempClassNode != NULL)
	{
		tempClassNode->classifyStudents();

		tempClassNode = tempClassNode->getNextClassNode();
	}


	/*Draw table*/
	
	/**Draw the skeleton*/
	//Detect the width of each column
	std::string title = "PHAN LOAI SINH VIEN";
	std::string classNameColumn = "Ten lop";
	std::string classifyColumnName[5] =
	{
		"Xuat sac",
		"Gioi",
		"Kha",
		"Trung binh",
		"Yeu"
	};
	std::string excellentColumnName = "Xuat sac",
		goodColumnName = "Gioi",
		prettyGoodColumnName = "Kha",
		averageColumnName = "Trung binh",
		weakColumnName = "Yeu";
	std::string quantityColumnName = "SL",
		percentageColumnName = "%";

	int bigVerticalEdgeCount = 7;

	//calculate class name column width
	int classNameWidth = classNameColumn.length();	
	tempClassNode = firstClassNode;
	while (tempClassNode != NULL)
	{
		if (tempClassNode->getClassName().length() > classNameWidth)
		{
			classNameWidth = tempClassNode->getClassName().length();
		}

		tempClassNode = tempClassNode->getNextClassNode();
	}

	//calculate each other column width
	const int quantityWidth = 3, percentageWidth = 3;	//this is two child columns in each big column

	int bigColumnWidth[5] =
	{
		excellentColumnName.length(),
		goodColumnName.length(),
		prettyGoodColumnName.length(),
		averageColumnName.length(),
		weakColumnName.length(),
	};

	for (int i = 0; i < 5; i++)
	{
		if (quantityWidth + 1 /*this is the width of the middle vertical edge*/ + percentageWidth > bigColumnWidth[i])
		{
			bigColumnWidth[i] = quantityWidth + 1 + percentageWidth;
		}
	}

	//Calculate the width of the table
	int tableWidth = classNameWidth + bigVerticalEdgeCount;
	for (int i = 0; i < 5; i++)
	{
		tableWidth += bigColumnWidth[i];
	}

	//Print title
	{
		int indentSpace = (tableWidth - title.length()) / 2;
		gotoXY(indentSpace + 1, 0);
		std::cout << title;
	}

	//Draw all horizontal edges
	int firstLine = 1,
		lastLine = firstLine + 4 + classCount * 2 + 2;

	{
		int currentLine = firstLine;
		for (int i = 0; i < classCount + 4; i++)
		{
			gotoXY(0, currentLine);
			for (int j = 0; j < tableWidth; j++)
			{
				std::cout << (char)196;
			}
			std::cout << "\n";
			currentLine += 2;
		}
	}
	

	//Draw all vertical edges

	//Draw all "big" vertical edges

	int bigVerticalEdge[7] =
	{
		0,
		0 + classNameWidth + 1,
		0, 0, 0, 0, 0
	};

	int middleVerticalEdge[5];

	for (int i = 2; i < 7; i++)
	{
		bigVerticalEdge[i] = bigVerticalEdge[i - 1] + bigColumnWidth[i - 2] + 1;

		middleVerticalEdge[i - 2] = bigVerticalEdge[i - 1] + quantityWidth + 1;
	}

	//draw all "big" vertical edges
	{
		int currentLine = firstLine + 1;
		for (int i = 0; i < classCount + 3; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				gotoXY(bigVerticalEdge[j], currentLine);
				std::cout << (char)179;
			}
			currentLine += 2;
		}
	}

	//draw all "small" vertical edges in each big classified column
	{
		int currentLine = firstLine + 3;
		for (int i = 0; i < classCount + 2; i++)
		{
			for (int j = 1; j < 6; j++)
			{
				gotoXY(bigVerticalEdge[j] + quantityWidth + 1, currentLine);
				std::cout << (char)179;
			}
			currentLine += 2;
		}
	}

	//Draw all corners
	//Draw all corners at the top edge
	{
		int currentLine = firstLine;
		gotoXY(0, firstLine);
		std::cout << (char)218;

		for (int i = 1; i < 6; i++)
		{
			gotoXY(bigVerticalEdge[i], currentLine);
			std::cout << (char)194;
		}

		gotoXY(bigVerticalEdge[6], currentLine);
		std::cout << (char)191;
	}

	//Draw all corners at the bottom line
	{
		gotoXY(bigVerticalEdge[0], lastLine);
		std::cout << (char)192;

		for (int i = 1; i < 6; i++)
		{
			gotoXY(bigVerticalEdge[i], lastLine);
			std::cout << (char)193;
		}

		gotoXY(bigVerticalEdge[6], lastLine);
		std::cout << (char)217;
	}

	//Draw all corners in the middle horizontal edge of the top row
	{
		int currentLine = firstLine + 2;

		gotoXY(bigVerticalEdge[0], currentLine);
		std::cout << (char)179;

		for (int i = 0; i < classNameWidth; i++)
		{
			std::cout << ' ';
		}

		std::cout << GOC_CHU_T_NGANG_TRAI;

		for (int i = 2; i < 7; i++)
		{
			gotoXY(bigVerticalEdge[i], currentLine);
			std::cout << (char)197;
		}

		gotoXY(bigVerticalEdge[6], currentLine);
		std::cout << (char)180;
	}

	//Draw all corners in the middle
	{
		int currentLine = firstLine + 4;		

		for (int i = 0; i < classCount + 1; i++)
		{
			gotoXY(bigVerticalEdge[0], currentLine);
			std::cout << GOC_CHU_T_NGANG_TRAI;

			for (int j = 1; j < 6; j++)
			{
				gotoXY(bigVerticalEdge[j], currentLine);
				std::cout << GOC_CHU_THAP;

				gotoXY(middleVerticalEdge[j - 1], currentLine);
				std::cout << GOC_CHU_THAP;
			}

			gotoXY(bigVerticalEdge[6], currentLine);
			std::cout << (char)180;

			currentLine += 2;
		}

		currentLine = firstLine + 2;
		for (int i = 0; i < 5; i++)
		{
			gotoXY(middleVerticalEdge[i], currentLine);
			std::cout << (char)194;

			gotoXY(middleVerticalEdge[i], currentLine + classCount * 2 + 4);
			std::cout << (char)193;
		}
		
	}


	/*Put the content in each box*/
	
	//Write class name and other columns names
	{
		int currentLine = firstLine + 2;
		gotoXY(bigVerticalEdge[0] + 1, currentLine);
		std::cout << classNameColumn;

		currentLine--;
		for (int i = 1; i < 6; i++)
		{
			gotoXY(bigVerticalEdge[i] + 1, currentLine);
			std::cout << classifyColumnName[i - 1];
		}

		currentLine += 2;
		for (int i = 0; i < 5; i++)
		{
			gotoXY(bigVerticalEdge[i + 1] + 1, currentLine);
			std::cout << quantityColumnName;

			gotoXY(middleVerticalEdge[i] + 1, currentLine);
			std::cout << percentageColumnName;
		}

	}

	//Write each class information to the table
	int classifiedCount[5] = { 0, 0, 0, 0, 0 };
	int classifiedPercent[5];
	{
		int currentLine = firstLine + 5;

		tempClassNode = firstClassNode;
		while (tempClassNode != NULL)
		{
			gotoXY(bigVerticalEdge[0] + 1, currentLine);
			std::cout << tempClassNode->getClassName();

			//excellent
			gotoXY(bigVerticalEdge[1] + 1, currentLine);
			std::cout << tempClassNode->getExcellentCount();
			classifiedCount[0] += tempClassNode->getExcellentCount();

			gotoXY(middleVerticalEdge[0] + 1, currentLine);
			std::cout << tempClassNode->getExcellentPercent();

			//good
			gotoXY(bigVerticalEdge[2] + 1, currentLine);
			std::cout << tempClassNode->getGoodCount();
			classifiedCount[1] += tempClassNode->getGoodCount();

			gotoXY(middleVerticalEdge[1] + 1, currentLine);
			std::cout << tempClassNode->getGoodPercent();

			//pretty good
			gotoXY(bigVerticalEdge[3] + 1, currentLine);
			std::cout << tempClassNode->getPrettyGoodCount();
			classifiedCount[2] += tempClassNode->getPrettyGoodCount();

			gotoXY(middleVerticalEdge[2] + 1, currentLine);
			std::cout << tempClassNode->getPrettyGoodPercent();

			//average
			gotoXY(bigVerticalEdge[4] + 1, currentLine);
			std::cout << tempClassNode->getAverageCount();
			classifiedCount[3] += tempClassNode->getAverageCount();

			gotoXY(middleVerticalEdge[3] + 1, currentLine);
			std::cout << tempClassNode->getAveragePercent();

			//weak
			gotoXY(bigVerticalEdge[5] + 1, currentLine);
			std::cout << tempClassNode->getWeakCount();
			classifiedCount[4] += tempClassNode->getWeakCount();

			gotoXY(middleVerticalEdge[4] + 1, currentLine);
			std::cout << tempClassNode->getWeakPercent();

			//update things
			currentLine += 2;
			tempClassNode = tempClassNode->getNextClassNode();
		}
	}
	
	for (int i = 0; i < 5; i++)
	{
		classifiedPercent[i] = (int)(((double)classifiedCount[i] / list->getSize()) * 100);
	}

	//Write the summary row
	{
		int currentLine = lastLine - 1;
		gotoXY(bigVerticalEdge[0] + 1, currentLine);
		std::cout << "TONG";

		for (int i = 0; i < 5; i++)
		{
			gotoXY(bigVerticalEdge[i + 1] + 1, currentLine);
			std::cout << classifiedCount[i];
			gotoXY(middleVerticalEdge[i] + 1, currentLine);
			std::cout << classifiedPercent[i];
		}

	}

	gotoXY(0, lastLine + 2);
	TextColor(249);
	std::cout << "Nhan phim bat ky de quay lai . . .";
	TextColor(240);

	_getch();
}
