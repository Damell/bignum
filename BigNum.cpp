// BigNum.cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <climits>
#include "BigNum.h"

// testovat castecne preteceni, tzn. mene nez velikost datoveho typu ale vice nez pocet cifer ktere pouzivam

using namespace std;

inline int ctoi(char c){ return int(c) - 48;}

template <class Any>
inline Any & compare(const Any & x, const Any & y) { return x > y ? x : y; }

template <class Any>
inline Any abs(const Any & x) { return x >= 0 ? x : -x; }

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
	sign = 1;
}

BigNum::BigNum(const char * str)
{
	setNum(str);
}

BigNum::BigNum ( const BigNum & x )
{
	this->n_parts = x.n_parts;
	this->exp = x.exp;
	this->sign = x.sign;
	this->number = new int [n_parts];
	for(int i = 0; i < n_parts; i++)
	{
		this->number[i] = x.number[i];
	}
}

void BigNum::setNum(const char * str)
{
	number = NULL;
	exp = 0;
	n_parts = 0;
	if ( str[0]=='-' ) //nastav pripadne znamenko na zacatku a preskoc ho
	{
		sign = -1;
		str++;
	} 
	else
	{
		if ( str[0] == '+' )
			str++;
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

BigNum & BigNum::operator=(const BigNum & b) 
{
	if( number != NULL )
	{
		delete [] number;
	}
	this->n_parts = b.n_parts;
	this->exp = b.exp;
	this->sign = b.sign;
	this->number = new int [n_parts];
	for(int i = 0; i < n_parts; i++)
	{
		this->number[i] = b.number[i];
	}
	return *this;
}

void BigNum::checkBoundaries(const int & i, int & x, const BigNum & a, const int & a_min, const int & a_max, int & y, const BigNum & b, const int & b_min, const int & b_max) const
{
	if (i > a_max || i < a_min)
	{
		x = 0;
	}
	else 
	{
		x = number[i - a_min];
	}
	if (i > b_max || i < b_min)
	{
		y = 0;
	}
	else 
	{
		y = b.number[i - b_min];
	}
}

BigNum BigNum::operator+(const BigNum & b) const 
{
	BigNum result;
	// zjisteni potrebneho rozsahu pro alokaci result
	int min, max;
	if( exp/BASE <= b.exp/BASE )
	{
		min = exp/BASE;
		result.exp = exp;
	}
	else
	{
		min = b.exp/BASE;
		result.exp = b.exp;
	}
	if( exp/BASE + n_parts > b.exp/BASE + b.n_parts )
	{
		max = exp/BASE + n_parts;
	}
	else
	{
		max = b.exp/BASE + b.n_parts;
	}
	result.n_parts = max - min;
	int this_min = (exp - result.exp) / BASE;
	int this_max = this_min + n_parts - 1;
	int b_min = (b.exp - result.exp) / BASE;
	int b_max = b_min + b.n_parts - 1;
	bool flag = true;
	if(sign == b.sign) // obe cisla jsou stejneho znamenka
	{
		result.sign = sign;
	}
	else // rozdilneho znamenka -> zjistuji jake bude znamenko vysledku
	{
		int i = result.n_parts - 1;
		while (flag && i >= 0)
		{
			int x, y;
			checkBoundaries(i, x, *this, this_min, this_max, y, b, b_min, b_max); // initialization of x and y, if i is out of boundaries, they are set to zero
			if (i > this_max || i < this_min)
			{
				x = 0;
			}
			else 
			{
				x = number[i - this_min];
			}
			if (i > b_max || i < b_min)
			{
				y = 0;
			}
			else 
			{
				y = b.number[i - b_min];
			}
			if(abs(x) > abs(y))
			{
				result.sign = sign;
				flag = false;
			}
			else if (abs(x) < abs(y))
			{
				result.sign = b.sign;
				flag = false;
			}
			else
			{
				result.n_parts--;
			}
			i--;
		}	
		if (flag == true)
		{
			result.n_parts = 0;
		}
	}
	result.number = new int [result.n_parts](); // inicializace na nulu
	int max_n = MAX + 1;
	int remember = 0;
	for(int i = 0; i < result.n_parts; i++)
	{
		int x, y, help;
		checkBoundaries(i, x, *this, this_min, this_max, y, b, b_min, b_max);
		x *= sign;
		y *= b.sign;
		// pokud jsou obe cisla kladna
		if(x >= 0 && y >= 0)
		{
			help = x - max_n + y + remember;
			if(help>=0)
			{
				result.number[i] = help;
				remember = 1;
			}
			else
			{
				result.number[i] = x + y + remember;
				remember = 0;
			}
		}	
		// pokud jsou obe zaporna
		else if(x < 0 && y < 0)
		{
			help = x + max_n + y + remember;
			if(help<=0)
			{
				result.number[i] = help;
				remember = -1;
			}
			else
			{
				result.number[i] = x + y + remember;
				remember = 0;
			}
		}
		// pokud jsou rozdilneho znamenka
		else 
		{
			result.number[i] = x + y + remember;
			remember = 0;
			if (result.number[i] < 0 && result.sign > 0)
			{
				result.number[i] += max_n;
				remember = -1;
			}
			else if (result.number[i] > 0 && result.sign < 0)
			{
				result.number[i] -= max_n;
				remember = 1;
			}
		}
		if ( ( result.sign == 1 ) && ( result.number[i] < 0 ) )
		{
			result.number[i] += max_n;
			remember--;
		}
		else if ( ( result.sign == -1 ) && ( result.number[i] > 0 ) )
		{
			result.number[i] -= max_n;
			remember++;
		}
		if (result.number[i] < 0)
		{
			result.number[i] *= -1;
		}
	}
	if ( remember )
	{
		int * bigger = new int [ ++result.n_parts ];
		bigger[ result.n_parts - 1 ] = 1;
		for ( int i = 0; i < result.n_parts - 1; i++ )
		{
			bigger[ i ] = result.number[ i ];
		}
		delete [] result.number;
		result.number = bigger;
	}
	//result.Optimize();
	return result;
}
void BigNum::Optimize ( void )
{
	BigNum opt;
	opt.n_parts = n_parts;
	opt.exp = exp;
	opt.sign = sign;
	int i = 0;
	while ( number[i] == 0 )
	{
		opt.n_parts --;
		opt.exp -= BASE;
		i++;
	}
	int j = n_parts - 1;
	while ( number[j] == 0 )
	{
		opt.n_parts --;
		opt.exp -= BASE;
		j--;
	}
	if ( opt.n_parts )
	{
		opt.number = new int [ opt.n_parts ];
		for ( int k = i; k <= j; k++ )
		{
			opt.number[ k - i ] = number[ k ];
		}
	}
	*this = opt;
}
BigNum BigNum::operator-(const BigNum & b) const 
{
	BigNum result;
	BigNum c = b;
	if ( c.sign == 1 )
	{
		c.sign = -1;
		result = *this + c;
	}
	else 
	{
		c.sign = 1;
		result = *this + c;
	}
	return result;
}

BigNum BigNum::operator * ( const BigNum & b ) const
{
	BigNum result;
	vector <int> vec;
	int carry, /*a0, a1, b0, b1, zx, zy,*/ res;
	for ( int i = 0; i < n_parts; i++ )
	{
		carry = 0;
		for ( int j = 0; j < b.n_parts; j++ )
		{
			long long int x = number[i];
			long long int y = b.number[j];
			/*os << endl << x*y << endl;
			a0 = number[i] & 0x0000ffff;
			a1 = number[i] >> 16;  // change to macros
			b0 = b.number[i] & 0x0000ffff;
			b1 = b.number[j] >> 16;
			zx = ( a1 * b0 );
			zy = ( a0 * b1 );
			res = ( a0 * b0 ) + ( zx << 16 ) + ( zy << 16 ) + carry;
			carry = ( zx >> 16 ) + ( zy >> 16 ) + ( a1 * b1 );
			os << endl << carry << endl;
			int carry10 = 0;
			for ( int k = 0; k < 32; k++ )
			{
				carry = carry << 1;
				carry10 = carry10 << 1;
				if ( carry < 0 )
				{
					carry10 ++;
					carry /= 10;
				}
			}
			os << endl << carry << endl;
			res += carry % 1000000000;
			carry10 += carry / 1000000000;
			carry = carry10;
			*/
			res = ((x*y) %1000000000) + carry;
			carry = (x*y)/1000000000;
			if ( ( i + j ) < (signed int) vec.size() )
			{
				vec.at( i + j ) += res;
				/*if ( vec.at( i + j ) < 0 )
				{
					carry++;
					vec.at( i + j ) -= max_n;
				}*/
				if ( vec.at( i + j ) > MAX )
				{
					carry++;
					vec.at( i + j ) -= MAX +1;
				}
			}
			else
			{
				vec.push_back(res);
			}
		}
		if ( carry )
		{
			vec.push_back( carry );
		}
	}

	result.exp = exp + b.exp;
	result.n_parts = vec.size();
	result.sign = sign * b.sign;
	bool resize = false;
	if ( result.n_parts > 1 && vec.at(0) == 0 )
	{
		result.n_parts --;
		resize = true;
		result.exp += BASE;
	}
	result.number = new int [result.n_parts];
	vector <int> ::iterator it;
	int i = 0;
	for ( it = vec.begin(); it != vec.end(); it++ )
	{
		if(resize)
		{
			it++;
			resize = false;
		}
		result.number[i] = *it;
		i++;
	}

	return result;
}

ostream & operator << ( ostream & os, const BigNum & n )
{
	if(n.n_parts == 0)
	{
		os << "0";
	}
	if(n.sign == -1)
	{
		os << '-';
	}
	int dotpart = -n.exp / BASE;
	bool dotprinted = false;
	if(n.exp<0 && dotpart >= n.n_parts)
	{
		os << "0.";
		dotprinted = true;
	}
	for(int i = 0; i < dotpart - n.n_parts; i++)
	{
		for(int j = 0; j < BASE; j++)
		{
			os << "0";
		}
	}
	os.fill('0');
	bool first = true;
	for(int i = n.n_parts-1; i >= 0; i--)
	{
		if(i == dotpart - 1 && !dotprinted) // vypis casti s desetinnou teckou
		{
			os << '.';
			dotprinted = true;
		}
		if(dotprinted && i==0)
		{
			int printn = n.number[i];
			int j = 0;
			while(printn % 10 == 0 && printn != 0)
			{
				printn = printn / 10; // nema zde byt exp ++ nebo neco takovyho?
				j++;
			}
			if(dotprinted)
			{
				os.width(BASE - j);
			}
			os << printn;
		}
		else
		{
			if(!first)
			{
				os.width(BASE);
			}
			os << n.number[i];
			first = false;
			//dotprinted = true;
		}
	}
	if(n.exp > 0)
	{
		for(int i = 0; i < n.exp; i += BASE)
		{
			os.width(BASE);
			os << "0";
		}
	}
	os << endl;
	return os;
}

BigNum::~BigNum()
{
	if ( number != NULL )
	{
		delete [] number;
	}
}

