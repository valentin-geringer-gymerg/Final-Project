#include <dirent.h>
#include "../helpers.h"
#include <stdio.h>
#include <string.h>

error_message find_name(char* options[], int opc, char* flags[], int flc)
{
    error_message result;

    int case_sense = 1;
    int sub = 0;

    for (int i = 0; i < flc; i++)
    {
        if (!strcmp("-c", flags[i]))
        {
            case_sense = 0;
        }

        if (!strcmp("-s", flags[i]))
        {
            sub = 1;
        }
    }

    char* directory = (opc >= 2) ? options[1] : "./";
    DIR *dir = opendir(directory);
    if (dir == NULL)
    {
        result.error = 12;
        result.message = "find-name: Error 12: Could not open directory";
        return result;
    }
    struct dirent *ent = readdir(dir);
    while (ent != NULL)
    {
        int is_equal = 0;
        switch (case_sense)
        {
            case 0:
                switch (sub)
                {
                case 0:
                    is_equal = !(strcasecmp(options[0], ent->d_name));
                    print("1");
                    break;
                
                default:
                    is_equal = !(strcasestr(options[0], ent->d_name) == NULL);
                    print("2");
                    break;
                }
            default:
                switch (sub)
                {
                case 0:
                    is_equal = !(strcmp(options[0], ent->d_name));
                    print("3");
                    break;
                
                default:
                    printf("%s\n", strstr(options[0], ent->d_name));
                    is_equal = (strstr(options[0], ent->d_name) != NULL);
                    printf("%i", is_equal);
                    print("4");
                    break;
                }
        }
        if (is_equal){
            printf ("%s\n", ent->d_name);
        }
        ent = readdir(dir);
    }

    result.error = 0;
    result.message = "";
    return result;
}