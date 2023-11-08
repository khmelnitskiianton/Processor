#ifndef MYASSERT_H
#define MYASSERT_H

#include "colors.h"

#define DEBUG 1

#ifdef DEBUG
#define MYASSERT(check, error_code, ending)                                                                         \
        do                                                                                                          \
        {                                                                                                           \
            if (!(check))                                                                                           \
            {                                                                                                       \
                printf(MAGENTA "Error in code! Error code: %d\n", error_code);                                      \
                printf("In File: %s, In Line: %d, In Function: %s\n" RESET, __FILE__, __LINE__,__PRETTY_FUNCTION__);   \
                ending;                                                                                             \
            }                                                                                                       \
        }                                                                                                           \
        while(0);
#else   
#define MYASSERT(check, error_code, ending)
#endif

//or structure?)
enum CODES_OF_ERRORS {
    BAD_POINTER_PASSED_IN_FUNC  = 1,
    NULL_POINTER_IN_OPEN_FILE   = 2,
    NULL_POINTER_IN_CLOSE_FILE  = 3,
    UNKNOWN_REGISTER            = 4,
};

#endif