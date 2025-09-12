#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class Element
{
private:
	Element* pPrev;
	Element* pNext;
	int Data;
	static int global_count;
public:
	Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr) : Data(Data), pPrev(pPrev), pNext(pNext)
	{
		++global_count;
#ifdef DEBUG
		cout << "EConstructor: " << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		--global_count;
#ifdef DEBUG
		cout << "EConstructor: " << this << endl;
#endif // DEBUG
	}
};

int Element::global_count = 0;

class List
{
private:
	Element* Head;
	Element* Tail;
	size_t size;
public:
	int get_size() const
	{
		return size;
	}
	Element* get_Head() const
	{
		return Head;
	}
	Element* get_Tail() const
	{
		return Tail;
	}

	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor: " << this << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "");



	return 0;
}