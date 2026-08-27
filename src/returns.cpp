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
        printf(RED_ "FILE ERROR" DEFAULT_COLOR);
        break;
    case INCORRECT_PARAM:
        printf(RED_ "INVALID PARAM" DEFAULT_COLOR);
        break;
    case INCORRECT_X_POWER:
        printf(RED_ "INVALID X POWER" DEFAULT_COLOR);
        break;
    case FEW_SIGNS_IN_ROW:
        printf(RED_ "INVALID INPUT: FEW SIGNS IN A ROW" DEFAULT_COLOR);
        break;
    case UNKNOWN_CLI_FLAGS:
        printf(RED_ "INCORRECT COMMAND LINE ARGS" DEFAULT_COLOR);
        break;
    case MAIN_CODE:
        break;
    }
}