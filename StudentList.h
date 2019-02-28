#pragma once
#include "Student.h"
#include "ManagingMenu.h"
#include "Node.h"


/*a linked list consists of students*/
class StudentList
{
private:	
	size_t listSize;
	Node * firstNode;
	std::string dataPath;

public:
	StudentList();

	bool dataFolderExist(std::string pathName);
	int studentCount();
	void addNewStudent(Student * newStudent);
	void deleteStudent(Student * student);
	void updateList();

	bool isEmpty();
	std::string getDataPath();
	Node * getFirstNode();
	Student ** getStudentArray();
	size_t getSize();

};
