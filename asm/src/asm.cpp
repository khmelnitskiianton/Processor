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
#include "buffer.h"
#include "asm.h"

int txt_to_asm (BufferAsm_t *asmCode)
{
    for (size_t i = 0; i < asmCode -> n_strings; i++)
    {
        char* str = (*((asmCode -> string_buffer) + i)).start_line;
        Elem_t value   = POISON_ELEMENT;
        char*  reg     = NULL;
        char*  command = NULL;
        
        size_t amount_args = 0;

        char* arg = strtok(str, " ");
        while (arg) 
        {
            switch (amount_args)
            {
                case 0:
                    if      (isalpha(arg[0])) 
                    {
                        command = arg;
                    }
                    else
                    {
                        //make dump print
                    }
                break;
                case 1:
                    if      (isalpha(arg[0])) reg   = arg;
                    else if (isdigit(arg[0])) value = STR_TO_TYPE(arg)
                    else
                    {
                        //make dump print
                    }
                break;

                default:
                        //make dump print
                break;
            }
            arg = strtok(NULL, " ");
            amount_args++;
        }
        write_command (command, reg, value, asmCode);
    }
    return 1;
}

int write_command (char* command, char* reg, Elem_t value, BufferAsm_t* asmCode)
{
    for (size_t i = 0; i < AMOUNT_OF_COMMANDS; i++)
    {
        if (!strcmp (command, COMMANDS[i].command))
        {
            int bin_command = (int) COMMANDS[i].bin_code & ARG_FORMAT_COMMAND;
            
            if (reg != NULL) bin_command |= ARG_FORMAT_REGISTER;

            if (!COMPARE_TYPE(value, POISON_ELEMENT)) bin_command |= ARG_FORMAT_IMMED;

            fwrite  (&bin_command, sizeof(int), 1, asmCode -> file_out);

            if (reg != NULL) 
            {
                int reg_id = get_reg_id (reg);
                fwrite(&reg_id, sizeof(int), 1, asmCode -> file_out);
            }

            if (!COMPARE_TYPE(value, POISON_ELEMENT))
            {
                fwrite(&value, sizeof(Elem_t), 1, asmCode -> file_out);
            }
            return 1;
        }
    }
    return 0;
}
 

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
