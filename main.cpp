// ARBITRARY PRECISION CALCULATOR
// author: Daniel Chabr
// main.cpp
#include <iostream>
#include "BigNum.h"


int main()
{
	using namespace std;
	BigNum a;
	a.setNum("11111101.022222222");
	//a.setNum("11111101.022222222000");
	a.print();
	BigNum b;
	b.setNum("-44444.48");
	//b.setNum("-44444.48");
	b.print();
	cout << "-------------" << endl;
	BigNum c;
	c = a + b;
	// correct 11066656.542222222
	// my      11066657.457777778
	c.print();

// 	BigNum b = cislo;  why doesnt work?

	return 0;
}
