#ifndef STACK_SUPPORT_H
#define STACK_SUPPORT_H

Elem_t*     expansion           (Stack_t *stk);
Elem_t*     comprassion         (Stack_t *stk);
int         mem_poison          (void* memptr, int num);
int         checkStack          (Stack_t *stk, const char* func);
int         output_error        (Stack_t *stk, const char* file, const size_t line, const char* pretty_function, int error_code);
int         printing_stack      (Stack* stk, const char* file, const size_t line, const char* pretty_function);
int         degree              (int a, int b);   
Hash_t      hash_func           (const char * str, size_t size);
Hash_t      MYHashFAQ6          (const char * str, size_t size);
size_t      size_data           (Stack* stk);
FILE*       file_write          (void);
int         file_close          (FILE *file_text);

#endif