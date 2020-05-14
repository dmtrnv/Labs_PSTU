#include "Time.h"
#include "FileWork.h"
#include "Error.h"
#include <iostream>


int main()
{
	try
	{
		Time val;
		int n = 0;
		char filename[30] = "";

		do
		{
			std::cout << "\n\tMenu\n\n"
					  << "1. Make file\n"
					  << "2. Print File\n"
					  << "3. Remove desired values from file\n"
					  << "4. Reduce desired values in file\n"
					  << "5. Add entries to the file after the desired value\n"
					  << "0. Exit\n\n"
					  << "Select an action: ";

			std::cin >> n;

			switch(n)
			{
				case 1:
						std::cout << "Enter the filename: ";
						std::cin >> filename;
						makeFile(filename);
						break;
				case 2:
						std::cout << "Enter the filename: ";
						std::cin >> filename;
						std::cout << std::endl;
						printFile(filename);
						break;
				case 3:
						std::cout << "Enter the filename: ";
						std::cin >> filename;
						std::cout << "Enter the value:\n";
						std::cin >> val;
						removeDesiredValues(filename, val);
						break;
				case 4:
						std::cout << "Enter the filename: ";
						std::cin >> filename;
						std::cout << "Enter the value:\n";
						std::cin >> val;
						reduceDesiredValues(filename, val);
						break;
				case 5:
						std::cout << "Enter the filename: ";
						std::cin >> filename;
						std::cout << "Enter the specified element:\n";
						std::cin >> val;
						addRecordsAfterValue(filename, val);
						break;
			}

		} while(n != 0);
	}
	catch(Error &e)
	{
		e.what();
	}

	system("pause");
	return 0;
}