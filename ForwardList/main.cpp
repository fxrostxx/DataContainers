#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
private:
	int data;
	Element* pNext;

public:
	Element(int data, Element* pNext = nullptr)
	{
		this->data = data;
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

	void push_front(int data)
	{
		Element* New = new Element(data);
		New->pNext = Head;
		Head = New;
	}

	void print() const
	{
		Element* temp = Head;
		while (temp)
		{
			cout << temp << tab << temp->data << tab << temp->pNext << endl;
			temp = temp->pNext;
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

	list.print();

	return 0;
}