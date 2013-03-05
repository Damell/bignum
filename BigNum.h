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
		void checkBoundaries(const int & i, int & x, const BigNum & a, const int & a_min, const int & a_max, int & y, const BigNum & b, const int & b_min, const int & b_max) const;
	public:
		BigNum();
		BigNum(const char * str); // inicializace retezcem
		void setNum(const char * str);
		BigNum & operator=(const BigNum &);
		BigNum operator+(const BigNum &) const;

		void print(void);
		//BigNum(const BigNum &);
		//BigNum & operator-(const BigNum &, const BigNum &) const;
		//BigNum & operator*(const BigNum &, const BigNum &) const;
		~BigNum();
};

#endif
