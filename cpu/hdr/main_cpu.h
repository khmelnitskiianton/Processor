#ifndef MAIN_SPU_H
#define MAIN_SPU_H

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
    Stack_t     myStack;
    Stack_t     myStackReturns;
    BufferCpu_t myBuffer;
    Elem_t      myMemory[MEMORY_LENGTH];

    FILE*       file_write;   

    Elem_t*     actual_command;

    Elem_t      rax;
    Elem_t      rbx; 
    Elem_t      rcx;
    Elem_t      rdx; 
} Cpu_t;

#endif 