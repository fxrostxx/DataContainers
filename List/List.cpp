#include "List.h"

template<typename T> List<T>::Element::Element(T Data, Element* pPrev, Element* pNext) : Data(Data), pPrev(pPrev), pNext(pNext)
{
	cout << "EConstructor: " << this << endl;
}
template<typename T> List<T>::Element::~Element()
{
	cout << "EDestructor: " << this << endl;
}

template<typename T> List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) : Temp(Temp) {}
template<typename T> List<T>::ConstBaseIterator::~ConstBaseIterator() {}
template<typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other) const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other) const
{
	return this->Temp != other.Temp;
}
template<typename T> T List<T>::ConstBaseIterator::operator*() const
{
	return Temp->Data;
}

template<typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) : ConstBaseIterator(Temp) {}
template<typename T> List<T>::ConstIterator::~ConstIterator() {}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

template<typename T> List<T>::Iterator::Iterator(Element* Temp) : ConstIterator(Temp) {}
template<typename T> List<T>::Iterator::~Iterator() {}
template<typename T> typename T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp) {}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator() {}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

template<typename T> List<T>::ReverseIterator::ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
template<typename T> List<T>::ReverseIterator::~ReverseIterator() {}
template<typename T> typename T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

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
template<typename T> typename List<T>::ConstReverseIterator List<T>::rbegin() const
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