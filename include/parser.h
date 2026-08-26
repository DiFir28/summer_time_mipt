#ifndef __PARSER__
#define __PARSER__

/**
 * @file parser.h
 * @brief function for extract coefficents fron standert writed eqation, support signs: +, -, *, /, ^
 */

/**
 * @brief macros add size of input arr
 * @param str  string for parse
 * @param arr  output array for 3 coefficents
 */
#define parsCoeffs(str, arr) parsCoeffsSys(str, arr, sizeof(arr))

/**
 * @brief main parse function //! Needs to fix
 * @param[in] input     string for parse
 * @param[out] x_coeffs output array for 3 coefficents
 * @return completed flag
 * @retval true         error: incorrect input eqation
 * @retval false        no error
 */
bool parsCoeffsSys(char *input, double x_coeffs[/* index ~ power of x*/], unsigned size);

/**
 * @brief function parse number in multiply
 * @param[in] input                         string for parse
 * @param[in] prev_sign_ptr                 pointer to previous sign
 * @param[in, out] current_number_multiply  value of current multiply
 * @param[in, out] current_x_power          power of X in current multiply
 * @return completed flag
 * @retval true         error: incorrect input eqation
 * @retval false        no error
 */
bool parsNumber(char *input,  const char *prev_sign_ptr, double *current_number_multiply, int *current_x_power);

/**
 * @brief function parse signs at the end of summand
 * @param[in] sign_ptr                      pointer to last sign of summand
 * @param[in] eqals_cnt                     count of equals signs for control sign(+ or -) in coefficents
 * @param[in, out] x_coeffs                 array for 3 coefficents (coeffs changed affter end of summand)
 * @param[in, out] current_number_multiply  value of current multiply (equals zero after end of summand)
 * @param[in, out] current_x_power          power of X in current summand (equals zero after end of summand)
 * @return completed flag
 * @retval true         error: incorrect input eqation
 * @retval false        no error
 */
bool parsSign(const char *sign_ptr, int eqals_cnt, double x_coeffs[], double *current_number_multiply, int *current_x_power);

/**
 * @brief clear from useless space and precheck of correct chars in input
 * @param[in, out] input string for cleaning
 * @return completed flag
 * @retval true         error: incorrect input eqation
 * @retval false        no error
 */
bool trashCleaner(char *input);

/**
 * @brief return pointer to nearest sign (only forward direction)
 * @param[in] input string for search nearest sign
 * @return sign_ptr pointer on sign
 */
const char *nearestSign(const char * const input);

#endif