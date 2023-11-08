#ifndef MAIN_ASM_H
#define MAIN_ASM_H

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
    size_t length_cmd;

    char   reg;

    char*  label;
    char*  cmd_label;

    Elem_t value;
    int    n_run;
    int    brackets;
} CMDLine_t;

typedef struct BufferBin {
    Elem_t* bin_buffer;
    int     n_elements;
} BufferBin_t;

typedef struct Asm {
    BufferAsm_t asmCode;
    BufferBin_t binCode;
    Label_t     labels[AMOUNT_OF_LABELS];
    FILE*       file_listing;
} Asm_t;

typedef struct Parsing {
    char*   start_word;
    size_t  length_word;
    int     n_word;
    int     end_of_str;
} Parsing_t;

#endif 