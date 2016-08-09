#include <stdio.h>
#include <stdlib.h>
#include "stack_pr.h"

#include <limits.h>

struct stack_a   //stack_a : stack using array, will have one more stack(simply, stack) using linked list
{
    int capacity;
    int size;
    int *elements;
};



stack_a*
stack_a_create(int max_elem)
{
    /* Create a stack_a */
    stack_a *S;
    S = (stack_a *)malloc(sizeof(stack_a));
    /* Initialise its properties */
    S->elements = (int *)malloc(sizeof(int)*max_elem);
    S->size = 0;
    S->capacity = max_elem;
    /* Return the pointer */
    return S;
}


void
stack_a_destroy(stack_a *S)
{
    free(S->elements); //delete the elements array
    S->elements = NULL;
    S->size = S->capacity = 0;

}

void
stack_a_push(stack_a *S, int elem)
{
    if(! stack_a_is_full(S))
    {
        S->elements[S->size] = elem;
        S->size += 1;
    }
    else
    {   
        fprintf(stderr, "stack_a is full, cannot PUSH element %d now\n", elem);
    }   
    
}

void
stack_a_pop(stack_a *S)
{
    if(! stack_a_is_empty(S))
    {
        S->size--;
    }
    else
    {
        fprintf(stderr, "stack_a is empty, cannot POP element...\n");
    }
}

int
stack_a_top(stack_a *S)
{
    if(! stack_a_is_empty(S))
        return S->elements[S->size-1];
    else
    {
        fprintf(stderr, "stack_a is empty...\n");
        return INT_MAX; //INT_MAX in case of any error
    }
}

int
stack_a_size(stack_a *S)
{
    return S->size;
}

int
stack_a_capacity(stack_a *S)
{
    return S->capacity;
}

int 
stack_a_is_empty(stack_a *S)
{
    return S->size == 0;
}

int
stack_a_is_full(stack_a *S)
{
    return S->size == S->capacity;
}

/*** Lined List Representaion of the stack, named, stack ***/

typedef struct stack_node_ //for LL representation
{
    void* data;
    struct stack_node_ *next;
}stack_node;

struct stack_            //for LL representation
{
    int size;
    stack_node *root;    
};

stack* 
stack_create()
{
    stack *S = (stack*) malloc(sizeof(stack));
    S->size = 0;
    S->root = NULL;

    return S;
}

void 
stack_destroy(stack *S)
{   
    S->size = 0;

    //destroy_LL(S->root); //Neeed to delete all the nodes 
    
    while(S->root != NULL)
    {
        stack_node *temp = S->root;
        S->root = S->root->next;
        free(temp);
    }
}

void 
stack_push(stack *S, void* data)
{
    stack_node *new_node = (stack_node*) malloc(sizeof(stack_node));
    new_node -> data = data;
    new_node -> next = NULL;
    
    new_node->next = S->root;
    S->root = new_node;
    S->size = S->size + 1;
}

void
stack_pop(stack *S)
{
    if(! stack_is_empty(S))
    {
        stack_node *temp = S->root;
        //int item = S->root->data;
        S->root = S->root->next;
        free(temp);
        S->size = S->size - 1;
    }
    else
    {
        fprintf(stderr, "Stack empty...can not POP now...\n");

    }
}

void* 
stack_top(stack *S)
{
    if(! stack_is_empty(S))
    {
        return S->root->data;
    }
    else
    {
        fprintf(stderr, "Stack is empty, top() failed...\n");
        return (void*)INT_MAX;
    }
}

int 
stack_size(stack *S)
{
    return S->size;
}

int 
stack_is_empty(stack *S)
{
    return S->size == 0;
}

/* These are not needed for LL stack ***

int 
stack_capacity(stack *S)
{

}

int 
stack_is_full(stack *S)
{

}

*/
