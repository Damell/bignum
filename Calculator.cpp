// Calculator.cpp
#include <string>
#include "Calculator.h"
#include "ShuntingYard.h"
using namespace std;
inline bool getSkipSpaces ( istringstream & is, char & c ) 
{
	char x;
	c = ' ';
	while ( is.good() && c == ' ' )
	{
		x = is.get();
		if( is.good() )
		{
			if( ((x < '0' || x > '9') && x != '(' && x != ')' && x != '+' && x != '-' && x != '*') || ( x == '.' && c == '.' ))
			{
				throw Exception ("Input expression is false, please try again:");
			}
		}
		c = x;
	}
	return is.good();
}

Calculator & Calculator::operator << ( string & str )
{
	ShuntingYard sh;
	istringstream is (str);
	string num;
	char c, x;
	bool last_op = true; // tests for two consecutive numbers without operand between them
	while(getSkipSpaces( is, c ))
	{
		if( (c >= '0' && c <= '9') || (last_op && (c == '-' || c == '+')) )
		{
			num = "";
			num += c;
			x = is.peek();
			while( is.good() && ( (x >= '0' && x <= '9') || x == '.' || (last_op && num.empty() && (x == '-' || x == '+')) ))
			{
				is.get(c);
				num += c;
				x = is.peek();
			}
			sh.Add( num );
			last_op = false;
		}
		else if( is.good() && ((!last_op && (c == '+' || c == '*' || c == '-' || c == ')' )) || (last_op && c == '(' )))
		{
			sh.Add( c );
			if ( c == ')' )
			{
				last_op = false;
			}
			else
			{
				last_op = true;
			}
		}
	}
	sh.End();
	result = sh.Result();
	return *this;
}
