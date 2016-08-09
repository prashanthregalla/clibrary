#ifndef PR_LINKED_LIST_H
#define PR_LINKED_LIST_H

#include "global_vars_pr.h"

typedef struct node_sll_
{
    void* data;
    struct node_sll_ *next;
}node_sll;

typedef struct slist_
{
    int size;
    int (*compare)(void*, void*);   //this is used for finding whether the element matches or not
    node_sll *head;
    node_sll *tail;
}slist;

//typedef slist SLIST; //use this in programs, might have to change it to SLIST_PR in future

slist* slist_create(compare_pr compare);
void slist_destroy(slist *SLL);

void slist_insert_first(slist *SLL, void* elem);
void slist_insert_last(slist *SLL, void* elem);

node_sll* slist_find_prev(slist *SLL, void* elem);
void slist_insert_after(slist *SLL, void* after, void* elem);
void slist_insert_before(slist *SLL, void* before, void* elem);

node_sll* slist_find(slist *SLL, void* elem);
void slist_delete(slist *SLL, void* elem);

int slist_size(slist *SLL);
compare_pr slist_compare(slist *SLL); //returns the compare function, which was provided at the time of creation

void slist_change_compare(slist *SLL, compare_pr new_compare);

#endif
