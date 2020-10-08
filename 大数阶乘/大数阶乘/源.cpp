#include<iostream>
using namespace std;
struct Node
{
	int data;
	Node* next;
	Node() { //初始化节点
	this->next = NULL; 
	this->data = 0; 
	}
	Node(int data) {
		this->data = data;
	}
};
class Link {
private:
	Node *first;//头节点
	int n;
public:
	Link() {};//构造函数
	~Link() {};//析构函数
	Link(int n) {//重载构造
		this->n = n;
		first = new Node();
		first->data = 1;
	};
	void print();
	void Operate();//实现一个节点保存三位数的函数
};
void Out(Node*node) {
	if (node != NULL) {
		Out(node->next);//递归调用，直到链尾
		if (node->next == NULL)//如果到了链尾，直接输出保存的数据
			cout << node->data;
	
		else 
		{//后面保存的数据可以为000，所以格式控制输出为固定三位
			cout.fill('0');//设置填充字符
			cout.width(3);//设置域宽
			cout << node->data;
		}
	}
}
void Link::print()
{
	Out(first);
}

void Link::Operate()
{
	int flag;
	for (int i = 1; i <= n; i++) {
		flag = 0;//初始化
		Node*current = first;
		while (current != NULL) {
			//当前的值乘i加上低位的进位flag就是当前节点应该取的值
			current->data = current->data*i + flag;
			if (current->data >= 1000 && current->next == NULL) {
				//如果当前的数值大于1000必须进位，如果后续节点为空需要添加一个新节点
				current->next = new Node();
			}
			//flag设置为低一位的进位
			flag=current->data / 1000;
			//当前节点的数值对一千取余即为该节点应取的值
			current->data = current->data % 1000;
			//判断后续节点
			current = current->next;
		}
	}
}


int main() {
	int n = 0;
	cout << "请输入n的值（求n的阶乘）：" << endl;
	cin >> n;
	Link test(n);//实例化一个对象test
	test.Operate();//进行数据操作
	test.print();//输出数据
	system("pause");
	return 0;
	
}