#include <iostream>
#include<Windows.h>

using namespace std;

int N = 10; //размер массива

class Stack {
private:
	int* arr;
	int top;

public:
	Stack() {
		arr = new int[N];
		top = -1;
	}
	Stack(int m) {
		arr = new int[m];
		top = -1;
	}
	void Push(int n) {
		if (top == N - 1) {
			cout << "Стек переполнен\n";
		}
		else {
			top++;
			arr[top] = n;
		}
	}
	int Pop() {
		if (top < 0) {
			cout << "Так, у нас стек пуст\n";
			return 0;
		}
		else {
			int element = arr[top];
			top = -1;
			return element;
		}
	}
};
class Queue {
private:
	int* arr;
	int head;
	int tail;

public:
	Queue() {
		arr = new int[N];
		head = 0;
		tail = 0;
	}
	Queue(int n) {
		arr = new int[n];
		head = 0;
		tail = 0;
	}
	void Put(int newElement) {
		if (head == (tail + 1) % N) {
			cout << "Йоу, у нас очередь переполнена\n";
		}
		else {
			arr[tail] = newElement;
			tail = (tail + 1) % N;
		}
	}
	int Get() {
		if (head != tail) {
			int output = arr[head];
			head = (head + 1) % N;
			return output;
		}
		else {
			cout << "Очередь пустая!\n";
			return 0;
		}
	}
};
int main() {
	int newElement;
	bool a;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 

	cout << "Сколько элементов будет в очереди и стеке?: ";
	cin >> N;
	Stack stack(N);
	Queue queue(N);

	for (int i = 0; i < N + 5; i++) {
		cout << "Чтобы добавить введите 1, чтобы удалить 0: ";
		cin >> a;

		if (a) {
			cout << "Введите значение: ";
			cin >> newElement;
			stack.Push(newElement);
		}
		else {
			int output = stack.Pop();
			cout << "Значение: \n" << output;
			cout << endl;
		}
	}
	for (int i = 0; i < N + 5; i++) {
		cout << "Чтобы добавить введите 1, чтобы удалить 0: ";
		cin >> a;

		if (a) {
			cout << "Введите значение: ";
			cin >> newElement;
			queue.Put(newElement);
		}
		else {
			int output = queue.Get();
			cout << "Значение: " << output;
			cout << endl;
		}
	}
	return 0;
}
