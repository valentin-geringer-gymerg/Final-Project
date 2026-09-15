#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

void print(char text[]){
    printf("%s\n", text);
}

char* concat(char* first, char* second)
{
    // Concatenates two strings such that first is followed by second

    // Allocate memory for the first concatenation
        char *cat = malloc(sizeof(char) * (strlen(first) + strlen(second) + 1));

        // Make sure memory was successfully allocated
        if (cat == NULL)
        {   
            print("Error 6: Could not allocate memory");
            return "";
        }

        // Copy the first string to the allocated memory
        for (int i = 0; i < (strlen(first) + 1); i++)
        {
            cat[i] = first[i];
        }

        // Concatenate first string with second string
        strcat(cat, second);

        return cat;
}