#include "Vector.h"
#include "Error.h"
#include <iostream>


int main()
{
	try
	{
		Vector b(9);
		std::cin >> b;
		std::cout << b;
		std::cout << b[4] << std::endl;

		b++;
		std::cout << b;

		++b; //генерируется исключительная ситуация
	}
	catch(Error &e)
	{
		e.what();
	}

	system("pause");
	return 0;
}