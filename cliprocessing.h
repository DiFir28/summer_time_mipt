#ifndef __CLI_PROC__
#define __CLI_PROC__

typedef enum{
    INFO = 0,
    HELP = 1,
    HAND_INPUT = 2,
    FILE_INPUT = 3,
    TESTING = 4,
    ERROR = 5
} CLI_SCRIPTS;

CLI_SCRIPTS getScript(int argc, char *argv[]);

#endif