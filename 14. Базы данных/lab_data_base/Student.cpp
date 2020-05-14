#include "Student.h"


Student::Student(const std::string &_group, const std::string &_name)
{
	group = _group;
	name = _name;
}

Student::Student(const Student &_student)
{
	group = _student.group;
	name = _student.name;
}

Student::~Student()
{  }

Student& Student::operator=(const Student &_student)
{
	if(&_student == this)
		return *this;

	group = _student.group;
	name = _student.name;

	return *this;
}

bool Student::operator==(const Student &_student)
{
	if(group == _student.group && name == _student.name)
		return true;
	else
		return false;
}

std::istream& operator>>(std::istream &in, Student &_student)
{
	std::cout << "Введите название группы: ";
	std::getline(in, _student.group);

	std::cout << "Введите Ф.И.О. студента: ";
	std::getline(in, _student.name);

	return in;
}

std::ostream& operator<<(std::ostream &out, const Student &_student)
{
	out << _student.group << '\t' << _student.name << std::endl;

	return out;
}

std::fstream& operator>>(std::fstream &fin, Student &_student)
{
	std::getline(fin, _student.group);
	std::getline(fin, _student.name);

	return fin;
}

std::fstream& operator<<(std::fstream &fout, Student &_student)
{
	fout << _student.group << std::endl << _student.name << std::endl;

	return fout;
}