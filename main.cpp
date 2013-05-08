// ARBITRARY PRECISION CALCULATOR
// author: Daniel Chabr
// main.cpp
#include <iostream>
#include "Calculator.h"
using namespace std;


int main()
{
	Calculator calc;
	cout << "Welcome to arbitrary precision calculator" << endl;
	cout << "To end program, enter \"q\"" << endl;
	cout << "Please enter arithmetical expression consisting of +, -, * and arbitrarily long precision numbers:" << endl;
	string str;
	cout << "New expression: ";
	while(getline( cin, str ))
	{
		if(str == "q") break;
		try
		{
		calc << str; // 20
		}
		catch ( int x )
		{
			if ( x == 11 )
			{
				cout << "You entered false expression, please try again." << endl;
				cout << "New expression: ";
				continue;
			}
		}
		cout << calc;
		cout << "New expression: ";
	}
	/*BigNum a;
	a.setNum("121510000.00052222222000000003");
	a.print();
	BigNum b;
	b.setNum("-22244.5548");
	b.print();
	cout << "-------------" << endl;
	BigNum c;
	c = a + b;
	c.print();
*/
// 	BigNum b = cislo;  why doesnt work?

	return 0;
}
