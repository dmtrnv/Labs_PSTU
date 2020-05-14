#include "Rightangled.h"


Rightangled::Rightangled() : Pair()
{ }

Rightangled::Rightangled(const int &f, const int &s) : Pair(f, s)
{ }

Rightangled::Rightangled(const Rightangled &r)
{
	first = r.first;
	second = r.second;
}

Rightangled::~Rightangled()
{ }

double Rightangled::hypotenuse() const
{
	return sqrt(first*first + second*second);
}

Rightangled& Rightangled::operator=(const Rightangled &r)
{
	if(&r == this) return *this;

	first = r.first;
	second = r.second;

	return *this;
}

std::istream& operator>>(std::istream &in, Rightangled &r)
{
	std::cout << "Введите длину первого катета: ";
	in >> r.first;
	while(in.fail() || r.first < 0)
		if(in.fail())
		{
			in.clear();
			in.ignore(100, '\n');
			std::cerr << "Ошибка: вы ввели некорректный символ. Попробуйте снова: ";
			in >> r.first;
		}
		else
		{
			std::cerr << "Ошибка: длина катета не может быть отрицательной. Попробуйте снова: ";
			in >> r.first;
		}

	std::cout << "Введите длину второго катета: ";
	in >> r.second;
	while(in.fail() || r.second < 0)
		if(in.fail())
		{
			in.clear();
			in.ignore(100, '\n');
			std::cerr << "Ошибка: вы ввели некорректный символ. Попробуйте снова: ";
			in >> r.second;
		}
		else
		{
			std::cerr << "Ошибка: длина катета не может быть отрицательной. Попробуйте снова: ";
			in >> r.second;
		}

	return in;
}
std::ostream& operator<<(std::ostream &out, const Rightangled &r)
{
	out << "Длина первого катета = " << r.first << std::endl
		<< "Длина второго катета = " << r.second << std::endl;

	return out;
}