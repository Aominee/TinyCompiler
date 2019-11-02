#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <iostream>

#define RESERVEDNUM 8

enum  TokenType
{
	IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
	PLUS, MINUS, TIMES, DIV, EQUAL, LT, LP, RP, SEMI, ASSIGN,
	NUM, ID,
	ERROR, ENDFILE
};


#endif //GLOBALS_H