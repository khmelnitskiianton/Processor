#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>

#include "arrays.h"
#include "type.h"
#include "stack_main.h"
#include "main_cpu.h"
#include "buffer.h"
#include "myassert.h"
#include "support.h"
#include "calc.h"

int main(int argc, char *argv[])
{
    USER_ERROR(argc == 2, CPU_NO_FILE_PASSED_IN_PROGRAM, exit(0))
    printf("\n<<<CPU: FILE TO IN/OUT: %s>>>\n", argv[1]);

    Cpu_t myCpu = {};

    CpuCtor(&myCpu, argv[1]);

    process_asm (&myCpu);

    CpuDtor     (&myCpu);

    printf("\n>>>CPU WELL DONE!!! CHECK LOG.TXT!!!<<<\n\n");
    return 0;
}