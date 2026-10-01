#include "header.h"

int search_db(Hash_t *ht)
{
    char word[50];

    printf("Enter word to search: ");
    scanf("%49s", word);

    int index;

    if(isalpha((unsigned char)word[0]))
        index = tolower((unsigned char)word[0]) - 'a';
    else
        index = 26;

    Mlist *mtemp = ht[index].link;

    while(mtemp != NULL)
    {
        if(strcmp(mtemp->word, word) == 0)
            break;

        mtemp = mtemp->link;
    }

    if(mtemp == NULL)
    {
        printf("Word '%s' not found in database.\n", word);
        return FAILURE;
    }

    printf("\nWord : %s\n", mtemp->word);
    printf("File Count : %d\n", mtemp->fileCount);

    Slist *stemp = mtemp->subLink;

    while(stemp != NULL)
    {
        printf("%s -> %d occurrence(s)\n",
               stemp->fileName,
               stemp->wordCount);

        stemp = stemp->link;
    }

    return SUCCESS;
}