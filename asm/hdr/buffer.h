#ifndef BUFFER_H
#define BUFFER_H

FILE*  file_open_read  (void);
FILE*  file_open_write (void);
int    file_close      (FILE* file_text);
size_t text_size       (FILE *file_text);
int    bufferCtor      (BufferAsm_t *asmCode);
int    bufferDtor      (BufferAsm_t *asmCode);
int    arrOfptr        (BufferAsm_t *asmCode);

#endif