#include <iostream>
#include <fstream>

using namespace std;
const int N = 11;
struct item {
	item* next;
	item* prev;
	int data;
};
class queue {
private:
	item* first; //Адрес первого элемента списка
	item* last; //Адрес последнего элемента списка
	int count; //Количество элементов в списке
public:
	queue()
	{
		last = NULL;
		first = NULL;
		count = 0;
	}
	void push(int a) //Добавление элемента в конец списка
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
	void pop() //Удаление елемента из начала очереди
	{
		item* place = first;
		if (place != last) //Если элемент первый, но НЕ последний
		{
			place->next->prev = NULL;
			first = place->next;
		}
		else //Если элемент первый и последний
		{
			first = NULL;
			last = NULL;
		}
		delete place;
		count--;
	}
	bool empty()  //Возвращает true если очередь пустая и false если нет
	{
		bool empt;
		if (first == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int front() //Возвращает значение из начала очереди
	{
		return first->data;
	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	ofstream output("OUTPUT.txt");
	queue q;    // очередь для хранения номеров вершин
	int schlange; //метка посещённых вершин
	bool besuchtet[N];  // если вершина не в очереди = 0, в очереди = 1
	int A[N][N] =
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
		{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	};   // матрица смежности
	int start, end; // номер стартовой и конечной вершин
	int rang[N]; // длина пути
	int VON_PUNKT[N]; // номер вершины, из которой попали в текущую
	int designing[N]; //конструрирование маршрута

	cout << "Введите начальную вершину (1-11): ";
	cin >> start;
	cout << "Введите конечную вершину (1-11): ";
	cin >> end;
	start--;
	end--;

	for (int i = 0; i < N; i++)
	{
		VON_PUNKT[i] = start;
		rang[i] = 999; // максимальное значение
		besuchtet[i] = false; // все вершины помечаем как непосещенные
	}
	// записываем начальную вершину в очередь
	q.push(start);
	besuchtet[start] = true; // помечаем её как посещенную
	VON_PUNKT[start] = -1; // пришли с условно -1
	rang[start] = 0; // начальный ранг равен 0

	while (!q.empty()) // пока очередь не пуста
	{
		schlange = q.front(); // запоминаем первый элемент в очереди
		q.pop(); // выталкиваем его
		for (int i = 0; i < N; i++)
		{
			// если не в очереди и имеется связь
			if (!besuchtet[i] && A[schlange][i])
			{
				q.push(i); // запихиваем в очередь
				besuchtet[i] = true; // помечаем как посещенную
				rang[i] = rang[schlange] + 1; // увеличиваем ранг
				VON_PUNKT[i] = schlange; // номер вершины равен текущей
			}
		}
	}
	designing[0] = end;
	int i = 1;
	do {
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
			cout << designing[i] + 1 << " ";
			i--;
		}
	} while (i >= 0);
	output.close();
}
