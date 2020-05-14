#pragma once


struct fraction
{
	int first; //цена товара
	int second; //кол-во единиц данного товара
	bool initialized = false;

	void Init(const int &f, const int &s);
	void Read();
	void Show() const;
	int Cost() const;
};