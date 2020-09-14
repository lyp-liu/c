#pragma once

#include<iostream>

#include<stdlib.h>
#include<Windows.h>
template<class T>
class LinkNode {	 	       		//链表结点类的定义
public:
	T data;			       	//数据域
	LinkNode <T>*link;     		//链指针域
	LinkNode(LinkNode<T>*ptr = NULL) {
		link = ptr;
	} 			//仅初始化指针成员的构造函数
	LinkNode(const T&item, LinkNode<T> *ptr = NULL) {
		data = item;
		link = ptr;
	} 	//初始化数据与指针成员的构造函数 
};
class DSksDlg;
template<class T>
class LinkList 
{
	friend class DSksDlg;
public:
	LinkList() { first = new LinkNode<T>; };
	~LinkList();
	//void CreateList(LinkList<T>L);
	int Insert( int&x);
	int Delete(int i);//删除第i个元素
	int Remove(T&x);//根据元素值删除
	int Length()const;
	int Trans();
	void makeEmpty();
	int DATA[100];
	int length = 0;
	LinkNode<T> *getHead() const { return first; }; //返回附加头结点
	LinkNode<T>*Locate(int i);
	bool IsEmpty() const//判断表是否为空
	{
		return first->link == NULL ? true : false;
	}

	LinkNode<T> *first;
};

template<class T>
LinkList<T>::~LinkList() {
	LinkNode<T> *q;
	while (first->link != NULL) {
		q = first->link;              	//保存被删结点
		first->link = q->link;    	//从链上摘下该结点
		delete q;		        	//删除
	}
}
/*template<class T>
void LinkList<T>::CreateList(LinkList<T>first) {
	first = (LinkNode *)malloc(sizeof(LinkNode));
	first->next = NULL;
}*/

template<class T>
void LinkList<T>::makeEmpty() {
	LinkNode<T> *q;
	while (first->link != NULL) {
		q = first->link;              	//保存被删结点
		first->link = q->link;    	//从链上摘下该结点 
		delete q;		        	//删除
	}
}
template<class T>
int LinkList<T>::Length() const {
	LinkNode<T> *p = first->link;
	//检测指针 p 指示第一个结点
	int count = 0;
	while (p != NULL) {      //逐个结点检测
		p = p->link;
		count++;
	}
	return count;
}
template<class T>
LinkNode<T> *LinkList<T>::Locate(int i) {
	//函数返回表中第 i 个元素的地址。若i < 0或 i 超
	//出表中结点个数，则返回NULL。
	if (i < 0) return NULL;		//i不合理
	LinkNode<T> *current = first; 
	int k = 0;
	while (current != NULL && k < i)
	{
		current = current->link;	
		k++;
	}
	return current;  //返回第 i 号结点地址或NULL
}
template<class T>
int LinkList<T>::Insert( int&x)
{
	LinkNode<T>*current = first;
	if (first->link == NULL) {
		LinkNode<T>*p = new LinkNode<T>(x);
		if (p == NULL) {
			AfxMessageBox(_T("内存分配错误"));
			exit(1);
		}

		first->link = p;		//(1)创建一个新的结点q。
						//(2)将此结点的数据域赋值为x，并将它的link指针指向第一个结点，即first。
						//(3)将first修改为指向新的结点p。
	}
	else {
		for (;; ) {
			if (current->link != NULL) {
				current = current->link;

			}
			
			else {
				LinkNode<T>*newNode = new LinkNode<T>(x);
				current->link = newNode;
				break;
			}
		}
	}
	return 0;
}
template<class T>
int LinkList<T>::Delete(int i) {//删除第i个元素
	LinkNode<T> *current1 = Locate(i - 1);
	if (current1 == NULL || current1->link == NULL)
		return -1; 	//删除不成功 	
	LinkNode<T> *del = current1->link;
	current1->link = del->link;
	delete del;
	return 0;
}
template<class T>
int LinkList<T>::Remove(T&x)//获取元素值为x的元素位置
{
	LinkNode<T>*current = first;
	int i = 0;
	while (current->link != NULL) {
		if (current->link->data == x) {
			LinkNode<T>*del = current->link;
			current->link = del->link;
			delete del;
		}
		if (current->link != NULL && current->link->data != x)
			current = current->link;

	}
	return 0;
}
template<class T>
int LinkList<T>::Trans() {
	int length = Length();
	LinkNode<T>*current = first;
	int arr[100];
	for (int i = 0; i < length; i++) {
		arr[i] = current->link->data;
		current = current->link;
	}
	LinkNode<T>*current1 = first;
	for (int i = length - 1; i >= 0; i--) {
		current1->link->data = arr[i];
		current1 = current1->link;
	}
	return 0;
}

template<class T>


bool IsExitsLoop(LinkNode<T>*head)
{
	LinkNode<T> *slow = head, *fast = head;
	while (fast && fast->link)
	{
		
		slow = slow->link;
		
		fast = fast->link->link;
		if (slow == fast) break;
	}
	fast = head;
	while (slow != fast) {
		n1 = slow;
		slow = slow->link;
		fast = fast->link;
		
	}
	m1 = fast;
	return !(fast == NULL || fast->link == NULL);
}
