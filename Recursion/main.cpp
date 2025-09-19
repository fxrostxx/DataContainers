#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void elevator(int floor);

int main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);

	return 0;
}

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}