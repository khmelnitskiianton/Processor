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

int process_asm (Spu_t *mySpu)
{
    int checkOk = 1;
    while (checkOk)
    {
        if (do_command (mySpu, (int) *(mySpu -> actual_command))) 
        {
            break;
        }
        else (mySpu -> actual_command)++;
    ON_PRINTING(
        printing_stack (&(mySpu -> myStack), __FILE__, __LINE__, __PRETTY_FUNCTION__);
    )
    }
    return 1;
}

int do_command (Spu_t* mySpu, int command)
{
    switch(command)
    {
        #define DEF_CMD(name, name_full, num, bin_num, ...)             \
            case COMMANDS[name_full].bin_code: __VA_ARGS__ break; 
            
        #include "commands.h"

        #undef DEF_CMD       
        
        default: 
        {
            fprintf(stdout, "\n<<<<<<<!YOU HAVE ERROR!>>>>>>\n<<<<<<!UNKNOWN CODE!>>>>>>\n");
            fprintf(mySpu -> myBuffer.file_out, "\n<<<<<<<!YOU HAVE ERROR!>>>>>>\n<<<<<<!UNKNOWN CODE!>>>>>>");
            file_close(mySpu -> myBuffer.file_out);
            abort(); 
        }
        break;
    }       
    return 0;
}

int print_result (Spu_t* mySpu)
{
    Elem_t result = POISON_ELEMENT;
    pop (&(mySpu -> myStack), &result);

    if ((mySpu -> myStack.size) > 0) printf("\n\n>>>WARNING<<<\nYour Stack is not empty now!!!\n\n"); 
ON_DOUBLE(
    fprintf (mySpu -> myBuffer.file_out, "%lf", result);
)
ON_INT(
    fprintf (mySpu -> myBuffer.file_out, "%lf", ((double) result) / N_DIGIT);
)
    return 1;
}

int push_num (Spu_t *mySpu)
{
    Elem_t value = *(++(mySpu -> actual_command));
    if (!COMPARE_TYPE(value, POISON_ELEMENT)) push (&(mySpu -> myStack), value);
    else printf("\n\n>>>WARNING<<<\nVALUE == NULL!!!\n\n");
    return 1;
}

int push_reg (Spu_t *mySpu)
{
    int n_reg = (int) *(++(mySpu -> actual_command));
    if (n_reg != NULL) 
    {
        switch (n_reg)
        {
            case 1:         push(&(mySpu -> myStack), mySpu -> rax);            break; 
            case 2:         push(&(mySpu -> myStack), mySpu -> rbx);            break;
            case 3:         push(&(mySpu -> myStack), mySpu -> rcx);            break;
            case 4:         push(&(mySpu -> myStack), mySpu -> rdx);            break;
        }
    }
    else printf("\n\n>>>WARNING<<<\nREG NUMBER == NULL!!!\n\n");
    return 1;
}

int pop_reg (Spu_t *mySpu)
{
    int n_reg = (int) *(++(mySpu -> actual_command));
    if (n_reg != NULL) 
    {
        switch (n_reg)
        {
            case 1:         pop(&(mySpu -> myStack), &(mySpu -> rax));          break;
            case 2:         pop(&(mySpu -> myStack), &(mySpu -> rbx));          break;
            case 3:         pop(&(mySpu -> myStack), &(mySpu -> rcx));          break;
            case 4:         pop(&(mySpu -> myStack), &(mySpu -> rdx));          break;
        }
    }
    else printf("\n\n>>>WARNING<<<\nREG NUMBER == NULL!!!\n\n");
    return 1;
}

int in (Spu_t* mySpu)
{
    double num = POISON_ELEMENT;
    printf("Enter value please to put in stack: ");
    while(scanf ("%lf", &num) != 1)
    {   
        clean_buffer ();
        printf ("\nWtf? Its not normal double number. Maybe it is infinite/NAN number or letters. Another attempt you piece of shit, hey you, MAAAAN!\n");
    }
ON_DOUBLE(
    push (&(mySpu -> myStack), num);
)
ON_INT(
    push (&(mySpu -> myStack), (int) (num * N_DIGIT));
)
    return 1;
}

int sub (Spu_t* mySpu)
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &y);
    pop(&(mySpu -> myStack), &x);
    push(&(mySpu -> myStack), x - y);
    return 1;
}

int add (Spu_t* mySpu)
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &y);
    pop(&(mySpu -> myStack), &x);
    push(&(mySpu -> myStack), x + y);
    return 1;
}

int div (Spu_t* mySpu)
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &y);
    pop(&(mySpu -> myStack), &x);
ON_DOUBLE(
    push(&(mySpu -> myStack), x / y);
)
ON_INT(
    push(&(mySpu -> myStack), (x * N_DIGIT) / y);
)
    return 1;
}

int mul (Spu_t* mySpu)
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &y);
    pop(&(mySpu -> myStack), &x);
ON_DOUBLE(
    push(&(mySpu -> myStack), x * y);
)
ON_INT(
    push(&(mySpu -> myStack), x * y / N_DIGIT);
)
    return 1;
}

int mysqrt (Spu_t* mySpu)
{
    Elem_t x = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &x);
ON_DOUBLE(
    if (x >= 0) push(&(mySpu -> myStack), sqrt(x));
)
ON_INT(
    double z =  sqrt(((double) x) / N_DIGIT);
    if (x >= 0) push(&(mySpu -> myStack), (int) (z * N_DIGIT));
)
    return 1;
}

int mysin (Spu_t* mySpu)
{
    Elem_t x = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &x);
ON_DOUBLE(
    push(&(mySpu -> myStack), sin(x));
)
ON_INT(
    double z =  sin(((double) x) / N_DIGIT);
    push(&(mySpu -> myStack), (int) (z * N_DIGIT));
)
    return 1;
}

int mycos (Spu_t* mySpu)
{
    Elem_t x = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &x);
ON_DOUBLE(
    push(&(mySpu -> myStack), cos(x));
)
ON_INT(
    double z =  cos(((double) x) / N_DIGIT);
    push(&(mySpu -> myStack), (int) (z * N_DIGIT));
)
    return 1;
}

int clean_buffer (void)
{
    int ch = 0;                     
    while ((ch = getchar ()) != '\n') {}   
    return 1;
}

int compare (double x, double y)
{
    if (((isnan (x) == 1) && (isnan (y) == 1)) || (fabs (x - y) < EPSILONE))
        return 1;
    else
        return 0;
}
