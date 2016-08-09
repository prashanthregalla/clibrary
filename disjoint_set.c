/*** DISJOINT_SET DATA STRUCTURE ***/

#include "disjoint_set_pr.h" 
#include<stdio.h>

int
djset_root(int *parent, int i)
{
    int res;

    if(parent[i] == i)
        return i;
    else
    {
        res = djset_root(parent, parent[i]);
        parent[i] = res;            //path compression here, updating the parent to the set's root/representative

        return res;

    }

}


int
djset_in_same(int *parent, int A, int B)
{
    return djset_root(parent, A) == djset_root(parent, B); //will return 1 if they are in same set, else 0
}

int
djset_are_connected(int *parent, int A, int B) // a different name for in_same_set
{
    return djset_in_same(parent, A, B);
}

static void 
normal_union(int *parent, int A ,int B)
{
    int root_A = djset_root(parent, A);
    int root_B = djset_root(parent, B);

     if (root_A == root_B) //already in the same set, nothing to do here
         return;

    parent[ root_A ] = root_B ;       //setting parent of djset_root(int *parent, A) as root(int *parent, B).
}


static void
update_rank(int *rank, int leader, int other, int rank_update)
{
    if(rank_update == 0) //nothing to do
        return;
    else if(rank_update > 0) //need to increase the leaders rank with the value of other's, rank[leader]+=rank[other]
        rank[leader] += rank[other];
    else
        rank[leader] -= rank[other];
}

static void
weighted_union(int *parent, int A,int B, int rank_update, int *rank)
{
    int root_A = djset_root(parent, A);
    int root_B = djset_root(parent, B);

    if (root_A == root_B) //already in same set
       return;

    if(rank[root_A] < rank[root_B ])
    {
        parent[ root_A ] = parent[root_B];
        //rank[root_B] += rank[root_A];
        update_rank(rank, root_B, root_A, rank_update);
    }
    else //if(rank[root_A] > rank[root_B ])
    {
        parent[ root_B ] = parent[root_A];
        //rank[root_A] += rank[root_B];
        update_rank(rank, root_A, root_B, rank_update);
    }

}

// if with_rank=1, rank will be considered among A and B, bigger rank will be the leader
// if with_rank=0, B will be the leader

//rank_update is for what to with ranks, if it is 0, no change is rank array
//if it is >0, rank[leader] will be added with the rank of the other
//if it is <0, rank[leader] will be subtracted with the rank of the other

// rank is the rank array, NULL if with_rank is 0

int
djset_union(int *parent, int A, int B, int with_rank, int rank_update, int *rank)
{
    if(with_rank == 0)
        normal_union(parent, A, B);
    else if(with_rank == 1 && rank == NULL)  //rank array is NULL, ERROR
        return -1;
    else 
        weighted_union(parent, A, B, rank_update, rank);
    
    return 0;
}


