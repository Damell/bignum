// Token.h
#ifndef TOKEN_H
#define TOKEN_H
class Token
{
	public:
		virtual const bool IsOperator( void ) const =0;
		virtual ~Token(){};
};
#endif
