#include "stdafx.h"
#include "StudentList.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <Windows.h>
#include <conio.h>
#include "EditList.h"


/*Create linked list from DAT files in folder "StudentsData" */
StudentList::StudentList()
{
	//if program is opened the first time then create a "StudentsData" folder inside the folder that has the exe and create List.txt file
	//check if StudentsData folder exists
	char * buffer = new char[80];
	GetModuleFileNameA(NULL, buffer, 80);
	std::string pathname = buffer;	//pathname is the directory of the "StudentsData" folder
	int index = pathname.length() - 1;
	while (pathname[index] != '\\')
	{
		index--;
	}
	pathname.erase(index + 1, pathname.length() - 1);
	pathname.append("StudentsData");

	this->dataPath = pathname;	//save pathname to a member function
	this->listSize = 0;

	//if StudentsData folder not exist then create it (if we use the program the first time)
	if (!dataFolderExist(pathname))
	{
		//set the UNICODE pathname for the creating-folder purpose.
		wchar_t * Wpathname = new wchar_t[pathname.length()];	//Wpathname is the pathname but has the Wide-Charater type (UNICODE)
		for (size_t i = 0; i < pathname.length(); i++)
		{
			Wpathname[i] = pathname[i];
		}
		Wpathname[pathname.length()] = 0;	//set the string-terminator character

		//create folder with Wpathname
		int status = _wmkdir(Wpathname);
		if (status < 0)
		{
			std::cout << "Data folder not created.\n";
		}
		else {
			std::cout << "Data folder created.\n";
		}

		return;
	}

	//create List.txt in folder "StudentsData" to store all filenames
	std::string command = "cd ";
	command.append(pathname);
	command.append(" && dir /B *.dat > List.txt");
	system(command.c_str());	// https://stackoverflow.com/questions/24722368/systemcd-path-in-a-c-program
	

	//read all objects to the StudentList with filenames inside List.txt
	std::string list_txt_Path = pathname;
	list_txt_Path.append("\\List.txt");
	std::fstream fileIn(list_txt_Path.c_str(), std::ios::in);
	std::string studentFilename;

	//read each file name in List.txt until EOF then use that to open each file to append to list
	std::getline(fileIn, studentFilename);
	if (studentFilename.empty())
	{
		//No file in "StudentsData" folder causes no file in List.txt
		return;
	}
	do
	{
		std::string studentFilePath = pathname;
		studentFilePath.append("\\");
		studentFilePath.append(studentFilename);

		Student * student = new Student(studentFilePath);

		//append to list
		this->addNewStudent(student);

		std::getline(fileIn, studentFilename);
	} while (!studentFilename.empty());

	//close files
	fileIn.close();
	
}

/*Check if the path has existed*/
bool StudentList::dataFolderExist(std::string pathname)
{
	/* https://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c */
	struct stat info;
	if (stat(pathname.c_str(), &info) != 0)
	{
		//printf_s("cannot access %s\n", pathname.c_str());
		return false;
	}		
	else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
	{
		//printf_s("%s is a directory\n", pathname.c_str());
		return true;
	}
	else
	{
		//printf_s("%s is no directory\n", pathname.c_str());
		return false;
	}
		
}

int StudentList::studentCount()
{
	
	return 0;
}

/*Add new student to the list*/
void StudentList::addNewStudent(Student * newStudent)
{
	//increase listSize by one unit
	this->listSize++;

	//if list is empty then create a new node as the first node then return
	if (this->firstNode == NULL)
	{
		this->firstNode = new Node(newStudent);
		return;
	}

	//if list not epmpty then just simply add a new node
	Node * temp = this->firstNode;
	while (temp->getNextNode() != NULL)
	{
		temp = temp->getNextNode();
	}
	Node * newNode = new Node(newStudent);
	temp->setNextNode(newNode);

	//update List.txt
	updateList();
}

/*Delete a student from the list*/
void StudentList::deleteStudent(Student * student)
{
	if (this->firstNode == NULL)
	{
		std::cout << "Danh sach trong. Nhan phim bat ky de quay lai.";
		_getch();
		return;
	}

	//if the student is the first in the linked list
	if (this->firstNode->getStudent()->getStudentID() == student->getStudentID())
	{
		this->firstNode = this->firstNode->getNextNode();
		return;
	}

	//traverse all the list to find the node previous to that student
	Node * temp = this->firstNode;
	while (temp->getNextNode()->getStudent()->getStudentID() != student->getStudentID() && temp != NULL)
	{
		temp = temp->getNextNode();
	}
	if (temp == NULL)
	{
		std::cout << "Khong co sinh vien can xoa trong danh sach. Khong the xoa. ";
		std::cout << "Nhan phim bat ky de quay lai.";
		_getch();
		return;
	}
	if (temp->getNextNode()->getNextNode() == NULL)
	{

	}
	temp->setNextNode(temp->getNextNode()->getNextNode());
	this->listSize--;
}

/*Update List.txt after adding or deleting students*/
void StudentList::updateList()
{
	std::string command = "cd ";
	command.append(this->dataPath);
	command.append(" &&");
	command.append(" dir /B *.dat > List.txt");
	system(command.c_str());
}

/*Check if list is empty*/
bool StudentList::isEmpty()
{
	return (this->firstNode == NULL);
}

/*return the directory of "StudentsData" folder */
std::string StudentList::getDataPath()
{
	return this->dataPath;
}

/*Returns first node of the linked list */
Node * StudentList::getFirstNode()
{
	return this->firstNode;
}

/*Make an array from the list*/
Student ** StudentList::getStudentArray()
{
	Student ** array = new Student *[this->listSize];

	Node * temp = this->firstNode;
	for (size_t i = 0; i < this->listSize; i++)
	{
		array[i] = temp->getStudent();
		temp = temp->getNextNode();
	}

	return array;
}

size_t StudentList::getSize()
{
	return this->listSize;
}

void StudentList::setFirstNode(Node * firstNode)
{
	this->firstNode = firstNode;

	//count nodes
	Node * temp = firstNode;
	this->listSize = 0;
	while (temp != NULL)
	{
		this->listSize++;
		temp = temp->getNextNode();
	}
}
