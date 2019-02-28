#pragma once
#include <string>

enum keyPressStatus {
	UP, DOWN, LEFT, RIGHT, ENTER, NONE
};

class Menu {

private:
	int size;
	std::string menuTitle;
	std::string *menuItem;

public:
	Menu();
	Menu(std::string menuTitle, int menuSize, std::string * menuItem);
	
	void setTitle(std::string title);
	void setMenuItem(int order, std::string newItem);
	int getMenuSize();
	void deleteMenuItem(int order);

	//display and select operations
	void displayMenu(int);
	keyPressStatus getKeyPressStatus(unsigned char);
	int getMenuItem(int currentLine);
	
};
