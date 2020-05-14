#include "Abiturient.h"


Abiturient::Abiturient() : Person()
{
	points = 0;
	specialty = "";
}

Abiturient::Abiturient(const std::string &_name, const int &_age, const int &_pts, const std::string &_splty) : Person(_name, _age)
{
	if(_pts < 0)
	{
		std::cerr << "Error: entered value for field points is negative." << std::endl;
		exit(EXIT_FAILURE);
	}

	points = _pts;
	specialty = _splty;
}

Abiturient::Abiturient(const Abiturient &a)
{
	name = a.name;
	age = a.age;
	points = a.points;
	specialty = a.specialty;
}

Abiturient::~Abiturient()
{ }

void Abiturient::Show() const
{
	std::cout << "Name - " << name << std::endl 
			  << "Age - " << age << std::endl
			  << "Points - " << points << std::endl
			  << "Specialty - " << specialty << std::endl;
}

void Abiturient::Input()
{
	std::cout << "Enter name: ";
	std::cin >> name;

	std::cout << "Enter age: ";
	std::cin >> age;
		while(std::cin.fail() || age < 0)
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cerr << "Error: invalid character entered. Try again: ";
			std::cin >> age;
		}
		else
		{
			std::cerr << "Error: entered value for field age is negative. Try again: ";
			std::cin >> age;
		}

	std::cout << "Enter points: ";
	std::cin >> points;
		while(std::cin.fail() || points < 0)
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cerr << "Error: invalid character entered. Try again: ";
			std::cin >> points;
		}
		else
		{
			std::cerr << "Error: entered value for field points is negative. Try again: ";
			std::cin >> points;
		}

	std::cout << "Enter specialty: ";
	std::cin >> specialty;
}

void Abiturient::setPoints(const int &_pts)
{
	if(_pts < 0)
	{
		std::cerr << "Error: entered value for field points is negative." << std::endl;
		exit(EXIT_FAILURE);
	}

	points = _pts;
}

void Abiturient::setSpecialty(const std::string &_splty)
{
	specialty = _splty;
}
	
Abiturient& Abiturient::operator=(const Abiturient &a)
{
	if(this == &a)
		return *this;

	name = a.name;
	age = a.age;
	points = a.points;
	specialty = a.specialty;

	return *this;
}