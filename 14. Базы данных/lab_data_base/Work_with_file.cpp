#pragma once
#include "Work_with_file.h"


void copyFileContentToList(const std::string &filename, std::list<Student> &_list)
{
	std::fstream fin(filename, std::ios::in);

	if(!fin.is_open())
		throw std::runtime_error("Ошибка: не удалось открыть/создать файл " + filename + ".\n");

	_list.clear();

	Student tmp;
	while(fin >> tmp)
		_list.push_back(tmp);

	fin.close();
}

void copyListContentToFile(const std::string &filename, std::list<Student> &_list)
{
	std::cout << "Сохранить изменения? (да/нет) : ";
	std::string answer;
	std::getline(std::cin, answer);

	if(answer == "Да" || answer == "да")
	{ }
	else if(answer == "Нет" || answer == "нет")
		return;
	else
		while(answer != "Да" && answer != "да" && answer != "Нет" && answer != "нет")
		{
			std::cerr << "Ошибка: некорректный ответ, следует ответить \"да\" или \"нет\". Попробуйте снова: ";
			std::getline(std::cin, answer);

			if(answer == "Да" || answer == "да")
			{ }
			else if(answer == "Нет" || answer == "нет")
				return;
		}

	std::fstream fout(filename, std::ios::out | std::ios::trunc);

	if(!fout.is_open())
		throw std::runtime_error("Ошибка: не удалось открыть файл " + filename + ".\n");

	for(Student &student : _list)
		fout << student;

	fout.close();
}

void copyListContentToFileWithoutSave(const std::string &filename, std::list<Student> &_list)
{
	std::fstream fout(filename, std::ios::out | std::ios::trunc);

	if(!fout.is_open())
		throw std::runtime_error("Ошибка: не удалось открыть файл " + filename + ".\n");

	for(Student &student : _list)
		fout << student;

	fout.close();
}

void viewGroupList()
{
	std::fstream fin("group_names.txt", std::ios::in);

	if(!fin.is_open())
		throw std::runtime_error("Ошибка: не удалось открыть файл group_names.txt.\n");

	std::string tmp;

	while(fin >> tmp)
		std::cout << tmp << "  ";
	std::cout << std::endl;

	fin.close();
}

void makeFile()
{
	//ввод данных
	std::cout << "Введите название группы: ";
	std::string groupName;
	std::getline(std::cin, groupName);

	//запись названия группы в общий файл
	std::fstream f("group_names.txt", std::ios::out | std::ios::app);
	
	if(!f.is_open())
		throw std::runtime_error("Ошибка: не удалось открыть файл group_names.txt.\n");

	f << groupName << std::endl;
	f.close();

	//продолжение ввода данных
	std::cout << "Введите количество студентов: ";
	int num;
	std::cin >> num;
	while(std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
		std::cin >> num;
	}
	std::cin.get(); // удаление из потока символа новой строки для корректной работы getline()

	std::string filename = groupName + ".txt";
	std::list<Student> list;
	Student tmp(groupName);
	std::string studentName;

	for(int i = 0; i < num; i++)
	{
		std::cout << "Введите Ф.И.О. студента: ";
		std::getline(std::cin, studentName);

		tmp.setName(studentName);
		list.push_back(tmp);
	}

	copyListContentToFile(filename, list);
}

void printFileContent()
{
	std::cout << "Введите название группы: ";
	std::string groupName;
	std::getline(std::cin, groupName);

	std::string filename = groupName + ".txt";
	std::list<Student> list;
	copyFileContentToList(filename, list);

	if(list.empty())
	{
		std::cout << "Список пуст.\n";
		return;
	}

	std::cout << "Список студентов группы " << groupName << ":\n";
	for(const Student &student : list)
		if(student.getName().substr(student.getName().size() - 7, 7) == "УДАЛЕНО")
			continue;
		else
			std::cout << student;
}

void addElementToFileBegin()
{
	Student tmp;
	std::cin >> tmp;

	std::string filename = tmp.getGroup() + ".txt";
	std::list<Student> list;
	
	copyFileContentToList(filename, list);
	list.push_front(tmp);

	copyListContentToFile(filename, list);
}

void addElementToFileEnd()
{
	Student tmp;
	std::cin >> tmp;

	std::string filename = tmp.getGroup() + ".txt";
	std::list<Student> list;
	
	copyFileContentToList(filename, list);
	list.push_back(tmp);

	copyListContentToFile(filename, list);
}

void addElementToFileAtPos()
{
	Student tmp;
	std::cin >> tmp;

	std::string filename = tmp.getGroup() + ".txt";
	std::list<Student> list;

	copyFileContentToList(filename, list);

	std::cout << "Укажите номер позиции, на которую следует записать студента: ";
	int pos;
	std::cin >> pos;
	while(std::cin.fail() || pos < 1 || pos > list.size() + 1)
	{
		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
			std::cin >> pos;
		}
		else
		{
			std::cerr << "Ошибка: указанная вами позиция недоступна, диапазон позиций: 1-" 
					  << list.size() + 1 << ". Попробуйте снова: ";
			std::cin >> pos;
		}
	}
	std::cin.get();

	std::list<Student>::iterator iterPos = list.begin();
	std::advance(iterPos, pos - 1);

	list.emplace(iterPos, tmp);

	copyListContentToFile(filename, list);
}

void makeBackupFile(std::list<Student> &_list)
{
	std::fstream fout("backup.txt", std::ios::out | std::ios::trunc);

	if(!fout.is_open())
		throw std::runtime_error("Ошибка: не удалось открыть файл backup.txt.\n");

	for(Student &student : _list)
		fout << student;

	fout.close();
}

void doBackup()
{
	std::list<Student> list;

	copyFileContentToList("backup.txt", list);
	copyListContentToFile(list.front().getGroup() + ".txt", list);
}

void removeElementFromFile()
{
	//ввод данных
	std::cout << "Введите название группы: ";
	std::string groupName;
	std::getline(std::cin, groupName);

	std::string filename = groupName + ".txt";
	std::list<Student> list;
	copyFileContentToList(filename, list);

	if(list.empty())
	{
		std::cout << "Список пуст.\n";
		return;
	}

	//создание резервной копии для отмены операции удаления
	makeBackupFile(list);

	//ввод данных
	std::cout << "Введите Ф.И.О. студента: ";
	std::string studentName;
	std::getline(std::cin, studentName);

	Student tmp(groupName, studentName);
	std::list<Student>::iterator iterFind = std::find(list.begin(), list.end(), tmp);
	
	//поиск указанного элемента
	if(iterFind == list.end())
	{
		std::cout << "Элемент не найден.\n";
		return;
	}
	else
	{
		iterFind->setName(iterFind->getName() + " УДАЛЕНО");
	}

	//подсчет кол-ва "удаленных" элементов
	std::vector<std::list<Student>::iterator> vec;
	std::list<Student>::iterator iterPos;
	
	for(iterPos = list.begin(); iterPos != list.end(); iterPos++)
		if(iterPos->getName().substr(iterPos->getName().size() - 7, 7) == "УДАЛЕНО")
			vec.push_back(iterPos);
	
	//удаление элементов из списка
	if(vec.size() > list.size() / 2)
		for(auto &iter : vec)
			list.erase(iter);
		
	copyListContentToFile(filename, list);
}

void changeElement()
{
	//ввод данных
	std::cout << "Введите название группы: ";
	std::string groupName;
	std::getline(std::cin, groupName);

	std::cout << "Введите Ф.И.О. студента: ";
	std::string studentName;
	std::getline(std::cin, studentName);

	//копирвоание содержимого файла в список
	std::string filename = groupName + ".txt";
	std::fstream fin(filename, std::ios::in);

	if(!fin.is_open())
	{
		std::cout << "Элемент не найден.\n";
		return;
	}

	std::list<Student> list;
	Student tmp;

	while(fin >> tmp)
		list.push_back(tmp);

	fin.close();

	//поиск указанного элемента
	tmp.setGroup(groupName);
	tmp.setName(studentName);
	std::list<Student>::iterator iterFind = std::find(list.begin(), list.end(), tmp);
	
	if(iterFind == list.end())
	{
		std::cout << "Элемент не найден.\n";
		return;
	}
	else
	{
		std::cout << "Введите новое название группы: ";
		std::string newGroupName;
		std::getline(std::cin, newGroupName);

		std::cout << "Введите новые Ф.И.О. студента: ";
		std::string newStudentName;
		std::getline(std::cin, newStudentName);

		tmp.setGroup(newGroupName);
		tmp.setName(newStudentName);
	}

	//если название группы изменилось
	if(tmp.getGroup() != groupName)
	{
		std::string newFilename = tmp.getGroup() + ".txt";

		std::fstream newFin(newFilename, std::ios::in);

		//если файла не существует, создаем новый
		if(!newFin.is_open())
		{
			std::fstream newFout(newFilename, std::ios::out | std::ios::trunc);
			newFout << tmp;

			newFout.close();
		}
		else
		{
			std::list<Student> newList;
			Student stud;

			while(newFin >> stud)
				newList.push_back(stud);

			newFin.close();

			newList.push_back(tmp);
			copyListContentToFileWithoutSave(newFilename, newList);
		}

		list.erase(iterFind);
		copyListContentToFile(filename, list);
	}
	//если данные не были изменены
	else if(tmp.getGroup() == groupName && tmp.getName() == studentName)
	{ }
	else
	{
		iterFind->setName(tmp.getName());
		copyListContentToFile(filename, list);
	}
}

void makeSharedFileSortedByName()
{
	//создание списка с названиями групп
	std::fstream f;
	f.open("group_names.txt", std::ios::in);
	std::list<std::string> listNames;
	std::string tmp;

	if(!f.is_open())
		throw std::runtime_error("Ошибка: не удалось открыть файл group_names.txt.\n");

	while(f >> tmp)
		listNames.push_back(tmp);

	f.close();

	//создание общего списка студентов
	std::list<Student> listMain;
	std::list<std::string>::iterator iter;

	for(iter = listNames.begin(); iter != listNames.end(); iter++)
	{
		f.open(*iter + ".txt", std::ios::in);

		if(!f.is_open())
			throw std::runtime_error("Ошибка: не удалось открыть/создать файл " + *iter + ".txt" + ".\n");

		Student tmp;
		while(f >> tmp)
			listMain.push_back(tmp);

		f.close();
	}

	//сортировка списка
	listMain.sort([](const Student &s1, const Student &s2)
	{
		return s1.getName() < s2.getName();
	});

	//создание общего файла
	std::cout << "Введите название для общего файла: ";
	std::string filename;
	std::getline(std::cin, filename);
	filename += ".txt";

	copyListContentToFile(filename, listMain);	
}

void makeSharedFileSortedByGroup()
{
	//создание списка с названиями групп
	std::fstream f;
	f.open("group_names.txt", std::ios::in);
	std::list<std::string> listNames;
	std::string tmp;

	if(!f.is_open())
		throw std::runtime_error("Ошибка: не удалось открыть файл group_names.txt.\n");

	while(f >> tmp)
		listNames.push_back(tmp);

	f.close();

	//создание общего списка студентов
	std::list<Student> listMain;
	std::list<std::string>::iterator iter;

	for(iter = listNames.begin(); iter != listNames.end(); iter++)
	{
		f.open(*iter + ".txt", std::ios::in);

		if(!f.is_open())
			throw std::runtime_error("Ошибка: не удалось открыть/создать файл " + *iter + ".txt" + ".\n");

		Student tmp;
		while(f >> tmp)
			listMain.push_back(tmp);

		f.close();
	}

	//сортировка списка
	listMain.sort([](const Student &s1, const Student &s2)
	{
		return s1.getGroup() > s2.getGroup();
	});

	//создание общего файла
	std::cout << "Введите название для общего файла: ";
	std::string filename;
	std::getline(std::cin, filename);
	filename += ".txt";

	copyListContentToFile(filename, listMain);	
}