// BigNum.cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "BigNum.h"

using namespace std;

inline int ctoi(char c){ return int(c) - 48;}

template <class Any>
inline Any & compare(Any & x, Any & y){ return x > y ? x : y; }

int powerOfTen(int n) // implementovat pres enum
{
	int x = 10;
	if(n == 0)
	{
		return 1;
	}
	for(int i = 1; i < n; i++)
	{
		x *= 10;
	}
	return x;
}

int error(void)
{
	return 1;
}

BigNum::BigNum()
{
	number = NULL;
	exp = 0;
	n_parts = 0;
	sign = 0;
}

BigNum::BigNum(const char * str)
{
	setNum(str);
}

void BigNum::setNum(const char * str)
{
	number = NULL;
	exp = 0;
	n_parts = 0;
	if(str[0]=='-') //nastav pripadne znamenko na zacatku a preskoc ho
	{
		sign = -1;
		str++;
	} 
	else 
	{
		sign = +1;
	}
	while ( str[0] == '0' ) // vymaz pocatecni nuly
	{
		str++;
	}
	int length = strlen(str);
	while ( str[ length - 1 ] == '0' ) // vymaz zaverecne nuly
	{
		exp++;
		length--;
	}
	bool dot = false;
	for( int i = 0; i < length; i++) // najdi desetinnou tecku, pokud existuje
	{
		if (str[length - i - 1]=='.') // osetri dve tecky
		{
			if (dot == true)
			{
				error();
			}
			exp = - i - exp;	
			dot = true;
		}
	}
	n_parts = length/BASE + 1;
	cout << BASE << endl;
	number = new int [n_parts];
	for ( int i = 0; i < n_parts; i++ )
	{
		number[i] = 0;
		for ( int j = 0; j < length - i * BASE && j < BASE; j++ )
		{
			if(str[length - 1 - (i * BASE) - j] == '.')
			{
				length --;
			}
			number[i] += powerOfTen(j) * ctoi(str[length - 1 - (i * BASE) - j]);
		}
	}
}

BigNum BigNum::operator+(const BigNum & b) const 
{
	BigNum result;
	const BigNum * bigger;
	if(n_parts >= b.n_parts && number[n_parts-1] >= b.number[n_parts-1])
	{
		bigger = this;
	}
	else
	{
		bigger = &b;
	}
	if(bigger->number[n_parts-1] >= BASE * powerOfTen(BASE))
	{
		result.n_parts = bigger->n_parts + 1;
	}
	else
	{
		result.n_parts = bigger->n_parts;
	}
	result.number = new int [n_parts];


	return result;
}

void BigNum::print(void)
{
	int dotpart = - exp / BASE;
	if(sign == -1)
	{
		cout << '-';
	}
	for(int i = n_parts-1; i >= 0; i--)
	{
		if(exp < 0 && dotpart == i) // vypis casti s desetinnou teckou
		{
			cout << int(number[i]/powerOfTen(-exp));
			cout << '.';
			cout << number[i] - int( number[i] / powerOfTen(-exp) ) * powerOfTen(-exp);
		}
		else 
		{
			cout << number[i];
		}
	}
	if(exp > 0)
	{
		for(int i = 0; i < exp; i++)
		{
			cout << 0;
		}
	}
	cout << endl;
}

BigNum::~BigNum()
{
	delete [] number;
}




