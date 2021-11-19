#include <fstream>
#include <iostream>
const int N = 11;
using namespace std;

class Stack {
private:
	int* arr; //указатель на массив
	int top; //переменная для вершины стека
public:
	Stack() //конструктор
	{
		arr = new int[N];
		top = -1;
	}
	Stack(int m) //конструктор с параметром
	{
		arr = new int[m];
		top = -1;
	}
	void Push(int n) //добавляем
	{
		if (top == N - 1) //если верхний эл. равен длинне
		{
			cout << "Стек переполнен!" << endl; //то стек переполнен
		}
		else //иначе
		{
			top++; //двигаем вверх на 1
			arr[top] = n; //полученное значение на место верхнего
		}
	}
	int Pop() //удаляем
	{
		if (top < 0) //если верхний элемент <0
		{
			cout << "Стек пуст!" << endl; //стек пуст
			return 0;
		}
		else //иначе
		{
			int element = arr[top]; //извлекаем значение
			top -= 1; //уменьшаем значение вершины
			return element;
		}
	}

	bool empty()
	{
		if (top >= 0)
			return true;
		else
			return false;
	}

	int front()
	{
		return arr[top];
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
	ofstream output("OUTPUT.txt");
	Stack st; //стек, в котором хранятся номера вершин
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
	st.Push(start);
	stacked[start] = true;
	VON_PUNKT[start] = -1;
	rang[start] = 0;
	while (!st.empty())
	{
		int besuch = st.front();
		st.Pop();
		for (int i = 0; i < N; i++)
		{
			if (!stacked[i] && A[besuch][i])
			{
				st.Push(i);
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
