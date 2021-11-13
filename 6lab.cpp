#include <iostream>
#include <fstream>

using namespace std;

const int N = 10;

void main()
{
	setlocale(LC_ALL, "Russian");
	int O = 10000;
	int FIKS[N]; //фиксация метки
	int MIN_WEG[N]; //минимальный вес вершины
	int VON_PUNKT[N]; //точки, через которые проходит кратчайший путь
	int DUG[N][N] = { //матрица смежности
		{ O, 12, 2, O, 24, O, 25, O, O, 10 },
		{ 12, O, 23, 26, O, 9, 10, O, 20, O },
		{ 2, 23, O, O, 19, O, O, 3, 12, 15 },
		{ O, 26, O, O, 2, 14, O, 26, 16, O },
		{ 24, O, 19, 2, O, 15, 3, 15, O, 12 },
		{ O, 9, O, 14, 15, O, O, 6, O, O },
		{ 25, 10, O, O, 3, O, O, O, O, 7 },
		{ O, O, 3, 26, 15, 6, O, O, O, O },
		{ O, 20, 12, 16, O, O, O, O, O, O },
		{ 10, O, 15, O, 12, O, 7, O, O, O } };
	int start, end; //начальная и конечная вершины
	while (true)
	{
		cout << "Введите начальную вершину (1-10):"; cin >> start;
		cout << "Введите конечную вершину (1-10):"; cin >> end;
		start--;
		end--;
		//ИНИЦИАЛИЗАЦИЯ
		for (int i = 0; i < N; i++)
		{
			FIKS[i] = 0;
			VON_PUNKT[i] = start;
			MIN_WEG[i] = DUG[start][i];
		}
		FIKS[start] = 1;
		VON_PUNKT[start] = 0;
		//ОБЩИЙ ШАГ
		bool fikscheck = true;
		while (fikscheck)
		{
			int j = 0;
			int min = O;
			for (int k = 0; k < N; k++) //поиск ближайшей смежной вершины
			{
				if (FIKS[k] == 0)
				{
					if (MIN_WEG[k] <= min)
					{
						min = MIN_WEG[k];
						j = k;
					}
				}
			}
			FIKS[j] = 1;
			for (int k = 0; k < N; k++) //вычисление веса вершины
			{
				if (k != start)
				{
					if (MIN_WEG[k] > MIN_WEG[j] + DUG[j][k])
					{
						MIN_WEG[k] = MIN_WEG[j] + DUG[j][k];
						VON_PUNKT[k] = j;
					}
				}
			}
			int fikscount = 0; //проверка, пройдены ли все вершины
			for (int i = 0; i < N; i++)	
				if (FIKS[i] == 1) 
					fikscount++;
			if (fikscount == N) 
				fikscheck = false;
		}
		//ВЫДАЧА
		int z = VON_PUNKT[end];
		bool check = true;
		int OUTPUT[N]; //массив для записи порядка прохождения
		int op = 0;
		while (check)
		{
			OUTPUT[op] = z;
			op++;
			z = VON_PUNKT[z];
			if (z == 0) 
				check = false;
		}
		ofstream f("OUTPUT.txt"); //запись в файл
		f << start + 1 << ", " << end + 1;
		for (int i = op - 1; i >= 0; i--)
		{
			if (OUTPUT[i] != start)
				f << ", " << OUTPUT[i] + 1;
		}
		cout << "Краткий путь успешно записан в OUTPUT.txt!" << endl << endl;
	}
}
