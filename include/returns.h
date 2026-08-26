#ifndef __RETURNS__
#define __RETURNS__

typedef enum{
    CORRECT = 0,
    MAIN_CODE = 1,
    INCORRECT_PARAM = 2,
    INCORRECT_X_POWER = 3,
    FILE_ERROR = 4,
    FEW_SIGNS_IN_ROW = 5,
    UNKNOWN_CLI_FLAGS = 6,
} OUTPUTS;

void errorHandler(OUTPUTS output);
#endif