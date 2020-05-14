#include "Vector.h"


Vector::Vector()
{
	size = 0;
	data = nullptr;
}

Vector::Vector(const int &_size)
{
	if(_size > MAX_SIZE) 
		throw MaxSizeError();

	if(_size < 0)
		throw MinSizeError();

	size = _size;
	data = new int[size];

	for(int i = 0; i < size; i++)
		data[i] = 0;
}

Vector::Vector(const int &_size, const int *_data)
{
	if(_size > MAX_SIZE) 
		throw MaxSizeError();

	if(_size < 0)
		throw MinSizeError();

	size = _size;
	data = new int[size];

	for(int i = 0; i < size; i++)
		data[i] = _data[i];
}

Vector::Vector(const Vector &v)
{
	size = v.size;
	data = new int[size];

	for(int i = 0; i < size; i++)
		data[i] = v.data[i];
}

Vector::~Vector()
{
	if(data != nullptr)
	{
		delete [] data;
		data = nullptr;
	}
}

Vector& Vector::operator=(const Vector &v)
{
	if(this == &v)
		return *this;

	if(data != nullptr)
		delete [] data;

	size = v.size;
	data = new int[size];

	for(int i = 0; i < size; i++)
		data[i] = v.data[i];

	return *this;
}

int& Vector::operator[](const int &index) const
{
	if(index >= size)
		throw MaxIndexError();

	if(index < 0)
		throw MinIndexError();

	return data[index];
}

void Vector::operator++()
{
	if(size + 1 > MAX_SIZE) 
		throw MaxSizeError();

	std::cout << "Enter element to add: ";
	int elem;
	std::cin >> elem;

	Vector temp(size + 1);
	for(int i = 1 ; i < temp.size; i++)
		temp[i] = data[i - 1];

	temp[0] = elem;

	*this = temp;
}

void Vector::operator++(int)
{
	if(size + 1 > MAX_SIZE) 
		throw MaxSizeError();

	std::cout << "Enter element to add: ";
	int elem;
	std::cin >> elem;

	Vector temp(size + 1);
	for(int i = 0 ; i < size; i++)
		temp[i] = data[i];

	temp[size] = elem;

	*this = temp;
}

std::istream& operator>>(std::istream &in, Vector &v)
{
	if(v.size == 0) 
		std::cout << "Vector is empty.\n";
	else
	{
		std::cout << "Enter vector elements:\n";
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
	}

	return in;
}

std::ostream& operator<<(std::ostream &out, const Vector &v)
{
	if(v.size == 0)
		std::cout << "Vector is empty.\n";
	else
	{
		std::cout << "Vector contains:\n";

		for(int i = 0; i < v.size; i++)
			std::cout << v.data[i] << "  ";

		std::cout << std::endl;
	}
	
	return out;
}