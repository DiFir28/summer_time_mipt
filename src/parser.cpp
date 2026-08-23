#include "parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quade.h"
#include "colors.h"

#define MAX_INPUT_SIZE 100


bool NEWparsCoeffs(QuadraticEquation *q){
    checkLink(q);
    // bool completed_flag = false;    
    char input[100] = {0};
    // double x_coeffs[3] = {0}; //! index ~ power of x
    // unsigned last_offset = 0;

    printf(GREEN "Enter your equation in format ax^2+bx+c: " DEFAULT_COLOR);
    scanf("%100[^\n]", input);

    if (trashCleaner(input)){
        printf(RED "INVALID INPUT" DEFAULT_COLOR);
        return true;
    }
    char *prev = input;
    char *ptr = sumSplit(input);
    while (*ptr != '\0'){
        strnprint(prev,ptr-prev);
        printf("\t");
        char *mprev = prev;
        char *mptr = mulSplit(prev);
        while (mptr != NULL && (mptr < ptr)){
            strnprint(mprev,mptr-mprev);
            printf(" ");
            mprev = mptr;
            mptr = mulSplit(mptr+1);
        }
        strnprint(mprev,mptr-mprev);
        printf("\n");
        prev = ptr;
        ptr = sumSplit(ptr+1);
    }
    strnprint(prev,ptr-prev);
    return false;
   

}

void strnprint(const char *input, unsigned n){
    for(unsigned i = 0; i < n; i++){
        printf("%c", *(input+i));
    }
}

char *sumSplit(char * const input){
    char *minus = strchr(input, '-');
    char *plus = strchr(input, '+');
    char *end = strchr(input, '\0');
    if (minus == NULL){
        if (plus == NULL){
            return end;
        }
        return plus;
    }
    if (plus == NULL){
        return minus;
    }
    if (minus < plus){
        return minus;
    }
    return plus;
}

char *mulSplit(char * const input){
    char *mul =strchr(input, '*');
    if (mul == NULL){
        return sumSplit(input);
    }
    return mul;
}


bool parsCoeffs(QuadraticEquation *q){
    checkLink(q);
    bool completed_flag = false;    
    char input[100] = {0};
    double x_coeffs[3] = {0}; //! index ~ power of x
    unsigned last_offset = 0;

    printf(GREEN "Enter your equation in format ax^2+bx+c: " DEFAULT_COLOR);
    scanf("%100[^\n]", input);

    if(trashCleaner(input) || signCheck(input)){
        printf(RED "INVALID INPUT" DEFAULT_COLOR);
        return true;
    }
    

    bool free_part_flag = false;
    bool start_flag = true;


    for(unsigned I = 0, n = unsigned(strlen(input)); I <= n; I++){
        if (input[I] != '+' && input[I] != '-' && input[I] != '\0'){
            continue;
        }       

        char* k_pntr = input + last_offset; 
        last_offset = I;
        double cur_k = 0; 
        char sign = input[I];
        input[I] = '\0';               

        char *x_pntr = strchr(k_pntr, 'x');
        if (x_pntr == NULL){
            free_part_flag = true;
        }else{
            free_part_flag = false;
            *x_pntr = '\0';
            x_pntr++;
        }

        if (*k_pntr == '\0' && start_flag && !free_part_flag){
            cur_k = 1;
            start_flag = false;
        }else if (*(k_pntr + 1) == '\0' && *k_pntr == '+'){
            cur_k = 1;
        }else if ( *(k_pntr + 1) == '\0' && *k_pntr == '-'){
            cur_k = -1;
        }else{        
            cur_k = atof(k_pntr);
        }
        if (free_part_flag){
            x_coeffs[0] += cur_k;
        }else if (*x_pntr == '\0'){
            x_coeffs[1] += cur_k;
        }else{
            //TODO atoi 3 times
            if (atoi(x_pntr) > 2 || atoi(x_pntr) < 0){
                return true;
            }
            x_coeffs[atoi(x_pntr)] += cur_k;
        }
        input[I] = sign;
    }

    printf("%lg %lg %lg\n", x_coeffs[2], x_coeffs[1], x_coeffs[0]);
    q->a = x_coeffs[2];
    q->b = x_coeffs[1];
    q->c = x_coeffs[0];

    return completed_flag;
}
//TODO func to splite sum and multipy
bool trashCleaner(char *input){
    const char *validChr = "0123456789.x+-*^\n\0";
    unsigned J = 0;
    for(unsigned I = 0, n =  unsigned(strlen(input)); I < n; I++){
        if (input[I] == ' '){
            continue;
        } 
          
        if (strchr(validChr, input[I]) == NULL){
            return true;
        }
        input[J] = input[I];
        J++;
    }
    input[J] = '\0';
    return false;
}

bool signCheck(char *input){
    unsigned J = 0;
    
    for(unsigned I = 0, n =  unsigned(strlen(input)); I < n; I++){
        if (input[I] == '*' || input[I] == '^'){
            if (input[I+1] == '*' || input[I+1] == '^'){
                return true;
            }
            if (input[I+1] == '+' || input[I+1] == '-'){
                return true;
            }
            continue;
        }
        if (input[I] == '+' || input[I] == '-'){
            if (input[I+1] == '+' || input[I+1] == '-'){
                return true;
            }
        }
        //TODO +*
        input[J] = input[I];
        J++;
    }
    input[J] = '\0';
    return false;
}