#ifndef __HANDLERS__
#define __HANDLERS__

#include "returns.h"
#include "cliprocessing.h"

OUTPUTS mainHandler(CLI_FLAG *cli_flag, char *argv[]);
void printInfo();
void printHelp();
OUTPUTS codeHandler(CLI_FLAG *cli_flag, char *argv[]);
OUTPUTS handInputHandler();
OUTPUTS fileInputHandler(const char *file_name);
OUTPUTS parsHandler();
OUTPUTS TestHandler();

#endif