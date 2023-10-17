#ifndef COMMANDS_H
#define COMMANDS_H
        
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
    {"push", 0b001'00001},
    {"push", 0b010'00001},

    {"pop",  0b010'00010},
    {"in",   0b000'00011},
    {"div",  0b000'00100},
    {"add",  0b000'00101},
    {"mul",  0b000'00110},

    {"sqrt", 0b000'00111},
    {"sub",  0b000'01000},
    {"cos",  0b000'01001},
    {"sin",  0b000'01010},  

    {"out",  0b000'01011}, 
    {"hlt",  0b000'11111}, 
};

enum math_codes {
    PUSH_NUM = 0,
    PUSH_REG = 1,
    POP_REG  = 2,
    IN       = 3,
    DIV      = 4,
    ADD      = 5,
    MUL      = 6,
    SQRT     = 7,
    SUB      = 8,
    COS      = 9,
    SIN      = 10,
    OUT      = 11,
    HLT      = 12,
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