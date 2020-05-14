#include "Vector.h"


Vector::Vector(const int &_size)
{
	if(_size <= 0)
	{
		std::cerr << "Error: entered invalid value for field size." << std::endl;
		exit(EXIT_FAILURE);
	}

	beg = new Object*[_size];
	size = _size;
	cur = 0;
}

Vector::Vector(const Vector &v)
{
	size = v.size;
	cur = v.cur;
	beg = new Object*[size];

	for(int i = 0; i < size; i++)
		beg[i] = v.beg[i];
}

Vector::~Vector()
{
	if(beg != nullptr)
	{
		for(int i = 0; i < cur; i++)
			delete beg[i];

		delete [] beg;
		beg = nullptr;
	}
}
	
void Vector::Add()
{
	if(cur >= size)
	{
		std::cerr << "Error: vector is full." << std::endl;
		return;
	}

	Object *obj;

	std::cout << "Select object type (1 - Person, 2 - Abiturient): ";
	int type;
	std::cin >> type;
	while(std::cin.fail() || type < 1 || type > 2)
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cerr << "Error: invalid character entered. Try again: ";
		std::cin >> type;
	}

	if(type == 1)
	{
		Person *p = new Person;
		p->Input();
		obj = p;

		beg[cur] = obj;
		cur++;	
	}
	else
	{
		Abiturient *p = new Abiturient;
		p->Input();
		obj = p;

		beg[cur] = obj;
		cur++;
	}	
}

void Vector::Add(Object *obj)
{
	if(cur >= size)
	{
		std::cerr << "Error: vector is full." << std::endl;
		return;
	}

	if(obj == nullptr)
	{
		std::cerr << "Error: object you trying to add is not initialized." << std::endl;
		return;
	}

	beg[cur] = obj;
	cur++;
}

void Vector::Del()	//память не освобождается (освобождается при вызове деструктора)
{
	if(cur == 0)	
		return;
	
	cur--;
}

void Vector::Show() const
{
	if(cur == 0)
	{
		std::cout << "Vector is empty." << std::endl;
		return;
	}

	for(int i = 0; i < cur; i++)
		beg[i]->Show();
}

void Vector::HandleEvent(const TEvent &event)
{
	if(event.what == evMessage)
	{
		double averageAge = 0;

		for(int i = 0; i < cur; i++)
			averageAge += beg[i]->HandleEvent(event);

		std::cout << "Average age: " << averageAge / cur << std::endl;
	}
}

Vector& Vector::operator=(const Vector &v)
{
	if(this == &v)
		return *this;

	size = v.size;
	cur = v.cur;

	if(beg != nullptr)
	{
		for(int i = 0; i < cur; i++)
			delete beg[i];

		delete [] beg;
		beg = nullptr;
	}

	beg = new Object*[size];
	for(int i = 0; i < size; i++)
		beg[i] = v.beg[i];

	return *this;
}

int Vector::operator()() const
{
	return size;
}