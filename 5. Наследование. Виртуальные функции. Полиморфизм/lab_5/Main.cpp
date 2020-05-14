#include "Object.h"
#include "Pair.h"
#include "Rightangled.h"
#include "Vector.h"
#include <iostream>


int main()
{
	setlocale(LC_ALL, "rus");

	Vector v(5);

	Pair p;
	std::cin >> p;

	Rightangled r;
	std::cin >> r;

	Object *obj = &p;
	v.add(obj);
	obj = &r;
	v.add(obj);

	std::cout << v;

	system("pause");
	return 0;
}