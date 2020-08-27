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

	~ListSet() { erase(); }

	ListSet(const ListSet& s) { copy(s); }
	ListSet(ListSet&& s) noexcept : head(s.head), tail(s.tail)
	{
		n = s.n;

		s.n = 0;
		s.head = s.tail = nullptr;
	}

	ListSet& operator=(const ListSet& s)
	{
		erase();

		copy(s);

		return *this;
	}
	ListSet& operator=(ListSet&& s) noexcept
	{
		erase();

		n = s.n;
		head = s.head;
		tail = s.tail;

		s.n = 0;
		s.head = s.tail = nullptr;

		return *this;
	}

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

	void copy(const ListSet& s);
	void erase();
};

#endif