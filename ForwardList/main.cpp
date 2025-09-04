#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
private:
	int Data;
	Element* pNext;

public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;

		cout << "EConstructor: " << this << endl;
	}
	~Element()
	{
		cout << "EDestructor: " << this << endl;
	}

	friend class ForwardList;
};

class ForwardList
{
private:
	Element* Head;
	int count;

public:
	ForwardList()
	{
		Head = nullptr;
		count = 0;

		cout << "FLConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head != nullptr)
		{
			Element* Temp = Head;
			Head = Head->pNext;
			delete Temp;
		}

		cout << "FLDestructor: " << this << endl;
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);

		New->pNext = Head;

		Head = New;

		++count;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);

		Element* New = new Element(Data);

		Element* Temp = Head;

		while (Temp->pNext) Temp = Temp->pNext;

		Temp->pNext = New;

		++count;
	}
	void pop_front()
	{
		if (Head == nullptr) return;

		if (Head->pNext == nullptr)
		{
			delete Head;
			Head = nullptr;
			--count;
			return;
		}

		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;

		--count;
	}
	void pop_back()
	{
		if (Head == nullptr) return;

		if (Head->pNext == nullptr)
		{
			delete Head;
			Head = nullptr;
			--count;
			return;
		}

		Element* Temp = Head;

		while (Temp->pNext->pNext) Temp = Temp->pNext;

		delete Temp->pNext;
		Temp->pNext = nullptr;

		--count;
	}
	void insert(int Data, int index)
	{
		if (Head == nullptr) return push_front(Data);

		if (index >= count) return push_back(Data);
		if (index <= 0) return push_front(Data);

		Element* Temp = Head;

		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;

		Element* New = new Element(Data);

		New->pNext = Temp->pNext;
		Temp->pNext = New;

		++count;
	}
	void erase(int index)
	{
		if (Head == nullptr) return;

		if (index >= count - 1) return pop_back();
		if (index <= 0) return pop_front();

		Element* Temp = Head;

		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;

		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;

		--count;
	}

	void print() const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}

		cout << "Количество элементов списка: " << count << endl;
	}
};

ForwardList& operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result;
	Element* Temp = left.Head;

	while (Temp)
	{

	}
}

//#define BASE_CHECK
#define COUNT_CHECK

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

#ifdef COUNT_CHECK
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

	cout << "Введите индекс удаляемого элемента: "; cin >> index;

	list1.erase(index);
	list1.print();

	ForwardList fusion = list1 + list2;
	fusion.print();
#endif // COUNT_CHECK


	return 0;
}