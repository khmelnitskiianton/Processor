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

Elem_t* expansion (Stack_t *stk)
{
    void* new_place = nullptr;
    (stk -> capacity) = (stk -> capacity) * MULTIPLIER;                                                                                      
    if ((new_place = realloc ((stk -> data), sizeof(Elem_t)*(stk -> capacity))) == nullptr)
    {   
        fprintf(stdout,            "ERROR IN RECALLOC IN %s", __PRETTY_FUNCTION__);
        fprintf(stk -> file_out,   "ERROR IN RECALLOC IN %s", __PRETTY_FUNCTION__);  
        abort();
    }
                                                 
    mem_poison (new_place + sizeof(Elem_t)*(stk -> size), (stk -> capacity)-(stk -> size));                        

    return (Elem_t*) new_place;
}

Elem_t* comprassion (Stack_t *stk)
{
    void* new_place = nullptr;
    (stk -> capacity) = (stk -> capacity) / MULTIPLIER;
    if ((new_place = realloc ((stk -> data), sizeof(Elem_t)*(stk -> capacity))) == nullptr)
    {
        fprintf(stdout,            "ERROR IN RECALLOC IN %s", __PRETTY_FUNCTION__);
        fprintf(stk -> file_out, "ERROR IN RECALLOC IN %s", __PRETTY_FUNCTION__);  
        abort();
    }                      
    return (Elem_t*) new_place;
}

int mem_poison (void* memptr, size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        *(((Elem_t*) memptr) + i) = POISON_ELEMENT;
    }
    return 1;
}

int checkStack (Stack_t *stk, const char* func)
{
    int error_code = 0;
    
    if (!stk)                    
    {
        error_code |= 1<<0;
        return error_code;
    }
    if (!(stk -> file_out))                    
    {
        error_code |= 1<<1;
        return error_code;
    }

    if (!(stk -> data))
    {
        error_code |= 1<<2;
        return error_code;
    }

    if ((strcmp(func, "int pop(Stack_t*, Elem_t*)") == 0)&&(!(stk -> ret_value)))
    {
        error_code |= 1<<3;
        return error_code;
    }
    if ((stk -> capacity) <= 0)             
    {
        error_code |= 1<<4;
        return error_code;
    }
        if ((stk -> size) < 0)                  
    {
        error_code |= 1<<5;
        return error_code;
    }
    if ((stk -> size) > (stk -> capacity))  
    {
        error_code |= 1<<6;
        return error_code;
    }
    if ((strcmp(func, "int pop(Stack_t*, Elem_t*)") == 0)&&((stk -> size) == 0)) 
    {
        error_code |= 1<<7;
        return error_code;
    }
    return error_code;
}

int output_error (Stack_t *stk, const char* file, const size_t line, const char* pretty_function, int error_code)
{   
    const char* mass_of_errors[N_ERRORS] = {
        "ADDRESS OF STRUCTURE == NULL. OUTPUT IN TERMINAL",
        "ADDRESS OF file_out == NULL",
        "ADDRESS OF ARRAY IN STRUCTURE == NULL",
        "ADDRESS OF RETURNING ARGUMENT IN POP == NULL",
        "CAPACITY <= 0",
        "SIZE < 0",
        "SIZE > CAPACITY",
        "POP() BUT DATA EMPTY"
    };
    int z = error_code;
    unsigned long bin_error = 0;
    size_t element = 0;
    int fatal_error = 0;
    printf("<<<<<!!!!YOU HAVE ERROR.CHECK OUTPUT.TXT OR TERMINAL!!!!>>>>>>>\n");
    if (z == 1)
    {
        printf("\n<<<<<<<<<<<<<<<YOU HAVE ERROR>>>>>>>>>>>>>>>>>\n"
            "Stack[%p] called from %s (string: %lld) in function %s\n"
            "1: [%s]\n", stk, file, line, pretty_function,mass_of_errors[0]);
        abort();
    }
    if (z == 2)
    {
        printf("\n<<<<<<<<<<<<<<<YOU HAVE ERROR>>>>>>>>>>>>>>>>>\n"
            "Stack[%p] called from %s (string: %lld) in function %s\n"
            "0: [OK]\n"
            "1: [%s]\n", stk, file, line, pretty_function,mass_of_errors[1]);
        abort();
    }

    fprintf(stk -> file_out, "\n<<<<<<<<<<<<<<<YOU HAVE ERROR>>>>>>>>>>>>>>>>>\n");
    fprintf(stk -> file_out, "\nERROR:\n");

    while (z > 0)
    {
        if (z % 2)
        {
            bin_error += 1<<(element);
            fprintf(stk -> file_out, "1: [%s]\n", mass_of_errors[element]);
            if(element != 15) fatal_error = 1;
        }
        else
        {
            fprintf(stk -> file_out, "0: [OK]\n");
        }
        z = z / 2;
        element++;
    }
    fprintf(stk -> file_out,"ERROR CODE: [%lu]\n\n", bin_error);
    
    if (!fatal_error)
    {
    fprintf (stk -> file_out,"Stack[%p] called from %s (string: %lld) in function %s\n"
    //      "\t\t%s             \n"
            "{                  \n"
            "\tsize        = %d \n"
            "\tcapacity    = %d \n"
            "\tdata[%p]         \n"
            "\t{                \n", stk, file, line, pretty_function, stk -> size, stk -> capacity, stk -> data);

    for (ssize_t i = 0; (i < (stk -> capacity)); i++)
    {
        if (i == stk -> size)                                    fprintf(stk -> file_out,"\t >[%lld] = " SPECIFIER "<\n", i, *((stk -> data) + i));
        else if (!compare(*((stk -> data) + i), POISON_ELEMENT)) fprintf(stk -> file_out,"\t #[%lld] = " SPECIFIER "\n", i, *((stk -> data) + i));
        else                                                     fprintf(stk -> file_out,"\t @[%lld] = " SPECIFIER "(POISON)\n", i, *((stk -> data) + i));
    }
    
    fprintf (stk -> file_out,"\t} \n"
            "}   \n");
    }
    file_close(stk -> file_out);
    abort();
    return 1;
}

int degree(int a, int b)
{
    int x = 1;
    for (int i = 0; i < b; i++)
    {
        x = x * a;
    }
    return x;
}

int SpuCtor(Spu_t* mySpu)
{
    BufferCtor (mySpu);
    StackCtor  (&(mySpu -> myStack), &(mySpu -> myBuffer));
    return 1;
}

int SpuDtor(Spu_t* mySpu)
{
    BufferDtor (mySpu);
    StackDtor  (&(mySpu -> myStack));
    return 1;
}