#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void elevator(int floor);
unsigned long long int Factorial(int n);
double Power(int n, int power);
void Fibonacci(unsigned int n, unsigned int a = 0, unsigned int b = 1);

int main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);

	cout << "Введите число: "; cin >> n;
	cout << n << "! = " << Factorial(n) << endl;

	int power;
	cout << "Введите число: "; cin >> n;
	cout << "Введите степень: "; cin >> power;
	cout << n << "^" << power << " = " << Power(n, power) << endl;

	unsigned int a;
	while (true)
	{
		cout << "Введите число до которого вывести ряд Фибоначчи: "; cin >> a;
		Fibonacci(a);
		cout << endl;
	}

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
unsigned long long int Factorial(int n)
{
	if (n < 0) return 0;
	if (n == 0 || n == 1) return 1;
	return (unsigned long long int)n * Factorial(n - 1);
}
double Power(int n, int power)
{
	if (!power) return 1;
	if (power < 0) return (double)1 / Power(n, -power);
	return n * Power(n, power - 1);
}
void Fibonacci(unsigned int n, unsigned int a, unsigned int b)
{
	if (n == 0)
	{
		cout << 0;
		return;
	}
	unsigned int c = a + b;
	if (c > n) return;
	if (c == 1) cout << a << ' ' << b << ' ';
	cout << c << ' ';
	Fibonacci(n, b, c);
}