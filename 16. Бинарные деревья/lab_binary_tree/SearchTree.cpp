#include "SearchTree.h"


//private methods
void SearchTree::copyTree(SearchTree *tree)
{
	if(tree != nullptr)
	{
		this->insertNode(tree->data);
		copyTree(tree->left);
		copyTree(tree->right);
	}
}

SearchTree* SearchTree::findElement(const char *_data)
{
	if(_data == nullptr)
		return nullptr;

	if(this == nullptr || std::strcmp(this->data, _data) == 0)
		return this;

	if(std::strcmp(_data, this->data) < 0)
		return this->left->findElement(_data);
	else
		return this->right->findElement(_data);
}

void SearchTree::deleteNodeByPointer(SearchTree *tree)
{
	//если у узла два потомка
	if(tree->left != nullptr && tree->right != nullptr)
	{
		SearchTree *next = tree->right->findMin();

		std::strcpy(tree->data, next->data);
		deleteNodeByPointer(next);
	}
	//если у узла один потомок
	else if (tree->left != nullptr || tree->right != nullptr)
	{
		if(tree->left != nullptr)
		{
			if(tree->parent->right == tree)
			{
				tree->parent->right = tree->left;
				tree->left->parent = tree->parent;
				delete [] tree->data;
				tree->data = nullptr;
				tree = nullptr;
			}
			else
			{
				tree->parent->left = tree->left;
				tree->left->parent = tree->parent;
				delete [] tree->data;
				tree->data = nullptr;
				tree = nullptr;
			}
		}
		else
		{
			if(tree->parent->right == tree)
			{
				tree->parent->right = tree->right;
				tree->right->parent = tree->parent;
				delete [] tree->data;
				tree->data = nullptr;
				tree = nullptr;
			}
			else
			{
				tree->parent->left = tree->right;
				tree->right->parent = tree->parent;
				delete [] tree->data;
				tree->data = nullptr;
				tree = nullptr;
			}
		}
	}
	//если у узла нет потомков
	else
	{
		if(tree->parent == nullptr)
		{
			delete [] tree->data;
			tree->data = nullptr;
			tree = nullptr;
		}
		else if(std::strcmp(tree->parent->left->data, tree->data) == 0)
		{
			delete [] tree->data;
			tree->data = nullptr;
			tree->parent->left = nullptr;
			tree = nullptr;
		}
		else if(std::strcmp(tree->parent->right->data, tree->data) == 0)
		{
			delete [] tree->data;
			tree->data = nullptr;
			tree->parent->right = nullptr;
			tree = nullptr;
		}
	}
}

void SearchTree::inOrder(SearchTree *tree) const
{
	if(tree != nullptr)
	{
		inOrder(tree->left);
		std::cout << tree->data << "  ";
		inOrder(tree->right);
	}
}

void SearchTree::printHorizontalHelp(int space)
{
	if(this == nullptr)
		return;

	space += 10;
			
	this->right->printHorizontalHelp(space);

	std::cout << "\n\n";
	for(int i = 10; i < space; i++)
		std::cout << ' ';
	std::cout << this->getData();

	this->left->printHorizontalHelp(space);
}




//public methods
SearchTree::SearchTree()
{
	data = nullptr;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

SearchTree::SearchTree(const char *_data)
{
	if(_data == nullptr)
		throw std::invalid_argument("Error: _data is nullptr (constructor()).\n");

	data = new char[dataSize];
	data[0] = '\0';
	std::strncat(data, _data, dataSize);

	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

SearchTree::SearchTree(SearchTree &_tree)
{
	if(&_tree == nullptr)
		throw std::invalid_argument("Error: _tree is empty (copyConstructor()).\n");

	this->parent = nullptr;
	this->data = nullptr;
	this->left = nullptr;
	this->right = nullptr;

	copyTree(&_tree);
}

SearchTree::~SearchTree()
{
	//сохраняем указатель на корень
	static SearchTree *st = this;
		
	if(left != nullptr)
	{
		delete [] left->data;
		left->data = nullptr;
		delete left;
		left = nullptr;
	}

	if(right != nullptr)
	{
		delete [] right->data;
		right->data = nullptr;
		delete right;
		right = nullptr;
	}

	//после того, как все узлы удалены, удаляем корень
	if(st == nullptr)
	{ }
	else if(st->left == nullptr && st->right == nullptr)
	{
		delete [] st->data;
		st->data = nullptr;
		st = nullptr;
	}
}

SearchTree& SearchTree::operator=(SearchTree &tree)
{
	if(this != nullptr)
		this->~SearchTree();

	copyTree(&tree);

	return *this;
}

char* SearchTree::getData()
{
	if(this == nullptr)
	{
		std::cerr << "Error: tree is nullptr (getData()).\n";
		return nullptr;
	}
	else if (this->data == nullptr)
	{
		std::cerr << "Error: data is nullptr (getData()).\n";
		return nullptr;
	}

	return this->data;
}

SearchTree* SearchTree::find(const char *_data) 
{
	if(this == nullptr || this->data == nullptr)
	{
		std::cerr << "Error: tree is empty (find()).\n";
		return nullptr;
	}

	SearchTree *st = findElement(_data);

	if(st == nullptr)
	{
		std::cerr << "Error: element not found (find()).\n";
		return st;
	}
	else
		return st;
}

SearchTree* SearchTree::findMin()
{
	if(this == nullptr || this->data == nullptr)
	{
		std::cerr << "Error: tree is empty (findMin()).\n";
		return nullptr;
	}

	if(this->left == nullptr)
		return this;

	return this->left->findMin();
}

SearchTree* SearchTree::findMax()
{
	if(this == nullptr || this->data == nullptr)
	{
		std::cerr << "Error: tree is empty (findMax()).\n";
		return nullptr;
	}

	if(this->right == nullptr)
		return this;

	return this->right->findMax();
}

void SearchTree::insertNode(const char *_data)
{
	if(_data == nullptr)
	{
		std::cerr << "Error: _data is nullptr (insertNode()).\n";
		return;
	}

	if(this == nullptr)
		throw std::runtime_error("Error: this is nullptr (insertNode()).\n");

	else if(this->data == nullptr)
	{
		data = new char[dataSize];
		data[0] = '\0';
		std::strncat(data, _data, dataSize);
		return;
	}

	SearchTree *tree = this;

	while(tree != nullptr)
	{
		//если добавляемый элемент меньше текущего
		if(std::strcmp(_data, tree->data) < 0)
		{
			if(tree->left != nullptr)
				tree = tree->left;
			else
			{
				SearchTree *st = new SearchTree(_data);
				st->parent = tree;
				tree->left = st;
				break;
			}
		}
		//если добавляемый элемент больше или равен текущему
		else if(std::strcmp(_data, tree->data) > 0 || std::strcmp(_data, tree->data) == 0)
		{
			if(tree->right != nullptr)
				tree = tree->right;
			else
			{
				SearchTree *st = new SearchTree(_data);
				st->parent = tree;
				tree->right = st;
				break;
			}
		}
	}
}

void SearchTree::deleteNode(const char *_data)
{
	if(this == nullptr || this->data == nullptr)
	{
		std::cerr << "Error: tree is empty (deleteNode()).\n";
		return;
	}

	if(_data == nullptr)
	{
		std::cerr << "Error: _data is nullptr (deleteNode()).\n";
		return;
	}

	SearchTree *tree = this->findElement(_data);

	if(tree == nullptr)
	{
		std::cerr << "Error: element not found (deleteNode()).\n";
		return;
	}

	//если у узла два потомка
	if(tree->left != nullptr && tree->right != nullptr)
	{
		SearchTree *next = tree->right->findMin();
			
		std::strcpy(tree->data, next->data);
		deleteNodeByPointer(next);
	}

	//если у узла один потомок
	else if (tree->left != nullptr || tree->right != nullptr)
	{
		//если узел является корнем дерева
		if(tree->parent == nullptr)
		{
			if(tree->left != nullptr)
			{
				SearchTree *next = tree->left->findMax();
			
				std::strcpy(tree->data, next->data);
				deleteNodeByPointer(next);
			}
			else
			{
				SearchTree *next = tree->right->findMin();
			
				std::strcpy(tree->data, next->data);
				deleteNodeByPointer(next);
			}
		}

		//если узел не является корнем дерева
		else if(tree->left != nullptr)
		{
			if(tree->parent->right == tree)
			{
				tree->parent->right = tree->left;
				tree->left->parent = tree->parent;
				delete [] tree->data;
				tree->data = nullptr;
				tree = nullptr;
			}
			else
			{
				tree->parent->left = tree->left;
				tree->left->parent = tree->parent;
				delete [] tree->data;
				tree->data = nullptr;
				tree = nullptr;
			}
		}
		else
		{
			if(tree->parent->right == tree)
			{
				tree->parent->right = tree->right;
				tree->right->parent = tree->parent;
				delete [] tree->data;
				tree->data = nullptr;
				tree = nullptr;
			}
			else
			{
				tree->parent->left = tree->right;
				tree->right->parent = tree->parent;
				delete [] tree->data;
				tree->data = nullptr;
				tree = nullptr;
			}
		}
	}
	//если у узла нет потомков
	else
	{
		if(tree->parent == nullptr)
		{
			delete [] tree->data;
			tree->data = nullptr;
			tree = nullptr;
		}
		else if(tree->parent->left != nullptr && tree->parent->left->data != nullptr)
		{
			if(std::strcmp(tree->parent->left->data, tree->data) == 0)
			{
				delete [] tree->data;
				tree->data = nullptr;
				tree->parent->left = nullptr;
				tree = nullptr;
			}
		}
		else if(std::strcmp(tree->parent->right->data, tree->data) == 0)
		{
			delete [] tree->data;
			tree->data = nullptr;
			tree->parent->right = nullptr;
			tree = nullptr;
		}
	}
}

void SearchTree::printInOrder()
{
	if(this->data == nullptr || this == nullptr)
	{
		std::cerr << "Error: tree is empty (print()).\n";
		return;
	}

	inOrder(this);
	std::cout << std::endl;
}

void SearchTree::printHorizontal()
{
	printHorizontalHelp(0);
}
