#include <stdio.h>
#include <ctype.h>

#include "linkedlist.h"

#define SIZE 500

node* hashtable[SIZE];

int hashFunction(char* word) {
    
    // Calculate the hash of a word to determine the index to store it in the hashtable
    /* D. J. Bernstein hash function */
    int hash;
    while (*word) {
        hash = (33 * 5381 ^ (unsigned char) *word++) % SIZE;
    }
        
    printf("The hash value for %s is %d\n", word, hash);        
            
    return hash;
}

void insert(int index, char* word) {
    if (hashtable[index] == NULL) {
        hashtable[index] = insertFirst(word);
    }else {
        hashtable[index] = insertInPlace(hashtable[index], word);
    }
}


int main(int argc, char* argv[]) {
    
    int idx;
    idx = hashFunction("hello");
    insert(idx, "hello");
    idx = hashFunction("apple");
    insert(idx, "apple");
    idx = hashFunction("cat");
    insert(idx, "cat");
    idx = hashFunction("caterpiller");
    insert(idx, "caterpiller");
    idx = hashFunction("and");
    insert(idx, "and");
    idx = hashFunction("ant");
    insert(idx, "ant");
    idx = hashFunction("ball");
    insert(idx, "ball");
    idx = hashFunction("airplane");
    insert(idx, "airplane");
    idx = hashFunction("airplane");
    insert(idx, "airplane");
    idx = hashFunction("zoo");
    insert(idx, "zoo");
    idx = hashFunction("cat");
    insert(idx, "cat");
    
    for (int i = 0; i < SIZE; i++) {
        if (hashtable[i] != NULL) {
            printf("This is the %dth index\n", i);
            int counter = 0;
            node* temp = hashtable[i];
            while (temp != NULL) {
                printf("The list element at %d is %s\n", counter, temp->word);
                temp = temp->next;
                counter ++;
            }
        }
    }
}