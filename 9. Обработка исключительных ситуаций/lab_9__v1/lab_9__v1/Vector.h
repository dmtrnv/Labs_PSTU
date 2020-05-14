#pragma once
#include <iostream>


const int MAX_SIZE = 10;


class Vector
{
	private:
		int size;
		int *data;

	public:
		Vector();
		Vector(const int &_size);
		Vector(const int &_size, const int *_data);
		Vector(const Vector &v);
		~Vector();
		Vector& operator=(const Vector &v);
		int& operator[](const int &index) const;
		void operator++();
		void operator++(int);
		friend std::istream& operator>>(std::istream &in, Vector &v);
		friend std::ostream& operator<<(std::ostream &out, const Vector &v);
};


