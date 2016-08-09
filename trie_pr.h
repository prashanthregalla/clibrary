#ifndef PR_TRIE_H
#define PR_TRIE_H


typedef struct trie_t trie;

trie* trie_create();
void trie_destroy(trie *Trie);

int trie_find(trie *Trie, const char *word);  //search trie for word
int trie_search(trie *Trie, const char *word);  //search trie for word, another name for find

void trie_insert(trie *Trie, const char *word); 
void trie_delete(trie *Trie, const char *word);

int trie_size(trie *Trie);
int trie_is_empty(trie *Trie);


int trie_frequency(trie *Trie, const char *word);
void trie_print(trie *Trie);


#endif
