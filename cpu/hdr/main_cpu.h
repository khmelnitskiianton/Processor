#ifndef MAIN_SPU_H
#define MAIN_SPU_H

#include <SDL2/SDL.h>

typedef struct BufferCpu {
    FILE*    file_in;
    size_t   size_text;
    Elem_t*  text_buffer;
} BufferCpu_t;

typedef struct ArgCMD {
    int     reg;
    Elem_t  value;
    Elem_t  result;
} ArgCMD_t;

typedef struct Cpu {
    Stack_t         myStack;
    Stack_t         myStackReturns;
    BufferCpu_t     myBuffer;
    Elem_t          myMemory[MEMORY_LENGTH];

    FILE*           file_write;   
    SDL_Renderer    *renderer = NULL;
    SDL_Window      *window   = NULL;

    Elem_t*         actual_command;

    Elem_t          myRegs[AMOUNT_OF_REGISTERS];
} Cpu_t;

#endif 