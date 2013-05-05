// ShuntingYard.h
#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <stack>
#include "BigNum.h"
#include "Operator.h"
using namespace std;

class ShuntingYard
{
	public:
		ShuntingYard & Add ( char & c );
		ShuntingYard & Add ( string & str );
		ShuntingYard & End ( void );
		BigNum Result ( void );
		~ShuntingYard ();
	private:
		stack <Token *> output;
		stack <Operator *> op_stack;
		stack <Token *> h_stack;
};
#endif
