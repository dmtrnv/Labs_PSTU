#pragma once
#include <iostream>
#include <exception>
#include <vector>


/*
Инструкция:
1. Для создания сбалансированного дерева следует использовать функцию makeBalancedTree();
2. При добавлении/удалении элементов баланс может быть нарушен - перестройка дерева не производится;
3. После заввершения работы с деревом следует освободить память функцией deleteBalancedTree().
*/


const int dataSize = 50;
struct node
{
	char *dataValue;
	node *left;
	node *right;
};

void insertLeft(node *root, node *nodeToInsert);
void insertRight(node *root, node *nodeToInsert);
void preOrder(node *root);
void printPreOrder(node *root);
node* makeBalancedTree(const int &size);
void deleteBalancedTree(node *root);
int countLeaves(node *root);
void copyBalancedTreeToVector(node *root, std::vector<char*> &vec);
void printHorizontalHelp(node *root, int space);
void printHorizontal(node *root);