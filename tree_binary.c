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

//Queue for Level Order Traversal

//static void queue_push_tree_node(tree_node *node);
//static tree_node* queue_pop_tree_node();
static void tree_levelorder_utility(tree_node *root, int level); //helper fn. for recursive O(n2) level order
static void tree_levelorder_recursive(tree_node* root);

static int tree_is_height_balanced_util(tree_node *root, int *height);

static tree_node* tree_construct_util_in_pre(int *array1, int *array2);
static tree_node* tree_construct_util_in_post(int *array1, int *array2);
static tree_node* tree_construct_util_in_level(int *array1, int *array2);

static tree_node* 
tree_construct_util_in_pre(int *array1, int *array2)
{

}

static tree_node* 
tree_construct_util_in_post(int *array1, int *array2)
{

}

static tree_node* 
tree_construct_util_in_level(int *array1, int *array2)
{

}

tree_node*
tree_create_node(int data)
{
    tree_node *new_node = MALLOC(tree_node);
    
    new_node->data = data;
    new_node->count = 0;
    new_node->left = new_node->right = NULL;
    new_node->count = 1;
    new_node->height = 0;

    return new_node;
}

tree_node* 
tree_add_node(int data)
{
    return tree_create_node(data);
}

tree_node* tree_insert(int data)
{
    return tree_create_node(data);
}

int 
tree_height(tree_node *root)
{
    if(root == NULL)
        return -1;  //height of leaf node will be 0 here, make it 0(return 0) for making height of leaf to be 1
    else
    {
        int left_ht = tree_height(root->left);
        int right_ht = tree_height(root->right);

        return bigger(left_ht, right_ht) + 1;
    }
}

        
void 
tree_update_height(tree_node* node)
{
    if(node == NULL)
        return;

  /*  int lh = 0, rh = 0;
    
    if(node->left)
        lh = node->left->height;
    else
        lh = -1;

    if(node->right)
        rh = node->right->height;
    else
        rh = -1;
*/
    node->height = bigger(tree_node_height(node->left), tree_node_height(node->right)) + 1;
}

int 
tree_node_height(tree_node* node)
{
    if(node == NULL)
        return -1;

    return node->height;
}

int 
tree_size(tree_node *root)
{
    if(root == NULL)
        return 0;
    else
    {
        int left_size = tree_size(root->left);
        int right_size = tree_size(root->right);

        return left_size + right_size + 1;
    }
}

void
tree_destroy(tree_node *root)
{
    if(root)
    {
        tree_destroy(root->left);
        tree_destroy(root->right);

        FREE(root);
    }
}


void 
tree_print(tree_node* root, TREE_TRAV type)
{
    switch(type)
    {
        case INORDER:
            printf("InOrder: ");
            tree_inorder(root);

            break;

        case PREORDER:
            printf("PreOrder: ");
            tree_preorder(root);

            break;

        case POSTORDER:
            printf("PostOrder: ");
            tree_postorder(root);

            break;

        case LEVELORDER:
            printf("LevelOrder: \n");
            tree_levelorder(root);

            break;

        default: 
           tree_print(root, INORDER);
           tree_print(root, PREORDER);
           tree_print(root, POSTORDER);
           tree_print(root, LEVELORDER);


    }
    printf("\n");
}

void 
tree_print_size(tree_node* root)
{
    printf("Size/NO_elements of this tree is : %d\n", tree_size(root));
}

void 
tree_print_height(tree_node* root)
{
    printf("Height(leaf node's height is 0) of this tree is: %d\n", tree_height(root));
}

void 
tree_inorder(tree_node* root)
{
    if(root != NULL)
    {
        tree_inorder(root->left);
        printf("%d, ", root->data);
        tree_inorder(root->right);

    }
    //printf("\n");
}

void 
tree_preorder(tree_node* root)
{
    if(root != NULL)
    {   
        printf("%d, ", root->data);
        tree_preorder(root->left);
        tree_preorder(root->right);        
    }
    //printf("\n");
}


void 
tree_postorder(tree_node* root)
{
    if(root != NULL)
    {
        tree_postorder(root->left);
        tree_postorder(root->right);
        printf("%d, ",root->data);         
    }
}

void 
tree_inorder_iterative(tree_node* root)
{

}

void 
tree_preorder_iterative(tree_node* root)
{

}

void 
tree_postorder_iterative(tree_node* root)
{

}

static void 
tree_levelorder_recursive(tree_node* root)  //this is without using queue, recursive and O(n2) approach
{
    if(root != NULL)
    {
        int height = tree_height(root);

        for(int i = 1; i <= height+1; i++) //height+1 as the height of leaf node is considered 0
        {
            tree_levelorder_utility(root, i);
            printf("\n");            
        }        
        
    }
}

void tree_levelorder(tree_node *root)
{
    tree_levelorder_iterative(root); //call the one using Queue as its efficient than the recursive one
}

void
tree_levelorder_iterative(tree_node* root)   //Using Queue
{
    //printf("IN LEVEL ORDER ITERATIVE\n");
    //queue_push_tree_node(root);
    queue *Q = queue_create();
    queue_enqueue(Q, (void*)root);
    tree_node *temp;   
    while(1)
    {
        if( queue_is_empty(Q))  //no more nodes in the queue, time to quit
            break;
        int no_level = queue_size(Q);
        while(no_level > 0)
        {
            temp = (tree_node*) queue_front(Q);

            printf("%d ",temp->data);
            if(temp->left)
                queue_enqueue(Q, (void*)temp->left);  //push all its left child into queue
            if(temp->right)
                queue_enqueue(Q, (void*)temp->right); //push the right child too
            
            //queue_pop_tree_node();
            
            queue_dequeue(Q); //this one will pop and return that node, that will be stored in temp for processing
            no_level--;  

        }
        printf("\n"); //One level Complete, now goto the next one
        //FREE(temp); //NOW free it, as we couldnt have done it in the function queue_pop_tree_node()
    } 
}

static void
tree_levelorder_utility(tree_node *root, int level)
{
    if(root != NULL)
    {
        if(level == 1)
            printf("%d ",root->data);
        tree_levelorder_utility(root->left, level - 1);
        tree_levelorder_utility(root->right, level - 1);
    }       
}

int 
tree_is_height_balanced1(tree_node *root)   //returns -1 in case not, else returns height of the tree(+ve value)
{
    if(root == NULL)
        return 0;  
    //printf("root data is %d\n", root->data);
    int lh = tree_is_height_balanced(root->left);
    int rh = tree_is_height_balanced(root->right);
   //printf("lh and rh are: %d %d\n", lh, rh);

//printf("%d lh=%d rh=%d\n", root->data, lh, rh);
    if(lh == -1 || rh == -1 || abs(lh - rh) > 1)   //height difference more than 1
        return -1;

    return bigger(lh, rh) + 1;

}

static int
tree_is_height_balanced_util(tree_node *root, int *height)
{
    if(root == NULL)
    {
        *height = 0; //no need as its already will be done from the parent call
        return TRUE;  
    }

    int lh = 0, rh = 0;
//int lb=0, rb=0;
    int lb = tree_is_height_balanced_util(root->left, &lh);  //lh will be calculated and stored here
    int rb = tree_is_height_balanced_util(root->right, &rh); //same as lh
   
    *height = bigger(lh, rh) + 1;
    return abs(lh - rh ) <= 1 && lb && rb;
}


int
tree_is_height_balanced(tree_node *root)
{
    int height = 0;
    //return tree_is_height_balanced_util(root, &height);
    return tree_is_height_balanced1(root); 
}

tree_node*
tree_construct(int *array1, int *array2, TREE_TRAV type1, TREE_TRAV type2)
{

}

static int
tree_check_if_bst_utility(tree_node* root, int min, int max)
{
    if(root == NULL)
        return TRUE;

    if(root->data < min || root->data > max)
        return FALSE;

    return ( tree_check_if_bst_utility(root->left, min, root->data-1) &&
             tree_check_if_bst_utility(root->right, root->data+1, max));    
}


int 
tree_check_if_bst(tree_node *root)
{        
    return tree_check_if_bst_utility(root, INT_MIN, INT_MAX);
}

static int no_nodes_convert; //for storing number of nodes in tree while converting it to bst in tree_convert_to_bst()
static int no_copied_convert;

static void
tree_inorder_paste_tree(tree_node *root, int *inorder_array)
{
        if(root != NULL)
        {
            tree_inorder_paste_tree(root->left, inorder_array);
            root->data = inorder_array[no_copied_convert];
            no_copied_convert++;
            tree_inorder_paste_tree(root->right, inorder_array);
        }
}
    
static void
tree_inorder_copy_array(tree_node *root, int *inorder_array)
{
        if(root != NULL)
        {
            tree_inorder_copy_array(root->left, inorder_array);
            inorder_array[no_copied_convert] = root->data;
            no_copied_convert++;
            tree_inorder_copy_array(root->right, inorder_array);
        }       
}

void
tree_convert_to_bst(tree_node *root)  //convert a binary to a bst keeping the same structure
{
    no_nodes_convert = tree_size(root);

    //Do the inorder traversal and copy the elements into an array
    int inorder_array[no_nodes_convert];
    no_copied_convert = 0; //no elements copied to the inorder array
    tree_inorder_copy_array(root, inorder_array);
    //printf("printing before sorting...\n");
    //print_array(inorder_array, no_nodes_convert);
    merge_sort(inorder_array, no_nodes_convert);

    //printf("printing after sorting...\n");
    //print_array(inorder_array, no_nodes_convert);

    no_copied_convert = 0;                              //reset this count so that this can be used in paste_array()
    tree_inorder_paste_tree(root, inorder_array);
    
    //printf("CONVERSION DONE...lets see how it is now...\n");
   // tree_print(root, 0); 

}

int 
tree_are_mirrors(tree_node* root1, tree_node* root2) //mirrors with same data too, along with structure
{
    if(root1 == NULL && root2 == NULL)
        return TRUE;
    if(root1 == NULL || root2 == NULL)
        return FALSE;

    return (root1->data == root2->data && 
            tree_are_mirrors(root1->left, root2->right) &&
            tree_are_mirrors(root1->right, root2->left));

    return FALSE;
}

int 
tree_are_struct_mirrors(tree_node* root1, tree_node* root2)  //mirrors with same structure, data might vary
{
   if(root1 == NULL && root2 == NULL)
        return TRUE; 
    if(root1 == NULL || root2 == NULL)
        return FALSE;
    
    return (tree_are_struct_mirrors(root1->left, root2->right) &&
            tree_are_struct_mirrors(root1->right, root2->left));
    
    return FALSE; 
}

int 
tree_is_mirror(tree_node *root)
{
    
    return tree_are_mirrors(root, root);
}

tree_node*
tree_convert_mirror(tree_node *root)
{
    if(!root)
        return NULL;
    tree_convert_mirror(root->left);  
    tree_convert_mirror(root->right);
    
    //swap left and right pointers/nodes now
    tree_node *temp = root->left;
    root->left = root->right; 
    root->right = temp;

    return root; 

}

int 
tree_are_identical(tree_node *root1, tree_node* root2)
{
    if(!root1 && !root2) //both are NULL
        return 1;

    if(root1 && root2)  //both are not empty/NULL
    {
        return (root1->data == root2->data &&
                tree_are_identical(root1->left, root2->left) &&
                tree_are_identical(root1->right, root2->right)); //three conditions should be true
    }
    return 0;

}

int 
tree_are_struct_identical(tree_node* root1, tree_node* root2) //same structure, data may be different
{
    if(!root1 && !root2) //both are NULL
        return 1;

    if(root1 && root2)  //both are not empty/NULL
    {
        return (tree_are_struct_identical(root1->left, root2->left) &&
                tree_are_struct_identical(root1->right, root2->right)); //only two conditions should be true, no need for data match
    }
    return 0;
}

void 
tree_delete(tree_node *root)
{
    if(root)
    {
        tree_delete(root->left);   //delete left subtree
        tree_delete(root->right);  //delete right subtree
        FREE(root);                //delete the node now

    }
}

tree_node* 
tree_lca(tree_node *root, int no1, int no2)
{
    
}

int
tree_is_foldable(tree_node* root)
{
    if(!root)
        return TRUE;
    
    return tree_are_struct_mirrors(root->left, root->right);
}


