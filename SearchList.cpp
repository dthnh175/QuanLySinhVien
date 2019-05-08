#include "stdafx.h"
#include "SearchList.h"
#include "PrintList.h"
#include "ManagingMenu.h"
#include "console.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <conio.h>

void searchList(StudentList * list)
{
	if (list->isEmpty())
	{
		TextColor(ColorCode_DarkRed);
		std::cout << "\n**Danh sach rong. Nhan phim bat ky de quay lai. . .";
		TextColor(default_ColorCode);
		_getch();
		return;
	}

	//	select field to search
	Menu * searchFieldMenu = createSearchFieldMenu();
	int searchField = 0;
	do
	{
		searchFieldMenu->displayMenu(searchField);
		searchField = searchFieldMenu->getMenuItem(searchField);
		if (searchField != searchFieldMenu->getMenuSize() - 1)
		{
			//	select algorithm to search
			Menu * searchAlgoMenu = createSearchAlgoMenu();
			int searchAlgo = 0;
			do
			{
				searchAlgoMenu->displayMenu(searchAlgo);
				searchAlgo = searchAlgoMenu->getMenuItem(searchAlgo);
				if (searchAlgo != searchAlgoMenu->getMenuSize() - 1)
				{
					std::string keyWord;
					std::cout << "Nhap tu khoa tim kiem: ";
					std::getline(std::cin, keyWord);
					Node * result = searchList(list, searchField, searchAlgo, keyWord);

					drawTable(result);

				}
			} while (searchAlgo != searchAlgoMenu->getMenuSize() - 1);
		}
	} while (searchField != searchFieldMenu->getMenuSize() - 1);
}

Node * searchList(StudentList * list, int searchField, int searchAlgo, std::string keyWord)
{
	switch (searchField)
	{
	case 0:
	{
		if (searchAlgo == 0)
		{
			return linearSearchName(list, keyWord);
		}
		if (searchAlgo == 1)
		{
			return binarySearchName(list, keyWord);
		}
		break;
	}

	case 1:
	{
		if (searchAlgo == 0)
		{
			return linearSearchID(list, keyWord);
		}
		if (searchAlgo == 1)
		{
			return binarySearchID(list, keyWord);
		}
		break;
	}

	case 2:
	{
		if (searchAlgo == 0)
		{
			return linearSearchDOB(list, keyWord);
		}
		if (searchAlgo == 1)
		{
			return binarySearchDOB(list, keyWord);
		}
		break;
	}
	
	case 3:
	{
		if (searchAlgo == 0)
		{
			return linearSearchGPA(list, keyWord);
		}
		if (searchAlgo == 1)
		{
			return binarySearchGPA(list, keyWord);
		}
		break;
	}

	case 4:
	{
		if (searchAlgo == 0)
		{
			return linearSearchStudyClass(list, keyWord);
		}
		if (searchAlgo == 1)
		{
			return binarySearchStudyClass(list, keyWord);
		}
		break;
	}

	}
}

Node * linearSearchName(StudentList * list, std::string keyWord)
{
	//traverse all the list, using REGEX to look for the nodes that contains the students with the nameSearch
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(keyWord.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;
	

	while (currentNode != NULL)
	{
		const std::string name = currentNode->getStudent()->getFullName();

		if (std::regex_search(name, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * linearSearchID(StudentList * list, std::string keyWord)
{
	//traverse all the list, using REGEX to look for the nodes that contains the students with the nameSearch
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(keyWord.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;

	while (currentNode != NULL)
	{
		const std::string currentStudentID = currentNode->getStudent()->getStudentID();

		if (std::regex_search(currentStudentID, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * linearSearchDOB(StudentList * list, std::string keyWord)
{
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(keyWord.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;

	while (currentNode != NULL)
	{
		const std::string dob = currentNode->getStudent()->getDateOfBirth()->toString();

		if (std::regex_search(dob, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * linearSearchGPA(StudentList * list, std::string GPA)
{
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(GPA.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;

	while (currentNode != NULL)
	{
		std::ostringstream oss;
		oss << currentNode->getStudent()->getGPA();
		const std::string gpaStr = oss.str();

		if (std::regex_search(gpaStr, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * linearSearchStudyClass(StudentList * list, std::string keyWord)
{
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(keyWord.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;

	while (currentNode != NULL)
	{
		const std::string currentStudyClass = currentNode->getStudent()->getStudyClass();

		if (std::regex_search(currentStudyClass, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * binarySearchName(StudentList * list, std::string keyWord)
{
	//traverse all the list, using REGEX to look for the nodes that contains the students with the nameSearch
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(keyWord.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;


	while (currentNode != NULL)
	{
		const std::string name = currentNode->getStudent()->getFullName();

		if (std::regex_search(name, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * binarySearchID(StudentList * list, std::string keyWord)
{
	//traverse all the list, using REGEX to look for the nodes that contains the students with the nameSearch
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(keyWord.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;

	while (currentNode != NULL)
	{
		const std::string currentStudentID = currentNode->getStudent()->getStudentID();

		if (std::regex_search(currentStudentID, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * binarySearchDOB(StudentList * list, std::string keyWord)
{
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(keyWord.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;

	while (currentNode != NULL)
	{
		const std::string dob = currentNode->getStudent()->getDateOfBirth()->toString();

		if (std::regex_search(dob, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * binarySearchGPA(StudentList * list, std::string GPA)
{
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(GPA.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;

	while (currentNode != NULL)
	{
		std::ostringstream oss;
		oss << currentNode->getStudent()->getGPA();
		const std::string gpaStr = oss.str();

		if (std::regex_search(gpaStr, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}

Node * binarySearchStudyClass(StudentList * list, std::string keyWord)
{
	Node * currentNode = list->getFirstNode();
	Node * searchResult = NULL;

	std::regex reg(keyWord.c_str(), std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch matches;

	while (currentNode != NULL)
	{
		const std::string currentStudyClass = currentNode->getStudent()->getStudyClass();

		if (std::regex_search(currentStudyClass, matches, reg))
		{
			if (searchResult == NULL)
			{
				//create searchResult
				searchResult = new Node(currentNode->getStudent());
			}
			else
			{
				//append to the list
				Node * temp = searchResult;
				while (temp->getNextNode() != NULL)
				{
					temp = temp->getNextNode();
				}
				Node * nodeFound = new Node(currentNode->getStudent());
				temp->setNextNode(nodeFound);
			}
		}

		currentNode = currentNode->getNextNode();
	}

	return searchResult;
}


/*Create a menu from search result */
Menu * createSearchResultMenu(Node * firstNode)
{
	std::string title = "KET QUA TIM KIEM";

	//count number of results
	Node * temp = firstNode;
	int resultCount = 0;
	while (temp != NULL)
	{
		resultCount++;
		temp = temp->getNextNode();
	}

	//create menu items from student's info
	temp = firstNode;
	const int menuSize = resultCount + 1;
	std::string * result = new std::string[menuSize];
	for (int i = 0; i < resultCount; i++)
	{
		Student * currentStudent = temp->getStudent();
		
		result[i] = currentStudent->toString();
		temp = temp->getNextNode();
	}
	result[resultCount] = "Quay lai";
	Menu * menu = new Menu(title, menuSize, result);
	return menu;
}

