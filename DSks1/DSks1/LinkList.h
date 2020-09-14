#pragma once

#include<iostream>

#include<stdlib.h>
#include<Windows.h>
template<class T>
class LinkNode {	 	       		//��������Ķ���
public:
	T data;			       	//������
	LinkNode <T>*link;     		//��ָ����
	LinkNode(LinkNode<T>*ptr = NULL) {
		link = ptr;
	} 			//����ʼ��ָ���Ա�Ĺ��캯��
	LinkNode(const T&item, LinkNode<T> *ptr = NULL) {
		data = item;
		link = ptr;
	} 	//��ʼ��������ָ���Ա�Ĺ��캯�� 
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
	int Delete(int i);//ɾ����i��Ԫ��
	int Remove(T&x);//����Ԫ��ֵɾ��
	int Length()const;
	int Trans();
	void makeEmpty();
	int DATA[100];
	int length = 0;
	LinkNode<T> *getHead() const { return first; }; //���ظ���ͷ���
	LinkNode<T>*Locate(int i);
	bool IsEmpty() const//�жϱ��Ƿ�Ϊ��
	{
		return first->link == NULL ? true : false;
	}

	LinkNode<T> *first;
};

template<class T>
LinkList<T>::~LinkList() {
	LinkNode<T> *q;
	while (first->link != NULL) {
		q = first->link;              	//���汻ɾ���
		first->link = q->link;    	//������ժ�¸ý��
		delete q;		        	//ɾ��
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
		q = first->link;              	//���汻ɾ���
		first->link = q->link;    	//������ժ�¸ý�� 
		delete q;		        	//ɾ��
	}
}
template<class T>
int LinkList<T>::Length() const {
	LinkNode<T> *p = first->link;
	//���ָ�� p ָʾ��һ�����
	int count = 0;
	while (p != NULL) {      //��������
		p = p->link;
		count++;
	}
	return count;
}
template<class T>
LinkNode<T> *LinkList<T>::Locate(int i) {
	//�������ر��е� i ��Ԫ�صĵ�ַ����i < 0�� i ��
	//�����н��������򷵻�NULL��
	if (i < 0) return NULL;		//i������
	LinkNode<T> *current = first; 
	int k = 0;
	while (current != NULL && k < i)
	{
		current = current->link;	
		k++;
	}
	return current;  //���ص� i �Ž���ַ��NULL
}
template<class T>
int LinkList<T>::Insert( int&x)
{
	LinkNode<T>*current = first;
	if (first->link == NULL) {
		LinkNode<T>*p = new LinkNode<T>(x);
		if (p == NULL) {
			AfxMessageBox(_T("�ڴ�������"));
			exit(1);
		}

		first->link = p;		//(1)����һ���µĽ��q��
						//(2)���˽���������ֵΪx����������linkָ��ָ���һ����㣬��first��
						//(3)��first�޸�Ϊָ���µĽ��p��
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
int LinkList<T>::Delete(int i) {//ɾ����i��Ԫ��
	LinkNode<T> *current1 = Locate(i - 1);
	if (current1 == NULL || current1->link == NULL)
		return -1; 	//ɾ�����ɹ� 	
	LinkNode<T> *del = current1->link;
	current1->link = del->link;
	delete del;
	return 0;
}
template<class T>
int LinkList<T>::Remove(T&x)//��ȡԪ��ֵΪx��Ԫ��λ��
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
