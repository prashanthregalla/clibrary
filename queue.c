#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "queue_pr.h"

/*** Array representation of a queue...named queue_a ***/

struct queue_a  //for array representaion of queue, named, queue_a
{
    int capacity;
    int size;
    int *elements;
    int front;
    int rear;
};

queue_a*
queue_a_create(int max_elem)
{
    queue_a *Q = (queue_a*) malloc(sizeof(queue_a));
    Q->capacity = max_elem;
    Q->size = 0;
    Q->front = Q->rear = 0;
    Q->elements = (int*) malloc(max_elem * sizeof(int));

}


void 
queue_a_destroy(queue_a *Q)
{
    free(Q->elements);
    Q->elements = NULL;
    Q->capacity = Q->size = Q->front = Q->rear = 0;
}

void 
queue_a_enqueue(queue_a *Q, int elem)
{
    if(! queue_a_is_full(Q))
    {
        Q->elements[Q->rear] = elem;
        Q->rear++;
        if(Q->rear == Q->capacity)  //circular fashion
            Q->rear = 0;
        Q->size++;
    }
    else
        fprintf(stderr, "Q is full and hence cannot enqueue element %d\n", elem);
}

int 
queue_a_dequeue(queue_a *Q)
{
    if(! queue_a_is_empty(Q))
    {
        Q->size--;
        Q->front++;
        if(Q->front == Q->capacity) //circular fashion
            Q->front = 0;
        return Q->elements[Q->front - 1];
    }
    else
        fprintf(stderr, "Q is empty, cannot dequeue now\n");
    return 0;
}

int 
queue_a_front(queue_a *Q)
{
    if(! queue_a_is_empty(Q))
        return Q->elements[Q->front];

    return 0;
}

int 
queue_a_rear(queue_a *Q)
{
    if(! queue_a_is_empty(Q))
        return Q->elements[Q->rear-1];

    return 0;
}

int 
queue_a_size(queue_a *Q)
{
    return Q->size;
}

int 
queue_a_capacity(queue_a *Q) 
{
    return Q->capacity;
}

int 
queue_a_is_empty(queue_a *Q)
{
    if(Q->size == 0)                 //reset the positions to 0
    {
        Q->front = Q->rear = 0;
    }
    return Q->size == 0;
}

int 
queue_a_is_full(queue_a *Q)
{
    return Q->size == Q->capacity;
}

/*** Linked List representation of the queue, named, queue ***/


typedef struct queue_node_  //for LL representation of queue, named, queue
{
    void* data;
    struct queue_node_ *next;
}queue_node;

struct queue_                //for LL representation of queue, named, queue
{
    int size;
    queue_node *front, *rear;
};

//typedef struct queue_ queue; 
//typedef struct queue_* queue_ptr;

queue* 
queue_create() 
{
    queue *Q = (queue*)malloc(sizeof(queue));
    Q->size = 0;
    Q->front = Q->rear = NULL;

    return Q;
}

void 
queue_destroy(queue *Q)
{
    Q->size = 0;
    while(Q->front != NULL)
    {
        queue_node *temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    }
    Q->front = Q->rear = NULL;
}

void 
queue_enqueue(queue *Q, void* data)
{
    Q->size++;

    queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
    new_node->data = data;
    new_node->next = NULL;
    
    if(Q->rear == NULL)
    {
        Q->front = Q->rear = new_node;
    }
    else
    {
        Q->rear->next = new_node;
        Q->rear = new_node;
    }

}

void 
queue_dequeue(queue *Q)
{
    if(queue_is_empty(Q))
    {
        fprintf(stderr, "Q is empty, dequeue failed...\n");
    }
    else
    {
        queue_node *temp = Q->front;
        Q->front = Q->front->next;

        free(temp);
        Q->size--;

    }

    if(Q->front == NULL)
        Q->rear = NULL;
}

void* 
queue_front(queue *Q)
{
    if(queue_is_empty(Q))
    {   
        fprintf(stderr, "Q is empty, front_queue failed...\n");
        return INT_MAX;
    }
    else
        return Q->front->data;   
}

void*
queue_rear(queue *Q)
{
    if(queue_is_empty(Q))
    {
        fprintf(stderr, "Q is empty, rear_queue failed...\n");
        return INT_MAX;
    }
    else
        return Q->rear->data;
}

int 
queue_size(queue *Q)
{
    return Q->size;
}

int 
queue_is_empty(queue *Q)
{
    return Q->size == 0;
}

//int capacity_queue(queue *Q)
//int is_full_queue(queue *Q)


