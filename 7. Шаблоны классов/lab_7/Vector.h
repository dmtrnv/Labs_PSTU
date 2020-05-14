#pragma once
#include <iostream>


template <typename T>
class Vector
{
private:
	int size;
	T *data;
	
public:
	Vector();
	Vector(const int &s, const T &k = 0);
	Vector(const Vector<T> &v);
	~Vector();
	int getSize() const { return size; }
	Vector& operator=(const Vector<T> &v);
	T& operator[](const int &index) const;
	Vector operator+(const Vector<T> &v) const;
	Vector& operator+(const T &val);
	template <typename T> friend std::istream& operator>>(std::istream &in, Vector<T> &v);
	template <typename T> friend std::ostream& operator<<(std::ostream &out, const Vector<T> &v);
};


template <typename T>
Vector<T>::Vector()
{
	size = 0;
	data = nullptr;
}

template <typename T>
Vector<T>::Vector(const int &s, const T &k)
{
	size = s;
	data = new T[size];

	for(int i = 0; i < size; i++)
		data[i] = k;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &v)
{
	size = v.size;
	data = new T[size];

	for(int i = 0; i < size; i++)
		data[i] = v.data[i];
}

template <typename T>
Vector<T>::~Vector()
{
	delete [] data;
	data = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &v)
{
	if(this == &v) 
		return *this;

	size = v.size;

	if(data != nullptr)
		delete [] data;

	data = new T[size];
	for(int i = 0; i < size; i++)
		data[i] = v.data[i];

	return *this;
}

template <typename T>
T& Vector<T>::operator[](const int &index) const
{
	if(index >= size || index < 0)
	{
		std::cerr << "Error: index is not valid." << std::endl;
		exit(EXIT_FAILURE);
	}

	return data[index];
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &v) const
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

	Vector<T> sum(size);
	for(int i = 0; i < size; i++)
		sum.data[i] = data[i] + v.data[i];

	return sum;
}

template <typename T>
Vector<T>& Vector<T>::operator+(const T &val)
{
	for(int i = 0; i < size; i++)
		data[i] = data[i] + val;

	return *this;
}

template <typename T>
std::istream& operator>>(std::istream &in, Vector<T> &v)
{
	std::cout << "Enter vector elements: \n";
	for(int i = 0; i < v.size; i++)
	{
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

template <typename T>
std::ostream& operator<<(std::ostream &out, const Vector<T> &v)
{
	for(int i = 0; i < v.size; i++)
		std::cout << v.data[i] << "  ";
	
	std::cout << std::endl;
	return out;
}
