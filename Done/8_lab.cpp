#include<iostream>
#include<fstream>
using namespace std;
#define N 8

class Stack //класс стек
{
private:
    int* mas; //стек
    int size, sp; //скин хед (голово)
public:
    Stack(int size) :size(size), sp(-1)
    {
        mas = new int[size];
    }
    ~Stack()
    {
        delete[] mas;
    }
    bool push(int value); //добавление элемента в стек
    int pop(); //извечение элемента из стека
    bool empty(); //проверка стека на отстутствие элементов
    bool no_value(int); //проверка отстутствия элемента
};
bool Stack::push(int value)
{
    if (sp == size - 1)
    {
        return 0; //стек полон
    }
    mas[++sp] = value;
    return 1; //элемент добавлен
}
int Stack::pop()
{
    if (sp == -1)
    {
        return -1; //стек пуст
    }
    return mas[sp--]; //возврат извлеченного элемента
}
bool Stack::empty()
{
    if (sp == -1)
    {
        return 1; //стек пуст
    }
    return 0;
}
bool Stack::no_value(int value)
{
    if (sp == -1) //если стек пуст
    {
        return 1; //элемента нет
    }
    for (int i = 0; i <= sp; i++)
    {
        if (mas[i] == value) //элемент есть
            return 0;
    }
    return 1; //элемента нет
}
class graph //наш граф
{
private:
    int matrix[N][N] =
    {
         {0, 1, 1, 0, 0, 1, 1, 1},
         {1, 0, 0, 0, 0, 0, 0, 1},
         {1, 0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 1, 1, 0, 0},
         {0, 0, 0, 1, 0, 1, 1, 1},
         {1, 0, 0, 1, 1, 0, 0, 0},
         {1, 0, 0, 0, 1, 0, 0, 0},
         {1, 1, 1, 0, 1, 0, 0, 0}
    }; //матрица смежности
    int cost[N][N]; //массив начальных меток вершин для всех вариантов стартовых вершин
    int* parent; //массив родительских вершин
    int start; //стартовая вершина
    int const count; //количество вершин
    int distance[N]; //массив пути от стартовой вершины (расстояния)
    int* visited; //массив пройденных вершин
public:
    graph() :start(-2), count(N) //конструктор с параметрами
    {
        parent = new int[N];
        visited = new int[N];
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if (matrix[i][j] == 0)
                    cost[i][j] = 99999;
                else
                    cost[i][j] = matrix[i][j];
            }
        }
    }
    ~graph() //деструктор
    {
        delete[] parent;
        delete[] visited;
    }
    int depth(int sstart, int finish, int* way); //алгоритм поиска в глубину для внешнего вызова
    void depth_insert(); //алгоритм поиска в глубину для вызова из depth()
};
//метод, реализующий алгоритм поиска в глубину для внешнего вызова
int graph::depth(int sstart, int finish, int* way)
{
    if (sstart != start) //если массив родительских вершин не заполнен для стартовой вершины
    {
        start = sstart;
        depth_insert();
    }
    for (int i = 0; i < count; i++) //заполняем массив несуществующими номерами вершин (-1)
    {
        way[i] = -1;
    }
    int i = finish, j = 0;
    way[j++] = finish;
    while (i != sstart) //записываем в way пути в обратном порядке (от конечной к начальной)
    {
        way[j] = parent[i];
        j++;
        i = parent[i];
    }
    j--;
    i = 0;
    int buff;
    while (i < j) //меняем порядок следования элементов пути от стартовой к финальной
    {
        buff = way[i];
        way[i] = way[j];
        way[j] = buff;
        i++;
        j--;
    }
    return distance[finish];
}
//метод, реализующий алгоритм поиска в глубину из depth()
void graph::depth_insert()
{
    int rang[N]; //массив рангов
    Stack stack{ N }; //стек LIFO
    for (int i = 0; i < N; i++)
    {
        rang[i] = 999; //заполняем массив рангов
        distance[i] = 0; //заполняем массив шага от стартовой вершины
        parent[i] = start; //заполняем массив родительских вершин номером стартовой вершины
        visited[i] = 0; //заполняем массив пройденных вершин
    }
    stack.push(start); //запись в стек начальной вершины
    rang[start] = 0; //ранг стартовой вершины -1
    while (!stack.empty()) //пока стек не пуст
    {
        int visited_node = stack.pop(); //получение текущей вершины из стека
        visited[visited_node] = 1; //отметка о посещении вершины
        int min = 999; //переменная для хранения минимального ранга вершин
        for (int i = count -1; i >=0; i--)
        {
            if (visited[i] && matrix[visited_node][i] && rang[i] < min)
            {
                min = rang[i]; //max - ранг вершин
                parent[visited_node] = i; //вершина назначается родительской вершиной для текущей
                rang[visited_node] = min + 1; //ранг текущей вершины = макс + i
                distance[visited_node] = distance[i] + 1; //расстояние от старта дл текущей i вершины определяется как расстояние от старта до родительской + 1
            }
            if (matrix[visited_node][i] && !visited[i] && stack.no_value(i))
            {
                stack.push(i); //запись в стек вершины
            }
        }
    }
}
int main()
{
    int first, last;
    int mas_parent[N], dist1;
    graph graph;
    cout << "Ented start: ";
    cin >> first;
    cout << "Enter end: ";
    cin >> last;
    dist1 = graph.depth(first, last, mas_parent);
    for (int i = 0; mas_parent[i] >= 0; i++)
    {
        cout << endl << mas_parent[i];
    }
    cout << endl << "Dist1(" << first << " - " << last << ") = " << dist1;
}
