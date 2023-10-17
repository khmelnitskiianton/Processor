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

int main(void)
{
    Spu_t mySpu = {};

    bufferCtor (&(mySpu));
    StackCtor  (&(mySpu.myStack), &(mySpu.myBuffer));

    process_asm (&(mySpu));

    printf("\n>>>WELL DONE!!! CHECK OUTPUT.TXT!!!<<<\n");

    bufferDtor (&(mySpu));
    StackDtor  (&(mySpu.myStack));
    return 0;
}