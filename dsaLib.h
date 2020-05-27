/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
	int ID;
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL), ID(0) {}
    L1Item(T &a) : data(a), pNext(NULL), ID(0) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t       _size; // number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
	~L1List() { clean(); };

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }
	int		getID(int i);


    T&      at(int i);				// give the reference to the element i-th in the list
	T&		atID(int ID);
    T&      operator[](int i);		// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);	// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
	int		findIDX(int ID);
	int		maxID();

    int     insert(int i, T& a, int ID);	// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);			// remove an element at position i in the list. Return 0 if success, -1 otherwise.
	int		insertItem(L1Item<T>* pPre, T& value, int ID);
	int		deleteItem(L1Item<T>* pPre, L1Item<T>* pLoc);

    int     push_back(T& a, int ID);		// insert to the end of the list
    int     insertHead(T& a, int ID);		// insert to the beginning of the list

    int     removeHead();			// remove the beginning element of the list
    int     removeLast();			// remove the last element of the list

    void    reverse();

    void    traverse(void (*op)(L1Item<T>*&)) {
        // TODO: Your code goes here
		L1Item<T>* pLoc = _pHead;
		while (pLoc != NULL)
		{
			op(pLoc);
			if (pLoc != NULL)
			{
				pLoc = pLoc->pNext;
			}
		}
    }
    void    traverse(void (*op)(L1Item<T>*&, void*), void* pParam) {
        // TODO: Your code goes here
		L1Item<T>* pLoc = _pHead;
		while (pLoc != NULL)
		{
			op(pLoc, pParam);
			if (pLoc != NULL)
			{
				pLoc = pLoc->pNext;
			}
		}
    }
};

template <class T> void L1List<T>::clean()
{
	if (this->_pHead != NULL)
	{
		while (this->_pHead != NULL)
		{
			L1Item<T>* pDel = this->_pHead;
			this->_pHead = this->_pHead->pNext;
			delete pDel;
		}
		this->_size = 0;
	}
}

template <class T> T& L1List<T>::at(int i)
{
	if (i >= _size || i < 0)
	{
		throw DSAException(-1);
	}
	else if (i == 0)
	{
		return _pHead->data;
	}
	else
	{
		L1Item<T>* pLoc = this->_pHead->pNext;
		for (int j = 1; j < i; j++)
		{
			pLoc = pLoc->pNext;
		}
		return pLoc->data;
	}
}
template <class T> int L1List<T>::getID(int i)
{
	if (i >= _size || i < 0)
	{
		return -1;
	}
	else if (i == 0)
	{
		return _pHead->ID;
	}
	else
	{
		L1Item<T>* pLoc = this->_pHead->pNext;
		for (int j = 1; j < i; j++)
		{
			pLoc = pLoc->pNext;
		}
		return pLoc->ID;
	}
}
template <class T> T& L1List<T>::atID(int i)
{
	L1Item<T>* pLoc = this->_pHead;
	while (pLoc != NULL)
	{
		if (pLoc->ID == i)
		{
			return pLoc->data;
		}
		pLoc = pLoc->pNext;
	}
	throw DSAException(-1);
}


template <class T> T& L1List<T>::operator[](int i)
{
	if (i >= _size || i < 0)
	{
		throw DSAException(-1);
	}
	else if (i == 0)
	{
		return _pHead->data;
	}
	else
	{
		L1Item<T>* pLoc = this->_pHead->pNext;
		for (int j = 1; j < i; j++)
		{
			pLoc = pLoc->pNext;
		}
		return pLoc->data;
	}
}

template <class T> bool L1List<T>::find(T& a, int& idx)
{

	int temp = 0;
	L1Item<T>* pLoc = this->_pHead;
	while (pLoc->data != a)
	{
		pLoc = pLoc->pNext;
		temp++;
		if (pLoc == NULL)
		{
			idx = -1;
			return 0;
		}
	}
	idx = temp;
	return 1;
}
template <class T> int L1List<T>::findIDX(int id)
{
	int temp = 0;
	L1Item<T>* pLoc = this->_pHead;
	while (pLoc->ID != id)
	{
		pLoc = pLoc->pNext;
		temp++;
		if (pLoc == NULL)
		{
			return -1;
		}
	}
	return temp;
}
template <class T> int L1List<T>::maxID()
{
	int max = 0;
	L1Item<T>* pLoc = this->_pHead;
	while (pLoc != NULL)
	{
		if (pLoc->ID > max)
		{
			max = pLoc->ID;
		}
		pLoc = pLoc->pNext;
	}
	return max;
}

template <class T> int L1List<T>::insert(int i, T& a, int ID)
{
	if (i < 0 || i >= _size)
	{
		return -1;
	}
	else if (i == 0)
	{
		return insertHead(a, ID);
	}
	else
	{
		L1Item<T>* pPre = this->_pHead;
		for (int j = 1; j < i; j++)
		{
			pPre = pPre->pNext;
		}
		return insertItem(pPre, a, ID);
	}
}
template <class T> int L1List<T>::remove(int i)
{
	if (i < 0 || i >= _size)
	{
		return -1;
	}
	else if (i == 0)
	{
		return removeHead();
	}
	else
	{
		L1Item<T>* pPre = this->_pHead;
		for (int j = 1; j < i; j++)
		{
			pPre = pPre->pNext;
		}
		return deleteItem(pPre, pPre->pNext);
		return 0;
	}
}

template <class T> int L1List<T>::insertItem(L1Item<T>* pPre, T &value, int ID)
{
	L1Item<T>* pNew = new L1Item<T>();
	if (pNew == NULL)
	{
		return -1;
	}
	pNew->data = value;
	pNew->ID = ID;
	if (pPre == NULL)
	{
		pNew->pNext = this->_pHead;
		this->_pHead = pNew;
	}
	else
	{
		pNew->pNext = pPre->pNext;
		pPre->pNext = pNew;
	}
	this->_size++;
	return 0;
}
template <class T> int L1List<T>::deleteItem(L1Item<T>* pPre, L1Item<T>* pLoc)
{
	if (pLoc == NULL)
	{
		return -1;
	}
	if (pPre == NULL)
	{
		this->_pHead = pLoc->pNext;
	}
	else
	{
		pPre->pNext = pLoc->pNext;
	}
	this->_size--;
	delete pLoc;
	return 0;
}

template <class T> int L1List<T>::push_back(T& a, int ID)
{
	if (this->_pHead != NULL)
	{
		L1Item<T>* pPre = this->_pHead;
		L1Item<T>* pLoc = pPre->pNext;
		while (pLoc != NULL)
		{
			pPre = pPre->pNext;
			pLoc = pLoc->pNext;
		}
		return insertItem(pPre, a, ID);
	}
	else return insertItem(nullptr, a, ID);
}
template <class T> int L1List<T>::insertHead(T &a, int ID) {
    // TODO: Your code goes here
	return insertItem(nullptr, a, ID);
}

template <class T> int L1List<T>::removeHead() {
	return deleteItem(nullptr, this->_pHead);
}
template <class T> int L1List<T>::removeLast() {
	if (this->_pHead != NULL)
	{
		L1Item<T>* pPre = this->_pHead;
		L1Item<T>* pLoc = pPre->pNext;
		while (pLoc->pNext != NULL)
		{
			pPre = pLoc;
			pLoc = pLoc->pNext;
		}
		return deleteItem(pPre, pLoc);
	}
	else return -1;
}

template <class T> void L1List<T>::reverse()
{
	if (this == NULL)
	{
		return;
	}
	L1Item<T>* p1 = new L1Item<T>();
	L1Item<T>* p2 = new L1Item<T>();
	L1Item<T>* p3 = new L1Item<T>();
	if (this->_pHead != NULL)
	{
		if (this->_pHead->pNext != NULL)
		{
			p1 = this->_pHead;
			p2 = p1->pNext;
			p3 = p2->pNext;
			p1->pNext = NULL;
			while ((p1 != NULL) && (p2 != NULL) && (p3 != NULL))
			{
				p2->pNext = p1;
				p1 = p3->pNext;
				if (p1 == NULL)
					break;
				p3->pNext = p2;
				p2 = p1->pNext;
				if (p2 == NULL)
					break;
				p1->pNext = p3;
				p3 = p2->pNext;
				if (p3 == NULL)
					break;
			}
			if (p1 == NULL)
			{
				this->_pHead = p3;
				this->_pHead->pNext = p2;
			}
			else if (p2 == NULL)
			{
				this->_pHead = p1;
				this->_pHead->pNext = p3;
			}
			else if (p3 == NULL)
			{
				this->_pHead = p2;
				this->_pHead->pNext = p1;
			}
		}
	}
}
#endif //DSA191_A1_DSALIB_H
