void print(char text[]);

typedef struct
{
    char* message;
    int error;
} error_message;

error_message cp_it(char* options[], char* flags[], char* path);
error_message find_content(char* options[], char* flags[]);
error_message find_name(char* options[], char* flags[]);