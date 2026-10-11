#include <dirent.h>
#include "../helpers.h"
#include <stdio.h>
#include <string.h>

error_message find_name(char* options[], int opc, char* flags[], int flc)
{
    error_message result;

    DIR *dir = opendir("./");
    if (dir == NULL)
    {
        result.error = 12;
        result.message = "find-name: Error 12: Could not open directory";
        return result;
    }
    struct dirent *ent = readdir(dir);
    while (ent != NULL)
    {
        if (!(strcmp(options[0], ent->d_name)))
        printf ("%s\n", ent->d_name);
        ent = readdir(dir);
    }

    result.error = 0;
    result.message = "";
    return result;
}