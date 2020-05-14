#include <iostream>
#include <set>
#include "Time.h"
#include "Error.h"


typedef std::multiset<Time> multiset;


multiset makeMultiset(const int &size);
void printMultiset(const multiset &ms);
void addElement(multiset &ms, const Time &val);
void removeElement(multiset &ms, const Time &val);
Time findDifference(const multiset &ms);
void reduceElements(multiset &ms, const Time &val);


int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		multiset ms = {125, 119, 318, 223, 215, 341, 189};
		printMultiset(ms);

		addElement(ms, 223);
		std::cout << "Добавлен элемент 3:43.\n";
		printMultiset(ms);

		removeElement(ms, 215);
		std::cout << "Удален элемент 3:35.\n";
		printMultiset(ms);

		Time val = findDifference(ms);
		reduceElements(ms, val);
		std::cout << "Из каждого элемента контейнера вычтена разница между минимальным и максимальным элементами.\n";
		printMultiset(ms);
	}
	catch(Error &e)
	{
		e.what();
	}

	system("pause");
	return 0;
}




multiset makeMultiset(const int &size)
{
	if(size < 0)
		throw Error("Error: multiset set size must be 0 or higher.\n");

	multiset ms;
	Time elem;

	std::cout << "Enter multiset elements:\n";
	for(int i = 0; i < size; i++)
	{
		std::cin >> elem;
		ms.insert(elem);
	}

	return ms;
}

void printMultiset(const multiset &ms)
{
	if(ms.empty())
	{
		std::cerr << "Error: multiset is empty.\n";
		return;
	}

	std::cout << "Множество содержит:\n";
	for(const auto &var : ms)
		std::cout << var << "  ";
	std::cout << std::endl;
}

void addElement(multiset &ms, const Time &val)
{
	multiset::iterator iter = ms.find(val);

	if(iter == ms.end())
	{
		std::cerr << "Error: element not found.\n";
		return;
	}
	else
		ms.insert(val);
}

void removeElement(multiset &ms, const Time &val)
{
	if(ms.empty())
	{
		std::cerr << "Error: multiset is empty.\n";
		return;
	}

	multiset::iterator iter = ms.find(val);

	if(iter == ms.end())
	{
		std::cerr << "Error: element not found.\n";
		return;
	}
	else
		ms.erase(val);
}

Time findDifference(const multiset &ms)
{
	if(ms.empty())
	{
		std::cerr << "Error: multiset is empty.\n";
		return 0;
	}

	return *ms.end().operator--() - *ms.begin();
}

void reduceElements(multiset &ms, const Time &val)
{
	if(val == 0)
		return;

	else if(ms.empty())
	{
		std::cerr << "Error: multiset is empty.\n";
		return;
	}

	multiset tmp;
	multiset::iterator iter;

	for(iter = ms.begin(); iter != ms.end(); iter++)
		tmp.insert(*iter - val);

	ms.clear();
	ms = tmp;
}
