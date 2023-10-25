#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "arrays.h"
#include "type.h"
#include "main.h"
#include "support.h"
#include "buffer.h"
#include "asm.h"

int get_reg_id (char* reg_str)
{
    for (size_t i = 0; i < AMOUNT_OF_REGISTERS; i++)
    {
        if (!strcmp(reg_str, REGISTERS[i].name)) return REGISTERS[i].id;
    }
    return 0;
}

int isReg (char* arg)
{
    if ((strlen(arg) > 2) && (arg[0] == 'r') && (arg[2] == 'x')) return 1;
    return 0;
}

int isCommand (char* arg)
{
    if (isalpha(arg[0])) return 1;
    return 0;
}

int isCMDLabel (char* arg)
{
    if (isalpha(arg[0])) return 1;
    return 0;
}

int isLabel (char* arg)
{
    if (strchr(arg, ':') != nullptr) return 1;
    return 0;
}

int isValue (char* arg)
{
    if (isdigit(arg[0])) return 1;
    return 0;
}

int RecoverTextBuffer (Asm_t* myAsm)
{
    for (size_t i = 0; i < (myAsm -> asmCode).n_strings; i++)
    {
        char*  str        = (*(((myAsm -> asmCode).string_buffer) + i)).start_line;
        size_t length_str = (*(((myAsm -> asmCode).string_buffer) + i)).len;
        for (size_t j = 0; j < length_str; j++)
        {
            if (*(str + j) == '\0') *(str + j) = ' ';
        }
    } 
    return 1;
}

int RecoverAll (Asm_t* myAsm)
{
    RecoverTextBuffer (myAsm);
    myAsm -> binCode.n_elements = 0;
    return 1;
}

int InitLine (CMDLine_t* myCMDline)
{
    myCMDline -> command   = nullptr;
    myCMDline -> reg       = nullptr; 

    myCMDline -> label     = nullptr;
    myCMDline -> cmd_label = nullptr;

    myCMDline -> value     = POISON_ELEMENT;

    myCMDline -> n_run     = NULL;

    return 1;
}

size_t LabelLength (CMDLine_t* myCMDline)
{
    char* str = myCMDline -> label;
    size_t n_chars = 0;
    while ((*(str + n_chars) != ':'))
    {
        n_chars++;
    }
    return n_chars;
}