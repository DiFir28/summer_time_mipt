#include <stdio.h>
#include "quade.h"

Quadratic tests[]={
    {4, 1, -1.3, 0.45863087, -0.70863087, ROOTS_TWO},
    {-1, 3.2, 4.7, -1.09443871, 4.29443871, ROOTS_TWO},
    {-4, 12, -9, 1.5, 0, ROOTS_ONE},
    {0, -2.6, 3.8, 1.46153846, 0, ROOTS_ONE},
    {0, 0, -6.6, 0, 0, ROOTS_ZERO},
    {0, 0, 0, 0, 0, ROOTS_INF},
    {-6.4, 0, 4.2, -0.81009258, 0.81009258, ROOTS_TWO}
};

int main(void){

    for (int i = 0; i < (sizeof(tests)/sizeof(tests[0])); i++){

        Quadratic Equat = initQuadratic();
        Equat.a = tests[i].a;
        Equat.b = tests[i].b;
        Equat.c = tests[i].c;
        validQuadratic(&Equat);

        solveQuadratic(&Equat);

        if (Equat.rootscount == tests[i].rootscount){
            if (isZero(tests[i].root1 - Equat.root1) && isZero(tests[i].root2 - Equat.root2)){
                printf("Test %i pass\n", i+1);
            }
            else{
            printf("Test %i fail\n", i+1);
            }
        }
        else{
            printf("Test %i fail\n", i+1);
        }
    }

    return 0;
}