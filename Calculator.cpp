// Calculator.cpp
#include <string>
#include "Calculator.h"
#include "ShuntingYard.h"
using namespace std;
inline void getSkipSpaces ( istringstream & is, char & c ) 
{
	do
	{
		c = is.get();
	} while ( is.good() && c == ' ' );
}

Calculator & Calculator::operator << ( string & str )
{
	ShuntingYard sh;
	istringstream is (str);
	string num;
	char c = is.peek();
	if ( c == 'q') throw QUIT;
	bool last_op = true;
	while(is.good())
	{
		getSkipSpaces( is, c );
		if( (c >= '0' && c <= '9') || (last_op && (c == '-' || c == '+')) )
		{
			num = "";
			while( is.good() && ( (c >= '0' && c <= '9') || c == '.' || (last_op && num.empty() && (c == '-' || c == '+')) ))
			{
				num += c;
				is.get(c);
			}
			sh.Add( num );
			last_op = false;
		}
		if( is.good() && ((!last_op && (c == '+' || c == '*' || c == '-' || c == ')' )) || (last_op && c == '(' )))
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
