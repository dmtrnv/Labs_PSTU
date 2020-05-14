#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>
#include <vector>
#include "Time.h"


typedef std::priority_queue<Time> queue;
typedef std::vector<Time> vector;


queue make(const int &size);
vector copyQueueToVector(queue que);
queue copyVectorToQueue(vector vec);
void print(const queue &que);
void addElementWithKey(queue &que, const Time &key);
void removeElement(queue &que, const Time &key);
Time findDifference(const queue &que);
void reduceElements(queue &que, const Time &val);


int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		queue que = make(7);
		print(que);
		
		addElementWithKey(que, 135);
		std::cout << "Добавлен элемент 2:15.\n";
		print(que);
		
		removeElement(que, 245);
		std::cout << "Удален элемент 4:05.\n";
		print(que);
		
		Time val = findDifference(que);
		reduceElements(que, 120);
		std::cout << "Из каждого элемента контейнера вычтена разница между минимальным и максимальным элементами.\n";
		print(que);
	}
	catch(Error &e)
	{
		e.what();
	}

	system("pause");
	return 0;
}




queue make(const int &size)
{
	if(size < 0)
		throw Error("Error: queue size must be 0 or higher");

	queue que;
	Time t;
	for(int i = 0; i < size; i++)
	{
		std::cin >> t;
		que.push(t);
	}

	return que;
}

vector copyQueueToVector(queue que)
{
	vector vec;

	while(!que.empty())
	{
		vec.push_back(que.top());
		que.pop();
	}

	return vec;
}

queue copyVectorToQueue(vector vec)
{
	queue que;

	for(int i = 0; i < vec.size(); i++)
		que.push(vec[i]);

	return que;
}

void print(const queue &que)
{
	if(que.empty())
	{
		std::cerr << "Error: queue is empty.\n";
		return;
	}

	vector vec = copyQueueToVector(que);

	std::cout << "Очередь содержит:\n";
	for(int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << "  ";
	std::cout << std::endl;
}

void addElementWithKey(queue &que, const Time &key)
{
	vector vec = copyQueueToVector(que);

	vector::iterator iter = std::find(vec.begin(), vec.end(), key);

	if(iter == vec.end())
	{
		std::cerr << "Error: element not found.\n";
		return;
	}
	else
		que.push(key);
}

void removeElement(queue &que, const Time &key)
{
	if(que.empty())
	{
		std::cerr << "Error: queue is empty.\n";
		return;
	}

	vector vec = copyQueueToVector(que);
	vector::iterator iter = std::remove_if(vec.begin(), vec.end(), std::bind2nd(std::equal_to<Time>(), key));
	vec.erase(iter, vec.end());

	que = copyVectorToQueue(vec);
}

Time findDifference(const queue &que)
{
	if(que.empty())
	{
		std::cerr << "Error: queue is empty.\n";
		return 0;
	}

	vector vec = copyQueueToVector(que);

	return *std::max_element(vec.begin(), vec.end()) - *std::min_element(vec.begin(), vec.end());
}

void reduceElements(queue &que, const Time &val)
{
	if(val == 0)
		return;

	else if(que.empty())
	{
		std::cerr << "Error: queue is empty.\n";
		return;
	}

	vector vec = copyQueueToVector(que);

	std::for_each(vec.begin(), vec.end(), std::bind2nd(std::mem_fun_ref(&Time::operator-), val));

	que = copyVectorToQueue(vec);
}