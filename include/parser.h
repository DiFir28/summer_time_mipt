#ifndef __PARSER__
#define __PARSER__

#include "quade.h"

bool parsCoeffs(QuadraticEquation *q);
bool NEWparsCoeffs(QuadraticEquation *q);
bool trashCleaner(char *input);
bool signCheck(char *input);
void strnprint(const char *input, unsigned n);
char *sumSplit(char * const input);
char *mulSplit(char * const input);


#endif