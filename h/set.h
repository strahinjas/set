#ifndef _SET_H_
#define _SET_H_

#include <exception>

class Set {
public:
	virtual ~Set() {}
	virtual bool member(int k) const = 0;
	virtual Set& operator+=(int k) = 0;
	virtual Set& operator-=(int k) = 0;
	virtual Set& removeInterval(int min, int max) = 0;

	friend auto card(const Set& s) { return s.n; }
protected:
	int n = 0;
};

class Empty : public std::exception {
public:
	const char* what() const noexcept override { return "\nGreska: Skup je prazan!\n\n"; }
};

class Duplicate : public std::exception {
public:
	const char* what() const noexcept override { return "\nGreska: Uneti element vec pripada skupu!\n\n"; }
};

class NotFound : public std::exception {
public:
	const char* what() const noexcept override { return "\nGreska: Trazeni element se ne nalazi u skupu!\n\n"; }
};

class Interval : public std::exception {
public:
	const char* what() const noexcept override { return "\nGreska: Pogresne granicne vrednosti intervala!\n\n"; }
};

class Error : public std::exception {
public:
	const char* what() const noexcept override { return "\nGreska: Neuspesno otvaranje datoteke!\n\n"; }
};

#endif