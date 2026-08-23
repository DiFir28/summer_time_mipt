#include "parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "quade.h"
#include "colors.h"


#define MAX_INPUT_SIZE 100
#define MAX_INPUT_SIZE_STR "100"

static const char *signs = "+-*/^=";

bool NEWparsCoeffs(QuadraticEquation *q){
    char input[MAX_INPUT_SIZE] = {0};
    double x_coeffs[3] = {0}; //! index ~ power of x
    
    printf(GREEN "Enter your equation: " DEFAULT_COLOR);
    scanf("%" MAX_INPUT_SIZE_STR "[^\n]", input); //fgets
    
    if (trashCleaner(input)){
        printf(RED "INVALID INPUT\n" DEFAULT_COLOR);
        return true;
    }
    printf("%s\n", input);
    bool sign = true; // true - plus false - minus 
    unsigned eqals_cnt =0;
    

    double current_number = 0; 
    double prev_number = 0;
    char *current_number_end = input;
    double current_number_multiply = 1; 
    int current_x_power = 0;

    const char *sign_ptr = nearestSign(input+1); //cringenaming
    const char *prev_sign_ptr = input;

    while (prev_sign_ptr != NULL){
        
        if (*prev_sign_ptr == '='){
            eqals_cnt+=1;
        }        

        if (*(prev_sign_ptr + 1) == 'x'){
            current_x_power += 1;
        }else
        {   
            
            current_number = strtod(prev_sign_ptr + 1, &current_number_end);
            if (input == prev_sign_ptr && isdigit(*input)){
                current_number = strtod(prev_sign_ptr, &current_number_end);
            }
            if (current_number != 0){
                if (*prev_sign_ptr == '*' || *prev_sign_ptr == '+' || *prev_sign_ptr == '-' || *prev_sign_ptr == '=' || prev_sign_ptr == input){
                    current_number_multiply *= current_number;
                }else if (*prev_sign_ptr == '/'){
                    current_number_multiply /= current_number;
                }else if (*prev_sign_ptr == '^'){
                    if (*(prev_sign_ptr-1) == 'x'){
                        current_x_power += unsigned(current_number - 1);
                    }else
                    {
                        current_number_multiply*= pow(prev_number, current_number - 1);
                    }
                }
                prev_number = current_number;
                if (*current_number_end == 'x'){
                    current_x_power +=1;
                }
            } else {
                printf(RED "somthing went wrong on %c\n" DEFAULT_COLOR, *prev_sign_ptr);
                break;
            }
        }
        if (sign_ptr == NULL || *sign_ptr == '+' || *sign_ptr == '-' || *sign_ptr == '='){
            if (current_x_power > 2 || current_x_power < 0){
                printf(RED "WRONG POWER" DEFAULT_COLOR);
                break;
            }
    
            if (sign^eqals_cnt){
                x_coeffs[current_x_power] += current_number_multiply;
            } else {
                x_coeffs[current_x_power] -= current_number_multiply;
            }            
            printf(YELLOW "power %d number %lg| " DEFAULT_COLOR, current_x_power, current_number_multiply);
            if (sign_ptr == NULL)
            { 

            } else if (sign_ptr != NULL && (*sign_ptr == '+' || *sign_ptr == '=')){
                sign = true;
            } else {
                sign = false;
            }
            current_x_power = 0;
            current_number_multiply = 1;
        }

        prev_sign_ptr = sign_ptr;
        if (sign_ptr != NULL && prev_sign_ptr != NULL){
            sign_ptr = nearestSign(sign_ptr+1);        
            if (sign_ptr - prev_sign_ptr == 0){
                printf(RED "2 sign in a row" DEFAULT_COLOR);
                break;
            }
        }
    }
    printf("Result: %lg %lg %lg", x_coeffs[2], x_coeffs[1], x_coeffs[0]);
    return false;
}

bool trashCleaner(char *input){
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
            input[J-1] = '^';
            continue;
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