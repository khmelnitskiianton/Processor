#include <stdio.h>
#include <assert.h>
#include <limits.h> 
#include <string.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>

#include "main.h"
#include "calc.h"
#include "stack.h"
#include "support.h"

int main(void)
{
    Stack_t myStack = {};
    
    StackCtor (&myStack);
    int command = NULL;
    double argument = POISON_ELEMENT;
    while (fscanf(myStack.file_in,"%d", &command) == 1)
    {
        if ((command == 1)) 
        {
            if (fscanf(myStack.file_in,"%lf", &argument) == 1)
            {
                do_command(&myStack, command, argument);
            }
            else continue;
        }
        else if (do_command(&myStack, command, POISON_ELEMENT)) break;

    ON_PRINTING(
        printing_stack (&myStack, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    )
    }

    StackDtor (&myStack);
    return 0;
}