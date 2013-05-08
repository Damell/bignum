// ARBITRARY PRECISION CALCULATOR
// author: Daniel Chabr
// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Calculator.h"
using namespace std;


int main( int argc, char * argv [] )
{
	Calculator calc;
	string str;
	if ( argc > 1 )
	{
		fstream fs;
		fs.open( argv[1], fstream::in );
		if ( getline( fs, str ) )
		{
			try
			{
				calc << str;
			}
			catch ( int x )
			{
				cout << "The expression in the entered file is false." << endl;
				return 0;
			}
			cout << "Result: " << calc;
		}
		return 0;
	}
	cout << "Welcome to arbitrary precision calculator" << endl;
	cout << "To end program, enter \"q\"" << endl;
	cout << "Please enter arithmetical expression consisting of +, -, * and arbitrarily long precision numbers:" << endl;
	cout << "New expression: ";
	while(getline( cin, str ))
	{
		if(str == "q") break;
		try
		{
			calc << str;
		}
		catch ( int x )
		{
			if ( x == FALSE_EXPR )
			{
				cout << "You entered false expression, please try again." << endl;
				cout << "New expression: ";
				continue;
			}
		}
		cout << "Result: " << calc;
		cout << "New expression: ";
	}
	return 0;
}
