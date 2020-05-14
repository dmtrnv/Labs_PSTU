#include <iostream>
#include <vector>
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


		Time a(4, 47);
		vec.addElementToPosition(a, 2);
		std::cout << "Произведено добавление элемента 4:47 на 2 позицию.\n";
		vec.print();

		vec.removeElement(135);
		std::cout << "Удален элемент 2:15.\n";
		vec.print();

		Time val = vec.findDifference();
		vec.reduceElements(val);
		std::cout << "Из каждого элемента вычтена разница между максимальным и минимальным элементами контейнера.\n";
		vec.print();
	}
	catch(Error &e)
	{
		e.what();
	}

	system("pause");
	return 0;
}