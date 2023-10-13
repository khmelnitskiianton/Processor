#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "commands.h"
#include "main.h"
#include "asm.h"

int main(void)
{ 
    Buffer_t asmCode = {};
    bufferCtor (&asmCode);

    arrOfptr   (&asmCode);
    txt_to_asm (&asmCode);

    bufferDtor (&asmCode);
    return 0;
}