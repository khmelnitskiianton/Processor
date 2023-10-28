#ifndef CALC_H
#define CALC_H

int process_asm     (Cpu_t *myCpu);
int do_command      (Cpu_t* myCpu);
int clean_buffer    (void);
int GetArg          (Cpu_t* myCpu, int command, ArgCMD_t* myArgCMD);

#endif
