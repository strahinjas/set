#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

class Empty : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "\nGreska: Skup je prazan!\n\n";
	}
};

class Duplicate : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "\nGreska: Uneti element vec pripada skupu!\n\n";
	}
};

class NotFound : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "\nGreska: Trazeni element se ne nalazi u skupu!\n\n";
	}
};

class Interval : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "\nGreska: Pogresne granicne vrednosti intervala!\n\n";
	}
};

class Error : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "\nGreska: Neuspesno otvaranje datoteke!\n\n";
	}
};

class Underflow : public std::exception
{
public:
	const char *what() const noexcept override
	{
		return "\nGreska: Uzimanje podatka sa praznog steka!\n\n";
	}
};

#endif