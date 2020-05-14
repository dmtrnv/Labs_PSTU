#pragma once
#include "Object.h"
#include <iostream>


class Vector
{
private:
	Object **beg;
	int size;
	int cur;

public:
	Vector();
	Vector(const int &n);
	~Vector();
	void add(Object *o);
	friend std::ostream& operator<<(std::ostream &out, const Vector &v);
};

