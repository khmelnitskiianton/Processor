#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include <unistd.h>

#include "arrays.h"
#include "type.h"
#include "stack_main.h"
#include "stack_base.h"
#include "stack_support.h"
#include "main_cpu.h"
#include "calc.h"
#include "buffer.h"
#include "support.h"

int process_asm (Cpu_t *myCpu)
{
    int checkOk = 1;
    int return_value = 0;
    while (checkOk)
    {
        return_value = do_command (myCpu);
        
        if (return_value == IF_HLT)     break;
        if (return_value == IF_COMMAND) (myCpu -> actual_command)++;
    }
    return 1;
}

int do_command (Cpu_t* myCpu)
{
    int command = *(myCpu -> actual_command);
    switch(command & ARG_FORMAT_COMMAND)
    {
        #define DEF_CMD(name, num, bin_num, ...)             \
            case bin_num: __VA_ARGS__ break; 
            
        #include "commands.h"

        #undef DEF_CMD       
        
        default: 
        {
            fprintf(stdout, "\n<<<<<<<!YOU HAVE ERROR!>>>>>>\n<<<<<<!UNKNOWN CODE!>>>>>>\n");
            fprintf(stdout, "%d\n", command);
            fprintf(myCpu -> myStack.file_write, "\n<<<<<<<!YOU HAVE ERROR!>>>>>>\n<<<<<<!UNKNOWN CODE!>>>>>>");
            file_close(myCpu -> myStack.file_write);
            abort(); 
        }
        break;
    }       
    return IF_COMMAND;
}

int clean_buffer (void)
{
    int ch = 0;                     
    while((ch = getchar ()) != '\n') {}   
    return 1;
}

int GetArg (Cpu_t* myCpu, int command, ArgCMD_t* myArgCMD)
{
    Elem_t summ = 0;    
    int modifier = 1;

    if (command & ARG_FORMAT_MEMORY) {modifier = N_DIGIT;}
    if (command & ARG_FORMAT_REGISTER)
    { 
        myArgCMD -> reg = *(++(myCpu -> actual_command));
        if ((myArgCMD -> reg >= 0) && (myArgCMD -> reg <= AMOUNT_OF_REGISTERS)) summ += (myCpu -> myRegs[myArgCMD -> reg])/modifier;
        else fprintf(myCpu -> myStack.file_write,">>>>>UNKNOWN REGISTER<<<<<");
    }
    if (command & ARG_FORMAT_IMMED)
    {
        myArgCMD -> value = *(++(myCpu -> actual_command));

        if ((myArgCMD -> value) != POISON_ELEMENT) 
        {
            summ += (myArgCMD -> value);
        }
        else fprintf(myCpu -> myStack.file_write,"\n\n>>>WARNING<<<\nVALUE == POISON!!!\n\n");
    }

    myArgCMD -> result = summ;

    return 1;
}