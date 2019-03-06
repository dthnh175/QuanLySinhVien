#include "stdafx.h"
#include <iostream>
#include "console.h"
#include "EditList.h"
#include "SearchList.h"
#include "Node.h"
#include <conio.h>
#include <fstream>
#include <sstream>



void editList(StudentList * list)
{
	Menu * editMenu = createEditMenu();
	int editOption = 0;
	do
	{
		//select option to edit list
		editMenu->displayMenu(editOption);
		editOption = editMenu->getMenuItem(editOption);

		if (editOption != editMenu->getMenuSize() - 1)
		{
			editList(list, editOption);
		}
	} while (editOption != editMenu->getMenuSize() - 1);
}

void editList(StudentList * list, int editOption)
{
    switch (editOption)
    {
        case 0:	//add new student
        {
            addNewStudent(list);
            break;
        }

        case 1:	//edit student info
        {
            chooseAndEditStudent(list);
            break;
        }

        case 2:	//delete student
        {
            chooseAndDeleteStudent(list);
            break;
        }
    }
}

/*	1. Enter new student info by enterStudentInfo(StudentList * list) function.
	2. Write that student instance to file.
	3. Update List.txt*/
void addNewStudent(StudentList * list)
{

	//create a new Student
	Student * newStudent = enterStudentInfo(list);

	//write object to "StudentsData" folder and update List.txt
	writeToFile(list, newStudent);

	//append to the list
	list->addNewStudent(newStudent);

	//printStudentInfo
	TextColor(ColorCode_Pink);
	std::cout << "\nThong tin cua sinh vien vua duoc nhap:" << std::endl;
	TextColor(default_ColorCode);
	newStudent->printInfo();
	TextColor(ColorCode_DarkBlue);
	std::cout << "\n**Thong tin cua sinh vien duoc luu ra file " << newStudent->getFileName();
	std::cout << " trong thu muc StudentsData.";
	std::cout << "\n**Nhan phim bat ky de quay tro lai...";
	TextColor(default_ColorCode);
	_getch();	

}

/*	1. Let the user chooses what they want to search by (name, dob...)
	2. Search for students with input keyWord.
	3. Append all found students to the linked list.
	4. Create a menu of found students.
	5. Let the user chooses the student to edit info.
	6. Edit that students info with editStudentInfo(Student * chosenStudent) function.*/
void chooseAndEditStudent(StudentList * list)
{
	//print search student option (search by name, class ... or print all students to find)
	Menu * searchFieldMenu = createSearchFieldMenu();
	
	int searchField = 0;
	do
	{
		searchFieldMenu->displayMenu(searchField);
		searchField = searchFieldMenu->getMenuItem(searchField);

		if (searchField != searchFieldMenu->getMenuSize() - 1)
		{
			Node * searchResult = new Node;
			Menu * searchResultMenu = new Menu;

			switch (searchField)
			{

			case 0:	//search by name
			{
				std::string keyWord;				

				//search student by name. if no result then ask the user to re-search or not
				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\nNhap ten de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

					//search all the list and append all found students to the linked list							
					searchResult = linearSearchName(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);

				break;
			}

			case 1:	//search by studentID
			{
				std::string keyWord;

				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\n**Nhap ma SV de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

					//search all the list and append all found students to the linked list							
					searchResult = linearSearchID(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);

				break;
			}

			case 2:	//search by date of birth
			{
				std::string keyWord;

				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\n**Nhap ngay sinh de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

					//search all the list and append all found students to the linked list							
					searchResult = linearSearchDOB(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);


				break;
			}

			case 3:	//search by GPA
			{
				std::string keyWord;

				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\n**Nhap diem TB de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

														//search all the list and append all found students to the linked list							
					searchResult = linearSearchGPA(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);

				break;
			}

			case 4:	//search by study class
			{
				std::string keyWord;

				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\n**Nhap lop hoc de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

					//search all the list and append all found students to the linked list							
					searchResult = linearSearchStudyClass(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);

				break;
			}

			case 5:	//print all list
			{
				searchResult = list->getFirstNode();
				searchResultMenu = createSearchResultMenu(searchResult);
				break;
			}

			//end of switch
			}

			//after searching, if any student is found then choose student to edit info
			//if no student found then go back
			if (searchResult != NULL)
			{
				int chosenStudentIndex = 0;
				do
				{
					searchResultMenu->displayMenu(chosenStudentIndex);
					chosenStudentIndex = searchResultMenu->getMenuItem(chosenStudentIndex);
					Student * chosenStudent = new Student;
					if (chosenStudentIndex != searchResultMenu->getMenuSize() - 1)
					{
						Node * temp = searchResult;
						for (int i = 0; i < chosenStudentIndex; i++)
						{
							temp = temp->getNextNode();	//Check this later
						}
						chosenStudent = temp->getStudent();

						//edit that chosenStudent info
						editStudentInfo(list, chosenStudent);

						std::string newStudentInfo = chosenStudent->toString();
						searchResultMenu->setMenuItem(chosenStudentIndex, newStudentInfo);
						std::cout << "";
					}

				} while (chosenStudentIndex != searchResultMenu->getMenuSize() - 1);

			}
			
		}	

	} while (searchField != searchFieldMenu->getMenuSize() - 1);

}

void chooseAndDeleteStudent(StudentList * list)
{
	//if list is empty then warn the user then return
	if (list->isEmpty())
	{
		std::cout << "Danh sach trong. Nhan phim bat ky de quay lai.";
		_getch();
		return;
	}

	//print search student option (search by name, class ... or print all students to search)
	Menu * searchFieldMenu = createSearchFieldMenu();

	int searchField = 0;
	do
	{
		searchFieldMenu->displayMenu(searchField);
		searchField = searchFieldMenu->getMenuItem(searchField);

		if (searchField != searchFieldMenu->getMenuSize() - 1)
		{
			Node * searchResult = new Node;
			Menu * searchResultMenu = new Menu;

			switch (searchField)
			{
			case 0:	//search by name
			{
				std::string keyWord;

				//search student by name. if no result then ask the user to re-search or not
				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\nNhap ten de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

														//search all the list and append all found students to the linked list							
					searchResult = linearSearchName(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);

				break;
			}

			case 1:	//search by studentID
			{
				std::string keyWord;

				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\n**Nhap ma SV de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

														//search all the list and append all found students to the linked list							
					searchResult = linearSearchID(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);

				break;
			}

			case 2:	//search by date of birth
			{
				std::string keyWord;

				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\n**Nhap ngay sinh de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

														//search all the list and append all found students to the linked list							
					searchResult = linearSearchDOB(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);


				break;
			}

			case 3:	//search by GPA
			{
				std::string keyWord;

				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\n**Nhap diem TB de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

														//search all the list and append all found students to the linked list							
					searchResult = linearSearchGPA(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);

				break;
			}

			case 4:	//search by study class
			{
				std::string keyWord;

				char userChoice;
				do
				{
					TextColor(ColorCode_DarkPink);
					std::cout << "\n**Nhap lop hoc de tim kiem: ";
					TextColor(default_ColorCode);

					std::rewind(stdin);
					std::getline(std::cin, keyWord);	//add a keyWordCheck() later

														//search all the list and append all found students to the linked list							
					searchResult = linearSearchStudyClass(list, keyWord);

					if (searchResult == NULL)
					{
						TextColor(ColorCode_Red);
						std::cout << "THONG BAO: ";
						TextColor(default_ColorCode);
						std::cout << "Khong tim thay sinh vien. Nhan ENTER de tim kiem lai, nhan phim khac de thoat.";
						userChoice = _getch();
					}
					else
					{
						searchResultMenu = createSearchResultMenu(searchResult);
						userChoice = 0;	//so it's not 13
					}

				} while (userChoice == 13);

				break;
			}

			case 5:	//print all list
			{
				searchResult = list->getFirstNode();
				searchResultMenu = createSearchResultMenu(searchResult);
				break;
			}
			//end of switch
			}

			//after searching, if any student is found then choose student to edit info
			//if no student found then go back
			if (searchResult != NULL)
			{
				int chosenStudentIndex = 0;
				do
				{
					searchResultMenu->displayMenu(chosenStudentIndex);
					chosenStudentIndex = searchResultMenu->getMenuItem(chosenStudentIndex);
					Student * chosenStudent = new Student;
					if (chosenStudentIndex != searchResultMenu->getMenuSize() - 1)
					{
						Node * temp = searchResult;
						for (int i = 0; i < chosenStudentIndex; i++)
						{
							temp = temp->getNextNode();	//Check this later
						}
						chosenStudent = temp->getStudent();

						//delete that student from the list, from searchResult and from searchResultMenu
						deleteStudent(list, chosenStudent);
						searchResultMenu->deleteMenuItem(chosenStudentIndex);
					}

				} while (chosenStudentIndex != searchResultMenu->getMenuSize() - 1);

			}

		}

	} while (searchField != searchFieldMenu->getMenuSize() - 1);

}

Student * enterStudentInfo(StudentList * list)
{
	clrscr();

	std::string fullName;
	std::string studentID;
	std::string studyClass;
	std::string dateOfBirth;
	int day, month, year;
	double GPA;
	std::string filename;

	rewind(stdin);

	TextColor(ColorCode_Red);
	std::cout << "NHAP THONG TIN SINH VIEN MOI" << std::endl << std::endl;
	TextColor(default_ColorCode);

	//enter full name until valid
	std::string directive = "Nhap ho ten: ";
	std::cout << directive;
	do
	{
		std::getline(std::cin, fullName);
	} while (!nameCheck(fullName));
	size_t oldFullnameLength = fullName.length();
	fullName = correctName(fullName);
	gotoXY(directive.length(), whereY() - 1);
	for (size_t i = 0; i < oldFullnameLength; i++)
	{
		std::cout << " ";
	}
	gotoXY(directive.length(), whereY());
	std::cout << fullName << std::endl;

	//enter studentID until valid
	std::cout << "Nhap ma SV: ";
	do
	{
		std::getline(std::cin, studentID);
	} while (!studentIDCheck(list, studentID));

	//enter studyClass
	std::cout << "Nhap ten lop hoc: ";
	std::cin >> studyClass;
	studyClass = correctStudyClass(studyClass);
	gotoXY(0, whereY() - 1);
	std::cout << "Nhap ten lop hoc: " << studyClass << std::endl;

	//enter date of birth until valid
	std::cout << "Nhap ngay sinh (dd/mm/yyyy): ";
	do
	{
		//enter date of birth until format is correct
		do
		{
			std::cin >> dateOfBirth;
		} while (!dateFormatCheck(dateOfBirth));

		int spaceCount = 0;
		int lastSpace = 0;
		for (int i = 0; i < (int)dateOfBirth.length(); i++)
		{
			if (dateOfBirth[i] == '/' || i == dateOfBirth.length() - 1)
			{
				spaceCount++;
				switch (spaceCount)
				{
				case 1:
				{
					day = std::stoi(dateOfBirth.substr(lastSpace, i));
					break;
				}
				case 2:
				{
					month = std::stoi(dateOfBirth.substr(lastSpace, i));
					break;
				}
				case 3:
				{
					year = std::stoi(dateOfBirth.substr(lastSpace, i));
					break;
				}
				}
				lastSpace = i + 1;
			}
		}
	} while (!(dateCheck(day, month, year)));

	//enter GPA until valid
	std::cout << "Nhap diem trung binh tich luy: ";
	do
	{
		std::cin >> GPA;
	} while (!gpaCheck(GPA));

	//enter file name without file extension until valid
	do
	{
		std::cout << "Nhap ten file (Khong can nhap phan mo rong file): ";
		std::cin >> filename;
	} while (!filenameCheck(list, filename));	

	Student * student = new Student(fullName, studentID, studyClass, day, month, year, GPA, filename);
	
	return student;
}

bool nameCheck(std::string fullName)
{
	//if full name is a empty string return false
	if (fullName.empty())
	{
		std::cout << "Khong co xau ky tu dau vao. Nhap lai ten: ";
		return false;
	}

	//if full name contains numbers then return false
	int spaceCount = 0;
    for (int i = 0; i < (int) fullName.length(); i++)
    {
		if (!((fullName[i] >= 'A' && fullName[i] <= 'Z') || (fullName[i] >= 'a' && fullName[i] <= 'z') || fullName[i] == ' '))
		{
			std::cout << "Ten chi duoc chua ky tu chu cai. Nhap lai: ";
			return false;
		}
		if (fullName[i] == ' ') spaceCount++;
    }

	//if full name doesn't contain first name (or last name) return false
	if (spaceCount == 0)
	{
		std::cout << "Ten khong day du. Nhap lai: " << std::endl;
		return false;
	}
    return true;
}

/*correct the input string*/
std::string correctName(std::string inputString)
{
	std::string fullName = inputString;

	//delete all the white space from the first character to the first-not-space
	int i = 0;
	while (fullName[i] == ' ')
	{
		i++;
	}
	fullName.erase(0, i);	//now variable i is the first-not-space character

	//delete all the space from the last character upward
	i = fullName.length();
	i--;
	while (fullName[i] == ' ')
	{
		i--;
	}
	fullName.erase(i + 1, fullName.length() - 1);	

	//delete all the redundant space between two words
	for (i = 0; i < (int) fullName.length() - 1; i++)
	{
		if (fullName[i] == ' ')
		{
			int j = i;
			while (fullName[j] == ' ')
			{
				j++;
			}
			if (j != i)
			{
				fullName.erase(i + 1, j - i - 1);
			}
			
		}
	}

	//first character after white space will be upper cased, the rest characters of the word is lower cased
	for (i = 0; i < (int) fullName.length(); i++)
	{
		if (i == 0)
		{
			fullName[i] = toupper(fullName[i]);
		}
		else if (fullName[i] == ' ')
		{
			fullName[i + 1] = toupper(fullName[i + 1]);
			i++;
		}
		else
		{
			fullName[i] = tolower(fullName[i]);
		}
		
	}
	return fullName;
}

std::string correctStudyClass(std::string inputString)
{
	for (size_t i = 0; i < inputString.length(); i++)
	{
		if ('a' <= inputString[i] && inputString[i] <= 'z')
		{
			inputString[i] = toupper(inputString[i]);
		}
	}
	return inputString;
}

bool studentIDCheck(StudentList * list, std::string studentID)
{
	for (int i = 0; i < (int)studentID.length(); i++)
	{
		if (studentID[i] == ' ')
		{
			std::cout << "Ma SV khong duoc co khoang trang. Nhap lai: ";
			return false;
		}
	}

	if (studentID.length() != 8)
	{
		std::cout << "Ma SV nhap sai (phai co 8 ky tu). Nhap lai: ";
		return false;
	}

    //Check if studentID had existed
	Node * temp = list->getFirstNode();
	while (temp != NULL)
	{
		if (studentID == temp->getStudent()->getStudentID())
		{
			std::cout << "Ma sinh vien da ton tai (" << temp->getStudent()->toString() << "). Nhap lai: ";
			return false;
		}

		temp = temp->getNextNode();
	}

	return true;
}

bool dateFormatCheck(std::string inputString)
{
	//check if inputString has two dash ('/')
	int dashCount = 0;

	for (int i = 0; i < (int)inputString.length(); i++)
	{
		if (inputString[i] == '/')
		{
			dashCount++;
		}
	}
	if (dashCount != 2)
	{
		std::cout << "Nhap lai ngay sinh dung cu phap (dd/mm/yyyy): ";
		return false;
	}

	//check if day, month, year in inputString is length-corrected (day is max 2 chars, month is max 2 chars, year is 4 chars)
	dashCount = 0;
	int dayLength = 0, monthLength = 0, yearLength = 0;
	for (int i = 0; i < (int) inputString.length(); i++)
	{
		if (inputString[i] != '/')
		{
			switch (dashCount)
			{
			case 0:
			{
				dayLength++;
				break;
			}
			case 1:
			{
				monthLength++;
				break;
			}
			case 2:
			{
				yearLength++;
				break;
			}
			}
		}
		else
		{
			dashCount++;
		}
	}
	if (dayLength > 2 || monthLength > 2 || yearLength > 4)
	{
		std::cout << "Khong ton tai ngay sinh " << inputString.c_str() << ". Nhap lai: ";
		return false;
	}

	return true;
}

/*	Check if input date is valid */
bool dateCheck(int day, int month, int year)
{
	if (year < 1900 || year > 2016)
	{
		std::cout << "Khong ton tai ngay sinh " << day << "/" << month << "/" << year << ". Nhap lai: ";
		return false;
	}
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
		if (day < 0 || day > 31)
		{
			std::cout << "Khong ton tai ngay sinh " << day << "/" << month << "/" << year << ". Nhap lai: ";
			return (day >= 1 && day <= 31);
		}
    } 
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
		if (day < 1 || day > 30)
		{
			std::cout << "Khong ton tai ngay sinh " << day << "/" << month << "/" << year << ". Nhap lai: ";
			return false;
		}
    } 
    else if (month == 2)
    {
        if (year % 4 == 0)
        {
			if (day < 0 || day > 29)
			{
				std::cout << "Khong ton tai ngay sinh " << day << "/" << month << "/" << year << ". Nhap lai: ";
				return false;
			}            
        }
        else 
			if (day < 0 || day > 28)
			{
				std::cout << "Khong ton tai ngay sinh " << day << "/" << month << "/" << year << ". Nhap lai: ";
				return false;
			}
    }
	else
	{
		std::cout << "Khong ton tai ngay sinh " << day << "/" << month << "/" << year << ". Nhap lai: ";
		return false;
	}
    return true;
}

bool gpaCheck(double GPA)
{
	if (!(GPA >= 0 && GPA <= 10))
	{
		std::cout << "Diem trung binh tich luy nhap sai. Nhap lai: ";
		return false;
	}
	return true;
}

bool filenameCheck(StudentList * list, std::string filename)
{
	//Check if file has already existed in folder StudentsData
	Node * temp = list->getFirstNode();
	while (temp != NULL)
	{
		std::string currentFilename = temp->getStudent()->getFileName();
		if (filename == currentFilename)
		{
			std::cout << "Ten file " << currentFilename << " da ton tai. Nhap lai: ";
			return false;
		}

		temp = temp->getNextNode();
	}

	return true;
}

void editStudentInfo(StudentList * list, Student * chosenStudent)
{
	//store old (student file path) to delete old file later.
	std::string oldFilePath = list->getDataPath();
	oldFilePath.append("\\");
	oldFilePath.append(chosenStudent->getFileName());

	//create StudentInfo menu
	Menu * studentInfoMenu = createStudentInfoMenu(chosenStudent);

	//choose field to edit info
	int editField = 0;
	do
	{
		studentInfoMenu->displayMenu(editField);
		editField = studentInfoMenu->getMenuItem(editField);

		if (editField != studentInfoMenu->getMenuSize() - 1)
		{
			switch (editField)
			{
			case 0:	//edit name
			{
				std::string newName;

				//enter full name until valid
				TextColor(ColorCode_Pink);
				std::cout << "\n**Nhap ho ten moi: ";
				TextColor(default_ColorCode);
				do
				{
					std::getline(std::cin, newName);
				} while (!nameCheck(newName));
				newName = correctName(newName);
				chosenStudent->setName(newName);

				std::string newMenuItem = "Ho ten		|";
				newMenuItem.append(chosenStudent->getFullName());
				studentInfoMenu->setMenuItem(0, newMenuItem);

				break;
			}

			case 1:	//edit studentID
			{
				std::string newStudentID;

				//enter new studentID until valid
				TextColor(ColorCode_Pink);
				std::cout << "\n**Nhap ma SV moi: ";
				TextColor(default_ColorCode);
				do
				{
					std::getline(std::cin, newStudentID);
				} while (!studentIDCheck(list, newStudentID));

				chosenStudent->setStudentID(newStudentID);

				std::string newMenuItem = "Ma SV		|";
				newMenuItem.append(chosenStudent->getStudentID());
				studentInfoMenu->setMenuItem(1, newMenuItem);

				break;
			}

			case 2:	//edit studyClass
			{
				std::string newStudyClass;

				//enter studyClass
				TextColor(ColorCode_Pink);
				std::cout << "\n**Nhap ten lop hoc moi: ";
				TextColor(default_ColorCode);
				std::cin >> newStudyClass;
				newStudyClass = correctStudyClass(newStudyClass);
				chosenStudent->setStudyClass(newStudyClass);

				std::string newMenuItem = "Lop hoc		|";
				newMenuItem.append(chosenStudent->getStudyClass());
				studentInfoMenu->setMenuItem(2, newMenuItem);

				break;
			}

			case 3:	//edit date of birth
			{
				std::string newDOB;
				int day, month, year;

				//enter date of birth until valid
				TextColor(ColorCode_Pink);
				std::cout << "\n**Nhap ngay sinh moi (dd/mm/yyyy): ";
				TextColor(default_ColorCode);
				do
				{
					//enter date of birth until format is correct
					do
					{
						std::cin >> newDOB;
					} while (!dateFormatCheck(newDOB));

					int spaceCount = 0;
					int lastSpace = 0;
					for (int i = 0; i < (int)newDOB.length(); i++)
					{
						if (newDOB[i] == '/' || i == newDOB.length() - 1)
						{
							spaceCount++;
							switch (spaceCount)
							{
							case 1:
							{
								day = std::stoi(newDOB.substr(lastSpace, i));
								break;
							}
							case 2:
							{
								month = std::stoi(newDOB.substr(lastSpace, i));
								break;
							}
							case 3:
							{
								year = std::stoi(newDOB.substr(lastSpace, i));
								break;
							}
							}
							lastSpace = i + 1;
						}
					}
				} while (!(dateCheck(day, month, year)));

				chosenStudent->setDateOfBirth(day, month, year);

				//set new menu item
				std::string newMenuItem = "Ngay sinh	|";
				newMenuItem.append(chosenStudent->getDateOfBirth()->toString());
				studentInfoMenu->setMenuItem(3, newMenuItem);

				break;
			}

			case 4: //edit GPA
			{
				double GPA;

				//enter GPA until valid
				TextColor(ColorCode_Pink);
				std::cout << "\n**Nhap diem trung binh tich luy moi: ";
				TextColor(default_ColorCode);
				do
				{
					std::cin >> GPA;
				} while (!gpaCheck(GPA));

				chosenStudent->setGPA(GPA);

				//change StudentInfoMenu GPA item
				std::string newMenuItem = "Diem TB		|";
				std::ostringstream oss;
				oss << GPA;
				newMenuItem.append(oss.str());
				studentInfoMenu->setMenuItem(4, newMenuItem);

				break;
			}

			case 5: //edit filename
			{
				std::string newFilename;

				//enter new studentID until valid
				TextColor(ColorCode_Pink);
				std::cout << "\n**Nhap ten file moi (khong nhap phan duoi mo rong): ";
				TextColor(default_ColorCode);
				do
				{
					std::getline(std::cin, newFilename);
				} while (!filenameCheck(list, newFilename));
				newFilename.append(".dat");
				chosenStudent->setFilename(newFilename);

				std::string newMenuItem = "Ten file	|";
				newMenuItem.append(chosenStudent->getFileName());
				studentInfoMenu->setMenuItem(5, newMenuItem);

				break;
			}

			//end of switch
			}
		}
	} while (editField != studentInfoMenu->getMenuSize() - 1);

	//delete old file
	deleteFile(oldFilePath);

	//write new file to StudentsData folder
	writeToFile(list, chosenStudent);

}

void deleteStudent(StudentList * list, Student * chosenStudent)
{
	//store student file path
	std::string studentFilePath = list->getDataPath();
	studentFilePath.append("\\");
	studentFilePath.append(chosenStudent->getFileName());

	//delete student from the list
	list->deleteStudent(chosenStudent);

	//delete file from folder
	deleteFile(studentFilePath);
}

void deleteFromLinkedList(Node ** firstNode, Student * student)
{
	if (firstNode == NULL)
	{
		return;
	}

	//if student is the first node
	if ((*firstNode)->getStudent() == student)
	{
		*firstNode = (*firstNode)->getNextNode();
		return;
	}

	//go to the node previous to the student's node
	Node * temp = *firstNode;
	while (temp->getNextNode()->getStudent() != student && temp != NULL)
	{
		temp = temp->getNextNode();
	}

	if (temp == NULL)
	{
		return;
	}

	temp->setNextNode(temp->getNextNode()->getNextNode());
}

/*Delete file at the specific filepath*/
void deleteFile(std::string filepath)
{
	std::string command = "del ";
	command.append(filepath);
	system(command.c_str());
}

/*Write the object of class Student to a BIN file in "StudentsData" folder */
void writeToFile(StudentList * list, Student * student)
{
	//make a studentFilePath
	std::string pathname = list->getDataPath();
	pathname.append("\\");
	pathname.append(student->getFileName());

	//if file is not existed, create a new one, if existed override that file
	student->writeToFile(pathname);
}
