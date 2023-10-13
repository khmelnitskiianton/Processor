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

typedef int Elem_t;
#define SPECIFIER "%d"

typedef struct Stack {
    Elem_t    *data;
    int       size;
    int       capacity; 

    int       ret_value;
    FILE*     file_in;
    FILE*     file_out;

} Stack_t;

const Elem_t POISON_ELEMENT = NULL;
const int    N_ERRORS = 8;
const int    MULTIPLIER = 2;
const int    MIN_LEN = 10;

#define EPSILONE 1e-10


#define FILE_IN  "D:/Study/C/Processor/input_bin.txt"
#define FILE_OUT "D:/Study/C/Processor/output.txt"

#endif 