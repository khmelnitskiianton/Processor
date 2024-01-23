#ifndef MYASSERT_H
#define MYASSERT_H

#include "colors.h"

#define DEBUG 1

#ifdef DEBUG
#define MYASSERT(check, error_code, ending)                                                              \
        do                                                                                                          \
        {                                                                                                           \
            if (!(check))                                                                                           \
            {                                                                                                       \
                printf(MAGENTA "\nError in code! Error code: %s\n", #error_code);                                   \
                printf("In File: %s, In Line: %d, In Function: %s\n" RESET, __FILE__, __LINE__,__PRETTY_FUNCTION__);\
                ending;                                                                                             \
            }                                                                                                       \
        }                                                                                                           \
        while(0);
#else   
#define MYASSERT(check, error_code, ending)
#endif

#define USER_ERROR(check, error_code, ending)                                                               \
        do                                                                                                  \
        {                                                                                                   \
            if (!(check))                                                                                   \
            {                                                                                               \
                fprintf(stderr, RED "\n>>>>> Error! Error code: %s <<<<<\n",  #error_code);      \
                fprintf(stderr, "In File: %s, In Line: %d, In Function: %s\n",__FILE__,__LINE__,__PRETTY_FUNCTION__);\
                fprintf(stderr, "In this condition:\t\"%s\"\n\n" RESET, #check);                            \
                ending;                                                                                     \
            }                                                                                               \
        }                                                                                                   \
        while(0);

enum CODES_OF_ERRORS {
    BAD_POINTER_PASSED_IN_FUNC    = 1,
    NULL_POINTER_IN_OPEN_FILE     = 2,
    NULL_POINTER_IN_CLOSE_FILE    = 3,
    UNKNOWN_REGISTER              = 4,
    ASM_NO_FILE_PASSED_IN_PROGRAM = 5,
    CPU_NO_FILE_PASSED_IN_PROGRAM = 6,
    BAD_NAME_OF_REGISTER          = 7,
    VALUE_OUT_OF_RANGE            = 8,
    BAD_CALLOC                    = 9,
    BAD_FREAD                     = 10,
    EMPTY_FILE                    = 11,
};

#endif