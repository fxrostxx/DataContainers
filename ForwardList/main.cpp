#include "stdafx.h"
#include "ForwardList.cpp"

void Print(int arr[])
{
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) / sizeof(arr[0]) << endl;
}


//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define ITERATORS_CHECK

int main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;

	for (int i = 0; i < n; ++i)
	{
		list.push_back(rand() % 100);
	}

	list.print();

	/*list.push_back(456);

	list.push_front(123);

	list.print();

	list.pop_front();

	list.pop_back();

	list.print();

	int index;
	int value;

	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	list.insert(value, index);

	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;

	list.erase(index);

	list.print();*/
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;

	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);

	for (int i = 0; i < list1.get_size(); ++i) cout << list1[i] << tab; cout << endl;

	ForwardList list2;

	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	for (int i = 0; i < list2.get_size(); ++i) cout << list2[i] << tab; cout << endl;

	ForwardList list3;
	cout << delimeter << endl;
	list3 = list1 + list2;
	cout << delimeter << endl;
	for (int i = 0; i < list3.get_size(); ++i) cout << list3[i] << tab; cout << endl;

	/*int index;
	int value;

	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	list1.insert(value, index);
	list1.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;

	list1.erase(index);
	list1.print();*/
#endif // OPERATOR_PLUS_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;

	clock_t t_start = clock();

	for (int i = 0; i < n; ++i)
	{
		list.push_front(rand() % 100);
	}

	clock_t t_end = clock();

	cout << "ForwardList filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
#endif // PERFORMANCE_CHECK

#ifdef SUBSCRIPT_OPERATOR_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list(n);

	clock_t t_start = clock();
	for (int i = 0; i < list.get_size(); ++i) list[i] = rand() % 100;
	clock_t t_end = clock();

	cout << "Список заполнен за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

	system("PAUSE");

	for (int i = 0; i < list.get_size(); ++i) cout << list[i] << tab;
	cout << endl;
#endif // SUBSCRIPT_OPERATOR_CHECK

#ifdef COPY_SEMANTIC_PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	clock_t t_start, t_end;
	ForwardList list1;

	t_start = clock();
	for (int i = 0; i < n; ++i) list1.push_front(rand() % 100);
	t_end = clock();

	cout << "Список заполнен за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	system("PAUSE");

	t_start = clock();
	ForwardList list2 = list1;
	t_end = clock();

	cout << "Список скопирован за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

	for (int i = 0; i < list1.get_size(); ++i) cout << list1[i] << tab; cout << endl;
	for (int i = 0; i < list2.get_size(); ++i) cout << list2[i] << tab; cout << endl;
#endif // COPY_SEMANTIC_PERFORMANCE_CHECK

#ifdef MOVE_SEMANTIC_CHECK
	ForwardList list1;
	ForwardList list2;

	clock_t t_start = clock();

	for (int i = 0; i < 3000000; ++i) list1.push_front(rand());
	for (int i = 0; i < 3000000; ++i) list2.push_front(rand());

	clock_t t_end = clock();

	cout << "Списки заполнены за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

	system("PAUSE");

	t_start = clock();

	ForwardList list3 = list1 + list2;

	t_end = clock();

	cout << "Списки соединены за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
#endif // MOVE_SEMANTIC_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[]{ 3, 5, 8, 13, 21 };

	cout << sizeof(arr) << endl;
	cout << sizeof(arr[0]) << endl;

	for (int i : arr) cout << i << tab; cout << endl;
	Print(arr);
#endif // RANGE_BASED_FOR_ARRAY

#ifdef ITERATORS_CHECK
	ForwardList<double> list = { 3.1, 5.2, 8.3, 13.4, 21.4 };
	list.print();

	for (double i : list) cout << i << tab; cout << endl;

	cout << delimeter << endl;

	for (Iterator<double> it = list.begin(); it != list.end(); ++it) cout << *it << tab;
	cout << endl;
#endif // ITERATORS_CHECK

	return 0;
}