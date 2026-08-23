#ifndef __CLI_PROC__
#define __CLI_PROC__

typedef enum{
    INFO = 0,
    HELP = 1,
    HAND_INPUT = 2,
    FILE_INPUT = 3,
    TESTING = 4,
    PARS = 5,
    ERROR = 6,
} CLI_SCRIPTS;

CLI_SCRIPTS getScript(int argc, const char *argv[]);

#endif