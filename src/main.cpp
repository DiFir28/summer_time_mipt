#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "colors.h"
#include "returns.h"
#include "cliprocessing.h"
#include "parser.h"
#include "quade.h"
#include "handlers.h"

int main(int argc, char *argv[])
{
    CLI_FLAG CLI_OUT = getCliFlags(argc, argv);
    OUTPUTS handler_output = mainHandler(&CLI_OUT);

    if (handler_output == MAIN_CODE){
        OUTPUTS code_output = codeHandler(&CLI_OUT, argv);
        errorHandler(code_output);
        return code_output;
    } else {
        errorHandler(handler_output);
        return handler_output;
    }    
}
