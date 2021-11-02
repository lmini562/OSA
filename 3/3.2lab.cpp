//двусвязный список
#include <iostream>
#include <string>

using namespace std;

int time_to_int(string time)
{
	return stoi(time.substr(0, time.find(':'))) * 60
		+ stoi(time.substr(time.find(':') + 1));
}
int date_to_int(string date)
{
	return stoi(date.substr(0, date.find('.'))) //день
		+ stoi(date.substr(date.find('.') + 1).substr(0, date.find('.'))) * 30 //месяц
		+ stoi(date.substr(date.find_last_of('.') + 1)) * 365; //год
}
struct calling
{
	int number; //переменная номера телефона
	int code; //переменная кода города
	string time; //переменная продолжительности звонка
	string date; //переменная даты звонка
};
calling inputFlight()
{
	calling fl;
	cout << "Введите информацию о телефонном звонке:" << endl
		<< "Введите номер телефона: ";
	cin >> fl.number;
	cout << "Введите код города: ";
	cin >> fl.code;
	cout << "Введите продолжительность звонка (ММ:СС): ";
	cin >> fl.time;
	cout << "Введите дату звонка (ДД.ММ.ГГ): ";
	cin >> fl.date;
	return fl;
}
struct item //структура элемента
{
	calling data;
	item* next; //ссылка на следующий элемент
	item* prev; //ссылка на предыдущий элемент (в двусвязном списке)
};
class TwoSidedLinkedList
{
private:
	item* head; //адрес первого элемента списка
	item* tail; //адрес посленего элемента списка
	int count; //количество элементов в списке
public:
	TwoSidedLinkedList()
	{
		tail = NULL;
		head = NULL;
		count = 0;
	}
	void add_tail(calling a) //добавление элемента в конец списка
	{
		item* newitem = new item;
		newitem->data = a;
		if (head == NULL)
		{
			newitem->prev = NULL;
			newitem->next = NULL;
			head = newitem;
			tail = newitem;
		}
		else
		{
			tail->next = newitem;
			newitem->next = NULL;
			newitem->prev = tail;
			tail = newitem;
		}
		count++;
	}
	void add_head(calling a) //добавление в начало списка
	{
		item* newitem = new item;
		newitem->data = a;
		if (head == NULL)
		{
			newitem->prev = NULL;
			newitem->next = NULL;
			head = newitem;
			tail = newitem;
		}
		else
		{
			head->prev = newitem;
			newitem->next = head;
			newitem->prev = NULL;
			head = newitem;
		}
		count++;
	}
	void fill() //заполнение списка
	{
		int N;
		cout << "Введите количество звонков для добавления: ";
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cout << "Звонок №" << i + 1 << endl;
			add_tail(inputFlight());
		}
	}
	void delete_tail() //удаление конца списка
	{
		item* tempitem = new item;
		if (head != NULL)
		{
			if (tail != head)
			{
				tempitem = tail;
				tail = tempitem->prev;
				tail->next = NULL;
			}
			else
			{
				head = NULL;
				tail = NULL;
			}
		}
		count--;
		delete tempitem;
	}
	void delete_head() //удаление начала списка
	{
		item* tempitem = new item;
		if (head != NULL)
		{
			if (tail != head)
			{
				tempitem = head;
				head = tempitem->next;
				head->prev = NULL;
			}
			else
			{
				head = NULL;
				tail = NULL;
			}
		}
		count--;
		delete tempitem;
	}
	item* search() //поиск адреса элемента по значению данных
	{
		cout << "Введите поле для поиска:" << endl
			<< "1 - номер телефона" << endl
			<< "2 - код города" << endl
			<< "3 - продолжительность звонка" << endl
			<< "4 - дата звонка" << endl;
		item* search = head;
		item* found = new item;
		string searchfield;
		int searchcount = 0, max = 0, min = 9999999;
		int finder;
		cin >> finder;
		switch (finder)
		{
		case 1: 
			cout << "Введите номер телефона для поиска: ";
			cin >> searchfield;
			while (search != NULL)
			{
				searchcount = abs(stoi(searchfield) - search->data.number);
				if (searchcount < min)
				{
					min = searchcount;
					found = search;
				}
				search = search->next;
			}
			break;
		case 2:
			cout << "Введите код города для поиска: ";
			cin >> searchfield;
			while (search != NULL)
			{
				searchcount = abs(stoi(searchfield) - search->data.code);
				if (searchcount < min)
				{
					min = searchcount;
					found = search;
				}
				search = search->next;
			}
			break;
		case 3:
			int time1, time2;
			cout << "Введите время для поиска (ММ:СС): ";
			cin >> searchfield;
			while (search != NULL)
			{
				time1 = time_to_int(searchfield);
				time2 = time_to_int(search->data.time);
				searchcount = abs(time1 - time2);
				if (searchcount < min)
				{
					min = searchcount;
					found = search;
				}
				search = search->next;
			}
			break;
		case 4:
			int date1, date2;
			cout << "Введите дату для поиска (ДД.ММ.ГГ): ";
			cin >> searchfield;
			while (search != NULL)
			{
				date1 = date_to_int(searchfield);
				date2 = date_to_int(search->data.date);
				searchcount = abs(date1 - date2);
				if (searchcount < min)
				{
					min = searchcount;
					found = search;
				}
				search = search->next;
			}
			break;
		}
		return found;
	}
	void add_after(item* place, calling a) //добавление элемента после найденного
	{
		item* newitem = new item;
		newitem->data = a;
		newitem->prev = place;
		if (place->next != NULL)
		{
			newitem->next = place->next;
			place->next->prev = newitem;
			place->next = newitem;
		}
		else
		{
			newitem->next = NULL;
			place->next = newitem;
			tail = newitem;
		}
		count++;
	}
	void delete_item(item* place) //удаление найденного
	{
		item* newitem = new item;
		if (place == head)
			delete_head();
		else if (place == tail)
			delete_tail();
		else
		{
			place->next->prev = place->prev;
			place->prev->next = place->next;
			delete place;
		}	
		count--;
	}
	void output() //вывод списка
	{
		item* outputitem = head;
		while(outputitem != NULL)
		{
			cout << "-----------------------------------" << endl;
			cout << "Номер телефона: " << outputitem->data.number << endl
				<< "Код города: " << outputitem->data.code << endl
				<< "Продолжительность звонка: " << outputitem->data.time << endl
				<< "Дата звонка: " << outputitem->data.date << endl;
			cout << "-----------------------------------" << endl;
			outputitem = outputitem->next;
		}
	}
	void output(item* outputitem)
	{
		cout << "-----------------------------------" << endl;
		cout << "Номер телефона: " << outputitem->data.number << endl
			<< "Код города: " << outputitem->data.code << endl
			<< "Продолжительность звонка: " << outputitem->data.time << endl
			<< "Дата звонка: " << outputitem->data.date << endl;
		cout << "-----------------------------------" << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	TwoSidedLinkedList two;
	bool working = true;
	int menu;
	while (working)
	{
		cout << endl << "-------------------------МЕНЮ-------------------------" << endl
			<< "1) Создание списка" << endl
			<< "2) Добавить элемент в конец" << endl
			<< "3) Добавить элемент в начало" << endl
			<< "4) Удалить конечный элемент" << endl
			<< "5) Удалить начальный элемент" << endl
			<< "6) Поиск элемента по заданному значению поля структуры" << endl
			<< "7) Добавление элемента после найденного" << endl
			<< "8) Удаление найденного элемента" << endl
			<< "0) Выход из программы" << endl
			<< "------------------------------------------------------" << endl
			<< "Выберите действие: ";
		cin >> menu;
		switch (menu)
		{
		case 1: two.fill(); two.output(); break;
		case 2: two.add_tail(inputFlight()); two.output(); break;
		case 3: two.add_head(inputFlight()); two.output(); break;
		case 4: two.delete_tail(); two.output(); break;
		case 5: two.delete_head(); two.output(); break;
		case 6: cout << "Найденный элемент: " << endl; two.output(two.search()); break;
		case 7: two.add_after(two.search(), inputFlight()); two.output(); break;
		case 8: two.delete_item(two.search()); two.output(); break;
		case 0: working = false; break;
		}
	}
}
