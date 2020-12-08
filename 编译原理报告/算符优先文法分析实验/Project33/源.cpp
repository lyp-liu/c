/////////////////////////////////////////////////

/*T423-3-7滕荟芸 编译课程设计 2007-9-6*/

/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
//#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include<string>
/////////////////////////////////////////////////

#define NULL 0
#define LStack LinkedStack
using namespace std;
/////////////////////////////////////////////////

// 链式栈类的前视定义
template <class T>
class LinkedStack;

/////////////////////////////////////////////////

// 定义链式栈结点类
template <class T>
class StackNode
{
	friend class LinkedStack<T>;
private:
	T data;
	StackNode<T> *next;
	StackNode(T item = 0, StackNode<T> *p = NULL)
	{
		data = item;
		next = p;
	}
};

/////////////////////////////////////////////////

// 定义链式栈类
template <class T>
class LinkedStack
{
private:
	StackNode<T> *top;
public:
	LinkedStack();
	~LinkedStack();
	bool IsEmpty(void) const;
	int Length(void) const;
	void Push(const T &item);
	T Pop(void);
	T GetTop(void);
	void Clear(void);
};
// 构造函数
template <class T>
LinkedStack<T>::LinkedStack()
{
	top = NULL;
}
// 析构函数
template <class T>
LinkedStack<T>::~LinkedStack()
{
	Clear();
}
// 判断栈是否为空
template <class T>
bool LinkedStack<T>::IsEmpty(void) const
{
	return (!top);
}
// 获取队列的长度
template <class T>
int LinkedStack<T>::Length(void) const
{
	StackNode<T> *temp = new StackNode<T>();
	temp = top;
	int length = 0;
	while (temp)
	{
		temp = temp->next;
		length++;
	}
	return length;
}
// 压入数据(入栈)
template <class T>
void LinkedStack<T>::Push(const T &item)
{
	top = new StackNode<T>(item, top);
}
// 抽出数据(出栈)
template <class T>
T LinkedStack<T>::Pop(void)
{
	if (!IsEmpty())
	{
		StackNode<T> *temp = top;
		top = top->next;
		T value = temp->data;
		delete temp;
		return value;
	}
	else
	{
		cout << "Stack Already Empty!" << endl;
		_getch();
		exit(1);
	}
}
// 获取栈头数据
template <class T>
T LinkedStack<T>::GetTop(void)
{
	if (!IsEmpty())
	{
		return top->data;
	}
	else
	{
		cout << "Stack Already Empty!" << endl;
		_getch();
		exit(1);
	}
}
// 设置栈为空栈
template <class T>
void LinkedStack<T>::Clear(void)
{
	StackNode<T> *temp = new StackNode<T>();
	while (top)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
}

/////////////////////////////////////////////////

// 定义邻接表的边表类
class Edge
{
public:
	int number;
	int position;
	char weight;
	Edge *link;
	Edge();
	Edge(int num, int pos, char ch);
};
Edge::Edge()
{
	number = -1;
	position = -1;
	link = NULL;
}
Edge::Edge(int num, int pos, char ch)
{
	number = num;
	position = pos;
	weight = ch;
	link = NULL;
}

/////////////////////////////////////////////////

// 定义邻接表的顶点类
class Vertex
{
public:
	int number;
	Vertex *next;
	Edge *out;
	Vertex();
	Vertex(int num);
};
Vertex::Vertex()
{
	number = -1;
	next = NULL;
	out = NULL;
}
Vertex::Vertex(int num)
{
	number = num;
	next = NULL;
	out = NULL;
}

/////////////////////////////////////////////////

// 用邻接表定义的图类
class AdjacentTable
{
private:
	Vertex *startVertex;
	int numOfVertices;
	int numOfEdges;
public:
	AdjacentTable();
	~AdjacentTable();
	int GetValueByPos(int pos) const;
	int GetPosByValue(int value) const;
	char GetWeightByPos(int v1, int v2) const;
	char GetWeightByValue(int value1, int value2) const;
	void SetValue(int value, int pos);
	void InsertVertex(int value);
	void InsertEdgeByPos(int v1, int v2, char weight);
	void InsertEdgeByValue(int value1, int value2, char weight);
	void RemoveAllEdges(void);
	void Clear(void);
	int* Closure(int *T);
	int* Move(int *T, char ch);
	void OutputNFA(void);
};
// 构造函数
AdjacentTable::AdjacentTable()
{
	numOfVertices = 1;
	numOfEdges = 0;
	startVertex = new Vertex();
}
// 析构函数
AdjacentTable::~AdjacentTable()
{
	Vertex *p;
	Edge *q;
	p = startVertex;
	for (int i = 0; i < numOfVertices; i++)
	{
		q = p->out;
		while (q)
		{
			p->out = q->link;
			delete q;
			q = p->out;
		}
		p = p->next;
	}
}
// 按顶点位置获取顶点的值
int AdjacentTable::GetValueByPos(int pos) const
{
	if ((pos >= 0) && (pos < numOfVertices))
	{
		Vertex *p = startVertex;
		for (int i = 0; i < pos; i++)
		{
			p = p->next;
		}
		return p->number;
	}
	return -1;
}
// 按顶点值获取顶点的位置
int AdjacentTable::GetPosByValue(int value) const
{
	Vertex *p = startVertex;
	for (int i = 0; i < numOfVertices; i++)
	{
		if (p->number == value)
		{
			return i;
		}
		p = p->next;
	}
	return -1;
}
// 按顶点位置获取边的权
char AdjacentTable::GetWeightByPos(int v1, int v2) const
{
	if ((v1 >= 0) && (v2 >= 0) && (v1 < numOfVertices) && (v2 < numOfVertices))
	{
		Vertex *p = startVertex;
		for (int i = 0; i < v1; i++)
		{
			p = p->next;
		}
		Edge *q = p->out;
		while (q)
		{
			if (q->position == v2)
			{
				return (q->weight);
			}
			else
			{
				q = q->link;
			}
		}
	}
	return '#';
}
// 按顶点值获取边的权
char AdjacentTable::GetWeightByValue(int value1, int value2) const
{
	return GetWeightByPos(GetPosByValue(value1), GetPosByValue(value2));
}
// 设置顶点的值
void AdjacentTable::SetValue(int value, int pos)
{
	if ((pos < 0) || (pos >= numOfVertices))
	{
		cout << "Illegal setting: The vertex doesn't exist!" << endl;
		_getch();
		exit(1);
	}
	Vertex *p = startVertex;
	for (int i = 0; i < pos; i++)
	{
		p = p->next;
	}
	p->number = value;
}
// 插入顶点
void AdjacentTable::InsertVertex(int value)
{
	int pos = GetPosByValue(value);
	if ((pos >= 0) && (pos < numOfVertices))
	{
		cout << "Illegal insertion: The same vertex has existed!" << endl;
		_getch();
		exit(1);
	}
	Vertex *p = startVertex;
	while (p->next)
	{
		p = p->next;
	}
	Vertex *newVertex = new Vertex(value);
	p->next = newVertex;
	numOfVertices++;
}
// 按顶点位置插入边表
void AdjacentTable::InsertEdgeByPos(int v1, int v2, char weight)
{
	if ((v1 < 0) || (v1 >= numOfVertices) || (v2 < 0) || (v2 >= numOfVertices))
	{
		cout << "Illegal insertion: The vertex doesn't exist!" << endl;
		_getch();
		exit(1);
	}
	Vertex *p = startVertex;
	for (int i = 0; i < v1; i++)
	{
		p = p->next;
	}
	Edge *q = p->out;
	Edge *newEdge = new Edge(GetValueByPos(v2), v2, weight);
	if (!q)
	{
		p->out = newEdge;
		numOfEdges++;
		return;
	}
	while ((q->position != v2) && (q->link))
	{
		q = q->link;
	}
	if (q->position == v2)
	{
		cout << "Illegal insertion: The Edge has existed!" << endl;
		_getch();
		exit(1);
	}
	if (!q->link)
	{
		q->link = newEdge;
		numOfEdges++;
	}
}
// 按顶点值插入边表
void AdjacentTable::InsertEdgeByValue(int value1, int value2, char weight)
{
	int v1 = GetPosByValue(value1), v2 = GetPosByValue(value2);
	InsertEdgeByPos(v1, v2, weight);
}
// 删除所有的边表
void AdjacentTable::RemoveAllEdges(void)
{
	Vertex *p = startVertex;
	for (int i = 0; i < numOfVertices; i++)
	{
		Edge *q = p->out;
		while (q)
		{
			p->out = q->link;
			delete q;
			q = p->out;
		}
		p = p->next;
	}
	numOfEdges = 0;
}
// 清空邻接表
void AdjacentTable::Clear(void)
{
	RemoveAllEdges();
	Vertex *p = startVertex->next;
	while (p)
	{
		startVertex->next = p->next;
		delete p;
		p = startVertex->next;
	}
	numOfVertices = 1;
}
// 闭包函数
int* AdjacentTable::Closure(int *T)
{
	int i = 0, j, k = 0, l, len = 0;
	int *temp = new int[128];
	Vertex *p;
	Edge *q;
	while (T[len] != -1)
	{
		len++;
	}
	while (T[i] != -1)
	{
		for (l = 0; l < k; l++)
		{
			if (T[i] == temp[l])
			{
				break;
			}
		}
		if (l == k)
		{
			temp[k] = T[i];
			k++;
		}
		int pos = GetPosByValue(T[i]);
		p = startVertex;
		for (j = 0; j < pos; j++)
		{
			p = p->next;
		}
		q = p->out;
		while (q)
		{
			if (q->weight == '~')
			{
				for (l = 0; l < k; l++)
				{
					if (q->number == temp[l])
					{
						break;
					}
				}
				if (l == k)
				{
					temp[k] = q->number;
					k++;
					T[len++] = q->number;
					T[len] = -1;
				}
			}
			q = q->link;
		}
		i++;
	}
	temp[k] = -1;
	return temp;
}
// 移动函数
int* AdjacentTable::Move(int *T, char ch)
{
	int i = 0, j, k = 0, l;
	int *temp = new int[128];
	Vertex *p;
	Edge *q;
	while (T[i] != -1)
	{
		int pos = GetPosByValue(T[i]);
		p = startVertex;
		for (j = 0; j < pos; j++)
		{
			p = p->next;
		}
		q = p->out;
		while (q)
		{
			if (q->weight == ch)
			{
				for (l = 0; l < k; l++)
				{
					if (q->number == temp[l])
					{
						break;
					}
				}
				if (l == k)
				{
					temp[k] = q->number;
					k++;
				}
			}
			q = q->link;
		}
		i++;
	}
	temp[k] = -1;
	return temp;
}
// 输出邻接表
void AdjacentTable::OutputNFA(void)
{
	Vertex *p = startVertex;
	Edge *q = new Edge();
	cout << "状态   边(权值)" << endl;
	for (int i = 0; i < numOfVertices; i++)
	{
		cout << p->number;
		if (p->number < 10)	 cout << "      ";
		else if (p->number < 100)  cout << "     ";
		else if (p->number < 1000)	cout << "    ";
		else  cout << "   ";
		q = p->out;
		if (q)
		{
			while (q)
			{
				cout << q->number << "(" << q->weight << ") ";
				q = q->link;
			}
		}
		else
		{
			cout << "END";
		}
		cout << endl;
		p = p->next;
	}
}

/////////////////////////////////////////////////

// 定义转移矩阵类
class TransitionTable
{
public:
	TransitionTable(int rowNum, int colNum);
	~TransitionTable();
	void SetValue(int i, int j, int value);
	int GetValue(int i, int j);
	int Transit(int current, char input, char *edge);
	void Clear(void);
private:
	int **matrix;
	int rowNumber;
	int colNumber;
};
// 构造函数
TransitionTable::TransitionTable(int rowNum, int colNum)
{
	rowNumber = rowNum;
	colNumber = colNum;
	matrix = (int**)(new int*[rowNumber]);
	for (int i = 0; i < rowNumber; i++)
	{
		matrix[i] = new int[colNumber];
	}
}
// 析构函数
TransitionTable::~TransitionTable()
{
	Clear();
}
// 设置元素的值
void TransitionTable::SetValue(int i, int j, int value)
{
	matrix[i][j] = value;
}
// 获取元素的值
int TransitionTable::GetValue(int i, int j)
{
	return matrix[i][j];
}
// 状态转移函数
int TransitionTable::Transit(int current, char input, char *edge)
{
	for (int i = 0; edge[i] != '\0'; i++)
	{
		if (input == edge[i])
		{
			return matrix[current][i];
		}
	}
	return -1;
}
// 清空转移矩阵
void TransitionTable::Clear(void)
{
	for (int i = 0; i < rowNumber; i++)
	{
		delete[] matrix[i];
	}
	delete matrix;
}

/////////////////////////////////////////////////

// 定义DFA的构造类
class DFA
{
public:
	DFA();
	~DFA();
	void GetRegExp();
	void InsertCatNode();
	void RegExpToPost();
	void GetEdgeNumber();
	void ThompsonConstruction();
	void SubsetConstruction();
	void FindMatchingPatternInFile();
private:
	char *exp;
	char *post;
	char *edge;
	int edgeNumber;
	int **DStates;
	int **Dtran;
	int *AcceptStates;
	int DStatesNumber;
	int DtranNumber;
	int NFAStatesNumber;
	int DFAStatesNumber;
	AdjacentTable *NFATable;
	TransitionTable *DFATable;
	int Precedence(char symbol);
	int CompArray(int *t1, int *t2);
	int MinimizeDFAStates(int **Dtran, int *AcceptStates, int DtranNumber, int edgeNumber);
	void RemoveFirstSymbol(char *buf, int &len);
};
// 构造函数
DFA::DFA()
{
	exp = new char[512];
	post = new char[512];
	edge = new char[512];
	edgeNumber = 0;
	NFAStatesNumber = 0;
	DFAStatesNumber = 0;
	DStatesNumber = 0;
	DtranNumber = 0;
	NFATable = new AdjacentTable();
}
// 析构函数
DFA::~DFA()
{
	delete[] exp;
	delete[] post;
	delete[] edge;
	delete[] AcceptStates;
	NFATable->Clear();
	DFATable->Clear();
}
// 获取输入
void DFA::GetRegExp()
{
	cout << "在下面输入正则表达式" << endl;
	cin >> exp;
	
	for (int i = 0; exp[i] != '\0'; i++)
	{
		if (exp[i] == '~')
		{
			cout << "\n字符'~'已经被程序禁用！" << endl;
			_getch();
			exit(1);
		}
	}
	cout << "\n------------------------" << endl;
}
// 加入cat-node作为连结点标志
void DFA::InsertCatNode()
{
	int i = 0, j, len = strlen(exp);
	while (exp[i + 1] != '\0')
	{
		if (((exp[i] != '(' && exp[i] != '.' && exp[i] != '|')
			|| exp[i] == ')'
			|| exp[i] == '*')
			&& (exp[i + 1] != ')' && exp[i + 1] != '.' && exp[i + 1] != '|' && exp[i + 1] != '*'))
		{
			for (j = len; j > i + 1; j--)
			{
				exp[j] = exp[j - 1];
			}
			exp[i + 1] = '.';
			len++;
			exp[len] = '\0';
			i++;
		}
		i++;
	}
	cout << "\n第一步: 加入连结点\n"
		<< exp << "\n"
		<< "字符串长度: " << len
		<< "\n\n------------------------" << endl;
}
// 定义运算符的优先级
int DFA::Precedence(char symbol)
{
	int priority;
	switch (symbol)
	{
	case '|': priority = 1; break;
	case '.': priority = 2; break;
	case '*': priority = 3; break;
	default:  priority = 0; break;
	}
	return priority;
}
// 将正则式转为逆波兰式
void DFA::RegExpToPost()
{
	int i = 0, j = 0;
	char ch, cl;
	strcpy(post, "\0");
	LStack<char> *ls = new LStack<char>();
	ls->Clear();
	ls->Push('#');
	ch = exp[i];
	while (ch != '\0')
	{
		if (ch == '(')
		{
			ls->Push(ch);
			ch = exp[++i];
		}
		else if (ch == ')')
		{
			while (ls->GetTop() != '(')
			{
				post[j++] = ls->Pop();
			}
			ls->Pop();
			ch = exp[++i];
		}
		else if ((ch == '|') || (ch == '*') || (ch == '.'))
		{
			cl = ls->GetTop();
			while (Precedence(cl) >= Precedence(ch))
			{
				post[j++] = cl;
				ls->Pop();
				cl = ls->GetTop();
			}
			ls->Push(ch);
			ch = exp[++i];
		}
		else
		{
			post[j++] = ch;
			ch = exp[++i];
		}
	}
	ch = ls->Pop();
	while ((ch == '|') || (ch == '*') || (ch == '.'))
	{
		post[j++] = ch;
		ch = ls->Pop();
	}
	post[j] = '\0';
	ls->Clear();
	cout << "\n第二步: 转为后缀式\n"
		<< post << "\n"
		<< "字符串长度: " << strlen(post)
		<< "\n\n------------------------" << endl;
}
// 扫描逆波兰式中除运算符以外的字符的数目
void DFA::GetEdgeNumber()
{
	int i = 0, j;
	edgeNumber = 0;
	while (post[i] != '\0')
	{
		if (post[i] == '.' || post[i] == '|' || post[i] == '*')
		{
			i++;
			continue;
		}
		for (j = 0; j < edgeNumber; j++)
		{
			if (post[i] == edge[j])
			{
				break;
			}
		}
		if (j == edgeNumber)
		{
			edge[edgeNumber] = post[i];
			edgeNumber++;
		}
		i++;
	}
	edge[edgeNumber] = '\0';
	cout << "\n第三步: 获取字符集\n";
	for (i = 0; i < edgeNumber; i++)
	{
		cout << edge[i] << ' ';
	}
	cout << "\n字符个数: " << edgeNumber
		<< "\n\n------------------------" << endl;
}
// 用Thompson构造法构造NFA
void DFA::ThompsonConstruction()
{
	int i, j;
	char ch;
	int s1, s2;
	LStack<int> *states = new LStack<int>();
	states->Clear();
	if (strlen(post) < 1)
	{
		cout << "No Valid Regular Expression Found!" << endl;
		_getch();
		exit(1);
	}
	NFATable->SetValue(0, 0);
	i = 1;
	j = 0;
	ch = post[j];
	while (ch != '\0')
	{
		if (ch == '.')
		{
			s2 = states->Pop();
			int temp1 = states->Pop();
			int temp2 = states->Pop();
			s1 = states->Pop();
			NFATable->InsertEdgeByValue(temp2, temp1, '~');
			states->Push(s1);
			states->Push(s2);
		}
		else if (ch == '|')
		{
			s2 = states->Pop();
			int temp1 = states->Pop();
			int temp2 = states->Pop();
			s1 = states->Pop();
			NFATable->InsertVertex(i);
			NFATable->InsertVertex(i + 1);
			NFATable->InsertEdgeByValue(i, s1, '~');
			NFATable->InsertEdgeByValue(i, temp1, '~');
			NFATable->InsertEdgeByValue(temp2, i + 1, '~');
			NFATable->InsertEdgeByValue(s2, i + 1, '~');
			s1 = i;
			s2 = i + 1;
			states->Push(s1);
			states->Push(s2);
			i += 2;
		}
		else if (ch == '*')
		{
			s2 = states->Pop();
			s1 = states->Pop();
			NFATable->InsertVertex(i);
			NFATable->InsertVertex(i + 1);
			NFATable->InsertEdgeByValue(i, i + 1, '~');
			NFATable->InsertEdgeByValue(s2, s1, '~');
			NFATable->InsertEdgeByValue(i, s1, '~');
			NFATable->InsertEdgeByValue(s2, i + 1, '~');
			s1 = i;
			s2 = i + 1;
			states->Push(s1);
			states->Push(s2);
			i += 2;
		}
		else
		{
			NFATable->InsertVertex(i);
			NFATable->InsertVertex(i + 1);
			NFATable->InsertEdgeByValue(i, i + 1, ch);
			s1 = i;
			s2 = i + 1;
			states->Push(s1);
			states->Push(s2);
			i += 2;
		}
		j++;
		ch = post[j];
	}
	s2 = states->Pop();
	s1 = states->Pop();
	NFATable->InsertEdgeByValue(0, s1, '~');
	if (!states->IsEmpty())
	{
		cout << "Some error in your input string!" << endl;
		_getch();
		exit(1);
	}
	NFAStatesNumber = s2 + 1;
}
// 比较两个一维数组是否含有完全相同的元素
int DFA::CompArray(int *t1, int *t2)
{
	int i = 0, j = 0, len1, len2;
	while (t1[i] != -1)
	{
		i++;
	}
	len1 = i;
	while (t2[j] != -1)
	{
		j++;
	}
	len2 = j;
	if (len1 != len2)
	{
		return 0;
	}
	for (i = 0; i < len1; i++)
	{
		for (j = 0; j < len2; j++)
		{
			if (t1[i] == t2[j])
			{
				break;
			}
		}
		if (j == len2)
		{
			return 0;
		}
	}
	return 1;
}
// 最小化Dtran表
int DFA::MinimizeDFAStates(int **Dtran, int *AcceptStates, int DtranNumber, int edgeNumber)
{
	int h, i, j, k, l;
	for (i = 0; i < DtranNumber - 1; i++)
	{
		for (j = i + 1; j < DtranNumber; j++)
		{
			if (AcceptStates[i] == AcceptStates[j])
			{
				for (k = 0; k < edgeNumber; k++)
				{
					if (Dtran[i][k] != Dtran[j][k])
					{
						break;
					}
				}
				if (k == edgeNumber)
				{
					for (l = j; l < DtranNumber - 1; l++)
					{
						for (k = 0; k < edgeNumber; k++)
						{
							Dtran[l][k] = Dtran[l + 1][k];
						}
						AcceptStates[l] = AcceptStates[l + 1];
					}
					for (l = 0; l < DtranNumber - 1; l++)
					{
						for (k = 0; k < edgeNumber; k++)
						{
							if (Dtran[l][k] == j)
							{
								Dtran[l][k] = i;
							}
						}
					}
					for (h = j; h < DtranNumber; h++)
					{
						for (l = 0; l < DtranNumber - 1; l++)
						{
							for (k = 0; k < edgeNumber; k++)
							{
								if (Dtran[l][k] == h + 1)
								{
									Dtran[l][k] = h;
								}
							}
						}
					}
					DtranNumber--;
					j--;
				}
			}
		}
	}
	return DtranNumber;
}
// 用子集构造法构造DFA
void DFA::SubsetConstruction()
{
	int i, j, k;
	DStatesNumber = 0;
	DtranNumber = 0;
	// 输出NFA状态表
	cout << "\n第四步: 构造NFA\n\n";
	NFATable->OutputNFA();
	cout << "\n------------------------" << endl;
	// 初始化DStates和Dtran两个构造表及AcceptStates数组
	DStates = (int**)(new int*[NFAStatesNumber + 1]);
	for (i = 0; i < NFAStatesNumber + 1; i++)
	{
		DStates[i] = new int[NFAStatesNumber + 1];
	}
	Dtran = (int**)(new int*[NFAStatesNumber + 1]);
	for (i = 0; i < NFAStatesNumber + 1; i++)
	{
		Dtran[i] = new int[edgeNumber + 1];
	}
	for (i = 0; i < NFAStatesNumber + 1; i++)
	{
		for (j = 0; j < edgeNumber + 1; j++)
		{
			Dtran[i][j] = -1;
		}
	}
	AcceptStates = new int[NFAStatesNumber + 1];
	for (i = 0; i < NFAStatesNumber + 1; i++)
	{
		AcceptStates[i] = 0;
	}
	// 调用闭包函数和移动函数构造DStates和Dtran两个表及AcceptStates数组
	int *T = new int[NFAStatesNumber + 1];
	int *temp = new int[NFAStatesNumber + 1];
	T[0] = 0;
	T[1] = -1;
	T = NFATable->Closure(T);
	DStates[DStatesNumber] = T;
	DStatesNumber++;
	k = 0;
	while (k < DStatesNumber)
	{
		for (i = 0; edge[i] != '\0'; i++)
		{
			temp = NFATable->Closure(NFATable->Move(T, edge[i]));
			if (temp[0] != -1)
			{
				for (j = 0; j < DStatesNumber; j++)
				{
					if (CompArray(temp, DStates[j]) == 1)
					{
						Dtran[k][i] = j;
						break;
					}
				}
				if (j == DStatesNumber)
				{
					DStates[DStatesNumber] = temp;
					Dtran[k][i] = DStatesNumber;
					DStatesNumber++;
				}
			}
		}
		k++;
		T = DStates[k];
	}
	DtranNumber = k;
	for (i = 0; i < DStatesNumber; i++)
	{
		for (j = 0; DStates[i][j] != -1; j++)
		{
			if (DStates[i][j] == NFAStatesNumber - 1)
			{
				AcceptStates[i] = 1;
				break;
			}
		}
	}
	// 输出DStates表项
	cout << "\n第五步: 构造DStates表\n\n";
	for (i = 0; i < DStatesNumber; i++)
	{
		cout << "项目" << i << ":  ";
		j = 0;
		while (DStates[i][j] != -1)
		{
			cout << DStates[i][j] << " ";
			j++;
		}
		cout << endl;
	}
	cout << "\n------------------------" << endl;
	// 输出Dtran表项
	cout << "\n第六步: 构造Dtran表\n\n状态 ";
	for (j = 0; j < edgeNumber; j++)
	{
		cout << "    " << edge[j];
	}
	cout << "    是否接收" << endl;
	for (i = 0; i < DtranNumber; i++)
	{
		if (i < 10)  cout << "   " << i << " ";
		else if (i < 100)  cout << "  " << i << " ";
		else if (i < 1000)  cout << " " << i << " ";
		else  cout << i << " ";
		for (j = 0; j < edgeNumber; j++)
		{
			if (Dtran[i][j] < 0)  cout << "     ";
			else if (Dtran[i][j] < 10)  cout << "    " << Dtran[i][j];
			else if (Dtran[i][j] < 100)  cout << "   " << Dtran[i][j];
			else if (Dtran[i][j] < 1000)  cout << "  " << Dtran[i][j];
			else  cout << " " << Dtran[i][j];
		}
		if (AcceptStates[i] == 1)
		{
			cout << "    Acc";
		}
		cout << endl;
	}
	cout << "\n------------------------" << endl;
	// 反复检测Dtran表中是否能化简，能则继续化简
	int DtranNumberAfterMinimization = MinimizeDFAStates(Dtran, AcceptStates, DtranNumber, edgeNumber);
	while (DtranNumberAfterMinimization != DtranNumber)
	{
		DtranNumber = DtranNumberAfterMinimization;
		DtranNumberAfterMinimization = MinimizeDFAStates(Dtran, AcceptStates, DtranNumber, edgeNumber);
	}
	// 将Dtran表的内容拷贝到DFA表
	DFATable = new TransitionTable(DtranNumber, edgeNumber);
	for (i = 0; i < DtranNumber; i++)
	{
		for (j = 0; j < edgeNumber; j++)
		{
			DFATable->SetValue(i, j, Dtran[i][j]);
		}
	}
	// 输出DFA状态表
	cout << "\n第七步: 构造最小DFA\n\n状态 ";
	for (j = 0; j < edgeNumber; j++)
	{
		cout << "    " << edge[j];
	}
	cout << "    是否接收" << endl;
	for (i = 0; i < DtranNumber; i++)
	{
		if (i < 10)  cout << "   " << i << " ";
		else if (i < 100)  cout << "  " << i << " ";
		else if (i < 1000)  cout << " " << i << " ";
		else  cout << i << " ";
		for (j = 0; j < edgeNumber; j++)
		{
			if (DFATable->GetValue(i, j) < 0)  cout << "     ";
			else if (DFATable->GetValue(i, j) < 10)  cout << "    " << DFATable->GetValue(i, j);
			else if (DFATable->GetValue(i, j) < 100)  cout << "   " << DFATable->GetValue(i, j);
			else if (DFATable->GetValue(i, j) < 1000)  cout << "  " << DFATable->GetValue(i, j);
			else  cout << " " << DFATable->GetValue(i, j);
		}
		if (AcceptStates[i] == 1)
		{
			cout << "    Acc";
		}
		cout << endl;
	}
	cout << "\n------------------------" << endl;
	// 析构DStates和Dtran表以及AcceptStates数组
	for (i = 0; i < NFAStatesNumber + 1; i++)
	{
		delete[] DStates[i];
		delete[] Dtran[i];
	}
	delete[] DStates;
	delete[] Dtran;
}
// 从字符串中删除第一个字符
void DFA::RemoveFirstSymbol(char *buf, int &len)
{
	for (int i = 0; i < len - 1; i++)
	{
		buf[i] = buf[i + 1];
	}
	len--;
	buf[len] = '\0';
}
// 从ASCII文件中找出所有的匹配式
void DFA::FindMatchingPatternInFile()
{
	cout << "\n第八步: 查找匹配字符串\n\n";
	
	char filePath[128];
	fstream infile;
	infile.open("Test.txt", ios::in );
	//Test.txt中存放的是要识别的C-minus语言编写的字符串
	if (!infile)
	{
		cout << "\n打开文件" << filePath << "失败！" << endl;
		_getch();
		exit(1);
	}
	cout << "请输入保存记录的文件" << endl;
	cin >> filePath;
	fstream outfile;
	outfile.open(filePath, ios::out | ios::trunc);
	if (!outfile)
	{
		cout << "\n建立文件" << filePath << "失败！" << endl;
		_getch();
		exit(1);
	}
	// 开始验证正则表达式的匹配串
	int ln = 1, col = 0, bufHead = 0;
	int state = 0;
	int count = 0;
	char buf[512];
	int curr = 0;
	int len = 0;
	char ch;
	while (infile.get(ch))
	{
		if ((ch == '\n') || (ch == ' '))
		{
			while (curr < len)
			{
				state = 0;
				while ((state != -1) && (curr < len))
				{
					state = DFATable->Transit(state, buf[curr], edge);
					if (AcceptStates[state] == 1)
					{
						outfile << "\nLn " << ln << ", Col " << bufHead << ": ";
						outfile.write(buf, curr + 1);
						count++;
					}
					curr++;
				}
				RemoveFirstSymbol(buf, len);
				bufHead++;
				curr = 0;
			}
			if (ch == '\n')
			{
				ln++;
				col = 0;
			}
			if (ch == ' ')
			{
				col++;
			}
		}
		else
		{
			col++;
			if (len == 0)
			{
				bufHead = col;
			}
			buf[len++] = ch;
			if (len >= 256)
			{
				cout << "读取字符串的长度超过最大限额！" << endl;
				_getch();
				exit(1);
			}
		}
	}
	while (curr < len)
	{
		state = 0;
		curr = 0;
		while ((state != -1) && (curr < len))
		{
			state = DFATable->Transit(state, buf[curr], edge);
			if (AcceptStates[state] == 1)
			{
				outfile << "\nLn " << ln << ", Col " << bufHead << ": ";
				outfile.write(buf, curr + 1);
				count++;
			}
			curr++;
		}
		RemoveFirstSymbol(buf, len);
		bufHead++;
	}
	if (count > 0)
	{
		outfile << "\n\n一共找到" << count << "匹配字符串";
	}
	else
	{
		outfile << "\n\n没有找到任何匹配字符串";
	}
	infile.close();
	outfile.close();
	cout << "\n查找结果已保存在" << filePath << "中\n"
		<< "\n------------------------" << endl;
}



// 主函数
void main()
{
	
	DFA dfa;
	dfa.GetRegExp();
	dfa.InsertCatNode();
	dfa.RegExpToPost();
	dfa.GetEdgeNumber();
	dfa.ThompsonConstruction();
	dfa.SubsetConstruction();
	dfa.FindMatchingPatternInFile();
	system("pause");
	return;
	
}

/////////////////////////////////////////////////

