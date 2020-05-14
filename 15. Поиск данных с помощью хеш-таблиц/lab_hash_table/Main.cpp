#include <iostream>
#include <vector>
#include <string>
#include "HashTable.h"
#include "MenuFunctions.h"


int main()
{
	try
	{
		std::cout << "\t\tMenu\n"
			<< "1. Create and fill the table\n"
			<< "2. Add element in the table\n"
			<< "3. Remove element from the table\n"
			<< "4. Find element in the table\n"
			<< "5. Change data of table's element\n"
			<< "6. Print the content of the table\n"
			<< "7. Show number of collisions in the table\n"
			<< "0. Exit\n\n";

		HashTable mainTable;
		int n;

		do
		{
			std::cout << "Select an action: ";
			std::cin >> n;
			while(std::cin.fail() || n < 0 || n > 7)
			{
				if(std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(100, '\n');
					std::cerr << "Error: invalid input. Try again: ";
					std::cin >> n;
				}
				else
				{
					std::cerr << "Error: incorrect number, the range of allowed numbers: 0-7. Try again: ";
					std::cin >> n;
				}
			}
			std::cin.get();

			switch(n)
			{
				case 1:
						mainTable = makeAndFill();
						break;
				case 2:
						add(mainTable);
						break;
				case 3:
						remove(mainTable);
						break;
				case 4:
						find(mainTable);
						break;
				case 5:
						changeData(mainTable);
						break;
				case 6:
						mainTable.print();
						break;
				case 7:
						showNumberOfCollisions(mainTable);
						break;
				default:
						break;
			}
		} while(n != 0);

	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	system("pause");
	return 0;
}


