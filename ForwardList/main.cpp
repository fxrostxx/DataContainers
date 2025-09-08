#include <iostream>
#include <time.h>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n------------------------------------\n"

class Element
{
private:
	int Data;
	Element* pNext;
	static int global_count;

public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		++global_count;

#ifdef DEBUG
		cout << "EConstructor: " << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		--global_count;

#ifdef DEBUG
		cout << "EDestructor: " << this << endl;
#endif // DEBUG

	}

	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int Element::global_count = 0;

class ForwardList
{
private:
	Element* Head;
	size_t size;

public:
	int get_size() const
	{
		return size;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;

		cout << "FLConstructor: " << this << endl;
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		*this = other;

		cout << "FLCopyConstructor: " << this << endl;
	}
	ForwardList(const int size)
	{
		Head = nullptr;
		this->size = 0;

		for (int i = 0; i < size; ++i) push_front(rand() % 100);
	}
	~ForwardList()
	{
		clock_t t_start = clock();

		while (Head != nullptr) pop_front();

		clock_t t_end = clock();

		cout << "FLDestructor: " << this << " completed for "<< double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	}

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;

		while (Head != nullptr) pop_front();

		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);

		cout << "FLCopyAssignment: " << this << endl;

		return *this;
	}

	void push_front(int Data)
	{
		/*Element* New = new Element(Data);

		New->pNext = Head;

		Head = New;*/

		Head = new Element(Data, Head);

		++size;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);

		Element* New = new Element(Data);

		Element* Temp = Head;

		while (Temp->pNext) Temp = Temp->pNext;

		Temp->pNext = New;

		++size;
	}
	void pop_front()
	{
		if (Head == nullptr) return;

		if (Head->pNext == nullptr)
		{
			delete Head;
			Head = nullptr;
			--size;
			return;
		}

		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;

		--size;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr) return pop_front();

		Element* Temp = Head;

		while (Temp->pNext->pNext) Temp = Temp->pNext;

		delete Temp->pNext;
		Temp->pNext = nullptr;

		--size;
	}
	void insert(int Data, int index)
	{
		if (Head == nullptr) return push_front(Data);

		if (index >= size) return push_back(Data);
		if (index <= 0) return push_front(Data);

		Element* Temp = Head;

		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);

		++size;
	}
	void erase(int index)
	{
		if (Head == nullptr) return;

		if (index >= size - 1) return pop_back();
		if (index <= 0) return pop_front();

		Element* Temp = Head;

		for (int i = 0; i < index - 1; ++i) Temp = Temp->pNext;

		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;

		--size;
	}

	void print() const
	{
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::global_count << endl;
	}

	const int& operator[] (int i) const
	{
		Element* Temp = Head;

		for (int j = 0; j < i && Temp; ++j, Temp = Temp->pNext);

		return Temp->Data;
	}
	int& operator[] (int i)
	{
		Element* Temp = Head;

		for (int j = 0; j < i && Temp; ++j, Temp = Temp->pNext);

		return Temp->Data;
	}

	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result;
	
	for (Element* Temp = left.Head; Temp; Temp = Temp->pNext)
		result.push_back(Temp->Data);

	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		result.push_back(Temp->Data);

	return result;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
#define HW_CHECK

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

	/*list.push_back(456);

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

	list.print();*/
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
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

	ForwardList fusion;
	cout << delimeter << endl;
	fusion = list1 + list2;
	cout << delimeter << endl;
	fusion.print();

	/*int index;
	int value;

	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	list1.insert(value, index);
	list1.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;

	list1.erase(index);
	list1.print();*/
#endif // OPERATOR_PLUS_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;

	clock_t t_start = clock();

	for (int i = 0; i < n; ++i)
	{
		list.push_front(rand() % 100);
	}

	clock_t t_end = clock();

	cout << "ForwardList filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
#endif // PERFORMANCE_CHECK

#ifdef HW_CHECK
	ForwardList list(50000);
	//list.print();

	cout << delimeter << endl;

	clock_t t_start = clock();

	for (int i = 0; i < list.get_size(); ++i) list[i] = rand() % 100;

	clock_t t_end = clock();
	cout << "operator[]: " << "completed for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

	//for (int i = 0; i < list.get_size(); ++i) cout << list[i] << tab;
#endif // HW_CHECK


	return 0;
}