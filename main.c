#include "header.h"

int main(int argc, char *argv[])
{
    Flist *f_head = NULL;
    Hash_t hashTable[HASH_SIZE];

    if(argc < 2)
    {
        printf("ERROR : Please pass input files through command line.\n");
        return FAILURE;
    }

    if(read_and_validate(argc, argv, &f_head) != SUCCESS)
    {
        printf("ERROR : File validation failed.\n");
        return FAILURE;
    }

    printf("\nReading and Validation successful.\n");

    if(init_hash_table(hashTable) != SUCCESS)
    {
        printf("ERROR : Hash table initialization failed.\n");
        return FAILURE;
    }

    int choice;

    while(1)
    {
        printf("\n----------------------------------\n");
        printf("          INVERTED SEARCH\n");
        printf("----------------------------------\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("----------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                if(create_db(f_head, hashTable) == SUCCESS)
                    printf("Database created successfully.\n");
                else
                    printf("ERROR : Database creation failed.\n");
                break;

            case 2:
                display_db(hashTable);
                break;

            case 3:
                search_db(hashTable);
                break;

            case 4:
                if(update_db(hashTable) == SUCCESS)
                    printf("Database updated successfully.\n");
                else
                    printf("ERROR : Database update failed.\n");
                break;

            case 5:
                if(save_db(hashTable) == SUCCESS)
                    printf("Database saved successfully.\n");
                else
                    printf("ERROR : Database save failed.\n");
                break;

            case 6:
                printf("Exiting...\n");
                return SUCCESS;

            default:
                printf("ERROR : Invalid choice.\n");
        }
    }

    return SUCCESS;
}