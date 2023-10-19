#ifndef ASM_H
#define ASM_H
     
int     WriteCommandToBuf           (CMDLine_t* myCMDline, Asm_t *myAsm);
int     WriteBufToFile              (Asm_t *myAsm);
int     AssemblingFirst             (Asm_t *myAsm);
int     AssemblingSecond            (Asm_t *myAsm);
int     CompleteStructWithCMD       (size_t amount_args, char* arg, CMDLine_t* myCMDline);
int     CompleteStructWithLabel     (char* arg, CMDLine_t* myCMDline, Asm_t* myAsm);
int     ProcessCMD                  (char* str, CMDLine_t* myCMDline, Asm_t* myAsm);
int     ProcessLabel                (char* str, CMDLine_t* myCMDline, Asm_t* myAsm);
int     FillLabels                  (CMDLine_t* myCMDline, Asm_t* myAsm);
int     SearchingLabel              (CMDLine_t* myCMDline, Asm_t *myAsm);

#endif