#include <Windows.h>
#include "Student.h"
#include "Work_with_file.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		std::cout << "\t\tМеню\n"
				  << "1. Распечатать список доступных групп\n"
				  << "2. Создасть список группы\n"
				  << "3. Распечатать список студентов группы\n"
				  << "4. Добавить данные о студенте в начало списка\n"
			      << "5. Добавить данные о студенте в конец списка\n"
				  << "6. Добавить данные о студенте в список на указанную позицию\n"
				  << "7. Удалить данные о студенте из списка группы\n"
				  << "8. Отменить последнюю операцию удаления\n"
				  << "9. Изменить данные о студенте\n"
				  << "10. Создать общий список студентов, отсортированный по алфавиту\n"
				  << "11. Создать общий список студентов, отсортированный по убыванию номеров групп\n"
				  << "0. Выйти\n\n";

		int n;

		do
		{
			std::cout << "Выберите действие: ";
			std::cin >> n;
			while(std::cin.fail() || n < 0 || n > 11)
			{
				if(std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(100, '\n');
					std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
					std::cin >> n;
				}
				else
				{
					std::cerr << "Ошибка: введен неверный номер, диапазон доступных номеров: 0-11. Попробуйте снова: ";
					std::cin >> n;
				}
			}
			std::cin.get();

			switch(n)
			{
				case 1:
						viewGroupList();
						std::cout << std::endl;
						break;
				case 2:
						makeFile();
						std::cout << std::endl;
						break;
				case 3: 
						printFileContent();
						std::cout << std::endl;
						break;
				case 4:
						addElementToFileBegin();
						std::cout << std::endl;
						break;
				case 5:
						addElementToFileEnd();
						std::cout << std::endl;
						break;
				case 6:
						addElementToFileAtPos();
						std::cout << std::endl;
						break;
				case 7:
						removeElementFromFile();
						std::cout << std::endl;
						break;
				case 8:
						doBackup();
						std::cout << std::endl;
						break;
				case 9:
						changeElement();
						std::cout << std::endl;
						break;
				case 10:
						makeSharedFileSortedByName();
						std::cout << std::endl;
						break;
				case 11:
						makeSharedFileSortedByGroup();
						std::cout << std::endl;
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






