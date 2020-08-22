#ifndef _LIST_SET_H_
#define _LIST_SET_H_

#include <iostream>

#include "set.h"

class ListSet : public Set
{
public:
	ListSet()
	{
		head = tail = nullptr;
	}

	ListSet(const ListSet& s);

	~ListSet();

	bool member(int k) const override;

	ListSet& operator+=(int k) override;
	ListSet& operator-=(int k) override;

	ListSet& removeInterval(int min, int max) override;

	friend ListSet operator-(const ListSet& a, const ListSet& b);

	friend std::ostream& operator<<(std::ostream& os, const ListSet& s);
private:
	struct Element
	{
		int info;
		Element* prev;
		Element* next;

		Element(int i, Element* p = nullptr, Element* n = nullptr) : info(i), prev(p), next(n) {}
	};

	Element* head;
	Element* tail;
};

#endif