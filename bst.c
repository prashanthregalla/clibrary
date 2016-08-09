#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "tree_pr.h"
#include "global_vars_pr.h"
#include "helper_fns_pr.h"
#include "queue_pr.h"
#include "stack_pr.h"
#include <assert.h>
#include "sorting_pr.h"

struct BST_NODE
{
    int height;
    int size;
    int max;
    int min;
    int median;
    tree_node *root;
};


typedef struct BST_NODE bst;

static tree_node* tree_min_bst(tree_node *root);
static tree_node* tree_max_bst(tree_node *root);
static tree_node* tree_inorder_predecessor_bst(tree_node* root, int key);
static tree_node* tree_inorder_successor_bst(tree_node *root, int key);

static tree_node* tree_delete_bst(tree_node *root, int key); //will return the root of new tree(if the old one is deleted) 
static tree_node* tree_insert_bst(tree_node *root, int data);  //always return the root
static int tree_count_key_bst(tree_node* root, int key);
static tree_node* tree_search_bst(tree_node *root, int data);
static tree_node* tree_find_bst(tree_node *root, int data);


/* BINARY SEARCH TREE---coded using two approaches
 *  * 1. pass root and data ...like how we do it in usual
 *   * 2. BST ADT---this will be useful in other programs too
 *    */


static tree_node*
tree_find_bst(tree_node *root, int data)
{
    if(root == NULL || root->data == data)  //data not present || data matches
        return root;                          
    if(data < root->data)
        return tree_find_bst(root->left, data);
    else
        return tree_find_bst(root->right, data);
}

static tree_node*
tree_search_bst(tree_node *root, int data)
{
     
    return tree_find_bst(root, data);
}

static int 
tree_count_key_bst(tree_node* root, int key)
{
    if(root == NULL)
        return 0;
    if(root->data == key)
        return root->count;
    else if(key < root->data)
        return tree_count_key_bst(root->left, key);
    else return tree_count_key_bst(root->right, key);
}



static tree_node*
tree_insert_bst(tree_node *root, int data)  //always return the root
{
    if(root == NULL) //empty tree
    {
        tree_node *new_node = tree_create_node(data);
        //new_node->count = 1;
        return new_node;
    }
    
    if(root->data == data)
        root->count++;   //multiple occurrence of this data, increment the count
    else if(data < root->data)
        root->left = tree_insert_bst(root->left, data);
    else 
        root->right = tree_insert_bst(root->right, data);

    return root;
       
}

static tree_node*
tree_delete_bst(tree_node *root, int key)  //will return the root of new tree(if the old one is deleted) or else original root
{
    if(root == NULL)
        return root;
    
    if(key < root->data)
        root->left = tree_delete_bst(root->left, key);
    else if (key > root->data)
         root->right = tree_delete_bst(root->right, key);
    else  //this is the node to be deleted
    {
        if(root->count > 1)  //more than one occurrence, decrement the count and return
        {
            root->count--;
            return root;
        }
        else  //only one time present
        {
            if(root->left == NULL)   //return the right child to parent
            {
                tree_node *temp = root->right;
                FREE(root);
                return temp;
            }
            else if(root->right == NULL) //return the left child to parent
           {
                tree_node *temp = root->left;
                FREE(root);
                return temp;
            }
            else   //has both childs, left and right, now find the minimu value on right, copy data to root and delte min node
            {
                tree_node *min_node = tree_min_bst(root->right);
                root->data = min_node->data;  //min_node will always be non_empty, as it can always be itself
                root->count = min_node->count;  //copy the count data too

                min_node->data = 1; 
                root->right = tree_delete_bst(root->right, min_node->data);
                        
            }
        }
    }
       
    return root;
}


static tree_node* 
tree_inorder_successor_bst(tree_node *root, int key)
{
    if(root == NULL)
        return root;

    tree_node *succ = NULL;

    while(root != NULL && root->data != key)
    {
        if(key < root->data)
        {
            succ = root;
            root = root->left;
        }
        else if(key > root->data)
            root = root->right;
    }   //while end, either we have found the key or not    
    
    if(root != NULL)
    {
        if(root->right)
            return tree_min_bst(root->right);
        else
            return succ;
    }
    return succ;

}

static tree_node* 
tree_inorder_predecessor_bst(tree_node* root, int key)
{
    if(root == NULL)
        return root;

    tree_node *pred = NULL;

    while(root != NULL && root->data != key)
    {                   
        if(key > root->data)
        {               
            pred = root;
            root = root->right;
        }               
        else if(key < root->data)           
            root = root->left;
    }   //while end, either we have found the key or not    
                                 
    if(root != NULL)             
    {                            
        if(root->right)          
            return tree_max_bst(root->left);
        else
            return pred;
    }
    return pred;
}


static tree_node* 
tree_max_bst(tree_node *root)
{
    if(root == 0)   //empty
        return NULL;
    
    tree_node *pfly = root;
    while(pfly->right != 0)
        pfly = pfly->right;

    //BST->max = pfly->data;
    return pfly; //this is the right most node(max)

}

static tree_node*
tree_min_bst(tree_node *root)
{
    if(!root)   //empty
        return NULL;
    
    tree_node *pfly = root;
    while(pfly->left != 0)
        pfly = pfly->left;

    //BST->min = pfly->data;
    return pfly; //this is the left most node(max) 
}


/* BST ADT */

typedef struct BST_NODE bst; //BST ADT, this is what we return(a pointer to it ofcourse
                            // might need to change it to BST_PR in future(!!??)


int 
bst_is_height_balanced(bst *BST)
{
    return tree_is_height_balanced(BST->root);  
}

/* Function to find LCA of n1 and n2. The function assumes that both
   n1 and n2 are present in BST . OR we can check if both of these exist before entering this*/
static tree_node*
tree_lca_bst(tree_node* root, int n1, int n2)
{
    if (root == NULL) return NULL;
 
    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (root->data > n1 && root->data > n2)
        return tree_lca_bst(root->left, n1, n2);
 
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->data < n1 && root->data < n2)
        return tree_lca_bst(root->right, n1, n2);
 
    return root;
}

tree_node*
bst_lca(bst *BST, int n1, int n2)
{
    return tree_lca_bst(BST->root, n1, n2);
}
    
bst* 
bst_create()
{
    bst *new_node = MALLOC(bst);

    new_node->size = 0;
    new_node->height = 0; //empty BST, height of leaf node will be 0, like what we did for normal binary tree
    new_node->max = INT_MAX;
    new_node->min = INT_MIN;
    new_node->median = 0;  //means tree is empty 
    new_node->root = NULL;

    return new_node;   
}

void 
bst_destroy(bst *BST)
{
    BST->size = BST->max = BST->min = BST->median = 0;
    BST->height = -1;
    tree_destroy(BST->root);

    BST->root = NULL;  //this will be done by tree_delete, but to be safe doing here too
    FREE(BST);  //free the memoty pointed by this node too
}

int
bst_is_empty(bst *BST)
{
    return BST->size == 0;
}

int bst_is_mirror(bst *BST)
{
    return tree_is_mirror(BST->root);
}

int 
bst_count_key(bst *BST, int key)
{
    return tree_count_key_bst(BST->root, key);
}

int 
bst_insert(bst *BST, int data)
{
    if((BST->root = tree_insert_bst(BST->root, data)) == NULL)  //it should not return NULL at any point, but to be safer   
       return -1;
    else
    {
        BST->size++;

        return 0; //SUCCESSFULLY INSERTED(ofcourse!) 

    }
}

tree_node* 
bst_find(bst *BST, int data)
{
   return tree_find_bst(BST->root, data);   
} 


int 
bst_delete(bst *BST, int data)
{
    tree_delete_bst(BST->root, data); 
        return 0;  //SUCCESS

}


tree_node* 
bst_max(bst *BST)
{
    //tree_node *pfly = 

    return tree_max_bst(BST->root);

   // if(pfly == NULL)
     //   return 0;
    
    //BST->max = pfly->data;
    //return BST->max; //this is the right most node(max)

}

tree_node*
bst_min(bst *BST)
{
    
    //tree_node *pfly = 
    return tree_min_bst(BST->root);
    
   // if(pfly == NULL)
     //   return 0;

    //BST->min = pfly->data;
    //return BST->min; //this is the left most node(max) 
}

int 
bst_median(bst *BST)
{
        return BST->median;        
}


int 
bst_size(bst *BST)
{
    return BST->size;
}

int 
bst_height(bst *BST)
{
    return BST->height;
}


tree_node*
bst_inorder_successor(bst *BST, int data)
{
    return tree_inorder_successor_bst(BST->root, data);
}

tree_node*
bst_inorder_predecessor(bst *BST, int data)
{
    return tree_inorder_predecessor_bst(BST->root, data);
}


void 
bst_print(bst *BST, TREE_TRAV type)
{
   switch(type)
    {
        case INORDER:
            printf("BST InOrder: ");
            tree_inorder(BST->root);

            break;

        case PREORDER:
            printf("BST PreOrder: ");
            tree_preorder(BST->root);

            break;

        case POSTORDER:
            printf("BST PostOrder: ");
            tree_postorder(BST->root);

            break;

        case LEVELORDER:
            printf("BST LevelOrder: ");
            tree_levelorder(BST->root);

            break;

        default:
           tree_print(BST->root, INORDER);
           tree_print(BST->root, PREORDER);
           tree_print(BST->root, POSTORDER);
           tree_print(BST->root, LEVELORDER);

           break;
    }
    
    printf("\n");
      
}

// PRINT ROUTINES

int 
bst_print_count_key(bst *BST, int key)
{
    printf("Key %d appears %d times in the BST\n", key, bst_count_key(BST, key));   
}

int 
bst_print_min(bst *BST)
{
    tree_node *min_node;
    int min;

    if( (min_node = bst_min(BST)) == NULL)
        min = 0;
    else
        min = min_node->data;

    BST->min = min;
    printf("BST MIN is : %d\n", min);
}

int 
bst_print_max(bst *BST)
{
    tree_node *max_node;
    int max;

    if( (max_node = bst_max(BST)) == NULL)
        max = 0;     
    else               
        max = max_node->data;

    BST->max = max;
    printf("BST MAX is : %d\n", max);

}

int 
bst_print_median(bst *BST)
{
    printf("BST MEDIAN is : %d\n",bst_median(BST));
}
    
int 
bst_print_size(bst *BST)
{
    printf("BST Size is : %d\n",bst_size(BST));
}

int 
bst_print_height(bst *BST)
{
    printf("BST Height is : %d\n",bst_height(BST));
}

int 
bst_print_inorder_successor(bst *BST, int data)
{
    tree_node *successor;
    int inorder_succ;

    if((successor = bst_inorder_successor(BST, data)) == NULL)
        inorder_succ = INT_MAX;
    else
        inorder_succ = successor->data;

    printf("Inorder Successor of %d is %d\n", data, inorder_succ);
}

int
bst_print_inorder_predecessor(bst *BST, int data)
{
    tree_node *predecessor;
    int inorder_pred;

    if((predecessor = bst_inorder_predecessor(BST, data)) == NULL)
        inorder_pred = INT_MIN;
    else
        inorder_pred = predecessor->data;

    printf("Inorder Predecessor of %d is %d\n", data,inorder_pred);
}


bst* 
bst_construct(int *array, int size) //construct BST from a array, keep on inserting until the end of array
{
    bst *new_bst = bst_create();
    assert(new_bst != 0);
    
    //merge_sort(array, size);   //see how the bst looks like when sorted array is given
    for(int i=0; i<size; i++)
        bst_insert(new_bst, array[i]);
    
    new_bst->size = tree_size(new_bst->root);  //it should simply be size but there may be duplicates too
                                               //in that case size will be different, counting duplicates only once
    new_bst->height = tree_height(new_bst->root);

    tree_node *temp = tree_min_bst(new_bst->root);
    if(temp)
        new_bst->min = temp->data;

    temp = tree_max_bst(new_bst->root);
    if(temp)
        new_bst->max = temp->data;

    
    return new_bst;
    
}


static tree_node*
bst_construct_optimal_utility(int *array, int begin, int end)
{
    if(begin > end)
        return NULL;

    int mid = begin + (end - begin)/2;
    tree_node* root = tree_create_node(array[mid]);
    root->left = bst_construct_optimal_utility(array, begin, mid-1);
    root->right = bst_construct_optimal_utility(array, mid+1, end);

    return root; 
}

bst* 
bst_construct_optimal(int *array, int size) //construct BST with optimal height, sort the array and then construct
{
    bst *BST = bst_create();
    assert(BST != 0);

    merge_sort(array, size);  //just to be safe, the input is supposed to be sorted

    BST->root = bst_construct_optimal_utility(array, 0, size-1);
    BST->size = tree_size(BST->root);
    BST->height = tree_height(BST->root);
    
    tree_node *temp = tree_min_bst(BST->root);
    if(temp)
        BST->min = temp->data;

    temp = tree_max_bst(BST->root);
    if(temp)
        BST->max = temp->data;

    return BST;
}

