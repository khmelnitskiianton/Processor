#ifndef MATH_H
#define MATH_H

int do_command   (Stack_t* stk, int command, Elem_t argument);
int print_result (Stack_t* stk);
int in           (Stack_t* stk);
int sub          (Stack_t* stk);
int add          (Stack_t* stk);
int div          (Stack_t* stk);
int mul          (Stack_t* stk);
int sqrt_stk     (Stack_t* stk);
int sin_stk      (Stack_t* stk);
int cos_stk      (Stack_t* stk);
int clean_buffer (void);
int compare      (double x, double y);

#endif
