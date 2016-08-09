#include "sorting_pr.h"
#include "helper_fns_pr.h"
#include "heap_pr.h"


static void 
merge_sort_utility(int *array, int begin, int end);

void 
selection_sort(int *array, int size)
{
    int i, j, min;
    int n = size;

    for(i = 0; i < n-1; i++)
    {
        min = i;

        for(j = i+1; j<n; j++)
            if(array[j] < array[min])
                min = j;

        swap(array, i, min);
    }
}

void 
bubble_sort(int *array, int size)
{
    int i, j;
    int n = size;

    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < (n-i-1); j++)
        {
            if(array[j] > array[j+1])
                swap(array, j, j+1);
        }
    }
}

void 
insertion_sort(int *array, int size)
{
    int i, j;
    int temp;
    
    int n = size;
    for(i = 1; i < n; i++)
    {
        
        temp = array[i];   
        j = i;
        while(j >0 && temp < array[j-1])
        {
            array[j] = array[j-1];
            j--;
        }
        array[j] = temp;
    }    
}


/*
 *
 * void  //for sorting anything, we need to provide a compare function
insertion_sort_void(void *array, int no_ele, int size, int (*compare)(void*, void*))
{
    int i, j;
    void *temp;
    
    int n = no_ele;
    for(i = 1; i < n; i++)
    {   
        
        temp = (void*) (array+(i-1)*size);
        j = i;
        while(j >0 && compare(temp, temp-size)  < 0)
        {   
            array[j] = array[j-1];
            j--;
        }
        array[j] = temp;
    } 
}
*/


void 
merge_sort(int *array, int size)
{
    merge_sort_utility(array, 0 , size-1);
}

static void quick_sort_utility(int *array, int begin, int end)
{
    if(begin < end)
    {
        int pivot_pos = partition_random(array, begin, end);
        
        quick_sort_utility(array, begin, pivot_pos-1);
        quick_sort_utility(array, pivot_pos+1, end);
    }
}

void 
quick_sort(int *array, int size)
{
    quick_sort_utility(array, 0, size-1);
}


static int heap_compare(void* s1, void* s2)
{
    return *(int*)s1 - *(int*)s2;
}

void 
heap_sort(int *array, int size)
{
    //int temp_arr[size+1]; //this will be passed to build_heap as we need 1 based indexing
    //int orig_size = size; //saving the original size for copying back from temp_arr

    //copy_range_array(array, 0, size-1, temp_arr, 1, size);

    //build_max_heap(temp_arr, size); //temp_arr is the max_heap
    
    build_max_heap((void*)array, sizeof(int), size, heap_compare);
    while(size > 1)
    {
        swap(array, 0, size-1);

        size -= 1; //decrease the size as we have one element at its position in the sorted array now 

        max_heapify((void*)array, sizeof(int), 0, size, heap_compare);
    }
    
    //array[0] = orig_size; //storing the size of the heap, which is the entire array now
    //Now temp_arr is sorted, copying it into array before returning
    //copy_range_array(temp_arr, 1, orig_size, array, 0, orig_size-1);

}



void 
counting_sort(int *array, int size, int max_no)
{
    int count[max_no+1];         //counts array
    int result_temp[size];                //temp array to store results, will copy from this to original before returning
    //int status[size];       //for storing the status of processing an array element **NOT GONNA USE THIS LOGIC NOW

    int i;

    for(i = 0; i <= max_no; i++)  //Initializing count array
        count[i] = 0;

    for(i = 0; i < size; i++)    //count the times a number has appeared in the array
        count[ array[i] ]++;

    for(i = 1; i <= max_no; i++)    //cumulative sum, upto the current index
        count[i] += count[i-1];
    
    for(i = size-1; i >=0 ; i--)    //Now place each array element at its correct place in the result_temp array
    {   
        result_temp[ count[array[i]] - 1 ] = array[i]; // -1 as the array starts at 0
        count[array[i]]--;
    }
    
    for(i = 0; i < size; i++)        //copy the results from result_temp to original array 'array'
        array[i] = result_temp[i];

}

void 
radix_sort(int *array, int size)
{

}

void
bucket_sort(int *array, int size)
{

}

void
shell_sort(int *array, int size)
{

}

void
comb_sort(int *array, int size)
{

}

static void 
merge_sort_utility(int *array, int begin, int end)
{
    int i, k;

    if(begin < end)
    {
        int mid = begin + (end - begin)/2;
        merge_sort_utility(array, begin, mid);
        merge_sort_utility(array, mid+1, end);
        
        //Merging both sorted halfs now        
        int size1 = mid-begin+1;  //no of elements in first half
        int size2 = end-mid; //no of elements in second half
        int size_res = end-begin+1; //no of elements in result array, same as the input array

        int temp1[size1]; //first half of array
        int temp2[size2]; //second/last half
        int result[size_res]; //result array after merging first and second halves
        
         
        k=0;
        for(i = begin; i<=mid; i++)  
            temp1[k++] = array[i];  //copy first half into temp1 array

        k=0;
        for(i = mid+1; i<= end; i++)
            temp2[k++] = array[i];  //copy first half into temp2 array

        //Now merge both using the merge function utility and get the result in result array
        merge(temp1, size1, temp2, size2, result);

        //Now copy back the contents from result array to the original array 'array'
        for(i = 0; i < size_res; i++)
            array[begin++] = result[i];
    }
}

