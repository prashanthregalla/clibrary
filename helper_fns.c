
/****** UTILITIES/HELPER FUNCTIONS used by all other programs ************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
smaller(int a, int b)
{
    if(a<b)
        return a;
    else
        return b;
}

int
bigger(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
}

void 
swap(int *array, int pos1, int pos2)
{
    int temp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = temp;
}

void       
swap_void(void *array1, int no1, int no2, int size)
{
    void *temp = malloc(size);

    memcpy(temp, array1+no1*size, size);
    memcpy(array1+no1*size, array1+no2*size, size);
    memcpy( array1+no2*size, temp, size);

}

int
partition(int *array, int begin, int end)
{
    //int mid = begin + (end - begin)/2; //mid is the pivot element

    //swap(array, begin, mid); //swap with first element
    int pivot = array[begin]; //first element is the pivot, not middle

    int i = begin + 1, j = end;
    while(i<=j)
    {
        while(array[i] <= pivot)
            i++;
        while(array[j] > pivot)
            j--;
        if(i<j)
            swap(array, i, j);
    }
    swap(array, begin, j);
    
    return j; //this is the pivot elements position in the array, all elements left are less and right are more than this
     
}

int 
partition_random(int *array, int begin, int end) //used by quick_sort
{
    int rand_index = begin + rand() % (end-begin+1);
    swap(array, begin, rand_index); //swap this with the first element to use the normal partitioning
    return partition(array, begin, end); //now call the normal partiton 
   
    return 0; 
}

int 
merge(int *array1, int size_1, int *array2, int size_2, int *result) //result array should be big enough
{
    //if( size_res < (size_1 + size_2))
      //      return -1;

    int i, j;
    int k=0; //index of result array

    i = 0; j = 0;
    while(i < size_1 && j < size_2)
    {
        if(array1[i] <= array2[j])
        { 
            result[k++] = array1[i++];
            
        }
        else
        {
            result[k++] = array2[j++];
            
        }
    }
    
    while(i < size_1)
        result[k++] = array1[i++];

    while(j < size_2)
         result[k++] = array2[j++];

    return 0;
}

void
print_array(int *array, int size)
{
    int i;

    for(i = 0; i < size; i++)
        printf("%d ", array[i]);
    
    printf("\n");
}

void
print_range_array(int *array, int begin, int end) //we can &/ need to pass size as an argument too, for bounds checking
{
    int i;
    
    for(i = begin; i <= end; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int
copy_array(int *source, int *dest, int size)
{ 
                                            //dest array should be big enough 
    int i;

    for(i = 0; i < size; i++)
        dest[i] = source[i];

    return 0;
}


//copy_range_array copies range from source to dest
int
copy_range_array(int *src, int src_begin, int src_end, int *dst, int dst_begin, int dst_end)
{
    if( (src_end - src_begin) != (dst_end - dst_begin))
        return -1;
    else
    {
        int i = src_begin, j = dst_begin;

        while(i <= src_end && j <= dst_end)
        {
            dst[j] = src[i];
            i++; j++;
        }
    }

    return 0;
}

void
fill_array(int *array, int size, int val)
{
    int i;

    for(i = 0; i < size; i++)
        array[i] = val;
}

void
fill_range_array(int *array, int begin, int end, int val)
{
    int i;

    for(i = begin; i <= end; i++)
        array[i] = val;
}

void
shuffle_word(char *word, int word_len)
{
    //char shuffle_buf[MAX_LENGTH]; //max word length, its defined in game_anagram.c file as 40, hard coding here
    char shuffle_buf[40];
    strcpy(shuffle_buf, word);
    int count = 0; //for the filled positions in the shuffle_buf    
    int shuffle_pos;
    fill_word(shuffle_buf, '.', word_len); //defined in game_anagram.c

    while(count <= word_len)
    {
        shuffle_pos = rand() % word_len;
        if(shuffle_buf[shuffle_pos] == '.')
        {
            shuffle_buf[shuffle_pos] = word[count];
            count++;
            if(count == word_len)
                break;
        }

    }
    strcpy(word, shuffle_buf);
    //printf("word is : %s\n", word);
    //printf("Shuffled word is : %s\n", shuffle_buf);
}

//same as memset
void
fill_word(char *word, char fill_char, int word_len)
{
    //int word_len = strlen(word);

    for(int i=0; i < word_len; i++)
        word[i] = fill_char;
}
