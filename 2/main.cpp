#include"Header.h"
void main()
{

	setlocale(LC_ALL, "Russian");
	bool working = true;
	int menu = -1;
	Database flight_db(10);
	int index = 0;
	int field = 0;
	string value;
	//flight_db.write_All_A();
	//flight_db.fill_database();
	//flight_db.write_All_A();

	//Выбор действий
	while (working)
	{
		cout << endl
			<< "-------------МЕНЮ-------------" << endl
			<< "1: Удалить элемент" << endl
			<< "2: Найти свободную переменную" << endl
			<< "3: Добавить элемент" << endl
			<< "4: Вывод элемента" << endl
			<< "5: Вывод всех элементов" << endl
			<< "6: Поиск элемента с заданным значением поля" << endl
			<< "7: Поиск элемента с минимальным значением поля" << endl
			<< "8: Сортировка А-Я" << endl
			<< "9: Сортировка Я-А" << endl
			<< "10: Очистка файла" << endl
			<< "11: Запись в файл" << endl
			<< "12: Чтение и отображение" << endl
			<< "0: Выход из программы" << endl
			<< "------------------------------" << endl
			<< "Выберите действие: ";
		cin >> menu;
		cout << endl;
		switch (menu)
		{
		case 1: // Удаление элемента 
			cout << "Введите индекс: "; cin >> index;
			flight_db.empty_item(index);
			cout << "Элемент удалён!" << endl;
			break;

		case 2: // Поиск свободной структурной переменной
			flight_db.free_struct_var();
			break;

		case 3: // Ввод элементов структуры с клавиатуры
			cout << "Какое количество звонков вы хотите добавить?" << endl << "Введите число: ";
			int N;  cin >> N;
			for (int i = 0; i < N; i++) {
				flight_db.input_struct_var(i);
				cout << endl;
			}
			break;
		case 4: // Вывод элемента на экран (по индексу)
			cout << "Введите элемент: ";
			cin >> index;
			cout << "Данные элемента " << index << ":" << endl;
			flight_db.output_struct_var(index);
			cout << endl;
			break;

		case 5: // Вывод всех элементов на экран
			cout << "Данные всех элементов:" << endl;
			flight_db.output_all();
			cout << endl;
			break;

		case 6:	// Поиск в массиве структур элемента с заданным значением
			cout << "Поиск по элементам" << endl
				<< "0: Номер телефона" << endl
				<< "1: Код города" << endl
				<< "2: Продолжительность звонка" << endl
				<< "3: Дата звонка" << endl
				<< "Выберите критерий для поиска(0-3): ";
			cin >> field;
			cout << "Введите значение для поиска: ";
			cin >> value;
			flight_db.search_item(field, value);
			cout << endl;
			break;

		case 7: // Поиск минимального значения по заданному полю
			cout << "Поиск по минимальному значению" << endl
				<< "0: Номер телефона" << endl
				<< "1: Код города" << endl
				<< "2: Продолжительность звонка" << endl
				<< "3: Дата звонка" << endl
				<< "Выберите критерий для поиска(0-3): ";
			cin >> field;
			flight_db.search_min_item(field);
			cout << endl;
			break;

		case 8: // Сортировка от меньшего к большему
			cout << "Сортировка А-Я" << endl
				<< "0: Номер телефона" << endl
				<< "1: Код города" << endl
				<< "2: Продолжительность звонка" << endl
				<< "3: Дата звонка" << endl
				<< "Выберите критерий для поиска(0-3): ";
			cin >> field;
			flight_db.sort_min_to_max(field);
			cout << endl;
			break;

		case 9: // Сортировка от большего к меньшему
			cout << "Сортировка Я-А" << endl
				<< "0: Номер телефона" << endl
				<< "1: Код города" << endl
				<< "2: Продолжительность звонка" << endl
				<< "3: Дата звонка" << endl
				<< "Выберите критерий для поиска(0-3): ";
			cin >> field;
			flight_db.sort_max_to_min(field);
			cout << endl;
			break;

		case 10: // Очистка файла
			flight_db.file_clear();
			break;

		case 11: // Запись данных в файл
			flight_db.write_in_file();
			break;

		case 12: // Чтение и вывод на экран данных из файла
			//flight_db.read_from_file();
			flight_db.fill_database();
			flight_db.dbDump();
			break;

		case 0: // Выход из программы
			cout << "Программа завершена" << endl;
			working = false;
			break;

		default:
			cout << "Неверный ввод. Попробуйте ещё раз." << endl;
			break;
		}
	}
}
