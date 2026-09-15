#include <ctype.h>
#include "../helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_file_number(char* name)
{
    int dot_ind = -1;

    int name_length = strlen(name);

    for (int i = 0; i < name_length; i++)
    {
        if (name[i] == '.')
        {
            dot_ind = i;
            break;
        }
    }

    if (dot_ind == -1)
    {
        dot_ind = name_length + 1;
    }

    int num_start = -1;

    for (int i = (dot_ind - 1); i >= 0; i--)
    {
        if (!isdigit(name[i]))
        {
            num_start = i + 1;
            break;
        }
    }

    printf("%i, %i\n", num_start, dot_ind);

    if (num_start == -1)
    {
        return 0;
    }

    char number[dot_ind - num_start + 1];

    for (int i = num_start; i < dot_ind; i++)
    {
        number[i-num_start] = name[i];
    }
    number[dot_ind-num_start] = '\0';
    print(number);
    int file_number = atoi(number);

    return file_number + 1;

}

error_message cp_it(char* options[], int opc, char* flags[], int flc, char* path)
{
    error_message result;
    if (opc < 2)
    {
        result.error = 8;
        result.message = "Error 8: Too few options given(cp-it)";
        return result;
    }

    char* file_path = options[0];
    int amount = atoi(options[1]);

    if (!(amount > 0))
    {
        result.error = 9;
        result.message = "Error 9: Could not convert option[amount] to int(cp-it)";
        return result;
    }

    int start = (opc >= 3) ? atoi(options[2]) : get_file_number(file_path);

    printf("%i\n", start);

    result.error = 0;
    result.message = "";
    return result;
}