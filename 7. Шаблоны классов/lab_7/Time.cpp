#include "Time.h"


Time::Time()
{
	min = 0;
	sec = 0;
}

Time::Time(const int &time)
{
	if(time < 0)
	{
		std::cerr << "Error: time unit is out of range." << std::endl;
		exit(EXIT_FAILURE);
	}

	min = time / 60;
	sec = time % 60;
}

Time::Time(const int &m, const int &s)
{
	if(s > 60 || s < 0)
	{
		std::cerr << "Error: sec field is out of range (must be 0-59)." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if(m < 0)
	{
		std::cerr << "Error: min field can't be negative." << std::endl;
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

Time& Time::operator+(const int &val)
{
	if(val <= 0)
		return *this;

	int tmp = min*60 + sec + val;
	min = tmp / 60;
	sec = tmp % 60;

	return *this;
}

Time Time::operator+(const Time &t) const
{
	int tmp = min*60 + sec + t.min*60 + t.sec;
	Time result(tmp/60, tmp%60);

	return result;
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
			in>> t.min;
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
