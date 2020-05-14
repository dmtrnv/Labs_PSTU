#include "Time.h"


Time::Time()
{
	min = 0;
	sec = 0;
}

Time::Time(const int &time)
{
	if(time < 0)
		throw Error("Error: time unit is out of range.\n");

	min = time / 60;
	sec = time % 60;
}

Time::Time(const int &m, const int &s)
{
	if(s >= 60 || s < 0)
		throw Error("Error: sec field is out of range (must be 0-59).\n");

	if(m < 0)
		throw Error("Error: min field can't be negative.\n");

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
	if(tmp < 0)
	{
		min = 0;
		sec = 0;
		return;
	}

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

bool Time::operator==(const Time &t) const
{
	if((*this).min == t.min && (*this).sec == t.sec)
		return true;

	return false;
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
			std::cerr << "Error: invalid character entered. Try again: ";
			in >> t.min;
		}
		else
		{
			std::cerr << "Error: the time unit cannot be negative. Try again: ";
			in >> t.min;
		}

	std::cout << "sec: ";
	in >> t.sec;
	while(in.fail() || t.sec < 0 || t.sec >= 60)
		if(in.fail())
		{
			in.clear();
			in.ignore(100, '\n');
			std::cerr << "Error: invalid character entered. Try again: ";
			in >> t.sec;
		}
		else
		{
			std::cerr << "Error: entered value is out of range (must be 0-59). Try again: ";
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

std::fstream& operator>>(std::fstream &fin, Time &t)
{
	fin >> t.min;
	fin >> t.sec;

	return fin;
}

std::fstream& operator<<(std::fstream &fout, Time &t)
{
	fout << t.min << std::endl << t.sec << std::endl;

	return fout;
}