#include <stdio.h>

#include "arrays.h"
#include "type.h"
#include "main.h"
#include "buffer.h"
#include "asm.h"

int main(void)
{ 
    Asm_t myAsm = {};
    
    AsmCtor         (&myAsm);
    arrOfptr        (&myAsm);

    Assembling      (&myAsm, 1);
    Assembling      (&myAsm, 2);

	WriteBufToFile  (&myAsm);
    AsmDtor         (&myAsm);

    printf("\n>>>WELL DONE!!! CHECK OUTPUT.TXT!!!<<<\n");
    return 0;
}