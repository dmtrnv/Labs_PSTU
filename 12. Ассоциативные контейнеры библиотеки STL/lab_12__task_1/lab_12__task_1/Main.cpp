#include <iostream>
#include <set>
#include <iomanip>
#include "Errorr.h"


typedef std::multiset<double> multiset;


multiset makeMultiset(const int &size);
void printMultiset(const multiset &ms);
void addElement(multiset &ms, const double &val);
void removeElement(multiset &ms, const double &val);
double findDifference(const multiset &ms);
void reduceElements(multiset &ms, const double &val);


int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		multiset ms = {5.25, 4.19, -1.12, 0.00, 7.11, 9.03, 6.18};
		printMultiset(ms);

		addElement(ms, 4.19);
		std::cout << "Добавлен элемент 4.19.\n";
		printMultiset(ms);

		removeElement(ms, 6.18);
		std::cout << "Удален элемент 6.18.\n";
		printMultiset(ms);

		double val = findDifference(ms);
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
	double elem = 0;

	std::cout << "Enter multiset elements:\n";
	for(int i = 0; i < size; i++)
	{
		std::cin >> elem;
		if(std::cin.fail())
		{
			std::cerr << "Error: entered invalid character. Try again:\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cin >> elem;
		}

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
		std::cout << std::fixed << std::setprecision(2) << var << "  ";
	std::cout << std::endl;
}

void addElement(multiset &ms, const double &val)
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

void removeElement(multiset &ms, const double &val)
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

double findDifference(const multiset &ms)
{
	if(ms.empty())
	{
		std::cerr << "Error: multiset is empty.\n";
		return 0;
	}

	return *ms.end().operator--() - *ms.begin();
}

void reduceElements(multiset &ms, const double &val)
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