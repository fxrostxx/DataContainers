#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n--------------------------------------------\n"

template<typename T> class List
{
private:
	class Element
	{
	private:
		T Data;
		Element* pPrev;
		Element* pNext;
	public:
		Element(T Data, Element* pPrev = nullptr, Element* pNext = nullptr) : Data(Data), pPrev(pPrev), pNext(pNext)
		{
			cout << "EConstructor: " << this << endl;
		}
		~Element()
		{
			cout << "EDestructor: " << this << endl;
		}
		friend class List;
	} *Head, * Tail;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) : Temp(Temp) {}
		~ConstBaseIterator() {}

		bool operator==(const ConstBaseIterator& other) const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other) const
		{
			return this->Temp != other.Temp;
		}
		T operator*() const
		{
			return Temp->Data;
		}
	};
	size_t size;
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp) : ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	ConstIterator begin() const;
	Iterator begin();
	ConstIterator end() const;
	Iterator end();
	ConstReverseIterator rbegin() const;
	ReverseIterator rbegin();
	ConstReverseIterator rend() const;
	ReverseIterator rend();

	List();
	List(int size);
	List(const List<T>& other);
	List(List<T>&& other);
	List(const std::initializer_list<T>& il);
	~List();

	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);

	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, int index);
	void erase(int index);

	void print() const;
	void reverse_print() const;
};

template<typename T> typename List<T>::ConstIterator List<T>::begin() const
{
	return Head;
}
template<typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T> typename List<T>::ConstIterator List<T>::end() const
{
	return nullptr;
}
template<typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>:: rbegin() const
{
	return Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::rend() const
{
	return nullptr;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor: " << this << endl;
}
template<typename T> List<T>::List(int size) : List()
{
	while (size--) push_front(0);
	cout << "LSizeConstructor: " << this << endl;
}
template<typename T> List<T>::List(const List<T>& other) : List()
{
	*this = other;
	cout << "LCopyConstructor: " << this << endl;
}
template<typename T> List<T>::List(List<T>&& other) : List()
{
	*this = std::move(other);
	cout << "LMoveConstructor: " << this << endl;
}
template<typename T>  List<T>::List(const std::initializer_list<T>& il) : List()
{
	for (T const* it = il.begin(); it != il.end(); ++it) push_back(*it);
	cout << "LitConstructor: " << this << endl;
}
template<typename T> List<T>::~List()
{
	while (Head) pop_front();
	cout << "LDestructor: " << this << endl;
}

template<typename T> List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other) return *this;
	while (Head) pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
	cout << "LCopyAssignment: " << this << endl;
	return *this;
}
template<typename T> List<T>& List<T>::operator=(List<T>&& other)
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

template<typename T> void List<T>::push_front(T Data)
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
template<typename T> void List<T>::push_back(T Data)
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
template<typename T> void List<T>::pop_front()
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
template<typename T> void List<T>::pop_back()
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
template<typename T> void List<T>::insert(T Data, int index)
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
template<typename T> void List<T>::erase(int index)
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

template<typename T> void List<T>::print() const
{
	cout << delimeter << endl;
	cout << "Head: " << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail: " << Tail << endl;
	cout << "Количество элементов списка: " << size;
	cout << delimeter << endl;
}
template<typename T> void List<T>::reverse_print() const
{
	cout << delimeter << endl;
	cout << "Tail: " << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Head: " << Head << endl;
	cout << "Количество элементов списка: " << size;
	cout << delimeter << endl;
}

template<typename T> List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> result = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
		result.push_back(*it);
	return result;
}

//#define BASE_CHECK
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

	List<double> d_list = { 2.7, 3.14, 5.8, 8.3 };
	for (double i : d_list) cout << i << tab; cout << endl;

	List<std::string> s_list = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	for (std::string i : s_list) cout << i << ' '; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout << *it << ' ';
	cout << endl;

	return 0;
}