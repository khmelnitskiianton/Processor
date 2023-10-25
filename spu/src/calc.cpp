#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "arrays.h"
#include "type.h"
#include "main.h"
#include "calc.h"
#include "buffer.h"
#include "stack.h"
#include "support.h"

int process_asm (Spu_t *mySpu)
{
    int checkOk = 1;
    while (checkOk)
    {
        int return_value = do_command (mySpu, *(mySpu -> actual_command));
        
        if (return_value == IF_HLT)     break;
        if (return_value == IF_COMMAND) (mySpu -> actual_command)++;

    ON_PRINTING(
        printing_stack (&(mySpu -> myStack), __FILE__, __LINE__, __PRETTY_FUNCTION__);
    )
    }
    return 1;
}

int do_command (Spu_t* mySpu, int command)
{
    switch(command)
    {
        #define DEF_CMD(name, name_full, num, bin_num, ...)             \
            case COMMANDS[name_full].bin_code: __VA_ARGS__ break; 
            
        #include "commands.h"

        #undef DEF_CMD       
        
        default: 
        {
            fprintf(stdout, "\n<<<<<<<!YOU HAVE ERROR!>>>>>>\n<<<<<<!UNKNOWN CODE!>>>>>>\n");
            fprintf(mySpu -> myBuffer.file_out, "\n<<<<<<<!YOU HAVE ERROR!>>>>>>\n<<<<<<!UNKNOWN CODE!>>>>>>");
            file_close(mySpu -> myBuffer.file_out);
            abort(); 
        }
        break;
    }       
    return IF_COMMAND;
}

int clean_buffer (void)
{
    int ch = 0;                     
    while ((ch = getchar ()) != '\n') {}   
    return 1;
}