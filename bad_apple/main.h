#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BLACK 0
#define WHITE 1

#define WIDTH 30
#define LENGTH 100

typedef int Elem_t;

typedef struct BadApple {
    FILE*    file_in;
    FILE*    file_out;
} BadApple_t;

FILE* file_open_read (void);
FILE* file_open_write (void);
int BufferCtor (BadApple_t *myBadApple);