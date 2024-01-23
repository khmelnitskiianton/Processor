#ifndef BUFFER_H
#define BUFFER_H

int         BufferCtor      (Cpu_t *myCpu, const char* data_read);
int         BufferDtor      (Cpu_t *myCpu);
int         MemoryCtor      (Cpu_t *myCpu);
int         MemoryDtor      (Cpu_t *myCpu);
size_t      text_size       (FILE *file_text);
FILE*       file_open_read  (const char* data_read);

#endif