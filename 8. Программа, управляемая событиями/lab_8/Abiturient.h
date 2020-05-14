#pragma once
#include "Person.h"
#include <string>
#include <iostream>


class Abiturient : public Person
{
private:
	int points;
	std::string specialty;
	
public:
	Abiturient();
	Abiturient(const std::string &_name, const int &_age, const int &_pts, const std::string &_splty);
	Abiturient(const Abiturient &a);
	~Abiturient();
	void Show() const;
	void Input();
	int getPoints() { return points; }
	std::string getSpecialty() { return specialty; }
	void setPoints(const int &_pts);
	void setSpecialty(const std::string &_splty);
	Abiturient& operator=(const Abiturient &a);
};

