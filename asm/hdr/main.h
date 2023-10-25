#ifndef HEAD_ASM_H
#define HEAD_ASM_H

typedef struct Line {
    size_t len;
    char* start_line;
} Line_t;

typedef struct BufferAsm {
    FILE*  file_in;
    FILE*  file_out;

    size_t size_text;
    size_t n_strings;

    char* text_buffer;
    Line_t* string_buffer;
} BufferAsm_t;

typedef struct Label {
    char*  label;
    int    address;
    size_t len_label;
} Label_t;

typedef struct CMDLine {
    char*  command;
    char*  reg;

    char*  label;
    char*  cmd_label;

    Elem_t value;

    int    n_run;
} CMDLine_t;

typedef struct BufferBin {
    Elem_t* bin_buffer;
    size_t  n_elements;
} BufferBin_t;

typedef struct Asm {
    BufferAsm_t asmCode;
    BufferBin_t binCode;
    Label_t     labels[AMOUNT_OF_LABELS];
} Asm_t;

#endif 