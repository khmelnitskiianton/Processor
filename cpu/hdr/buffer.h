#ifndef BUFFER_H
#define BUFFER_H

int     BufferCtor      (Cpu_t *myCpu);
int     BufferDtor      (Cpu_t *myCpu);
int     MemoryCtor      (Cpu_t *myCpu);
int     MemoryDtor      (Cpu_t *myCpu);
size_t  text_size       (FILE *file_text);
FILE*   file_open_read  (void);

#endif