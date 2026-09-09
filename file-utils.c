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

    if (getcwd(cur_path, sizeof(cur_path)) == NULL)
    {
        print("Error 3: Could not get directory command is ran in");
        return 3;
    }
    
    char options[commands[command_index].max_options][LONGEST_OPTION];
    int options_cur_index = 0;
    char flags[commands[command_index].max_flags][LONGEST_FLAG];
    int flags_cur_index = 0;

    for (int i = 2; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            bool already_given = false;

            for (int j = 0; j < (flags_cur_index + 1); j++)
            {
                printf("%s, %s\n", argv[i], flags[j]);
                if (!strcmp(argv[i], flags[j]))
                {
                    already_given = true;
                    break;
                }
            }

            if (already_given)
            {
                print("Flag ignored because it already exists");
                continue;
            }

            for (int j = 0; j < (strlen(argv[i]) + 1); j++)
            {
                flags[flags_cur_index][j] = argv[i][j];
            }
            flags_cur_index += 1;
            print("Flag");
            continue;
        }
        for (int j = 0; j < (strlen(argv[i]) + 1); j++)
        {
            options[options_cur_index][j] = argv[i][j];
        }
        options_cur_index += 1;
        print("Option");
    }

}