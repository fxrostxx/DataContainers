#include "stdafx.h"
#include "List.cpp"

//#define BASE_CHECK
//#define HOMEWORK
#define TEMPLATION_CHECK

int main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list1;
	for (int i = 0; i < n; ++i) list1.push_back(rand() % 100);
	list1.print();
	list1.reverse_print();

	/*list1.pop_back();
	list1.print();
	list1.reverse_print();*/

	int index, value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.insert(value, index);
	list1.print();
	list1.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list1.erase(index);
	list1.print();
	list1.reverse_print();
#endif // BASE_CHECK

#ifdef HOMEWORK
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	list1.print();
	list2.print();

	List<int> list3 = list1 + list2;
	list3.print();

	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;

	for (List<int>::ConstIterator it = list1.begin(); it != list1.end(); ++it)
		cout << *it << tab;
	cout << endl;
	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) *it *= 100;
	for (List<int>::ConstReverseIterator it = list1.rbegin(); it != list1.rend(); ++it)
		cout << *it << tab;
	cout << endl;
#endif // HOMEWORK

#ifdef TEMPLATION_CHECK
	List<double> d_list = { 2.7, 3.14, 5.8, 8.3 };
	for (double i : d_list) cout << i << tab; cout << endl;

	List<std::string> s_list = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	for (std::string i : s_list) cout << i << ' '; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout << *it << ' ';
	cout << endl;
#endif // TEMPLATION_CHECK


	return 0;
}