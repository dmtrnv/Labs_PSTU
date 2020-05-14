#include "Vector.h"
#include "Time.h"
#include <iostream>


int main()
{
	Vector<int> A(3);
	std::cin >> A;
	std::cout << "Vector A contains:\n" << A;
	A = A + 19;
	std::cout << "Vector A contains:\n" << A;

	Vector<float> B(4, 1);
	std::cout << "Vector B contains:\n" << B;
	std::cin >> B;
	std::cout << "Vector B contains:\n" << B;
	B[3] = 55.71;
	std::cout << "Vector B contains:\n" << B;
	
	Vector<double> C(5);
	std::cin >> C;
	std::cout << "Vector C contains:\n" << C;
	Vector<double> D(5);
	D = C;
	std::cout << "Vector D contains:\n" << D;

	Vector<Time> E(5);
	std::cin >> E;
	std::cout << "Vector E contains:\n" << E;
	
	Vector<Time> F = E;
	std::cout << "Vector F contains:\n" << F;

	F[2] = Time(10, 11);
	std::cout << "Vector F contains:\n" << F;
	//из числа 547 создается объект класса Time
	//т.к. первый операнд является объектом класса Time
	//см. перегруженную шаблонную функцию класса Vector
	E = E + 547; 
	std::cout << "Vector E contains:\n" << E;

	Vector<Time> G(5);
	G = E + F;
	std::cout << "Vector G contains:\n" << G;	
	G[0] = G[3] + 44;
	std::cout << "Vector G contains:\n" << G;

	system("pause");
	return 0;
}