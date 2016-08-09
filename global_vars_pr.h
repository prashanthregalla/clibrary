#ifndef PR_GLOBAL_VARS_H
#define PR_GLOBAL_VARS_H


typedef enum my_var_type_enum
{ 
    INTS=0, 
    FLOATS, 
    CHARS, 
    STRINGS 
}my_var_type;

typedef int (*compare_pr)(void*, void*);


#define TRUE 1
#define FALSE 0

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
  
//  // Converts key current character into index
//  // use only 'a' through 'z' and lower case


#define CHAR_TO_INDEX_LOWER(c) (tolower((int)c) - (int)'a')
#define INDEX_CHAR_LOWER(c) (tolower((int)c) - (int)'a')

#define CHAR_TO_INDEX_UPPER(c) (toupper((int)c) - (int)'A')
#define INDEX_CHAR_UPPER(c) (toupper((int)c) - (int)'A')

/*** MEMORY ALLOCATION MACROS ***/

/* Allocates a single object using malloc() */
#define MALLOC(type) ((type *)malloc(sizeof(type)))
 
/* Allocates an array of objects using malloc() */
#define MALLOC_ARRAY(number, type) \
        ((type *)malloc((number) * sizeof(type)))
 
/*
 *  * Allocates a single object with a flexible
 *   * array member using malloc().
 *    */
#define MALLOC_FLEX(stype, number, etype) \
        ((stype *)malloc(sizeof(stype) \
                + (number) * sizeof(etype)))
 
/* Allocates an array of objects using calloc() */
#define CALLOC(number, type) \
        ((type *)calloc(number, sizeof(type)))
 
/* Reallocates an array of objects using realloc() */
#define REALLOC_ARRAY(pointer, number, type) \
        ((type *)realloc(pointer, (number) * sizeof(type)))
 
/*
 *  * Reallocates a single object with a flexible
 *   * array member using realloc().
 *    */
#define REALLOC_FLEX(pointer, stype, number, etype) \
        ((stype *)realloc(pointer, sizeof(stype) \
                + (number) * sizeof(etype)))

#define FREE(type) free(type); type = 0



#endif
