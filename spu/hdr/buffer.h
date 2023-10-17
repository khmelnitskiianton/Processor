#ifndef BUFFER_H
#define BUFFER_H

int    bufferCtor      (Spu_t *mySpu);
int    bufferDtor      (Spu_t *mySpu);
size_t text_size       (FILE *file_text);
FILE*  file_open_read  (void);
FILE*  file_open_write (void);
int    file_close      (FILE* file_text);

#endif