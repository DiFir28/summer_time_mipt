#include "returns.h"

#include <stdio.h>
#include "colors.h"

void errorHandler(OUTPUTS output)
{
    switch(output)
    {
    case CORRECT:
        break;
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
    case MAIN_CODE:
        break;
    }
}