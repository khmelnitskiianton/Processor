#ifndef TYPE_H
#define TYPE_H

#define TYPE_DOUBLE 0

#define EPSILONE 1e-10

#if (TYPE_DOUBLE) 
#define ON_DOUBLE(...) __VA_ARGS__
#define ON_INT(...) 
typedef double Elem_t;
#define SPECIFIER "%lf"
const Elem_t POISON_ELEMENT = NAN;
#define STR_TO_TYPE(arg) strtod (arg, NULL);                                
#define COMPARE_TYPE(value1, value2) (compare(value1, value2)) 
#else
#define ON_DOUBLE(...) 
#define ON_INT(...) __VA_ARGS__
typedef int Elem_t;
#define SPECIFIER "%d"
const Elem_t POISON_ELEMENT = NULL;
const int N_DIGIT = 1e2;
#define STR_TO_TYPE(arg) (int) (strtod(arg, NULL)*N_DIGIT);
#define COMPARE_TYPE(value1, value2) (value1 == value2) 
#endif

#endif