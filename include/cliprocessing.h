#ifndef __CLI_PROC__
#define __CLI_PROC__

typedef enum{
    CLI_INFO = 0,
    CLI_HELP = 1,
    CLI_CODE = 2,
    CLI_FILE_ERROR = 3,
    CLI_ERROR = 5
}CLI_MAIN_FLAG;

typedef enum{
    HAND_INPUT = 0,
    PARS_INPUT = 1,
    TEST_INPUT = 2
}CLI_INPUT_TYPE_FLAG;

// typedef enum{
//     INPUT_TYPE = 1,
//     FILE_FLAG = 2,
//     SHOORT_OUTPUT = 4
// }CLI_SPECIAL_FLAG;

struct CLI_FLAG{
    CLI_MAIN_FLAG main_flag;
    CLI_INPUT_TYPE_FLAG input_type;
    unsigned input_count;
    // short special_flag; 
    int file_name_index;
    bool input_type_flag : 1;
    bool file_flag : 1;
    bool shoort_output_flag : 1;
};

CLI_FLAG getCliFlags(int argc, char *argv[]);

#endif