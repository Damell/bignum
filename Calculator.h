#ifndef CALCULATOR_H
#define CALCULATOR_H
#define QUIT 12

#include <iostream>
#include <sstream>
#include "BigNum.h"
#include "ShuntingYard.h"
using namespace std;

class Calculator : private ShuntingYard
{
	public:
		Calculator & operator << ( string & is );
		friend ostream & operator << ( ostream & os, const Calculator & res )
		{
			os << res.result;
			return os;
		}
	private:
		BigNum result;
};
#endif
