#pragma once
#include "MenuFunctions.h"
#include "HashTable.h"


HashTable makeAndFill()
{
	std::cout << "Enter table size: ";
	int size;
	std::cin >> size;
	while(std::cin.fail() || size <= 0)
	{
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cerr << "Error: invalid input. Try again: ";
			std::cin >> size;
		}
		else
		{
			std::cerr << "Error: incorrect table size. Try again: ";
			std::cin >> size;
		}
	}
	std::cin.get();

	std::vector<std::string> names = { "Oliver", "Jack", "Harry", "Jacob", "Charlie", 
									   "Thomas", "George", "Oscar", "James", "William" };

	std::vector<std::string> surnames = { "Smith", "Jones", "Taylor", "Davies", "Evans",
										  "Johnson", "Roberts", "Robinson", "Thompson", "Green" }; 

	std::vector<std::string> patronymics = { "Adamson", "Barson", "Hobson", "Wilson", "Fennel",
											 "Coleson", "Jackson", "Iveson", "Tennyson", "Garrison" };

	std::srand(std::time(nullptr));
	HashTable tmp(size);
	
	for(int i = 0; i < tmp.size(); i++)
		tmp.add( { names[std::rand() % names.size()] + ' ' 
				   + patronymics[std::rand() % patronymics.size()]
				   + ' ' + surnames[std::rand() % surnames.size()],
				   std::rand() % 1000000,
				   (double) std::rand() / 1.315} );

	return tmp;
}

void add(HashTable &table)
{
	data tmp;
	
	std::cout << "Enter name: ";
	std::getline(std::cin, tmp.name);
	
	std::cout << "Enter account number: ";
	std::cin >> tmp.accountNumber;
	while(std::cin.fail() || tmp.accountNumber < 0)
	{
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cerr << "Error: invalid input. Try again: ";
			std::cin >> tmp.accountNumber;
		}
		else
		{
			std::cerr << "Error: incorrect number. Try again: ";
			std::cin >> tmp.accountNumber;
		}
	}
	std::cin.get();

	std::cout << "Enter sum: ";
	std::cin >> tmp.sum;
	while(std::cin.fail())
	{
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cerr << "Error: invalid input. Try again: ";
			std::cin >> tmp.sum;
		}
	}
	std::cin.get();

	table.add(tmp);
}

void remove(HashTable &table)
{
	std::cout << "Enter person name: ";
	std::string name;
	std::getline(std::cin, name);

	table.remove(name);
}

void find(HashTable &table)
{
	std::cout << "Enter person name: ";
	std::string name;
	std::getline(std::cin, name);

	data tmp = table.find(name);

	if(tmp.name != "empty")
		std::cout << "The item is found: \nName: " << tmp.name
				  << "\nAccount number: " << tmp.accountNumber
				  << "\nSum: " << tmp.sum << std::endl;
	else
		return;
}

void changeData(HashTable &table)
{
	std::cout << "Enter the name of the person whose data you want to change: ";
	std::string name;
	std::getline(std::cin, name);

	data tmp = table.find(name);

	if(tmp.name != "empty")
	{
		std::cout << "Enter new account number: ";
		int newNum;
		std::cin >> newNum;
		while(std::cin.fail() || newNum < 0)
		{
			if(std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cerr << "Error: invalid input. Try again: ";
				std::cin >> newNum;
			}
			else
			{
				std::cerr << "Error: incorrect number. Try again: ";
				std::cin >> newNum;
			}
		}
		std::cin.get();

		std::cout << "Enter new sum: ";
		double newSum;
		std::cin >> newSum;
		while(std::cin.fail())
		{
			if(std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cerr << "Error: invalid input. Try again: ";
				std::cin >> newSum;
			}
		}
		std::cin.get();

		table.changeData(name, newNum, newSum);
	}
	else
		return;
}

void showNumberOfCollisions(HashTable &table)
{
	int count = table.getCollisionNumber();

	std::cout << "There is " << count << " collisions in the table.\n";
}