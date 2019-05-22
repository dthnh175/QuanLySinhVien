#include "stdafx.h"
#include "SortList.h"
#include <iostream>
#include <conio.h>
#include "console.h"
#include "PrintList.h"

void sortList(StudentList * list)
{
	if (list->isEmpty())
	{
		TextColor(ColorCode_DarkRed);
		std::cout << "\n**Danh sach rong. Nhan phim bat ky de quay lai. . .";
		TextColor(default_ColorCode);
		_getch();
		return;
	}

	//select field to sort
	Menu * sortFieldMenu = createSortFieldMenu();
	int sortField = 0;
	do
	{
		sortFieldMenu->displayMenu(sortField);
		sortField = sortFieldMenu->getMenuItem(sortField);

		if (sortField != sortFieldMenu->getMenuSize() - 1)
		{
			//select algorithm to sort
			Menu * sortAlgoMenu = createSortAlgoMenu();
			int sortAlgo = 0;
			do
			{
				sortAlgoMenu->displayMenu(sortAlgo);
				sortAlgo = sortAlgoMenu->getMenuItem(sortAlgo);
				if (sortAlgo != sortAlgoMenu->getMenuSize() - 1)
				{
					//sort the list with the chosen field and algorithm
					sortList(list, sortField, sortAlgo);

					//print the list after sorting
					drawTable(list->getFirstNode());
				}
			} while (sortAlgo != sortAlgoMenu->getMenuSize() - 1);
		}

	} while (sortField != sortFieldMenu->getMenuSize() - 1);
}

void sortList(StudentList * list, int sortField, int sortAlgo)
{
	SortField field;
	switch (sortField)
	{
	case 0:
	{
		field = SortField::NAME;
		break;
	}
	case 1:
	{
		field = SortField::STUDENT_ID;
		break;
	}
	case 2:
	{
		field = SortField::STUDY_CLASS;
		break;
	}
	case 3:
	{
		field = SortField::DATE_OF_BIRTH;
		break;
	}
	case 4:
	{
		field = SortField::GPA;
		break;
	}
	}

	switch (sortAlgo)
	{
	case 0:
	{
		selectionSort(list, field);
		break;
	}
	case 1:
	{
		insertionSort(list, field);
		break;
	}
	case 2:
	{
		quickSort(list, field);
		break;
	}
	case 3:
	{
		mergeSort(list, field);
		break;
	}
	case 4:
	{
		heapSort(list, field);
		break;
	}
	}
}

void swap(Student ** student1, Student ** student2)
{
	Student * temp = *student1;
	*student1 = *student2;
	*student2 = temp;
}


void selectionSort(StudentList * list, SortField sortField)
{
	if (list->isEmpty())
	{
		std::cout << "Danh sach sinh vien rong. Nhan phim bat ky de quay lai.";
		_getch();
		return;
	}

	if (list->getSize() == 1)
	{
		return;
	}

	Student ** students = list->getStudentArray();

	if (students == NULL)
	{
		std::cout << "Danh sach sinh vien rong. Nhan phim bat ky de quay lai.";
		_getch();
		return;
	}

	switch (sortField)
	{
	case SortField::NAME:	//sort by name
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->compareName(students[j]) > 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	case SortField::STUDENT_ID:	//sort by studentID
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->getStudentID().compare(students[j]->getStudentID()) > 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	case SortField::STUDY_CLASS:	//sort by studyClass
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->getStudyClass().compare(students[j]->getStudyClass()) > 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	case SortField::DATE_OF_BIRTH:	//sort by DOB
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->getDateOfBirth()->compare(students[j]->getDateOfBirth()) > 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	case SortField::GPA:	//sort by GPA
	{
		for (size_t i = 0; i < list->getSize(); i++)
		{
			size_t minIndex = i;
			for (size_t j = i; j < list->getSize(); j++)
			{
				if (students[minIndex]->getGPA() > students[j]->getGPA())
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				swap(&students[minIndex], &students[i]);
			}
		}
		break;
	}
	}

	Node * firstNode = new Node(students[0]);
	Node * temp = firstNode;
	for (size_t i = 1; i < list->getSize(); i++)
	{
		Node * nextNode = new Node(students[i]);
		temp->setNextNode(nextNode);
		temp = temp->getNextNode();
	}

	list->setFirstNode(firstNode);
}


void insertionSort(StudentList * list, SortField sortField)
{
	if (list->isEmpty())
	{
		std::cout << "Danh sach rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}

	//if list has only one element
	if (list->getSize() == 1)
	{
		return;
	}

	Student ** studentArr = list->getStudentArray();
	//if studentArr is empty
	if (studentArr == NULL)
	{
		std::cout << "Danh sach rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}

	switch (sortField)
	{
	case SortField::NAME:
	{
		for (int i = 1; i < list->getSize(); i++)
		{
			//find the correct position of the student at position i
			Name currentName = studentArr[i]->getFullName();
			Student currentStudent = *(studentArr[i]);
			int j = i - 1;
			while (j >= 0)
			{
				if (currentName.compare(studentArr[j]->getName()) < 0)
				{
					*(studentArr[j + 1]) = *(studentArr[j]);
					j--;
				}
				else
				{
					break;
				}
			}
			if (j != i - 1)
			{
				*(studentArr[j + 1]) = currentStudent;
			}
		}

		break;
	}

	case SortField::STUDENT_ID:
	{
		for (int i = 1; i < list->getSize(); i++)
		{
			//find the correct position of the student at position i
			Student currentStudent = *(studentArr[i]);
			int j = i - 1;
			while (j >= 0)
			{
				if (currentStudent.compareStudentID(studentArr[j]) < 0)
				{
					*(studentArr[j + 1]) = *(studentArr[j]);
					j--;
				}
				else
				{
					break;
				}
			}
			if (j != i - 1)
			{
				*(studentArr[j + 1]) = currentStudent;
			}
		}

		break;
	}

	case SortField::STUDY_CLASS:
	{
		for (int i = 1; i < list->getSize(); i++)
		{
			//find the correct position of the student at position i
			Student currentStudent = *(studentArr[i]);
			int j = i - 1;
			while (j >= 0)
			{
				if (currentStudent.compareStudyClass(studentArr[j]) < 0)
				{
					*(studentArr[j + 1]) = *(studentArr[j]);
					j--;
				}
				else
				{
					break;
				}
			}
			if (j != i - 1)
			{
				*(studentArr[j + 1]) = currentStudent;
			}
		}

		break;
	}

	case SortField::DATE_OF_BIRTH:
	{
		for (int i = 1; i < list->getSize(); i++)
		{
			//find the correct position of the student at position i
			Student currentStudent = *(studentArr[i]);
			int j = i - 1;
			while (j >= 0)
			{
				if (currentStudent.compareDateOfBirth(studentArr[j]) < 0)
				{
					*(studentArr[j + 1]) = *(studentArr[j]);
					j--;
				}
				else
				{
					break;
				}
			}
			if (j != i - 1)
			{
				*(studentArr[j + 1]) = currentStudent;
			}
		}

		break;
	}

	case SortField::GPA:
	{
		for (int i = 1; i < list->getSize(); i++)
		{
			//find the correct position of the student at position i
			Student currentStudent = *(studentArr[i]);
			int j = i - 1;
			while (j >= 0)
			{
				if (currentStudent.compareGPA(studentArr[j]) < 0)
				{
					*(studentArr[j + 1]) = *(studentArr[j]);
					j--;
				}
				else
				{
					break;
				}
			}
			if (j != i - 1)
			{
				*(studentArr[j + 1]) = currentStudent;
			}
		}

		break;
	}

	}


}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to the left of pivot and all greater elements to the right
of pivot */
int partition(Student ** arr, int low, int high, SortField sortField)
{
	switch (sortField)
	{
	case SortField::NAME:
	{
		Student pivot = *arr[high];    // pivot 
		int i = (low - 1);  // Index of smaller element array

		for (int j = low; j <= high - 1; j++)
		{
			// If current element is smaller than or equal to pivot  
			if (arr[j]->compareName(&pivot) <= 0)
			{
				i++;    // increment index of smaller element 
				swap(&arr[i], &arr[j]);
			}
		}

		swap(&arr[i + 1], &arr[high]);

		return (i + 1);

		break;
	}

	case SortField::STUDENT_ID:
	{
		Student pivot = *arr[high];    // pivot 
		int i = (low - 1);  // Index of smaller element array

		for (int j = low; j <= high - 1; j++)
		{
			// If current element is smaller than or equal to pivot  
			if (arr[j]->compareStudentID(&pivot) <= 0)
			{
				i++;    // increment index of smaller element 
				swap(&arr[i], &arr[j]);
			}
		}

		swap(&arr[i + 1], &arr[high]);

		return (i + 1);

		break;
	}

	case SortField::STUDY_CLASS:
	{
		Student pivot = *arr[high];    // pivot 
		int i = (low - 1);  // Index of smaller element array

		for (int j = low; j <= high - 1; j++)
		{
			// If current element is smaller than or equal to pivot  
			if (arr[j]->compareStudyClass(&pivot) <= 0)
			{
				i++;    // increment index of smaller element 
				swap(&arr[i], &arr[j]);
			}
		}

		swap(&arr[i + 1], &arr[high]);

		return (i + 1);

		break;
	}

	case SortField::DATE_OF_BIRTH:
	{
		Student pivot = *arr[high];    // pivot 
		int i = (low - 1);  // Index of smaller element array

		for (int j = low; j <= high - 1; j++)
		{
			// If current element is smaller than or equal to pivot  
			if (arr[j]->compareDateOfBirth(&pivot) <= 0)
			{
				i++;    // increment index of smaller element 
				swap(&arr[i], &arr[j]);
			}
		}

		swap(&arr[i + 1], &arr[high]);

		return (i + 1);

		break;
	}

	case SortField::GPA:
	{
		Student pivot = *arr[high];    // pivot 
		int i = (low - 1);  // Index of smaller element array

		for (int j = low; j <= high - 1; j++)
		{
			// If current element is smaller than or equal to pivot  
			if (arr[j]->compareGPA(&pivot) <= 0)
			{
				i++;    // increment index of smaller element 
				swap(&arr[i], &arr[j]);
			}
		}

		swap(&arr[i + 1], &arr[high]);

		return (i + 1);

		break;
	}

	}

}

/* The main function that implements QuickSort
arr		<== Array to be sorted,
low		<== Starting index,
high	<== Ending index */
void quickSort(Student ** arr, int low, int high, SortField sortField)
{
	if (low < high)
	{
		/* partitionIndex is partitioning index, arr[partitionIndex] is now at right place */
		int partitionIndex = partition(arr, low, high, sortField);

		//Sort all elements before partitionIndex in this current sub array
		quickSort(arr, low, partitionIndex - 1, sortField);

		//Sort all elements aftfer partitionIndex in this current sub array
		quickSort(arr, partitionIndex + 1, high, sortField);
	}
}

void quickSort(StudentList * list, SortField sortField)
{
	if (list->isEmpty())
	{
		std::cout << "Danh sach rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}

	//if list has only one element
	if (list->getSize() == 1)
	{
		return;
	}

	Student ** arr = list->getStudentArray();
	//if studentArr is empty
	if (arr == NULL)
	{
		std::cout << "Danh sach rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}

	quickSort(arr, 0, list->getSize() - 1, sortField);

	/* Reassign students in the list with the order sorted */

	Node * firstNode = new Node(arr[0]);
	Node * temp = firstNode;
	for (size_t i = 1; i < list->getSize(); i++)
	{
		Node * nextNode = new Node(arr[i]);
		temp->setNextNode(nextNode);
		temp = temp->getNextNode();
	}

	list->setFirstNode(firstNode);

}


void merge(Student ** arr, int leftIndex, int midIndex, int rightIndex, SortField sortField)
{
	int n1 = midIndex - leftIndex + 1;	//size of left array
	int n2 = rightIndex - midIndex;		//size of right array

	//Create temporary array
	Student * leftArray = new Student[n1], * rightArray = new Student[n2];

	//Copy data to temporary array leftArray and right Array
	for (int i = 0; i < n1; i++)
	{
		leftArray[i] = *arr[leftIndex + i];
	}

	for (int i = 0; i < n2; i++)
	{
		rightArray[i] = *arr[midIndex + 1 + i];
	}

	//Merge the temp arrays back into array[left..right]
	int i = 0,	//initial index of first subarray
		j = 0,	//initial index of second subarray
		k = leftIndex;	//(index of the initial element of merged subarray) in the main array

	switch (sortField)
	{
	case SortField::NAME:
	{
		while (i < n1 && j < n2)
		{
			if (leftArray[i].compareName(&rightArray[j]) <= 0)
			{
				arr[k] = &leftArray[i];
				i++;
			}
			else
			{
				arr[k] = &rightArray[j];
				j++;
			}

			k++;
		}

		break;
	}

	case SortField::STUDENT_ID:
	{
		while (i < n1 && j < n2)
		{
			if (leftArray[i].compareStudentID(&rightArray[j]) <= 0)
			{
				arr[k] = &leftArray[i];
				i++;
			}
			else
			{
				arr[k] = &rightArray[j];
				j++;
			}

			k++;
		}

		break;
	}

	case SortField::STUDY_CLASS:
	{
		while (i < n1 && j < n2)
		{
			if (leftArray[i].compareStudyClass(&rightArray[j]) <= 0)
			{
				arr[k] = &leftArray[i];
				i++;
			}
			else
			{
				arr[k] = &rightArray[j];
				j++;
			}

			k++;
		}

		break;
	}

	case SortField::DATE_OF_BIRTH:
	{
		while (i < n1 && j < n2)
		{
			if (leftArray[i].compareDateOfBirth(&rightArray[j]) <= 0)
			{
				arr[k] = &leftArray[i];
				i++;
			}
			else
			{
				arr[k] = &rightArray[j];
				j++;
			}

			k++;
		}

		break;
	}

	case SortField::GPA:
	{
		while (i < n1 && j < n2)
		{
			if (leftArray[i].compareGPA(&rightArray[j]) <= 0)
			{
				arr[k] = &leftArray[i];
				i++;
			}
			else
			{
				arr[k] = &rightArray[j];
				j++;
			}

			k++;
		}

		break;
	}
	}

	/* Copy the remaining elements of leftArray[], if there are any */
	while (i < n1)
	{
		arr[k] = &leftArray[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there	are any */
	while (j < n2)
	{
		arr[k] = &rightArray[j];
		j++;
		k++;
	}
	
}

void mergeSort(Student ** arr, int leftIndex, int rightIndex, SortField sortField)
{
	if (leftIndex < rightIndex)
	{
		int midIndex = (leftIndex + rightIndex) / 2;

		// Sort first and second halves 
		mergeSort(arr, leftIndex, midIndex, sortField);
		mergeSort(arr, midIndex + 1, rightIndex, sortField);

		merge(arr, leftIndex, midIndex, rightIndex, sortField);
	}
}

void mergeSort(StudentList * list, SortField sortField)
{
	if (list->isEmpty())
	{
		std::cout << "Danh sach rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}

	//if list has only one element
	if (list->getSize() == 1)
	{
		return;
	}

	Student ** studentArr = list->getStudentArray();
	//if studentArr is empty
	if (studentArr == NULL)
	{
		std::cout << "Danh sach rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}
	
	mergeSort(studentArr, 0, list->getSize() - 1, sortField);

	/* Reassign students in the list with the order sorted */
	
	Node * firstNode = new Node(studentArr[0]);
	Node * temp = firstNode;
	for (size_t i = 1; i < list->getSize(); i++)
	{
		Node * nextNode = new Node(studentArr[i]);
		temp->setNextNode(nextNode);
		temp = temp->getNextNode();
	}

	list->setFirstNode(firstNode);
}


void heapSort(StudentList * list, SortField sortField)
{
	if (list->isEmpty())
	{
		std::cout << "Danh sach rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}

	//if list has only one element
	if (list->getSize() == 1)
	{
		return;
	}

	Student ** arr = list->getStudentArray();

	//if studentArr is empty then get out
	if (arr == NULL)
	{
		std::cout << "Danh sach rong. Nhan phim bat ky de quay lai . . .";
		_getch();
		return;
	}

	int n = (int) list->getSize();

	switch (sortField)
	{
	case SortField::NAME:
	{
		// Build heap (rearrange array) 
		for (int i = n / 2 - 1; i >= 0; i--)
			heapifyName(arr, n, i);

		// One by one extract an element from heap 
		for (int i = n - 1; i >= 0; i--)
		{
			// Move current root to end 
			swap(&arr[0], &arr[i]);

			// call max heapify on the reduced heap 
			heapifyName(arr, i, 0);
		}

		break;
	}

	case SortField::STUDENT_ID:
	{
		// Build heap (rearrange array) 
		for (int i = n / 2 - 1; i >= 0; i--)
			heapifyStudentID(arr, n, i);

		// One by one extract an element from heap 
		for (int i = n - 1; i >= 0; i--)
		{
			// Move current root to end 
			swap(&arr[0], &arr[i]);

			// call max heapify on the reduced heap 
			heapifyStudentID(arr, i, 0);
		}

		break;
	}

	case SortField::STUDY_CLASS:
	{
		// Build heap (rearrange array) 
		for (int i = n / 2 - 1; i >= 0; i--)
			heapifyStudyClass(arr, n, i);

		// One by one extract an element from heap 
		for (int i = n - 1; i >= 0; i--)
		{
			// Move current root to end 
			swap(&arr[0], &arr[i]);

			// call max heapify on the reduced heap 
			heapifyStudyClass(arr, i, 0);
		}

		break;
	}

	case SortField::DATE_OF_BIRTH:
	{
		// Build heap (rearrange array) 
		for (int i = n / 2 - 1; i >= 0; i--)
			heapifyDOB(arr, n, i);

		// One by one extract an element from heap 
		for (int i = n - 1; i >= 0; i--)
		{
			// Move current root to end 
			swap(&arr[0], &arr[i]);

			// call max heapify on the reduced heap 
			heapifyDOB(arr, i, 0);
		}

		break;
	}

	case SortField::GPA:
	{
		// Build heap (rearrange array) 
		for (int i = n / 2 - 1; i >= 0; i--)
			heapifyGPA(arr, n, i);

		// One by one extract an element from heap 
		for (int i = n - 1; i >= 0; i--)
		{
			// Move current root to end 
			swap(&arr[0], &arr[i]);

			// call max heapify on the reduced heap 
			heapifyGPA(arr, i, 0);
		}

		break;
	}

	}

	/* Reassign students in the list with the order sorted */

	Node * firstNode = new Node(arr[0]);
	Node * temp = firstNode;
	for (size_t i = 1; i < list->getSize(); i++)
	{
		Node * nextNode = new Node(arr[i]);
		temp->setNextNode(nextNode);
		temp = temp->getNextNode();
	}

	list->setFirstNode(firstNode);
}

/*To heapify a subtree rooted with node i which is an index in arr[], n is the size of heap*/
void heapifyName(Student ** arr, int n, int i)
{
	int largestIndex = i;	//initialize largest as root
	int leftIndex = 2 * i + 1;
	int rightIndex = 2 * i + 2;

	//if left child is larger than root
	if (leftIndex < n && arr[leftIndex]->compareName(arr[largestIndex]) > 0)
	{
		largestIndex = leftIndex;
	}

	//if right child is larger than current largest
	if (rightIndex < n && arr[rightIndex]->compareName(arr[largestIndex]) > 0)
	{
		largestIndex = rightIndex;
	}

	//if largest is not root
	if (largestIndex != i)
	{
		swap(&arr[i], &arr[largestIndex]);

		//recursively heapify the current subtree
		heapifyName(arr, n, largestIndex);
	}
}

void heapifyStudentID(Student ** arr, int n, int i)
{
	int largestIndex = i;	//initialize largest as root
	int leftIndex = 2 * i + 1;
	int rightIndex = 2 * i + 2;

	//if left child is larger than root
	if (leftIndex < n && arr[leftIndex]->compareStudentID(arr[largestIndex]) > 0)
	{
		largestIndex = leftIndex;
	}

	//if right child is larger than current largest
	if (rightIndex < n && arr[rightIndex]->compareStudentID(arr[largestIndex]) > 0)
	{
		largestIndex = rightIndex;
	}

	//if largest is not root
	if (largestIndex != i)
	{
		swap(&arr[i], &arr[largestIndex]);

		//recursively heapify the current subtree
		heapifyStudentID(arr, n, largestIndex);
	}
}

void heapifyStudyClass(Student ** arr, int n, int i)
{
	int largestIndex = i;	//initialize largest as root
	int leftIndex = 2 * i + 1;
	int rightIndex = 2 * i + 2;

	//if left child is larger than root
	if (leftIndex < n && arr[leftIndex]->compareStudyClass(arr[largestIndex]) > 0)
	{
		largestIndex = leftIndex;
	}

	//if right child is larger than current largest
	if (rightIndex < n && arr[rightIndex]->compareStudyClass(arr[largestIndex]) > 0)
	{
		largestIndex = rightIndex;
	}

	//if largest is not root
	if (largestIndex != i)
	{
		swap(&arr[i], &arr[largestIndex]);

		//recursively heapify the current subtree
		heapifyStudyClass(arr, n, largestIndex);
	}
}

void heapifyDOB(Student ** arr, int n, int i)
{
	int largestIndex = i;	//initialize largest as root
	int leftIndex = 2 * i + 1;
	int rightIndex = 2 * i + 2;

	//if left child is larger than root
	if (leftIndex < n && arr[leftIndex]->compareDateOfBirth(arr[largestIndex]) > 0)
	{
		largestIndex = leftIndex;
	}

	//if right child is larger than current largest
	if (rightIndex < n && arr[rightIndex]->compareDateOfBirth(arr[largestIndex]) > 0)
	{
		largestIndex = rightIndex;
	}

	//if largest is not root
	if (largestIndex != i)
	{
		swap(&arr[i], &arr[largestIndex]);

		//recursively heapify the current subtree
		heapifyDOB(arr, n, largestIndex);
	}
}

void heapifyGPA(Student ** arr, int n, int i)
{
	int largestIndex = i;	//initialize largest as root
	int leftIndex = 2 * i + 1;
	int rightIndex = 2 * i + 2;

	//if left child is larger than root
	if (leftIndex < n && arr[leftIndex]->compareGPA(arr[largestIndex]) > 0)
	{
		largestIndex = leftIndex;
	}

	//if right child is larger than current largest
	if (rightIndex < n && arr[rightIndex]->compareGPA(arr[largestIndex]) > 0)
	{
		largestIndex = rightIndex;
	}

	//if largest is not root
	if (largestIndex != i)
	{
		swap(&arr[i], &arr[largestIndex]);

		//recursively heapify the current subtree
		heapifyGPA(arr, n, largestIndex);
	}
}


void selectionSortStudyClass(StudentList * list)
{
	Student ** students = list->getStudentArray();

	if (students == NULL)
	{
		std::cout << "Mang sinh vien rong. Nhan phim bat ky de quay lai.";
		_getch();
		return;
	}

	for (size_t i = 0; i < list->getSize(); i++)
	{
		size_t minIndex = i;
		for (size_t j = i; j < list->getSize(); j++)
		{
			if (students[j]->getStudyClass().compare(students[minIndex]->getStudyClass()) < 0)
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			swap(&students[minIndex], &students[i]);
		}
	}

	Node * firstNode = new Node(students[0]);
	Node * temp = firstNode;
	for (size_t i = 1; i < list->getSize(); i++)
	{
		Node * nextNode = new Node(students[i]);
		temp->setNextNode(nextNode);
		temp = temp->getNextNode();
	}

	list->setFirstNode(firstNode);

}
