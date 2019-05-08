#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include "ManagingMenu.h"
#include "Student.h"


Menu * createMainMenu()
{
	std::string mainMenuTitle = "CHUONG TRINH QUAN LY SINH VIEN";
	std::string mainMenuItem[6] = {
		"1. Chinh sua ho so sinh vien",
		"2. In ho so sinh vien",
		"3. Sap xep ho so sinh vien",
		"4. Tim kiem sinh vien",
		"5. Thong ke",
		"6. Thoat"
	};
	Menu * mainMenu = new Menu(mainMenuTitle, 6, mainMenuItem);
	return mainMenu;
}

Menu * createEditMenu()
{
	std::string menuTitle = "CHINH SUA DANH SACH SINH VIEN";
	std::string editMenuItem[4] = {
		"1. Them sinh vien",
		"2. Sua thong tin sinh vien",
		"3. Xoa sinh vien",
		"4. Quay lai"
	};
	Menu * editMenu = new Menu(menuTitle, 4, editMenuItem);
	return editMenu;
}

Menu * createPrintMenu()
{
	std::string menuTitle = "IN THONG TIN SINH VIEN";
	std::string printMenuItem[3] {
		"1. In theo lop",
		"2. In toan bo",
		"3. Quay lai"
	};
	Menu * printMenu = new Menu(menuTitle, 3, printMenuItem);
	return printMenu;
}

Menu * createSortFieldMenu()
{
	std::string menuTitle = "CHON TRUONG DE SAP XEP";
	const size_t menuSize = 6;
	std::string keySortMenuItem[menuSize] = {
		"1. Ho ten",
		"2. Ma SV",
		"3. Lop hoc",
		"4. Ngay sinh",
		"5. Diem Trung binh",
		"6. Quay lai"
	};
	Menu * keySortMenu = new Menu(menuTitle, menuSize, keySortMenuItem);
	return keySortMenu;
}

Menu * createSortAlgoMenu()
{
	std::string menuTitle = "CHON THUAT TOAN SAP XEP";
	std::string sortMenuItem[6] = {
		"1. Sap xep Chon",
		"2. Sap xep Chen",
		"3. Sap xep QuickSort",
		"4. Sap xep MergeSort",
		"5. Sap xep HeapSort",
		"6. Quay lai"
	};
	Menu * sortMenu = new Menu(menuTitle, 6, sortMenuItem);
	return sortMenu;
}

Menu * createSearchFieldMenu()
{
	std::string menuTitle = "CHON TRUONG DE TIM KIEM SINH VIEN";
	const int menuSize = 7;
	std::string searchFieldMenuItem[menuSize] = {
		"1. Ho ten",
		"2. Ma SV",
		"3. Ngay sinh",
		"4. Diem Trung binh",
		"5. Lop",
		"6. In toan bo danh sach",
		"7. Quay lai"
	};
	Menu * searchFieldMenu = new Menu(menuTitle, menuSize, searchFieldMenuItem);
	return searchFieldMenu;
}

Menu * createSearchAlgoMenu()
{
	std::string menuTitle = "CHON THUAT TOAN TIM KIEM";
	const int menuSize = 3;
	std::string searchMenuItem[menuSize] = {
		"1. Tim kiem tuan tu",
		"2. Tim kiem nhi phan",
		"3. Quay lai"
	};
	Menu * searchMenu = new Menu(menuTitle, menuSize, searchMenuItem);
	return searchMenu;
}

Menu * createStatMenu()
{
	std::string menuTitle = "CHON PHUONG THUC THONG KE";
	const int menuSize = 3;
	std::string statMenuItem[menuSize] = 
	{
		"1. Thong ke so luong sinh vien theo lop",
		"2. Thong ke phan loai ket qua hoc tap",
		"3. Quay lai"
	};
	Menu * statMenu = new Menu(menuTitle, menuSize, statMenuItem);
	return statMenu;
}

//Use for editting student info and delete student
Menu * createClassesMenu()
{
	//Count number of folders (classes)

	return nullptr;
}

Menu * createStudentInfoMenu(Student * student)
{
	std::string title = "SINH VIEN ";
	title.append(student->getFullName());

	const int menuSize = 7;
	std::string * menuItem = new std::string[menuSize];
	menuItem[0] = "Ho ten		|";
	menuItem[0].append(student->getFullName());
	menuItem[1] = "Ma SV		|";
	menuItem[1].append(student->getStudentID());
	menuItem[2] = "Lop hoc		|";
	menuItem[2].append(student->getStudyClass());
	menuItem[3] = "Ngay sinh	|";
	menuItem[3].append(student->getDateOfBirth()->toString());
	menuItem[4] = "Diem TB		|";
	std::ostringstream oss;
	oss << student->getGPA();
	menuItem[4].append(oss.str());
	menuItem[5] = "Ten file	|";
	menuItem[5].append(student->getFileName());
	menuItem[6] = "Quay lai";

	Menu * studentInfo = new Menu(title, menuSize, menuItem);

	return studentInfo;
}
