#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include "Time.h"
#include "Error.h"


typedef std::map<std::string, Time> map;
typedef std::pair<std::string, Time> pair;


map make(const int &size);
void print(map &mp);
void addElement(map &mp, const pair &val);
void removeElement(map &mp, const pair &val);
Time findValueDifference(const map &mp);
void reduceElementsValue(map &mp, const Time &val);


int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		map mp = { {"sleep", 128},
				   {"eat", 248},
				   {"swim", 212},
				   {"play", 55},
				   {"write", 160},
				   {"read", 185} };
		print(mp);
		
		pair p = {"walk", 177};
		addElement(mp, p);
		std::cout << "Добавлен элемент \"walk\".\n";
		print(mp);

		removeElement(mp, {"play", 55});
		std::cout << "Удален элемент \"play\".\n";
		print(mp);

		Time t = findValueDifference(mp);
		reduceElementsValue(mp, t);
		std::cout << "Из каждого элемента контейнера вычтена разница между минимальным и максимальным элементами.\n";
		print(mp);
	}
	catch(Error &e)
	{
		e.what();
	}

	system("pause");
	return 0;
}


map make(const int &size)
{
	if(size < 0)
		throw Error("Error: map size must be 0 or higher");

	map mp;
	Time time;

	for(int i = 0; i < size; i++)
	{
		std::cout << "event: ";
		std::string event;
		std::cin >> event;
		std::cin >> time;
		mp.emplace(event, time);
	}

	return mp;
}

void print(map &mp)
{
	if(mp.empty())
	{
		std::cerr << "Error: map is empty.\n";
		return;
	}

	std::cout << "Словарь содержит:\n";
	for(const pair &p : mp)
		std::cout << p.first << " - " << p.second << std::endl;
	std::cout << "***********\n";
}

void addElement(map &mp, const pair &val)
{
	map::iterator iter = std::find_if(mp.begin(), mp.end(), [val](const pair &p)
	{
		return p.first == val.first;
	});

	if(iter == mp.end())
		mp.insert(val);
	else
	{
		std::cerr << "Error: element with given key is already in map.\n";
		return;
	}
}

void removeElement(map &mp, const pair &val)
{
	if(mp.empty())
	{
		std::cerr << "Error: map is empty.\n";
		return;
	}

	map::iterator iter = std::find_if(mp.begin(), mp.end(), [val](const pair &p)
	{
		return (p.first == val.first && p.second == val.second);
	});

	if(iter == mp.end())
	{
		std::cerr << "Error: element not found.\n";
		return;
	}
	else
		mp.erase(iter);
}

Time findValueDifference(const map &mp)
{
	if(mp.empty())
	{
		std::cerr << "Error: map is empty.\n";
		return 0;
	}

	auto max = std::max_element(mp.begin(), mp.end(), [](const pair &p, const pair &pr)
	{ 
		return p.second < pr.second;
	});

	auto min = std::min_element(mp.begin(), mp.end(), [](const pair &p, const pair &pr)
	{ 
		return p.second < pr.second;
	});

	return (*max).second - (*min).second;
}

void reduceElementsValue(map &mp, const Time &val)
{
	if(val == 0)
		return;

	else if(mp.empty())
	{
		std::cerr << "Error: map is empty.\n";
		return;
	}

	std::for_each(mp.begin(), mp.end(), [val](std::pair<const std::string, Time> &p)
	{
		p.second = p.second - val;
	});
}
