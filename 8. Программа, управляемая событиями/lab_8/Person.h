#pragma once
#include "Object.h"
#include <string>
#include <iostream>


class Person : public Object
{
protected:
	std::string name;
	int age;

public:
	Person();
	Person(const std::string &_name, const int &_age);
	Person(const Person &p);
	virtual ~Person();
	void Show() const;
	void Input();
	int HandleEvent(const TEvent &event);
	std::string getName() const { return name; }
	int getAge() const { return age; }
	void setName(const std::string &_name);
	void setAge(const int &_age);
	Person& operator=(const Person &p);
};

