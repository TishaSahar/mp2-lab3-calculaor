#pragma once

#include<iostream>
#include<exception>

using namespace std;

template <class T>
class ICollection {
public:
	//virtual ~ICollection() = 0;
	virtual int GetSize() = 0;

	virtual void push(const T& v) = 0;
	virtual T& pop() = 0;
	virtual bool IsEmpty() = 0;
	virtual bool IsFull() = 0;

};

template <class T>
class Queue: public ICollection<T> {
	T* mem;
	int n;
	int last, first;
	int next(int i){
		return ((i + 1) % n);
	}


public:
	Queue(int _n = 100);
	Queue(const Queue<T>& q);
	Queue<T>& operator=(const Queue<T>& q);
	~Queue();

	bool operator==(const Queue<T>& q)const;

	int GetSize();

	void push(const T& v);
	T& pop();

	bool IsFull();
	bool IsEmpty();
};

template <class T>
class Stack : public ICollection<T> {
	T* memS;
	int n;
	int top;
public:
	Stack(int _n = 100);
	Stack(const Stack<T>& s);
	Stack<T>& operator=(const Stack<T>& s);
	~Stack();

	bool operator==(const Stack<T>& q);

	int GetSize();

	void push(const T& v);
	T& pop();
	bool IsFull();
	bool IsEmpty();
};



template <class T>
Queue<T>::Queue(int _n = 100):n(_n + 1) {
	if (_n < 0)
		throw logic_error("Negative_length_of_queue");
	mem = new T[n];
	first = 0;
	last = n - 1;
}

template <class T>
Queue<T>::Queue(const Queue<T> &q) {
	n = q.n;
	mem = new T[n];
	first = q.first;
	last = q.last;
	for (int i = 0; i < n; i++)
	{
		mem[i] = q.mem[i];
	}
}

template <class T>
int Queue<T>::GetSize(){
	return n;
}
/*
template <class T>
int Queue<T>::next(int i) {
	return ((i + 1) % n);
}*/

template <class T>
Queue<T>::~Queue() {
	delete[]mem;
}

template <class T>
Queue<T> &Queue<T>::operator=(const Queue<T>& q) {
	if (this == &q) 
		return *this;
	delete[] mem;
	n = q.n;
	first = q.first;
	mem = new T[n];
	for (int i = 0; i < n; i++)
	{
		mem[i] = q.mem[i];
	}
	return *this;
}

template <class T>
bool Queue<T>::operator==(const Queue<T>& q)const{

	if (n != q.n)
		return false;

	if (IsEmpty() && q.IsEmpty()) 
		return true;

	if ((!IsEmpty() && q.IsEmpty()) || (IsEmpty() && !q.IsEmpty()))
		return false;



	int i = first;
	int j = q.first;
	if ((i != last) || (j != q.last))
		return false;

	while ((i != last) && (j != q.last))
	{
		if (mem[i] != q.mem[i]) 
			return false;
		i++;
		j++;
	}
	return true;
}

template <class T>
void Queue<T>::push(const T& v){
	if (IsFull()) { 
		throw logic_error("Queue_overflow");
	}

	last = next(last);
	mem[last] = v;
}

template <class T>
T& Queue<T>::pop()
{
	if (IsEmpty()) { throw logic_error("Queue_is_empty"); }
	int tmp = first;
	first = next(first);
	return mem[tmp];
}

template <class T>
bool Queue<T>::IsFull(){
	int t = next(next(last));
	return (t == first);
}

template <class T>
bool Queue<T>::IsEmpty(){
	return next(last) == first;
}


template <class T>
Stack<T>::Stack(int _n = 100) :n(_n) {
	if (_n < 0) 
		throw logic_error("Negative_length_of_stack");
	top = -1;
	memS = new T[n];
}

template <class T>
Stack<T>::Stack(const Stack<T> &q){
	n = s.n;
	top = s.top;
	memS = new T[n];
	for (int i = 0; i < n; i++)
	{
		memS[i] = s.memS[i];
	}
}

template <class T>
int Stack<T>::GetSize() {
	return n;
}

template <class T>
Stack<T>::~Stack() {
	delete[]memS;
}

template <class T>
Stack<T> &Stack<T>::operator=(const Stack<T>& q) {
	if (this == &s) 
		return *this;
	delete[] memS;
	n = s.n;
	memS = new T[n];
	top = s.top;
	for (int i = 0; i <= top; i++)
	{
		memS[i] = s.memS[i];
	}
	return *this;
}

template <class T>
bool Stack<T>::operator==(const Stack<T>& q) {
	if ((n != s.n)|| (top != s.top)) 
		return false;

	for (int i = 0; i < top; i++)
	{
		if (pStack[i] != s.pStack[i]) 
			return false;
	}
	
	return true;
}

template <class T>
void Stack<T>::push(const T& v) {
	if (IsFull()) { 
		throw logic_error("Stack_overflow");
	}
	else {
		top++;
		memS[top] = v;
	}
}

template <class T>
T& Stack<T>::pop()
{
	if (IsEmpty()) { 
		throw logic_error("Stack_is_empty"); 
	}
	int tmp = top;
	top--;
	return memS[tmp];
}

template <class T>
bool Stack<T>::IsFull() {
	return ((n-1) == top);
}

template <class T>
bool Stack<T>::IsEmpty() {
	return (top == -1);
}