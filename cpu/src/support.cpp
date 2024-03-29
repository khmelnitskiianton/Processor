#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>

#include "arrays.h"
#include "type.h"
#include "stack_main.h"
#include "stack_base.h"
#include "stack_support.h"
#include "main_cpu.h"
#include "calc.h"
#include "buffer.h"
#include "support.h"
#include "myassert.h"

int CpuCtor(Cpu_t* myCpu, const char* data_read)
{
    MYASSERT(myCpu, BAD_POINTER_PASSED_IN_FUNC, return 0)

    BufferCtor (myCpu, data_read);
    StackCtor  (&(myCpu -> myStack));
    StackCtor  (&(myCpu -> myStackReturns));
    myCpu -> file_write = myCpu -> myStack.file_write;
    MemoryCtor (myCpu);
    return 1;
}

int CpuDtor(Cpu_t* myCpu)
{
    MYASSERT(myCpu, BAD_POINTER_PASSED_IN_FUNC, return 0)

    BufferDtor (myCpu);
    StackDtor  (&(myCpu -> myStack));
    StackDtor  (&(myCpu -> myStackReturns));
    MemoryDtor (myCpu);
    return 1;
}

int PrintMemoryListing (Cpu_t* myCpu)
{
    MYASSERT(myCpu, BAD_POINTER_PASSED_IN_FUNC, return 0)
    
    size_t n_element = 0;
    fprintf (myCpu -> file_write, "\nMEMORY: [");
    while (n_element < MEMORY_LENGTH)
    {
        fprintf (myCpu -> file_write, "|%d|", myCpu -> myMemory[n_element]);
        if (myCpu -> myMemory[n_element] == POISON_ELEMENT)
        {
            break;
        }
        n_element++;
    }
    fprintf (myCpu -> file_write, "]\n");
    fprintf (myCpu -> file_write, DIVIDER);
    return 1;
}