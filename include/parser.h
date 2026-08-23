#ifndef __PARSER__
#define __PARSER__

#include "quade.h"

bool parsCoeffs(QuadraticEquation *q);
bool NEWparsCoeffs(QuadraticEquation *q);
bool trashCleaner(char *input);
bool signCheck(char *input);
void strnprint(const char *input, unsigned n);
const char *sumSplit(const char * const input);
const char *mulSplit(const char * const input);
bool sumParsint (const char *input, const char *endMul, double output_k[]);
int mulPars(const char *input, const char *endMul, double *output_k);


#endif