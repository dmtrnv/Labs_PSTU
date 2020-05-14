#pragma once
#include <string>
#include <iostream>
#include <fstream>


class Student
{
	private:
		std::string group;
		std::string name;

	public:
		Student(const std::string &_group = "", const std::string &_name = "");
		Student(const Student &_student);
		~Student();
		std::string getGroup() const { return group; }
		std::string getName() const { return name; }
		void setGroup(const std::string &_group) { group = _group; }
		void setName(const std::string &_name) { name = _name; }
		Student& operator=(const Student &_student);
		bool operator==(const Student &_student);
		friend std::istream& operator>>(std::istream &in, Student &_student);
		friend std::ostream& operator<<(std::ostream &out, const Student &_student);
		friend std::fstream& operator>>(std::fstream &fin, Student &_student);
		friend std::fstream& operator<<(std::fstream &fout, Student &_student);
};

