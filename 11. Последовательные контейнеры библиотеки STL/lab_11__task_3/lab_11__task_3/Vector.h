#pragma once
#include <iostream>
#include <vector>
#include "Error.h"


template <typename T>
class Vector
{
private:
	std::vector<T> vec;
	
public:
	Vector();
	Vector(const int &length);
	Vector(Vector<T> &v);
	~Vector();
	int size() { return vec.size(); }
	Vector& operator=(Vector<T> &v);
	typename std::vector<T>::iterator operator[](const int &index);
	typename std::vector<T>::iterator find(const T &key);
	void print() const;
	void addElementToPosition(const T &key, const int &pos);
	void removeElement(const T &key);
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
		throw Error("Error: vector size must be 0 or higher,\n");

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

		vec.push_back(tmp);
	}
}

template <typename T>
Vector<T>::Vector(Vector<T> &v)
{
	for(int i = 0; i < v.size(); i++)
		vec.push_back(*v[i]);
}

template <typename T>
Vector<T>::~Vector()
{ }

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &v)
{
	if(this == &v) 
		return *this;

	vec.clear();

	for(int i = 0; i < v.size(); i++)
		vec.push_back(*v[i]);

	return *this;
}

template <typename T>
typename std::vector<T>::iterator Vector<T>::operator[](const int &index)
{
	if(index >= vec.size() || index < 0)
		std::cerr << "Error: invalid index." << std::endl;

	return vec.begin() + index;
}

template <typename T>
typename std::vector<T>::iterator Vector<T>::find(const T &key)
{
	if(vec.empty())
		throw Error("Error: element not found.\n"); 

	typename std::vector<T>::iterator iter;

	if(vec.front() == key)
	{
		iter = vec.begin();
		return iter;
	}
	else if(vec.back() == key)
	{
		iter = vec.end() - 1;
		return iter;
	}
	
	for(iter = vec.begin() + 1; iter != vec.end(); iter++)
		if(*iter == key)
			return iter;

	//выбрасываетс¤ исключение, т.к. итератор не может указывать на нулл
	throw Error("Error: element not found.\n"); 
}

template <typename T>
void Vector<T>::print() const
{
	if(vec.empty())
	{
		std::cerr << "Error: vector is empty.\n";
		return;
	}

	std::cout << "¬ектор содержит:\n";
	for(int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << "  ";
	
	std::cout << std::endl;
}

template <typename T>
void Vector<T>::addElementToPosition(const T &key, const int &pos)
{
	if(pos <= 0 || pos > vec.size() + 1)
	{
		std::cerr << "Error: invalid position value. It must be in the range 1-" << vec.size() + 1 << ".\n";
		return;
	}

	typename std::vector<T>::iterator iterKey = find(key);
	typename std::vector<T>::iterator iterPos = vec.begin() + (pos - 1);

	vec.insert(iterPos, *iterKey);
}

template <typename T>
void Vector<T>::removeElement(const T &key)
{
	if(vec.empty())
	{
		std::cerr << "Error: vector is empty.\n";
		return;
	}

	typename std::vector<T>::iterator iter = find(key);

	vec.erase(iter);
}

template <typename T>
void Vector<T>::reduceElements(const T &val)
{
	if(val == 0)
		return;

	else if(vec.empty())
	{
		std::cerr << "Error: vector is empty.\n";
		return;
	}
	
	for(int i = 0; i < vec.size(); i++)
		vec[i] = vec[i] - val;
}	

template <typename T>
T Vector<T>::findDifference()
{
	if(vec.empty())
	{
		std::cerr << "Error: vector is empty.\n";
		return 0;
	}

	T min = vec[0], max = vec[0];

	for(int i = 1; i < vec.size(); i++)
	{
		if(vec[i] > max)
			max = vec[i];

		else if(vec[i] < min)
			min = vec[i];
	}

	return (max - min);
}