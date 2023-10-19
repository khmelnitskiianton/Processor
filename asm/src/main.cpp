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
    Asm_t myAsm = {};
    
    AsmCtor    (&myAsm);
    arrOfptr   (&myAsm);

    AssemblingFirst  (&myAsm);
    AssemblingSecond (&myAsm);

    AsmDtor    (&myAsm);
    return 0;
}