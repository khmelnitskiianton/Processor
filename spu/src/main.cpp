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

    SpuCtor     (&mySpu);

    process_asm (&(mySpu));

    SpuDtor     (&mySpu);

    printf("\n>>>WELL DONE!!! CHECK OUTPUT.TXT!!!<<<\n");
    return 0;
}