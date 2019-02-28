#include "stdafx.h"
#include "Node.h"


/*Only for declaring new instance to use later*/
Node::Node()
{
	//do nothing
}

Node::Node(Student * student)
{
	this->student = student;
	this->nextNode = NULL;
}

Node::Node(Student * student, Node * nextNode)
{
	this->student = student;
	this->nextNode = nextNode;
}

void Node::setStudent(Student * student)
{
	this->student = student;
}

Student * Node::getStudent()
{
	return this->student;
}

void Node::setNextNode(Node * nextNode)
{
	this->nextNode = nextNode;
}

Node * Node::getNextNode()
{
	return this->nextNode;
}

