#ifndef ASM_H
#define ASM_H
  
FILE* file_open_read  (void);
FILE* file_open_write (void);
int   file_close      (FILE* file_text);
int   compare_command (char command[], FILE* file_write);
int   clean_str       (char* command);

#endif