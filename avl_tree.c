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


typedef struct BST_NODE avltree;

static tree_node* tree_insert_avltree(tree_node *root, int data);
static tree_node* tree_delete_avltree(tree_node *root, int data);
static void avltree_update_height(tree_node* node);
static tree_node* avltree_right_rotate(tree_node *y);
static tree_node* avltree_left_rotate(tree_node *x);
static int avltree_get_balance(tree_node* node);    //returns the diff between left and right heightoid
//static int avltree_node_height(tree_node* node);
static tree_node* tree_min_avltree(tree_node *root);
static tree_node* tree_max_avltree(tree_node *root);

static tree_node*
tree_min_avltree(tree_node *root)
{
        if(!root)   //empty
            return NULL;

        tree_node *pfly = root;
        while(pfly->left != 0)
            pfly = pfly->left;

        return pfly; //this is the left most node(max) 
}

static tree_node*
tree_max_avltree(tree_node *root)
{
    if(root == 0)   //empty
        return NULL;

    tree_node *pfly = root;
    while(pfly->right != 0)
        pfly = pfly->right;

    //BST->max = pfly->data;
    return pfly; //this is the right most node(max)

}

static void
avltree_update_height(tree_node* node)
{
    tree_update_height(node);
}

static tree_node*
avltree_right_rotate(tree_node *y)
{
    tree_node* x = y->left;
    tree_node* xright = x->right;

    x->right = y;
    y->left = xright;

    //now lets update the heights too

   // y->height =  avltree_node_height(y->left) + avltree_node_height(y->right) + 1;
   // x->height = avltree_node_height(x->left) + avltree_node_height(x->right) + 1;

    avltree_update_height(y);
    avltree_update_height(x);

    return x;
}


static tree_node*
avltree_left_rotate(tree_node *x)
{
    tree_node* y = x->right;
    tree_node* yleft = y->left;

    y->left = x;
    x->right = yleft;

    //now lets update the heights too

    //x->height = avltree_node_height(x->left) + avltree_node_height(x->right) + 1;
    //y->height =  avltree_node_height(y->left) + avltree_node_height(y->right) + 1;
    avltree_update_height(x);
    avltree_update_height(y);

    return y;
}

static int
avltree_get_balance(tree_node* node)    //returns the diff between left and right height
{
    if(node == NULL)
        return 0;
    return tree_node_height(node->left) - tree_node_height(node->right);
}

static tree_node*
tree_insert_avltree(tree_node* root, int key)
{
    if(root == NULL)
        return tree_create_node(key);

    if(key < root->data)
        root->left = tree_insert_avltree(root->left, key);
    else if(key > root->data)
        root->right = tree_insert_avltree(root->right, key);
    else    //duplicate
        root->count++;
            //return root;
        

    //now see if this insert did any damage to the balance of the tree
    avltree_update_height(root);
    int balance = avltree_get_balance(root);

    if(balance > 1)   //left left case or left right case
    {
        if(key < root->left->data)   //left left case
        {
            return avltree_right_rotate(root);
        }
        else   //left right case
        {
            root->left = avltree_left_rotate(root->left);
            return avltree_right_rotate(root);
        }
    }

    if(balance < -1)  //right right case or right left case
    {
        if(key > root->right->data)  //right right case
            return avltree_left_rotate(root);
        else  //right left case
        {
            root->right = avltree_right_rotate(root->right);
            return avltree_left_rotate(root);
        }
    }

    return root;
}

static tree_node*
tree_delete_avltree(tree_node* root, int key)
{
    if(root == NULL)
        return NULL;  //nothing to do here

    if(key < root->data)
        root->left = tree_delete_avltree(root->left, key);
    else if(key > root->data)
        root->right = tree_delete_avltree(root->right, key);
    else  //this is the key to be deleted
    {
        if(root->count > 1)
        {
            root->count--;
            return root;
        }
        else
        {
            if(root->left == NULL && root->right == NULL)  //leaf node
            {
                tree_node *temp = root;
                root = NULL;
                FREE(temp);
                //return root;
            }
            else if(root->left == NULL)  //only right child present
            {
                root->data = root->right->data;
                root->count = root->right->count;
                FREE(root->right);
                //return root;
            }
            else if(root->right == NULL)  //only left child present
            {
                root->data = root->left->data;
                root->count = root->left->count;

                FREE(root->left);
               // return root;
            }
            else  //it has both children
            {
                tree_node* right_min = tree_min_avltree(root->right);
                root->data = right_min->data;
                root->count = right_min->count;

                root->right = tree_delete_avltree(root->right, root->data);

                //return root;
            }
        }
    } //deletion over, lets check the balance property

    if(root == NULL)
        return root;

    avltree_update_height(root);

    int balance = avltree_get_balance(root);

    if(balance > 1)  //left left or left right
    {
        if(avltree_get_balance(root->left) >=0) //left left
            return avltree_right_rotate(root);
        else  //left right
        {
            root->left = avltree_left_rotate(root->left);
            return avltree_right_rotate(root);
        }
    }

    if(balance < -1)  //right right or right left
    {
        if(avltree_get_balance(root->right) <=0) //right right
            return avltree_left_rotate(root);
        else   //right left
        {
            root->right = avltree_right_rotate(root->right);
            return avltree_left_rotate(root);
        }

    }

    return root;
}


/* AVLT ADT */

avltree* 
avltree_create()
{
    /*avltree *new_node = MALLOC(avltree);

    new_node->size = 0;
    new_node->height = -1; //empty AVLT, height of leaf node will be 0, like what we did for normal binary tree
    new_node->max = INT_MAX;
    new_node->min = INT_MIN;
    new_node->median = 0;  //means tree is empty 
    new_node->root = NULL;

    return new_node;   
    */
    return bst_create();
}

void 
avltree_destroy(avltree *AVLT)
{
    /*AVLT->size = AVLT->max = AVLT->min = AVLT->median = 0;
    AVLT->height = -1;
    tree_destroy(AVLT->root);

    AVLT->root = NULL;  //this will be done by tree_delete, but to be safe doing here too
    FREE(AVLT);  //free the memoty pointed by this node too
    */

    bst_destroy(AVLT);
}

int
avltree_is_empty(avltree *AVLT)
{
    return AVLT->size == 0;
}

int avltree_is_mirror(avltree *AVLT)
{
    return tree_is_mirror(AVLT->root);
}

int 
avltree_count_key(avltree *AVLT, int key)
{
    return bst_count_key(AVLT, key);
}

int 
avltree_insert(avltree *AVLT, int data)
{
    if((AVLT->root = tree_insert_avltree(AVLT->root, data)) == NULL)  //it should not return NULL at any point, but to be safer   
       return -1;
    else
    {
        AVLT->size++;

        return 0; //SUCCESSFULLY INSERTED(ofcourse!) 

    }
}

tree_node* 
avltree_find(avltree *AVLT, int data)
{
   return bst_find(AVLT, data);   
} 


int 
avltree_delete(avltree *AVLT, int data)
{
    tree_delete_avltree(AVLT->root, data); 
    return 0;  //SUCCESS

}


tree_node* 
avltree_max(avltree *AVLT)
{
    //tree_node *pfly = 

    return bst_max(AVLT);

   // if(pfly == NULL)
     //   return 0;
    
    //AVLT->max = pfly->data;
    //return AVLT->max; //this is the right most node(max)

}

tree_node*
avltree_min(avltree *AVLT)
{
    
    //tree_node *pfly = 
    return bst_min(AVLT);
    
   // if(pfly == NULL)
     //   return 0;

    //AVLT->min = pfly->data;
    //return AVLT->min; //this is the left most node(max) 
}

int 
avltree_median(avltree *AVLT)
{
        return AVLT->median;        
}


int 
avltree_size(avltree *AVLT)
{
    return AVLT->size;
}

int 
avltree_height(avltree *AVLT)
{
    return AVLT->height;
}


tree_node*
avltree_inorder_successor(avltree *AVLT, int data)
{
    return bst_inorder_successor(AVLT, data);
}

tree_node*
avltree_inorder_predecessor(avltree *AVLT, int data)
{
    return bst_inorder_predecessor(AVLT, data);
}


void 
avltree_print(avltree *AVLT, TREE_TRAV type)
{
   
    bst_print(AVLT, type);
    /*
    * switch(type)
    {
        case INORDER:
            printf("AVLT InOrder: ");
            tree_inorder(AVLT->root);

            break;

        case PREORDER:
            printf("AVLT PreOrder: ");
            tree_preorder(AVLT->root);

            break;

        case POSTORDER:
            printf("AVLT PostOrder: ");
            tree_postorder(AVLT->root);

            break;

        case LEVELORDER:
            printf("AVLT LevelOrder: ");
            tree_levelorder(AVLT->root);

            break;

        default:
           tree_print(AVLT->root, INORDER);
           tree_print(AVLT->root, PREORDER);
           tree_print(AVLT->root, POSTORDER);
           tree_print(AVLT->root, LEVELORDER);

           break;
    }
    
    printf("\n");
    */

      
}

// PRINT ROUTINES

int 
avltree_print_count_key(avltree *AVLT, int key)
{
    printf("Key %d appears %d times in the AVLT\n", key, avltree_count_key(AVLT, key));   
}

int 
avltree_print_min(avltree *AVLT)
{
    tree_node *min_node;
    int min;

    if( (min_node = avltree_min(AVLT)) == NULL)
        min = 0;
    else
        min = min_node->data;

    AVLT->min = min;
    printf("AVLT MIN is : %d\n", min);
}

int 
avltree_print_max(avltree *AVLT)
{
    tree_node *max_node;
    int max;

    if( (max_node = avltree_max(AVLT)) == NULL)
        max = 0;     
    else               
        max = max_node->data;

    AVLT->max = max;
    printf("AVLT MAX is : %d\n", max);

}

int 
avltree_print_median(avltree *AVLT)
{
    printf("AVLT MEDIAN is : %d\n",avltree_median(AVLT));
}
    
int 
avltree_print_size(avltree *AVLT)
{
    printf("AVLT Size is : %d\n",avltree_size(AVLT));
}

int 
avltree_print_height(avltree *AVLT)
{
    printf("AVLT Height is : %d\n",avltree_height(AVLT));
}

int 
avltree_print_inorder_successor(avltree *AVLT, int data)
{
    tree_node *successor;
    int inorder_succ;

    if((successor = avltree_inorder_successor(AVLT, data)) == NULL)
        inorder_succ = INT_MAX;
    else
        inorder_succ = successor->data;

    printf("Inorder Successor of %d is %d\n", data, inorder_succ);
}

int
avltree_print_inorder_predecessor(avltree *AVLT, int data)
{
    tree_node *predecessor;
    int inorder_pred;

    if((predecessor = avltree_inorder_predecessor(AVLT, data)) == NULL)
        inorder_pred = INT_MIN;
    else
        inorder_pred = predecessor->data;

    printf("Inorder Predecessor of %d is %d\n", data,inorder_pred);
}

int 
avltree_is_height_balanced(avltree *AVLT)
{
    return tree_is_height_balanced(AVLT->root);  
}

/* Function to find LCA of n1 and n2. The function assumes that both
   n1 and n2 are present in AVLT . OR we can check if both of these exist before entering this*/
tree_node*
avltree_lca(avltree *AVLT, int n1, int n2)
{
    /*
     * if (root == NULL) return NULL;
 
    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (root->data > n1 && root->data > n2)
        return lca(root->left, n1, n2);
 
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->data < n1 && root->data < n2)
        return lca(root->right, n1, n2);
 
    return root;
    */
    
    return bst_lca(AVLT, n1, n2);
}

avltree*
avltree_construct(int *array, int size) //construct AVL_TREE from a array, keep on inserting until the end of array
{   
    avltree *new_avltree = avltree_create();
    assert(new_avltree != 0);
    
    //merge_sort(array, size);   //see how the avltree looks like when sorted array is given
    for(int i=0; i<size; i++)
        avltree_insert(new_avltree, array[i]);
    
    new_avltree->size = tree_size(new_avltree->root);  //it should simply be size but there may be duplicates too
                                               //in that case size will be different, counting duplicates only once
    new_avltree->height = tree_height(new_avltree->root);
    
    tree_node *temp = tree_min_avltree(new_avltree->root);
    if(temp)
        new_avltree->min = temp->data;
    
    temp = tree_max_avltree(new_avltree->root);
    if(temp)
        new_avltree->max = temp->data;


    return new_avltree;

}
