#ifndef PR_SEARCHING_H
#define PR_SEARCHING_H

#include "global_vars_pr.h"

/*
 *
 * int linear_search(void *array_var, int begin, int end, my_var_type type_of_var, void *key ); //linear search, returns location of first occurance
int linear_search_reverse(void *array_var, int begin, int end, my_var_type type_of_var, void *key ); //search from end, returns last key

int binary_search(void *array_var, int begin, int end, my_var_type type_of_var, void *key ); //binary search, returns index of a hit

int first_key(void *array_var, int begin, int end, my_var_type type_of_var, void *key ); //first occurrence
int last_key(void *array_var, int begin, int end, my_var_type type_of_var, void *key ); //last occurrence
int count_element(void *array_var, int begin, int end, my_var_type type_of_var, void *key ); //number of times an elements occurs in an array

*/

int linear_search(int *array, int begin, int end, int key);            //begin is the start position
int linear_search_reverse(int *array, int begin, int end, int key);    //end is the end position, ex. n-1 in a array of size n

int binary_search(int *array, int begin, int end, int key);

int first_key(int *array, int begin, int end, int key);
int last_key(int *array, int begin, int end, int key);
int count_key(int *array, int begin, int end, int key);

int lower_bound(int *array, int begin, int end, int key); //index to the first key thats less than or equal to the key
int upper_bound(int *array, int begin, int end, int key); //index to the first key thats greater than the key

#endif
