//****************************************************************************************************
//
//		File:					Student.h
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

#ifndef STUDENT_H
#define STUDENT_H

//*****************************************************************************************************

struct Student
{
	int id;
	char name[50];
	char citystate[50];
	char phone[12];
	char gender;
	int year;
	int credits;
	float gpa;
	char major[6];

	Student();
	friend ostream & operator << (ostream & out, const Student & data);
	bool operator == (const Student & rhs) const;
	bool operator == (int val) const;
	bool operator != (const Student & rhs) const;
	bool operator != (int val) const;
	bool operator < (const Student & rhs) const;
	bool operator < (int val) const;
	bool operator > (const Student & rhs) const;
	bool operator > (int val) const;
	bool operator <= (const Student & rhs) const;
	bool operator <= (int val) const;
	bool operator >= (const Student & rhs) const;
	bool operator >= (int val) const;
	int operator % (int value) const;
	Student & operator = (int value);
};

//*****************************************************************************************************

ostream & operator << (ostream & out, const Student & data)
{
	out << setw(5) << data.id << "/" << data.name[0] << data.name[1] 
		<< data.name[2] << data.name[3]  << data.name[4] << data.name[5];
	
	return out;
}

//*****************************************************************************************************

Student::Student()
{
	id = 0;
}

//*****************************************************************************************************

bool Student::operator == (const Student & rhs) const
{
	return (this->id == rhs.id);
}

//*****************************************************************************************************

bool Student::operator == (int val) const
{
	return (this->id == val);
}

//*****************************************************************************************************

bool Student::operator != (const Student & rhs) const
{
	return (this->id != rhs.id);
}

//*****************************************************************************************************

bool Student::operator != (int val) const
{
	return (this->id != val);
}

//*****************************************************************************************************

bool Student::operator < (const Student & rhs) const
{
	return (this->id < rhs.id);
}

//*****************************************************************************************************

bool Student::operator < (int val) const
{
	return (this->id < val);
}

//*****************************************************************************************************

bool Student::operator > (const Student & rhs) const
{
	return (this->id > rhs.id);
}

//*****************************************************************************************************

bool Student::operator > (int val) const
{
	return (this->id > val);
}

//*****************************************************************************************************

bool Student::operator <= (const Student & rhs) const
{
	return (this->id <= rhs.id);
}

//*****************************************************************************************************

bool Student::operator <= (int val) const
{
	return (this->id <= val);
}

//*****************************************************************************************************

bool Student::operator >= (const Student & rhs) const
{
	return (this->id >= rhs.id);
}

//*****************************************************************************************************

bool Student::operator >= (int val) const
{
	return (this->id >= val);
}

//*****************************************************************************************************

int Student::operator % (int value) const
{
	return this->id % value;
}

//*****************************************************************************************************

Student & Student::operator = (int value)
{
	this->id = value;
	return * this;

}

//*****************************************************************************************************

#endif