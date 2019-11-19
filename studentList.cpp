//****************************************************************************************************
//
//		File:					studentList.cpp
//		
//		Student:				Manish Bhandari
//
//		Assignment:	 			Program  # 9
//
//		Course Name:			Data Structures   II 
//
//		Course Number:			COSC 3100 - 01
//
//		Due:					Oct 16, 2019
//
//
//		This program implements the hash table class to manipulate student data.
//		
//****************************************************************************************************

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
using namespace std;

#include "HashTable.h"
#include "student.h"

//****************************************************************************************************

void process(HashTable<Student> & studentList);
char getChoice();
void buildList(HashTable<Student> & studentList);
void displayStudents(HashTable<Student> & studentList);
void printStudents(HashTable<Student> & studentList);
void addStudent(HashTable<Student> & studentList);
void findStudent(HashTable<Student> & studentList);
void removeStudent(HashTable<Student> & studentList);
void displayStatistics(HashTable<Student> & studentList);

//****************************************************************************************************

int main()
{
	HashTable<Student> studentList(61);

	buildList(studentList);
	process(studentList);

	return 0;

}

//****************************************************************************************************

void process(HashTable<Student> & studentList)
{
	char choice;

	do
	{
		choice = getChoice();

		switch (choice)
		{
			case 'A':	addStudent(studentList);
						break;
			case 'F':	findStudent(studentList);
						break;
			case 'R':	removeStudent(studentList);
						break;
			case 'S':	displayStatistics(studentList);
						break;
			case 'D':	displayStudents(studentList);
						break;		
			case 'P':	printStudents(studentList);
						break;
			case 'Q':	break;
		}
	}
	while (choice != 'Q');
}

//****************************************************************************************************

char getChoice()
{
	char choice;
	bool valid;

	cout << "========MENU=======\n"
		 << "A:    Add a new Student \n"
		 << "F:    Find a student Record \n"
		 << "R:    Remove a student Record \n"
		 << "S:    Display statistics \n"
		 << "D:    Display student Record \n"
		 << "P:    Print student record \n"
		 << "Q:    Quit    \n \n"
		 << "Enter your choice: ";

	do
	{
		cin >> choice;
		choice = toupper(choice);

		switch (choice)
		{
			case 'A':	valid = true;
						break;
			case 'F':	valid = true;
						break;
			case 'R':	valid = true;
						break;
			case 'S':	valid = true;
						break;	
			case 'D':	valid = true;
						break;
			case 'P':	valid = true;
						break;		
			case 'Q':	valid = true;
						break;
			default:	valid = false;
						cout << "\a Invalid choice \n" << "Please try again:";
						break;
		}
	}
	while (!valid);

	return choice;

}

//****************************************************************************************************

void buildList(HashTable<Student> & studentList)
{
	Student student;
	ifstream studentData;

	studentData.open("studentFile.txt");

	while (studentData >> student.id)
	{
		studentData.ignore();
		studentData.getline(student.name, 50);
		studentData.getline(student.citystate, 50);
		studentData >> student.phone
					>> student.gender
					>> student.year
					>> student.credits
					>> student.gpa
					>> student.major;

		studentList.insert(student);
	}

	studentData.close();
}

//****************************************************************************************************

void displayStudents(HashTable<Student> & studentList)
{
	studentList.displayTable();
}

//****************************************************************************************************

void printStudents(HashTable<Student> & studentList)
{
	studentList.writeFile();
}

//****************************************************************************************************

void addStudent(HashTable<Student> & studentList)
{
	Student newStudent;

	cout << "Enter student id:";
	cin >> newStudent.id;

	cin.ignore();
	cout << "Enter student name:";
	cin.getline(newStudent.name, 50);

	cout << "Enter city and state:";
	cin.getline(newStudent.citystate, 50);

	cout << "Enter phone number:";
	cin >> newStudent.phone;

	cout << "Enter gender:";
	cin >> newStudent.gender;

	cout << "Enter year:";
	cin >> newStudent.year;

	cout << "Enter credits:";
	cin >> newStudent.credits;

	cout << "Enter gpa:";
	cin >> newStudent.gpa;

	cout << "Enter major:";
	cin >> newStudent.major;

	if (studentList.insert(newStudent))
	{
		cout << "Student added to the list" << endl;
		cout << left << setw(15) << "Student id: " << newStudent.id << endl;
		cout << left << setw(15) << "Student name: " << newStudent.name << endl;
		cout << left << setw(15) << "Citystate:" << newStudent.citystate << endl;
		cout << left << setw(15) << "Phone:" << newStudent.phone << endl;
		cout << left << setw(15) << "Gender:" << newStudent.gender << endl;
		cout << left << setw(15) << "Year:" << newStudent.year << endl;
		cout << left << setw(15) << "Credits:" << newStudent.credits << endl;
		cout << left << setw(15) << "GPA:" << newStudent.gpa << endl;
		cout << left << setw(15) << "Major:" << newStudent.major << endl;
	}
	else
		cout << "Cannot add student to the list";

}

//****************************************************************************************************

void findStudent(HashTable<Student> & studentList) 
{
	Student student;

	cout << "Enter the student id:";
	cin >> student.id;

	if (studentList.retrieve(student))
	{
		cout << "STUDENT FOUND" << endl;
		cout << left << setw(15) << "Student id: " << student.id << endl;
		cout << left << setw(15) << "Student name: " << student.name << endl;
		cout << left << setw(15) << "Citystate:" << student.citystate << endl;
		cout << left << setw(15) << "Phone:" << student.phone << endl;
		cout << left << setw(15) << "Gender:" << student.gender << endl;
		cout << left << setw(15) << "Year:" << student.year << endl;
		cout << left << setw(15) << "Credits:" << student.credits << endl;
		cout << left << setw(15) << "GPA:" << student.gpa << endl;
		cout << left << setw(15) << "Major:" << student.major << endl;
	}
	else
		cout << "Student not found!!" << endl;
}

//****************************************************************************************************

void removeStudent(HashTable<Student> & studentList)
{
	Student student;

	cout << "Enter the student id:";
	cin >> student.id;

	if (studentList.remove(student))
	{
		cout << "STUDENT REMOVED" << endl;
		cout << left << setw(15) << "Student id: " << student.id << endl;
		cout << left << setw(15) << "Student name: " << student.name << endl;
		cout << left << setw(15) << "Citystate:" << student.citystate << endl;
		cout << left << setw(15) << "Phone:" << student.phone << endl;
		cout << left << setw(15) << "Gender:" << student.gender << endl;
		cout << left << setw(15) << "Year:" << student.year << endl;
		cout << left << setw(15) << "Credits:" << student.credits << endl;
		cout << left << setw(15) << "GPA:" << student.gpa << endl;
		cout << left << setw(15) << "Major:" << student.major << endl;
	}
	else
		cout << "Student not found!!" << endl;
}

//****************************************************************************************************

void displayStatistics(HashTable<Student> & studentList)
{
	studentList.statistics();
}

//****************************************************************************************************

/*
Table Size:                   67
Number of elements:           61
Empty Positions:              28
Num. of chains:               17
Max Chain length:             4
Num. of collisions:           22
Avg. Chain Length:            1.3
Percent Collisions:           36.1%
Load Factor:                  58.2%
Avg # Search Steps:           1.5

Table is Not Empty
*/
