/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Struct for trie
typedef struct node {
    bool is_word;
    struct node* children[27];
} node;

// Root node pointer
node* root;

// Word count
int wordCounter = 0;

int getIdx(char c) {
    return abs((tolower(c) - 65) % 32);
}

// Helper for loading dictionary into the trie
void insert(char* word) {
    if (root == NULL) {
        root = calloc(sizeof(node), 1);
    }
     
    node* crawler = root;
    int len = strlen(word);
    int idx; 
     
    for (int i = 0; i < len; i++) {
        idx = getIdx(word[i]);
        if (crawler->children[idx] == NULL) {
             crawler->children[idx] = calloc(sizeof(node), 1);
             crawler = crawler->children[idx];
        }else {
            crawler = crawler->children[idx];
        }
    }
    
    crawler->children[idx] = NULL;
    crawler->is_word = true;
    
}

// Helper to check if the word is in the trie
bool checkWord(const char* word) {
    if (root != NULL) {
        
        node* crawler = root;
        int len = strlen(word);
        int idx;
        for (int i = 0; i < len; i++) {
            idx = getIdx(word[i]);
            if (crawler->children[idx] != NULL) {
                 crawler = crawler->children[idx];
            }else {
                return false;
            }
        }
        if (crawler->is_word == true) {
            //printf("Word found!!\n");
            return true;
        }
    }
    
    return false;
}

// Helper to unload words from the trie
void unloadWords(node* node) {
    
    if (node == NULL) {
        node = root;
    }
    
    for (int i = 0; i < 27; i++) {
        if (node->children[i] != NULL) {
            unloadWords(node->children[i]);                 
        }
    }
    free(node);
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return checkWord(word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    // Try to open the dictionary file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        //unload();
        return false;
    }
    
    char word[LENGTH + 1];
    while(fscanf(fp, "%s", word) == 1) {
        insert(word);
        wordCounter ++;
    }
    
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCounter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
   unloadWords(root);
   return true;
}