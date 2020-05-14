#include "Pair.h"
#include "Rightangled.h"
#include <iostream>


void f1(Pair &p)
{
	p.setFirst(3);
	std::cout << p;
}

Pair f2()
{
	Rightangled r(25, 19);
	return r;
}


int main()
{
	setlocale(LC_ALL, "rus");

	//Работа с классом Pair
	Pair A;
	std::cin >> A;
	std::cout << "Объект А:\n" << A;

	Pair B(11, 17);
	std::cout << "Объект B:\n" << B;

	A = B;
	std::cout << "Объект A:\n" << A;

	//Работа с классом Rightangled
	Rightangled C;
	std::cin >> C;
	std::cout << "Объект C:\n" << C;
	std::cout << "C.hypotenuse() = " << C.hypotenuse() << std::endl;

	//Принцип подстановки
	f1(C);
	A = f2();
	std::cout << A;

	system("pause");
	return 0;
}