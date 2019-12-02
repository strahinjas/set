#ifndef _STACK_H_
#define _STACK_H_

#include <exception>

class Underflow : public std::exception {
public:
	const char* what() const noexcept override { return "\nGreska: Uzimanje podatka sa praznog steka!\n\n"; }
};

template<typename T> class Stack {
public:
	Stack() { top = nullptr; }
	Stack(const Stack& s) { copy(s); }
	Stack(Stack&& s) { move(s); }
	~Stack() { erase(); }

	Stack& operator=(const Stack& s) { if (this != &s) erase(), copy(s); return *this; }
	Stack& operator=(Stack&& s) { if (this != &s) erase(), move(s); return *this; }

	bool notEmpty() const { return top; }
	friend void push(Stack& s, T t) {
		Element *p = new Element(t, s.top);
		s.top = p;
	}
	friend T pop(Stack& s) {
		if (!s.top) throw Underflow();
		Element *p = s.top;
		s.top = s.top->next;
		T t = p->info;
		delete p;
		return t;
	}
	friend T peek(const Stack& s) {
		if (!s.top) throw Underflow();
		else return s.top->info;
	}
private:
	struct Element {
		T info; Element *next;
		Element(const T& i, Element *n = nullptr) : info(i), next(n) {}
	};

	Element *top;

	void copy(const Stack& s);
	void move(Stack& s) {
		top = s.top;
		s.top = nullptr;
	}
	void erase();
};

template<typename T> void Stack<T>::copy(const Stack& s) {
	top = nullptr;
	Element *p = nullptr;
	for (Element *e = s.top; e; e = e->next)
		p = (top ? p->next : top) = new Element(e->info);
}

template<typename T> void Stack<T>::erase() {
	while (top) {
		Element *e = top;
		top = top->next;
		delete e;
	}
}

#endif