#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

struct obj //структура отдельного элемента
{
	int data;
	obj* left, * right;
};

struct tree
{
	obj* root; //указатель на корень
};

void add_obj(obj*& current, int inputdata) //добавление элементов
{
	if (current != NULL)
	{
		if (inputdata < current->data)
			add_obj(current->left, inputdata); //идем налево
		else
			add_obj(current->right, inputdata); //идем направо
	}
	else
	{
		obj* temp = new obj;
		temp->data = inputdata;
		temp->left = NULL;
		temp->right = NULL;
		current = temp;
	}
}
void createTree(tree& currtree) //функция заполнения дерева
{
	cout << "Введите 13 чисел, полученных при компиляции..." << endl;
	int inputData;
	for (int i = 0; i < 13; i++)
	{
		cin >> inputData;
		add_obj(currtree.root, inputData);
	}
}
void objsearch(obj* currobj) //обход дерева
{
	if (currobj == NULL)
		return;
	ofstream out;
	out.open("tree.txt", ios::app);
	if (out.is_open())
		if (currobj->data / 10 == 0)
			out << "0" << currobj->data << " ";
		else
			out << currobj->data << " ";
	out.close();
	objsearch(currobj->left); //рекурсия влево
	objsearch(currobj->right); //рекурсия вправо
}
void treesearch(tree currtree)
{
	if (currtree.root == NULL)
	{
		cout << "Дерево не создано!" << endl;
		return;
	}
	objsearch(currtree.root); //обход дерева, начиная с корня
}
int deleter(struct tree* tree, int item)
{
	struct obj** q, * z;
	assert(tree != NULL);
	q = &tree->root;
	z = tree->root;
	for (;;) //поиск элемента удаления
	{
		if (z == NULL)
			return NULL;
		else if (item == z->data)
			break;
		else if (item > z->data)
		{
			q = &z->right;
			z = z->right;
		}
		else
		{
			q = &z->left;
			z = z->left;
		}
	}
	if (z->right == NULL) //первый случай
		*q = z->left;
	else
	{
		struct obj* y = z->right;
		if (y->left == NULL) //второй случай
		{
			y->left = z->left;
			*q = y;
		}
		else
		{
			struct obj* x = y->left;
			while (x->left != NULL)
			{
				y = x;
				x = y->left;
			}
			y->left = x->right;
			x->left = z->left;
			x->right = z->right;
			*q = x;
		}
	}
	free(z); //удаление элемента
	return 1;
};
int main()
{
	setlocale(LC_ALL, "Russian");
	tree treemain;
	treemain.root = NULL;
	int menu;
	bool working = true;
	while (working)
	{
		cout << "-------------------МЕНЮ-------------------" << endl
			<< "1. Создание дерева" << endl
			<< "2. Обход дерева и запись в файл" << endl
			<< "3. Удаление элемента дерева" << endl
			<< "0. Выход из программы" << endl
			<< "------------------------------------------" << endl
			<< "Введите пункт: ";
		cin >> menu;
		switch (menu)
		{
		case 1: createTree(treemain); break;
		case 2: treesearch(treemain); break;
		case 3:
			int choice;
			cout << "Введите значение элемента, который хотите удалить: ";
			cin >> choice;
			deleter(&treemain, choice); break;
		case 0: working = false;
		}
	}
}
