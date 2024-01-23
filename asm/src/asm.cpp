#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "arrays.h"
#include "type.h"
#include "main_asm.h"
#include "support.h"
#include "buffer.h"
#include "asm.h"
#include "myassert.h"

int Assembling(Asm_t *myAsm, int n_run)
{
    myAsm -> binCode.n_elements = 0;
    for (size_t i = 0; i < (myAsm -> asmCode).n_strings; i++)
    {
        char* str = (*(((myAsm -> asmCode).string_buffer) + i)).start_line;

    ON_FIRST_RUN(
        CleaningComments (str, SYMBOL_OF_COMMENT);
    )
        str = SkipSpaces (str);
        if (!str) continue;
        
        CMDLine_t myCMDline = {};
        InitLine (&myCMDline);
        myCMDline.n_run = n_run;

        if (isLabel(str))
        {
            ProcessLabel (str, &myCMDline, myAsm);
        }
        else
        {
            ProcessCMD   (str, &myCMDline, myAsm); 
        }
    }
    ON_LISTING(
        fprintf (myAsm -> file_listing, DIVIDER);
    )
    return 1;
}

int WriteCommandToBuf (CMDLine_t* myCMDline, Asm_t *myAsm)
{
    MYASSERT(myCMDline -> command, BAD_POINTER_PASSED_IN_FUNC, return 0)

    for (size_t i = 0; i < AMOUNT_OF_COMMANDS; i++)
    {
        if (!strncmp (myCMDline -> command, COMMANDS[i].command, myCMDline -> length_cmd))
        {
            int bin_command = (int) COMMANDS[i].bin_code & ARG_FORMAT_COMMAND;
            if ((myCMDline -> reg) != 0)                bin_command |= ARG_FORMAT_REGISTER;
            if ((myCMDline -> value) != POISON_ELEMENT) bin_command |= ARG_FORMAT_IMMED;
            if ((myCMDline -> brackets) != 0)           bin_command |= ARG_FORMAT_MEMORY;

        ON_LISTING(
            int no_arg = PrintAsmListing (myCMDline, myAsm, bin_command);
        )    

            *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = bin_command;
            (myAsm -> binCode).n_elements++;

            if ((myCMDline -> reg) != 0) 
            {
                int reg_id = get_reg_id (myCMDline -> reg);
                *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = reg_id;
            ON_LISTING(
                no_arg = 0;    
                fprintf (myAsm -> file_listing, "\t|REG: %d|", reg_id);
            )
                ((myAsm -> binCode).n_elements)++;
            }

            if ((myCMDline -> value) != POISON_ELEMENT)
            {
                *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = myCMDline -> value;
            ON_LISTING(    
                no_arg = 0;
                fprintf (myAsm -> file_listing, "\t|VALUE: %d|", myCMDline -> value);
            )
                ((myAsm -> binCode).n_elements)++;
            }

            if ((myCMDline -> cmd_label) != NULL)
            {
                *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = -1;
                
            ON_SECOND_RUN(
                *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = SearchingLabel (myCMDline, myAsm);
            )

            ON_LISTING(    
                no_arg = 0;
                fprintf (myAsm -> file_listing, "\t|LABEL: %d|", *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements));
            )
                ((myAsm -> binCode).n_elements)++;
            }
            ON_LISTING(
                if (no_arg) fprintf (myAsm -> file_listing, "\t\t|NO ARGS|");
                fprintf (myAsm -> file_listing,"\n");
            )
            return 1;
        }
    }
    return 0;
}

int CompleteStructWithCMD (Parsing_t myActualWord, CMDLine_t* myCMDline)
{
    switch (myActualWord.n_word)
    {
        case 0:
            if (isCommand (myActualWord.start_word)) 
            {
                myCMDline -> command    = myActualWord.start_word;
                myCMDline -> length_cmd = myActualWord.length_word;
            }
            else
            {
                printf ("\n>>>>>UNKNOWN SYMBOL!!!<<<<<\n");
            }
        break;
        case 1:
        {
            int scan_done = 0; 
            if (strchr (myActualWord.start_word, '[') != nullptr)
            {
                if (strchr (myActualWord.start_word, ']') == nullptr) 
                {
                    printf ("\n>>>>>NO CLOSE BRACKET!!!<<<<<\n");
                }
                scan_done = ScanWithBrackets    (myActualWord, myCMDline);
            }
            else
            {
                scan_done = ScanWithoutBrackets (myActualWord, myCMDline);
            }
            if (!scan_done)
            {
                myCMDline -> cmd_label = myActualWord.start_word;
            }
        }
        break;
        default: break;
    }
    return 0;
}

int CompleteStructWithLabel (char* arg, CMDLine_t* myCMDline, Asm_t* myAsm)
{
    myCMDline -> label = arg;
    FillLabels (myCMDline, myAsm);
    return 1;
}

int ProcessCMD (char* str, CMDLine_t* myCMDline, Asm_t* myAsm)
{    
    Parsing_t myActualWord = {};
    myActualWord.start_word  = str;
    myActualWord.length_word = ParsingString (&myActualWord, ' ');
    int run = 1;
    while (run) 
    {
        CompleteStructWithCMD (myActualWord, myCMDline);
        if ((myActualWord.end_of_str == 1) || (myActualWord.n_word > 2))
        {
            break;
        }
        
        myActualWord.start_word = myActualWord.start_word + myActualWord.length_word + 1;
        myActualWord.length_word = ParsingString (&myActualWord, ' ');
        myActualWord.n_word++;
    }
    WriteCommandToBuf (myCMDline, myAsm);
    return 1;
}

int ProcessLabel (char* str, CMDLine_t* myCMDline, Asm_t* myAsm)
{
    ON_SECOND_RUN(return 1;)
    char* arg = str;
    CompleteStructWithLabel (arg, myCMDline, myAsm);
    return 1;
}

int WriteBufToFile (Asm_t *myAsm)
{
    fwrite((myAsm -> binCode).bin_buffer, sizeof(Elem_t), (size_t)(myAsm -> binCode).n_elements , (myAsm -> asmCode).file_out);
    return 1;
}

int FillLabels (CMDLine_t* myCMDline, Asm_t* myAsm)
{
    int many_labels = 1;
    for (size_t i = 0; i < AMOUNT_OF_LABELS; i++)
    {
        if (myAsm -> labels[i].label == NULL)
        {
            many_labels = 0;
            myAsm -> labels[i].label     = myCMDline -> label;
            myAsm -> labels[i].address   = myAsm -> binCode.n_elements;
            myAsm -> labels[i].len_label = LabelLength (myCMDline);                 
            break;
        }
    }
    if (many_labels) 
    {
        printf ("\n>>>>>OVERFLOW IN ARRAY OF LABELS!!!<<<<<\n");
        return 0; 
    }
    else return 1;
}

int SearchingLabel (CMDLine_t* myCMDline, Asm_t *myAsm)
{
    for (size_t i = 0; i < AMOUNT_OF_LABELS; i++)
    {
        if (!strncmp (myAsm -> labels[i].label, myCMDline -> cmd_label, myAsm -> labels[i].len_label))
        {
            return myAsm -> labels[i].address; 
        }
    }
    fprintf (stdout, ">>>>>NO MATCHING LABELS!!!!<<<<<");
    return -1;
}

int ScanWithoutBrackets (Parsing_t myActualWord, CMDLine_t* myCMDline)
{
    double double_number = NAN;
    myCMDline -> brackets = 0;
    int n_1 = -1;
    int n_2 = -1;
    char ch[10] = {};
    int return_amount = -1;

    return_amount = sscanf(myActualWord.start_word, " %nr%1[a-z]x%n + %lf", &n_1, ch, &n_2, &(double_number));
    if (return_amount == 2)
    {
        if ((n_2 - n_1) == 3) 
        { 
            (myCMDline -> reg) = *ch;
        }
        else 
        {   
            USER_ERROR(0, BAD_NAME_OF_REGISTER, exit(0))
        }
        if (!isnan (double_number)) myCMDline -> value = (int) (double_number * N_DIGIT);
        else 
        {
            USER_ERROR(0, VALUE_OUT_OF_RANGE, exit(0))
        }
        return 1;
    }

    return_amount = sscanf (myActualWord.start_word, " %nr%1[a-z]x%n", &n_1, ch, &n_2);
    if (return_amount == 1)
    {
        if ((n_2 - n_1) == 3) 
        { 
            (myCMDline -> reg) = *ch;
        }
        else 
        {   
            (myCMDline -> reg) = 0;
            USER_ERROR(0, BAD_NAME_OF_REGISTER, exit(0))
        }
        return 1;
    }

    return_amount = sscanf (myActualWord.start_word, " %lf",  &(double_number));
    if (return_amount == 1)
    {
        myCMDline -> value = (int) (double_number * N_DIGIT);
        return 1;
    }

    return 0;
}

int ScanWithBrackets (Parsing_t myActualWord, CMDLine_t* myCMDline)
{   
    myCMDline -> brackets = HAVE_BRACKETS;
    int number = -1;
    int n_1 = -1;
    int n_2 = -1;
    char ch[10] = {};
    int return_amount = -1;

    return_amount = sscanf (myActualWord.start_word, " %n[r%1[a-z]x%n + %d]",  &n_1, ch, &n_2, &number);
    if (return_amount == 2)
    {
        if ((n_2 - n_1) == 4)
        {
            myCMDline -> reg = *ch;
            myCMDline -> value = number;
        }
        else 
        {
            (myCMDline -> reg) = 0;
            USER_ERROR(0, BAD_NAME_OF_REGISTER, exit(0))
        }
        return 1;
    }
    return_amount = sscanf (myActualWord.start_word, " %n[r%1[a-z]x]%n", &n_1, ch, &n_2);
    if (return_amount == 1)
    {
        if ((n_2 - n_1) == 5)
        {
            myCMDline -> reg = *ch;
        }
        else
        {
            (myCMDline -> reg) = 0;
            USER_ERROR(0, BAD_NAME_OF_REGISTER, exit(0))
        }
        return 1;
    }    

    return_amount = sscanf (myActualWord.start_word, " [%d]", &number);
    if (return_amount == 1)
    {
        myCMDline -> value = number;
        return 1;
    }
    return 0;
}