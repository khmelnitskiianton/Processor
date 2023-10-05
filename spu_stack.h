#ifndef STACK_H
#define STACK_H

int     StackCtor      (Stack_t* stk);
int     StackDtor      (Stack_t* stk);
int     push           (Stack_t* stk, Elem_t value);
int     pop            (Stack_t* stk, Elem_t* ret_value);
int     printing_stack (Stack_t* stk, const char* file, const size_t line, const char* pretty_function);

#endif