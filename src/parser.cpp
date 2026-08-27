#include "parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "returns.h"
#include "colors.h"
#include "quade.h"

static const char *signs = "+-*/^=";

bool parsCoeffsSys(char *input, double x_coeffs[/* index ~ power of x*/], unsigned size)
{
    if (size / sizeof(double) < 3){ // constant
        return true;
    }
    if (trashCleaner(input))
        return true;
        // printf(RED "INVALID INPUT\n" DEFAULT_COLOR);
    // printf("%s\n", input);
  
    unsigned eqals_cnt =0;    
    double current_number_multiply = 1; 
    int current_x_power = 0;
    const char *sign_ptr = nearestSign(input+1);
    const char *prev_sign_ptr = input;
    bool sign = true; // true - plus false - minus ;
    if (*prev_sign_ptr == '-'){
        sign = false;
    }
    while (prev_sign_ptr != NULL){
        if (*prev_sign_ptr == '='){
            eqals_cnt+=1;
            if (eqals_cnt > 1){
                printf(YELLOW_ "WARNING: Your input more than 1 eqals sign, eqation will consist of first 2 parts only\n");
                break;
            }
        }        

        if (*(prev_sign_ptr + 1) == 'x' ){
            
            current_x_power += 1;
        }else
        {   
            if (parsNumber(input, prev_sign_ptr, &current_number_multiply, &current_x_power))
                return true;
        }

        if (parsSign(sign_ptr, eqals_cnt, &sign, x_coeffs, &current_number_multiply, &current_x_power))
            return true;

        prev_sign_ptr = sign_ptr;
        if (sign_ptr != NULL && prev_sign_ptr != NULL){
            sign_ptr = nearestSign(sign_ptr+1);        
            if (sign_ptr - prev_sign_ptr == 0){
                // printf(RED "2 sign in a row" DEFAULT_COLOR);
                return true;
            }
        }
    }
    return false;
}

bool parsNumber(char *input,  const char *prev_sign_ptr, double *current_number_multiply, int *current_x_power)
{
    static double prev_number = 0;
    char *current_number_end = input;
    double current_number = strtod(prev_sign_ptr + 1, &current_number_end);
    if (input == prev_sign_ptr){ //TODO: KOSTYL!
        if (isdigit(*input)){
        current_number = strtod(prev_sign_ptr, &current_number_end);
        }else if(*prev_sign_ptr == 'x'){
            current_number = 1;
        }
    }
    if (current_number == 0 && *(prev_sign_ptr + 1) != '0'){
        // printf(RED "somthing went wrong on %c\n" DEFAULT_COLOR, *prev_sign_ptr);
        return true;
    }
    if (*prev_sign_ptr == '*' || *prev_sign_ptr == '+' || *prev_sign_ptr == '-' || *prev_sign_ptr == '=' || prev_sign_ptr == input){
        (*current_number_multiply) *= current_number;
    }else if (*prev_sign_ptr == '/'){
        (*current_number_multiply) /= current_number;
    }else if (*prev_sign_ptr == '^'){
        if (*(prev_sign_ptr-1) == 'x'){
            
            (*current_x_power) += unsigned(current_number - 1);
        }else
        {
            
            (*current_number_multiply) *= pow(prev_number, current_number - 1);
        }
    }
    prev_number = current_number;
    if (*current_number_end == 'x' || (prev_sign_ptr == input && *prev_sign_ptr == 'x')){
        (*current_x_power) +=1;
    }
    return false;
}

bool parsSign(const char *sign_ptr, int eqals_cnt, bool *sign, double x_coeffs[], double *current_number_multiply, int *current_x_power)
{
    // static  bool sign = true; // true - plus false - minus ;
    if (sign_ptr == NULL || *sign_ptr == '+' || *sign_ptr == '-' || *sign_ptr == '='){
        if (*current_x_power > 2 || *current_x_power < 0){
            // printf(RED "WRONG POWER" DEFAULT_COLOR);
            return true;
        }

        if (*sign^(eqals_cnt)){
            x_coeffs[*current_x_power] += *current_number_multiply;
        } else {
            x_coeffs[*current_x_power] -= *current_number_multiply;
        }            
        // printf(YELLOW "power %d number %lg| " DEFAULT_COLOR, current_x_power, current_number_multiply);
        if (sign_ptr != NULL && (*sign_ptr == '+' || *sign_ptr == '=')){
            *sign = true;
        } else if (sign_ptr != NULL){
            *sign = false;
        }
        *current_x_power = 0;
        *current_number_multiply = 1;
    }
    return false;
}

bool trashCleaner(char *input)
{
    const char *validChr = "0123456789.x+-*/^=\n\0";
    unsigned J = 0;
    for(unsigned I = 0, n =  unsigned(strlen(input)); I < n; I++){
        if (input[I] == ' '){
            continue;
        }          
        if (strchr(validChr, input[I]) == NULL){
            return true;
        }
        if (input[I] == '*' && input[J-1] == '*'){
            if (input[I+1] == 'x'){
                return true;
            }
            input[J-1] = '^';
            continue;
        }
        if (input[I] == '^'){
            if (input[I+1] == 'x'){
                return true;
            }
        }
        input[J] = input[I];
        J++;
    }
    input[J] = '\0';
    return false;
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