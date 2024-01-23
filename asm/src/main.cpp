#include <stdio.h>
#include <stdlib.h>

#include "arrays.h"
#include "type.h"
#include "main_asm.h"
#include "myassert.h"
#include "buffer.h"
#include "asm.h"

int main(int argc, char *argv[])
{ 
    USER_ERROR(argc == 3, ASM_NO_FILE_PASSED_IN_PROGRAM, exit(0))
    printf("\n<<<ASM: FILE TO IN:  %s>>>\n", argv[1]);
    printf(  "<<<ASM: FILE TO OUT: %s>>>\n", argv[2]);

    Asm_t myAsm = {};

    AsmCtor         (&myAsm, argv[1], argv[2]);
    arrOfptr        (&myAsm);

    Assembling      (&myAsm, 1);
    Assembling      (&myAsm, 2);

	WriteBufToFile  (&myAsm);
    AsmDtor         (&myAsm);

    printf("\n>>>ASM WELL DONE!!! CHECK LISTING.TXT AND INPUT_BIN.TXT!!!<<<\n");
    return 0;
}