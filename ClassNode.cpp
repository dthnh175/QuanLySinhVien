
#include "stdafx.h"
#include "ClassNode.h"


ClassNode::ClassNode()
{
	//nothing here
}

ClassNode::ClassNode(std::string className)
{
	this->className = className;
	this->studentCount = 1;
	this->nextClassNode = NULL;
}

ClassNode::ClassNode(std::string className, Node * firstStudentNode)
{
	this->className = className;
	this->studentCount = 1;
	this->firstStudentNode = firstStudentNode;
}

void ClassNode::setNextClassNode(ClassNode * nextClassNode)
{
	this->nextClassNode = nextClassNode;
}

void ClassNode::setStudentCount(int newStudentCount)
{
	this->studentCount = newStudentCount;
}

void ClassNode::setFirstStudentNode(Node * firstNode)
{
	this->firstStudentNode = firstNode;
}

void ClassNode::addNewStudentNode(Node * newStudentNode)
{
	if (this->firstStudentNode == NULL)
	{
		return;
	}

	Node * temp = this->firstStudentNode;

	while (temp->getNextNode() != NULL)
	{
		temp = temp->getNextNode();
	}

	temp->setNextNode(newStudentNode);
}

std::string ClassNode::getClassName()
{
	return this->className;
}

int ClassNode::getStudentCount()
{
	return this->studentCount;
}

ClassNode * ClassNode::getNextClassNode()
{
	return this->nextClassNode;
}

Node * ClassNode::getFirstStudentNode()
{
	return this->firstStudentNode;
}

int ClassNode::getExcellentCount()
{
	return this->excellentCount;
}

int ClassNode::getExcellentPercent()
{
	return this->excellentPercent;
}

int ClassNode::getGoodCount()
{
	return this->goodCount;
}

int ClassNode::getGoodPercent()
{
	return this->goodPercent;
}

int ClassNode::getPrettyGoodCount()
{
	return this->prettyGoodCount;
}

int ClassNode::getPrettyGoodPercent()
{
	return this->prettyGoodPercent;
}

int ClassNode::getAverageCount()
{
	return this->averageCount;
}

int ClassNode::getAveragePercent()
{
	return this->averagePercent;
}

int ClassNode::getWeakCount()
{
	return this->weakCount;
}

int ClassNode::getWeakPercent()
{
	return this->weakPercent;
}

void ClassNode::incClassSize()
{
	this->studentCount++;
}

void ClassNode::classifyStudents()
{
	Node * tempStudentNode = this->firstStudentNode;

	while (tempStudentNode != NULL)
	{
		double currentStudentGPA = tempStudentNode->getStudent()->getGPA();

		if (currentStudentGPA > EXCELLENT_MARK)
		{
			this->excellentCount++;
		}
		else if (currentStudentGPA > GOOD_MARK)
		{
			this->goodCount++;
		}
		else if (currentStudentGPA > PRETTYGOOD_MARK)
		{
			this->prettyGoodCount++;
		}
		else if (currentStudentGPA > AVERAGE_MARK)
		{
			this->averageCount++;
		}
		else
		{
			this->weakCount++;
		}

		tempStudentNode = tempStudentNode->getNextNode();
	}

	this->excellentPercent = (int)(((double) this->excellentCount / this->studentCount) * 100);
	this->goodPercent = (int)(((double) this->goodCount / this->studentCount) * 100);
	this->prettyGoodPercent = (int)(((double) this->prettyGoodCount / this->studentCount) * 100);
	this->averagePercent = (int)(((double) this->averageCount / this->studentCount) * 100);
	this->weakPercent = 100 
		- this->excellentPercent 
		- this->goodPercent 
		- this->prettyGoodPercent 
		- this->averagePercent;
}
