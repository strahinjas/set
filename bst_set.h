#ifndef _BST_SET_H_
#define _BST_SET_H_

#include <iostream>

#include "set.h"

class BSTSet : public Set
{
public:
	BSTSet() { root = nullptr; }

	BSTSet(const BSTSet& s);

	~BSTSet();

	bool member(int k) const override
	{
		return search(k);
	}

	BSTSet& operator+=(int k) override;
	BSTSet& operator-=(int k) override;

	BSTSet& removeInterval(int min, int max) override;

	friend BSTSet operator-(const BSTSet& a, const BSTSet& b);

	friend std::ostream& operator<<(std::ostream& os, const BSTSet& s);
private:
	struct Node
	{
		int key;
		Node* left;
		Node* right;

		Node(int k, Node* l = nullptr, Node* r = nullptr) : key(k), left(l), right(r) {}
	};

	Node* root;
	Node* search(int k) const;
	Node* handler(Node* p);
};

#endif