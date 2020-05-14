#pragma once
#include <iostream>


class Iterator
{
	friend class Vector;

private:
	int *elem;

public:
	Iterator() { elem = nullptr; }
	Iterator(const Iterator &it) { elem = it.elem; }
	bool operator==(const Iterator &it) const { return elem == it.elem; }
	bool operator!=(const Iterator &it) const { return elem != it.elem; }
	void operator++() { ++elem; }
	void operator--() { --elem; }
	int& operator*() const { return *elem; }
	Iterator& operator=(const Iterator &it);
};


class Vector
{
private:
	int size;
	int *data;
	Iterator begin;
	Iterator end; //pointer to the element following the last one
	
public:
	Vector();
	Vector(const int &s, const int &k = 0);
	Vector(const Vector &v);
	~Vector();
	Iterator first() const { return begin; }
	Iterator last() const { return end; }
	int getSize() const { return size; }
	Vector& operator=(const Vector &v);
	int& operator[](const int &index) const;
	Vector operator+(const Vector &v) const;
	Vector& operator+(const int &val);
	friend std::istream& operator>>(std::istream &in, Vector &v);
	friend std::ostream& operator<<(std::ostream &out, const Vector &v);
};