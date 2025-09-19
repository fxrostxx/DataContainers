#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void elevator(int floor);

int main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "������� ����� �����: "; cin >> n;
	elevator(n);

	return 0;
}

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "�� � �������" << endl;
		return;
	}
	cout << "�� �� " << floor << " �����" << endl;
	elevator(floor - 1);
	cout << "�� �� " << floor << " �����" << endl;
}