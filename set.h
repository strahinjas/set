#ifndef _SET_H_
#define _SET_H_

class Set
{
public:
	virtual ~Set() { }

	virtual bool member(int k) const = 0;
	virtual Set& operator+=(int k) = 0;
	virtual Set& operator-=(int k) = 0;
	virtual Set& removeInterval(int min, int max) = 0;

	int size() const { return n; }
protected:
	int n = 0;
};

#endif