#ifndef __PARSER__
#define __PARSER__

#define parsCoeffs(x, y) parsCoeffsSys(x, sizeof(x), y)

bool parsCoeffsSys(double x_coeffs[/* index ~ power of x*/], unsigned size, char *input);
bool parsNumber(char *input,  const char *prev_sign_ptr, double *current_number_multiply, int *current_x_power);
bool parsSign(const char *sign_ptr, int *current_x_power,  double x_coeffs[], double *current_number_multiply, int eqals_cnt);
bool trashCleaner(char *input);
const char *nearestSign(const char * const input);

#endif