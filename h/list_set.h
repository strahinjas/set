#ifndef _LIST_SET_H_
#define _LIST_SET_H_

#include "set.h"
#include <iostream>
using namespace std;

class ListSet : public Set {
public:
	ListSet() { head = tail = nullptr; }
	ListSet(const ListSet& s) { copy(s); }
	ListSet(ListSet&& s) { move(s); }
	~ListSet() { erase(); }

	ListSet& operator=(const ListSet& s) { if (this != &s) erase(), copy(s); return *this; }
	ListSet& operator=(ListSet&& s) { if (this != &s) erase(), move(s); return *this; }

	bool member(int k) const override;
	ListSet& operator+=(int k) override;
	ListSet& operator-=(int k) override;
	ListSet& removeInterval(int min, int max) override;
	friend ListSet operator-(const ListSet& a, const ListSet& b);

	friend ostream& operator<<(ostream& os, const ListSet& s);
private:
	struct Element {
		int info;
		Element *prev, *next;
		Element(int i, Element* p = nullptr, Element* n = nullptr) : info(i), prev(p), next(n) {}
	};

	Element *head, *tail;

	void copy(const ListSet& s);
	void move(ListSet& s) {
		n = s.n;
		head = s.head; tail = s.tail;
		s.head = s.tail = nullptr;
	}
	void erase();
};

#endif