#ifndef ASM_H
#define ASM_H

int     WriteCommandToBuf           (CMDLine_t* myCMDline, Asm_t *myAsm);
int     WriteBufToFile              (Asm_t *myAsm);
int     Assembling                  (Asm_t *myAsm, int n_run);
int     CompleteStructWithCMD       (Parsing_t myActualWord, CMDLine_t* myCMDline);
int     CompleteStructWithLabel     (char* arg, CMDLine_t* myCMDline, Asm_t* myAsm);
int     ProcessCMD                  (char* str, CMDLine_t* myCMDline, Asm_t* myAsm);
int     ProcessLabel                (char* str, CMDLine_t* myCMDline, Asm_t* myAsm);
int     FillLabels                  (CMDLine_t* myCMDline, Asm_t* myAsm);
int     SearchingLabel              (CMDLine_t* myCMDline, Asm_t *myAsm);
int     ScanWithoutBrackets         (Parsing_t myActualWord, CMDLine_t* myCMDline);
int     ScanWithBrackets            (Parsing_t myActualWord, CMDLine_t* myCMDline);

#endif