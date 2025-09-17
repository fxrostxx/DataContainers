#pragma once

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
		Element(T Data, Element* pPrev = nullptr, Element* pNext = nullptr);
		~Element();
		friend class List;
	} *Head, * Tail;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other) const;
		bool operator!=(const ConstBaseIterator& other) const;
		T operator*() const;
	};
	size_t size;
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();
		T& operator*();
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		T& operator*();
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