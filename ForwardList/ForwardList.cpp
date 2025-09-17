#include "stdafx.h"

template<typename T> Element<T>::Element(T Data, Element* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
	++global_count;
#ifdef DEBUG
	cout << "EConstructor: " << this << endl;
#endif // DEBUG
}
template<typename T> Element<T>::~Element()
{
	--global_count;
#ifdef DEBUG
	cout << "EDestructor: " << this << endl;
#endif // DEBUG
}

template<typename T> Iterator<T>::Iterator(Element<T>* Temp) : Temp(Temp)
{
	cout << "ItConstructor: " << this << endl;
}
template<typename T> Iterator<T>::~Iterator()
{
	cout << "ItDestructor: " << this << endl;
}
template<typename T> typename Iterator<T>::Iterator& Iterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T> typename Iterator<T>::Iterator Iterator<T>::operator++(int)
{
	Iterator old = *this;
	Temp = Temp->pNext;
	return old;
}
template<typename T> bool Iterator<T>::operator==(const Iterator& other) const
{
	return this->Temp == other.Temp;
}
template<typename T> bool Iterator<T>::operator!=(const Iterator& other) const
{
	return this->Temp != other.Temp;
}
template<typename T> T Iterator<T>::operator*() const
{
	return Temp->Data;
}
template<typename T> T& Iterator<T>::operator*()
{
	return Temp->Data;
}

template<typename T> int ForwardList<T>::get_size() const
{
	return size;
}
template<typename T> typename Iterator<T> ForwardList<T>::begin() const
{
	return Head;
}
template<typename T> typename Iterator<T> ForwardList<T>::end() const
{
	return nullptr;
}
template<typename T> ForwardList<T>::ForwardList()
{
	Head = nullptr;
	size = 0;
	cout << "FLConstructor: " << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(const ForwardList& other) : ForwardList()
{
	*this = other;
	cout << "FLCopyConstructor: " << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(int size) : ForwardList()
{
	while (size--) push_front(T());
	cout << "FLSizeConstructor: " << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(const std::initializer_list<T>& il) : ForwardList()
{
	for (T const* it = il.begin(); it != il.end(); ++it) push_back(*it);
	cout << "FLitConstructor: " << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(ForwardList&& other) : ForwardList()
{
	*this = std::move(other);
}
template<typename T> ForwardList<T>::~ForwardList()
{
	clock_t t_start = clock();
	while (Head != nullptr) pop_front();
	clock_t t_end = clock();
	cout << "FLDestructor: " << this << " completed for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
}
template<typename T> typename ForwardList<T>::ForwardList& ForwardList<T>::operator=(const ForwardList& other)
{
	if (this == &other) return *this;
	while (Head != nullptr) pop_front();
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext) push_front(Temp->Data);
	reverse();
	cout << "FLCopyAssignment: " << this << endl;
	return *this;
}
template<typename T> typename ForwardList<T>::ForwardList& ForwardList<T>::operator=(ForwardList&& other)
{
	if (this == &other) return *this;
	while (Head) pop_front();
	this->Head = other.Head;
	this->size = other.size;
	other.Head = nullptr;
	other.size = 0;
	cout << "FLMoveAssignment: " << this << endl;
	return *this;
}
template<typename T> T ForwardList<T>::operator[] (int index) const
{
	Element<T>* Temp = Head;
	for (int i = 0; i < index; ++i) Temp = Temp->pNext;
	return Temp->Data;
}
template<typename T> T& ForwardList<T>::operator[] (int index)
{
	Element<T>* Temp = Head;
	for (int i = 0; i < index; ++i) Temp = Temp->pNext;
	return Temp->Data;
}
template<typename T> void ForwardList<T>::push_front(T Data)
{
	Head = new Element<T>(Data, Head);
	++size;
}
template<typename T> void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr) return push_front(Data);
	Element<T>* New = new Element<T>(Data);
	Element<T>* Temp = Head;
	while (Temp->pNext) Temp = Temp->pNext;
	Temp->pNext = New;
	++size;
}
template<typename T> void ForwardList<T>::pop_front()
{
	if (Head == nullptr) return;
	if (Head->pNext == nullptr)
	{
		delete Head;
		Head = nullptr;
		--size;
		return;
	}
	Element<T>* Erased = Head;
	Head = Head->pNext;
	delete Erased;
	--size;
}
template<typename T> void ForwardList<T>::pop_back()
{
	if (Head == nullptr || Head->pNext == nullptr) return pop_front();
	Element<T>* Temp = Head;
	while (Temp->pNext->pNext) Temp = Temp->pNext;
	delete Temp->pNext;
	Temp->pNext = nullptr;
	--size;
}
template<typename T> void ForwardList<T>::insert(T Data, int index)
{
	if (Head == nullptr) return push_front(Data);
	if (index >= size) return push_back(Data);
	if (index <= 0) return push_front(Data);
	Element<T>* Temp = Head;
	for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;
	Temp->pNext = new Element<T>(Data, Temp->pNext);
	++size;
}
template<typename T> void ForwardList<T>::erase(int index)
{
	if (Head == nullptr) return;
	if (index >= size - 1) return pop_back();
	if (index <= 0) return pop_front();
	Element<T>* Temp = Head;
	for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;
	Element<T>* Erased = Temp->pNext;
	Temp->pNext = Erased->pNext;
	delete Erased;
	--size;
}
template<typename T> void ForwardList<T>::print() const
{
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << "Общее количество элементов списка: " << Element<T>::global_count << endl;
}
template<typename T> void ForwardList<T>::reverse()
{
	ForwardList<T> reverse;
	while (Head)
	{
		reverse.push_front(Head->Data);
		pop_front();
	}
	*this = std::move(reverse);
	reverse.Head = nullptr;
}
template<typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> result;
	for (Element<T>* Temp = left.Head; Temp; Temp = Temp->pNext)
		result.push_front(Temp->Data);
	for (Element<T>* Temp = right.Head; Temp; Temp = Temp->pNext)
		result.push_front(Temp->Data);
	result.reverse();
	return result;
}