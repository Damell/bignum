// BigNum.cpp
#include "BigNum.h"

// testovat castecne preteceni, tzn. mene nez velikost datoveho typu ale vice nez pocet cifer ktere pouzivam

using namespace std;

inline int ctoi(char c){ return int(c) - 48;}

template <class Any>
inline Any abs(const Any & x) { return x >= 0 ? x : -x; }


int powerOfTen(int n) { // implementovat pres enum
	int x = 10;
	if(n == 0) {
		return 1;
	}
	for(int i = 1; i < n; i++) {
		x *= 10;
	}
	return x;
}


BigNum::BigNum() {
	exp = 0;
	sign = PLUS_SIGN;
}

BigNum::BigNum(const string & str) {
	setNum(str);
}

BigNum::BigNum ( const BigNum & x ) {
	exp = x.exp;
	sign = x.sign;
	number = x.number;
}

void BigNum::setNum(const string & num) {
	string str = num;
	exp = 0;
	if ( str[0]=='-' ) { //nastav pripadne znamenko na zacatku a preskoc ho
		sign = MINUS_SIGN;
		str.erase(0,1);
	} 
	else {
		if ( str[0] == '+' ) {
			str.erase(0,1);
		}
		sign = PLUS_SIGN;
	}
	unsigned int length = str.length();
	//int padding = 0;
	//				throw Exception ("Number contains two dots, please try again:");
	unsigned int dot_pos;
	int padding = 0;
	if( str.find_last_of('.') != string::npos ) {
		dot_pos = str.find_last_of('.');
		str.erase(dot_pos,1);
		length --;
		exp = -(length - dot_pos);
		padding = BASE - (-exp % BASE );
		exp -= padding;
		str.append(padding, '0');
		length += padding;
	}
	// osetrit vstupy
	for( int i = length - 1; i >= 0; i-- ) {
		if( (length - i - 1)/BASE >= number.size() ) {
			number.push_back( ctoi( str[i] ) * powerOfTen( (length - i - 1) % BASE ) );
		} else {
			number[(length - i - 1)/BASE] += ctoi( str[i] ) * powerOfTen( (length - i - 1) % BASE );
		}
	}
	Optimize();
} 

BigNum & BigNum::operator=(const BigNum & b) 
{
	exp = b.exp;
	sign = b.sign;
	number = b.number;
	return *this;
}

int BigNum::checkBoundaries(const int & i, const BigNum & a, const int & min, const int & max) const
{
	if (i > max || i < min)
	{
		return 0;
	}
	else 
	{
		return a.number[i - min];
	}
}

BigNum BigNum::operator+(const BigNum & b) const {
	BigNum result;
	// zjisteni potrebneho rozsahu pro alokaci result
	int min, max;
	if( exp/BASE <= b.exp/BASE ) {
		min = exp/BASE;
		result.exp = exp;
	} else {
		min = b.exp/BASE;
		result.exp = b.exp;
	}
	if( exp/BASE + number.size() > b.exp/BASE + b.number.size() ) {
		max = exp/BASE + number.size();
	} else {
		max = b.exp/BASE + b.number.size();
	}
	int n_parts = max - min;
	int this_min = (exp - result.exp) / BASE;
	int this_max = this_min + number.size() - 1;
	int b_min = (b.exp - result.exp) / BASE;
	int b_max = b_min + b.number.size() - 1;
	bool flag = true;
	if(sign == b.sign) { // obe cisla jsou stejneho znamenka
		result.sign = sign;
	} else { // rozdilneho znamenka -> zjistuji jake bude znamenko vysledku
		int i = n_parts - 1;
		while (flag && i >= 0) {
			int x, y;
			x = checkBoundaries(i, *this, this_min, this_max); // initialization of x and y, if i is out of boundaries, they are set to zero
			y = checkBoundaries(i, b, b_min, b_max); // initialization of x and y, if i is out of boundaries, they are set to zero
			if(abs(x) > abs(y)) {
				result.sign = sign;
				flag = false;
			}
			else if (abs(x) < abs(y)) {
				result.sign = b.sign;
				flag = false;
			}
			else {
				//	result.n_parts--;
			}
			i--;
		}	
		if (flag == true)
		{
			//	result.n_parts = 0;
			result.exp = 0;
		}
	}
	//result.number = new int [result.n_parts](); // inicializace na nulu
	int max_n = MAX + 1;
	int carry = 0;
	// pokud jsou vysledne casti odzadu nulove, je treba vysledek zmensit
	for(int i = 0; i < n_parts; i++) {
		int x, y, help;
		x = checkBoundaries(i, *this, this_min, this_max); // initialization of x and y, if i is out of boundaries, they are set to zero
		y = checkBoundaries(i, b, b_min, b_max); // initialization of x and y, if i is out of boundaries, they are set to zero
		if( this->sign == MINUS_SIGN) {
			x *= -1;
		}
		if( b.sign == MINUS_SIGN) {
			y *= -1;
		}
		// pokud jsou obe cisla kladna
		if(x >= 0 && y >= 0) {
			help = x - max_n + y + carry;
			if(help>=0) {
				result.number.push_back(help);
				carry = 1;
			} else {
				result.number.push_back( x + y + carry );
				carry = 0;
			}
			// pokud jsou obe zaporna
		} else if(x < 0 && y < 0) {
			help = x + max_n + y + carry;
			if(help<=0) {
				result.number.push_back(help);
				carry = -1;
			}
			else {
				result.number.push_back( x + y + carry );
				carry = 0;
			}
			// pokud jsou rozdilneho znamenka
		} else {
			result.number.push_back( x + y + carry );
			carry = 0;
			if (result.number[i] < 0 && result.sign > 0) {
				result.number[i] += max_n;
				carry = -1;
			} else if (result.number[i] > 0 && result.sign < 0) {
				result.number[i] -= max_n;
				carry = 1;
			}
		}
		// if the number is different sign than it should be
		if ( ( result.sign == 1 ) && ( result.number[i] < 0 ) ) {
			result.number[i] += max_n;
			carry--;
		} else if ( ( result.sign == -1 ) && ( result.number[i] > 0 ) ) {
			result.number[i] -= max_n;
			carry++;
		}
		result.number[i] = abs( result.number[i] );
	}
	if ( carry ) {
		result.number.push_back(carry);
	}
	result.Optimize();
	return result;
}

void BigNum::Optimize ( void ) { // probably obsolete
	deque <int> ::iterator it;
	if(number.size()) {
		it = number.begin();
		while( it < number.end() && *it == 0 ) {
			number.pop_front();
			exp += BASE;
			it++;
		}
		it = number.end();
		it--;
		while( it >= number.begin() && *it == 0 ) {
			number.pop_back();
			it--;
		}
	}
}

BigNum BigNum::operator-(const BigNum & b) const {
	BigNum result;
	BigNum c = b;
	if ( c.sign == 1 ) {
		c.sign = MINUS_SIGN;
		result = *this + c;
	}
	else {
		c.sign = PLUS_SIGN;
		result = *this + c;
	}
	return result;
}

BigNum BigNum::operator * ( const BigNum & b ) const {
	BigNum result;
	int carry, res;
	for ( unsigned int i = 0; i < number.size(); i++ ) {
		carry = 0;
		for ( unsigned int j = 0; j < b.number.size(); j++ ) {
			long long int x = number.at(i);
			long long int y = b.number.at(j);
			res = ((x*y) %1000000000) + carry;
			carry = (x*y)/1000000000;
			if ( ( i + j ) < result.number.size() ) {
				result.number.at( i + j ) += res;
				if ( result.number.at( i + j ) > MAX ) {
					carry++;
					result.number.at( i + j ) -= MAX +1;
				}
			} else {
				result.number.push_back(res);
			}
		}
		if ( carry ) {
			result.number.push_back( carry );
		}
	}
	result.exp = exp + b.exp;
	if( sign == b.sign ) {
		result.sign = PLUS_SIGN;
	} else {
		result.sign = MINUS_SIGN;
	}

	result.Optimize();
	return result;
}

ostream & operator << ( ostream & os, const BigNum & n ) {
	if(n.number.size() == 0) {
		os << "0";
		os << endl;
		return os;
	}
	if(n.sign == MINUS_SIGN) {
		os << '-';
	}
	int dot_part = -n.exp / BASE;
	bool dot_printed = false;
	if( n.exp < 0 && dot_part >= (signed) n.number.size() ) {
		os << "0.";
		dot_printed = true;
	}
	for(int i = 0; i < dot_part - (signed) n.number.size(); i++) {
		for(int j = 0; j < BASE; j++) {
			os << "0";
		}
	}
	os.fill('0');
	bool first = true;
	for(int i = n.number.size()-1; i >= 0; i--) {
		if(i == dot_part - 1 && !dot_printed) { // vypis casti s desetinnou teckou
			os << '.';
			dot_printed = true;
		}
		if(dot_printed && i==0) {
			int printn = n.number[i];
			int j = 0;
			while(printn % 10 == 0 && printn != 0) {
				printn = printn / 10; // nema zde byt exp ++ nebo neco takovyho?
				j++;
			}
			if(dot_printed) {
				os.width(BASE - j);
			}
			os << printn;
		} else {
			if(!first)
			{
				os.width(BASE);
			}
			os << n.number[i];
			first = false;
		}
	}
	if(n.exp > 0) {
		for(int i = 0; i < n.exp; i += BASE) {
			os.width(BASE);
			os << "0";
		}
	}
	os << endl;
	return os;
}
