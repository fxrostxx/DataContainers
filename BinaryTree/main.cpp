#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Tree
{
private:
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
		cout << "TDestructor: " << this << endl;
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
	int minValue(Element* Root)
	{
		/*if (!this->Root) return;
		if (!Root->pLeft) return Root->Data;
		else return minValue(Root->pLeft);*/
		return !Root ? INT_MIN : !Root->pLeft ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		/*if (!this->Root) return;
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
	void print(Element* Root) const
	{
		if (!Root) return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

int main()
{
	setlocale(LC_ALL, "");

	int n;
	Tree tree;

	cout << "Введите количество элементов: "; cin >> n;
	for (int i = 0; i < n; ++i) tree.insert(rand() % 100, tree.get_Root());
	tree.print(tree.get_Root());
	cout << endl;

	cout << "Минимальное значение в дереве: " << tree.minValue(tree.get_Root()) << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue(tree.get_Root()) << endl;
	cout << "Количество элементов в дереве: " << tree.count(tree.get_Root()) << endl;

	return 0;
}