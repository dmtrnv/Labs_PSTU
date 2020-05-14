#include "BalancedTree.h"


void insertLeft(node *root, node *nodeToInsert)
{
	if(root == nullptr)
		if(nodeToInsert != nullptr)
		{
			root = nodeToInsert;
			return;
		}
		else 
			throw std::invalid_argument("Error: node to insert is nullptr (insertRight()).\n");

	node *tmp = root;
	if(tmp->left != nullptr)
	{
		tmp = tmp->left;
		insertLeft(tmp, nodeToInsert);
	}
	else
		tmp->left = nodeToInsert;
}

void insertRight(node *root, node *nodeToInsert)
{
	if(root == nullptr)
		if(nodeToInsert != nullptr)
		{
			root = nodeToInsert;
			return;
		}
		else 
			throw std::invalid_argument("Error: node to insert is nullptr (insertRight()).\n");

	node *tmp = root;
	if(tmp->right != nullptr)
	{
		tmp = tmp->right;
		insertRight(tmp, nodeToInsert);
	}
	else
		tmp->right = nodeToInsert;
}

void preOrder(node *root)
{		
	if(root != nullptr)
	{
		std::cout << root->dataValue << "  ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

void printPreOrder(node *root)
{
	if(root == nullptr)
	{
		std::cerr << "Error: tree is empty (print()).\n";
		return;
	}

	preOrder(root);
	std::cout << std::endl;
}

node* makeBalancedTree(const int &size)
{
	if(size < 0)
		throw std::invalid_argument("Error: tree size < 0 (makeBalancedTree()).\n");

	if(size == 0)
		return nullptr;

	std::cout << "”кажите данные: ";
	char *_data = new char[dataSize];
	std::cin.getline(_data, dataSize, '\n');

	node* root = new node {_data, nullptr, nullptr};

	insertLeft(root, makeBalancedTree(size / 2));
	insertRight(root, makeBalancedTree(size - size/2 - 1));

	return root;
}

void deleteBalancedTree(node *root)
{
	if(root != nullptr)
	{
		deleteBalancedTree(root->left);
		deleteBalancedTree(root->right);
		delete [] root->dataValue;
		root->dataValue = nullptr;
		delete root;
		root = nullptr;
	}
}

int countLeaves(node *root)
{
	if(root == nullptr)
		return 0;

	if(root->left == nullptr && root->right == nullptr)
		return 1;
	else
		return countLeaves(root->left) + countLeaves(root->right);
}

void copyBalancedTreeToVector(node *root, std::vector<char*> &vec)
{
	if(root != nullptr)
	{
		vec.push_back(root->dataValue);
		copyBalancedTreeToVector(root->left, vec);
		copyBalancedTreeToVector(root->right, vec);
	}
}

void printHorizontalHelp(node *root, int space)
{
	if(root == nullptr)
		return;

	space += 10;

	printHorizontalHelp(root->right, space);

	std::cout << "\n\n";
	for(int i = 10; i < space; i++)
		std::cout << ' ';
	std::cout << root->dataValue;

	printHorizontalHelp(root->left, space);
}

void printHorizontal(node *root)
{
	printHorizontalHelp(root, 0);
}