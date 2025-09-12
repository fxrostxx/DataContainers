#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n--------------------------------------------\n"

class List
{
private:
	class Element
	{
	private:
		int Data;
		Element* pPrev;
		Element* pNext;
	public:
		Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr) : Data(Data), pPrev(pPrev), pNext(pNext)
		{
			cout << "EConstructor: " << this << endl;
		}
		~Element()
		{
			cout << "EDestructor: " << this << endl;
		}
		friend class List;
	} *Head, *Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor: " << this << endl;
	}
	~List()
	{
		while (Head) pop_front();
		cout << "LDestructor: " << this << endl;
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (!Head && !Tail) Head = Tail = New;
		else
		{
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;
		}
		++size;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		if (!Head && !Tail) Head = Tail = New;
		else
		{
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;
		}
		++size;
	}
	void pop_front()
	{
		if (!Head && !Tail) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		--size;
	}
	void pop_back()
	{
		if (!Head && !Tail) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		--size;
	}
	void insert(int Data, int index)
	{
		if ((!Head && !Tail)) return push_front(Data);
		if (index < 0) return;
		if (index >= size) return push_back(Data);
		if (index == 0) return push_front(Data);
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = new Element(Data);
		}
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; ++i, Temp = Temp->pNext);
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; ++i, Temp = Temp->pPrev);
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		++size;
	}

	void print()
	{
		cout << delimeter << endl;
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail: " << Tail << endl;
		cout << "Количество элементов списка: " << size;
		cout << delimeter << endl;
	}
	void reverse_print()
	{
		cout << delimeter << endl;
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head: " << Head << endl;
		cout << "Количество элементов списка: " << size;
		cout << delimeter << endl;
	}
};

#define BASE_CHECK
//#define HOMEWORK

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
#endif // BASE_CHECK

#ifdef HOMEWORK
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;

	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;
#endif // HOMEWORK

	return 0;
}