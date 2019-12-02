#ifndef _BST_SET_H_
#define _BST_SET_H_

#include "set.h"
#include "stack.h"
#include <iostream>
using namespace std;

class BSTSet : public Set {
public:
	BSTSet() { root = nullptr; }
	BSTSet(const BSTSet& s) { copy(s); }
	BSTSet(BSTSet&& s) { move(s); }
	~BSTSet() { erase(); }

	BSTSet& operator=(const BSTSet& s) { if (this != &s) erase(), copy(s); return *this; }
	BSTSet& operator=(BSTSet&& s) { if (this != &s) erase(), move(s); return *this; }

	bool member(int k) const override { return search(k); }
	BSTSet& operator+=(int k) override;
	BSTSet& operator-=(int k) override;
	BSTSet& removeInterval(int min, int max) override;
	friend BSTSet operator-(const BSTSet& a, const BSTSet& b);

	friend ostream& operator<<(ostream& os, const BSTSet& s);
private:
	struct Node {
		int key;
		Node *left, *right;
		Node(int k, Node *l = nullptr, Node *r = nullptr) : key(k), left(l), right(r) {}
	};

	Node* root;
	Node* search(int k) const;
	Node* handler(Node*& p);

	void copy(const BSTSet& s);
	void move(BSTSet& s) {
		n = s.n; root = s.root;
		s.root = nullptr;
	}
	void erase();
};

#endif