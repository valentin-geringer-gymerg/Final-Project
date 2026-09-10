#include "helpers.h"
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LONGEST_FLAG 2
#define LONGEST_OPTION 10000

typedef struct
{
    char* name;
    int min_options;
    int max_options;
    int max_flags;
} command;

command commands[] = 
{
    {"cp-it", 2, 4, 1},
    {"find-content", 1, 2, 3},
    {"find-name", 1, 2, 3},
};

const int COMMAND_COUNT = sizeof(commands)/sizeof(command);

bool command_exists = false;
int command_index = -1;

char cur_path[PATH_MAX];

bool using_help_flag = false;

int main(int argc, char *argv[])
{

    // Make sure that file utils is not ran without any options
    if (argc < 2)
    {
        print("Error 1: Usage: file-utils [command] [options] [flags]");
        return 1;
    }

    if ((argc == 2) && (!strcmp(argv[1],"-h")))
    {
        for (int i = 0; i < COMMAND_COUNT; i++)
        {
            print(commands[i].name);
        }
        return 0;
    }

    // Make sure command exists
    for (int i = 0; i < COMMAND_COUNT; i++)
    {
        if (!strcmp(argv[1], commands[i].name))
        {
            command_exists = true;
            command_index = i;
            break;
        }
    }
    if (!command_exists)
    {
        print("Error 2: Unknown command. For full command list use \"file-utils -h\".");
        return 2;
    }

    // Get directory command is ran in
    if (getcwd(cur_path, sizeof(cur_path)) == NULL)
    {
        print("Error 3: Could not get directory command is ran in");
        return 3;
    }
    
    char *options[commands[command_index].max_options];
    int options_cur_index = 0;
    // Note: Size of array is doubled to avoid error when the user accidentally types wrong flags
    char *flags[commands[command_index].max_flags * 2];
    int flags_cur_index = 0;

    for (int i = 2; i < argc; i++)
    {

        for (int i = 0; i < flags_cur_index; i++)
        {
            printf("Flag %i: %s\n", i, flags[i]);
        }

        for (int i = 0; i < options_cur_index; i++)
        {
            printf("Option %i: %s\n", i, options[i]);
        }

        if (argv[i][0] == '-')
        {
            flags[flags_cur_index] = argv[i];
            flags_cur_index += 1;
            //printf("Added Flag %s to index %i\n", flags[flags_cur_index - 1], flags_cur_index - 1);
            //print("Flag");
            continue;
        }
        options[options_cur_index] = argv[i];
        options_cur_index += 1;
        //printf("Added Option %s to index %i\n", options[options_cur_index - 1], options_cur_index - 1);
        //print("Option");
    }

    for (int i = 0; i < flags_cur_index; i++)
    {
        if (!strcmp(flags[i], "-h"))
        {
            using_help_flag = true;
        }
        //printf("Flag %i: %s\n", i, flags[i]);
    }

    for (int i = 0; i < options_cur_index; i++)
    {
        //printf("Option %i: %s\n", i, options[i]);
    }

    if (using_help_flag)
    {
        char *prefix = "command-templates/";
        char *suffix = ".txt";
        char *command_name = commands[command_index].name;
        char *first_cat = malloc(sizeof(char) * (strlen(prefix) + strlen(command_name) + 1));

        for (int i = 0; i < (strlen(prefix) + 1); i++)
        {
            first_cat[i] = prefix[i];
        }
        strcat(first_cat, command_name);

        char *second_cat = malloc(sizeof(char) * (strlen(first_cat) + strlen(suffix) + 1));

        for (int i = 0; i < (strlen(first_cat) + 1); i++)
        {
            second_cat[i] = first_cat[i];
        }

        strcat(second_cat, suffix);
        free(first_cat);
        //printf("%s\n", second_cat);
        FILE *file = fopen(second_cat, "r");
        if (file == NULL)
        {
            free(second_cat);
            print("Error 5: Could not open template");
            return 5;
        }
        char c;
        while (fread(&c, sizeof(char), 1, file) != 0)
        {
            printf("%c", c);
        }
        print("");
        free(second_cat);
        fclose(file);
        return 0;
    }
}