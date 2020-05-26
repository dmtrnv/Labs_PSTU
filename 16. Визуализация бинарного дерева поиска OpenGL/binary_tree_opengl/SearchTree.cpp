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

int SearchTree::getAmountOfNodes()
{
	int count = 1;

	if(this->left != nullptr)
		count += this->left->getAmountOfNodes();
	if(this->right != nullptr)
		count += this->right->getAmountOfNodes();

	return count;
}




void SearchTree::setCoordsForNode(int window_width, int window_height, int shift,
					  int tree_width, int tree_height, int x, int y, int R)
{
	//это условие не выполняется, когда дерево состоит из одного элемента
	if (tree_width != tree_height)
	{
		//коэффициент пропорциональности по оси Ох
		int k_x = (window_width - 2 * (shift + R)) / (tree_width - 1);
		//коэффициент пропорциональности по оси Оy
		int k_y = (window_height - 2 * (shift + R)) / (tree_height - 1);

		node_x = (window_width - 2*shift) * abs(2*x - 1) / pow(2, y+1) + shift;
		node_y = window_height - k_y * y - shift - R;
	}
	else
	{
		node_x = (window_width - 2*shift) * abs(2*x - 1) / pow(2, y+1) + shift;
		node_y = window_height / 2;
	}
}
		
SearchTree* SearchTree::getNodeByCoords(int x, int y, int R)
{
	SearchTree *node = this;
	node = get_help(node, x, y, R);
	return node;
}

void SearchTree::setCoordsForText(int k, int R)
{
	//х-координата первого символа текста
	text_x = node_x - 3 * R / 4;
	//у-координата первого символа текста
	text_y = node_y - 3 * R / (4 * k);
}

SearchTree* SearchTree::get_help(SearchTree *tree, int x, int y, int R)
{
	if(pow(x - tree->node_x, 2) + pow(y - tree->node_y, 2) <= pow(R, 2))
		return tree;

	SearchTree *tmp = nullptr;

	if(tree->getLeft() != nullptr)
		tmp = get_help(tree->getLeft(), x, y, R);

	if(tmp != nullptr)
		return tmp;

	if(tree->getRight() != nullptr)
		tmp = get_help(tree->getRight(), x, y, R);

	return tmp;
}

void SearchTree::initWindow(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - glutContext.window_width) / 2, 
						   (glutGet(GLUT_SCREEN_HEIGHT) - glutContext.window_height) / 2); 
	glutInitWindowSize(glutContext.window_width, glutContext.window_height);
	glutCreateWindow("Binary Search Tree with OpenGL");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mousePressed);
	glutMainLoop();
}

void SearchTree::display(void) 
{
	SearchTree* tree = (SearchTree*)glutContext.tree;

	int k = glutContext.k;
	int window_width = glutContext.window_width;
	int window_height = glutContext.window_height;
	int shift = glutContext.shift;
	int height = tree->getHeight();
	int maxLeafs = pow(2, height - 1); //максимальное число листов на нижнем уровне (нумерация с нуля)
	int width = 2 * maxLeafs - 1; //минимальная ширина дерева для печати (не конечная, но необходимая)
	int curLevel = 0; //номер строки (на выводе)
	int index = 0; //номер элемента в строке (нумерация с нуля)
	std::vector<SearchTree*> nodes; //массив для хранения узлов дерева
	int R; //радиус круга
	R = (window_width - 2 * shift) / (2 * width);
	if(2 * R * height > (window_height - 2 * shift)) 
		R = (window_height - 2 * shift) / (2 * width);
	glutContext.R = R;

	//устанавливаем координаты корня при рисовании
	tree->setCoordsForNode(window_width, window_height, shift, width, height, index, curLevel, R);
	nodes.push_back(tree);
		
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_POINT_SMOOTH);
	drawInsertButton();
	drawDeleteButton();

	for(int i = 0; i < tree->getAmountOfNodes(); i++) 
	{
		if(pow(2, curLevel) <= index + 1) 
		{
			index = 0;
			curLevel++;
		}

		if(nodes.at(i)->getLeft() != nullptr) 
		{
			nodes.push_back(nodes.at(i)->getLeft());
			index++;

			nodes.at(i)->getLeft()->setCoordsForNode(window_width, window_height, shift, width, height, index, curLevel, R);

			if(std::strcmp(nodes.at(i)->getLeft()->getData(), "-1_empty_000") != 0) 
			{
				int x1 = nodes.at(i)->node_x;
				int y1 = nodes.at(i)->node_y;
				int x2 = nodes.at(i)->getLeft()->node_x;
				int y2 = nodes.at(i)->getLeft()->node_y;
				drawLine(x1, y1, x2, y2);
			}
		}

		if(nodes.at(i)->getRight() != nullptr) 
		{
			nodes.push_back(nodes.at(i)->getRight());
			index++;

			nodes.at(i)->getRight()->setCoordsForNode(window_width, window_height, shift, width, height, index, curLevel, R);

			if(std::strcmp(nodes.at(i)->getRight()->getData(), "-1_empty_000") != 0) 
			{
				int x1 = nodes.at(i)->node_x;
				int y1 = nodes.at(i)->node_y;
				int x2 = nodes.at(i)->getRight()->node_x;
				int y2 = nodes.at(i)->getRight()->node_y;
				drawLine(x1, y1, x2, y2);
			}
		}

		if(std::strcmp(nodes.at(i)->getData(), "-1_empty_000") != 0)
		{

			if(glutContext.state == 0) 
			{
				drawFillCircle(nodes.at(i)->node_x, nodes.at(i)->node_y, R);
			}
			else 
			{
				drawFillCircle(nodes.at(i)->node_x, nodes.at(i)->node_y, R);

				if((tree->getNodeByCoords(glutContext.x, glutContext.y, R)->node_x == nodes.at(i)->node_x)
					&& (tree->getNodeByCoords(glutContext.x, glutContext.y, R)->node_y == nodes.at(i)->node_y))
				{
					drawGreenCircle(nodes.at(i)->node_x, nodes.at(i)->node_y, R);
				}
			}

			nodes.at(i)->setCoordsForText(k, R);
			drawText(nodes.at(i)->getData(), GLUT_STROKE_MONO_ROMAN, nodes.at(i)->text_x, nodes.at(i)->text_y, R, k);
		}
		
		if(glutContext.x >= glutContext.window_width * 0.02 && glutContext.x <= glutContext.window_width * 0.12 
			&& glutContext.y <= glutContext.window_height * 0.05 && glutContext.y >= glutContext.window_height * 0.02)
		{
			drawInsertButtonPressed();
		}

		if(glutContext.x >= glutContext.window_width * 0.02 && glutContext.x <= glutContext.window_width * 0.12 
			&& glutContext.y <= glutContext.window_height * 0.09 && glutContext.y >= glutContext.window_height * 0.06)
		{
			drawDeleteButtonPressed();
		}
	}

	glFinish();
	glutSwapBuffers();
}

void SearchTree::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, (GLsizei)w, 0, (GLsizei)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutContext.window_width = w;
	glutContext.window_height = h;

	glutPostRedisplay();
}

void SearchTree::drawLine(int x1, int y1, int x2, int y2)
{
	glLineWidth(2);
	glBegin(GL_LINES);

	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);

	glEnd();
}

void SearchTree::drawFillCircle(int x, int y, int R)
{
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	float x1, y1;

	for(int i = 0; i <= R; i++) 
	{
		for(int t = 0; t <= 360; t++) 
		{
			x1 = i * sin(t) + x;
			y1 = i * cos(t) + y;

			glVertex2f(x1, y1);
		}
	}

	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);

	for(int i = R - 1; i <= R; i++) 
	{
		for(int t = 0; t <= 360; t++) 
		{
			x1 = R * sin(t) + x;
			y1 = R * cos(t) + y;

			glVertex2f(x1, y1);
		}
	}

	glEnd();
}

void SearchTree::drawGreenCircle(int x, int y, int R)
{
	glColor3f(0.5, 0.85, 0.5);
	glBegin(GL_POINTS);
	float x1, y1;

	for(int i = 0; i <= R; i++) 
	{
		for(int t = 0; t <= 360; t++) 
		{
			x1 = i * sin(t) + x;
			y1 = i * cos(t) + y;

			glVertex2f(x1, y1);
		}
	}

	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);

	for(int i = R - 1; i <= R; i++) 
	{
		for(int t = 0; t <= 360; t++) 
		{
			x1 = R * sin(t) + x;
			y1 = R * cos(t) + y;

			glVertex2f(x1, y1);
		}
	}

	glEnd();
}

void SearchTree::drawText(const char *text, void* font, int text_x, int text_y, int R, int k)
{
	glLineWidth(1);
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(text_x, text_y, 0.0);

	std::string str = text;
	
	int max_char_width = 0;
	int char_width = 0;

	for(const auto c : str) 
	{
		char_width = glutStrokeWidth(font, c);
		
		if(max_char_width < char_width)
			max_char_width = char_width;
	}
	
	float expand_x = (float)1.5 * R / (float)(k * max_char_width) / (float)(str.size() * 0.50);
	float expand_y = (float)1.5 * R / (float)(k * 100);

	glScalef(expand_x, expand_y, 1.0);

	for(const auto c : str)
		glutStrokeCharacter(font, c);

	glPopMatrix();
}

void SearchTree::drawInsertButton()
{
	float x1 = glutContext.window_width * 0.02;
	float x2 = glutContext.window_width * 0.12;
	float y1 = glutContext.window_height * 0.98;
	float y2 = glutContext.window_height * 0.95;

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);

	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(0.35);
	glBegin(GL_LINES);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y1);

	glEnd();

	std::string str = "Insert node";

	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(x1 + 2, y2 + 3, 0.0);

	float expand_x = (float) (x2 - x1) / 740;
	float expand_y = (float) (y1 - y2) / 140;
	glScalef(expand_x, expand_y, 1.0);
	
	for(const auto c : str)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	glPopMatrix();
}

void SearchTree::drawDeleteButton()
{
	float x1 = glutContext.window_width * 0.02;
	float x2 = glutContext.window_width * 0.12;
	float y1 = glutContext.window_height * 0.94;
	float y2 = glutContext.window_height * 0.91;

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);

	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(0.35);
	glBegin(GL_LINES);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y1);

	glEnd();

	std::string str = "Delete node";

	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(x1 + 2, y2 + 3, 0.0);

	float expand_x = (float) (x2 - x1) / 785;
	float expand_y = (float) (y1 - y2) / 140;
	glScalef(expand_x, expand_y, 1.0);
	
	for(const auto c : str)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	glPopMatrix();
}

void SearchTree::drawInsertButtonPressed()
{
	float x1 = glutContext.window_width * 0.02;
	float x2 = glutContext.window_width * 0.12;
	float y1 = glutContext.window_height * 0.98;
	float y2 = glutContext.window_height * 0.95;

	glColor3f(0.0, 0.85, 1.0);
	glBegin(GL_QUADS);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);

	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(0.35);
	glBegin(GL_LINES);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y1);

	glEnd();

	std::string str = "Insert node";

	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(x1 + 2, y2 + 3, 0.0);

	float expand_x = (float) (x2 - x1) / 740;
	float expand_y = (float) (y1 - y2) / 140;
	glScalef(expand_x, expand_y, 1.0);
	
	for(const auto c : str)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	glPopMatrix();
}

void SearchTree::drawDeleteButtonPressed()
{
	float x1 = glutContext.window_width * 0.02;
	float x2 = glutContext.window_width * 0.12;
	float y1 = glutContext.window_height * 0.94;
	float y2 = glutContext.window_height * 0.91;

	glColor3f(0.0, 0.85, 1.0);
	glBegin(GL_QUADS);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);

	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(0.35);
	glBegin(GL_LINES);

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y2);
	glVertex2f(x1, y1);

	glEnd();

	std::string str = "Delete node";

	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(x1 + 2, y2 + 3, 0.0);

	float expand_x = (float) (x2 - x1) / 785;
	float expand_y = (float) (y1 - y2) / 140;
	glScalef(expand_x, expand_y, 1.0);
	
	for(const auto c : str)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	glPopMatrix();
}

void SearchTree::mouseMove(int x, int y) 
{
	SearchTree *tree = (SearchTree*)glutContext.tree;
	int R = glutContext.R;

	SearchTree *node = tree->getNodeByCoords(x, glutContext.window_height - y, R);

	if(node != nullptr) 
	{
		glutContext.x = x;
		glutContext.y = glutContext.window_height - y;
		glutContext.state = 1;

		glutPostRedisplay();
	}
	else 
	{
		glutContext.state = 0;
		glutContext.x = x;
		glutContext.y = y;
		glutPostRedisplay();
	}
}

void SearchTree::mousePressed(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_UP)
	{
			if(x >= glutContext.window_width * 0.02 && x <= glutContext.window_width * 0.12 
				&& y <= glutContext.window_height * 0.05 && y >= glutContext.window_height * 0.02)
			{
				SetForegroundWindow(GetConsoleWindow());

				std::cout << "Enter the value you want to insert: ";
				char data[dataSize];
				std::cin.getline(data, dataSize, '\n');
				glutContext.root->insertNode(data);

				delete glutContext.temp;
				glutContext.temp = new SearchTree(pow(2, glutContext.root->getHeight()));
				glutContext.temp->copyTreeWithEmpty(glutContext.root);
				glutContext.tree = glutContext.temp;

				HWND hWnd = FindWindow(nullptr, L"Binary Search Tree with OpenGL");
				SetForegroundWindow(hWnd);
			}

			if(x >= glutContext.window_width * 0.02 && x <= glutContext.window_width * 0.12 
				&& y <= glutContext.window_height * 0.09 && y >= glutContext.window_height * 0.06)
			{
				SetForegroundWindow(GetConsoleWindow());

				std::cout << "Enter the value you want to delete: ";
				char data[dataSize];
				std::cin.getline(data, dataSize, '\n');
				glutContext.root->deleteNode(data);

				delete glutContext.temp;
				glutContext.temp = new SearchTree(pow(2, glutContext.root->getHeight()));
				glutContext.temp->copyTreeWithEmpty(glutContext.root);
				glutContext.tree = glutContext.temp;

				HWND hWnd = FindWindow(nullptr, L"Binary Search Tree with OpenGL");
				SetForegroundWindow(hWnd);
			}
		}
	}
}




SearchTree::SearchTree(const int &size)
{
	if(size <= 0)
		throw std::invalid_argument("Error: tree size <= 0 (constructor()).\n");

	data = new char[dataSize];
	std::strcpy(data, "-1_empty_000");

	parent = nullptr;
	left = nullptr;
	right = nullptr;

	int validSize = size - 1;
	
	this->insertLeftWithEmpty(makeCompleteTreeWithEmpty(validSize / 2));
	this->insertRightWithEmpty(makeCompleteTreeWithEmpty(validSize - validSize/2 - 1));
}

void SearchTree::insertLeftWithEmpty(SearchTree *nodeToInsert)
{
	SearchTree *tmp = this;

	if(tmp->left != nullptr && std::strcmp(tmp->left->data, nodeToInsert->data) != 0)
	{
		tmp = tmp->left;
		insertLeftWithEmpty(nodeToInsert);
	}
	else
		tmp->left = nodeToInsert;
}

void SearchTree::insertRightWithEmpty(SearchTree *nodeToInsert)
{
	SearchTree *tmp = this;

	if(tmp->right != nullptr && std::strcmp(tmp->left->data, nodeToInsert->data) != 0)
	{
		tmp = tmp->right;
		insertRightWithEmpty(nodeToInsert);
	}
	else
		tmp->right = nodeToInsert;
}

SearchTree* SearchTree::makeCompleteTreeWithEmpty(const int &size)
{
	if(size < 0)
		throw std::invalid_argument("Error: tree size < 0 (makeCompleteTreeWithEmpty()).\n");

	if(size == 0)
		return nullptr;

	SearchTree* root = new SearchTree("-1_empty_000");
			
	root->insertLeftWithEmpty(makeCompleteTreeWithEmpty(size / 2));
	root->insertRightWithEmpty(makeCompleteTreeWithEmpty(size - size/2 - 1));

	return root;
}

void SearchTree::copyTreeWithEmpty(SearchTree *tree)
{
	if(tree != nullptr)
	{
		this->insertNodeWithEmpty(tree->data);
		copyTreeWithEmpty(tree->left);
		copyTreeWithEmpty(tree->right);
	}
}

void SearchTree::insertNodeWithEmpty(const char *_data)
{
	if(_data == nullptr)
	{
		return;
	}

	if(this == nullptr)
		throw std::runtime_error("Error: this is nullptr (insertNodeWithEmpty()).\n");

	else if(std::strcmp(this->data, "-1_empty_000") == 0)
	{
		std::strcpy(data, _data);
		return;
	}

	SearchTree *tree = this;

	while(std::strcmp(tree->data, "-1_empty_000") != 0)
	{
		//если добавляемый элемент меньше текущего
		if(std::strcmp(_data, tree->data) < 0)
		{
			if(std::strcmp(tree->left->data, "-1_empty_000") != 0)
				tree = tree->left;
			else
			{
				std::strcpy(tree->left->data, _data);
				break;
			}
		}
		//если добавляемый элемент больше или равен текущему
		else if(std::strcmp(_data, tree->data) > 0 || std::strcmp(_data, tree->data) == 0)
		{
			if(std::strcmp(tree->right->data, "-1_empty_000") != 0)
				tree = tree->right;
			else
			{
				std::strcpy(tree->right->data, _data);
				break;
			}
		}
	}
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

int SearchTree::getHeight() 
{ 
	if (this == nullptr) 
		return 0; 
  
	std::queue<SearchTree*> q; 
  
	q.push(this); 
	int height = 0; 
  
	while (1) 
	{ 
		int nodeCount = q.size(); 
		if (nodeCount == 0) 
			return height; 
  
		height++; 
  
		while (nodeCount > 0) 
		{ 
			SearchTree *node = q.front(); 
			q.pop(); 

			if (node->left != NULL) 
				q.push(node->left); 

			if (node->right != NULL) 
				q.push(node->right); 

			nodeCount--; 
		} 
	} 
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

void SearchTree::drawTree(int argc, char** argv, int window_width, int window_height, int shift, int k)
{
	glutContext.root = this;
	glutContext.temp = new SearchTree(pow(2, glutContext.root->getHeight()));
	glutContext.temp->copyTreeWithEmpty(glutContext.root);
	glutContext.tree = glutContext.temp;
	glutContext.window_width = window_width;
	glutContext.window_height = window_height;
	glutContext.shift = shift;
	glutContext.k = k;
	std::cout << "Screen: width = " << window_width << ", height = " << window_height << std::endl;

	initWindow(argc, argv);
}