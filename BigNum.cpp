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
	int length = strlen(str);
	int dot = 0;
	for( int i = 0; i < length; i++) // najdi desetinnou tecku, pokud existuje
	{
		if (str[length - i - 1]=='.') // osetri dve tecky
		{
			if (dot)
			{
				error();
			}
			exp = - i;	
			dot = 1;
		}
	}
	while ( str[0] == '0' || str[0] == '.') // vymaz pocatecni nuly
	{
		str++;
		length--;
	}
	while ( str[ length - 1 ] == '0' ) // vymaz zaverecne nuly
	{
		exp++;
		length--;
	}
	// zjisteni vyplne nulou a upraveni exponentu, tak aby desetinna tecka vychazela na okraj casti
	int padding = exp % BASE;
	if(padding<0)
	{ 
		padding += BASE;
	}
	exp -= padding;
	// zjisteni potrebneho poctu casti
	n_parts = (length + padding - dot - 1) / BASE + 1;
	// alokace potrebneho poctu casti 
	number = new int [n_parts];
	dot = 0;
	for ( int i = 0; i < n_parts; i++ )
	{
		number[i] = 0;

		for ( int j = i * BASE; j < BASE * ( i + 1) && j < length + padding - dot; j++ )
		{
			if(j >= padding)
			{
				if(str[length - 1 - j + padding] == '.')
				{
					dot = 1;
				}
				number[i] += powerOfTen(j - i * BASE) * ctoi(str[length - 1 - j + padding - dot]);
			}
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
	if(sign == -1)
	{
		cout << '-';
	}
	int dotpart = -exp / BASE;
	bool dotprinted = false;
	cout << exp << endl << dotpart << endl;
	cout << n_parts << endl;
	for(int i = 0; i < n_parts; i++)
	{
		cout << number[i] << endl;
	}
	cout << "------" << endl;
	if(exp<0 && dotpart >= n_parts)
	{
		cout << "0.";
		dotprinted = true;
	}

	for(int i = 0; i < dotpart - n_parts; i++)
	{
		for(int j = 0; j < BASE; j++)
		{
			cout << "0";
		}
	}
	cout.fill('0');
	for(int i = n_parts-1; i >= 0; i--)
	{
		if(i == dotpart - 1) // vypis casti s desetinnou teckou
		{
			cout << '.';
			dotprinted = true;
		}
		if(dotprinted && i==0)
		{
			int printn = number[i];
			while(printn % 10 == 0)
			{
				printn = printn / 10;
			}
			cout << printn;
		}
		else
		{
			if(dotprinted)
			{
				cout.width(9);
			}
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




