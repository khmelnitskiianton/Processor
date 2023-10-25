#ifndef SUPPORT_H
#define SUPPORT_H

int     get_reg_id              (char* reg_str);
int     isReg                   (char* arg);
int     isCommand               (char* arg);
int     isCMDLabel              (char* arg);
int     isLabel                 (char* arg);
int     isValue                 (char* arg);
int     RecoverAll              (Asm_t* myAsm);
int     RecoverTextBuffer       (Asm_t* myAsm);
int     InitLine                (CMDLine_t* myCMDline);
size_t  LabelLength             (CMDLine_t* myCMDline);

#endif