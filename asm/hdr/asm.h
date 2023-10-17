#ifndef ASM_H
#define ASM_H
     
int    write_command   (char* command, char* reg, Elem_t value, BufferAsm_t* asmCode);
int    compare         (double x, double y);
int    get_reg_id      (char* reg_str);
int    txt_to_asm      (BufferAsm_t *asmCode);

#endif