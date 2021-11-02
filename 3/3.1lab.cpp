//односвязный список
#include <iostream>
#include <string>

using namespace std;

int time_to_int(string time)
{
	return stoi(time.substr(0, time.find(':'))) * 60 +
		stoi(time.substr(time.find(':') + 1));
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
	string date; //переменная даты совершения звонка
};
calling inputCalls()//ввод элементов
{
	calling calls;
	cout << "Введите информацию о звонке: " << endl
		<< "Введите номер телефона: ";
	cin >> calls.number;
	cout << "Введите код города:";
	cin >> calls.code;
	cout << "Введите продолжительность разговора (ММ:СС):";
	cin >> calls.time;
	cout << "Введите дату звонка (ДД.ММ.ГГ):";
	cin >> calls.date;
	return calls;
}
struct item //структура элемента
{
	calling data;
	item* next; //ссылка на следующий элемент
};
class OneSideLinkedList
{
private:
	item* head; //Адрес первого элемента списка
	int count; //Количество элементов в списке
public:
	OneSideLinkedList()
	{
		head = NULL;
		count = 0;
	}
	void add_tail(calling a) //добавление элемента в конец списка
	{
		item* tempitem = head;
		item* newitem = new item;
		newitem->data = a;
		if (head == NULL)
		{
			newitem->next = NULL;
			head = newitem;
		}
		else
		{
			while (tempitem->next != NULL) tempitem = tempitem->next;
			tempitem->next = newitem;
			newitem->next = NULL;
		}
		count++;
	}
	void add_head(calling a) //добавление в начало списка
	{
		item* newitem = new item;
		newitem->data = a;
		if (head == NULL)
		{
			newitem->next = NULL;
			head = newitem;
		}
		else
		{
			newitem->next = head;
			head = newitem;
		}
		count++;
	}
	void fill() //заполнение списка
	{
		int N;
		cout << "Введите количество звонков:";
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cout << "Звонок №" << i + 1 << endl;
			add_tail(inputCalls());
		}
	}
	void delete_tail() //удаление последнего элемента
	{
		item* tempitem = head;
		if (head != NULL)
		{
			if (head->next != NULL)
			{
				while (tempitem->next->next != NULL) tempitem = tempitem->next;
				{
					tempitem->next = NULL;
				}
			}
			else
			{
				head = NULL;
			}
		}
		count--;
	}
	void delete_head() //удаление головы
	{
		item* tempitem = new item;
		if (head != NULL)
		{
			if (head->next != NULL)
			{
				tempitem = head;
				head = tempitem->next;
			}
			else
			{
				head = NULL;
			}
		}
		count--;
	}
	item* search() //поиск адреса элемента по значению данных
	{
		cout << "Введите поле для поиска:" <<
			"1 - номер телефона" << endl <<
			"2 - код города" << endl <<
			"3 - продолжительность звонка" << endl <<
			"4 - дата звонка" << endl;
		item* search = head;
		item* found = new item;
		string searchfield;
		int searchcount = 0, max = 0, min = 9999999;
		int finder;
		cin >> finder;
		switch (finder)
		{
		case 1:
			cout << "Введите номер телефона: ";
			cin >> searchfield;
			while (search != NULL)
			{
				searchcount = abs(stoi(searchfield) - search->data.number);;
				if (searchcount < min)
				{
					min = searchcount;
					found = search;
				}
				search = search->next;
			}
			break;
		case 2:
			cout << "Введите код города: ";
			cin >> searchfield;
			while (search != NULL)
			{
				searchcount = abs(stoi(searchfield) - search->data.code);;
				if (searchcount < min) {
					min = searchcount;
					found = search;
				}
				search = search->next;
			}
			break;
		case 3:
			int time1, time2;
			cout << "Введите время (ММ:СС) ";
			cin >> searchfield;
			while (search != NULL)
			{
				time1 = time_to_int(searchfield);
				time2 = time_to_int(search->data.time);
				searchcount = abs(time1 - time2);
				if (searchcount < min) {
					min = searchcount;
					found = search;
				}
				search = search->next;
			}
			break;
		case 4:
			int date1, date2;
			cout << "Введите дату (ДД.ММ.ГГ): ";
			cin >> searchfield;
			while (search != NULL)
			{
				date1 = date_to_int(searchfield);
				date2 = date_to_int(search->data.date);
				searchcount = abs(date1 - date2);
				if (searchcount < min) {
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
		if (place->next != NULL)
		{
			newitem->next = place->next;
			place->next = newitem;
		}
		else
		{
			newitem->next = NULL;
			place->next = newitem;
		}
		count++;
	}
	void delete_item(item* place) //удаление найденного элемента
	{
		item* newitem = new item;
		if (place == head) delete_head();
		else if (place->next == NULL) delete_tail();
		else
		{
			while (newitem->next != place)
			{
				newitem = newitem->next;
			}
			newitem->next = newitem->next->next;
		}
		count--;
	}
	void output()
	{
		item* outputitem = head;
		while (outputitem != NULL)
		{
			cout << "-----------------------------------" << endl;
			cout << "Номер телефона: " << outputitem->data.number << endl
				<< "Код города: " << outputitem->data.code << endl
				<< "Продолжительность звонка: " << outputitem->data.time << endl
				<< "Дата совершенного звонка: " << outputitem->data.date << endl;
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
			<< "Дата совершенного звонка: " << outputitem->data.date << endl;
		cout << "-----------------------------------" << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	OneSideLinkedList one;
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
			<< "6) Поиск эл-та по заданному значению поля структуры" << endl
			<< "7) Добавление элемента после найденного" << endl
			<< "8) Удаление найденного элемента" << endl
			<< "0) Выход из программы" << endl
			<< "------------------------------------------------------" << endl
			<< "Выберите действие: ";
		cin >> menu;
		switch (menu)
		{
		case 1: one.fill(); one.output(); break;
		case 2: one.add_tail(inputCalls()); one.output(); break;
		case 3: one.add_head(inputCalls()); one.output(); break;
		case 4: one.delete_tail(); one.output(); break;
		case 5: one.delete_head(); one.output(); break;
		case 6: cout << "Найденный элемент:" << endl; one.output(one.search()); break;
		case 7: one.add_after(one.search(), inputCalls()); one.output(); break;
		case 8: one.delete_item(one.search()); one.output(); break;
		case 0: working = false; break;
		}
	}
}
