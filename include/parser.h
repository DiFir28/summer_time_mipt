#ifndef __PARSER__
#define __PARSER__

#include "quade.h"

bool NEWparsCoeffs(QuadraticEquation *q);
bool trashCleaner(char *input);
bool signCheck(char *input);
const char *nearestSign(const char * const input);

#endif