#ifndef PR_DISJOINT_SET_H
#define PR_DISJOINT_SET_H

#include "global_vars_pr.h"

// if with_rank=1, rank will be considered among A and B, bigger rank will be the leader
// // if with_rank=0, B will be the leader
//
// //rank_update is for what to with ranks, if it is 0, no change is rank array
// //if it is >0, rank[leader] will be added with the rank of the other
// //if it is <0, rank[leader] will be subtracted with the rank of the other
//
// // rank is the rank array, NULL if with_rank is 0

int djset_union(int *parent, int A, int B, int with_rank, int rank_update, int *rank);


int djset_root(int *parent, int i);

int djset_in_same_set(int *parent, int A, int B); //are they in same set, if yes returns 1, else returns 0 

int djset_are_connected(int *parent, int A, int B); // a different name for in_same_set

#endif
