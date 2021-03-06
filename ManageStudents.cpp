// ManageStudents.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "StudentList.h"
#include "ManagingMenu.h"
#include "EditList.h"
#include "PrintList.h"
#include "SortList.h"
#include "SearchList.h"
#include "Statistic.h"
#include "console.h"



int main()
{
	system("color F0");

	//create list
	StudentList * list = new StudentList();

	//create main menu
 	Menu *mainMenu = createMainMenu();

	//user chooses action
	int mainMenuItemSelected = 0;
	do
	{
		mainMenu->displayMenu(mainMenuItemSelected);
		mainMenuItemSelected = mainMenu->getMenuItem(mainMenuItemSelected);
		switch (mainMenuItemSelected)
		{

		case 0:	//user wants to edit the list
		{
			editList(list);
			break;
		}

		case 1:	//user wants to print list
		{
			printList(list);
			break;
		}

		case 2:	//user wants to sort the list
		{
			sortList(list);
			break;
		}

		case 3:	//user wants to search students in the list
		{
			searchList(list);
			break;
		}

		case 4:	//statistics
		{
			statistic(list);
			break;
		}

		}
	} while (mainMenuItemSelected != mainMenu->getMenuSize() - 1);

	return EXIT_SUCCESS;
}

