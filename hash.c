#include "header.h"

int init_hash_table(Hash_t *ht)
{
    for(int i = 0; i < HASH_SIZE; i++)
    {
        ht[i].index = i;
        ht[i].link = NULL;
    }

    return SUCCESS;
}