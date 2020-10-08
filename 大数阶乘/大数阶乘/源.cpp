#include<iostream>
using namespace std;
struct Node
{
	int data;
	Node* next;
	Node() { //��ʼ���ڵ�
	this->next = NULL; 
	this->data = 0; 
	}
	Node(int data) {
		this->data = data;
	}
};
class Link {
private:
	Node *first;//ͷ�ڵ�
	int n;
public:
	Link() {};//���캯��
	~Link() {};//��������
	Link(int n) {//���ع���
		this->n = n;
		first = new Node();
		first->data = 1;
	};
	void print();
	void Operate();//ʵ��һ���ڵ㱣����λ���ĺ���
};
void Out(Node*node) {
	if (node != NULL) {
		Out(node->next);//�ݹ���ã�ֱ����β
		if (node->next == NULL)//���������β��ֱ��������������
			cout << node->data;
	
		else 
		{//���汣������ݿ���Ϊ000�����Ը�ʽ�������Ϊ�̶���λ
			cout.fill('0');//��������ַ�
			cout.width(3);//�������
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
		flag = 0;//��ʼ��
		Node*current = first;
		while (current != NULL) {
			//��ǰ��ֵ��i���ϵ�λ�Ľ�λflag���ǵ�ǰ�ڵ�Ӧ��ȡ��ֵ
			current->data = current->data*i + flag;
			if (current->data >= 1000 && current->next == NULL) {
				//�����ǰ����ֵ����1000�����λ����������ڵ�Ϊ����Ҫ���һ���½ڵ�
				current->next = new Node();
			}
			//flag����Ϊ��һλ�Ľ�λ
			flag=current->data / 1000;
			//��ǰ�ڵ����ֵ��һǧȡ�༴Ϊ�ýڵ�Ӧȡ��ֵ
			current->data = current->data % 1000;
			//�жϺ����ڵ�
			current = current->next;
		}
	}
}


int main() {
	int n = 0;
	cout << "������n��ֵ����n�Ľ׳ˣ���" << endl;
	cin >> n;
	Link test(n);//ʵ����һ������test
	test.Operate();//�������ݲ���
	test.print();//�������
	system("pause");
	return 0;
	
}