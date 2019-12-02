#include "bst_set.h"

void BSTSet::copy(const BSTSet& s) {
	root = nullptr; n = s.n;
	Stack<Node*> stack, helper;
	push(stack, s.root);
	while (stack.notEmpty()) {
		Node *p = pop(stack), *q = nullptr, *r = nullptr;
		if (helper.notEmpty()) r = pop(helper);
		while (p) {
			if (q) q = q->left = new Node(p->key);
			else q = new Node(p->key);
			if (!root) root = q;
			if (r) r->right = q, r = nullptr;
			if (p->right) {
				push(stack, p->right);
				push(helper, q);
			}
			p = p->left;
		}
	}
}

void BSTSet::erase() {
	Stack<Node*> stack;
	Node *p = root;
	while (true) {
		while (p) {
			push(stack, p);
			p = p->left;
		}
		if (stack.notEmpty()) {
			Node *e = pop(stack);
			p = e->right;
			delete e;
		}
		else break;
	}
	root = nullptr; n = 0;
}

BSTSet::Node* BSTSet::search(int k) const {
	Node *p = root;
	while (p && k != p->key) {
		if (k < p->key) p = p->left;
		else p = p->right;
	}
	return p;
}

BSTSet& BSTSet::operator+=(int k) {
	Node *p = root, *q = nullptr;
	while (p) {
		q = p;
		if (k == p->key) throw Duplicate();
		if (k < p->key) p = p->left;
		else p = p->right;
	}
	if (!q) root = new Node(k);
	else if (k < q->key) q->left = new Node(k);
	else q->right = new Node(k);
	++n;
	return *this;
}

BSTSet::Node* BSTSet::handler(Node*& p) {
	Node *r, *s, *t;
	if (!p->left) r = p->right;
	else if (!p->right) r = p->left;
	else {
		t = p; r = p->right; s = r->left;
		while (s) {
			t = r, r = s;
			s = s->left;
		}
		if (t != p) {
			t->left = r->right;
			r->right = p->right;
		}
		r->left = p->left;
	}
	return r;
}

BSTSet& BSTSet::operator-=(int k) {
	if (!root) throw Empty();
	Node *p = root, *q = nullptr;
	while (p && k != p->key) {
		q = p;
		if (k < p->key) p = p->left;
		else p = p->right;
	}
	if (!p) throw NotFound();
	Node *r = handler(p);
	if (!q) root = r;
	else if (p == q->left) q->left = r;
	else q->right = r;
	--n; delete p;
	return *this;
}

BSTSet& BSTSet::removeInterval(int min, int max) {
	if (min > max) throw Interval();
	if (!root) throw Empty();
	Node *p = root, *q = nullptr;
	while (p) {
		if (p->key < min) {
			q = p;
			p = p->right;
		}
		else if (p->key > max) {
			q = p;
			p = p->left;
		}
		else {
			Node *r = handler(p);
			if (!q) root = r;
			else if (p == q->left) q->left = r;
			else q->right = r;
			--n; delete p;
			p = r;
		}
	}
	return *this;
}

BSTSet operator-(const BSTSet& a, const BSTSet& b) {
	BSTSet s;
	Stack<BSTSet::Node*> stack;
	push(stack, a.root);
	while (stack.notEmpty()) {
		BSTSet::Node *p = pop(stack);
		while (p) {
			if (!b.member(p->key)) s += p->key;
			if (p->right) push(stack, p->right);
			p = p->left;
		}
	}
	return s;
}

ostream& operator<<(ostream& os, const BSTSet& s) {
	if (!s.root) throw Empty();
	Stack<BSTSet::Node*> stack;
	BSTSet::Node *p = s.root;
	int i = 0; os << '{';
	while (true) {
		while (p) {
			push(stack, p);
			p = p->left;
		}
		if (stack.notEmpty()) {
			p = pop(stack);
			++i;
			os << p->key << (i == s.n ? "}" : ", ");
			p = p->right;
		}
		else break;
	}
	return os;
}