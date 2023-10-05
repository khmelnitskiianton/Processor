#include "head.h"

int StackCtor (Stack_t *stk)
{
    stk -> file_in  = file_rb_open ();
	stk -> file_out = file_wb_open ();
    stk -> size = 0; 
    stk -> capacity = 1;
    stk -> ret_value = 1;

    if ((stk -> data = (Elem_t*) calloc (1, sizeof(Elem_t)*(stk -> capacity))) == nullptr)
    {   
        fprintf(stdout,            "ERROR IN INITIALIZATION OF CALLOC");
        fprintf(stk -> file_out, "ERROR IN INITIALIZATION OF CALLOC");  
        abort();
    }

    ASSERT_STACK(stk, __PRETTY_FUNCTION__)
    return 1;
}

int push (Stack_t *stk, Elem_t value)
{ 
    ASSERT_STACK(stk, __PRETTY_FUNCTION__)

    if ((stk -> size) == (stk -> capacity))
    {
        (stk -> data) = expansion (stk);
    }

    *((stk -> data) + (stk -> size)) = value;
    (stk -> size)++; 

    ASSERT_STACK(stk, __PRETTY_FUNCTION__)

    return 1;
}

int pop (Stack_t *stk, Elem_t* ret_value)
{
    if (!stk) 
    {
        ASSERT_STACK(stk, __PRETTY_FUNCTION__)
    }
    else if (ret_value == NULL) 
    {
        stk -> ret_value = 0;
        ASSERT_STACK(stk, __PRETTY_FUNCTION__)
    }
    else 
    {
        stk -> ret_value = 1;
        ASSERT_STACK(stk, __PRETTY_FUNCTION__)
    }

    Elem_t save_value = POISON_ELEMENT;
    (stk -> size)--;
    save_value = *((stk -> data) + (stk -> size));  
    if (((stk -> size) > 0) && ((stk -> size)*MULTIPLIER < (stk -> capacity)) && ((stk -> capacity) > MIN_LEN))
    {
        (stk -> data) = comprassion (stk);
    }
    *((stk -> data) + (stk -> size)) = POISON_ELEMENT;
    *ret_value = save_value;

    return 1;
}

int StackDtor (Stack_t *stk)
{
    ASSERT_STACK(stk, __PRETTY_FUNCTION__)

    free(stk -> data);
    file_close(stk -> file_in);
    file_close(stk -> file_out);
    stk -> data = NULL;
    stk = NULL;
    return 1;
}

int printing_stack (Stack_t* stk, const char* file, const size_t line, const char* pretty_function)
{
    fprintf (stk -> file_out,"\nStack[%p] called from %s (string: %lld) in function %s\n"
            "{                  \n"
            "\tsize        = %d \n"
            "\tcapacity    = %d \n"
            "\tdata[%p]         \n"
            "\t{                \n", stk, file, line, pretty_function, stk -> size, stk -> capacity, stk -> data);

    for (ssize_t i = 0; (i < (stk -> capacity)); i++)
    {
        if (i == (stk -> size))                                  fprintf(stk -> file_out,"\t >[%lld] = " SPECIFIER "<\n", i, *((stk -> data) + i));
        else if (!compare(*((stk -> data) + i), POISON_ELEMENT)) fprintf(stk -> file_out,"\t #[%lld] = " SPECIFIER "\n", i, *((stk -> data) + i));
        else                                                     fprintf(stk -> file_out,"\t @[%lld] = " SPECIFIER "(POISON)\n", i, *((stk -> data) + i));
    }
    
    fprintf (stk -> file_out,"\t} \n"
            "}   \n");
    return 1;
}

