// BigNum.h
#ifndef BIGNUM_H
#define BIGNUM_H

#include <climits>

#if INT_MAX/1000/1000 < 999
#define BASE 4
#elif INT_MAX/1000/1000/1000/1000/1000 < 999
#define BASE 9
#elif INT_MAX/1000/1000/1000/1000/1000 > 999
#define BASE 18
#endif



class BigNum 
{
	private:
		int * number;
		int exp;
		int n_parts; 
		int sign; // -1 for negative, +1 for positive
	public:
		BigNum();
		BigNum(const char * str); // inicializace retezcem
		void setNum(const char * str);
		void print(void);
		//BigNum(const BigNum &);
		BigNum operator+(const BigNum &) const;
		//BigNum & operator-(const BigNum &, const BigNum &) const;
		//BigNum & operator*(const BigNum &, const BigNum &) const;
		~BigNum();
};

#endif
