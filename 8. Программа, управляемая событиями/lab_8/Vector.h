#pragma once
#include "Object.h"
#include "Person.h"
#include "Abiturient.h"
#include <iostream>


class Vector
{
protected:
	Object **beg;
	int size;
	int cur;

public:
	Vector(const int &_size = 5);
	Vector(const Vector &v);
	~Vector();
	void Add();
	void Add(Object *obj);
	void Del();
	void Show() const;
	void HandleEvent(const TEvent &event);
	Vector& operator=(const Vector &v);
	int operator()() const; //размер вектора
};

