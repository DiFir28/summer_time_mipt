#ifndef __HANDLERS__
#define __HANDLERS__

#include "returns.h"
#include "cliprocessing.h"

OUTPUTS mainHandler(CLI_FLAG *cli_flag, char *argv[]);
OUTPUTS codeHandler(CLI_FLAG *cli_flag, char *argv[]);
OUTPUTS TestHandler();

#endif