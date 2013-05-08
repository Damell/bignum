// ShuntingYard.cpp
#include <iostream>
#include "ShuntingYard.h"
#include "BigNum.h"
using namespace std;

ShuntingYard & ShuntingYard::Add ( char & c )
{
	Operator * op = new Operator ( c );
	switch ( op->Show() )
	{
		case L_PAR:
			op_stack.push( op );
			break;
		case R_PAR:
			/*while( !op_stack.empty() )
			{
				cout << op_stack.top()->Show() << endl;
				op_stack.pop();
			}
			cout << "<<<<<<<<<<<<<<<" << endl;
			*/
			while( !op_stack.empty() && ( op_stack.top()->Show() != L_PAR ) )
			{
				output.push( op_stack.top() );
				op_stack.pop();
			}
			if( !op_stack.empty() )
			{
				op_stack.pop();
			}
			delete op;
			break;
		case TIMES:
		case PLUS:
		case MINUS:
			while( !op_stack.empty() &&  op_stack.top()->ShowPriority() <= op->ShowPriority() )
			{
				output.push( op_stack.top() );
				op_stack.pop();
			}
			op_stack.push( op );
	}
	return *this;
}
ShuntingYard & ShuntingYard::Add ( string & str )
{
	BigNum * num = new BigNum( str.data() );
	output.push( num );
	return *this;
}
ShuntingYard & ShuntingYard::End ( void )
{
	while( !op_stack.empty() )
	{
		output.push( op_stack.top() );
		op_stack.pop();
	}
	return *this;
}
BigNum ShuntingYard::Result ( void )
{
	BigNum res;
	BigNum * a = NULL, * b = NULL;
	Operator * op = NULL;
	bool error = false;;
	/*while( !output.empty() )
	{
		if(!output.top()->IsOperator())
		(static_cast<BigNum*>(output.top()))->Print();
		if(output.top()->IsOperator())
		cout << "Operator: " << (static_cast<Operator*>(output.top()))->Show() << endl;
		output.pop();
	}
	cout << "--------------" << endl;
	*/
	while( output.size() != 1 || !h_stack.empty() )
	{
		while( !output.empty() )
		{
			if( !output.top()->IsOperator() && !h_stack.empty() && !h_stack.top()->IsOperator() )
				break;
			h_stack.push( output.top() );
			output.pop();
		}
		if( !output.empty() )
		{
			a = static_cast<BigNum *>( output.top() );
			//a->Print();
			output.pop();
		}
		else
			error = true;
		if( !h_stack.empty() )
		{
			b = static_cast<BigNum *>( h_stack.top() );
			//b->Print();
			h_stack.pop();
		}
		else
			error = true;
		if( !h_stack.empty() )
		{
			op = static_cast<Operator *>( h_stack.top() );
			//cout << "Operator: " << op->Show() << endl;
			h_stack.pop();
		}
		else
			error = true;
		if ( !error )
		{
			switch ( op->Show() )
			{
				case TIMES:
					output.push( new BigNum( *a * *b ) );
					break;
				case PLUS:
					output.push( new BigNum( *a + *b ) );
					break;
				case MINUS:
					output.push( new BigNum( *a - *b ) );
					break;
			}
		}
		if ( a != NULL )
		{
			delete a;
			a = NULL;
		}
		if ( b != NULL )
		{
			delete b;
			b = NULL;
		}
		if ( op != NULL )
		{
			delete op;
			op = NULL;
		}
		if ( error )
		{
			throw 11;
			return res; // throw exception
		}
	}
	res = *(static_cast<BigNum *>(output.top()));

	return res;
}
ShuntingYard::~ShuntingYard ( void )
{
	while ( !output.empty() )
	{
		delete output.top();
		output.pop();
	}
	while ( !op_stack.empty() )
	{
		delete op_stack.top();
		op_stack.pop();
	}
}
