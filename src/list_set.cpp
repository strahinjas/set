#include "list_set.h"

void ListSet::copy(const ListSet& s) {
	n = s.n;
	head = tail = nullptr;
	for (Element *e = s.head; e; e = e->next)
		tail = (head ? tail->next : head) = new Element(e->info, tail);
}

void ListSet::erase() {
	while (head) {
		Element *e = head;
		head = head->next;
		delete e;
	}
	tail = nullptr;
}

bool ListSet::member(int k) const {
	if (!head) return false;
	Element *e;
	if (k - head->info <= tail->info - k) {
		e = head;
		while (e && e->info < k) e = e->next;
	}
	else {
		e = tail;
		while (e && e->info > k) e = e->prev;
	}
	if (e && e->info == k) return true;
	return false;
}

ListSet& ListSet::operator+=(int k) {
	if (!head) head = tail = new Element(k);
	else if (k - head->info <= tail->info - k) {
		Element *e = head;
		while (e && e->info < k) e = e->next;
		if (e && e->info == k) throw Duplicate();
		(e->prev ? e->prev->next : head) = (e ? e->prev : tail) = new Element(k, e->prev, e);
	}
	else {
		Element *e = tail;
		while (e && e->info > k) e = e->prev;
		if (e && e->info == k) throw Duplicate();
		(e->next ? e->next->prev : tail) = e->next = new Element(k, e, e->next);
	}
	++n;
	return *this;
}

ListSet& ListSet::operator-=(int k) {
	if (!head) throw Empty();
	if (k - head->info <= tail->info - k) {
		Element *e = head;
		while (e && e->info < k) e = e->next;
		if (e && e->info == k) {
			(e->prev ? e->prev->next : head) = e->next;
			(e->next ? e->next->prev : tail) = e->prev;
			--n;
			delete e;
		}
		else throw NotFound();
	}
	else {
		Element *e = tail;
		while (e && e->info > k) e = e->prev;
		if (e && e->info == k) {
			(e->next ? e->next->prev : tail) = e->prev;
			e->prev->next = e->next;
			--n;
			delete e;
		}
		else throw NotFound();
	}
	return *this;
}

ListSet& ListSet::removeInterval(int min, int max) {
	if (min > max) throw Interval();
	if (!head) throw Empty();
	Element *prev = nullptr;
	if (head->info - min <= tail->info - max) {
		Element *e = head;
		while (e && e->info < min) { prev = e; e = e->next; }
		while (e && e->info <= max) {
			Element *p = e;
			e = e->next;
			--n;
			delete p;
		}
		(prev ? prev->next : head) = e;
		(e ? e->prev : tail) = prev;
	}
	else {
		Element *e = tail;
		while (e && e->info > max) { prev = e; e = e->prev; }
		while (e && e->info >= min) {
			Element *p = e;
			e = e->prev;
			--n;
			delete p;
		}
		(prev ? prev->prev : tail) = e;
		(e ? e->next : head) = prev;
	}
	return *this;
}

ListSet operator-(const ListSet& a, const ListSet& b) {
	ListSet s;
	ListSet::Element *p = a.head, *q = b.head;
	while (p && q) {
		if (p->info < q->info) {
			s += p->info;
			p = p->next;
		}
		else if (p->info == q->info) p = p->next, q = q->next;
		else q = q->next;
	}
	while (p) { s += p->info; p = p->next; }
	return s;
}

ostream& operator<<(ostream& os, const ListSet& s) {
	if (!s.head) throw Empty();
	os << '{';
	for (ListSet::Element *e = s.head; e; e = e->next) os << e->info << (e->next ? ", " : "}");
	return os;
}