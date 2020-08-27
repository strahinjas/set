#ifndef _STACK_H_
#define _STACK_H_

#include "exceptions.h"

template<typename T>
class Stack
{
public:
	Stack() { top = nullptr; }

	~Stack();

	bool empty() const { return !top; }

	void push(T t)
	{
		top = new Element(t, top);
	}

	T pop()
	{
		if (empty()) throw Underflow();

		Element* e = top;
		T t = e->info;

		top = top->next;
		delete e;

		return t;
	}

	T peek() const
	{
		if (empty()) throw Underflow();

		return top->info;
	}
private:
	struct Element
	{
		T info;
		Element* next;

		Element(const T& i, Element* n = nullptr) : info(i), next(n) {}
	};

	Element* top;
};

template<typename T>
Stack<T>::~Stack()
{
	while (top)
	{
		Element* e = top;
		top = top->next;
		delete e;
	}
}

#endif