// BigNum.h
#ifndef BIGNUM_H
#define BIGNUM_H

#include <climits>
#include "Token.h"

#if INT_MAX/1000/1000 < 999
#define BASE 4
#define MAX 9999
#elif INT_MAX/1000/1000/1000/1000/1000 < 999
#define BASE 9
#define MAX 999999999
#elif INT_MAX/1000/1000/1000/1000/1000 > 999
#define BASE 18
#define MAX 999999999999999999
#endif

class BigNum : public Token
{
	public:
		BigNum ( void );
		BigNum ( const char * str ); // inicializace retezcem
		BigNum ( const BigNum & );
		void setNum ( const char * str);
		BigNum & operator = ( const BigNum & );
		BigNum operator + ( const BigNum & ) const;
		BigNum operator - ( const BigNum & ) const;
		BigNum operator * ( const BigNum & ) const;
		void Optimize ( void );
		const bool IsOperator ( void ) const { return false; }
		void Print( void ) const;
		~BigNum();
	private:
		int * number;
		int exp;
		int n_parts; 
		int sign; // -1 for negative, +1 for positive
		void checkBoundaries(const int & i, int & x, const BigNum & a, const int & a_min, const int & a_max, int & y, const BigNum & b, const int & b_min, const int & b_max) const;
};

#endif
