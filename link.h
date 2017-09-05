#ifndef LINK_H
#define LINK_H
#include "node.h"
#include<cstdio>
#include<iostream>
using namespace std;
template<class T>
class Link {
private:
	//数据成员
	Node<T> *front, *rear;		//表头和表尾指针
	Node<T> *prevPtr, *currPtr;	//记录表当前遍历位置的指针，由插入和删除操作更新
	int size;					//表中元素个数
	int position;				//当前元素在表中的位置序号，有函数reset使用

	//函数成员
	//生成新结点，数据域为item，指针域为ptrNext
	Node<T> *newNode(const T &item, Node<T> *ptrNext = NULL);

	//释放结点
	void freeNode(Node<T> *p);

	//将链表L复制到当前表（假设当前表为空）
	//被复制构造函数和“operator=”调用
	void copy(const Link<T> &L);


public:
	Link();		//构造函数
	Link(const Link<T> &L);	//复制构造函数
	~Link();		//析构函数
	Link<T>& operator= (const Link<T> &L);	//重载赋值运算符

	int getSize() const;		//返回链表中元素个数
	bool isEmpty() const;		//链表是否为空

	void reset(int pos = 0);	//初始化游标的位置
	void next();				//使游标移动到下一个结点
	bool endOfList() const;		//游标是否到了链尾
	int currentPosition(void) const;	//返回游标当前的位置

	void insertFront(const T &item);	//在表头插入结点
	void insertRear(const T &item);		//在表尾添加结点
	void insertAt(const T &item);		//在当前结点之前插入结点
	void insertAfter(const T &item);	//在当前结点之后插入结点

	T deleteFront();		//删除头结点
	void deleteCurrent();	//删除当前结点

	T& data();		//返回对当前结点成员数据的引用
	const T& data() const;	//返回对当前成员数据的常引用

	//清空链表：释放所有结点的内存空间。被析构函数和“operator=”调用
	void clear();

};

//类的实现部分
template<class T>
Node<T> * Link<T>::newNode(const T &item, Node<T> *ptrNext/*=NULL*/) {
	Node<T> *p;
	p = new Node<T>(item, ptrNext);
	if (p == NULL) {
		cout << "Memory allocation failure" << endl;
		exit(1);
	}
	return p;
}

template<class T>
void Link<T>::freeNode(Node<T> *p) {
	delete p;
}

template<class T>
void Link<T>::copy(const Link<T>& L) {
	Node<T> *p = L.front;		//p用来遍历链表L
	int pos;
	while (p != NULL) {
		InsertRear(p->data);
		p = p->nextNode();
	}
	if (position == -1) 		//如果链表为空
		return;
	//在新链表中重新设置prevPtr,currPtr
	prevPtr = NULL;
	currPtr = front;
	for (pos = 0;pos != position;pos++) {
		prevPtr = currPtr;
		currPtr = currPtr->nextNode();
	}

}


template<class T>
Link<T> ::Link() {
	front = NULL;
	rear = NULL;
	currPtr = NULL;
	prevPtr = NULL;
	size = 0;
	position = -1;
}

template<class T>
Link<T>::Link(const Link<T>& L) {
	front = rear = NULL;
	prevPtr = currPtr = NULL;
	size = 0;
	position = -1;
	copy(L);
}

template<class T>
Link<T>::~Link() {
	clear();
}


template<class T>
Link<T>& Link<T>::operator=(const Link<T>&L) {
	if (this == &L)		//不能将链表赋值给它自身
		return *this;
	clear();
	copy(L);
	return *this;
}

template<class T>
int Link<T>::getSize() const {
	return size;
}

template<class T>
bool Link<T>::isEmpty() const {
	return size == 0;
}


template<class T>
void Link<T> :: reset(int pos/*=0*/) {
	int startPos;
	if (front == NULL)
		return;
	if (pos<0 || pos>size - 1) {		//如果指定位置不合法，返回
		cerr << "Reset:Invalid list position:" << pos << endl;
		return;
	}
	if (pos == 0) {		//如果pos为0，将指针重新设置到表头
		prevPtr = NULL;
		currPtr = front;
		position = 0;
	}
	else {			//否则重新设置currPtr,prevPtr,position
		currPtr = front->nextNode();
		prevPtr = front;
		startPos = 1;
		for (position = startPos;position != pos;position++) {
			prevPtr = currPtr;
			currPtr = currPtr->nextNode();
		}
	}
}

template<class T>
void Link<T>::next() {
	if (currPtr != NULL) {
		prevPtr = currPtr;
		currPtr = currPtr->nextNode();
		position++;
	}
}

template<class T>
bool Link<T>::endOfList()const {
	return currPtr == NULL;
}

template<class T>
int Link<T>::currentPosition(void)const {
	return position;
}

template<class T>
void Link<T>::insertFront(const T &item) {
	if (front != NULL)
		reset();
	insertAt(item);
}

template<class T>
void Link<T>::insertRear(const T &item) {
	Node<T> *p;
	prevPtr = rear;
	p = newNode(item);
	if (rear == NULL)
		front = rear = p;
	else {
		rear->insertAfter(p);
		rear = p;
	}
	currPtr = rear;
	position = size;
	size++;
}

template<class T>
void Link<T>::insertAt(const T &item) {
	Node<T> *nNode;
	if (prevPtr == NULL) {		//插入在链表头，包括将结点插入到空表中
		nNode = newNode(item, front);
		front = nNode;
	}
	else {					//插入到链表之中，将结点置于prevPtr之后
		nNode = newNode(item);
		prevPtr->insertAfter(nNode);
	}	
	if (prevPtr == rear) {		//正在向空表中插入，或者是插入到非空表的表尾
		rear = nNode;
		position = size;
	}
	currPtr = nNode;
	size++;
}

template<class T>
void Link<T>::insertAfter(const T &item) {
	Node<T> *p;
	p = newNode(item);
	if (front == NULL) {		//插入到空链表中
		front = rear = currPtr = p;
		position = 0;
	}
	else {
		if (currPtr == NULL)
			currPtr = prevPtr;
		currPtr->insertAfter(p);
		if (currPtr == rear) {
			rear = p;		//更新尾指针
			position = size;		//更新位置
		}
		else
			position++;
		prevPtr = currPtr;
		currPtr = p;
	}
	size++;
}

template<class T>
T Link<T>::deleteFront() {
	T item;
	reset();
	if (front == NULL) {
		cerr << "Invalid deletion!" << endl;
		exit(1);
	}
	item = currPtr->data;
	deleteCurrent();
	return item;
}

template<class T>
void Link<T>::deleteCurrent() {
	Node<T> *p;
	if (currPtr == NULL) {		//链表为空或者到达表尾
		cerr << "Invalid deletion!" << endl;
		exit(1);
	}
	if (prevPtr == NULL) {		//删除发生在表头
		p = front;
		front = front->nextNode();
	}
	else {	//分离prevPtr之后的一个结点，保存其地址
		p = prevPtr->deleteAfter();
	}
	if (p == rear) {
		rear = prevPtr;
		position--;
	}
	currPtr = p->nextNode();		//使currPtr越过被删除的结点
	freeNode(p);
	size--;
}

template<class T>
T& Link<T>::data() {
	if (size == 0 || currPtr == NULL) {
		cerr << "Data:invalid reference!" << endl;
		exit(1);
	}
	return currPtr->data;
}

template<class T>
void Link<T>::clear() {
	Node<T> *currPosition, *nextPosition;
	currPosition = front;
	while (currPosition != NULL) {
		nextPosition = currPosition->nextNode();
		freeNode(currPosition);
		currPosition = nextPosition;
	}
	front = rear = NULL;
	prevPtr = currPtr = NULL;
	size = 0;
	position = -1;
}
#endif
