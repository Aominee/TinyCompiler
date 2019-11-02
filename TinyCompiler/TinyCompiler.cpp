#include "pch.h"
#include "globals.h"
#include "scan.h"
int main()
{
	while (true)
	{
		TokenType token =  GetNextToken();
		if (token == ENDFILE)
			break;
		//If we didn't break
		std::string tokenType;
		switch (token)
		{
		case IF:
			tokenType = "reserved";
			break;
		case THEN:
			tokenType = "reserved";
			break;
		case ELSE:
			tokenType = "reserved";
			break;
		case END:
			tokenType = "reserved";
			break;
		case REPEAT:
			tokenType = "reserved";
			break;
		case UNTIL:
			tokenType = "reserved";
			break;
		case READ:
			tokenType = "reserved";
			break;
		case WRITE:
			tokenType = "reserved";
			break;
		case PLUS:
			tokenType = "symbol";
			break;
		case MINUS:
			tokenType = "symbol";
			break;
		case TIMES:
			tokenType = "symbol";
			break;
		case DIV:
			tokenType = "symbol";
			break;
		case EQUAL:
			tokenType = "symbol";
			break;
		case LT:
			break;
			tokenType = "symbol";
		case LP:
			break;
			tokenType = "symbol";
		case RP:
			break;
			tokenType = "symbol";
		case SEMI:
			tokenType = "symbol";
			break;
		case ASSIGN:
			tokenType = "symbol";
			break;
		case NUM:
			tokenType = "number";
			break;
		case ID:
			tokenType = "identifier";
			break;
		case ERROR:
			tokenType = "error";
			break;
		default:
			break;
		}
		std::cout << tokenString << ", " << tokenType << std::endl;
	}
}
