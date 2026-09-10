#include "helpers.h"
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
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
    {"find-content", 1, 2, 1},
    {"find-name", 1, 2, 1},
};

const int COMMAND_COUNT = sizeof(commands)/sizeof(command);

bool command_exists = false;
int command_index = -1;

char cur_path[PATH_MAX];

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
    char *flags[commands[command_index].max_flags];
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
            printf("Added Flag %s to index %i\n", flags[flags_cur_index - 1], flags_cur_index - 1);
            //print("Flag");
            continue;
        }
        options[options_cur_index] = argv[i];
        options_cur_index += 1;
        printf("Added Option %s to index %i\n", options[options_cur_index - 1], options_cur_index - 1);
        //print("Option");
    }

    for (int i = 0; i < flags_cur_index; i++)
    {
        printf("Flag %i: %s\n", i, flags[i]);
    }

    for (int i = 0; i < options_cur_index; i++)
    {
        printf("Option %i: %s\n", i, options[i]);
    }

}