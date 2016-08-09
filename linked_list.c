#include<stdio.h>
#include<stdlib.h>
#include "linked_list_pr.h"
#include <assert.h>
#include "global_vars_pr.h"

typedef int (*compare_t)(void*, void*);

static node_sll* 
create_new_sll_node(void* data)
{
    node_sll *new_node = (node_sll*) malloc(sizeof(node_sll));

    new_node->data = data;
    new_node->next = NULL;
    
    
    return new_node; 
}

slist* 
slist_create(compare_pr my_compare)
{
    slist *SLL = (slist*) malloc(sizeof(slist));
    SLL->size = 0;
    SLL->compare = my_compare;
    SLL->head = NULL;
    SLL->tail = NULL;

    return SLL;
}

void 
slist_destroy(slist *SLL)
{
    SLL->size = 0;
    while(SLL->head != NULL)
    {
        node_sll *temp = SLL->head;
        SLL->head = SLL->head->next;
        free(temp);
    }
    SLL->head = SLL->tail = NULL;
    SLL->compare = NULL;
    free(SLL);
    SLL = NULL;
}


void 
slist_insert_first(slist *SLL, void* elem)  //insert at the beginning
{
    //node_sll *new_node = (node_sll*) malloc(sizeof(node_sll));
    //new_node->data = elem;
    
    node_sll *new_node = create_new_sll_node(elem);
    
    if(SLL->head == NULL)
    {
        SLL->head = SLL->tail = new_node;
    }
    else
    {
        new_node->next = SLL->head;
        SLL->head = new_node;
    }

    SLL->size++;
}

void 
slist_insert_last(slist *SLL, void* elem) //insert at the beginning
{
    node_sll *new_node = create_new_sll_node(elem);
    
    if(SLL->tail == NULL)
        SLL->head = SLL->tail = new_node;
    else
    {
        SLL->tail->next = new_node;
        SLL->tail = new_node;
    }
        
    SLL->size++;
}

void 
slist_insert_after(slist *SLL, void* after_this, void* elem)
{
    node_sll *this_node = slist_find(SLL, after_this);
    if(this_node == NULL) //elem not present in the list
    {
        fprintf(stderr, "This is not present in the list, cant insert after it, inserting at the end instead...\n");
        slist_insert_last(SLL, elem);
    }
    else if(this_node->next == NULL)
    {
        slist_insert_last(SLL, elem);
    }
    else
    {   
        node_sll *new_node = create_new_sll_node(elem);
        node_sll *temp = this_node->next;

        this_node->next = new_node;
        new_node->next = temp;
        SLL->size++;

    }

}   

node_sll*
slist_find_prev(slist *SLL, void* elem)
{
    //assert(SLL);

    node_sll *t_node = SLL->head; //for traversing the list till end
    if(t_node == NULL)
       return NULL;
    else if(SLL->compare(t_node->data, elem) == 0)  //elem is the first element in the list, at head, there's no element before that
        return t_node;
    
    while(t_node->next && !SLL->compare(t_node->next->data, elem) )
    {
            t_node = t_node->next;
            
    }
    
    if(t_node->next == NULL)
        return NULL;
    else
        return t_node;

}

void
slist_insert_before(slist *SLL, void* before_this, void* elem)
{
    node_sll *prev_node = slist_find_prev(SLL, before_this);
    
    if(prev_node == NULL) //elem not present in the list
    {
        fprintf(stderr, "This is not present in the list, cant insert after it, inserting at the beginning\n");
        slist_insert_first(SLL, elem);
    }
    else if(prev_node == SLL->head) //elem was the first element
    {
        slist_insert_first(SLL, elem);
    }
    else
    {
        node_sll *new_node = create_new_sll_node(elem);
        node_sll *temp = prev_node->next;

        prev_node->next = new_node;
        new_node->next = temp;
        SLL->size++;

    }
}

node_sll* 
slist_find(slist *SLL, void* elem)
{
    node_sll *t_node = SLL->head; //for traversing the list till end
    while(t_node)
    {
        if(SLL->compare(t_node->data, elem) == 0)
            return t_node;
        else
            t_node = t_node->next;
    }

    return NULL; //NOT FOUND
}

void 
slist_delete(slist *SLL, void* elem)
{
    node_sll *prev_node = slist_find_prev(SLL, elem);

    if(prev_node == NULL) //elem is not there in the list
    {
        fprintf(stderr, "This is not in the list, cannot delete it...\n");        
    }
    else if(prev_node == SLL->head ) //elem is the first element
    {
        SLL->head = SLL->head->next;
        free(prev_node);
        SLL->size--;
    }
    else
    {
        node_sll *temp = prev_node->next;

        prev_node->next = prev_node->next->next;
        if(prev_node->next == NULL)  //elem was the last element and we have deleted it, need to update the tail now
            SLL->tail = prev_node;
        SLL->size--;
        free(temp);
    }


}

int
slist_size(slist *SLL)
{
        return SLL->size;
}

compare_pr
slist_compare(slist *SLL)
{
    return SLL->compare;
}

void
slist_change_compare(slist *SLL, compare_pr new_compare)
{
    if(new_compare)
        SLL->compare = new_compare;
}
