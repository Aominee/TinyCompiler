#ifndef SCAN_H
#define SCAN_H


#define MAXTOKENLENGTH 50

TokenType GetNextToken();

extern char tokenString[MAXTOKENLENGTH + 1];


#endif //SCAN_H