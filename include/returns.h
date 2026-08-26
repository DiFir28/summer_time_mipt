#ifndef __RETURNS__
#define __RETURNS__

/**
 * @file returns.h
 * @brief processing code outputs
 */

 /**
  * @brief enum of possible code outputs
  */
typedef enum{
    CORRECT = 0,            /**< No errors */
    MAIN_CODE = 1,          /**< No errors on Input, start main code*/
    INCORRECT_PARAM = 2,    /**< Incorrect param errors */
    INCORRECT_X_POWER = 3,  /**< Incorrect X power in equation */
    FILE_ERROR = 4,         /**< File error */
    FEW_SIGNS_IN_ROW = 5,   /**< Incorrect input: few signs in a row */
    UNKNOWN_CLI_FLAGS = 6,  /**< Incorrect CLI input */
} OUTPUTS;

/**
 * @brief processing possible errors
 * @param[in] output output for processing
 */
void errorHandler(OUTPUTS output);
#endif