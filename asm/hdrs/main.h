#ifndef HEAD_ASM_H
#define HEAD_ASM_H

typedef double Elem_t;
#define SPECIFIER "%lf"

const Elem_t POISON_ELEMENT = NAN;

#define FILE_IN  "D:/Study/C/Processor/input_text.txt"
#define FILE_OUT "D:/Study/C/Processor/input_num.txt"

enum math_codes {
    HLT  = -1,
    OUT  = 0,
    PUSH = 1,
    IN   = 2,
    SUB  = 3,
    DIV  = 4,
    ADD  = 5,
    MUL  = 6,
    SQRT = 7,
    SIN  = 8,
    COS  = 9,
};

#endif 