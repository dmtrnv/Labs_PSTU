#include "Person.h"


Person::Person()
{
	name = "";
	age = 0;
}

Person::Person(const std::string &_name, const int &_age)
{
	if(_age < 0)
	{
		std::cerr << "Error: entered value for field age is negative." << std::endl;
		exit(EXIT_FAILURE);
	}

	name = _name;
	age = _age;
}
	
Person::Person(const Person &p)
{
	name = p.name;
	age = p.age;
}

Person::~Person()
{ }

void Person::Show() const
{
	std::cout << "Name - " << name << std::endl
			  << "Age - " << age << std::endl;
}

void Person::Input()
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
}

int Person::HandleEvent(const TEvent &event)
{
	if(event.what == evMessage)
	{
		switch(event.command)
		{
			case cmGet:
				return age;
				break;	
		}
	}
	else
		return 0;
}

void Person::setName(const std::string &_name)
{
	name = _name;
}

void Person::setAge(const int &_age)
{
	if(_age < 0)
	{
		std::cerr << "Error: entered value for field age is negative." << std::endl;
		exit(EXIT_FAILURE);
	}

	age = _age;
}

Person& Person::operator=(const Person &p)
{
	if(this == &p)
		return *this;

	name = p.name;
	age = p.age;

	return *this;
}