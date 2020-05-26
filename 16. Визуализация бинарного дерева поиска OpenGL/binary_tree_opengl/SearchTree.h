#pragma once
#include <iostream>
#include <cstring>
#include <exception>
#include <queue>
#include <string>
#include <vector>
#include <GL/glut.h>
#include <Windows.h>


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
		SearchTree* getLeft() { return this->left; }
		SearchTree* getRight() { return this->right; }
		int getAmountOfNodes();

		//данные для вывода дерева на экран с помощью OpenGL
		static struct
		{
			void* tree;
			SearchTree *root, *temp;
			int window_width, window_height, shift, k, R, x, y, state;
		} glutContext;

		int node_x;
		int node_y;
		int text_x;
		int text_y;

		//методы для вывода дерева на экран с помощью OpenGl
		void setCoordsForNode(int window_width, int window_height, int shift,
							  int tree_width, int tree_height, int x, int y, int R);
		SearchTree* getNodeByCoords(int x, int y, int R);
		void setCoordsForText(int k, int R);
		SearchTree* get_help(SearchTree *node, int x, int y, int R);
		void initWindow(int argc, char** argv);
		static void display(void);
		static void reshape(int w, int h);
		static void drawLine(int x1, int y1, int x2, int y2);
		static void drawFillCircle(int x, int y, int R);
		static void drawGreenCircle(int x, int y, int R);
		static void drawText(const char *text, void* font, int text_x, int text_y, int R, int k);
		static void drawInsertButton();
		static void drawDeleteButton();
		static void drawInsertButtonPressed();
		static void drawDeleteButtonPressed();
		static void mouseMove(int x, int y);
		static void mousePressed(int button, int state, int x, int y);

		//конструктор с аргументом "size" и функции с окончанием "WithEmpty" предназначены
		//исключительно для кооректной отрисовки дерева с помощью OpenGL
		SearchTree(const int &size);
		void insertLeftWithEmpty(SearchTree *nodeToInsert);
		void insertRightWithEmpty(SearchTree *nodeToInsert);
		SearchTree* makeCompleteTreeWithEmpty(const int &size);
		void copyTreeWithEmpty(SearchTree *tree);
		void insertNodeWithEmpty(const char *_data);

	public:
		SearchTree();
		SearchTree(const char *_data);
		SearchTree(SearchTree &_tree);
		~SearchTree();
		SearchTree& operator=(SearchTree &tree);
		char* getData();
		int getHeight();
		SearchTree* find(const char *_data) ;
		SearchTree* findMin();
		SearchTree* findMax();
		void insertNode(const char *_data);
		void deleteNode(const char *_data);
		void drawTree(int argc, char** argv, int window_width, int window_height, int shift, int k);
};
