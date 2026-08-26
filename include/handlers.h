#ifndef __HANDLERS__
#define __HANDLERS__

/**
 * @file handlers.h
 * @brief handlers based on CLI arguments
 */
#include "returns.h"
#include "cliprocessing.h"

/**
 * @brief handle CLI arguments
 * @param[in] cli_flag  parsed CLI arguments
 * @return OUTPUTS
 * @see OUTPUTS
 */
OUTPUTS mainHandler(CLI_FLAG *cli_flag);

/**
 * @brief run code based on CLI arguments
 * @param[in] cli_flag  parsed CLI arguments
 * @param[in] argv      CLI arguments
 * @return OUTPUTS
 * @see OUTPUTS
 */
OUTPUTS codeHandler(CLI_FLAG *cli_flag, char *argv[]);

/**
 * @brief run unitets based on CLI arguments
 * @return OUTPUTS
 * @see OUTPUTS
 */
OUTPUTS TestHandler();

#endif