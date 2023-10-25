#ifndef CALC_H
#define CALC_H

int process_asm  (Spu_t *mySpu);
int do_command   (Spu_t* mySpu, int command);
int print_result (Spu_t* mySpu);
int push_num     (Spu_t *mySpu);
int push_reg     (Spu_t *mySpu);
int pop_reg      (Spu_t *mySpu);
int in           (Spu_t* mySpu);
int sub          (Spu_t* mySpu);
int add          (Spu_t* mySpu);
int div          (Spu_t* mySpu);
int mul          (Spu_t* mySpu);
int mysqrt       (Spu_t* mySpu);
int mysin        (Spu_t* mySpu);
int mycos        (Spu_t* mySpu);
int clean_buffer (void);

#endif
