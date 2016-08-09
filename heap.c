/*** HEAP DATASTRUCTURE  ***/

#include "helper_fns_pr.h"
#include "heap_pr.h"
#include <string.h>
#include <stdlib.h>


typedef int (*compare_pr)(void*, void*);

static int
parent_heap(int i)
{
    return (i-1)/2;  // 0 based indexing
}

static int
right_heap(int i)
{
    return 2*i + 2 ;  // 0 based indexing
}

static int 
left_heap(int i)
{
    return 2*i + 1;  //0 based indexing and array[0] stores heap_size
}


int
max_heapify(void *array, int size, int i, int no_elem, compare_pr compare)
{
    
    int left = left_heap(i);
    int right = right_heap(i);
    
    int heap_size = no_elem - 1; //ie., heap is from array[0..no_elem - 1]

    int largest_child = i;
    if(left <= heap_size && compare(array+size*(left), array+size*(i)) > 0)
        largest_child = left;
    if(right <= heap_size && compare(array+size*(right), array+size*(largest_child)) > 0)
                                                //right is the bigger of one of node, else left is bigger
        largest_child = right;
    
    if(largest_child != i)
    {   
        swap_void(array, i, largest_child, size);
        max_heapify(array, size, largest_child, no_elem, compare);
    }

    return 0;

}

int
min_heapify(void* array, int size, int i, int no_elem, compare_pr compare)
{
    int left = left_heap(i);
    int right = right_heap(i);
         
    int heap_size = no_elem - 1; //ie., heap is from array[0..no_elem-1]

    int smallest_child = i;
    if(left <= heap_size && compare(array+size*(left), array+size*(i)) < 0)
        smallest_child = left;

    if(right <= heap_size && compare(array+size*(right), array+size*(smallest_child)) < 0) 
                                        //right is the bigger of one of node, else left is bigger
        smallest_child = right;

    if(smallest_child != i)
    {
        swap_void(array, i, smallest_child, size);
        min_heapify(array, size, smallest_child, no_elem, compare);
    } 
    return 0;
}


int
build_max_heap(void *array, int size, int no_elem, compare_pr mycompare)
{   
    int i;
        
   // array[0] = no_ele; //this is the heap_size, always in array[0], will be updated when it needs to be
    
    for(i = no_elem/2; i>=0; i--)
        max_heapify(array, size, i, no_elem, mycompare);
    
    return 0;
}

int
build_min_heap(void* array, int size, int no_elem, compare_pr mycompare)
{
    int i;
    
    //array[0] = no_ele; //this is the heap_size, always in array[0], will be updated when it needs to be

    for(i = no_elem/2; i>=0; i--)
        min_heapify(array, size, i, no_elem, mycompare);

    return 0;
}
