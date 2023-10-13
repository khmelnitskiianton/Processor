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

struct Line {
    size_t len;
    char* start_line;
};

typedef struct Buffer {
    FILE*  file_in;
    FILE*  file_out;

    size_t size_text;
    size_t n_strings;

    char* text_buffer;
    Line* string_buffer;

} Buffer_t;

enum math_codes {
    PUSH_NUM = 0,
    PUSH_REG = 1,
    POP_REG  = 2,
    IN       = 3,
    SUB      = 4,
    DIV      = 5,
    ADD      = 6,
    MUL      = 7,
    SQRT     = 8,
    SIN      = 9,
    COS      = 10,
    OUT      = 11,
    HLT      = 12,
};

enum arg_formats {
    ARG_FORMAT_COMMAND  = 0b0000'1111,
    ARG_FORMAT_IMMED    = 0b0001'0000,
    ARG_FORMAT_REGISTER = 0b0010'0000,
};

const BinCommand_t COMMANDS[] = 
{
    {"push", 0b0001'0001},
    {"push", 0b0010'0001},

    {"pop",  0b0010'0010},
    {"in",   0b0000'0011},
    {"div",  0b0000'0100},
    {"add",  0b0000'0101},
    {"mul",  0b0000'0110},

    {"sqrt", 0b0000'0111},
    {"sub",  0b0000'1000},
    {"cos",  0b0000'1001},
    {"sin",  0b0000'1010},  
    {"out",  0b0000'1011}, 

    {"hlt",  0b0000'1111}, 
};

const RegID_t REGISTERS[] = {
    {"rax", 1},
    {"rbx", 2},
    {"rcx", 3},
    {"rdx", 4},
};

const size_t AMOUNT_OF_COMMANDS  = sizeof(COMMANDS)  / sizeof(BinCommand);
const size_t AMOUNT_OF_REGISTERS = sizeof(REGISTERS) / sizeof(RegID_t);
  
#endif 