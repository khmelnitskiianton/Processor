#ifndef TYPE_H
#define TYPE_H

#include <limits.h>
#define EPSILONE 1e-10
typedef int Elem_t;
#define SPECIFIER "%d"
const Elem_t POISON_ELEMENT = INT_MAX;
const int N_DIGIT = 1e2;
#define STR_TO_INT(arg) (int) (strtod(arg, NULL)*N_DIGIT);
#define COMPARE_TYPE(value1, value2) (value1 == value2) 

#endif