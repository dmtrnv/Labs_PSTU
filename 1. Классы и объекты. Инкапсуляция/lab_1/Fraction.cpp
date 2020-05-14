#include "Fraction.h"
#include <iostream>

// Выбрал тип int, т.к. unsigned int то же нужно проверять на отрицательность
// (при передаче отрицательного значения выводятся значения с конца) 

void fraction::Init(const int &f, const int &s)
{
	if(f < 0 || s < 0)
	{
		std::cerr << "Ошибка: цена и количество товаров не могут быть отрицательными. Заверешние программы.";
		exit(EXIT_FAILURE);
	}

	first = f;
	second = s;
	initialized = true;
}

void fraction::Read()
{
	std::cout << "Введите цену товара: ";
	std::cin >> first;
	while(std::cin.fail() || first < 0)
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
			std::cin >> first;
		}
		else
		{
			std::cerr << "Ошибка: цена товара не может быть отрицательной. Попробуйте снова: ";
			std::cin >> first;
		}

	std::cout << "Введите количество единиц данного товара: ";
	std::cin >> second;
	while(std::cin.fail() || second < 0)
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
			std::cin >> second;
		}
		else
		{
			std::cerr << "Ошибка: количество товаров не может быть отрицательным. Попробуйте снова: ";
			std::cin >> second;
		}

	initialized = true;
}

void fraction::Show() const
{
	if(!initialized)
	{
		std::cerr << "Ошибка: данные не определены\n";
		return;
	}

	std::cout << "Цена товара: " << first << std::endl;
	std::cout << "Количество единиц данного товара: " << second << std::endl;
}

int fraction::Cost() const
{
	if(!initialized)
	{
		std::cerr << "Ошибка: данные не определены\n";
		return -1;
	}

	return first * second;
}