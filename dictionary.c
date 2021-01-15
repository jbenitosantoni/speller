// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

int counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_word;
    hash_word = hash(word);
    node *cursor = table[hash_word];
    while(cursor != NULL) {
        if (strcasecmp(word, cursor->word) == 0)
            return true;
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int first_letter_ascii = (int) word[0];
    if (first_letter_ascii >= 65 && first_letter_ascii <= 90) {
        return (first_letter_ascii - 65);
    }
    else if (first_letter_ascii >= 97 && first_letter_ascii <= 122) {
        return (first_letter_ascii - 97);
    }

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *fp;
    char *word = malloc(sizeof(char) * (LENGTH + 1));
    int hash_word;
    fp = fopen(dictionary, "r");
    if (fp == NULL)
        return false;
    while (fscanf(fp, "%s", word) != EOF) {
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            unload();
            return false;
        }
        strcpy(n->word, word);
        hash_word = hash(word);
        if (table[hash_word] == NULL) {
            n->next = NULL;
            table[hash_word] = n;
            counter++;
        } else {
            n->next = table[hash_word];
            table[hash_word] = n;
            counter++;
        }
    }
    fclose(fp);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *head = NULL;
    node *cursor = head;
    // freeing linked lists
    while (cursor != NULL)
    {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    return true;
}
