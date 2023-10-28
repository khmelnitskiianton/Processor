#ifndef ARRAYS_H
#define ARRAYS_H

#define LISTING_ASM 1

#if LISTING_ASM
#define ON_LISTING(...) __VA_ARGS__
#else
#define ON_LISTING(...)
#endif

#define LISTING_MEMORY 0

#if LISTING_MEMORY
#define ON_LISTING_MEMORY(...) __VA_ARGS__
#else
#define ON_LISTING_MEMORY(...)
#endif

typedef struct BinCommand
{
    const char* const command;
    const int bin_code;

} BinCommand_t;

typedef struct RegisterID
{
    const char* name;
    const int   id;
} RegID_t;

enum arg_formats {
    ARG_FORMAT_COMMAND  = 0b000'11111,
    ARG_FORMAT_IMMED    = 0b001'00000,
    ARG_FORMAT_REGISTER = 0b010'00000,
    ARG_FORMAT_MEMORY   = 0b100'00000,
};

constexpr BinCommand_t COMMANDS[] = 
{
    #define DEF_CMD(name, num, bin_num, ...) {#name, bin_num},

    #include "commands.h"

    #undef DEF_CMD
};

const RegID_t REGISTERS[] = {
    {"rax", 1},
    {"rbx", 2},
    {"rcx", 3},
    {"rdx", 4},
};

#define MEMORY_LENGTH 1600
#define LENG_OF_WINDOW 40

const size_t AMOUNT_OF_LABELS    = 30;
const size_t AMOUNT_OF_COMMANDS  = sizeof(COMMANDS)  / sizeof(BinCommand_t);
const size_t AMOUNT_OF_REGISTERS = sizeof(REGISTERS) / sizeof(RegID_t);

const int HAVE_BRACKETS = 1;
const char SYMBOL_OF_COMMENT = ';';

enum return_of_command {
    IF_HLT     = 0,
    IF_LABEL   = 1,
    IF_COMMAND = 2,
};

#define ON_FIRST_RUN(...) if (n_run == 1) __VA_ARGS__
#define ON_SECOND_RUN(...) if ((myCMDline -> n_run) == 2) __VA_ARGS__

#define DIVIDER "-------------------------------------------------------------------------------------------------------------\n"

#define FILE_TEXT "./input_text.txt"
#define FILE_BIN "./input_bin.txt"
#define FILE_LIST "./listing.txt"
#define FILE_LOG "./log.txt"
 
#endif 
