// ARBITRARY PRECISION CALCULATOR
// author: Daniel Chabr
// main.cpp
#include <iostream>
#include "Calculator.h"
using namespace std;


int main()
{
	Calculator calc;
	string str;
	getline( cin, str );
	calc << str; // 20
	cout << calc;
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
