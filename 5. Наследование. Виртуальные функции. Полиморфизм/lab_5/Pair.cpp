#include "Pair.h"


Pair::Pair()
{
	first = 0;
	second = 0;
}

Pair::Pair(const int &f, const int &s)
{
	first = f;
	second = s;
}

Pair::Pair(const Pair &p)
{
	first = p.first;
	second = p.second;
}

Pair::~Pair()
{ };

int Pair::getFirst() const
{
	return first;
}

int Pair::getSecond() const
{
	return second;
}

void Pair::setFirst(const int &val)
{
	first = val;
}

void Pair::setSecond(const int &val)
{
	second = val;
}

int Pair::multiply() const
{
	return first * second;
}

void Pair::show()
{
	std::cout << "first: " << first << "\tsecond: " << second << std::endl;
}

Pair& Pair::operator=(const Pair &p)
{
	if(&p == this) return *this;

	first = p.first;
	second = p.second;

	return *this;
}

std::istream& operator>>(std::istream &in, Pair &p)
{
	std::cout << "first: ";
	in >> p.first;
	while(in.fail())
	{
		in.clear();
		in.ignore(100, '\n');
		std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
		in >> p.first;
	}

	std::cout << "second: ";
	in >> p.second;
	while(in.fail())
	{
		in.clear();
		in.ignore(100, '\n');
		std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
		in >> p.first;
	}

	return in;
}

std::ostream& operator<<(std::ostream &out, const Pair &p)
{
	out << "first: " << p.first << "\tsecond: " << p.second << std::endl;
	return out;
}
