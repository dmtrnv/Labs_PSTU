#include "Time.h"


Time::Time()
{
	min = 0;
	sec = 0;
}

Time::Time(const int &m, const int &s)
{
	if(s > 60 || s < 0)
	{
		std::cerr << "Ошибка: поле sec вне диапазона (допустимый диапазон: 0-59)." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if(m < 0)
	{
		std::cerr << "Ошибка: поле min не может принимать отрицательное значение." << std::endl;
		exit(EXIT_FAILURE);
	}

	min = m;
	sec = s;
}

Time::Time(const Time &t)
{
	min = t.min;
	sec = t.sec;
}

Time::~Time() 
{ }

int Time::getMin() const
{
	return min;
}

int Time::getSec() const
{
	return sec;
}

void Time::setMin(const int &val)
{
	if(val <= 0)
		return;

	min = val;
}

void Time::setSec(const int &val)
{
	if(val <= 0)
		return;

	sec = val;
}

void Time::addSec(const int &val)
{
	if(val <= 0)
		return;

	int tmp = min*60 + sec + val;
	min = tmp / 60;
	sec = tmp % 60;
}

void Time::subtractSec(const int &val)
{
	if(val <= 0)
		return;

	int tmp = min*60 + sec - val;
	min = tmp / 60;
	sec = tmp % 60;
}

Time& Time::operator=(const Time &t)
{
	if(&t == this) return *this;

	min = t.min;
	sec = t.sec;

	return *this;
}

std::istream& operator>>(std::istream &in, Time &t)
{
	std::cout << "min: ";
	in >> t.min;
	while(in.fail() || t.min < 0)
		if(in.fail())
		{
			in.clear();
			in.ignore(100, '\n');
			std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
			in >> t.min;
		}
		else
		{
			std::cerr << "Ошибка: единица времени не может быть отрицательной. Попробуйте снова: ";
			in >> t.min;
		}

	std::cout << "sec: ";
	in >> t.sec;
	while(in.fail() || t.sec < 0 || t.sec >= 60)
		if(in.fail())
		{
			in.clear();
			in.ignore(100, '\n');
			std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
			in >> t.sec;
		}
		else
		{
			std::cerr << "Ошибка: поле sec вне диапазона (допустимый диапазон: 0-59). Попробуйте снова: ";
			in >> t.sec;
		}

	return in;
}

std::ostream& operator<<(std::ostream &out, const Time &t)
{
	if(t.min < 10)
		out << "0" << t.min << ":";
	else 
		out << t.min << ":";

	if(t.sec < 10)
		out << "0" << t.sec;
	else
		out << t.sec;

	return out;
}