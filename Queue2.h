#ifndef QUEUE_H
#define QUEUE_H
#include<cassert>
#include"node.h"

template<class T>
class Queue {
private:
	Node<T> *front, *rear;
	int count;
public:
	Queue();						//构造函数，初始化队头指针，队尾指针，元素个数
	void insert(const T	&item);		//新元素入队
	T remove();						//元素出队
	void clear();					//清空队列
	const T &getFront() const;		//访问队首元素

	int getLength() const;			//求队列长度（元素个数）
	bool isEmpty() const;			//判断队列空否
	bool isFull() const;			//判断队列满否
};

template<class T>
Queue<T>::Queue() { front = rear = 0; count = 0; }

template<class T>
void Queue<T>::insert(const T &item) {
	assert(!isFull());
	Node<T> *p = new Node<T> (item);
	if (rear == 0) {
		front = p;
	}
	else {
		rear->insertAfter(p);
	}
	count++;
	rear = p;
}

template<class T>
T Queue<T>::remove() {		//一个问题：如何重新设置头指针
	assert(!isEmpty());
	Node<T> *p = front->nextNode();
	T item;
	item = front->data;
	delete front;
	front = p;
	count--;
	return item;

}

template<class T>
void Queue<T>::clear() {
	Node<T> *curr, *next;
	curr = front;
	while (curr != 0) {
		next = curr->nextNode();
		delete(curr);
		curr = next;
	}
	front = rear = 0;
	count = 0;
}

template<class T>
const T& Queue<T>::getFront() const {
	cassert(!isEmpty());
	return front->data;
}

template<class T>
int Queue<T>::getLength() const {
	return count;
}

template<class T>
bool Queue<T>::isEmpty() const {
	return count == 0;
}

template<class T>
bool Queue<T>::isFull() const {
	return count == 50;
}
#endif
