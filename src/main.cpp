#include <stdio.h>
#include <math.h>

#include "colors.h"
#include "returns.h"
#include "cliprocessing.h"
#include "parser.h"
#include "quade.h"
#include "handlers.h"
#include "visual.h"

int main(int argc, char *argv[])
{    
    CLI_FLAG CLI_OUT = getCliFlags(argc, argv);
    OUTPUTS handler_output = mainHandler(&CLI_OUT);
    
    if (handler_output == MAIN_CODE){
        QuadraticEquation Q = {};
        OUTPUTS code_output = codeHandler(&CLI_OUT, argv, &Q);
        if (code_output == CORRECT && CLI_OUT.input_type != CODE_TEST && CLI_OUT.visual_flag){
            visualInit();
            visualLoop(&Q);
            CloseWindow();
            printRoots(&Q);
        }
        errorHandler(code_output);
        return code_output;
    } else {
        errorHandler(handler_output);
        return handler_output;
    }    
}
