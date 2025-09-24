#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define DEBUG

class Tree
{
protected:
	class Element
	{
	private:
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor: " << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor: " << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	} *Root;
public:
	Element* get_Root() const
	{
		return Root;
	}
	Tree() : Root(nullptr)
	{
		cout << "TConstructor: " << this << endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it) insert(*it, Root);
		cout << "ILConstructor: " << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor: " << this << endl;
	}
	void clear()
	{
		clear(Root);
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue() const
	{
		return minValue(Root);
	}
	int maxValue() const
	{
		return maxValue(Root);
	}
	int count() const
	{
		return count(Root);
	}
	int sum() const
	{
		return sum(Root);
	}
	double avg() const
	{
		return (double)sum(Root) / count(Root);
	}
	void print() const
	{
		print(Root);
		cout << endl;
	}
private:
	void clear(Element*& Root)
	{
		if (!Root) return;
		clear(Root->pRight);
		clear(Root->pLeft);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (!this->Root) this->Root = new Element(Data);
		if (!Root) return;
		if (Data < Root->Data)
		{
			if (!Root->pLeft) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (!Root->pRight) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (!Root) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root) const
	{
		/*if (!this->Root) return;
		if (!Root->pLeft) return Root->Data;
		else return minValue(Root->pLeft);*/
		return !Root ? INT_MIN : !Root->pLeft ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root) const
	{
		/*if (!this->Root) return;
		if (!Root->pRight) return Root->Data;
		else return maxValue(Root->pRight);*/
		return !Root ? INT_MAX : !Root->pRight ? Root->Data : maxValue(Root->pRight);
	}
	int count(Element* Root) const
	{
		/*if (!Root) return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root) const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	void print(Element* Root) const
	{
		if (!Root) return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree : public Tree
{
private:
	void insert(int Data, Element* Root)
	{
		if (!this->Root) this->Root = new Element(Data);
		if (!Root) return;
		if (Data < Root->Data)
		{
			if (!Root->pLeft) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (!Root->pRight) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK

int main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	Tree tree;

	cout << "Введите количество элементов: "; cin >> n;
	for (int i = 0; i < n; ++i) tree.insert(rand() % 100);
	tree.print();

	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << tree.count() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; ++i) u_tree.insert(rand() % 100);
	u_tree.print();

	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << u_tree.count() << endl;
	cout << "Сумма элементов дерева: " << u_tree.sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << u_tree.avg() << endl;
#endif // BASE_CHECK

	Tree tree =
	{
					50,

			25,				75,

		16,		32,		58,		85
	};
	tree.print();

	int n;
	cout << "Введите значение удаляемого элемента: "; cin >> n;
	tree.erase(n);
	tree.print();

	return 0;
}