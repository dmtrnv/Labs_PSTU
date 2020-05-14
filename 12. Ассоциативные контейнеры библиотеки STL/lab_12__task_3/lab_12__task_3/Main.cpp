#include <iostream>
#include <set>
#include "Error.h"
#include "Time.h"
#include "Vector.h"


int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		Vector<Time> vec(7);
		vec.print();

		vec.addElement(215);
		std::cout << "Добавлен элемент 3:35.\n";
		vec.print();

		vec.removeElement(318);
		std::cout << "Удален элемент 5:18.\n";
		vec.print();

		Time val = vec.findDifference();
		vec.reduceElements(val);
		std::cout << "Из каждого элемента контейнера вычтена разница между минимальным и максимальным элементами.\n";
		vec.print();
	}
	catch(Error &e)
	{
		e.what();
	}

	system("pause");
	return 0;
}