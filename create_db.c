#include "header.h"

int create_db(Flist *f_head, Hash_t *ht)
{
    Flist *temp = f_head;

    /* Traverse through all the files in Flist */
    while(temp != NULL)
    {
        /* Open the current file */
        FILE *fptr = fopen(temp->file_name, "r");

        if(fptr == NULL)
        {
            printf("ERROR : Unable to open '%s'\n", temp->file_name);
            return FAILURE;
        }

        char word[50];

        /* Read words from the current file one by one */
        while(fscanf(fptr, "%49s", word) != EOF)
        {
            int index;

            /*
             * Calculate hash index based on
             * first character of the word.
             *
             * a -> 0
             * b -> 1
             * ...
             * z -> 25
             * special character -> 26
             */
            if(isalpha((unsigned char)word[0]))
            {
                index = tolower((unsigned char)word[0]) - 'a';
            }
            else
            {
                index = 26;
            }

            /*
             * Search for the word in the Mlist
             * of the calculated hash index.
             */
            Mlist *mtemp = ht[index].link;

            while(mtemp != NULL)
            {
                if(strcmp(mtemp->word, word) == 0)
                {
                    break;
                }

                mtemp = mtemp->link;
            }

            /*
             * =====================================================
             * CASE 1:
             * Word is NOT present in the Mlist
             * =====================================================
             */
            if(mtemp == NULL)
            {
                /*
                 * Create a new Mlist node
                 */
                Mlist *mnew = malloc(sizeof(Mlist));

                if(mnew == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                /*
                 * Allocate memory for the word
                 */
                mnew->word = malloc(strlen(word) + 1);

                if(mnew->word == NULL)
                {
                    free(mnew);
                    fclose(fptr);
                    return FAILURE;
                }

                /*
                 * Copy word into Mlist node
                 */
                strcpy(mnew->word, word);

                /*
                 * Since this is the first file
                 * containing this word
                 */
                mnew->fileCount = 1;

                /*
                 * Initialize links
                 */
                mnew->subLink = NULL;
                mnew->link = NULL;

                /*
                 * -------------------------------------------------
                 * Create the first Slist node
                 * -------------------------------------------------
                 */
                Slist *snew = malloc(sizeof(Slist));

                if(snew == NULL)
                {
                    free(mnew->word);
                    free(mnew);
                    fclose(fptr);
                    return FAILURE;
                }

                /*
                 * Allocate memory for file name
                 */
                snew->fileName = malloc(strlen(temp->file_name) + 1);

                if(snew->fileName == NULL)
                {
                    free(snew);
                    free(mnew->word);
                    free(mnew);
                    fclose(fptr);
                    return FAILURE;
                }

                /*
                 * Copy file name
                 */
                strcpy(snew->fileName, temp->file_name);

                /*
                 * First occurrence of the word
                 * in this file
                 */
                snew->wordCount = 1;

                /*
                 * Initialize Slist link
                 */
                snew->link = NULL;

                /*
                 * Connect Slist to Mlist
                 */
                mnew->subLink = snew;

                /*
                 * -------------------------------------------------
                 * Insert Mlist node into Hash Table
                 * -------------------------------------------------
                 */

                /*
                 * If this is the first word
                 * at this hash index
                 */
                if(ht[index].link == NULL)
                {
                    ht[index].link = mnew;
                }
                else
                {
                    /*
                     * Otherwise traverse to the
                     * last Mlist node
                     */
                    Mlist *mlast = ht[index].link;

                    while(mlast->link != NULL)
                    {
                        mlast = mlast->link;
                    }

                    /*
                     * Insert new Mlist node at the end
                     */
                    mlast->link = mnew;
                }
            }

            /*
             * =====================================================
             * CASE 2:
             * Word is already present in the Mlist
             * =====================================================
             */
            else
            {
                /*
                 * Search the Slist corresponding
                 * to this word
                 */
                Slist *stemp = mtemp->subLink;

                while(stemp != NULL)
                {
                    /*
                     * Check whether current file
                     * is already present
                     */
                    if(strcmp(stemp->fileName, temp->file_name) == 0)
                    {
                        break;
                    }

                    stemp = stemp->link;
                }

                /*
                 * =================================================
                 * CASE 2A:
                 * Same word + same file
                 * =================================================
                 */
                if(stemp != NULL)
                {
                    /*
                     * Word already exists in this file.
                     * Increase occurrence count.
                     */
                    stemp->wordCount++;
                }

                /*
                 * =================================================
                 * CASE 2B:
                 * Same word + different file
                 * =================================================
                 */
                else
                {
                    /*
                     * Create a new Slist node
                     */
                    Slist *snew = malloc(sizeof(Slist));

                    if(snew == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }

                    /*
                     * Allocate memory for file name
                     */
                    snew->fileName = malloc(strlen(temp->file_name) + 1);

                    if(snew->fileName == NULL)
                    {
                        free(snew);
                        fclose(fptr);
                        return FAILURE;
                    }

                    /*
                     * Copy file name
                     */
                    strcpy(snew->fileName, temp->file_name);

                    /*
                     * First occurrence of this word
                     * in this new file
                     */
                    snew->wordCount = 1;

                    /*
                     * Initialize link
                     */
                    snew->link = NULL;

                    /*
                     * Insert Slist node
                     */
                    if(mtemp->subLink == NULL)
                    {
                        mtemp->subLink = snew;
                    }
                    else
                    {
                        Slist *slast = mtemp->subLink;

                        while(slast->link != NULL)
                        {
                            slast = slast->link;
                        }

                        slast->link = snew;
                    }

                    /*
                     * Since the word has now appeared
                     * in another file
                     */
                    mtemp->fileCount++;
                }
            }
        }

        /*
         * Close current file
         */
        fclose(fptr);

        /*
         * Move to next file in Flist
         */
        temp = temp->link;
    }

    return SUCCESS;
}