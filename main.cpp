// ARBITRARY PRECISION CALCULATOR
// author: Daniel Chabr
// main.cpp
#include <iostream>
#include "BigNum.h"


int main()
{
	using namespace std;
	BigNum cislo;
	cislo.setNum("12345678.9123");
	cislo.print();
	/*
	   int x = 2147483647, y = 100;
	   int a = (x+y)/10;
	   cout << INT_MAX << endl;
	   cout << 2147483647 << endl;
	   cout << x+y << endl;
	   cout << a << endl;
	 */
	return 0;
}
