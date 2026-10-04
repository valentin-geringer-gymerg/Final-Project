#include <ctype.h>
#include "../helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    int copy;
    char* name;
} file_info;


int get_dot_position(char* name);

int get_num_start(char* name, int dot_ind);

long get_file_number(char* name, int dot_ind, int num_start);

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

    int dot_ind = get_dot_position(file_path);
    int num_start = get_num_start(file_path, dot_ind);

    char* file_name = options[0];

    char prefix[num_start];

    for (int i = 0; i < (num_start); i++)
    {
        prefix[i] = file_name[i];
    }

    prefix[num_start] = '\0';
    
    int file_number = get_file_number(file_path, dot_ind, num_start);

    int start = (opc >= 3) ? atoi(options[2]) : file_number + 1;

    int max_digits = get_digits(start + amount - 1);

    char number[max_digits + 1];

    int suffix_length = strlen(file_name) - (num_start + get_digits(file_number)) + 1;
    char suffix[suffix_length];

    for (int i = 0; i < (suffix_length); i++)
    {
        suffix[i] = file_name[i + num_start + get_digits(file_number)];
    }
    
    FILE *og_file = fopen(file_name, "r");

    if (og_file == NULL)
    {
        result.error = 10;
        result.message = "cp-it: Error 10: Could not open file";
        return result;
    }

    file_info copies[amount];

    for (int i = 0; i < amount; i++)
    {
        char* first_cat = concat(prefix, itoa(start+i));
        char* second_cat = concat(first_cat, suffix);
        copies[i].name = malloc(sizeof(second_cat));
        free(first_cat);
        for (int j = 0, length = strlen(second_cat) + 1; j < length; j++)
        {
            copies[i].name[j] = second_cat[j];
        }
        free(second_cat);

        // TODO: Check whether file already exist and ask user whether to copy anyways or not
        if (access(copies[i].name, F_OK) != 0)
        {
            copies[i].copy = 1;
            continue;
        }
        char confirmation;
        printf("%s already exists. Do you want to copy it anyways? [y/n]", copies[i].name);
        scanf("%c", &confirmation);
        if (confirmation != 'y')
        {
            copies[i].copy = 1;
            continue;
        }
        copies[i].copy = 0;
    }

    char c;

    while (fread(&c, sizeof(BYTE), 1, og_file) != 0)
    {

    } 

    result.error = 0;
    result.message = "";
    return result;
}

int get_dot_position(char* name)
{
    //Get the position of the dot in the file name
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

    return dot_ind;
}

int get_num_start(char* name, int dot_ind)
{
    //Gets the position of the first digit of the number in the file before the dot
    int num_start = -1;

    for (int i = (dot_ind - 1); i >= 0; i--)
    {
        if (!isdigit(name[i]))
        {
            num_start = i + 1;
            break;
        }
    }

    return num_start;

}

long get_file_number(char* name, int dot_ind, int num_start)
{
    // Converts the number before the dot in the file name to an int

    if (num_start == -1)
    {
        return -1;
    }

    char number[dot_ind - num_start + 1];

    for (int i = num_start; i < dot_ind; i++)
    {
        number[i-num_start] = name[i];
    }
    number[dot_ind-num_start] = '\0';
    long file_number = atol(number);

    return file_number;

}