#pragma once
#include <iostream>
#include <set>
#include "Error.h"


template <typename T>
class Vector
{
private:
	std::multiset<T> ms;
	
public:
	Vector();
	Vector(const int &length);
	Vector(const Vector<T> &v);
	~Vector();
	int size() { return ms.size(); }
	Vector& operator=(Vector<T> &v);
	void print() const;
	void addElement(const T &val);
	void removeElement(const T &val);
	void reduceElements(const T &val);
	T findDifference();
};


template <typename T>
Vector<T>::Vector()
{ }

template <typename T>
Vector<T>::Vector(const int &length)
{
	if(length < 0)
		throw Error("Error: vector size must be 0 or higher.");

	T tmp;

	std::cout << "Enter vector elements:\n";
	for(int i = 0; i < length; i++)
	{
		std::cin >> tmp;
		while(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cerr << "Error: invalid character entered. Try again: ";
			std::cin >> tmp;
		}

		ms.insert(tmp);
	}
}

template <typename T>
Vector<T>::Vector(const Vector<T> &v)
{
	ms.clear();
	ms = v.ms;
}

template <typename T>
Vector<T>::~Vector()
{ }

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &v)
{
	if(this == &v) 
		return *this;

	ms.clear();
	ms = v.ms;

	return *this;
}

template <typename T>
void Vector<T>::print() const
{
	if(ms.empty())
	{
		std::cerr << "Error: vector is empty.\n";
		return;
	}

	std::cout << "Вектор содержит:\n";
	for(const auto &var : ms)
		std::cout << var << "  ";
	std::cout << std::endl;
}

template <typename T>
void Vector<T>::addElement(const T &val)
{
	typename std::multiset<T>::iterator iter = ms.find(val);

	if(iter == ms.end())
	{
		std::cerr << "Error: element not found.\n";
		return;
	}
	else
		ms.insert(val);
}

template <typename T>
void Vector<T>::removeElement(const T &val)
{
	if(ms.empty())
	{
		std::cerr << "Error: multiset is empty.\n";
		return;
	}
	
	typename std::multiset<T>::iterator iter = ms.find(val);

	if(iter == ms.end())
	{
		std::cerr << "Error: element not found.\n";
		return;
	}
	else
		ms.erase(val);
}

template <typename T>
void Vector<T>::reduceElements(const T &val)
{
	if(val == 0)
		return;

	else if(ms.empty())
	{
		std::cerr << "Error: multiset is empty.\n";
		return;
	}

	std::multiset<T> tmp;
	typename std::multiset<T>::iterator iter;

	for(iter = ms.begin(); iter != ms.end(); iter++)
		tmp.insert(*iter - val);

	ms.clear();
	ms = tmp;
}	

template <typename T>
T Vector<T>::findDifference()
{
	if(ms.empty())
	{
		std::cerr << "Error: multiset is empty.\n";
		return 0;
	}

	return *ms.end().operator--() - *ms.begin();
}