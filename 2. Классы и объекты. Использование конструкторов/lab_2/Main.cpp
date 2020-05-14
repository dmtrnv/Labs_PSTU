#include "Route.h"
#include <string>
#include <iostream>
#include <windows.h>


Route makeRoute()
{
	std::string departure, arrival;
	float time;

	std::cout << "Введите название пункта отправления: ";
	std::cin >> departure;
	std::cout << "Введите название пункта назначения: ";
	std::cin >> arrival;
	std::cout << "Введите количество времени, проведенного в пути: ";
	std::cin >> time;
	while(std::cin.fail() || time < 0)
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cerr << "Ошибка: был введен некорректный символ. Попробуйте снова: ";
			std::cin >> time;
		}
		else
		{
			std::cerr << "Ошибка: время, проведенное в пути не может быть отрицательным. Попробуйте снова: ";
			std::cin >> time;
		}

	Route r(departure, arrival, time);
	return r;
}

void printRoute(Route r)
{
	r.show();
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Route r1;
	r1.show();

	Route r2("Москва", "Пермь", 2.25);
	r2.show();

	Route r3 = r2;
	r3.setDeparturePoint("Пермь");
	r3.setArrivalPoint("Санкт-Петербург");
	r3.setTravelTime(2.10);
	printRoute(r3);

	r1 = makeRoute();
	r1.show();
	
	system("pause");
	return 0;
}