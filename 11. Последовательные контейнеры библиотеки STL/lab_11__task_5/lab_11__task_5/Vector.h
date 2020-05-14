#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Error.h"


template <typename T>
std::vector<T> copyQueueToVector(std::priority_queue<T> que)
{
	std::vector<T> vec;

	while(!que.empty())
	{
		vec.push_back(que.top());
		que.pop();
	}

	return vec;
}

template <typename T>
std::priority_queue<T> copyVectorToQueue(std::vector<T> vec)
{
	std::priority_queue<T> que;

	for(int i = 0; i < vec.size(); i++)
		que.push(vec[i]);

	return que;
}




template <typename T>
class Vector
{
private:
	std::priority_queue<T> que;
	
public:
	Vector();
	Vector(const int &length);
	Vector(const Vector<T> &v);
	~Vector();
	int size() { return que.size(); }
	Vector& operator=(Vector<T> &v);
	T find(const T &key);
	void print() const;
	void addElementWithKey(const T &key);
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
		throw Error("Error: vector size must be 0 or higher");

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

		que.push(tmp);
	}
}

template <typename T>
Vector<T>::Vector(const Vector<T> &v)
{
	std::vector<T> vec = copyQueueToVector(v.que);
	
	que = copyVectorToQueue(vec);
}

template <typename T>
Vector<T>::~Vector()
{ }

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &v)
{
	if(this == &v) 
		return *this;

	std::vector<T> vec = copyQueueToVector(v.que);
	
	que = copyVectorToQueue(vec);

	return *this;
}

template <typename T>
T Vector<T>::find(const T &key)
{
	if(que.empty())
		throw Error("Error: element not found.\n"); 

	std::priority_queue<T> tmp = que;

	while(!tmp.empty())
	{
		if(tmp.top() == key)
			return tmp.top();

		tmp.pop();
	}

	throw Error("Error: element not found.\n");
}

template <typename T>
void Vector<T>::print() const
{
	if(que.empty())
	{
		std::cerr << "Error: vector is empty.\n";
		return;
	}

	std::vector<T> vec = copyQueueToVector(que);

	std::cout << "¬ектор содержит:\n";
	for(int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << "  ";
	std::cout << std::endl;
}

template <typename T>
void Vector<T>::addElementWithKey(const T &key)
{
	//проверка находитс¤ ли нужный элемент в очереди
	T val = find(key);
	
	//если элемент найден, просто добавл¤ем его в очередь (позицию в очереди выбрать нельз¤)
	que.push(val);
}

template <typename T>
void Vector<T>::removeElement(const T &key)
{
	T val = find(key);

	std::vector<T> vec = copyQueueToVector(que);
	typename std::vector<T>::iterator iter = std::find(vec.begin(), vec.end(), val);
	vec.erase(iter);

	que = copyVectorToQueue(vec);
}

template <typename T>
void Vector<T>::reduceElements(const T &val)
{
	if(val == 0)
		return;

	else if(que.empty())
	{
		std::cerr << "Error: vector is empty.\n";
		return;
	}

	std::vector<T> vec;

	while(!que.empty())
	{
		vec.push_back(que.top() - val);
		que.pop();
	}

	que = copyVectorToQueue(vec);
}	

template <typename T>
T Vector<T>::findDifference()
{
	if(que.empty())
	{
		std::cerr << "Error: vector is empty.\n";
		return 0;
	}

	std::vector<T> vec = copyQueueToVector(que);

	return vec[0] - vec[vec.size() - 1];
}