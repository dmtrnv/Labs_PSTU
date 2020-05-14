#include "Vector.h"


Iterator& Iterator::operator=(const Iterator &it) 
{ 
	if(this == &it) 
		return *this;

	elem = it.elem; 

	return *this;
}

Vector::Vector()
{
	size = 0;
	data = nullptr;
}

Vector::Vector(const int &s, const int &k)
{
	size = s;
	data = new int[size];

	for(int i = 0; i < size; i++)
		data[i] = k;

	begin.elem = &data[0];
	end.elem = &data[size];
}

Vector::Vector(const Vector &v)
{
	size = v.size;
	data = new int[size];

	for(int i = 0; i < size; i++)
	{
		data[i] = v.data[i];
	}

	begin.elem = &data[0];
	end.elem = &data[size]; 
}

Vector::~Vector()
{
	delete [] data;
	data = nullptr;
}

Vector& Vector::operator=(const Vector &v)
{
	if(this == &v) 
		return *this;

	size = v.size;

	if(data != nullptr)
		delete [] data;

	data = new int[size];
	for(int i = 0; i < size; i++)
		data[i] = v.data[i];

	begin.elem = &data[0];
	end.elem = &data[size];

	return *this;
}

int& Vector::operator[](const int &index) const
{
	if(index >= size || index < 0)
	{
		std::cerr << "Error: index is not valid." << std::endl;
		exit(EXIT_FAILURE);
	}

	return data[index];
}

Vector Vector::operator+(const Vector &v) const
{
	if(data == nullptr || v.data == nullptr)
	{
		std::cerr << "Error: vector is not initialized." << std::endl;
		exit(EXIT_FAILURE);
	}

	if(size != v.size)
	{
		std::cerr << "Error: summable vectors have different sizes." << std::endl;
		exit(EXIT_FAILURE);
	}

	Vector sum(size);
	for(int i = 0; i < size; i++)
		sum.data[i] = data[i] + v.data[i];

	return sum;
}

Vector& Vector::operator+(const int &val)
{
	for(int i = 0; i < size; i++)
		data[i] += val;

	return *this;
}

std::istream& operator>>(std::istream &in, Vector &v)
{
	std::cout << "Enter vector elements: \n";
	for(int i = 0; i < v.size; i++)
	{
		std::cout << "data[" << i << "] = ";
		in >> v.data[i];

		while(in.fail())
		{
			in.clear();
			in.ignore(100, '\n');
			std::cerr << "Error: invalid character entered. Try again: " << std::endl;
			std::cout << "data[" << i << "] = ";
			in >> v.data[i];
		}
	}

	return in;
}

std::ostream& operator<<(std::ostream &out, const Vector &v)
{
	for(int i = 0; i < v.size; i++)
		std::cout << v.data[i] << "  ";
	
	std::cout << std::endl;
	return out;
}