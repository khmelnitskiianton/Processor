#ifndef HEAD_ASM_H
#define HEAD_ASM_H

struct Line {
    size_t len;
    char* start_line;
};

typedef struct BufferAsm {
    FILE*  file_in;
    FILE*  file_out;

    size_t size_text;
    size_t n_strings;

    char* text_buffer;
    Line* string_buffer;
} BufferAsm_t;

#endif 