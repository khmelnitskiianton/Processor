#ifndef ASM_H
#define ASM_H

FILE* file_read_asm   (void);
FILE* file_write_asm  (void);
int   file_close_asm  (FILE* file_text);
int   compare_command (char command[], FILE* file_write);
int   clean_str       (char* command);

#endif