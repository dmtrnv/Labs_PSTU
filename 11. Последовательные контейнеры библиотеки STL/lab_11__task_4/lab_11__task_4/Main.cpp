#include <iostream>
#include <queue>
#include <vector>
#include "Time.h"


typedef std::priority_queue<Time> queue;
typedef std::vector<Time> vector;


queue make(const int &size);
vector copyQueueToVector(queue que);
queue copyVectorToQueue(vector vec);
void print(const queue &que);
Time find(queue que, const Time &key);
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
		std::cout << "Произведено добавление элемента 2:15.\n";
		print(que);

		removeElement(que, 245);
		std::cout << "Удален элемент 4:05.\n";
		print(que);

		Time val = findDifference(que);
		reduceElements(que, val);
		std::cout << "Из каждого элемента вычтена разница между максимальным и минимальным элементами контейнера.\n";
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

Time find(queue que, const Time &key)
{
	if(que.empty())
		throw Error("Error: element not found.\n"); 

	while(!que.empty())
	{
		if(que.top() == key)
			return que.top();

		que.pop();
	}

	throw Error("Error: element not found.\n");
}

void addElementWithKey(queue &que, const Time &key)
{
	//проверка находится ли нужный элемент в очереди
	Time val = find(que, key);

	//если элемент найден, просто добавляем его в очередь (позицию в очереди выбрать нельзя)
	que.push(val);
}

void removeElement(queue &que, const Time &key)
{
	Time val = find(que, key);

	vector vec = copyQueueToVector(que);
	vector::iterator iter = std::find(vec.begin(), vec.end(), val);
	vec.erase(iter);

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

	return vec[0] - vec[vec.size() - 1];
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

	vector vec;

	while(!que.empty())
	{
		vec.push_back(que.top() - val);
		que.pop();
	}

	que = copyVectorToQueue(vec);
}