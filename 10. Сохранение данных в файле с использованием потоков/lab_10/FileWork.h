#pragma once
#include "Time.h"
#include "Error.h"
#include <iostream>


void makeFile(const char *filename)
{
	std::fstream fout(filename, std::ios::out | std::ios::trunc);

	if(!fout.is_open())
		throw Error("Error: could not open file.\n");

	std::cout << "Enter the number of objects to write to the file: ";
	int n;
	std::cin >> n;

	Time t;
	for(int i = 0; i < n; i++)
	{
		std::cin >> t;
		fout << t;
	}

	fout.close();
}

void printFile(const char *filename)
{
	std::fstream fin(filename, std::ios::in);

	if(!fin.is_open())
		throw Error("Error: could not open file.\n");

	bool empty = true;
	Time t;
	while(fin >> t)
	{
		std::cout << t << std::endl;
		empty = false;
	}

	fin.close();
	if(empty)
		std::cout << "File " << filename << " is empty.\n";
}

void removeDesiredValues(const char *filename, const Time &val)
{
	std::fstream fin(filename, std::ios::in);
	std::fstream fout("temp.txt", std::ios::out | std::ios::trunc);

	if(!fout.is_open() || !fin.is_open())
		throw Error("Error: could not open file.\n");

	bool found = false;
	Time t;
	while(fin >> t)
	{
		if(t == val)
		{
			found = true;
			continue;
		}

		fout << t;
	}

	fin.close();
	fout.close();

	if(std::remove(filename))
		throw Error("Error: failed to remove the file.\n");

	if(std::rename("temp.txt", filename))
		throw Error("Error: failed to rename the file.\n");

	if(!found)
		std::cout << "\nValue " << val << " not found.\n";
}

void reduceDesiredValues(const char *filename, const Time &val)
{
	std::fstream fin(filename, std::ios::in);
	std::fstream fout("temp.txt", std::ios::out | std::ios::trunc);

	if(!fout.is_open() || !fin.is_open())
		throw Error("Error: could not open file.\n");

	bool found = false;
	Time t;
	while(fin >> t)
	{
		if(t == val)
		{
			t.subtractSec(90);
			found = true;
		}

		fout << t;
	}

	fin.close();
	fout.close();

	if(std::remove(filename))
		throw Error("Error: failed to remove the file.\n");

	if(std::rename("temp.txt", filename))
		throw Error("Error: failed to rename the file.\n");

	if(!found)
		std::cout << "\nValue " << val << " not found.\n";
}

void addRecordsAfterValue(const char *filename, const Time &val)
{
	std::fstream fin(filename, std::ios::in);
	std::fstream fout("temp.txt", std::ios::out | std::ios::trunc);

	if(!fout.is_open() || !fin.is_open())
		throw Error("Error: could not open file.\n");

	bool found = false;
	Time t;
	while(fin >> t)
	{
		if(t == val)
		{
			fout << t;

			std::cout << "Enter the number of objects to add after the specified element: ";
			int n;
			std::cin >> n;

			for(int i = 0; i < n; i++)
			{
				std::cin >> t;
				fout << t;
			}

			found = true;
			continue;
		}

		fout << t;
	}

	fin.close();
	fout.close();

	if(std::remove(filename))
		throw Error("Error: failed to remove the file.\n");

	if(std::rename("temp.txt", filename))
		throw Error("Error: failed to rename the file.\n");

	if(!found)
		std::cout << "Value " << val << " not found.\n";
}
