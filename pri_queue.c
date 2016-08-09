#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "queue_pr.h"
#include "global_vars_pr.h"
#include "heap_pr.h" // for accessing max_heap etc., fns
#include "helper_fns_pr.h"

/***** PRIORITY QUEUE *****/

/*** PRIORITY QUEUE , which can have max and min priority queues depending on the type ***/


struct pri_queue_
{
    int capacity;
    int size;
    
    prq_type type; //type of priority queue 0: MIN_PRI_Q, 1: MAX_PRI_Q
    pri_queue_data *elements;

    //int size_ele;
    compare_pr compare;
    
};

typedef struct pri_queue_ pri_queue;

static void
pri_queue_swap(pri_queue_data* elements, int i1, int i2)
{
    pri_queue_data temp;
    temp = elements[i1];
    elements[i1] = elements[i2];
    elements[i2] = temp;    
}
   
int 
pri_queue_compare(void* p1, void* p2)
{
    pri_queue_data t1 = *(pri_queue_data*)p1;
    pri_queue_data t2 = *(pri_queue_data*)p2;   

    return t1.priority - t2.priority;

}   

pri_queue* 
pri_queue_create(int max_elem, prq_type type) 
                                                                // 0: MIN_PRI_Q, 1: MAX_PRI_Q , is type of PR_Q
{
    pri_queue *PRQ = MALLOC(pri_queue); //using the macro here, to be easier
    
    if( ! PRQ )
    {
        perror("Unable to allocate memory");
    }
    else
    {
        PRQ->capacity = max_elem;
        PRQ->size = 0;
        PRQ->type = type;

        PRQ->elements = MALLOC_ARRAY(max_elem, pri_queue_data);  //size_ele is the size of each element in the elements array
                                                            //it can be a int, float, structure or a pointer to a structure
        //PRQ->size_ele = size_ele; //saving the size_ele, size of each element, might use for validation while push/pop
        PRQ->compare = pri_queue_compare; //this is for heapify functions
        

    for(int i=0; i<max_elem; i++)
        PRQ->elements[i].pri_queue_content = NULL;
    
    return PRQ;
    }

}

void 
pri_queue_destroy(pri_queue *PRQ)
{
    //free(PRQ->elements);
    //PRQ->elements = NULL;
    
    //both the above can be done by macro FREE
    FREE(PRQ->elements);
    PRQ->compare = NULL;
    PRQ->capacity = PRQ->size = 0;
    PRQ->type = PRQ_DESTROYED;
}

void 
pri_queue_enqueue(pri_queue *PRQ, pri_queue_data elem, prq_type type)
{
    if(type != PRQ->type)
    {
        fprintf(stderr, "enqueue_PRQ: Enqueue on wrong type of PRQ, check if its the right type of PR_QUEUE\n");
    }
    else if(pri_queue_is_full(PRQ))
    {
        fprintf(stderr, "enqueue_PRQ: This Priority Queue is full...its capacity is %d\n", PRQ->size);

    }
    else
    {
        switch(PRQ->type)
        {
            case MAX_PRI_Q: 
                
                PRQ->elements[PRQ->size].priority = INT_MIN;
                PRQ->elements[PRQ->size].pri_queue_content = elem.pri_queue_content;
                PRQ->size++;
                pri_queue_increase_key(PRQ, PRQ->size-1, elem.priority);
                break;

            case MIN_PRI_Q:
                PRQ->elements[PRQ->size].priority = INT_MAX;
                PRQ->elements[PRQ->size].pri_queue_content = elem.pri_queue_content;
                PRQ->size++;
                pri_queue_decrease_key(PRQ, PRQ->size-1, elem.priority);

                break;
        }
    }
}

pri_queue_data
pri_queue_dequeue(pri_queue *PRQ)
{
    pri_queue_data key_to_return;

    if(pri_queue_is_empty(PRQ))
    {
        fprintf(stderr, "dequeue_PRQ: This Priority Queue is empty...its capacity is %d\n", PRQ->size);

    }
    else
    {   
        key_to_return = PRQ->elements[0];
        //abort();
        switch(PRQ->type)
        {
            case MAX_PRI_Q: 
                PRQ->elements[0] = PRQ->elements[PRQ->size-1];
                max_heapify(PRQ->elements, sizeof(pri_queue_data), 0, PRQ->size, PRQ->compare);
                
                break;

            case MIN_PRI_Q:
                PRQ->elements[0] = PRQ->elements[PRQ->size-1];
                min_heapify(PRQ->elements, sizeof(pri_queue_data), 0, PRQ->size, PRQ->compare);

                break;
        }
        
        PRQ->size--;
        return key_to_return;
    }

}

int 
pri_queue_type(pri_queue *PRQ) // 0: MIN_PRI_Q, 1: MAX_PRI_Q
{
    return PRQ->type;
}

pri_queue_data 
pri_queue_extract_min(pri_queue *PRQ) //will do nothing if its a min_pr_q, logs to stderr ofcourse
{
    if(PRQ->type != MIN_PRI_Q)
    {
        fprintf(stderr, "extract_MIN_PRQ: This is a max_PRQ...check once again...\n");
        //return INT_MIN;
    }
    else if(pri_queue_is_empty(PRQ))
    {
        fprintf(stderr, "extract_MIN_PRQ: This Priority Queue is empty...its capacity is %d\n", PRQ->capacity);
        //return INT_MIN;
    }
    else
    {
        pri_queue_data key_to_return = PRQ->elements[0];

        PRQ->elements[0] = PRQ->elements[PRQ->size-1];
        PRQ->size--;
        min_heapify(PRQ->elements, sizeof(pri_queue_data), 0, PRQ->size, PRQ->compare);
        
        return key_to_return;
    }
}

pri_queue_data 
pri_queue_extract_max(pri_queue *PRQ) //will log error if its a max_pr_q
{

    if(PRQ->type != MAX_PRI_Q)
    {
        fprintf(stderr, "extract_MAX_PRQ: This is a min_PRQ...check once again...\n");
        //return INT_MIN;
    }
    else if(pri_queue_is_empty(PRQ))
    {
        fprintf(stderr, "extract_MAX_PRQ: This Priority Queue is empty...its capacity is %d\n", PRQ->size);
        //return INT_MIN;
    }
    else
    {
        pri_queue_data key_to_return = PRQ->elements[0];

        PRQ->elements[0] = PRQ->elements[PRQ->size-1];
        PRQ->size--;
        max_heapify(PRQ->elements, sizeof(pri_queue_data), 0, PRQ->size, PRQ->compare);
        
        return key_to_return;
    }
}

pri_queue_data
pri_queue_peek_max(pri_queue *PRQ) //will do nothing if its a min_pr_q, logs ofcourse
{
    if(PRQ->size > 0 && PRQ->type == MAX_PRI_Q)
        return PRQ->elements[0];
    else
    {
        fprintf(stderr,"The PR_QUE is min priority queue...you are asking for peek-MIN here\n");
        //return INT_MIN;
    }
}

pri_queue_data
pri_queue_peek_min(pri_queue *PRQ) //will log error if its a max_pr_q
{
    if(PRQ->size > 0 && PRQ->type == MIN_PRI_Q)
        return PRQ->elements[0];
    else
    {
        fprintf(stderr,"The PR_QUE is min priority queue...you are asking for peek-MAX here\n");
      //  return INT_MIN;
    }
}

int 
pri_queue_size(pri_queue *PRQ)
{
    return PRQ->size;
}

int 
pri_queue_capacity(pri_queue *PRQ)
{
    return PRQ->capacity;
}

int 
pri_queue_is_empty(pri_queue *PRQ)
{
    return PRQ->size == 0;
}

int 
pri_queue_is_full(pri_queue *PRQ)
{
    return PRQ->size == PRQ->capacity;
}


void 
pri_queue_increase_key(pri_queue *PRQ, int index, int new_pri_val) //will do nothing if its a min_pr_q, logs ofcourse
{
    if(PRQ->type != MAX_PRI_Q)
    {
        fprintf(stderr, "increase_key_PRQ: This is a NOT a max_PRQ...increase_key not allowed...check once again...\n");
        //return INT_MIN;
    }
    else if(pri_queue_is_empty(PRQ))
    {
        fprintf(stderr, "increase_key_PRQ: This MAX_Priority Queue is empty...its capacity is %d\n", PRQ->capacity);
        
    }
    else
    {
        if(PRQ->elements[index].priority > new_pri_val)
        {
            fprintf(stderr, "increase_key_PRQ: This value of the new priority is not more than the current val...current val: %d\n", PRQ->elements[index].priority);
        }
        else
        {
            PRQ->elements[index].priority = new_pri_val;
            int parent_i;
            while( index >=0 )
            {
                parent_i = (index-1)/2;
                if(PRQ->elements[parent_i].priority < new_pri_val) //parent is less than this new_val
                    pri_queue_swap(PRQ->elements, parent_i, index);
                else
                    break;
                index = parent_i;
            }


        }
    }    
}

void 
pri_queue_decrease_key(pri_queue *PRQ, int index, int new_pri_val) //will log error if its a max_pr_q
{

    if(PRQ->type != MIN_PRI_Q)
    {
        fprintf(stderr, "decrease_key_PRQ: This is a NOT a min_PRQ...decrease_key not allowed...check once again...\n");
        //return INT_MIN;
    }
    else if(pri_queue_is_empty(PRQ))
    {
        fprintf(stderr, "decrease_key_PRQ: This MIN_Priority Queue is empty...its capacity is %d\n", PRQ->capacity);
        
    }
    else
    {
        if(PRQ->elements[index].priority < new_pri_val)
        {
            fprintf(stderr, "decrease_key_PRQ: This value of the new priority is not less than the current val...current val: %d\n", PRQ->elements[index].priority);
        }
        else
        {
            PRQ->elements[index].priority = new_pri_val;
            int parent_i;
            while( index >=0 )
            {
                parent_i = (index-1)/2;
                if(PRQ->elements[parent_i].priority > new_pri_val) //parent is less than this new_val
                    pri_queue_swap(PRQ->elements, parent_i, index);
                else
                    break;
                index = parent_i;
            }


        }
    }

}

