// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

//Total number of words in the dictionary
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)];

    do
    {
        char *listWord = cursor -> word;
        if(strcasecmp(listWord, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    while(cursor != NULL);
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9189q/  //source
    // TODO
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ (tolower(word[i]));
    }
    return hash % N;
    //return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //opening the file
    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }

    char str[LENGTH + 1];
    while(true)
    {
        //fscanf(file, "%s", str);
        if(fscanf(file, "%s", str) == EOF)
        {
            break;
        }

        node *tmp = malloc(sizeof(node));
        if(tmp == NULL)
        {
            return false;
        }

        strcpy(tmp -> word, str);
        tmp -> next = NULL;

        int hashIndex = hash(str);
        if(table[hashIndex] == NULL)
        {
            table[hashIndex] = tmp;
        }
        else
        {
            tmp -> next = table[hashIndex];
            table[hashIndex] = tmp;
        }

        count = count + 1;
        //free(tmp);
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    node *cursor;
    for(int i = 0; i < N; i++)
    {
        tmp = table[i];
        cursor = tmp;
        do
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }
        while(cursor != NULL && tmp != NULL);

        if(cursor != NULL && tmp != NULL)
        {
            return false;
        }
    }
    return true;
}
