#pragma once
#include "Pair.h"
#include <cmath>

class Rightangled : public Pair
{
public:
	Rightangled();
	Rightangled(const int &f, const int &s);
	Rightangled(const Rightangled &r);
	~Rightangled();
	double hypotenuse() const;	
	Rightangled& operator=(const Rightangled &r);
	friend std::istream& operator>>(std::istream &in, Rightangled &r);
	friend std::ostream& operator<<(std::ostream &out, const Rightangled &r);
};
