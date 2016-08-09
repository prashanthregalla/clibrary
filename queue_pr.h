/*** QUEUE DST ****/

#ifndef PR_QUEUE_DST_H
#define PR_QUEUE_DST_H

/*** Array representation of a queue...named queue_a ***/

typedef struct queue_a queue_a;
typedef struct queue_a* queue_a_ptr;

queue_a* queue_a_create(int max_elem);
void queue_a_destroy(queue_a *Q);

void queue_a_enqueue(queue_a *Q, int elem);
int queue_a_dequeue(queue_a *Q);

int queue_a_front(queue_a *Q);
int queue_a_rear(queue_a *Q);

int queue_a_size(queue_a *Q);
int queue_a_capacity(queue_a *Q);

int queue_a_is_empty(queue_a *Q);
int queue_a_is_full(queue_a *Q);

/*** Linked List representation of the queue, named, queue ***/

typedef struct queue_ queue;
typedef struct queue_* queue_ptr;
//typedef queue QUEUE;            //use this in programs, might need to change it to QUEUE_PR in future

queue* queue_create();
void queue_destroy(queue *Q);

void queue_enqueue(queue *Q, void* data);
void queue_dequeue(queue *Q);
void* queue_front(queue *Q);
void* queue_rear(queue *Q);

int queue_size(queue *Q);
int queue_is_empty(queue *Q);

//int capacity_queue(queue *Q);
//int is_full_queue(queue *Q);

/*** PRIORITY QUEUE , which can have max and min priority queues ***/

//For PRIORITY QUEUE

typedef struct pri_queue_ pri_queue;
typedef struct pri_queue_* pri_queue_ptr;

struct pri_queue_data_t
{
        int priority;
        void* pri_queue_content;
};
    
typedef struct pri_queue_data_t pri_queue_data;

typedef int (*compare_pr)(void*, void*);

typedef enum PRQ_TYPE
{ 
    MIN_PRI_Q, 
    MAX_PRI_Q, 
    PRQ_DESTROYED
} prq_type; 


int pri_queue_compare(void* p1, void* p2); //will be used by heapify functions
pri_queue* pri_queue_create(int max_elem, prq_type q_type); // 0: MIN_PRI_Q, 1: MAX_PRI_Q , is type of PR_Q
void pri_queue_destroy(pri_queue *PRQ);

void pri_queue_enqueue(pri_queue *PRQ, pri_queue_data elem, prq_type type);
pri_queue_data pri_queue_dequeue(pri_queue *PRQ);

int pri_queue_type(pri_queue *PRQ); // 0: MIN_PRI_Q, 1: MAX_PRI_Q

pri_queue_data pri_queue_extract_min(pri_queue *PRQ); //will do nothing if its a min_pr_q, logs to stderr ofcourse
pri_queue_data pri_queue_extract_max(pri_queue *PRQ); //will log error if its a max_pr_q

pri_queue_data pri_queue_peek_max(pri_queue *PRQ); //will do nothing if its a min_pr_q, logs ofcourse
pri_queue_data pri_queue_peek_min(pri_queue *PRQ); //will log error if its a max_pr_q

int pri_queue_size(pri_queue *PRQ);
int pri_queue_capacity(pri_queue *PRQ);

int pri_queue_is_empty(pri_queue *PRQ);
int pri_queue_is_full(pri_queue *PRQ);

void pri_queue_increase_key(pri_queue *PRQ, int index, int new_pri_val); //will do nothing if its a min_pr_q, logs ofcourse
void pri_queue_decrease_key(pri_queue *PRQ, int index, int new_pri_val); //will log error if its a max_pr_q

#endif
