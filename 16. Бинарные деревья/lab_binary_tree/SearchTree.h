#pragma once
#include <iostream>
#include <cstring>
#include <exception>


class SearchTree
{
	private:
		static const int dataSize = 50;
		char *data;
		SearchTree *parent;
		SearchTree *left;
		SearchTree *right;

		void copyTree(SearchTree *tree);
		SearchTree* findElement(const char *_data);
		void deleteNodeByPointer(SearchTree *tree);
		void inOrder(SearchTree *tree) const;
		void printHorizontalHelp(int space);

	public:
		SearchTree();
		SearchTree(const char *_data);
		SearchTree(SearchTree &_tree);
		~SearchTree();
		SearchTree& operator=(SearchTree &tree);
		char* getData();
		SearchTree* find(const char *_data) ;
		SearchTree* findMin();
		SearchTree* findMax();
		void insertNode(const char *_data);
		void deleteNode(const char *_data);
		void printInOrder();
		void printHorizontal();
};

