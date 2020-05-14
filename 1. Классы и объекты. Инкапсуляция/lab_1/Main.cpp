#include "Fraction.h"
#include <iostream>


fraction makeFraction(const int &f, const int &s)
{
	fraction fract;
	fract.Init(f, s);

	return fract;
}


int main()
{
	setlocale(LC_ALL, "rus");
	
	fraction A;
	fraction B;
	A.Init(25, 17);
	B.Read();
	A.Show();
	B.Show();
	std::cout << "A.Cost(" << A.first << ", " << A.second << ") = " << A.Cost() << std::endl;
	std::cout << "B.Cost(" << B.first << ", " << B.second << ") = " << B.Cost() << "\n\n";
	
	fraction *X = new fraction;
	X->Init(11, 16);
	X->Show();
	std::cout << "X.Cost(" << X->first << ", " << X->second << ") = " << X->Cost() << "\n\n";
	delete X;

	fraction mas[3];
	for(int i = 0; i < 3; i++)
		mas[i].Read();
	for(int i = 0; i < 3; i++)
		mas[i].Show();
	for(int i = 0; i < 3; i++)
		std::cout << "mas[" << i << "].Cost(" << mas[i].first << ", " << mas[i].second << ") = " << mas[i].Cost() << std::endl;
	std::cout << std::endl;

	fraction *p_mas = new fraction[3];
	for(int i = 0; i < 3; i++)
		p_mas[i].Read();
	for(int i = 0; i < 3; i++)
		p_mas[i].Show();
	for(int i = 0; i < 3; i++)
		std::cout << "p_mas[" << i << "].Cost(" << p_mas[i].first << ", " << p_mas[i].second << ") = " << p_mas[i].Cost() << std::endl;
	std::cout << std::endl;
	delete [] p_mas;

	fraction F = makeFraction(22, 49);
	F.Show();

	system("pause");
	return 0;
}