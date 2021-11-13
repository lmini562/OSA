#include <iostream> 
#include <string> 
#include <fstream> 
#include <math.h>

using namespace std;
struct calling //название структуры рейсов
{
	bool flag = false; //переменная, проверяющая нализиче записи
	int number = 0; //переменная номера телефона
	int code; //переменная кода города
	string time; //переменная продолжительности разговора
	string date; //переменная даты разговора
};
int time_to_int(string time)
{
	return stoi(time.substr(0, time.find(':'))) * 60 * 60 //часы
		+ stoi(time.substr(time.find(':') + 1).substr(0, time.find('.'))) * 60 //минуты
		+ stoi(time.substr(time.find_last_of(':') + 1)); //секунды
}
int date_to_int(string date)
{
	return stoi(date.substr(0, date.find('.'))) //день
		+ stoi(date.substr(date.find('.') + 1).substr(0, date.find('.'))) * 30 //месяц
		+ stoi(date.substr(date.find_last_of('.') + 1)) * 365; //год
}

class Database
{
private:
	int N = 3;
	calling* a = new calling[N];
public:
	Database(int number) :N(number) {}
	~Database()
	{
		delete[]a;
	}
	//удаление элемента
	void empty_item(int index)
	{
		if (a[index].flag == false)
		{
			cout << "Элемент удален!" << endl;
		}
		else
		{
			a[index].number = 0;
			a[index].code = 0;
			a[index].time = "";
			a[index].date = "";
			a[index].flag = false;
		}
		return;
	}
	//Поиск свободной структурной переменной
	void free_struct_var()
	{
		for (int i = 0; i < N; i++)
		{
			if (a[i].flag == false)
			{
				cout << "Место №" << i << "свободно" << endl;
				break;
			}
		}
		return;
	}
	//Запись данных в структуру
	void input_struct_var(int index)
	{
		calling call;
		cout << "Введите информацию о телефонном звонке №" << index + 1 << ":" << endl << "Введите номер телефона: ";
		cin >> call.number;
		cout << "Введите код города: ";
		cin >> call.code;
		cout << "Введите продолжительность звонка (ЧЧ:ММ:СС): ";
		cin >> call.time;
		cout << "Введите дату совершенного звонка (ДД.ММ.ГГ): ";
		cin >> call.date;

		a[index].flag = true;
		a[index].number = call.number;
		a[index].code = call.code;
		a[index].time = call.time;
		a[index].date = call.date;
		return;
	}
	//Вывод элемента по индексу
	void output_struct_var(int index)
	{
		cout << "---------------------------------" << endl;
		cout << "Номер телефона: " << a[index].number << endl
			<< "Код города: " << a[index].code << endl
			<< "Продолжительность звонка: " << a[index].time << endl
			<< "Дата звонка: " << a[index].date << endl;
		cout << "---------------------------------" << endl;
		return;
	}
	//Вывод всех элементов
	void output_all()
	{
		cout << "---------------------------------" << endl;
		for (int i = 0; i < N; i++)
		{
			if (a[i].flag == true)
			{
				cout << "Номер телефона: " << a[i].number << endl
					<< "Код города: " << a[i].code << endl
					<< "Продолжительность звонка: " << a[i].time << endl
					<< "Дата звонка: " << a[i].date << endl;
				cout << "---------------------------------" << endl;
			}
		}
		return;
	}
	//Найти элемент с указанным значение поля
	void search_item(int field, string item)
	{
		int count = 0;
		int max = 0;
		int min = 9999999;
		string maxstr;
		string name_of_field;
		int required_item_index = 0;
		switch (field)
		{
		case 0:
			for (int i = 0; i < N; i++)
			{
				if (a[i].flag)
				{
					count = abs(stoi(item) - a[i].number);
					if (count < min)
					{
						min = count;
						maxstr = a[i].number;
						required_item_index = i;
					}
					count = 0;
				}
			}
			break;
		case 1:
			for (int i = 0; i < N; i++)
			{
				if (a[i].flag)
				{
					count = abs(stoi(item) - a[i].code);
					if (count < min)
					{
						min = count;
						maxstr = a[i].code;
						required_item_index = i;
					}
					count = 0;
				}
			}
			break;
		case 2:
			int time1, time2;
			for (int i = 0; i < N; i++) {
				if (a[i].flag)
				{
					time1 = time_to_int(item);
					time2 = time_to_int(a[i].time);
					count = abs(time1 - time2);
					if (count < min) {
						min = count;
						maxstr = a[i].time;
						required_item_index = i;
					}
					count = 0;
				}
			}
			break;
		case 3:
			int date1, date2;
			for (int i = 0; i < N; i++) {
				if (a[i].flag)
				{
					date1 = date_to_int(item);
					date2 = date_to_int(a[i].date);
					count = abs(date1 - date2);
					if (count < min) {
						min = count;
						maxstr = a[i].date;
						required_item_index = i;
					}
					count = 0;
				}
			}
			break;
		default:
			cout << "Неизвестное поле. Попробуйте ещё раз." << endl;
			break;
		}
		cout << "Самый ближайший подходящий элемент: " << endl;
		output_struct_var(required_item_index);
		return;
	}
	//Найти элемент с минимальным значением поля
	void search_min_item(int field)
	{
		string name_of_field;
		string min;
		calling* calls = new calling[N];
		int count = 0;
		for (int i = 0; i < N; i++) {
			if (a[i].flag) {
				calls[count] = a[i];
				count++;
			}
		}
		int min2;
		switch (field) {
		case 0:
			name_of_field = "НОМЕР ТЕЛЕФОНА";
			min2 = calls[0].number;
			for (int i = 0; i < count; i++) {
				if (min2 > calls[i + 1].number) {
					min2 = calls[i + 1].number;
				}
			}
			min = to_string(min2);
			break;
		case 1:
			name_of_field = "КОД ГОРОДА";
			min2 = calls[0].code;
			for (int i = 0; i < count; i++) {
				if (min2 > calls[i + 1].code) {
					min2 = calls[i + 1].code;
				}
			}
			min = to_string(min2);
			break;
		case 2:
			name_of_field = "ДЛИТЕЛЬНОСТЬ ЗВОНКА";
			int min2;
			min = calls[0].time;
			min2 = time_to_int(min);
			for (int i = 0; i < count; i++) {
				if (min2 > time_to_int(a[i + 1].time)) {
					min2 = time_to_int(a[i + 1].time);
					min = calls[i + 1].time;
				}
			}
			break;
		case 3:
			name_of_field = "ДАТА СОВЕРШЕННОГО 3ВОНКА";
			min = calls[0].date;
			min2 = date_to_int(min);
			for (int i = 0; i < count; i++) {
				if (min2 > date_to_int(a[i + 1].date)) {
					min2 = date_to_int(a[i + 1].date);
					min = calls[i + 1].date;
				}
			}
			break;
		default:
			cout << "Неизвестное поле. Попробуйте ещё раз." << endl;
			break;
		}
		cout << "Минимальное значение поля " << name_of_field << ": " << min << endl;
		delete[] calls;
		return;
	}
	//Сортировка от меньшего к большему по выбранному полю
	void sort_min_to_max(int field)
	{
		calling calls;
		switch (field)
		{
		case 0:
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (a[i].number < a[j].number)
					{
						calls = a[i];
						a[i] = a[j];
						a[j] = calls;
					}
				}
			}
			break;
		case 1:
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (a[i].code < a[j].code)
					{
						calls = a[i];
						a[i] = a[j];
						a[j] = calls;
					}
				}
			}
			break;
		case 2:
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (time_to_int(a[i].time) < time_to_int(a[j].time))
					{
						calls = a[i];
						a[i] = a[j];
						a[j] = calls;
					}
				}
			}
			break;
		case 3:
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (date_to_int(a[i].date) < date_to_int(a[j].date))
					{
						calls = a[i];
						a[i] = a[j];
						a[j] = calls;
					}
				}
			}
			break;
		default:
			cout << "Неизвестное поле. Попробуйте ещё раз." << endl;
			break;
		}
		output_all();
		return;
	}
	//Сортиртивка от большего к меньшему по выбранному полю
	void sort_max_to_min(int field)
	{
		calling calls;
		switch (field)
		{
		case 0:
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (a[i].number > a[j].number) {
						calls = a[i];
						a[i] = a[j];
						a[j] = calls;
					}
				}
			}
			break;
		case 1:
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (a[i].code > a[j].code) {
						calls = a[i];
						a[i] = a[j];
						a[j] = calls;
					}
				}
			}
			break;
		case 2:
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (time_to_int(a[i].time) > time_to_int(a[j].time)) {
						calls = a[i];
						a[i] = a[j];
						a[j] = calls;
					}
				}
			}
			break;
		case 3:
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (date_to_int(a[i].date) > date_to_int(a[j].date)) {
						calls = a[i];
						a[i] = a[j];
						a[j] = calls;
					}
				}
			}
			break;
		default:
			cout << "Неизвестное поле. Попробуйте ещё раз." << endl;
			break;
		}
		output_all();
		return;
	}
	//Запись данных в файл
	void write_in_file()
	{
		string tr = "\n";
		ofstream file("database.txt");
		for (int i = 0; i < N; i++)
		{
			if (a[i].flag)
			{
				file << to_string(a[i].number) + tr;
				file << to_string(a[i].code) + tr;
				file << a[i].time + tr;
				file << a[i].date + tr;
				file << endl;
			}
		}
		file.close();
		cout << "Информация записанна в файл database.txt" << endl;
		return;
	}
	//Чтение данных из файла
	void read_from_file()      ////////////////////////////////////////////////////////////////////   ОРИГИНАЛ
	{
		string line;
		ifstream file("database.txt");
		cout << "Информация из файла database.txt" << endl;
		while (getline(file, line))
		{
			cout << line << endl; //записывать данные в массив а[N]
		}
		file.close();
		return;
	}
	void fill_database()
	{
		ifstream file("database.txt");

		for (int i = 0; i < N; i++)
		{
			file >> this->a[i].number;
			file >> this->a[i].code;
			file >> this->a[i].time;
			file >> this->a[i].date;
			if (this->a[i].number != 0)
				this->a[i].flag = true;
		}
		file.close();
		return;
	}
	//Очистка файла
	void file_clear()
	{
		ofstream file("database.txt");
		file.write("", 0);
		file.close();
		cout << "Файл database.txt успешно очищен" << endl;
		return;
	}
	void dbDump()
	{

		for (int i = 0; i < N; i++)
		{
			if (this->a[i].flag)
			{
				cout << "i = " << i << '\n';
				cout << this->a[i].number << '\n';
				cout << this->a[i].code << '\n';
				cout << this->a[i].time << '\n';
				cout << this->a[i].date << '\n';
			}
			else
				cout << "i = " << i << '\n' << "empty" << '\n';
		}
		return;
	}
};
