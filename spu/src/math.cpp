#include <stdio.h>
#include <assert.h>
#include <limits.h> 
#include <string.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>

#include "main.h"
#include "calc.h"
#include "stack.h"
#include "support.h"

int do_command(Stack_t* stk, int command, Elem_t argument)
{
    switch(command)
    {
        case HLT:
            return 1;
        break;

        case OUT:
            print_result(stk);
        break;

        case PUSH:
            push(stk, argument);
        break;
        
        case IN:
            in (stk);
        break;

        case SUB:
            sub (stk);
        break;

        case DIV:
            div (stk);
        break;

        case ADD:
            add (stk);
        break;

        case MUL:
            mul (stk);
        break;

        case SQRT:
            sqrt_stk (stk);
        break;

        case SIN:
            sin_stk (stk);
        break;

        case COS:
            cos_stk (stk);
        break;

        default: 
        fprintf(stdout,          "\n<<<<<<<!YOU HAVE ERROR!>>>>>>\n<<<<<<!UNKNOWN CODE!>>>>>>");
        fprintf(stk -> file_out, "\n<<<<<<<!YOU HAVE ERROR!>>>>>>\n<<<<<<!UNKNOWN CODE!>>>>>>");
        abort();
        break;
    }       
    return 0;
}

int print_result (Stack_t* stk)
{
    Elem_t result = POISON_ELEMENT;
    pop (stk, &result);
    fprintf (stk -> file_out, SPECIFIER, result);
    return 1;
}

int in (Stack_t* stk)
{
    Elem_t num = POISON_ELEMENT;
    printf("Enter value please to put in stack: ");
    while(scanf (SPECIFIER, &num) != 1)
    {   
        clean_buffer ();
        printf ("\nWtf? Its not normal double number. Maybe it is infinite/NAN number or letters. Another attempt you piece of shit, hey you, MAAAAN!\n");
    }
    push (stk, num);
    return 1;
}

int sub (Stack_t* stk)
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(stk, &y);
    pop(stk, &x);
    push(stk, x - y);
    return 1;
}

int add (Stack_t* stk)
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(stk, &y);
    pop(stk, &x);
    push(stk, x + y);
    return 1;
}

int div (Stack_t* stk)
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(stk, &y);
    pop(stk, &x);
    push(stk, x / y);
    return 1;
}

int mul (Stack_t* stk)
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(stk, &y);
    pop(stk, &x);
    push(stk, x * y);
    return 1;
}

int sqrt_stk (Stack_t* stk)
{
    Elem_t x = POISON_ELEMENT;
    pop(stk, &x);
    if (x >= 0)
    push(stk, sqrt(x));
    return 1;
}

int sin_stk (Stack_t* stk)
{
    Elem_t x = POISON_ELEMENT;
    pop(stk, &x);
    push(stk, sin(x));
    return 1;
}

int cos_stk (Stack_t* stk)
{
    Elem_t x = POISON_ELEMENT;
    pop(stk, &x);
    push(stk, cos(x));
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