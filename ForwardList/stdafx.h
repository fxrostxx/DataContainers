#pragma once

#include <iostream>
#include <time.h>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n------------------------------------\n"

template<typename T> class ForwardList;
template<typename T> class Iterator;

template<typename T> class Element
{
private:
	T Data;
	Element* pNext;
	static int global_count;

public:
	Element(T Data, Element* pNext = nullptr);
	~Element();
	friend class Iterator<T>;
	friend class ForwardList<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};

template<typename T> int Element<T>::global_count = 0;

template<typename T> class Iterator
{
private:
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr);
	~Iterator();
	Iterator& operator++();
	Iterator operator++(int);
	bool operator==(const Iterator& other) const;
	bool operator!=(const Iterator& other) const;
	T operator*() const;
	T& operator*();
};

template<typename T> class ForwardList
{
private:
	Element<T>* Head;
	size_t size;
public:
	int get_size() const;
	Iterator<T> begin() const;
	Iterator<T> end() const;
	ForwardList();
	ForwardList(const ForwardList& other);
	ForwardList(int size);
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(ForwardList&& other);
	~ForwardList();
	ForwardList& operator=(const ForwardList& other);
	ForwardList& operator=(ForwardList&& other);
	T operator[] (int index) const;
	T& operator[] (int index);
	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, int index);
	void erase(int index);
	void print() const;
	void reverse();
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};