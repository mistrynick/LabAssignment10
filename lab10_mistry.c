// Nicholas Mistry
// Lab Assignment 10

#include <stdio.h>
#include <stdlib.h> // For the malloc function
#include <string.h>


// Struct provided by TA
typedef struct TrieNode {
    int count;
    struct TrieNode *children[26];
} Trie;

void insert(Trie **ppTrie, char *word); // inserts a tree
int numberOfOccurances(Trie *pTrie, char *word); // Counts occurances
Trie *deallocateTrie(Trie *pTrie); // deletes everything

int main(void) // Code written by Prof. T
{
    Trie *trie = NULL;
    // read the number of words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]); // Change made to parse data
        printf("%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);

  // Check if memory was free'd
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}


void insert(Trie **ppTrie, char *word) {

  // CODE: It will enter into null territory so initialize the first node
    if (*ppTrie == NULL) {  // This code block completes the action
        *ppTrie = (Trie *)malloc(sizeof(Trie));
        (*ppTrie)->count = 0;
        for (int i = 0; i < 26; i++) {
            (*ppTrie)->children[i] = NULL; // Init to Nulls
        }
    }
  // Now we have it setup to take in information 
  // MashAllah
  // Create the tree and it essentially checks the characters and creates a new tree if not inside of the prev tree
    Trie *temp = *ppTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a'; // Using Ascii math to decide indicies
        if (temp->children[index] == NULL) { // Not found condition
            temp->children[index] = (Trie *)malloc(sizeof(Trie)); // init new node
            temp->children[index]->count = 0; // set data for new node
            for (int j = 0; j < 26; j++) { 
                temp->children[index]->children[j] = NULL;
            }
        }
        temp = temp->children[index];
    }
    temp->count++;
}


Trie *deallocateTrie(Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
      // Using Recursion to deallocate all children
      // It will deallocate the ends then go up so everything is free'd in between and thus not lost.
    }
    free(pTrie);
    return NULL;
}
int numberOfOccurances(Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }
    Trie *temp = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) {
          // If not found then return 0
            return 0;
        }
      // else check othern nodes
        temp = temp->children[index];
    }
    return temp->count; // we stored count already
}


