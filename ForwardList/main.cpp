#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
private:
	int Data;
	Element* pNext;
	static int count;

public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		++count;

		cout << "EConstructor: " << this << endl;
	}
	~Element()
	{
		--count;

		cout << "EDestructor: " << this << endl;
	}

	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
private:
	Element* Head;

public:
	ForwardList()
	{
		Head = nullptr;

		cout << "FLConstructor: " << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor: " << this << endl;
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);

		New->pNext = Head;

		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);

		Element* New = new Element(Data);

		Element* Temp = Head;

		while (Temp->pNext) Temp = Temp->pNext;

		Temp->pNext = New;
	}
	void pop_front()
	{
		if (Head == nullptr) return;

		if (Head->pNext == nullptr)
		{
			delete Head;
			Head == nullptr;
			return;
		}

		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}
	void pop_back()
	{
		if (Head == nullptr) return;

		if (Head->pNext == nullptr)
		{
			delete Head;
			Head == nullptr;
			return;
		}

		Element* Temp = Head;

		while (Temp->pNext->pNext) Temp = Temp->pNext;

		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int Data, int index)
	{
		if (Head == nullptr) return push_front(Data);

		if (index >= Element::count) return push_back(Data);
		if (index <= Element::count) return push_front(Data);

		Element* Temp = Head;

		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;

		Element* New = new Element(Data);

		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		if (Head == nullptr) return;

		if (index == 1) return pop_front();

		Element* Temp = Head;

		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;

		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
	}

	void print() const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}

		cout << "Количество элементов списка: " << Element::count << endl;
	}
};

//#define BASE_CHECK

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

	list.push_back(456);

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

	list.print();
#endif // BASE_CHECK

	ForwardList list1;

	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);

	list1.print();

	ForwardList list2;

	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list2.print();

	int index;
	int value;

	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	list1.insert(value, index);
	list1.print();

	return 0;
}