#ifndef ARRAYS_H
#define ARRAYS_H
        
typedef struct BinCommand
{
    const char* const command;
    const int bin_code;

} BinCommand_t;

typedef struct RegisterID
{
    const char* name;
    const int id;

} RegID_t;

enum arg_formats {
    ARG_FORMAT_COMMAND  = 0b000'11111,
    ARG_FORMAT_IMMED    = 0b001'00000,
    ARG_FORMAT_REGISTER = 0b010'00000,
};

constexpr BinCommand_t COMMANDS[] = 
{
    #define DEF_CMD(name, name_full, num, bin_num, ...) {#name, bin_num},

    #include "commands.h"

    #undef DEF_CMD
};

enum math_codes {
    #define DEF_CMD(name, name_full, num, bin_num, ...) name_full = num,
    
    #include "commands.h"

   #undef DEF_CMD
};

const RegID_t REGISTERS[] = {
    {"rax", 1},
    {"rbx", 2},
    {"rcx", 3},
    {"rdx", 4},
};

const size_t AMOUNT_OF_COMMANDS  = sizeof(COMMANDS)  / sizeof(BinCommand);
const size_t AMOUNT_OF_REGISTERS = sizeof(REGISTERS) / sizeof(RegID_t);

#define FILE_TEXT  "./input_text.txt"
#define FILE_BIN   "./input_bin.txt"
#define FILE_OUT   "./output.txt"

#endif 