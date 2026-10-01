#include "header.h"

int save_db(Hash_t *ht)
{
    char filename[100];

    printf("Enter database file name: ");
    scanf("%99s", filename);

    FILE *fptr = fopen(filename, "w");

    if(fptr == NULL)
    {
        printf("ERROR : Unable to create database file.\n");
        return FAILURE;
    }

    for(int i = 0; i < HASH_SIZE; i++)
    {
        Mlist *mtemp = ht[i].link;

        while(mtemp != NULL)
        {
            fprintf(fptr, "#%d;%s;%d;",
                    i,
                    mtemp->word,
                    mtemp->fileCount);

            Slist *stemp = mtemp->subLink;

            while(stemp != NULL)
            {
                fprintf(fptr, "%s;%d;",
                        stemp->fileName,
                        stemp->wordCount);

                stemp = stemp->link;
            }

            fprintf(fptr, "\n");

            mtemp = mtemp->link;
        }
    }

    fclose(fptr);

    return SUCCESS;
}