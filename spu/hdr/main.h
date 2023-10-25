#ifndef MAIN_H
#define MAIN_H

#define ASSERT_MYSTACK 1
#define DEBUG_PRINTING 0

#if (ASSERT_MYSTACK != 0)
#define ASSERT_STACK(stk, func)                             \
        if (checkStack(stk, func) != 0)                     \
        {                                                   \
            STACK_DUMP (stk, checkStack(stk, func))         \
        }                                                   
#define STACK_DUMP(stk, error_code) output_error(stk, __FILE__, __LINE__, __PRETTY_FUNCTION__, error_code);
#else   
#define ASSERT_STACK(stk, func)                   
#define STACK_DUMP(stk, error_code)        
#endif

#if (DEBUG_PRINTING != 0)
#define ON_PRINTING(...) __VA_ARGS__
#else
#define ON_PRINTING(...) 
#endif

typedef struct Stack {
    Elem_t*  data;
    int      size;
    int      capacity; 
    int      ret_value;

    FILE*    file_in;
    FILE*    file_out;
} Stack_t;

typedef struct BufferSpu {
    FILE*    file_in;
    FILE*    file_out;

    size_t   size_text;
    Elem_t*  text_buffer;
} BufferSpu_t;

typedef struct Spu {
    Stack_t     myStack;
    BufferSpu_t myBuffer;

    Elem_t*     actual_command;

    Elem_t      rax;
    Elem_t      rbx; 
    Elem_t      rcx;
    Elem_t      rdx; 
} Spu_t;

const int N_ERRORS = 8;
const int MULTIPLIER = 2;
const int MIN_LEN = 5;

enum return_of_command {
    IF_HLT     = 0,
    IF_LABEL   = 1,
    IF_COMMAND = 2,
};

#endif 