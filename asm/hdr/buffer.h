#ifndef BUFFER_H
#define BUFFER_H

FILE*   file_open_read      (const char* data_read);
FILE*   file_open_write     (const char* data_write);
FILE*   file_open_listing   (void);
int     file_close          (FILE* file_text);
size_t  text_size           (FILE *file_text);
int     BufferTextCtor      (Asm_t *myAsm, const char* data_read, const char* data_write);
int     BufferTextDtor      (Asm_t *myAsm);
int     arrOfptr            (Asm_t *myAsm);
int     BufferBinCtor       (Asm_t *myAsm);
int     BufferBinDtor       (Asm_t *myAsm);
int     AsmCtor             (Asm_t *myAsm, const char* data_read, const char* data_write);
int     AsmDtor             (Asm_t *myAsm);

#endif