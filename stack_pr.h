#ifndef PR_STACK_DST_H
#define PR_STACK_DST_H

/*** Array representation of a stack...named stack_a ***/

typedef struct stack_a stack_a;
typedef struct stack_a* stack_a_ptr;

stack_a* stack_a_create(int max_elem);
void stack_a_destroy(stack_a *S);

void stack_a_push(stack_a *S, int elem);
void stack_a_pop(stack_a *S);
int stack_a_top(stack_a *S);

int stack_a_size(stack_a *S);
int stack_a_capacity(stack_a *S);
int stack_a_is_empty(stack_a *S);
int stack_a_is_full(stack_a *S);

/*** Linked List representation of the stack, named, stack ***/

typedef struct stack_ stack;
typedef struct stack_* stack_ptr;

stack* stack_create();
void stack_destroy(stack *S);

void stack_push(stack *S, void* data);;
void stack_pop(stack *S);
void* stack_top(stack *S);

int stack_size(stack *S);
int stack_is_empty(stack *S);

//int capacity_stack(stack *S);
//int is_full_stack(stack *S);


#endif
