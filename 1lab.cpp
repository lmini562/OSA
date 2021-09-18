#include <iostream>
#include<Windows.h>

using namespace std;

int N = 10;

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
};

class Queue {
private:
	int* arr; //указатель на массив
	int head; //переменная начала очереди
	int tail; // переменная для конца очереди

public:
	Queue() //конструктор без аргументов
	{
		arr = new int[N]; 
		head = 0;
		tail = 0;
	}

	Queue(int n) //конструктор с 1 аргументом
	{
		arr = new int[n];
		head = 0;
		tail = 0;
	}

	void Put(int newElement) //добавляем
	{
		if (head == (tail + 1) % N) //если в очереди нет места
		{
			cout << "Очередь переполнена!" << endl; //то очередь переполнена
		}
		else //иначе
		{
			arr[tail] = newElement; //записываем значение в массив
			tail = (tail + 1) % N; //даем хвосту номер последнего эл.
		}
	}

	int Get() //извлекаем
	{
		if (head != tail) //проверяем наличие элементов в очереди
		{
			int output = arr[head]; //выводим первый с головы эл.
			head = (head + 1) % N; //присваеваем голове номер след.эл.
			return output;
		}
		else //иначе
		{
			cout << "Очередь пуста!" << endl;
			return 0;
		}
	}
};

int main() {
	//русификация
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int newElement; //число для ввода
	bool r; //флаг проверки условий

	cout << "Сколько элементов в очереди и стеке?: ";
	cin >> N;
	Stack stack(N);
	Queue queue(N);

	for (int i = 0; i < N + 5; i++)
	{
		cout << "Чтобы добавить введите 1, чтобы удалить 0: ";
		cin >> r;

		if (r)
		{
			cout << "Введите значение: ";
			cin >> newElement;
			stack.Push(newElement); //добавляем
		}
		else
		{
			int output = stack.Pop(); //убираем
			cout << "Значение: " << output;
			cout << endl;
		}

	}

	for (int i = 0; i < N + 5; i++)
	{
		cout << "Чтобы добавить введите 1, чтобы удалить 0: ";
		cin >> r;

		if (r)
		{
			cout << "Введите значение: ";
			cin >> newElement;
			queue.Put(newElement); //добавляем
		}
		else
		{
			int output = queue.Get(); //убираем
			cout << "Значение: " << output;
			cout << endl;
		}

	}

	return 0;
}
