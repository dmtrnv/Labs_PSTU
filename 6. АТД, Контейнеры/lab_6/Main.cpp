#include "Vector.h"
#include <iostream>


int main()
{
	Vector A(5);
	std::cin >> A;
	std::cout << "Vector A contains:\n" << A;
	A[3] = 111;
	std::cout << "Vector A contains:\n" << A;

	Vector B(5, 19);
	std::cout << "Vector B contains:\n" << B;
	B = A;
	B = B + 55;
	std::cout << "Vector B contains:\n" << B;
	
	Vector C = A + B;
	std::cout << "Vector C contains:\n";
	for(Iterator itC = C.first(); itC != C.last(); ++itC)
		std::cout << *itC << "  ";
	std::cout << std::endl;
	
	Iterator itA = A.first();
	Iterator itB = B.first();
	std::cout << std::boolalpha << (*itA == *itB) << std::endl;

	itA = itB;
	std::cout << std::boolalpha << (*itA == *itB) << std::endl;

	system("pause");
	return 0;
}