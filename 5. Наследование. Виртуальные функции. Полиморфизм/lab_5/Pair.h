#pragma once
#include "Object.h"
#include <iostream>

class Pair : public Object
{
protected:
	int first;
	int second;

public:
	Pair();
	Pair(const int &f, const int &s);
	Pair(const Pair &p);
	virtual ~Pair();
	int getFirst() const;
	int getSecond()   const;
	void setFirst(const int &val);
	void setSecond(const int &val);
	void show();
	int multiply() const;
	Pair& operator=(const Pair &p);
	friend std::istream& operator>>(std::istream &in, Pair &p);
	friend std::ostream& operator<<(std::ostream &out, const Pair &p);
};

