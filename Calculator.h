#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include "BigNum.h"
#include "ShuntingYard.h"

class Calculator : private ShuntingYard
{
	public:
		Calculator & operator << ( const string & str );
		friend ostream & operator << ( ostream & os, const Calculator & res )
		{
			cout << " = ";
			res.result.Print();
			return os;
		}
	private:
		BigNum result;
};
#endif
