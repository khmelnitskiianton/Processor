#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "arrays.h"
#include "type.h"
#include "main_asm.h"
#include "support.h"

int get_reg_id (char reg)
{
    int number = reg - 'a'; 
    if ((number >= 0) && (number <= AMOUNT_OF_REGISTERS)) return number;
    else
    {
        return -1;
        printf(">>>>>UNKNOWN REGISTER!!!<<<<<");
    }
}

int isValue   (char* arg)
{
    if(isdigit (arg[0])) return 1;
    return 0;
}

int isCommand (char* arg)
{
    if (isalpha (arg[0])) return 1;
    return 0;
}

int isLabel (char* arg)
{
    if (strchr (arg, ':') != nullptr) return 1;
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

int InitLine (CMDLine_t* myCMDline)
{
    myCMDline -> command   = nullptr;
    myCMDline -> reg       = 0; 

    myCMDline -> label     = nullptr;
    myCMDline -> cmd_label = nullptr;

    myCMDline -> value     = POISON_ELEMENT;

    myCMDline -> n_run     = 0;

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

size_t ParsingString (Parsing_t* myActualWord, char symbol)
{
    size_t counter_symbols = 0;
    while((*(myActualWord -> start_word + counter_symbols) != symbol) && (*(myActualWord -> start_word + counter_symbols) != '\0'))
    {
        counter_symbols++;
    }
    if (*(myActualWord -> start_word + counter_symbols) == '\0') myActualWord -> end_of_str = 1;
    return counter_symbols;
}

int CleaningComments (char* str, char symbol_of_comment)
{
    char* start_comment = strchr(str, symbol_of_comment);

    if (start_comment == NULL) return 0;

    int shift = 0;
    while (*(start_comment + shift) != '\0')
    {
        *(start_comment + shift) = '\0';
    }
    return 1;
}

int PrintAsmListing (CMDLine_t* myCMDline, Asm_t *myAsm, int bin_command)
{
    int no_arg = 1;
    fprintf (myAsm -> file_listing,"\t|\t%d\t|\t\t[%p]\t\t{0b", (myAsm -> binCode).n_elements, (myCMDline -> command));
    int copy_bin_command = bin_command;
    int bin_command_array[8] = {};
    int n_bit = 7;
    while (copy_bin_command > 0)
    {
        bin_command_array[n_bit] = copy_bin_command % 2;
        copy_bin_command = copy_bin_command / 2;
        n_bit--;
    }
    for (size_t j = 0; j < 8; j++)
    {
        if (j == 2) fprintf (myAsm -> file_listing, "%d\'", bin_command_array[j]);
        else fprintf (myAsm -> file_listing, "%d", bin_command_array[j]);
    }
    fprintf (myAsm -> file_listing, "}\t\t\"%s\"", myCMDline -> command);

    return no_arg;
}

char* SkipSpaces (char* str)
{
    while ((*str != '\0')&&(isspace(*str) != 0))
    {
        str++;
    }
    if (*str == '\0') return NULL;
    return str; 
}

int CheckNoArgs(char* str)
{
    int n_symbol = 0;
    while (*(str + n_symbol) != '\0')
    {
        if (*(str + n_symbol) != ' ') 
        {
            return 1;
        }
        n_symbol++;
    }
    return 0;
}