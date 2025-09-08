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
	ForwardList(int size) : ForwardList()
	{
		while (size--) push_front(0);

		cout << "FLSizeConstructor: " << this << endl;
	}
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other);
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

		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_front(Temp->Data);

		reverse();

		cout << "FLCopyAssignment: " << this << endl;

		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
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
	int operator[] (int index) const
	{
		Element* Temp = Head;

		for (int i = 0; i < index; ++i) Temp = Temp->pNext;

		return Temp->Data;
	}
	int& operator[] (int index)
	{
		Element* Temp = Head;

		for (int i = 0; i < index; ++i) Temp = Temp->pNext;

		return Temp->Data;
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
	void reverse()
	{
		ForwardList reverse;

		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
		}

		/*Head = reverse.Head;
		size = reverse.size;*/
		*this = std::move(reverse);
		reverse.Head = nullptr;
	}

	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result;
	
	for (Element* Temp = left.Head; Temp; Temp = Temp->pNext)
		result.push_front(Temp->Data);

	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		result.push_front(Temp->Data);

	result.reverse();

	return result;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
#define MOVE_SEMANTIC_CHECK

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

	for (int i = 0; i < list1.get_size(); ++i) cout << list1[i] << tab; cout << endl;

	ForwardList list2;

	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	for (int i = 0; i < list2.get_size(); ++i) cout << list2[i] << tab; cout << endl;

	ForwardList list3;
	cout << delimeter << endl;
	list3 = list1 + list2;
	cout << delimeter << endl;
	for (int i = 0; i < list3.get_size(); ++i) cout << list3[i] << tab; cout << endl;

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

#ifdef SUBSCRIPT_OPERATOR_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list(n);

	clock_t t_start = clock();
	for (int i = 0; i < list.get_size(); ++i) list[i] = rand() % 100;
	clock_t t_end = clock();

	cout << "Список заполнен за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

	system("PAUSE");

	for (int i = 0; i < list.get_size(); ++i) cout << list[i] << tab;
	cout << endl;
#endif // SUBSCRIPT_OPERATOR_CHECK

#ifdef COPY_SEMANTIC_PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	clock_t t_start, t_end;
	ForwardList list1;

	t_start = clock();
	for (int i = 0; i < n; ++i) list1.push_front(rand() % 100);
	t_end = clock();

	cout << "Список заполнен за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	system("PAUSE");

	t_start = clock();
	ForwardList list2 = list1;
	t_end = clock();

	cout << "Список скопирован за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

	for (int i = 0; i < list1.get_size(); ++i) cout << list1[i] << tab; cout << endl;
	for (int i = 0; i < list2.get_size(); ++i) cout << list2[i] << tab; cout << endl;
#endif // COPY_SEMANTIC_PERFORMANCE_CHECK

#ifdef MOVE_SEMANTIC_CHECK
	ForwardList list1;
	ForwardList list2;

	clock_t t_start = clock();

	for (int i = 0; i < 3000000; ++i) list1.push_front(rand());
	for (int i = 0; i < 3000000; ++i) list2.push_front(rand());

	clock_t t_end = clock();

	cout << "Списки заполнены за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

	system("PAUSE");

	t_start = clock();

	ForwardList list3 = list1 + list2;

	t_end = clock();

	cout << "Списки соединены за " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
#endif // MOVE_SEMANTIC_CHECK


	return 0;
}