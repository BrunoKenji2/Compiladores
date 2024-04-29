#ifndef _SCAN_H_
#define _SCAN_H_

#define alfabeto 26
#define MAXTOKENLEN 40
#define MAXRESERVED 6

extern char tokenString[MAXTOKENLEN + 1];
TokenType getToken(void);

#endif // SCAN_H