#include <stdio.h>

#include "arrays.h"
#include "type.h"
#include "main_asm.h"
#include "buffer.h"
#include "asm.h"

int main()
{ 
    Asm_t myAsm = {};
    
    AsmCtor         (&myAsm);
    arrOfptr        (&myAsm);

    Assembling      (&myAsm, 1);
    Assembling      (&myAsm, 2);

	WriteBufToFile  (&myAsm);
    AsmDtor         (&myAsm);

    printf("\n>>>ASM WELL DONE!!! CHECK LISTING.TXT AND INPUT_BIN.TXT!!!<<<\n");
    return 0;
}