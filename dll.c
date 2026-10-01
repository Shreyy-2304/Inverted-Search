#include "header.h"

int insert_filename(Flist **head, char *filename)
{
    Flist *new = malloc(sizeof(Flist));

    if(new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->file_name, filename);
    new->link = NULL;

    // If list is empty
    if(*head == NULL)
    {
        *head = new;
    }
    else
    {
        Flist *temp = *head;

        // Go to last node
        while(temp->link != NULL)
        {
            temp = temp->link;
        }

        // Insert new node at last
        temp->link = new;
    }

    return SUCCESS;
}