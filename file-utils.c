#include "helpers.h"
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define COMMAND_COUNT 1

typedef struct{
    char* name;
    int min_options;
    int max_options;
} command;

command commands[] = {
    {"cp-it", 2, 4},
    {"find-content", 1, 2},
    {"find-name", 1, 2},
};

bool command_exists = false;
int command_index = -1;

char cur_path[PATH_MAX];

int main(int argc, char *argv[]){

    if (argc < 2){
        print("Error 1: Usage: file-utils [command] [options] [flags]");
        return 1;
    }

    for (int i = 0; i < COMMAND_COUNT; i++){
        if (!strcmp(argv[1], commands[i].name)){
            command_exists = true;
            command_index = i;
            break;
        }
    }
    if (!command_exists){
        print("Error 2: Unknown command. For full command list use \"file-utils -h\".");
        return 2;
    }

    if (getcwd(cur_path, sizeof(cur_path)) == NULL){
        print("Error 3: Could not get working directory");
        return 3;
    }
    printf("Cur_directory: %s\n", cur_path);


}