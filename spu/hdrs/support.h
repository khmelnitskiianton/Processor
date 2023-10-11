#ifndef SUPPORT_H
#define SUPPORT_H

Elem_t* expansion      (Stack_t *stk);
Elem_t* comprassion    (Stack_t *stk);
int     checkStack     (Stack_t *stk, const char* func);
int     output_error   (Stack_t *stk, const char* file, const size_t line, const char* pretty_function, int error_code);
int     mem_poison     (void* memptr, size_t num);
int     degree         (int a, int b);
FILE*   file_rb_open   (void);
FILE*   file_wb_open   (void);
int     file_close     (FILE *file_text);

#endif 