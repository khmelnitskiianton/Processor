#ifndef SUPPORT_H
#define SUPPORT_H

int     get_reg_id              (char reg);
int     isCommand               (char* arg);
int     isLabel                 (char* arg);
int     RecoverTextBuffer       (Asm_t* myAsm);
int     InitLine                (CMDLine_t* myCMDline);
size_t  LabelLength             (CMDLine_t* myCMDline);
size_t  ParsingString           (Parsing_t* myActualWord, char symbol);
int     CleaningComments        (char* str, char symbol_of_comment);
int     isValue                 (char* arg);
int     PrintAsmListing         (CMDLine_t* myCMDline, Asm_t *myAsm, int bin_command);
char*   SkipSpaces              (char* str);
int     CheckNoArgs             (char* str);

#endif