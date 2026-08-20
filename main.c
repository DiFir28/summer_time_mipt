#include <stdio.h>
#include "quade.h"

int main(void){

    Quadratic Equat = initQuadratic();

    if (inputQuadratic(&Equat)){
        printf("Incorrect input.\n");
        return 1;
    }

    solveQuadratic(&Equat);
    printQuadratic(&Equat);

    return 0;
}