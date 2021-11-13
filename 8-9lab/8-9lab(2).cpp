//программа с рекурсией
#include <fstream>
#include <iostream>

const int N = 11;
using namespace std;
bool visited[N]; //записывает пройденные точки
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
}; //матрица смежности
int rang[N]; //хранит длинну пути
int VON_PUNKT[N]; //хранит путь от начальной до конечной точки
int designing[N]; //составляет путь от начальной до конечной точки
void go(int curr) //рекурсивная функция вычисления пути
{
	visited[curr] = 1;
	for(int i = 0; i < N; i++)
		if (!visited[i] && A[curr][i])
		{
			VON_PUNKT[i] = curr;
			visited[i] = true;
			go(i);
		}
}
void main()
{
	setlocale(LC_ALL, "Russian");
	int start, end; //номера начальной и коенчной вершин
	ofstream output("OUTPUT.txt");
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
		visited[i] = false;
	}
	visited[start] = true;
	VON_PUNKT[start] = -1;
	rang[start] = 0;
	go(start);
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
			i--;
		else
		{
			output << designing[i] + 1 << " ";
			i--;
		}
	} while (i >= 0);
	cout << "Путь успешно записан в OUTPUT.txt!" << endl;
	output.close();
}
