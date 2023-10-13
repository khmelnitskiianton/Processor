#ifndef ASM_H
#define ASM_H
  
FILE*  file_open_read  (void);
FILE*  file_open_write (void);
int    file_close      (FILE* file_text);
int    clean_str       (char* command);
size_t text_size       (FILE *file_text);
int    bufferCtor      (Buffer_t *asmCode);
int    arrOfptr        (Buffer_t *asmCode);
int    bufferDtor      (Buffer_t *asmCode);
int    write_command   (char* command, char* reg, Elem_t value, Buffer_t* asmCode);
int    compare         (double x, double y);
int    get_reg_id      (char* reg_str);
int    txt_to_asm      (Buffer_t *asmCode);

#endif