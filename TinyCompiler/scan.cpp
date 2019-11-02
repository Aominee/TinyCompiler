#include "pch.h"
#include "globals.h"
#include "scan.h"


char tokenString[MAXTOKENLENGTH + 1];

enum StateType
{
	START, INCOMMENT, INNUM, INID, INASSIGN, DONE
};


static std::string currLine;
static int linePos = 0;


static char GetNextChar()
{
	if (linePos >= currLine.length())
	{
		//Attempt reading next line
		if (std::getline(std::cin, currLine))
		{
			linePos = 0;
			return currLine[linePos++];
		}
		else
		{
			return EOF;
		}
	}
	else
	{
		//Return current character
		return currLine[linePos++];
	}
}
static void UndoGet()
{
	linePos--;
}

static struct TokenData
{
	std::string value;
	TokenType token;
};

TokenData reservedWords[RESERVEDNUM] = { {"if", IF}, {"then", THEN}, {"else", ELSE}, {"end", END}, {"repeat", REPEAT}, {"until", UNTIL}, {"read", READ}, {"write", WRITE} };
static TokenType reservedCheck(std::string value)
{
	for (int i = 0; i < RESERVEDNUM; i++)
	{
		if (reservedWords[i].value == value)
		{
			return reservedWords[i].token;
		}
	}
	return ID;
}

TokenType GetNextToken()
{
	TokenType currentToken;
	//Lets determine what the token is

	//Determines whether we save or not 
	bool saveToValue;
	//Determined how ahead are we in the length of the token value
	int tokenStringIndex = 0;
	//We start our diagram with Start
	StateType state = START;

	while (state != DONE)
	{
		char c = GetNextChar();
		saveToValue = true;
		switch (state)
		{
		case START:
			if (isdigit(c))
			{
				state = INNUM;
			}
			else if (isalpha(c))
			{
				state = INID;
			}
			else if (c == ':')
			{
				state = INASSIGN;
			}
			else if (c == ' ' || c == '\t' || c == '\n')
			{
				//Do not include this character c to our token value
				saveToValue = false;
			}
			else if (c == '{')
			{
				saveToValue = false;
				state = INCOMMENT;
			}
			else
			{
				state = DONE;
				//Therefore this character represents the end of our token and hence we need to check and send our token
				switch (c)
				{
				case EOF:
					//We don't want to save EOF to our value
					saveToValue = false;
					currentToken = ENDFILE;
					break;
				case '=':
					currentToken = EQUAL;
					break;
				case '<':
					currentToken = LT;
					break;
				case '+':
					currentToken = PLUS;
					break;
				case '-':
					currentToken = MINUS;
					break;
				case '*':
					currentToken = TIMES;
					break;
				case '/':
					currentToken = DIV;
					break;
				case '(':
					currentToken = LP;
					break;
				case ')':
					currentToken = RP;
					break;
				case ';':
					currentToken = SEMI;
					break;
				default:
					currentToken = ERROR;
					//We also save in case of error so we can display it 
					break;
				}
			}
			break;
		case INCOMMENT:
			//We don't care about storing for a comment, we also don't have a token for it
			saveToValue = false;
			if (c == '}')
				state = START;
			break;
		case INNUM:
			if (!isdigit(c))
			{
				//We let next start handle getting the new character
				UndoGet();
				saveToValue = false;
				state = DONE;
				currentToken = NUM;
			}
			break;
		case INID:
			if (!isalpha(c))
			{
				UndoGet();
				saveToValue = false;
				state = DONE;
				currentToken = ID;
			}
			break;
		case INASSIGN:
			//Because its only 2 characters 
			state = DONE;
			if (c == '=')
			{
				currentToken = ASSIGN;
			}
			else
			{
				UndoGet();
				saveToValue = false;
				currentToken = ERROR;
			}
			break;
		case DONE:
			break;
		default:
			std::cout << "Scanner bug: " + state << std::endl;
			state = DONE;
			currentToken = ERROR;
			break;
		}

		if (saveToValue && tokenStringIndex <= MAXTOKENLENGTH)
		{
			tokenString[tokenStringIndex++] = c;
		}

		if (state == DONE)
		{
			tokenString[tokenStringIndex] = '\0';
			if (currentToken == ID)
			{
				currentToken = reservedCheck(tokenString);
			}
		}
	}
	return currentToken;
}
