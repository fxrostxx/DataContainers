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
		Element* New = new Element(Data);

		if (Head == nullptr)
		{
			Head = New;
			return;
		}

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
			Head = nullptr;
			return;
		}

		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
	}
	void pop_back()
	{
		if (Head == nullptr) return;

		if (Head->pNext == nullptr)
		{
			delete Head;
			Head = nullptr;
			return;
		}

		Element* Temp = Head;

		while (Temp->pNext->pNext) Temp = Temp->pNext;

		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int Data, int index)
	{
		if (index == 1 || Head == nullptr)
		{
			push_front(Data);
			return;
		}
		
		Element* Temp = Head;
		int current_index{ 1 };

		while (Temp && current_index < index - 1)
		{
			Temp = Temp->pNext;
			++current_index;
		}

		if (Temp == nullptr)
		{
			cout << "Выход за границы списка" << endl;
			return;
		}

		Element* New = new Element(Data);

		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index)
	{
		if (Head == nullptr) return;

		if (index == 1)
		{
			pop_front();
			return;
		}

		Element* Temp = Head;
		int current_index{ 1 };

		while (Temp && current_index < index - 1)
		{
			Temp = Temp->pNext;
			++current_index;
		}

		if (Temp == nullptr || Temp->pNext == nullptr)
		{
			cout << "Выход за границы списка" << endl;
			return;
		}

		Element* ToDelete = Temp->pNext;
		Temp->pNext = ToDelete->pNext;
		delete ToDelete;
	}

	void print() const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;

	for (int i = 0; i < n; ++i)
	{
		list.push_front(rand() % 100);
	}

	list.push_back(456);

	list.push_front(123);

	list.pop_front();

	list.pop_back();

	list.insert(789, 3);

	list.erase(5);

	list.print();

	return 0;
}