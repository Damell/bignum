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
				cout << "Result: " << calc;
			}
			catch ( Exception e )
			{
				cout << e;
			}
		}
		return 0;
	}
	cout << "Welcome to arbitrary precision calculator" << endl;
	cout << "To end program, enter \"q\"" << endl;
	cout << "Please enter arithmetical expression consisting of '+', '-', '*', '(', ')' and arbitrarily long precision numbers:" << endl;
	cout << "New expression: ";
	while(getline( cin, str ))
	{
		if(str == "q") break;
		try
		{
			calc << str;
			cout << "Result: " << calc;
		}
		catch ( Exception e )
		{
			cout << e;
		}
		cout << "New expression: ";
	}
	return 0;
}
