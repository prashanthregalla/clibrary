#ifndef PR_HELPER_FNS_H
#define PR_HELPER_FNS_H

#include "global_vars_pr.h"

/**** UTILITIES/HELPER FUNCTIONS ****/

void print_array(int *array, int size);
void print_range_array(int *array, int begin, int end); //we may/needTo pass array size as an argument too, for bounds checking

int copy_array(int *source, int *dest, int size); //will copy from begin to end, into dest

//copy_range_array copies range from source to dest
int copy_range_array(int *src, int src_begin, int src_end, int *dst, int dst_begin, int dst_end);

void fill_array(int *array, int size, int val);
void fill_range_array(int *array, int begin, int end, int val);

int bigger(int a, int b);
int smaller(int a, int b);

int partition_random(int *array, int begin, int end);
int merge(int *array1, int size1, int *array2, int size2, int *result); //result array should be big enough

void swap(int *array, int pos1, int pos2);
void swap_void(void *array1, int no1, int no2, int size);  //for swapping in void arrays


void fill_word(char *word, char fill_char, int word_len); //fill the word with fill_char
void shuffle_word(char *word, int word_len); //shuffles/jumbles the characters in the words

//need to implement, shifted to string_pr.h
//void string_fill(char* str, char fill_char, int str_len);
//void string_shuffle(char* str, int str_len);

#endif
