#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "colors.h"
#include "returns.h"
#include "cliprocessing.h"
#include "parser.h"
#include "quade.h"
#include "handlers.h"




int main(int argc, char *argv[]){

    CLI_FLAG script = getCliFlags(argc, argv);

    // if error, maybe not call main at all
    
    OUTPUTS main_output = mainHandler(&script, argv);
    switch (main_output)
    {
    case CORRECT:
        return 0;
    case FILE_ERROR:
        printf(RED "FILE ERROR" DEFAULT_COLOR);
        break;
    case INCORRECT_PARAM:
        printf(RED "INVALID PARAM" DEFAULT_COLOR);
        break;
    case INCORRECT_X_POWER:
        printf(RED "INVALID X POWER" DEFAULT_COLOR);
        break;
    case FEW_SIGNS_IN_ROW:
        printf(RED "INVALID INPUT: FEW SIGNS IN A ROW" DEFAULT_COLOR);
        break;
    case UNKNOWN_CLI_FLAGS:
        printf(RED "INCORRECT COMMAND LINE ARGS" DEFAULT_COLOR);
        break;
    }
    return main_output;
}
