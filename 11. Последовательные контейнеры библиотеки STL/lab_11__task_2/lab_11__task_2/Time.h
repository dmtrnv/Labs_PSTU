#pragma once
#include <iostream>
#include "Error.h"


class Time
{
	private:
		int min;
		int sec;

	public:
		Time();
		Time(const int &time);
		Time(const int &m, const int &s);
		Time(const Time &t);
		~Time();
		void addSec(const int &val);
		void subtractSec(const int &val);
		Time& operator=(const Time &t);
		Time operator-(const Time&t) const;
		bool operator==(const Time &t) const;
		bool operator>(const Time &t) const;
		bool operator<(const Time&t) const;
		friend std::istream& operator>>(std::istream &in, Time &t);
		friend std::ostream& operator<<(std::ostream &out, const Time &t);
};


