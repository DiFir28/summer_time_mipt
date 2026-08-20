#ifndef __CLI_PROC__
#define __CLI_PROC__

typedef enum{
    INFO = 0,
    HELP = 1,
    HAND_INPUT = 2,
    FILE_INPUT = 3,
    ERROR = 4
} CLI_SCRIPTS;

#define HELP_ARG "--help"
#define HAND_WRITE_ARG "-input"
#define FILE_READ_ARG "-file"

CLI_SCRIPTS getScript(int argc, char *argv[]);

#endif