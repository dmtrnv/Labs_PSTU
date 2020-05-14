#pragma once
#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <iomanip>


struct data
{
	std::string name; //key
	int accountNumber;
	double sum;
};


class HashTable
{
	private:
		data *table;
		int capacity;
		int currentSize;
		
	public:
		HashTable(const int &_size = 31);
		HashTable(const HashTable &_hashTable);
		~HashTable();
		HashTable& operator=(const HashTable &_hashTable) ;
		int size() const { return capacity;}
		bool empty() const { return currentSize == 0; }
		bool full() const { return currentSize == capacity; }
		int hash(const std::string &key);
		void add(const data &_data);
		void remove(const std::string &_name);
		data find(const std::string &_name);
		void changeData(const std::string &_name, const int &_accountNumber, const double &_sum);
		int getCollisionNumber();
		void print();
};
