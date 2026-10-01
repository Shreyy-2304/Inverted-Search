#include "header.h"

int read_and_validate(int argc, char *argv[], Flist **head)
{
    for(int i = 1; i < argc; i++)
    {
        char *extn = strrchr(argv[i], '.');

        if(extn != NULL && strcmp(extn, ".txt") == 0)
        {
            //  check for valid extension
            printf("'%s' is a valid 'txt' file.\n", argv[i]);

            //check whether file is present in the directory or not
            FILE *fptr = fopen(argv[i], "r");

            if(fptr != NULL)
            {
                //check whether file is empty or not
                fseek(fptr, 0, SEEK_END);
                if(ftell(fptr))
                {
                    if(insert_filename(head, argv[i]) == SUCCESS)
                    {
                        printf("'%s' file successfully inserted in the Flist.\n", argv[i]);
                    }
                    else
                    {
                        printf("ERROR : '%s' file is not inserted in Flist.\n", argv[i]);                

                    }
                }
                else
                {
                    printf("ERROR : '%s' file is empty.\n", argv[i]);                
                }             
                  fclose(fptr);
            }
            else
            {
                printf("ERROR : '%s' file is not present.\n", argv[i]);
            }

        }
        else
        {
            printf("ERROR : '%s' not a valid 'txt' file.\n", argv[i]);
        }
    }
    return SUCCESS;
}