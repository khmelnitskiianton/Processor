#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h> 
#include <string.h>
#include <stddef.h>
#include <math.h>

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

typedef double Elem_t;
#define SPECIFIER "%lf"

typedef struct Stack {
    Elem_t    *data;
    int       size;
    int       capacity; 

    int       ret_value;
    FILE*     file_in;
    FILE*     file_out;

} Stack_t;

const Elem_t POISON_ELEMENT = NAN;
const int    N_ERRORS = 8;
const int    MULTIPLIER = 2;
const int    MIN_LEN = 10;

#define EPSILONE 1e-10

#include "spu_math.h"
#include "spu_stack.h"
#include "spu_support.h"
#include "asm.h"

#define FILE_IN_TEXT "input_text.txt"
#define FILE_IN_NUM  "input_num.txt"
#define FILE_OUT     "output.txt"

enum math_codes {
    HLT  = -1,
    OUT  = 0,
    PUSH = 1,
    IN   = 2,
    SUB  = 3,
    DIV  = 4,
    ADD  = 5,
    MUL  = 6,
    SQRT = 7,
    SIN  = 8,
    COS  = 9,
};

#endif 