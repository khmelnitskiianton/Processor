#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

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

int compare (double x, double y)
{
    if (((isnan (x) == 1) && (isnan (y) == 1)) || (fabs (x - y) < EPSILONE))
        return 1;
    else
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
    if (arg[0] == ':') return 1;
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