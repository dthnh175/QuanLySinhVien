#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "Menu.h"
#include "console.h"

/*Only for declaring new instance to use later*/
Menu::Menu()
{
	//do nothing
}

Menu::Menu(std::string menuTitle, int size, std::string * menuItem)
{
	this->menuTitle = menuTitle;
	this->size = size;
	this->menuItem = new std::string[size];
	for (int i = 0; i < size; i++)
	{
		this->menuItem[i] = menuItem[i];
	}
}

void Menu::setTitle(std::string title)
{
	this->menuTitle = title;
}

void Menu::setMenuItem(int order, std::string newItem)
{
	if (order > this->size || order < 0)
	{
		return;
	}

	this->menuItem[order] = newItem;
}

int Menu::getMenuSize()
{
	return this->size;
}

void Menu::deleteMenuItem(int order)
{
	if (order >= size)
	{
		return;
	}
	for (int i = order; i < size - 1; i++)
	{
		menuItem[i] = menuItem[i + 1];
	}
	this->size--;
}

void Menu::displayMenu(int lineCursor)
{
	clrscr();
	TextColor(ColorCode_Red);
	std::cout << this->menuTitle << std::endl << std::endl;
	for (int i = 0; i < this->size; i++)
	{
		TextColor(ColorCode_Black);
		if (i == lineCursor)
		{
			TextColor(176);
		}
		std::cout << menuItem[i] << std::endl;
		TextColor(ColorCode_Black);
	}
}

keyPressStatus Menu::getKeyPressStatus(unsigned char keyPress)
{
	if (keyPress == 224)
	{
		unsigned char c;
		c = _getch();
		switch (c)
		{
		case 72:
			return UP;
		case 80:
			return DOWN;
		case 75:
			return LEFT;
		case 77:
			return RIGHT;
		default:
			return NONE;
		}
	}
	else if (keyPress == 13) {
		return ENTER;
	}
	else return NONE;
}

int Menu::getMenuItem(int currentLineCursor)
{
	//	return user's choice of menu item
	int lineCursor = currentLineCursor;
	while (true)
	{
		unsigned char keyPress = _getch();
		unsigned char keyPressed = getKeyPressStatus(keyPress);
		switch (keyPressed)
		{
		case UP:
			if (lineCursor == 0) {
				lineCursor = this->size - 1;
			}
			else {
				lineCursor--;
			}
			break;
		case DOWN:
			if (lineCursor == this->size - 1) {
				lineCursor = 0;
			}
			else {
				lineCursor++;
			}
			break;
		case ENTER:
		{
			system("color F0");
			return lineCursor;
		}
			
		default:
			break;
		}
		
		displayMenu(lineCursor);
	}
}


