#include <iostream>
#include <Windows.h>
#include "BalancedTree.h"
#include "SearchTree.h"


node *makeBT();
void printCountLeaves(node *root);
void convertTree(node *balanced, SearchTree *search);
void insertNodeInSearchTree(SearchTree *tree);
void deleteNodeFromSearchTree(SearchTree *tree);
void findNodeInSearchTree(SearchTree *tree);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		std::cout << "\t\tМеню\n"
				  << "1. Создать идеально сбалансированное дерево\n"
				  << "2. Распечатать дерево\n"
				  << "3. Подсчитать количество листьев в дереве\n"
				  << "4. Преобразовать идеально сбалансированное дерево в дерево поиска\n"
				  << "0. Выйти\n\n";

		node *balancedTree = nullptr;
		SearchTree *searchTree = new SearchTree;
		int n;

		do
		{
			std::cout << "Выберите действие: ";
			std::cin >> n;
			while(std::cin.fail() || n < 0 || n > 4)
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
					std::cerr << "Ошибка: введен неверный номер, диапазон доступных номеров: 0-4. Попробуйте снова: ";
					std::cin >> n;
				}
			}
			std::cin.get();

			switch(n)
			{
				case 1:
						balancedTree = makeBT();
						std::cout << std::endl;
						break;
				case 2:
						printHorizontal(balancedTree);
						std::cout << std::endl;
						break;
				case 3: 
						printCountLeaves(balancedTree);
						std::cout << std::endl;
						break;
				case 4:
						convertTree(balancedTree, searchTree);
						std::cout << std::endl;
						goto searchT; // searchT находится сразу после цикла do-while
				default:
						break;
			}
		} while(n != 0);

		std::cout << std::endl;
		system("pause");
		return 0;

	searchT:
		std::cout << "\t\tМеню\n"
				  << "1. Распечать дерево\n"
				  << "2. Добавить элемент в дерево\n"
				  << "3. Удалить элемент из дерева\n"
				  << "4. Найти элемент в дереве\n"
				  << "0. Выйти\n\n";

		do
		{
			std::cout << "Выберите действие: ";
			std::cin >> n;
			while(std::cin.fail() || n < 0 || n > 4)
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
					std::cerr << "Ошибка: введен неверный номер, диапазон доступных номеров: 0-4. Попробуйте снова: ";
					std::cin >> n;
				}
			}
			std::cin.get();

			switch(n)
			{
				case 1:
						searchTree->printHorizontal();
						std::cout << std::endl;
						break;
				case 2:
						insertNodeInSearchTree(searchTree);
						std::cout << std::endl;
						break;
				case 3: 
						deleteNodeFromSearchTree(searchTree);
						std::cout << std::endl;
						break;
				case 4:
						findNodeInSearchTree(searchTree);
						std::cout << std::endl;
						break;
				default:
						break;
			}
		} while(n != 0);

	}
	catch(const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}


node *makeBT()
{
	int size;
	std::cout << "Укажите размер дерева: ";
			std::cin >> size;
			while(std::cin.fail() || size < 0)
			{
				if(std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(100, '\n');
					std::cerr << "Ошибка: введен некорректный символ. Попробуйте снова: ";
					std::cin >> size;
				}
				else
				{
					std::cerr << "Ошибка: введен неверный размер. Попробуйте снова: ";
					std::cin >> size;
				}
			}
			std::cin.get();

	return makeBalancedTree(size);
}

void printCountLeaves(node *root)
{
	std::cout << "Количество листьев: " << countLeaves(root) << ".\n";
}

void convertTree(node *balanced, SearchTree *search)
{
	std::vector<char*> vec;
	copyBalancedTreeToVector(balanced, vec);

	for(const auto& data : vec)
		search->insertNode(data);

	deleteBalancedTree(balanced);
}

void insertNodeInSearchTree(SearchTree *tree)
{
	std::cout << "Укажите данные: ";
	char *data = new char[dataSize];
	std::cin.getline(data, dataSize, '\n');

	tree->insertNode(data);
}

void deleteNodeFromSearchTree(SearchTree *tree)
{
	std::cout << "Укажите данные: ";
	char *data = new char[dataSize];
	std::cin.getline(data, dataSize, '\n');

	tree->deleteNode(data);
}

void findNodeInSearchTree(SearchTree *tree)
{
	std::cout << "Укажите данные: ";
	char *data = new char[dataSize];
	std::cin.getline(data, dataSize, '\n');

	SearchTree *st = tree->find(data);

	if(st == nullptr)
		return;
	else
		std::cout << "Элемент " << st->getData() << " найден.\n";
}
