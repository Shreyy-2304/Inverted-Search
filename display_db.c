#include "header.h"

int display_db(Hash_t *ht)
{
    int found = 0;

    printf("\n====================================================\n");
    printf("                 DATABASE\n");
    printf("====================================================\n");

    for(int i = 0; i < HASH_SIZE; i++)
    {
        Mlist *mtemp = ht[i].link;

        while(mtemp != NULL)
        {
            found = 1;

            printf("[%d] %s -> %d file(s) : ",
                   i,
                   mtemp->word,
                   mtemp->fileCount);

            Slist *stemp = mtemp->subLink;

            while(stemp != NULL)
            {
                printf("%s(%d)",
                       stemp->fileName,
                       stemp->wordCount);

                if(stemp->link != NULL)
                    printf(" -> ");

                stemp = stemp->link;
            }

            printf("\n");

            mtemp = mtemp->link;
        }
    }

    if(found == 0)
    {
        printf("Database is empty.\n");
    }

    printf("====================================================\n");

    return SUCCESS;
}