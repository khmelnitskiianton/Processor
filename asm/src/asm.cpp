#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arrays.h"
#include "type.h"
#include "main.h"
#include "support.h"
#include "buffer.h"
#include "asm.h"

int Assembling(Asm_t *myAsm, int n_run)
{
    RecoverAll (myAsm);
    for (size_t i = 0; i < (myAsm -> asmCode).n_strings; i++)
    {
        char* str = (*(((myAsm -> asmCode).string_buffer) + i)).start_line;
        CMDLine_t myCMDline = {};
        InitLine(&myCMDline);
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
    return 1;
}

int WriteCommandToBuf (CMDLine_t* myCMDline, Asm_t *myAsm)
{
    for (size_t i = 0; i < AMOUNT_OF_COMMANDS; i++)
    {
        if (!strcmp (myCMDline -> command, COMMANDS[i].command))
        {
            int bin_command = (int) COMMANDS[i].bin_code & ARG_FORMAT_COMMAND;
            
            if ((myCMDline -> reg) != NULL) bin_command |= ARG_FORMAT_REGISTER;

            if (!COMPARE_TYPE((myCMDline -> value), POISON_ELEMENT)) bin_command |= ARG_FORMAT_IMMED;
            
            *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = bin_command;
            (myAsm -> binCode).n_elements++;

            if ((myCMDline -> reg) != NULL) 
            {
                int reg_id = get_reg_id (myCMDline -> reg);
                *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = reg_id;
                ((myAsm -> binCode).n_elements)++;
            }

            if (!COMPARE_TYPE((myCMDline -> value), POISON_ELEMENT))
            {
                *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = myCMDline -> value;
                ((myAsm -> binCode).n_elements)++;
            }

            if ((myCMDline -> cmd_label) != NULL)
            {
                *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = -1;
                
            ON_SECOND_RUN(
                *((myAsm -> binCode).bin_buffer + (myAsm -> binCode).n_elements) = SearchingLabel (myCMDline, myAsm);
            )

                ((myAsm -> binCode).n_elements)++;
            }

            return 1;
        }
    }
    return 0;
}

int CompleteStructWithCMD (size_t amount_args, char* arg, CMDLine_t* myCMDline)
{
    switch (amount_args)
    {
        case 0:
            if (isCommand(arg)) 
            {
                myCMDline -> command = arg;
            }
            else
            {
                //make dump print
            }
        break;
        case 1: 
            if      (isReg(arg))      {myCMDline -> reg       = arg;}
            else if (isCMDLabel(arg)) {myCMDline -> cmd_label = arg;}
            else if (isValue(arg))    {myCMDline -> value     = STR_TO_INT(arg)}
            else 
            {
                //make dump print
            }
        break;

        default:
                //make dump print
        break;
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
    size_t amount_args = 0;
    char* arg = strtok(str, " ");
    while (arg) 
    {
        CompleteStructWithCMD (amount_args, arg, myCMDline);
        arg = strtok(NULL, " ");
        amount_args++;
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
    fwrite((myAsm -> binCode).bin_buffer, sizeof(Elem_t), (myAsm -> binCode).n_elements , (myAsm -> asmCode).file_out);
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
    if   (many_labels) return 0; //TODO: check for overflow array of labels
    else return 1;
}

int SearchingLabel (CMDLine_t* myCMDline, Asm_t *myAsm)
{
    for (size_t i = 0; i < AMOUNT_OF_LABELS; i++)
    {
        if (myAsm -> labels[i].len_label == 0)
        {
            if (!strcmp(myAsm -> labels[i].label + 1, myCMDline -> cmd_label))
            {
                return myAsm -> labels[i].address;
            }
        }
        else if (!strncmp(myAsm -> labels[i].label, myCMDline -> cmd_label, myAsm -> labels[i].len_label))
        {
            return myAsm -> labels[i].address; 
        }
    }
    return -1; //TODO: no matching labels
}
