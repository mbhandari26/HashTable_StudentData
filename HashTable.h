//****************************************************************************************************
//
//		File:					Hashtable.h
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

#ifndef HASTHTABLE_H
#define HASTHTABLE_H

//****************************************************************************************************

#include<new>
#include<iomanip>
#include "Node.h"

//****************************************************************************************************

template<typename TYPE>
class HashTable
{
private:
		Node<TYPE> * table;
		int size;

		bool _isPrime(int s) const;
		int _hash(const TYPE & dataIn) const;
		void _tableOut(ostream & out) const;
public:
		HashTable(int s = 23);
		~HashTable();
		bool insert(const TYPE & dataIn);
		void writeFile() const;
		void displayTable() const;
		bool remove(TYPE & data);
		bool retrieve(TYPE & dataOut) const;
		bool isEmpty() const;
		void statistics() const;
};

//****************************************************************************************************

template<typename TYPE>
HashTable<TYPE>::HashTable(int s)
{
	if (s % 2 == 0)
		s = s + 1;
	else
		s = s + 2;

	while (!_isPrime(s))
		s = s + 2;

	size = s;
	table = new Node<TYPE>[size];
}

//****************************************************************************************************

template<typename TYPE>
bool HashTable<TYPE>::_isPrime(int s) const
{
	bool goodPrime = false;

	if ((s % 3 != 0) && (s % 5 != 0) && (s % 7 != 0) && (s % 9 != 0) &&
		(s % 11 != 0) && (s % 13 != 0) && (s % 15 != 0) && (s % 17 != 0) && 
		(s % 19 != 0))
	{
		goodPrime = true;
	}

	return goodPrime;
}

//****************************************************************************************************

template<typename TYPE>
HashTable<TYPE>::~HashTable()
{
	Node<TYPE> * pDelete;

	for (int i = 0; i < size; i++)
	{
		while (table[i].next)
		{
			pDelete = table[i].next;
			table[i].next = table[i].next->next;
			delete pDelete;
		}
	}

	size = 0;
	delete [] table;
	table = nullptr;
}

//****************************************************************************************************

template<typename TYPE>
int  HashTable<TYPE>::_hash(const TYPE & dataIn) const
{
	return dataIn % size;
}

//****************************************************************************************************

template<typename TYPE>
bool HashTable<TYPE>::insert(const TYPE & dataIn)
{
	bool success = false;
	Node<TYPE>* pNew;
	int loc;

	loc = _hash(dataIn);

	if (table[loc].data == 0)
	{
		table[loc].data = dataIn;
		success = true;
	}
	else
	{
		pNew = new (nothrow) Node<TYPE>(dataIn, table[loc].next);
		if (pNew)
		{
			table[loc].next = pNew;
			success = true;
		}
		
	}

	return success;
}

//****************************************************************************************************

template<typename TYPE>
void HashTable<TYPE>::writeFile() const
{
	ofstream outFile("studentTable.txt");
	_tableOut(outFile);
	outFile.close();
}

//****************************************************************************************************

template<typename TYPE>
void HashTable<TYPE>::displayTable() const
{
	_tableOut(cout);
}

//****************************************************************************************************

template<typename TYPE>
void HashTable<TYPE>::_tableOut(ostream & out) const
{
	out << "Address" << " Prime Area" << setw(20) << "Overflow" << endl;
	Node<TYPE> * pTemp;

	for (int loc = 0; loc < size; loc++)
	{
		pTemp = table[loc].next;

		if (loc < 10)
			out << "[0" << loc << "]  ";
		else
			out << "[" << loc << "]  ";

		if (table[loc].data != 0)
			out << table[loc].data << setw(7) << "";
		else
			out << "";

		while (pTemp)
		{
			out << pTemp->data;

			if (pTemp->next)
				out << ",   ";

			pTemp = pTemp->next;
		}

		out << endl;
	}
}

//****************************************************************************************************

template<typename TYPE>
bool HashTable<TYPE>::remove(TYPE & dataOut)
{
	int loc;
	bool success = false;
	Node<TYPE> * pTemp;
	Node<TYPE> * pPrev;

	loc = _hash(dataOut);
	pTemp = table[loc].next;
	pPrev = &(table[loc]);

	if (table[loc].data == dataOut)
	{
		dataOut = table[loc].data;

		if (!table[loc].next)
			table[loc].data = 0;
		else
		{
			table[loc] = *pTemp;
			delete pTemp;
		}

		success = true;
	}
	else
	{
		while ((pTemp) && (pTemp->data != dataOut))
		{
			pPrev = pTemp;
			pTemp = pTemp->next;
		}

		if ((pTemp) && (pTemp->data == dataOut))
		{
			dataOut = pTemp->data;

			if (pPrev)
				pPrev->next = pTemp->next;

			delete pTemp;
			success = true;
		}
	}

	return success;
}

//****************************************************************************************************

template<typename TYPE>
bool HashTable<TYPE>::retrieve(TYPE & dataOut) const
{
	bool success = false;
	int loc;
	Node<TYPE> * pTemp;

	loc = _hash(dataOut);
	pTemp = table[loc].next;

	if (table[loc].data == dataOut)
	{
		dataOut = table[loc].data;
		success = true;
	}
	else
	{
		while ((pTemp) && (pTemp->data != dataOut))
		{
			pTemp = pTemp->next;
		}

		if ((pTemp) && (pTemp->data == dataOut))
		{
			dataOut = pTemp->data;
			success = true;
		}
	}

	return success;
}

//****************************************************************************************************

template<typename TYPE>
bool HashTable<TYPE>::isEmpty() const
{
	bool isEmpty = true;
	int loc = 1;

	if (table[0].data != 0)
		isEmpty = false;
	else
	{
		while ((loc < size) && (isEmpty))
		{
			if (table[loc].data != 0)
				isEmpty = false;
		}
	}

	return isEmpty;
}

//****************************************************************************************************

template<typename TYPE>
void HashTable<TYPE>::statistics() const
{
	int numElements = 0,
		numEmptyLoc = 0,
		numOverflowChains = 0,
		numCollisions = 0,
		numSteps = 0,
		longestChain = 1,
		totalChainLen = 0,
		chainLen;
	double	avgChainLen,
			loadFactor,
			perCollisions,
			avgSteps;
	Node<TYPE> * pTemp;

	for (int loc = 0; loc < size; loc++)
	{
		pTemp = table[loc].next;
		chainLen = 0;

		numSteps++;

		if (table[loc].data != 0)
			numElements++;
		else
			numEmptyLoc++;

		if (table[loc].next)
			numOverflowChains++;

		while (pTemp)
		{
			numElements++;
			numCollisions++;
			chainLen++;
			numSteps++;
			totalChainLen++;
			pTemp = pTemp->next;
		}

		if (chainLen > longestChain)
			longestChain = chainLen;
	}

	avgChainLen = totalChainLen / static_cast<double> (numOverflowChains);
	loadFactor = (size - numEmptyLoc) / static_cast<double> (size) * 100;
	perCollisions = numCollisions / static_cast<double> (numElements) * 100;
	avgSteps = numSteps / static_cast<double> (numElements);

	cout << left << setw(30) << "Table Size:" << size << endl;
	cout << left << setw(30) << "Number of elements:" << numElements << endl;
	cout << left << setw(30) << "Empty Positions:" << numEmptyLoc << endl;
	cout << left << setw(30) << "Num. of chains:" << numOverflowChains << endl;
	cout << left << setw(30) << "Max Chain length:" << longestChain << endl;
	cout << left << setw(30) << "Num. of collisions:" << numCollisions << endl;
	cout << setprecision(1) << fixed;
	cout << left << setw(30) << "Avg. Chain Length:" << avgChainLen << endl;
	cout << left << setw(30) << "Percent Collisions:" << perCollisions << "%\n";
	cout << left << setw(30) << "Load Factor:" << loadFactor << "%"<< endl;
	cout << left << setw(30) << "Avg # Search Steps:" << avgSteps << endl << endl;

	if (isEmpty())
		cout << "Table is empty" << endl;
	else
		cout << "Table is Not Empty" << endl;
}

//****************************************************************************************************

#endif




