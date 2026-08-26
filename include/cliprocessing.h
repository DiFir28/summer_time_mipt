#ifndef __CLI_PROC__
#define __CLI_PROC__

/** 
 * @file cpiprocessing.h
 * @brief pars CLI arguments
*/

/**
 * @brief enum for main code behavior
 */
typedef enum{
    CLI_INFO = 0, /**< print info */
    CLI_HELP = 1, /**< print help */
    CLI_CODE = 2, /**< run main code */
    CLI_ERROR = 3 /**< CLI error */
}CLI_MAIN_FLAG;

/**
 * @brief enum for data source
 */
typedef enum{
    SEP_INPUT = 0, /**< flag for hand input: a b c */ //TODO rename
    PARS_INPUT = 1, /**< flag for parse input*/
    CODE_TEST = 2  /**< unitest flag */
}CLI_INPUT_TYPE_FLAG;

/**
 * @brief CLI output struct
 */
struct CLI_FLAG{
    CLI_MAIN_FLAG main_flag;        /**< main code behavior*/
    CLI_INPUT_TYPE_FLAG input_type; /**< data source*/
    unsigned input_count;           /**< count of repeat */
    // short special_flag; 
    int file_name_index;            /**< index of file name */
    bool input_type_flag : 1;       /**< flag that input type already inputed */
    bool file_flag : 1;             /**< file source flag */
    // bool shoort_output_flag : 1;  
};

/**
 * @brief CLI arg parser
 * @param[in] argc arg count
 * @param[in] argv args
 * @return CLI_FLAG
 */
CLI_FLAG getCliFlags(int argc, char *argv[]);

#endif