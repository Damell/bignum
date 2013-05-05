// Operator.h
#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include "Token.h"

enum {
	L_PAR,
	R_PAR,
	TIMES,
	PLUS,
	MINUS
};

class Operator : public Token
{
	public:
		Operator ( char & c )
		{
			switch ( c )
			{
				case '(':
					op = L_PAR;
					priority = 3;
					break;
				case ')':
					op = R_PAR;
					priority = 3;
					break;
				case '*':
					op = TIMES;
					priority = 1;
					break;
				case '+':
					op = PLUS;
					priority = 2;
					break;
				case '-':
					op = MINUS;
					priority = 2;
					break;
				default:
					op = -1;
					priority = -1;
			}
		}
		const short int & Show ( void ) const { return op; }
		const short int & ShowPriority ( void ) const { return priority; }
		const bool IsOperator ( void ) const { return true; }
	private:
		short int op;
		short int priority;
};

#endif
