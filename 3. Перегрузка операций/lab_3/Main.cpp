#include "Time.h"
#include <iostream>


int main()
{
	setlocale(LC_ALL, "rus");

	Time A;
	std::cin >> A;
	Time B(11, 40);
	std::cout << "Время А - " << A << std::endl; 
	std::cout << "Время В - " << B << "\n\n";

	A.addSec(165);
	B.subtractSec(330);
	std::cout << "Время А - " << A << std::endl; 
	std::cout << "Время В - " << B << "\n\n";

	A = B;
	std::cout << "Время А - " << A << std::endl; 
	std::cout << "Время В - " << B << "\n\n";

	system("pause");
	return 0;
}