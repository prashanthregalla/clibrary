#ifndef PR_TREE_H
#define PR_TREE_H

typedef int (*segtree_op)(int, int);  //operation for segmentation tree, sum or max or min etc.,   

typedef struct tree_node_t
{
    int data;
    int count;
    int height; //for AVLTREE so that all avltree functions' writing gets simpler. though its a waste of space for each node
    struct tree_node_t *left;
    struct tree_node_t *right;
}tree_node;


typedef enum TRAVERSAL
{
    ALL = 0,
    PREORDER=1,
    INORDER,
    POSTORDER,
    LEVELORDER
}TREE_TRAV;

tree_node* tree_create_node(int data);
void tree_destroy(tree_node *root);

tree_node* tree_add_node(int data);
tree_node* tree_insert(int data);


int tree_height(tree_node *root);
int tree_size(tree_node *root);

void tree_update_height(tree_node* node);
int tree_node_height(tree_node* node);

void tree_inorder(tree_node* root);
void tree_preorder(tree_node* root);
void tree_postorder(tree_node* root);
void tree_levelorder(tree_node* root);

void tree_inorder_iterative(tree_node* root);
void tree_preorder_iterative(tree_node* root);
void tree_postorder_iterative(tree_node* root);
void tree_levelorder_iterative(tree_node* root);


/* print utilities...can/need to uncomment if not necessary
 *
 */

void tree_print(tree_node* root, TREE_TRAV type);
void tree_print_size(tree_node* root);
void tree_print_height(tree_node* root);


/**
 * This function constructs the tree, given any two traversals, one of which is inorder
 * first two arguments are arrays which store the data
 * next two arguments are type_of_traversal of the data in those arrays
 *
 * returns root of the constructed tree
 * 
 *
 *
 */

tree_node* tree_construct(int *array1, int *array2, TREE_TRAV type1, TREE_TRAV type2);
void tree_convert_to_bst(tree_node *root);  //convert a binary to a bst keeping the same structure

/* BINARY SEARCH TREE---coded using two approaches
 * 1. pass root and data ...like how we do it in usual
 * 2. BST ADT---this will be useful in other programs too
 */
 
int tree_check_if_bst(tree_node *root);
void tree_convert_to_bst(tree_node *root); //convert the given tree to BST, with structure intact

// EXTRA FUNCTIONS


int tree_are_mirrors(tree_node* root1, tree_node* root2);  //mirrors with identical data
int tree_are_struct_mirrors(tree_node* root1, tree_node* root2);  //mirrors with same structure, data might vary

int tree_are_struct_identical(tree_node* root1, tree_node* root2); //same structure, data may be different
int tree_are_identical(tree_node *root1, tree_node* root2); //same structure and data too

int tree_is_mirror(tree_node *root); //mirror with same data too
int tree_is_foldable(tree_node* root); //mirror left and right subtrees at root, no need of data match

int tree_is_height_balanced(tree_node *root);
int tree_is_height_balanced1(tree_node *root);

tree_node* tree_convert_mirror(tree_node *root); //exchange left and right subtreses at each node

void tree_delete(tree_node *root);
tree_node* tree_lca(tree_node *root, int no1, int no2);


/* BST ADT */

typedef struct BST_NODE bst; //BST ADT, this is what we return(a pointer to it ofcourse
                             // might need to change it to BST_PR in future(!!??)

bst* bst_create();
void bst_destroy(bst *BST);

int bst_is_empty(bst *BST);
int bst_is_height_balanced(bst *BST);   //returns -1 if unbalanced else returns a +VE value
int bst_is_mirror(bst *BST);

int bst_insert(bst *BST, int data);
tree_node* bst_find(bst *BST, int data);
int bst_delete(bst *BST, int data);
int bst_count_key(bst *BST, int key);

tree_node* bst_max(bst *BST);
tree_node* bst_min(bst *BST);
int bst_median(bst *BST);

int bst_size(bst *BST);
int bst_height(bst *BST);

void bst_inorder(bst *BST);
void bst_preorder(bst *BST);
void bst_postorder(bst *BST);
void bst_levelorder(bst *BST);

tree_node* bst_inorder_successor(bst *BST, int data);
tree_node* bst_inorder_predecessor(bst *BST, int data);
tree_node* bst_lca(bst *BST, int no1, int no2);  //Least Common Ancestor

void bst_print(bst *BST, TREE_TRAV type);

//***** PRINT ROUTINES */

int bst_prin_count_key(bst *BST, int key);
int bst_print_min(bst *BST);
int bst_print_max(bst *BST);
int bst_print_median(bst *BST);
int bst_print_size(bst *BST);
int bst_print_height(bst *BST);
int bst_print_inorder_successor(bst *BST, int data);
int  bst_print_inorder_predecessor(bst *BST, int data);

bst* bst_construct(int *array, int size); //construct BST from a array, keep on inserting until the end of array
bst* bst_construct_optimal(int *array, int size); //construct BST with optimal height, sort the array and then construct

//AVL TREES

typedef struct BST_NODE avltree; //same as BST ADT, this is what we return(a pointer to it ofcourse)

                             // might need to change it to BST_PR in future(!!??)

avltree* avltree_create();
void avltree_destroy(avltree *AVL);

int avltree_is_empty(avltree *AVL);

int avltree_insert(avltree *AVL, int data);
tree_node* avltree_find(avltree *AVL, int data);
int avltree_delete(avltree *AVL, int data);
int avltree_count_key(avltree *AVL, int key);

tree_node* avltree_max(avltree *AVL);
tree_node* avltree_min(avltree *AVL);
int avltree_median(avltree *AVL);


int avltree_size(avltree *AVL);
int avltree_height(avltree *AVL);

void avltree_inorder(avltree *AVL);
void avltree_preorder(avltree *AVL);
void avltree_postorder(avltree *AVL);
void avltree_levelorder(avltree *AVL);

tree_node* avltree_inorder_successor(avltree *AVL, int data);
tree_node* avltree_inorder_predecessor(avltree *AVL, int data);
tree_node* avltree_lca(avltree *AVL, int n1, int n2);

void avltree_print(avltree *AVL, TREE_TRAV type);

//***** PRINT ROUTINES */

int avltree_prin_count_key(avltree *AVL, int key);
int avltree_print_min(avltree *AVL);
int avltree_print_max(avltree *AVL);
int avltree_print_median(avltree *AVL);
int avltree_print_size(avltree *AVL);
int avltree_print_height(avltree *AVL);
int avltree_print_inorder_successor(avltree *AVL, int data);
int avltree_print_inorder_predecessor(avltree *AVL, int data);

avltree* avltree_construct(int *array, int ddsize); //construct AVL from a array, keep on inserting until the end of array


//**** SEGMENTATION TREE **** Elements are/canbe int only ****

typedef struct segtree_node segtree;


//no need to specify operation for query/update, only need to specify it while creating
//boundary_val = 0, when operation is sum/GCD
//             = INT_MAX, when opearation in min
//             = INT_MIN, when operation is max
// one needs to be a little careful of boundary_val 
//we can also use enum SEG_MIN,SEG_MAX,SEG_SUM for these and signature would be create(a, size, op, SEG_MIN)
//segtree_create(a, size, SEGMIN/SEGMAX/SEGGCD/SEGSUM/SEGOTHER, operationOTHER, OTHER_BOUNDARY_VAL)---alternate signature
segtree* segtree_create(int *array, int size, segtree_op operation, int boundary_val);  

//segtree* segtree_create(int *array, int size);
void segtree_destroy(segtree* ST);
int segtree_query(segtree* ST, int l, int r);
void segtree_update_range(segtree* ST, int l, int r, int val);
int* segtree_orig_array(segtree *ST);
void segtree_print(segtree *ST);  //print the segtree_array

#endif
