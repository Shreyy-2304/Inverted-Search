#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define MAX_FILENAME 15
#define HASH_SIZE 27


/* ---------------- Flist ---------------- */

typedef struct Node
{
    char file_name[MAX_FILENAME];
    struct Node *link;

} Flist;


/* ---------------- Slist ---------------- */

typedef struct SubNode
{
    int wordCount;
    char *fileName;

    struct SubNode *link;

} Slist;


/* ---------------- Mlist ---------------- */

typedef struct MainNode
{
    int fileCount;
    char *word;

    Slist *subLink;
    struct MainNode *link;

} Mlist;


/* ---------------- Hash Table ---------------- */

typedef struct Hash
{
    int index;
    Mlist *link;

} Hash_t;


/* ---------------- Function Prototypes ---------------- */

/* Validation */
int read_and_validate(int argc, char *argv[], Flist **head);

/* Flist */
int insert_filename(Flist **head, char *filename);

/* Database creation */
int create_db(Flist *f_head, Hash_t *ht);

/* Display */
int display_db(Hash_t *ht);

/* Search */
int search_db(Hash_t *ht);

/* Update */
int update_db(Hash_t *ht);

/* Save */
int save_db(Hash_t *ht);

//Init hash table
int init_hash_table(Hash_t *ht);

#endif