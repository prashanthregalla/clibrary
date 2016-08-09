#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tree_pr.h"
#include "global_vars_pr.h"
#include <limits.h>
#include "helper_fns_pr.h"

#define LEFT(node) ((2*node)+1)
#define RIGHT(node) ((2*node)+2)

struct segtree_node
{
    
    int size;  //array_size
    int *orig_array;  //this is the array provided to us initially, also modify this whenever there are updates
    int *segtree_array;
    int segtree_size; //segment tree size
    segtree_op seg_op;
    int boundary_val;
};

typedef struct segtree_node segtree;


static void segtree_build_helper(segtree *ST, int node, int begin, int end);
static int segtree_query_helper(segtree* ST, int node, int begin, int end, int l, int r);
static void segtree_update_range_helper(segtree* ST, int node, int begin, int end, int l, int r, int val);

segtree*
segtree_create(int *array, int size, segtree_op operation, int boundary_val)
{
    segtree* ST = MALLOC(segtree);

    int t = (int) ceil(log2(size));
    int max_nodes = 2 * (int) pow(2, t) + 1;

    ST->size = size;
    ST->segtree_size = max_nodes;
    ST->segtree_array = CALLOC(max_nodes, int);

    ST->orig_array = MALLOC_ARRAY(size, int);

    copy_array(array, ST->orig_array, size); // no need to do this but just to preserve the original array
    ST->seg_op = operation;
    ST->boundary_val = boundary_val;
    segtree_build_helper(ST, 0, 0, size-1);
    return ST;
}

void
segtree_destroy(segtree* ST)
{
    ST->size = 0;
    FREE(ST->orig_array);
    FREE(ST->segtree_array);
    ST->seg_op = NULL;
}

void
segtree_print(segtree *ST)  //print the segtree_array
{
    print_array(ST->segtree_array, ST->segtree_size);
}
    
int
segtree_query(segtree* ST, int l, int r)
{
    return segtree_query_helper(ST, 0, 0, ST->size - 1, l, r);
}

void
segtree_update_range(segtree* ST, int l, int r, int val)
{
    segtree_update_range_helper(ST, 0, 0, ST->size - 1, l, r, val);
}


static void
segtree_build_helper(segtree *ST, int node, int begin, int end)
{
    if(begin == end) //leaf node
    {
        ST->segtree_array[node] = ST->orig_array[begin];
        return NULL;
    }   
    
    int mid = begin + (end - begin)/2;
    segtree_build_helper(ST, LEFT(node), begin, mid);
    segtree_build_helper(ST, RIGHT(node), mid+1, end);

    ST->segtree_array[node] = ST->seg_op(ST->segtree_array[LEFT(node)] , ST->segtree_array[RIGHT(node)]);
}
    


static int 
segtree_query_helper(segtree* ST, int node, int begin, int end, int l, int r)
{
    //if(begin == end)  //leaf node
      //  return ST->segtree_array[begin];

    if(r < begin || l > end) //this node is not in the range of l and r
        return ST->boundary_val;

    if(l <= begin && r>= end)  //in the range
       return ST->segtree_array[node];

   //partially in the range
 //  if(begin > l || end < r) 
  // {
       int mid = begin + (end - begin)/2;
       int lt = segtree_query_helper(ST, LEFT(node), begin, mid, l, r);
       int rt = segtree_query_helper(ST, RIGHT(node), mid+1, end, l, r);
       //if(lt == INT_MAX && rt == INT_MAX)
       //    return INT_MAX;
       //if(lt == INT_MAX)
         //  return rt;
       //else
           
       return ST->seg_op(lt, rt);
   // }
         
}

static void 
segtree_update_range_helper(segtree* ST, int node, int begin, int end, int l, int r, int val)
{
    if(begin > end || r < begin || l > end)  //out of range, no update to do here
        return;

    if(begin == end) //leaf node, update it now
    {
        ST->orig_array[begin] += val; //update the original array
        ST->segtree_array[node] += val; //update the segtree   
        return NULL; 
    }
    
    int mid = begin + (end - begin)/2;
    segtree_update_range_helper(ST, LEFT(node), begin, mid, l, r, val);
    segtree_update_range_helper(ST, RIGHT(node), mid+1, end, l, r, val);

    ST->segtree_array[node] = ST->seg_op(ST->segtree_array[LEFT(node)] , ST->segtree_array[RIGHT(node)]);

}

int*
segtree_orig_array(segtree *ST)   //this will give the pointer to the array after all modifications, in case you need it
{
    return ST->orig_array;
}
