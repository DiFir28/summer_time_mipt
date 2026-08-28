#include "parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "colors.h"
#include "quade.h"

const unsigned coefficents_count = 3;
static const char *signs = "+-*/^=";
static const bool CORRECT = false;
static const bool INCORRECT = true;

bool parseCoeffsSys(char *input, double x_coeffs[/* index ~ power of x*/], unsigned size)
{
    if (size / sizeof(double) < coefficents_count){ // constant
        return INCORRECT;
    }
    if (trashCleaner(input))
        return INCORRECT;
        // printf(RED "INVALID INPUT\n" DEFAULT_COLOR);
    // printf("%s\n", input);
  
    unsigned eqals_cnt =0;    
    double current_number_multiply = 1; 
    int current_x_power = 0;
    const char *sign_ptr = nearestSign(input);
    const char *prev_sign_ptr = input;
    bool sign = INCORRECT; // true - plus false - minus ;
    while (prev_sign_ptr != NULL){
        if (sign_ptr != NULL && *prev_sign_ptr == '^' && *sign_ptr == '^'){
            return INCORRECT;
        }
        if (*prev_sign_ptr == '='){
            eqals_cnt+=1;
            if (eqals_cnt > 1){
                printf(YELLOW_ "WARNING: Your input more than 1 eqals sign, eqation will consist of first 2 parts only\n");
                break;
            }
        }       
        if (sign_ptr != NULL && sign_ptr <= prev_sign_ptr + 1){
            if (*prev_sign_ptr == '*' || *prev_sign_ptr == '/' || *prev_sign_ptr == '^' )
            {
                return INCORRECT;
            }
            if (*sign_ptr == '-')
            {
                sign = false;
            }
            else{
                sign = true;  
            }
            prev_sign_ptr = sign_ptr;
            sign_ptr = nearestSign(sign_ptr+1);
            continue;
        }

        if (*(prev_sign_ptr + 1) == 'x' )
        {            
            current_x_power += 1;
        }
        else{   
            if (parseNumber(prev_sign_ptr, &current_number_multiply, &current_x_power))
                return INCORRECT;
        }
        if (parseSign(sign_ptr, eqals_cnt, &sign, x_coeffs, &current_number_multiply, &current_x_power))
            return INCORRECT;

        prev_sign_ptr = sign_ptr;
        if (sign_ptr != NULL && prev_sign_ptr != NULL)
        {
            sign_ptr = nearestSign(sign_ptr+1);        
            if (sign_ptr - prev_sign_ptr == 0)
            {
                // printf(RED "2 sign in a row" DEFAULT_COLOR);
                return INCORRECT;
            }
        }
    }
    return CORRECT;
}

bool parseNumber(const char *prev_sign_ptr, double *current_number_multiply, int *current_x_power)
{
    static double prev_number = 0;
    char *current_number_end = NULL;
    double current_number = strtod(prev_sign_ptr + 1, &current_number_end);
    if (current_number == 0 && *(prev_sign_ptr + 1) != '0'){
        // printf(RED "somthing went wrong on %c\n" DEFAULT_COLOR, *prev_sign_ptr);
        return INCORRECT;
    }
    if (*prev_sign_ptr == '*' || *prev_sign_ptr == '+' || *prev_sign_ptr == '-' || *prev_sign_ptr == '='){
        (*current_number_multiply) *= current_number;
    }
    else if (*prev_sign_ptr == '/'){
        (*current_number_multiply) /= current_number;
    }
    else if (*prev_sign_ptr == '^'){
        if (*(prev_sign_ptr-1) == 'x'){            
            (*current_x_power) += unsigned(current_number - 1);
        }
        else{            
            (*current_number_multiply) *= pow(prev_number, current_number - 1);

        }
    }
    prev_number = current_number;
    if (*current_number_end == 'x'){
        (*current_x_power) +=1;
    }
    return CORRECT;
}

bool parseSign(const char *sign_ptr, int eqals_cnt, bool *sign, double x_coeffs[], double *current_number_multiply, int *current_x_power)
{
    // static  bool sign = true; // true - plus false - minus ;
    if (sign_ptr == NULL || *sign_ptr == '+' || *sign_ptr == '-' || *sign_ptr == '=')
    {
        if (*current_x_power > 2 || *current_x_power < 0){
            // printf(RED "WRONG POWER" DEFAULT_COLOR);
            return INCORRECT;
        }

        if (*sign^(eqals_cnt)){
            x_coeffs[*current_x_power] += *current_number_multiply;
        }
        else {
            x_coeffs[*current_x_power] -= *current_number_multiply;
        }            
        // printf(YELLOW "power %d number %lg| " DEFAULT_COLOR, current_x_power, current_number_multiply);
        if (sign_ptr != NULL && (*sign_ptr == '+' || *sign_ptr == '='))
        {
            *sign = true;
        }
        else if (sign_ptr != NULL)
        {
            *sign = false;
        }
        *current_x_power = 0;
        *current_number_multiply = 1;
    }
    return CORRECT;
}

bool trashCleaner(char *input)
{
    const char *validChr = "0123456789.x+-*/^=\n\0";
    unsigned J = 0;
    for(unsigned I = 0, n =  unsigned(strlen(input)); I < n; I++){
        if (input[I] == ' ' || input[I] == '\t'){
            continue;
        }          
        if (strchr(validChr, input[I]) == NULL){
            return INCORRECT;
        }
        input[J] = input[I];
        J++;
    }
    J = 0;
    for(unsigned I = 0, n =  unsigned(strlen(input)); I < n; I++){
        if (input[I] == '*' && input[J-1] == '*'){
            if (input[I+1] == 'x'){
                return INCORRECT;
            }
            input[J-1] = '^';
            continue;
        }
        if (input[I] == '^' || input[I] == '/' || input[I] == 'x'){
            if (input[I+1] == 'x'){
                return INCORRECT;
            }
        }
        if (input[I] == 'x' && isdigit(input[I+1])){
                return INCORRECT;
        }
        input[J] = input[I];
        J++;
    }
    input[J] = '\0';
    return CORRECT;
}

const char *nearestSign(const char *input){
    unsigned i = 0;
    while (input[i] != '\0'){
        if (strchr(signs, input[i]) != NULL){
            return input+i;
        }
        i++;
    }
    return NULL;
}