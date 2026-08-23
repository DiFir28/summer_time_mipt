#include "parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quade.h"
#include "colors.h"


#define MAX_INPUT_SIZE 100
#define MAX_INPUT_SIZE_STR "100"

bool NEWparsCoeffs(QuadraticEquation *q){
    checkLink(q);
    char input[MAX_INPUT_SIZE] = {0};
    double x_coeffs[3] = {0}; //! index ~ power of x
    
    printf(GREEN "Enter your equation in format ax^2+bx+c: " DEFAULT_COLOR);
    scanf("%" MAX_INPUT_SIZE_STR "[^\n]", input);
    
    if (trashCleaner(input)){
        printf(RED "INVALID INPUT\n" DEFAULT_COLOR);
        return true;
    }
    if ( signCheck(input)){
        printf(RED "INVALID INPUT\n" DEFAULT_COLOR);
        return true;
    }
    printf("%s\n", input);
    const char *prev = input;
    const char *ptr = sumSplit(input);
    while (*ptr != '\0'){
        // strnprint(prev,ptr-prev);
        // printf("\t");
        if(sumParsint(prev, ptr, x_coeffs)){
            printf(RED "INVALID INPUT POWER\n" DEFAULT_COLOR);
            return true;
        }
        prev = ptr;
        ptr = sumSplit(ptr+1);        
        // printf("\n");

        
        
    }
    // strnprint(prev,ptr-prev);
    // printf("\t");
    if(sumParsint(prev, ptr, x_coeffs)){
        printf(RED "INVALID INPUT POWER\n" DEFAULT_COLOR);
        return true;
    }    
    // printf("\n");
    printf("%lg %lg %lg", x_coeffs[2], x_coeffs[1], x_coeffs[0]);
    return false;
}

void strnprint(const char *input, unsigned n){
    for(unsigned i = 0; i < n; i++){
        printf("%c", *(input+i));
    }
}

const char *sumSplit(const char * const input){
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

const char *mulSplit(const char * const input){
    char *mul =strchr(input, '*');
    if (mul == NULL){
        return sumSplit(input);
    }
    return mul;
}

bool sumParsint (const char *prev, const char *ptr, double output_k[]){
   
    const char *mprev = prev;
    const char *mptr = mulSplit(prev+1);
    int x_power = 0;
    double curl_k = 1;
    while (mptr != NULL && ((ptr - mptr) > 0 )){
            // strnprint(mprev,mptr-mprev);
            // printf(" ");
            double cur_k = 0;
            int power = mulPars(mprev, mptr, &cur_k);
            curl_k*=cur_k;
            // printf("->%lg ^%i ", cur_k, power);
            x_power += power;
            mprev = mptr;
            mptr = mulSplit(mptr+1);
        }
        if (((ptr - mptr) < 0) || mptr == NULL){
            mptr = ptr;
        }
        // printf("end");
        // strnprint(mprev,mptr-mprev);
        // printf(" ");
        double cur_k = 0;
        int power = mulPars(mprev, mptr, &cur_k);
        curl_k*=cur_k;
        // printf("->%lg ^%i ", cur_k, power);
        x_power += power;


        if (x_power > 2 || x_power < 0){
            return true;
        }
        // printf( "k=%lg p=%i", curl_k, x_power);
        output_k[x_power] += curl_k;
        return false;
}

int mulPars(const char *input, const char *endMul, double *output_k){ // int - power of X
    while (input[0] == '*'){
        input++;
    }
    char *endK;
    *output_k = strtod(input, &endK);
    if (endMul == endK){
        return 0;
    }

    if (*output_k == 0.0){
        if (*input == 'x'){
            *output_k = 1;
        }
        else if(*input == '+'){
            *output_k = 1;
        }
        else {
            *output_k = -1;
        }
    }
    char *power = strchr(input, '^');
    if (power == NULL ||  power > endMul){
        return 1;
    }
    if (*(power+1) != '2'){
        return -1;
    }
    return 2;
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
        if (input[I] == '*' || input[I] == '^' || input[I] == '+' || input[I] == '-'){
            if (input[I+1] == '^' || input[I+1] == '-' || input[I+1] == '+'){
                return true;
            }
            if (input[I] == '*' && input[I+1] == '*'){
                if (input[I+2] == '*' || input[I+2] == '^' || input[I+2] == '+' || input[I+2] == '-'){
                    return true;
                }
                input[J] = '^';
                J++;
                I++;
                continue;
            }
        }
        input[J] = input[I];
        J++;
    }
    input[J] = '\0';
    return false;
}