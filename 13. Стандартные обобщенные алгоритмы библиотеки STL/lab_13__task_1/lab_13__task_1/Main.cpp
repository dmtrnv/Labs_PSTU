#include <iostream>
#include <deque>
#include <functional>
#include <algorithm>
#include "Time.h"
#include "Error.h"


typedef std::deque<Time> deque;


struct equalTime : std::binary_function<Time, Time, bool>
{
	bool operator()(const Time &t1, const Time &t2) const
	{
		return t1 == t2;
	}
};

//sort from large to samll
struct sortTimeFLTS : std::binary_function<Time, Time, bool>
{
	bool operator()(const Time &elem1, const Time &elem2) const
	{
		return elem1 > elem2;
	}
};


deque make(const int &size);
void print(const deque &deq);
void addElementToPosition(deque &deq, const Time &key, const int &pos);
void removeElement(deque &deq, const Time &key);
Time findDifference(const deque &deq);
void reduceElements(deque &deq, const Time &val);


int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		deque deq = {210, 135, 250, 200, 110, 325, 155, 255, 310, 225};
		print(deq);
		
		addElementToPosition(deq, 200, 10);
		std::cout << "ƒобавлен элемент 3:20 на 10 позицию.\n";
		print(deq);

		removeElement(deq, 155);
		std::cout << "”дален элемент 2:35.\n";
		print(deq);

		Time val = findDifference(deq);
		reduceElements(deq, val);
		std::cout << "»з каждого элемента контейнера вычтена разница между минимальным и максимальным элементами.\n";
		print(deq);

		std::sort(deq.begin(), deq.end(), sortTimeFLTS());
		std::cout << "Ёлементы контейнера отсортированы в пор¤дке убывани¤.\n";
		print(deq);
	}
	catch(Error &e)
	{
		e.what();
	}

	system("pause");
	return 0;
}


deque make(const int &size)
{
	if(size < 0)
		throw Error("Error: deque size must be 0 or higher");

	deque deq;
	Time t;
	for(int i = 0; i < size; i++)
	{
		std::cin >> t;
		deq.push_back(t);
	}

	return deq;
}

void print(const deque &deq)
{
	if(deq.empty())
	{
		std::cerr << "Error: deque is empty.\n";
		return;
	}

	std::cout << "ќчередь содержит:\n";
	for(int i = 0; i < deq.size(); i++)
		std::cout << deq[i] << "  ";
	std::cout << std::endl;
}

void addElementToPosition(deque &deq, const Time &key, const int &pos)
{
	if(pos <= 0 || pos > deq.size() + 1)
	{
		std::cerr << "Error: invalid position value. It must be in the range 1-" << deq.size() + 1 << ".\n";
		return;
	}

	deque::iterator iterKey = std::find(deq.begin(), deq.end(), key);
	
	if(iterKey == deq.end())
	{
		std::cerr << "Error: element not found.\n";
		return;
	}
	else
	{
		deque::iterator iterPos = deq.begin() + (pos - 1);
		deq.insert(iterPos, *iterKey);
	}
}

void removeElement(deque &deq, const Time &key)
{
	if(deq.empty())
	{	
		std::cerr << "Error: deque is empty.\n";
		return;
	}
	
	deque::iterator iter = std::remove_if(deq.begin(), deq.end(), std::bind2nd(equalTime(), key));
	deq.erase(iter, deq.end()); 
}

Time findDifference(const deque &deq)
{
	if(deq.empty())
	{
		std::cerr << "Error: deque is empty.\n";
		return 0;
	}

	Time min = *(std::min_element(deq.begin(), deq.end()));
	Time max = *(std::max_element(deq.begin(), deq.end()));

	return (max - min);
}

void reduceElements(deque &deq, const Time &val)
{
	if(val == 0)
		return;

	else if(deq.empty())
	{
		std::cerr << "Error: deque is empty.\n";
		return;
	}

	std::for_each(deq.begin(), deq.end(), [val](Time &t)
	{
		t = t - val;
	});
}	