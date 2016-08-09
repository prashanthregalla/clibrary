#include "trie_pr.h"
#include "global_vars_pr.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

typedef struct trie_node
{
    int is_leaf;
    int count;                                        //count is FREQUENCY of a word
    struct trie_node *alphabet[ALPHABET_SIZE];        
}trie_node;

struct trie_t
{
    int no_words;
    trie_node *root;
};

typedef struct trie_t trie;

static trie_node* create_new_trie_node();
static int trie_is_free_node(trie_node *Trie_node);
static int trie_is_leaf_node(trie_node *Trie_node);
static int trie_delete_utility(trie_node *root, const char *word, int level, int length); //used by trie_delete function
    
static trie_node*                    //create a new trie_node structure
create_new_trie_node()
{
    trie_node *new_node = MALLOC(trie_node);
    
    new_node->is_leaf = FALSE;
    new_node->count = 0;
    
    for(int i=0; i < ALPHABET_SIZE; i++)   
        new_node->alphabet[i] = NULL;

    return new_node;
}

trie* 
trie_create()
{
    trie *new_trie = MALLOC(trie);
    new_trie->no_words = 0;
    new_trie->root = create_new_trie_node();

    return new_trie;   
}

void 
trie_destroy(trie *Trie)
{
    Trie->no_words = 0;
    FREE(Trie->root);
}

static int 
trie_is_free_node(trie_node *Trie_node)
{
    for(int i=0; i< ALPHABET_SIZE; i++)
        if(Trie_node->alphabet[i] != NULL)
            return FALSE;

    return TRUE;
}

static int 
trie_is_leaf_node(trie_node *Trie_node)
{
    return Trie_node->is_leaf;
}

int 
trie_size(trie *Trie)
{
    return Trie->no_words;
}

int
trie__frequency(trie *Trie, const char *word)
{
    trie_node *pfollow = Trie->root;
    int length = strlen(word);

    for(int i=0; i<length; i++)
    {
        int index = CHAR_TO_INDEX_LOWER(word[i]);
        if(pfollow->alphabet[index] == NULL)     //word not present in this trie
            return FALSE;

        pfollow = pfollow->alphabet[index];
    }

    if(pfollow != NULL && pfollow->is_leaf)
        return pfollow->count;
    else
        return 0;
}    

int 
trie_is_empty(trie *Trie)
{
    return Trie->no_words == 0;
}

int 
trie_find(trie *Trie, const char *word)  //search trie for word
{
    trie_node *pfollow = Trie->root;
    int length = strlen(word);

    for(int i=0; i<length; i++)
    { 
        int index = CHAR_TO_INDEX_LOWER(tolower(word[i]));
        if(pfollow->alphabet[index] == NULL)     //word not present in this trie
            return FALSE;
    
        pfollow = pfollow->alphabet[index];
    }   
    
    return(pfollow !=NULL && pfollow->is_leaf);
}

int 
trie_search(trie *Trie, const char *word)  //search trie for word, another name for find
{
    return trie_find(Trie, word);
}

void 
trie_insert(trie *Trie, const char *word)  
{
    trie_node *pfollow = Trie->root;
    int length = strlen(word);
    
    for(int i=0; i<length; i++)
    {

        int index = CHAR_TO_INDEX_LOWER(tolower(word[i]));  //also can change in the MACRO---add tolower there
        if(pfollow->alphabet[index] == NULL)       //new entry here it seems
            pfollow->alphabet[index] = create_new_trie_node();

        pfollow =  pfollow->alphabet[index];
    }
    pfollow->is_leaf = 1;  //insertion done, marking it as a leaf node
    pfollow->count++;      //Increment the frequency
    Trie->no_words++;      //new word added, increment the count 
}

static int deleted_word_frequency = 0; 

static int 
trie_delete_utility(trie_node *pfollow, const char *word, int level, int length) //used by trie_delete function
{
    if(pfollow)
    {
        if(level == length)  //we are at the (level) node which is/supposed to be end of this word
        {
            pfollow->is_leaf = FALSE;  //mark it as non_leaf now, as we are deleting this word
            deleted_word_frequency = pfollow->count; //static global, for delete_trie function to decrease the no_words in TRIE
            pfollow->count = 0;          //make count = 0
            
            if(trie_is_free_node(pfollow))  //No more other words with this prefix,we can delete this node, mark is for deletion 
                return TRUE;                //TRUE: parent node will delete this as this is free node    
            
            return FALSE;                   //FALSE: this is not free node, other words prsent, DONT DELETE
        }
        else
        {
            int index = CHAR_TO_INDEX_LOWER(tolower(word[level]));
            if((trie_delete_utility(pfollow->alphabet[index], word, level+1, length) != 0)) 
            {
                //we have to delete the node below this level as the return value was TRUE(free_node)
                FREE(pfollow->alphabet[index]);

                //now check if this is a leaf node or a free node
                //we should not delete this node if any of those is true, convey that to the parent of this node
                //if it is not a leaf node and it is free then send TRUE upstairs, else send FALSE
                return (!trie_is_leaf_node(pfollow) &&  trie_is_free_node(pfollow));
            }
        }        
    }
    return FALSE;    
}
    
void 
trie_delete(trie *Trie, const char *word)
{
    int length = strlen(word);

    if(length > 0)
        trie_delete_utility(Trie->root, word, 0, length);

    //now if the word got, deleted we need to decrease the Trie->size by that frequency, which is stored in deleted_word_frequency
    Trie->no_words = Trie->no_words - deleted_word_frequency;

}

static void 
trie_print_utility(trie_node *root)
{
    if(root == NULL)
        return;
    
    for(int i=0; i < ALPHABET_SIZE; i++)
    {
        if(root->alphabet[i] != NULL)
        {
            printf("%c", (char)(i+97));
            if(root->alphabet[i]->is_leaf)
                printf(" ");
            trie_print_utility(root->alphabet[i]);
            
        }
    }
}

static int
trie_print_node(trie_node *root)   //helper for printing all NON NULL chars in a trie_node...for debugging purpose
{
    for(int i=0; i<26; i++)
        if(root->alphabet[i] != NULL)
            printf("%c ", (char)(i+97));
    printf("\n");
}
    
void 
trie_print(trie *Trie)
{
    //trie_print_node(Trie->root);
    //return;
    trie_print_utility(Trie->root);

}

