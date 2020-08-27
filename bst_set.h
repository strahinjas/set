#ifndef _BST_SET_H_
#define _BST_SET_H_

#include <iostream>

#include "set.h"

class BSTSet : public Set
{
public:
	BSTSet() { root = nullptr; }

	~BSTSet() { erase(); }

	BSTSet(const BSTSet& s) { copy(s); }
	BSTSet(BSTSet&& s) noexcept : root(s.root)
	{
		n = s.n;

		s.n = 0;
		s.root = nullptr;
	}

	BSTSet& operator=(const BSTSet& s)
	{
		erase();

		copy(s);

		return *this;
	}
	BSTSet& operator=(BSTSet&& s) noexcept
	{
		erase();

		n = s.n;
		root = s.root;

		s.n = 0;
		s.root = nullptr;

		return *this;
	}

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

	void copy(const BSTSet& s);
	void erase();
};

#endif