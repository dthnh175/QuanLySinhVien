#include "stdafx.h"
#include "Statistic.h"

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

		}
	} while (choice != statMenu->getMenuSize() - 1);
}
