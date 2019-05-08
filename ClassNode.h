#pragma once

#include "StudentList.h"
#include <string.h>


#define EXCELLENT_MARK 3.6
#define GOOD_MARK 3
#define PRETTYGOOD_MARK 2.5
#define AVERAGE_MARK 2
//otherwise weak mark

class ClassNode
{
private:
	std::string className;
	int studentCount;	//class size

	/*Variables for statistic*/
	int excellentCount, excellentPercent,
		goodCount, goodPercent,
		prettyGoodCount, prettyGoodPercent,
		averageCount, averagePercent,
		weakCount, weakPercent;

	/*First student node for the linked list*/
	Node * firstStudentNode;


	ClassNode * nextClassNode;

public:

	/*Constructors*/

	ClassNode();
	ClassNode(std::string className);
	ClassNode(std::string className, Node * firstStudent);

	/*Setters*/

	void setNextClassNode(ClassNode * nextClassNode);
	void setStudentCount(int newStudentCount);
	void setFirstStudentNode(Node * firtsNode);

	/*Getters*/

	std::string getClassName();
	int getStudentCount();
	ClassNode * getNextClassNode();
	Node * getFirstStudentNode();

	int getExcellentCount();
	int getExcellentPercent();
	int getGoodCount();
	int getGoodPercent();
	int getPrettyGoodCount();
	int getPrettyGoodPercent();
	int getAverageCount();
	int getAveragePercent();
	int getWeakCount();
	int getWeakPercent();

	/*Add new student to the linked list*/
	void addNewStudentNode(Node * newStudentNode);


	/*Increase this class's size (this->studentCount) by one*/
	void incClassSize();


	/*Classify all students in this class two 5 types.
	How to classify:
	Excellent: gpa > EXCELLENT_MARK
	Good: gpa > GOOD_MARK
	Pretty good: gpa > PRETTYGOOD_MARK
	Average: gpa > AVERAGE_MARK
	Week: gpa < AVERAGE_MARK
	*/
	void classifyStudents();

};
