#pragma once
#include "Student.h"

class Node
{
private:
	Student * student;
	Node * nextNode;
public:
	Node();
	Node(Student * student);
	Node(Student * student, Node * nextNode);

	void setStudent(Student * student);
	void setNextNode(Node * nextNode);

	Student * getStudent();	
	Node * getNextNode();
};
