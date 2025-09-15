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
		friend List operator+(const List& left, const List& right);
	} *Head, * Tail;
	size_t size;
public:
	class Iterator
	{
	private:
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) : Temp(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor: " << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor: " << this << endl;
#endif // DEBUG
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other) const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other) const
		{
			return this->Temp != other.Temp;
		}
		int operator*() const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator
	{
	private:
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) : Temp(Temp) {}
		~ReverseIterator() {}

		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const ReverseIterator& other)
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)
		{
			return this->Temp != other.Temp;
		}
		int operator*() const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	const Iterator begin() const
	{
		return Head;
	}
	const Iterator end() const
	{
		return nullptr;
	}
	const ReverseIterator rbegin() const
	{
		return Tail;
	}
	const ReverseIterator rend() const
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor: " << this << endl;
	}
	List(int size) : List()
	{
		while (size--) push_front(0);
		cout << "LSizeConstructor: " << this << endl;
	}
	List(const List& other) : List()
	{
		*this = other;
		cout << "LCopyConstructor: " << this << endl;
	}
	List(List&& other) : List()
	{
		*this = std::move(other);
		cout << "LMoveConstructor: " << this << endl;
	}
	List(const std::initializer_list<int>& il) : List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it) push_back(*it);
		cout << "LitConstructor: " << this << endl;
	}
	~List()
	{
		while (Head) pop_front();
		cout << "LDestructor: " << this << endl;
	}

	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		cout << "LCopyAssignment: " << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "LMoveAssignment: " << this << endl;
		return *this;
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
		if (index < 0 || index > size) return;
		if (index == 0 || size == 0) return push_front(Data);
		if (index == size) return push_back(Data);
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
	void erase(int index)
	{
		if (index < 0 || index >= size) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			--size;
			return;
		}
		if (index == 0) return pop_front();
		if (index == size - 1) return pop_back();
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
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		--size;
	}

	void print() const
	{
		cout << delimeter << endl;
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail: " << Tail << endl;
		cout << "Количество элементов списка: " << size;
		cout << delimeter << endl;
	}
	void reverse_print() const
	{
		cout << delimeter << endl;
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head: " << Head << endl;
		cout << "Количество элементов списка: " << size;
		cout << delimeter << endl;
	}
	friend List operator+(const List& left, const List& right);
};

List operator+(const List& left, const List& right)
{
	List result = left;
	for (List::Iterator it = right.begin(); it != right.end(); ++it)
		result.push_back(*it);
	return result;
}

//#define BASE_CHECK
#define HOMEWORK

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
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	list1.print();
	list2.print();

	List list3 = list1 + list2;
	list3.print();

	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;

	for (List::Iterator it = list1.begin(); it != list1.end(); ++it)
		cout << *it << tab;
	cout << endl;
	for (List::ReverseIterator it = list1.rbegin(); it != list1.rend(); ++it)
		cout << *it << tab;
	cout << endl;
#endif // HOMEWORK

	return 0;
}