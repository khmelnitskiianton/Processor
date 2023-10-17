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

int main(void)
{ 
    BufferAsm_t asmCode = {};
    bufferCtor (&asmCode);

    arrOfptr   (&asmCode);
    txt_to_asm (&asmCode);

    bufferDtor (&asmCode);
    
    return 0;
}