#include "HashTable.h"


HashTable::HashTable(const int &_size)
{
	if(_size <= 0)
		throw std::invalid_argument("Error: _size <= 0.\n");

	capacity = _size;
	currentSize = 0;
	table = new data[capacity];

	data tmp = {"empty", 0, 0};

	for(int i = 0; i < capacity; i++)
		table[i] = tmp;
}

HashTable::HashTable(const HashTable &_hashTable)
{
	if(_hashTable.table == nullptr)
		throw std::invalid_argument("Error: _hashTable.table is nullptr.\n");

	capacity = _hashTable.capacity;
	currentSize = _hashTable.currentSize;
	table = new data[capacity];

	for(int i = 0; i < capacity; i++)
		table[i] = _hashTable.table[i];
}

HashTable::~HashTable()
{
	if(table != nullptr)
	{
		delete [] table;
		table = nullptr;
	}
}
		
HashTable& HashTable::operator=(const HashTable &_hashTable) 
{
	if(_hashTable.table == nullptr)
		throw std::invalid_argument("Error: _hashTable.table is nullptr.\n");

	if(this == &_hashTable)
		return *this;

	if(table != nullptr)
	{
		delete [] table;
		table = nullptr;
	}

	capacity = _hashTable.capacity;
	currentSize = _hashTable.currentSize;
	table = new data[capacity];

	for(int i = 0; i < capacity; i++)
		table[i] = _hashTable.table[i];

	return *this;
}

int HashTable::hash(const std::string &key)
{
	int asciiSum = 0;

	for(int i = 0, p = 1; i < key.size(); i++, p ++)
		asciiSum += key[i] * p;

	return asciiSum % capacity;
}

void HashTable::add(const data &_data)
{
	if(this->full())
	{
		std::cerr << "Error: table is full.\n";
		return;
	}

	int hashKey = hash(_data.name);

	//"-1" means element is deleted
	if(table[hashKey].name == "empty" || table[hashKey].name == "-1") 
	{
		table[hashKey] = _data;
		currentSize++;
		return;
	}

	while(table[hashKey].name != "empty" || table[hashKey].name != "-1")
	{
		//go to the next element
		hashKey++;
		//if end of the table reached, go to the beginning
		if(hashKey == capacity)
			hashKey = 0;
				
		if(table[hashKey].name == "empty" || table[hashKey].name == "-1")
		{
			table[hashKey] = _data;
			currentSize++;
			return;
		}
	}
}

void HashTable::remove(const std::string &_name)
{
	if(this->empty())
	{
		std::cerr << "Error: table is empty.\n";
		return;
	}

	int hashKey = hash(_name);

	if(table[hashKey].name == _name)
	{
		table[hashKey].name = "-1";
		table[hashKey].accountNumber = 0;
		table[hashKey].sum = 0;
		currentSize--;
		return;
	}

	int checkedElements = 1;
	while(table[hashKey].name != "empty")
	{
		//go to the next element
		hashKey++;
		//if end of the table reached, go to the beginning
		if(hashKey == capacity)
			hashKey = 0;

		if(table[hashKey].name == _name)
		{
			table[hashKey].name = "-1";
			table[hashKey].accountNumber = 0;
			table[hashKey].sum = 0;
			currentSize--;
			return;
		}

		checkedElements++;
		//if all table elements are checked
		if(checkedElements == capacity)
		{
			std::cerr << "Error: element not found.\n";
			return;
		}
	}

	std::cerr << "Error: element not found.\n";
}

data HashTable::find(const std::string &_name)
{
	if(this->empty())
	{
		std::cerr << "Error: table is empty.\n";
		return {"empty", 0, 0};
	}

	int hashKey = hash(_name);

	if(table[hashKey].name == _name)
		return table[hashKey];

	int checkedElements = 1;
	while(table[hashKey].name != "empty")
	{
		//go to the next element
		hashKey++;
		//if end of the table reached, go to the beginning
		if(hashKey == capacity)
			hashKey = 0;

		if(table[hashKey].name == _name)
			return table[hashKey];

		checkedElements++;
		//if all table elements are checked
		if(checkedElements == capacity)
		{
			std::cerr << "Error: element not found.\n";
			return {"empty", 0, 0};
		}
	}

	std::cerr << "Error: element not found.\n";
	return {"empty", 0, 0};
}

void HashTable::changeData(const std::string &_name,  //key
						   const int &_accountNumber, //new account number
						   const double &_sum)		  //new sum
{
	if(this->empty())
	{
		std::cerr << "Error: table is empty.\n";
		return;
	}

	int hashKey = hash(_name);

	if(table[hashKey].name == _name)
	{
		table[hashKey].accountNumber = _accountNumber;
		table[hashKey].sum = _sum;
		return;
	}

	int checkedElements = 0;
	while(table[hashKey].name != "empty")
	{
		//go to the next element
		hashKey++;
		//if end of the table reached, go to the beginning
		if(hashKey == capacity)
			hashKey = 0;

		if(table[hashKey].name == _name)
		{
			table[hashKey].accountNumber = _accountNumber;
			table[hashKey].sum = _sum;
			return;
		}

		checkedElements++;
		//if all table elemnts are checked
		if(checkedElements == capacity)
		{
			std::cerr << "Error: element not found.\n";
			return;
		}
	}

	std::cerr << "Error: element not found.\n";
}

int HashTable::getCollisionNumber()
{
	int count = 0;

	for(int i = 0; i < capacity; i++)
	{
		if(table[i].name == "empty")
			continue;

		if(hash(table[i].name) != i)
			count++;
	}

	return count;
}

void HashTable::print()
{
	std::cout << std::setw(8) << "Hash key" << std::setw(31) << "Name" 
			  << std::setw(31) << "Account number" << std::setw(14) << "Sum\n";

	for(int i = 0; i < capacity; i++)
	{
		if(table[i].name == "empty" || table[i].name == "-1")
			std::cout << std::setw(8) << "missing" << std::setw(37) << table[i].name
					  << std::setw(20) << table[i].accountNumber << std::setw(20) 
					  << std::fixed << std::setprecision(2) << table[i].sum << std::endl;
		else
			std::cout << std::setw(5) << hash(table[i].name) << std::setw(40) << table[i].name
					  << std::setw(20) << table[i].accountNumber << std::setw(20) 
					  << std::fixed << std::setprecision(2) << table[i].sum << std::endl;
	}
}