#include "header.h"

int update_db(Hash_t *ht)
{
    char filename[100];

    printf("Enter database file name to update from: ");
    scanf("%99s", filename);

    FILE *fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        printf("ERROR : Unable to open database file.\n");
        return FAILURE;
    }

    /*
     * Clear current hash table.
     * Normally update is expected on an empty database,
     * but this prevents duplicate entries.
     */
    for(int i = 0; i < HASH_SIZE; i++)
    {
        ht[i].link = NULL;
    }

    char line[1000];

    while(fgets(line, sizeof(line), fptr) != NULL)
    {
        char *token = strtok(line, ";");

        if(token == NULL)
            continue;

        if(token[0] == '#')
            token++;

        int index = atoi(token);

        token = strtok(NULL, ";");

        if(token == NULL)
            continue;

        char word[100];

        strcpy(word, token);

        token = strtok(NULL, ";");

        if(token == NULL)
            continue;

        int fileCount = atoi(token);

        Mlist *mnew = malloc(sizeof(Mlist));

        if(mnew == NULL)
        {
            fclose(fptr);
            return FAILURE;
        }

        mnew->word = malloc(strlen(word) + 1);

        if(mnew->word == NULL)
        {
            free(mnew);
            fclose(fptr);
            return FAILURE;
        }

        strcpy(mnew->word, word);

        mnew->fileCount = fileCount;
        mnew->subLink = NULL;
        mnew->link = NULL;

        /*
         * Read all fileName / wordCount pairs.
         */
        Slist *slast = NULL;

        for(int i = 0; i < fileCount; i++)
        {
            token = strtok(NULL, ";");

            if(token == NULL)
                break;

            char fileName[MAX_FILENAME];

            strcpy(fileName, token);

            token = strtok(NULL, ";");

            if(token == NULL)
                break;

            int wordCount = atoi(token);

            Slist *snew = malloc(sizeof(Slist));

            if(snew == NULL)
            {
                fclose(fptr);
                return FAILURE;
            }

            snew->fileName = malloc(strlen(fileName) + 1);

            if(snew->fileName == NULL)
            {
                free(snew);
                fclose(fptr);
                return FAILURE;
            }

            strcpy(snew->fileName, fileName);

            snew->wordCount = wordCount;
            snew->link = NULL;

            if(mnew->subLink == NULL)
            {
                mnew->subLink = snew;
            }
            else
            {
                slast->link = snew;
            }

            slast = snew;
        }

        /*
         * Insert Mlist into hash table.
         */
        if(ht[index].link == NULL)
        {
            ht[index].link = mnew;
        }
        else
        {
            Mlist *mlast = ht[index].link;

            while(mlast->link != NULL)
                mlast = mlast->link;

            mlast->link = mnew;
        }
    }

    fclose(fptr);

    return SUCCESS;
}