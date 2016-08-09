
#include "global_vars_pr.h"
#include "searching_pr.h"

int 
linear_search(int *array, int begin, int end, int key)
{
    int i;
    
    if(begin > end)
        return -1;

    for (i = begin; i <= end; i++)
    {
        if(array[i] == key)
            return i;
    }
    
    return -1; //not found


}

int 
linear_search_reverse(int *array, int begin, int end, int key)
{
    int i;
    
    if(begin > end)
        return -1;

    for (i = end ; i>=0; i--)
        if(array[i] == key)
            return i;

    return -1; //not found
}

int 
binary_search(int *array, int begin, int end, int key)
{
    if(begin > end)
        return -1;
    else
    {
        int mid = begin + (end - begin) / 2 ;
        
        if(array[mid] == key)
            return mid;
        else if (array[mid] > key)
            return binary_search(array, begin, mid - 1, key);
        else
            return binary_search(array, mid + 1, end, key);

    }

    return -1; //not found
}



int 
first_key(int *array, int begin, int end, int key)
{
    if(begin > end)
        return -1; 
    else
    {   
        int mid = begin + (end - begin) / 2 ;

        if(array[mid] == key && (mid == 0 || array[mid - 1] < key))
            return mid;
        else if (array[mid] >= key)
            return first_key(array, begin, mid - 1, key);
        else
            return first_key(array, mid + 1, end, key);

    }

    return -1; //not found
}


static int 
last_key_utility(int *array, int begin, int end, int key, int array_size)
{
    if(begin > end)
        return -1;
    else
    {
        int mid = begin + (end - begin) / 2 ;

        if(array[mid] == key && (mid == array_size || array[mid + 1] > key))
            return mid;
        else if (array[mid] > key)
            return last_key_utility(array, begin, mid - 1, key, array_size);
        else
            return last_key_utility(array, mid + 1, end, key, array_size);

    }

    return -1; //not found
}

int 
last_key(int *array, int begin, int end, int key)
{
    return last_key_utility(array, begin, end, key, end );      
}

int 
count_key(int *array, int begin, int end, int key)
{
    int first = first_key(array, begin, end, key);

    if(first == -1)
        return -1;

    int last = last_key(array, begin, end, key);

    return last - first + 1;
}

static int 
lower_bound_utility(int *array, int begin, int end, int key, int size) //index to the key thats less than the key
{

    if(begin > end)
        return -1; 
    else
    {   
        int mid = begin + (end - begin) / 2 ;
        
    
        if( mid == 0 || mid == size || 
            (array[mid] == key && array[mid-1] < key) ||  //this is the left most key in the array
            (array[mid] < key && array[mid+1] > key) )    //key not found
                return mid;
        else if(array[mid] > key && array[mid-1]<key)    //key not found
                return mid-1;
        else if(array[mid] >= key)
            return lower_bound_utility(array, begin, mid - 1, key, size);
        else
            return lower_bound_utility(array, mid + 1, end, key, size);

    }

    return -1; //should not come here
}

int
static upper_bound_utility(int *array, int begin, int end, int key, int size) //index to the key thats greater than the key
{
    if(begin > end)
        return -1;
    else
    {
        int mid = begin + (end - begin) / 2 ;

        if( mid == size || mid == 0 ||
            (array[mid] > key && array[mid-1] <= key) )
                return mid;
        else if(array[mid] <= key && array[mid+1]>key)
                return mid+1;
        else if(array[mid] > key)
            return upper_bound_utility(array, begin, mid - 1, key, size);
        else
            return upper_bound_utility(array, mid + 1, end, key, size);

    } 
    return -1; //should not come to this
}

int
upper_bound(int *array, int begin, int end, int key)
{
    return upper_bound_utility(array, begin, end, key, end );
}

int
lower_bound(int *array, int begin, int end, int key)
{
        return lower_bound_utility(array, begin, end, key, end );
}
