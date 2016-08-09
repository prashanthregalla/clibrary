#ifndef PR_SORTING_H
#define PR_SORTING_H

#include "global_vars_pr.h"

void selection_sort(int *array, int size); //size here is the number of elements in the array
void bubble_sort(int *array, int size);
void insertion_sort(int *array, int size);

void merge_sort(int *array, int size);
void quick_sort(int *array, int size);
void heap_sort(int *array, int size);

void counting_sort(int *array, int size, int max_no);
void radix_sort(int *array, int size);

void bucket_sort(int *array, int size);
void shell_sort(int *array, int size);
void comb_sort(int *array, int size);

//void  //for sorting anything, we need to provide a compare function
//insertion_sort_void(void *array, int no_ele, int size, int (*compare)(void*, void*));

#endif
