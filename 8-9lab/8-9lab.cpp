//программа с использованием стека
#include <fstream>
#include <iostream>

const int N = 11;
using namespace std;
struct item
{
	item* next;
	item* prev;
	int data;
};
class stack
{
private:
	item* first;
	item* last;
	int count;
public:
	stack()
	{
		last = NULL;
		first = NULL;
		count = 0;
	}
	void push(int a)
	{
		item* newitem = new item;
		newitem->data = a;
		if (first == NULL)
			first = newitem;
		newitem->next = NULL;
		newitem->prev = last;
		if (last != NULL)
			last->next = newitem;
		last = newitem;
		count++;
	}
	void pop()
	{
		item* place = last;
		if (place != first)
		{
			place->prev->next = NULL;
			last = place->prev;
		}
		else
		{
			first = NULL;
			last = NULL;
		}
		delete place;
		count--;
	}
	bool empty()
	{
		if (first == NULL)
			return true;
		else
			return false;
	}
	int front()
	{
		return last->data;
	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	ofstream output("OUTPUT.txt");

	stack st; //стек, в котором хранятся номера вершин
	bool stacked[N]; //массив, в котором хранится информация, если ли вершина в стеке
	bool A[N][N] = //матрица смежности графа
	{
		{0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0}
	};
	int start, end; //номера начальной и конечной вершин
	int rang[N]; //хранит длину пути
	int VON_PUNKT[N]; //хранит путь от начальной до конечной точки
	int designing[N]; //составляет путь от начальной до конечной точки
	cout << "Введите начальную вершину (1-11): ";
	cin >> start;
	cout << "Введите конечную вершину (1-11): ";
	cin >> end;
	start--;
	end--;
	for (int i = 0; i < N; i++)
	{
		VON_PUNKT[i] = start;
		rang[i] = 999;
		stacked[i] = false;
	}
	st.push(start);
	stacked[start] = true;
	VON_PUNKT[start] = -1;
	rang[start] = 0;
	while (!st.empty())
	{
		int besuch = st.front();
		st.pop();
		for (int i = 0; i < N; i++)
		{
			if (!stacked[i] && A[besuch][i])
			{
				st.push(i);
				stacked[i] = true;
				rang[i] = rang[besuch] + 1;
				VON_PUNKT[i] = besuch;
			}
		}
	}
	designing[0] = end;
	int i = 1;
	do
	{
		designing[i] = VON_PUNKT[end];
		i++;
		end = VON_PUNKT[end];
	} while (end != VON_PUNKT[0]);
	i--;
	do
	{
		if (designing[i] < 0)
		{
			i--;
		}
		else
		{
			output << designing[i] + 1 << " ";
			i--;
		}
	} while (i >= 0);
	cout << "Путь успешно записан в OUTPUT.txt!" << endl;
	output.close();
}
