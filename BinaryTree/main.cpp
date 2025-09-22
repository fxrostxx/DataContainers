#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

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
			cout << "EConstructor: " << this << endl;
		}
		~Element()
		{
			cout << "EDestructor: " << this << endl;
		}
		friend class UniqueTree;
		friend class Tree;
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
	~Tree()
	{
		clear(Root);
		cout << "TDestructor: " << this << endl;
	}
	virtual void insert(int Data, Element* Root)
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
	void erase(int Data, Element* Root)
	{
		if (!this->Root || !Root) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft && Root->pLeft->Data == Data)
			{
				if (!Root->pLeft->pLeft && !Root->pLeft->pRight)
				{
					delete Root->pLeft;
					Root->pLeft = nullptr;
				}
				else if (Root->pLeft->pLeft && !Root->pLeft->pRight)
				{
					Root->pLeft = Root->pLeft->pLeft;
					delete Root->pLeft;
				}
				else if (!Root->pLeft->pLeft && Root->pLeft->pRight)
				{
					Root->pRight = Root->pLeft->pRight;
					delete Root->pLeft;
				}
				else if (Root->pLeft->pLeft && Root->pLeft->pRight)
				{
					//???
				}
			}
			else erase(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight && Root->pRight->Data == Data)
			{
				if (!Root->pRight->pLeft && !Root->pRight->pRight)
				{
					delete Root->pRight;
					Root->pRight = nullptr;
				}
				else if (Root->pRight->pLeft && !Root->pRight->pRight)
				{
					Root->pLeft = Root->pRight->pLeft;
					delete Root->pRight;
				}
				else if (!Root->pRight->pLeft && Root->pRight->pRight)
				{
					Root->pRight = Root->pRight->pRight;
					delete Root->pRight;
				}
				else if (Root->pRight->pLeft && Root->pRight->pRight)
				{
					//???
				}
			}
			else erase(Data, Root->pRight);
		}
	}
	void clear(Element* Root)
	{
		if (!Root) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	int minValue(Element* Root)
	{
		/*if (!Root) return INT_MIN;
		if (!this->Root) return;
		if (!Root->pLeft) return Root->Data;
		else return minValue(Root->pLeft);*/
		return !Root ? INT_MIN : !Root->pLeft ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		/*if (!Root) return INT_MAX;
		if (!this->Root) return;
		if (!Root->pRight) return Root->Data;
		else return maxValue(Root->pRight);*/
		return !Root ? INT_MAX : !Root->pRight ? Root->Data : maxValue(Root->pRight);
	}
	int count(Element* Root)
	{
		/*if (!Root) return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int Sum(Element* Root)
	{
		/*if (!Root) return 0;
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;*/
		return !Root ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	double Avg(Element* Root)
	{
		/*if (!Root) return 0;
		else return (double)Sum(Root) / count(Root);*/
		return !Root ? 0 : (double)Sum(Root) / count(Root);
	}
	bool find(int Data, Element* Root)
	{
		if (!Root) return false;
		if (Root->Data == Data) return true;
		if (Data < Root->Data) return find(Data, Root->pLeft);
		else return find(Data, Root->pRight);
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
public:
	void insert(int Data, Element* Root) override
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
		else return;
	}
};

//#define TREE_TEST
#define U_TREE_TEST

int main()
{
	setlocale(LC_ALL, "");

#ifdef TREE_TEST
	int n;
	Tree tree;

	cout << "Введите количество элементов: "; cin >> n;
	for (int i = 0; i < n; ++i) tree.insert(rand() % 100, tree.get_Root());
	tree.print(tree.get_Root());
	cout << endl;

	cout << "Минимальное значение в дереве: " << tree.minValue(tree.get_Root()) << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue(tree.get_Root()) << endl;
	cout << "Количество элементов дерева: " << tree.count(tree.get_Root()) << endl;
	cout << "Сумма элементов дерева: " << tree.Sum(tree.get_Root()) << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg(tree.get_Root()) << endl;
	cout << "Введите значение удаляемого элемента: "; cin >> n;
	tree.erase(n, tree.get_Root());
	tree.print(tree.get_Root());
	cout << endl;
	cout << "Введите значение искомого элемента: "; cin >> n;
	cout << (tree.find(n, tree.get_Root()) ? "Элемент найден" : "Элемент не найден") << endl;
	cout << endl;
#endif // TREE_TEST


#ifdef U_TREE_TEST
	int n;
	UniqueTree u_tree;
	cout << "Введите количество элементов: "; cin >> n;
	for (int i = 0; i < n; ++i) u_tree.insert(rand() % 100, u_tree.get_Root());
	u_tree.print(u_tree.get_Root()); cout << endl;
	cout << "Введите значение добавляемого элемента: "; cin >> n;
	cout << (u_tree.find(n, u_tree.get_Root()) ? "Элемент уже есть в дереве. Пропуск." : "Элемент добавлен.") << endl;
	u_tree.insert(n, u_tree.get_Root());
	u_tree.print(u_tree.get_Root()); cout << endl;
#endif // U_TREE_TEST


	return 0;
}