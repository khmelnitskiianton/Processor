#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "arrays.h"
#include "type.h"
#include "stack_main.h"
#include "main_cpu.h"
#include "buffer.h"
#include "support.h"
#include "calc.h"

int main(void)
{
    Cpu_t myCpu = {};

    CpuCtor     (&myCpu);

    process_asm (&myCpu);

    CpuDtor     (&myCpu);

    printf("\n>>>CPU WELL DONE!!! CHECK LOG.TXT!!!<<<\n\n");
    return 0;
}