#include <stdio.h>
#include "quade.h"

double tests[7][6]={
    {4, 1, -1.3, ROOTS_TWO, 0.45863087, -0.70863087},
    {-1, 3.2, 4.7, ROOTS_TWO, -1.09443871, 4.29443871},
    {-4, 12, -9, ROOTS_ONE, 1.5, 0},
    {0, -2.6, 3.8, ROOTS_ONE, 1.46153846, 0},
    {0, 0, -6.6,  ROOTS_ZERO, 0, 0},
    {0, 0, 0, ROOTS_INF, 0, 0},
    {-6.4, 0, 4.2, ROOTS_TWO, -0.81009258, 0.81009258}
};

int main(void){

    for (int i = 0; i<7; i++){

        Quadratic Equat = initQuadratic();
        Equat.a = tests[i][0];
        Equat.b = tests[i][1];
        Equat.c = tests[i][2];
        checkQuadratic(&Equat);

        solveQuadratic(&Equat);

        if (Equat.rootscount == tests[i][3]){
            if (isZero(tests[i][4] - Equat.root1) && isZero(tests[i][5] - Equat.root2)){
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

    // Quadratic Equat = initQuadratic();
    // if (inputQuadratic(&Equat)){
    //     printf("Incorrect input.\n");
    //     return 1;
    // }

    // solveQuadratic(&Equat);
    // printQuadratic(&Equat);

    return 0;
}