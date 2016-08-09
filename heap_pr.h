#ifndef PR_HEAP_H
#define PR_HEAP_H

#include "global_vars_pr.h"

typedef int (*compare_pr)(void*, void*);

int max_heapify(void* array, int size, int i, int no_elem, compare_pr compare);
int min_heapify(void* array, int size, int i, int no_elem, compare_pr compare);


int build_max_heap(void *array, int size, int no_elem, compare_pr mycompare);
int build_min_heap(void* array, int size, int no_elem, compare_pr mycompare);

//int max_heapify(int *array, int i, int no_elem); 
//int min_heapify(int *array, int i, int no_elem);

//int build_max_heap(int *array, int no_elem); //no_ele is the no. of elements in heap, and array[0] stores the heap_size
//int build_min_heap(int *array, int no_elem);     // heap starts from 1, ie., 1 based indexing in arrays



#endif
